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


static showVideo(char *name, int x, int y, int wd, int ht, int nl, int skipFr);


//some variables for FatFs
FATFS FatFs; 	//Fatfs handle
FIL fil; 		//File handle
FRESULT fres; //Result after operations


void sd_process(void)
{

  ST7735_SetRotation(3);
  //ST7735_WriteString(0, 0, "UnNatural presents", Font_7x10, WHITE,BLACK);
  HAL_Delay(1000);
  fillScreen(BLACK);

  //Open the file system
  fres = f_mount(&FatFs, "", 1); //1=mount now
  if(fres != FR_OK)
  {

	  while(1);

  }

  showVideo(char *name, int x, int y, int wd, int ht, int nl, int skipFr);

  /////////////////////

  /*

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


}
*/

// Params:
// name - file name
// x,y - start x,y on the screen
// wd,ht - width, height of the video (raw data has no header with such info)
// nl - num lines read in one operation (nl*wd*2 bytes are loaded)
// skipFr - num frames to skip
void showVideo(char *name, int x, int y, int wd, int ht, int nl, int skipFr)
{

	uint16_t buf[200*NLINES];


	fres = f_open(&fil, name, FA_READ);
	if(fres != FR_OK)
	{

		while(1);

	}

	// Start from the intial
	f_rewind(&fil);

  //handleButton();

  while(!f_eof(&fil)) {

    for(int i = 0 ; i < ( ht / nl ) ; i++)
    {

      fres = f_read(&fil, buf, ( wd * 2 * nl ), NULL);
      for(int j = 0 ; j < nl ;j++)
    	  ST7735_DrawImage(0, ( ( i * nl ) + j ), lcd.width(), 1, ( buf + 20 + ( j * wd ) ));

    }

  }

  f_close(&fil);

}


