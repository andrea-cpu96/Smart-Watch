/*
 * sd_ex.h
 *
 *  Created on: Apr 27, 2024
 *      Author: andre
 */

#ifndef INC_SD_EX_H_
#define INC_SD_EX_H_


#include "fatfs.h"


/*************** SETTINGS BMP *****************/

// Frame sizes
#define FRAME_DIM_HT					50
#define FRAME_DIM_WD					50

// Frame division factor (in order to save RAM during run time I chose
// to subdivide each frame in multiple sub-frames)
// It must be a multiple of 2
#define FRAME_DIV_FACTOR				50

// Number of frames to be skipped ( in order to save processing time )
#define FRAME_SKIP_FACTOR				0

// File name
#define FILE_NAME						"sample11.bmp"

// File header number of bytes (to be skipped)
#define FILE_HEADER						54					// .bmp = 54B

// Number of bit of depth
#define COLOUR_DEPTH 					32

/*****************************************/


/*************** SETTINGS GIF *****************/

#define GIF_FILE_NAME					"sample11.gif"

/*****************************************/


/*************** SETTINGS VIDEOPLAYER *****************/

#define TRUE_GIF 						0
#define BMP_GIF							1
#define BMP_VIDEO						2

#define FORMAT_TYPE						BMP_GIF

#define RELOAD							0
#define BACK_AND_FORTH					1

#define GIF_LOOP_TYPE					BACK_AND_FORTH

#define NUM_OF_FRAMES					4

#define ROOT_NAME						"sample"

#define FIRST_FRAME_NUM					1

/*****************************************/


/*************** FIXED PARAMETERS BMP *****************/

// Display sizes (considering the rotation of the display)
#define WIDTH							ST7735_HEIGHT
#define HEIGHT							ST7735_WIDTH

// Number of bytes per pixel
#define BYTE_PER_PXL					( COLOUR_DEPTH / 8 )

// Frame sizes
#define FRAME_TOTAL_BYTE_SIZE			( FRAME_DIM_WD * FRAME_DIM_HT * BYTE_PER_PXL)
#define FRAM_TOTAL_BYTE_16_SIZE			( FRAME_DIM_WD * FRAME_DIM_HT * 2 )
#define FRAME_SECTION_BYTE_SIZE			( FRAME_DIM_WD * FRAME_DIV_FACTOR * BYTE_PER_PXL )
#define FRAME_SECTION_BYTE_16_SIZE 		( FRAME_DIM_WD * FRAME_DIV_FACTOR * 2 )
#define FRAME_SECTION_PXL_SIZE			( FRAME_DIM_WD * FRAME_DIV_FACTOR )

// Max buffer size
#define MAX_BUFF_RAM 					( FRAME_SECTION_BYTE_SIZE + 200 )

/*****************************************/


/******************* ERRORS	******************/


enum
{

	ERROR_GENERIC				=  1,
	ERROR_MOUNT,
	ERROR_OPEN,
	ERROR_READ_FILE,
	ERROR_READ_FEW_DATA,

	ERROR_GIF_HEADER,
	ERROR_GIF_VERSION,
	ERROR_GIF_GCT,
	ERROR_GIF_TABLE,

};


/*****************************************/

typedef union
{

	uint16_t *u16Arr;
	uint8_t *u8Arr;

}doubleFormat;


extern FATFS FatFs; 						//Fatfs handle
extern FIL fil; 							//File handle
extern FRESULT fres; 						//Result after operations
extern uint8_t buf[MAX_BUFF_RAM];			// RAM buffer


void sd_process(void);

void videoPlayer(void);
void showImageBmp(char *name);
void ferror_handler(uint8_t error);

#endif /* INC_SD_EX_H_ */
