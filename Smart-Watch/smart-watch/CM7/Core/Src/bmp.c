/*
 * bmp.c
 *
 *  Created on: May 7, 2024
 *      Author: Fato
 */

#include <string.h>
#include "bmp.h"


static error_bmp read_sign_bmp(BMP *bmp, uint8_t *slotsBuf);
static error_bmp read_fSize_bmp(BMP *bmp, uint8_t *slotsBuf);
static error_bmp read_off_bmp(BMP *bmp, uint8_t *slotsBuf);
static error_bmp read_width_bmp(BMP *bmp, uint8_t *slotsBuf);
static error_bmp read_height_bmp(BMP *bmp, uint8_t *slotsBuf);
static error_bmp read_depth_bmp(BMP *bmp, uint8_t *slotsBuf);
static error_bmp skip_slots_bmp(BMP *bmp, uint16_t byteToSkip);
static error_bmp read_bmp_blocks(BMP *bmp, uint8_t *buf, size_t nbytes);
static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx);
static void imageWindowed(doubleFormat *data);


error_bmp bmp_init(BMP *bmp, FIL *fil, char *fName, const void (*drawFunc))
{

	bmp->fp = fil;
	bmp->name = fName;
	bmp->draw = drawFunc;

	return open_bmp(bmp);

}


error_bmp open_bmp(BMP *bmp)
{

	FRESULT fres; 		//Result after operations


    fres = f_open(bmp->fp, bmp->name, FA_READ);

    if(fres!=FR_OK)
    	return ERROR_BMP_OPEN;

    /* Header */

    return read_header_bmp(bmp);

}



////////////////////////////////////////////////////////////////////////////////
// Params:
// name - file name
// x,y - start x,y on the screen
// wd,ht - width, height of the video (raw data has no header with such info)
// nl - num lines read in one operation (nl*wd*2 bytes are loaded)
// skipFr - num frames to skip
//
error_bmp showImageBmp(BMP *bmp)
{

	FRESULT fres; 		//Result after operations

	uint8_t bufRam[MAX_BUFF_RAM];
	doubleFormat pBuf;

	uint32_t sectionSizeByte;
	uint32_t sectionDim;
	uint8_t bytePerPxl;

	UINT byteRead;


	pBuf.u8Arr = bufRam;					// Pointer to buf in order to convert format from uint8_t to uint16_t

	sectionSizeByte = ( ( bmp->height * bmp->width ) * ( bmp->depth / 8 ) );
	sectionDim = ( bmp->height * bmp->width );
	bytePerPxl = ( bmp->depth / 8 );

	// Point to the initial position
	f_rewind(bmp->fp);


	while(!f_eof(bmp->fp))
	{

		// Skip header file
		f_lseek(bmp->fp, bmp->fp->fptr + bmp->offset);

		memset(bufRam, 0, MAX_BUFF_RAM);
		fres = f_read(bmp->fp, bufRam, sectionSizeByte, &byteRead);

		if(fres != FR_OK)
			return ERROR_BMP_READ_FILE;

		if(byteRead != sectionSizeByte)
			return ERROR_BMP_READ_FEW_DATA;

		depth24To16(&pBuf, sectionDim, bytePerPxl);
		imageWindowed(&pBuf);

		bmp->draw(0, 0, bmp->width, bmp->height, pBuf.u8Arr);

	}

	return BMP_OK;

}


error_bmp read_header_bmp(BMP *bmp)
{

	uint8_t slotRam[10];
	uint8_t *pSlotRam = slotRam;

	memset(slotRam, 0, 10);
	if(read_sign_bmp(bmp, pSlotRam) != BMP_OK)
		return ERROR_BMP_HEADER;

	memset(slotRam, 0, 10);
	read_fSize_bmp(bmp, pSlotRam);

	skip_slots_bmp(bmp, 4);

	memset(slotRam, 0, 10);
	read_off_bmp(bmp, pSlotRam);

	skip_slots_bmp(bmp, 4);

	memset(slotRam, 0, 10);
	read_width_bmp(bmp, pSlotRam);

	memset(slotRam, 0, 10);
	read_height_bmp(bmp, pSlotRam);

	skip_slots_bmp(bmp, 2);

	memset(slotRam, 0, 10);
	read_depth_bmp(bmp, pSlotRam);

	return BMP_OK;

}


//////////////////////////////////////////////////////////////


static error_bmp read_sign_bmp(BMP *bmp, uint8_t *slotsBuf)
{

	read_bmp_blocks(bmp, slotsBuf, 2);

	if(memcmp(slotsBuf, "BM", 2) != 0)
		return ERROR_BMP_HEADER;

	return BMP_OK;

}


static error_bmp read_fSize_bmp(BMP *bmp, uint8_t *slotsBuf)
{

	read_bmp_blocks(bmp, slotsBuf, 4);

	return BMP_OK;

}


static error_bmp read_off_bmp(BMP *bmp, uint8_t *slotsBuf)
{

	read_bmp_blocks(bmp, slotsBuf, 4);

	bmp->offset = slotsBuf[0];

	return BMP_OK;

}


static error_bmp read_width_bmp(BMP *bmp, uint8_t *slotsBuf)
{

	read_bmp_blocks(bmp, slotsBuf, 4);

	bmp->width = FILE_WORD(slotsBuf);

	return BMP_OK;

}


static error_bmp read_height_bmp(BMP *bmp, uint8_t *slotsBuf)
{

	read_bmp_blocks(bmp, slotsBuf, 4);

	bmp->height = FILE_WORD(slotsBuf);

	return BMP_OK;

}


static error_bmp read_depth_bmp(BMP *bmp, uint8_t *slotsBuf)
{

	read_bmp_blocks(bmp, slotsBuf, 2);

	bmp->depth = slotsBuf[0];

	return BMP_OK;

}


static error_bmp skip_slots_bmp(BMP *bmp, uint16_t byteToSkip)
{

	uint8_t dummyBuf[byteToSkip];
	uint8_t *pDummyBuf = dummyBuf;

	read_bmp_blocks(bmp, pDummyBuf, byteToSkip);

	return BMP_OK;

}


static error_bmp read_bmp_blocks(BMP *bmp, uint8_t *buf, size_t nbytes)
{

	UINT cnt;
	FRESULT fres; 		//Result after operations

    fres = f_read(bmp->fp, buf, nbytes, &cnt);

    if(fres!=FR_OK)
    	return ERROR_BMP_READ_FILE;

    if(cnt!=nbytes)
    	return ERROR_BMP_READ_FEW_DATA;

    return BMP_OK;

}


static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx)
{

	uint8_t b;
	uint8_t g;
	uint8_t r;


	for(int i = 0 ; i < length ; i++)
	{

		b = pxArr->u8Arr[i*bpx];
		g = pxArr->u8Arr[i*bpx+1];
		r = pxArr->u8Arr[i*bpx+2];

		pxArr->u16Arr[i] = color565(b, r, g);
		pxArr->u16Arr[i] = ( ( ( pxArr->u16Arr[i] & 0x00ff ) << 8 ) | (( pxArr->u16Arr[i] & 0xff00 ) >> 8) );

	}

}


static void imageWindowed(doubleFormat *data)
{

	uint16_t tmp;


	for(int i = 0 ; i < 240 ; i++)
	{

		for(int j = 0 ; j < 120 ; j++)
		{

			tmp = data->u16Arr[j+(i*240)];
			data->u16Arr[j+(i*240)] = data->u16Arr[(240-1-j)+(i*240)];
			data->u16Arr[(240-1-j)+(i*240)] = tmp;

		}

	}

}