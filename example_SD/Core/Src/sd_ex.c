/*
 * sd_ex.c
 *
 *  Created on: Apr 27, 2024
 *      Author: Fato
 */

#include "main.h"

#include "sd_ex.h"
#include "ST7735.h"
#include "GFX_FUNCTIONS.h"
#include "fatfs.h"


static void showVideo(char *name, int wd, int ht, int nl, int skipFr);
static void ferror_handler(uint8_t error);


FATFS FatFs; 		//Fatfs handle
FIL fil; 			//File handle
FRESULT fres; 		//Result after operations


void sd_process(void)
{

	ST7735_SetRotation(3); // (wd = 160 ; x_start = 0)  and (ht = 128 ; y_start = 0)
	HAL_Delay(1000);
	fillScreen(BLACK);

	//Open the file system
	fres = f_mount(&FatFs, "", 1); // 1 = mount now
	if(fres != FR_OK)
		ferror_handler(ERROR_0_MOUNT);

	showVideo(FILE_NAME, FRAME_DIM_WD, FRAME_DIM_HT, FRAME_DIV_FACTOR, FRAME_SKIP_FACTOR);

}


// Params:
// name - file name
// x,y - start x,y on the screen
// wd,ht - width, height of the video (raw data has no header with such info)
// nl - num lines read in one operation (nl*wd*2 bytes are loaded)
// skipFr - num frames to skip
static void showVideo(char *name, int wd, int ht, int nl, int skipFr)
{

	uint16_t buf[MAX_BUFF_RAM];			// RAM buffer
	UINT byteRead;						// Number of bytes elaborated at time


	fres = f_open(&fil, name, FA_READ);
	if(fres != FR_OK)
		ferror_handler(ERROR_1_OPEN);

	// Point to the initial position
	f_rewind(&fil);


	while(!f_eof(&fil))
	{

		// Skip header file
		f_lseek(&fil, fil.fptr + FILE_HEADER);

		for(int i = 0 ; i < ( ht / nl ) ; i++)
		{

			fres = f_read(&fil, buf, ( wd * BYTE_PER_PXL * nl ), &byteRead);

			if(fres != FR_OK)
				ferror_handler(ERROR_2_READ);

			if(byteRead != FRAME_SECTION_SIZE)
				ferror_handler(ERROR_3_READ);

			for(int j = 0 ; j < nl ;j++)
				ST7735_DrawImage(0, ( ( i * nl ) + j ), wd, 1, ( &buf[( j * wd )] ));

		}

		// Skip a number of frames
		if(skipFr > 0)
			f_lseek(&fil, fil.fptr + ( wd * ht * BYTE_PER_PXL * skipFr ));

	}

	f_close(&fil);

}

static void ferror_handler(uint8_t error)
{

	switch(error)
	{


		case ERROR_0_MOUNT:

			//Error during mount
			while(1);

			break;

		case ERROR_1_OPEN:

			// Error during file opening
			while(1);

			break;

		case ERROR_2_READ:

			// Error during file reading
			while(1);

			break;

		case ERROR_3_READ:

			// Data read are less than expected
			while(1);

			break;


	}

}
