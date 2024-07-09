/*
 * lcd.h
 *
 *  Created on: Jun 1, 2024
 *      Author: andre
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "GC9A01.h"
#include "jpeg_utils.h"
#include "fatfs.h"


extern FATFS SDFatFs;  				// File system object for SD card logical drive
extern FIL file;    	      		// MJPEG File object
extern char fileName[];
extern uint8_t rtext[_MAX_SS];		// File read buffer

#define FILE_NAME						"video.avi"           //"image3.jpg"

#define LCD_WIDTH						240
#define LCD_HEIGHT						240

#define IMAGE_MAX_WIDTH					LCD_WIDTH
#define IMAGE_MAX_HEIGHT				LCD_HEIGHT
#define BYTE_PER_PIXEL					3					// 24 bit RGB888 ( 16 bit RGB565 )

#define MAX_BUFFER_SIZE					( IMAGE_MAX_WIDTH * IMAGE_MAX_HEIGHT * BYTE_PER_PIXEL )

#define MJPEG_VID_BUFFER_SIZE 			((uint32_t)(1024 *96))
#define MJPEG_AUD_BUFFER_SIZE 			((uint32_t)(1024 *0))         // No audio currently


// Process function
void lcd_process(void);

// LCD functions
void lcd_init(void);
void lcd_draw(uint16_t sx, uint16_t sy, uint16_t wd, uint16_t ht, uint8_t *data);

// Demonstration functions
void lcd_demo(void);
void sd_image_demo(void);
#ifdef JPEG_ON
void jpeg_demo(void);
#else
void mjpeg_demo(void);
#endif


#endif /* INC_LCD_H_ */
