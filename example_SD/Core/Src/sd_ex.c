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
#include "bmp.h"
#include "gif.h"


static void playBmp(void);
static void playGif(void);

static error_bmp ramPipeline(BMP *bmp);


FATFS FatFs; 		//Fatfs handle
FIL fil; 			//File handle
FRESULT fres; 		//Result after operations

BMP bmp;


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

	//bmp_init(&bmp, &fil, FILE_NAME, ST7735_DrawImage);
	//showImageBmp(&bmp);

}


void videoPlayer(void)
{

	if(( FORMAT_TYPE == BMP_GIF ) || ( FORMAT_TYPE == BMP_VIDEO ) )
		playBmp();

}


void playBmp(void)
{

	uint8_t first = 1;
	uint8_t fillPipe = 0;

	uint8_t bufRam1[MAX_BUFF_RAM];
	uint8_t bufRam2[MAX_BUFF_RAM];

	char name[30] = ROOT_NAME;
	int inc = 1;

	bmp.dataBuf[0] = bufRam1;
	bmp.dataBuf[1] = bufRam2;

	uint8_t frameNum = strlen(ROOT_NAME);
	for(int i = 1 ; i <= NUM_OF_FRAMES ; )
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

		if(first != 0)
		{

			first = 0;

			bmp_init(&bmp, &fil, name, ST7735_DrawImage);

			bmp.pipeFlag = 1;

		}
		else
		{

			bmp.name = name;

			f_open(bmp.fp, bmp.name, FA_READ);

		}

		ramPipeline(&bmp);

		if(fillPipe >= 1)
			showImageBmp(&bmp);
		else
			fillPipe++;

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



static error_bmp ramPipeline(BMP *bmp)
{

	FRESULT fres;

	UINT byteRead;

	uint32_t sectionSizeByte;
	uint32_t linesPerSec;


	linesPerSec = linesPerSection(bmp);
	sectionSizeByte = ( ( linesPerSec * bmp->width ) * ( bmp->depth / 8 ) );

	// Enter new data in pipe

	memset(bmp->dataBuf[bmp->pipeIndex], 0, MAX_BUFF_RAM);
	fres = f_read(bmp->fp, bmp->dataBuf[bmp->pipeIndex], sectionSizeByte, &byteRead);

	if(fres != FR_OK)
		return ERROR_BMP_READ_FILE;

	// Elaborate data ready

	bmp->pipeIndex = ( ( bmp->pipeIndex + 1 ) % 2 );

	return BMP_OK;

}
