/*
 * smart_watch.h
 *
 *  Created on: Jul 22, 2024
 *      Author: Fato
 */

#ifndef EXAMPLE_USER_CM7_SMART_WATCH_H_
#define EXAMPLE_USER_CM7_SMART_WATCH_H_


#define MJPEG_VID_BUFFER_SIZE 		((uint32_t)(1024 *50))
#define MJPEG_AUD_BUFFER_SIZE 		((uint32_t)(1024 *0))

/* DISPLAY SETTINGS */

#define LCD_SIDE_SIZE				240
#define DISPLAY_STANDBY_TIMER		59

#define LCD_X_SIZE					LCD_SIDE_SIZE
#define LCD_Y_SIZE					LCD_SIDE_SIZE

/* FRAME RATE SETTINGS */

#define BLOCK_PX_PER_SIDE			12
#define SPARE_DIV_FACT				4   // One pixel every SPARE_DIV_FACT is compared
#define COMPARED_FRAC				4   // Fraction of pixels that subtracted to COMPARED_PX is MAX_EQU_NUM
#define FULL_UPDATE_PERIOD			18  // Period after that a full update is implemented

#define BORDER_START				( 2 * BLOCK_PX_PER_SIDE )
#define BORDER_END					( 2 * BLOCK_PX_PER_SIDE )
#define COMPARED_PX					( ( BLOCK_PX_PER_SIDE * BLOCK_PX_PER_SIDE ) / SPARE_DIV_FACT )
#define MAX_EQU_NUM					( COMPARED_PX - ( COMPARED_PX / COMPARED_FRAC ) )
#define PX_PER_BLOCK_X				BLOCK_PX_PER_SIDE
#define PX_PER_BLOCK_Y				BLOCK_PX_PER_SIDE
#define PX_IN_A_RAW					LCD_SIDE_SIZE
#define BLOCK_SIZE 					( PX_PER_BLOCK_X * PX_PER_BLOCK_Y )
#define BLOCKS_PER_CHUNK			( PX_IN_A_RAW / PX_PER_BLOCK_X )
#define CHUNKS_NUM					( ( PX_IN_A_RAW * PX_IN_A_RAW ) / ( BLOCKS_PER_CHUNK * BLOCK_SIZE ) )


enum mode
{

	SETTING_MODE = 0,
	NORMAL_MODE

};

enum display_status
{

	DISPLAY_OFF	= 0,
	DISPLAY_ON

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

	RTC_TimeTypeDef time;

	uint16_t file_idx;
	uint8_t isfirstFrame;
	uint8_t FrameType;
	uint16_t width;
	uint16_t height;
	uint16_t xPos;
	uint16_t yPos;
	uint32_t frameCount;

	int frameToSkip;							// Defines for each cycle how many frames time skip
	float frame_time;	  						// Holds the time duration of the single frame
	uint32_t actual_time; 						// Takes trace of the actual time
	uint32_t tick_offset;

	uint32_t jpegOutDataAdreess; 				// Buffer for the decoded data

	enum mode video_mode;
	enum settings set;

	uint32_t display_ts;

	uint8_t display_status;

}video_t;


extern __IO uint32_t Jpeg_HWDecodingEnd;


void smart_watch_init(void);
void smart_watch_process(void);
int lcd_draw(uint16_t sx, uint16_t sy, uint16_t wd, uint16_t ht, uint8_t *data, uint8_t swap);
int lcd_draw_opt(uint16_t sx, uint16_t sy, uint16_t wd, uint16_t ht, uint8_t *data);

int smart_watch_test_sd(void);
int smart_watch_test_display(void);
int smart_watch_test_mjpeg(void);


#endif /* EXAMPLE_USER_CM7_SMART_WATCH_H_ */
