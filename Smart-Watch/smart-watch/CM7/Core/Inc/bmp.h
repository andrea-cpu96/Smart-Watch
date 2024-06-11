/*
 * bmp.h
 *
 *  Created on: May 7, 2024
 *      Author: Fato
 */

#ifndef INC_BMP_H_
#define INC_BMP_H_

#include <sys/types.h>
#include "fatfs.h"

// Max buffer size
#define MAX_BUFF_RAM 					( 240 * 240 * 3 )

#define color565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

#define FILE_HWORD(data) 				( (uint16_t)data[0] + ( ( (uint16_t)data[1] ) << 8 ) )
#define FILE_WORD(data)					( (uint32_t)data[0] + ( ( (uint32_t)data[1] ) << 8 ) + ( ( (uint32_t)data[1] ) << 16 ) + ( ( (uint32_t)data[1] ) << 24 ) )

typedef union
{

	uint16_t *u16Arr;
	uint8_t *u8Arr;

}doubleFormat;

typedef enum
{

	BMP_OK							=  0,
	ERROR_BMP_GENERIC,
	ERROR_BMP_MOUNT,
	ERROR_BMP_OPEN,
	ERROR_BMP_HEADER,
	ERROR_BMP_READ_FILE,
	ERROR_BMP_READ_FEW_DATA,

}error_bmp;


typedef struct BMP
{

	FIL *fp;
	char *name;
    uint16_t offset;
    uint32_t width;
	uint32_t height;
    uint16_t depth;

    uint32_t frameNum;

    const void (*draw)(uint16_t x, uint16_t y, uint16_t wd, uint16_t ht, const uint8_t *data);

}BMP;



error_bmp bmp_init(BMP *bmp, FIL *fil, char *fName, const void (*drawFunc));
error_bmp open_bmp(BMP *bmp);
error_bmp read_header_bmp(BMP *bmp);
error_bmp showImageBmp(BMP *bmp);


#endif /* INC_BMP_H_ */
