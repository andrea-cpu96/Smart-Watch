/*
 * sd.c
 *
 *  Created on: Jun 6, 2024
 *      Author: Fato
 */

#include "main.h"

#include "sd.h"


FATFS SDFatFs;  				// File system object for SD card logical drive
FIL file;          				// MJPEG File object
char fileName[] = "image.bmp";
uint8_t rtext[_MAX_SS];			// File read buffer


static void sd_error_handler(void);


void sd_init(void)
{

    if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) != FR_OK)
    	sd_error_handler();

    if(f_mkfs((TCHAR const*)SDPath, FM_ANY, 0, rtext, sizeof(rtext)) != FR_OK)
		sd_error_handler();

}


void sd_open(FIL *file, char *fileName, char rw)
{

	if(f_open(file, fileName, FA_READ) != FR_OK)
		sd_error_handler();

}


/****************************************** PRIVATE FUNCTIONS */


static void sd_error_handler(void)
{

	while(1);

}
