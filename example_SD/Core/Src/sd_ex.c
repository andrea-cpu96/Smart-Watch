/*
 * sd_ex.c
 *
 *  Created on: Apr 27, 2024
 *      Author: andre
 */

#include "main.h"

#include "sd_ex.h"
#include "ST7735.h"
#include "GFX_FUNCTIONS.h"
#include "fatfs.h"


void sd_process(void)
{

  ST7735_SetRotation(3);
  //ST7735_WriteString(0, 0, "UnNatural presents", Font_7x10, WHITE,BLACK);
  HAL_Delay(1000);
  fillScreen(BLACK);

  //some variables for FatFs
  FATFS FatFs; 	//Fatfs handle
  FIL fil; 		//File handle
  FRESULT fres; //Result after operations

  //Open the file system
  fres = f_mount(&FatFs, "", 1); //1=mount now
  if(fres != FR_OK)
  {

	  //myprintf("f_mount error (%i)\r\n", fres);
	  while(1);

  }

  //Let's get some statistics from the SD card
  DWORD free_clusters, free_sectors, total_sectors;

  FATFS* getFreeFs;

  fres = f_getfree("", &free_clusters, &getFreeFs);
  if(fres != FR_OK)
  {

	  //myprintf("f_getfree error (%i)\r\n", fres);
	  while(1);

  }

  //Formula comes from ChaN's documentation
  total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
  free_sectors = free_clusters * getFreeFs->csize;

  //myprintf("SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);

  //Now let's try to open file "test.txt"
  fres = f_open(&fil, "ex.txt", FA_READ);
  if(fres != FR_OK)
  {

	  //myprintf("f_open error (%i)\r\n");
	  while(1);

  }

  //myprintf("I was able to open 'test.txt' for reading!\r\n");

  //Read 30 bytes from "test.txt" on the SD card
  BYTE readBuf[30];

  //We can either use f_read OR f_gets to get data out of files
  //f_gets is a wrapper on f_read that does some string formatting for us
  TCHAR* rres = f_gets((TCHAR*)readBuf, 30, &fil);
  if(rres != 0)
  {

	  //myprintf("Read string from 'test.txt' contents: %s\r\n", readBuf);
	  ST7735_SetRotation(3);
	  ST7735_WriteString(0, 0, rres, Font_7x10, WHITE,BLACK);
	  HAL_Delay(1000);
	  //fillScreen(BLACK);


  }
  else
  {

	  //myprintf("f_gets error (%i)\r\n", fres);

  }

  //Be a tidy kiwi - don't forget to close your file!
  f_close(&fil);

/*

  //Now let's try and write a file "write.txt"
  fres = f_open(&fil, "write.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
  if(fres == FR_OK)
  {

	  //myprintf("I was able to open 'write.txt' for writing\r\n");

  }
  else
  {

	  //myprintf("f_open error (%i)\r\n", fres);

  }

  //Copy in a string
  strncpy((char*)readBuf, "a new file is made!", 19);
  UINT bytesWrote;
  fres = f_write(&fil, readBuf, 19, &bytesWrote);
  if(fres == FR_OK)
  {

	  //myprintf("Wrote %i bytes to 'write.txt'!\r\n", bytesWrote);

  }
  else
  {

	  myprintf("f_write error (%i)\r\n");

  }

  //Be a tidy kiwi - don't forget to close your file!
  f_close(&fil);

  //We're done, so de-mount the drive
  f_mount(NULL, "", 0);

*/

}
