/*
 * sd_ex.h
 *
 *  Created on: Apr 27, 2024
 *      Author: andre
 */

#ifndef INC_SD_EX_H_
#define INC_SD_EX_H_

/*************** SETTINGS *****************/

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

/*************** FIXED PARAMETERS *****************/

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

#define ERROR_0_MOUNT			0
#define ERROR_1_OPEN			1
#define ERROR_2_READ			2
#define ERROR_3_READ			3

/*****************************************/

typedef union
{

	uint16_t *u16Arr;
	uint8_t *u8Arr;

}doubleFormat;

void sd_process(void);
void showImageBmp(char *name);

#endif /* INC_SD_EX_H_ */
