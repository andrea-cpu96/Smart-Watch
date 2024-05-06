/*
 * sd_ex.c
 *
 *  Created on: Apr 27, 2024
 *      Author: Fato
 */

#include <stdlib.h>
#include <string.h>

#include "main.h"

#include "sd_ex.h"
#include "ST7735.h"
#include "GFX_FUNCTIONS.h"
#include "gif.h"


static void depth24To16(doubleFormat *pxArr, uint16_t length);
static void playBmp(void);
static void playGif(void);


FATFS FatFs; 		//Fatfs handle
FIL fil; 			//File handle
FRESULT fres; 		//Result after operations

uint8_t buf[MAX_BUFF_RAM];			// RAM buffer


void sd_process(void)
{

	ST7735_SetRotation(0); // (wd = 160 ; x_start = 0)  and (ht = 128 ; y_start = 0)
	HAL_Delay(1000);
	fillScreen(BLACK);

	//Open the file system
	fres = f_mount(&FatFs, "", 1); // 1 = mount now
	if(fres != FR_OK)
		ferror_handler(ERROR_MOUNT);


	videoPlayer();

	// showImageBmp(FILE_NAME);

}


void videoPlayer(void)
{

	if(( FORMAT_TYPE == BMP_GIF ) || ( FORMAT_TYPE == BMP_VIDEO ) )
		playBmp();

}



// Params:
// name - file name
// x,y - start x,y on the screen
// wd,ht - width, height of the video (raw data has no header with such info)
// nl - num lines read in one operation (nl*wd*2 bytes are loaded)
// skipFr - num frames to skip
void showImageBmp(char *name)
{

	doubleFormat pBuf;
	UINT byteRead;						// Number of bytes elaborated at time


	pBuf.u8Arr = buf;					// Pointer to buf in order to convert format from uint8_t to uint16_t

	fres = f_open(&fil, name, FA_READ);
	if(fres != FR_OK)
		ferror_handler(ERROR_OPEN);

	// Point to the initial position
	f_rewind(&fil);

	while(!f_eof(&fil))
	{

		// Skip header file
		f_lseek(&fil, fil.fptr + FILE_HEADER);

		for(int i = 0 ; i < ( FRAME_DIM_HT / FRAME_DIV_FACTOR ) ; i++)
		{

			//HAL_Delay(100);

			memset(buf, 0, MAX_BUFF_RAM);
			fres = f_read(&fil, buf, FRAME_SECTION_BYTE_SIZE, &byteRead);

			if(fres != FR_OK)
				ferror_handler(ERROR_READ_FILE);

			if(byteRead != FRAME_SECTION_BYTE_SIZE)
				ferror_handler(ERROR_READ_FILE);

			if(COLOUR_DEPTH >= 24)
				depth24To16(&pBuf, FRAME_SECTION_PXL_SIZE);

			for(int j = 0 ; j < FRAME_DIV_FACTOR ;j++)
				ST7735_DrawImage(0, ( ( i * FRAME_DIV_FACTOR ) + j ), FRAME_DIM_WD, 1, ( &pBuf.u16Arr[( j * FRAME_DIM_WD )] ));

		}

		// Skip a number of frames
		if(FRAME_SKIP_FACTOR > 0)
			f_lseek(&fil, fil.fptr + ( FRAME_TOTAL_BYTE_SIZE * FRAME_SKIP_FACTOR ));

	}

	//HAL_Delay(10);

	f_close(&fil);

}


static void depth24To16(doubleFormat *pxArr, uint16_t length)
{

	uint8_t b;
	uint8_t g;
	uint8_t r;


	for(int i = 0 ; i < length ; i++)
	{

		b = pxArr->u8Arr[i*BYTE_PER_PXL];
		g = pxArr->u8Arr[i*BYTE_PER_PXL+1];
		r = pxArr->u8Arr[i*BYTE_PER_PXL+2];

		pxArr->u16Arr[i] = color565(r, g, b);
		pxArr->u16Arr[i] = ( ( ( pxArr->u16Arr[i] & 0x00ff ) << 8 ) | (( pxArr->u16Arr[i] & 0xff00 ) >> 8) );

	}

}


void playBmp(void)
{

	char name[30] = ROOT_NAME;
	int inc = 1;


	uint8_t frameNum = strlen(ROOT_NAME);
	for(int i = 1 ; i < NUM_OF_FRAMES ; )
	{

		if(i > 9)
		{

			name[frameNum] = ( i / 10 ) + 48;
			name[frameNum+1] = ( i % 10 ) + 48;

			name[frameNum+2] = '.';
			name[frameNum+3] = 'b';
			name[frameNum+4] = 'm';
			name[frameNum+5] = 'p';

		}
		else
		{

			name[frameNum] = ( i % 10 ) + 48;

			name[frameNum+1] = '.';
			name[frameNum+2] = 'b';
			name[frameNum+3] = 'm';
			name[frameNum+4] = 'p';

		}


		showImageBmp(name);


		if(FORMAT_TYPE == BMP_GIF)
		{

			if(GIF_LOOP_TYPE == BACK_AND_FORTH)
			{

				if(i >= NUM_OF_FRAMES)
					inc = -1;
				if(i == FIRST_FRAME_NUM)
					inc = 1;
			}

		}

			i += inc;

	}

}


static void playGif(void)
{

	gd_GIF	gif;
	gd_GIF *pgif;


	pgif = &gif;

	open_gif(pgif);



	close_gif(pgif);


}


void ferror_handler(uint8_t error)
{

	if(error)
		while(1);

}
