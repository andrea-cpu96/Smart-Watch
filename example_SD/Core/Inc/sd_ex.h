/*
 * sd_ex.h
 *
 *  Created on: Apr 27, 2024
 *      Author: andre
 */

#ifndef INC_SD_EX_H_
#define INC_SD_EX_H_


#define FILE_NAME						"sonic.gif"



/*************** SETTINGS VIDEOPLAYER *****************/

#define TRUE_GIF 						0
#define BMP_GIF							1
#define BMP_VIDEO						2

#define FORMAT_TYPE						TRUE_GIF

#define RELOAD							0
#define BACK_AND_FORTH					1

#define GIF_LOOP_TYPE					BACK_AND_FORTH

#define NUM_OF_FRAMES					4

#define ROOT_NAME						"sample"

#define FIRST_FRAME_NUM					1

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

void sd_process(void);

void videoPlayer(void);
void ferror_handler(uint8_t error);

#endif /* INC_SD_EX_H_ */
