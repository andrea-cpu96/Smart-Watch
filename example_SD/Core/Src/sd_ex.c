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


FATFS FatFs; 		//Fatfs handle
FIL fil; 			//File handle
FRESULT fres; 		//Result after operations

BMP bmp;
gd_GIF gif;


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

	if(FORMAT_TYPE == TRUE_GIF)
		playGif();

}


void playBmp(void)
{

	uint8_t first = 1;

	char name[30] = ROOT_NAME;
	int inc = 1;


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

		}

		bmp.name = name;

		GPIOB->ODR |= ( 1 << 5 );

		//GPIOB->ODR ^= ( 1 << 5 );

	    f_open(bmp.fp, bmp.name, FA_READ);

	    GPIOB->ODR &= ~( 1 << 5 );

		showImageBmp(&bmp);


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


		//	GPIOB->ODR ^= ( 1 << 5 );
	}

}


static void playGif(void)
{

	int ret;


	gif_init(&gif, &fil, FILE_NAME);

	uint8_t frame[gif.width * gif.height * 3];
	//uint8_t frame_old[gif.width * gif.height * 3];

	uint8_t *color = frame;
	//uint8_t *color_old = frame_old;


	while(1)
	{

		ret = getGifFrame(&gif);

		if(ret == -1)
			while(1);

		renderGifFrame(&gif, frame);

		color = frame;
		//color_old = frame_old;

		for(int i = 0; i < gif.height; i++)
		{

			for(int j = 0; j < gif.width; j++)
			{

				//								R		  G		    B
				ST7735_DrawPixel(j, i, color565(color[0], color[1], color[2]));
				color += 3;
			//	color_old += 3;

			}

		}

		//for(int h = 0 ; h < gif.width * gif.height * 3 ; h++)
			//frame_old[h] = frame[h];

		//HAL_Delay(50);
        if(ret == 0)
        	rewindGif(&gif);

	}

}


void ferror_handler(uint8_t error)
{

	if(error)
		while(1);

}
