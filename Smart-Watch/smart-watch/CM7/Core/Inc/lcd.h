/*
 * lcd.h
 *
 *  Created on: Jun 1, 2024
 *      Author: andre
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "GC9A01.h"
#include "fatfs.h"

extern FATFS SDFatFs;  				// File system object for SD card logical drive
extern FIL file;    	      		// MJPEG File object
extern char fileName[];
extern uint8_t rtext[_MAX_SS];		// File read buffer


#define LCD_FRAME_BUFFER 0xD0000000
#define JPEG_OUTPUT_DATA_BUFFER  0xD0200000


// Process function
void lcd_process(void);

// LCD functions
void lcd_init(void);
void lcd_draw(uint16_t sx, uint16_t sy, uint16_t wd, uint16_t ht, uint8_t *data);

// Demonstration functions
void lcd_demo(void);
void sd_image_demo(void);
void jpeg_demo(void);


#endif /* INC_LCD_H_ */
