/*
 * smart_watch.h
 *
 *  Created on: Jul 22, 2024
 *      Author: Fato
 */

#ifndef EXAMPLE_USER_CM7_SMART_WATCH_H_
#define EXAMPLE_USER_CM7_SMART_WATCH_H_


#define MJPEG_VID_BUFFER_SIZE 		((uint32_t)(1024 *96))
#define MJPEG_AUD_BUFFER_SIZE 		((uint32_t)(1024 *0))

#define LCD_X_SIZE					240
#define LCD_Y_SIZE					240

#define TIME_ELAPSED(current, ts)	( ( current - ts ) > 0 ? ( current - ts ) : ( ts - current ) )
#define DISPLAY_STANDBY_TIMER		59

#define DISPLAY_ON					1
#define DISPLAY_OFF					0

enum mode
{

	SETTING_MODE = 0,
	NORMAL_MODE

};


enum settings
{

	SET_IDLE = 0,
	SET_HOURS,
	SET_MINUTES,
	SET_START

};


typedef struct
{

	//RTC_TimeTypeDef time;

	uint16_t file_idx;
	uint8_t isfirstFrame;
	uint8_t FrameType;
	uint16_t width;
	uint16_t height;
	uint16_t xPos;
	uint16_t yPos;
	uint32_t frameCount;

	int frameToSkip;											// Defines for each cycle how many frames time skip
	uint16_t frame_time;	  									// Holds the time duration of the single frame
	uint32_t actual_time; 										// Takes trace of the actual time
	uint32_t tick_offset;

	uint32_t jpegOutDataAdreess; 								// Buffer for the decoded data

	enum mode video_mode;
	enum settings set;

	uint32_t display_ts;

	uint8_t display_status;

}video_t;


extern __IO uint32_t Jpeg_HWDecodingEnd;


void smart_watch_init(void);
void smart_watch_process(void);
int lcd_draw(uint16_t sx, uint16_t sy, uint16_t wd, uint16_t ht, uint8_t *data);

int smart_watch_test_sd(void);
int smart_watch_test_display(void);
void smart_watch_test_mjpeg(void);


#endif /* EXAMPLE_USER_CM7_SMART_WATCH_H_ */
