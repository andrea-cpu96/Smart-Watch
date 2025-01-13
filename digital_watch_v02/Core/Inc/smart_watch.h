/*
 * smart_watch.h
 *
 *  Created on: Jul 22, 2024
 *      Author: Fato
 */

#ifndef EXAMPLE_USER_CM7_SMART_WATCH_H_
#define EXAMPLE_USER_CM7_SMART_WATCH_H_

#include "GC9A01.h"
#include "FXLS8974C.h"

/* DEBUG SETTINGS */

//#define DEBUG_TIME

/* OPTIMIZZATION SETTINGS */

//#define OPT
//#define OPT2
//#define OPT3

/* MJPEG SETTINGS */

#define MJPEG_VID_BUFFER_SIZE 		((uint32_t)(1024 *50))
#define MJPEG_AUD_BUFFER_SIZE 		((uint32_t)(1024 *0))

/* DISPLAY SETTINGS */

#define LCD_SIDE_SIZE				240
#define DISPLAY_STANDBY_TIMER		59
#define LCD_X_SIZE					LCD_SIDE_SIZE
#define LCD_Y_SIZE					LCD_SIDE_SIZE

/* BLOCKS SETTINGS */

#ifdef OPT3
#define BLOCK_SIDE_SIZE				12
#define BLOCKS_PER_RAW				( LCD_SIDE_SIZE / BLOCK_SIDE_SIZE )
#define BLOCK_TOT_PIXELS			( BLOCK_SIDE_SIZE * BLOCK_SIDE_SIZE )
#define BLOCK_NUM					( ( LCD_SIDE_SIZE * LCD_SIDE_SIZE ) / BLOCK_TOT_PIXELS )
#endif

/* CIRCULAR MASK */

#define R							( ( LCD_SIDE_SIZE / 2 ) - 1 ) // Ray of the round display
#define SQUARE(x)					( (x) * (x) )
#define PIX_TO_CIRC_COORD(p)		( ( p >= R) ? ( p - R ) : ( R - p ) ) // Put the pixel position in a circle reference (where the center is the 0 position)
#define CIRCLE_MASK(px, py)			( ( SQUARE(PIX_TO_CIRC_COORD(px)) + SQUARE(PIX_TO_CIRC_COORD(py)) ) >= SQUARE(R) )

/* OTHERS DEFINITIONS */

#define DIFF_THRESHOLD				5
#define PIXELS_DIFF(pix1, pix2)		( ( pix1 > pix2 ) ? ( pix1 - pix2 ) : ( pix2 - pix1 ) )
#define PIXELS_COMP(pix1, pix2)		( PIXELS_DIFF(pix1, pix2) < DIFF_THRESHOLD )

#define RESET_ITER_NUM				30


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

enum button_status
{

	BTN_NONE = 0,
	BTN_PLUS,
	BTN_SET,
	BTN_MINUS

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

typedef struct
{

	uint8_t first_day;
	uint8_t first_month;

	uint8_t current_day;
	uint8_t current_month;

	uint8_t minutes_offs;

}time_t;

#ifdef OPT3
typedef struct
{

	struct GC9A01_frame display_frame;
	uint8_t *buffer_frame1[BLOCK_SIDE_SIZE];
	uint8_t *buffer_frame2[BLOCK_SIDE_SIZE];

}block_t;
#endif


extern __IO uint32_t Jpeg_HWDecodingEnd;
extern uint8_t *outputData;

int smart_watch_init(void);
int smart_watch_process(void);
int lcd_draw(uint8_t *data);
#ifdef OPT
int lcd_draw_opt(uint8_t *data);
#endif
#ifdef OPT2
void lcd_draw_opt2(doubleFormat *data);
#endif
#ifdef OPT3
void lcd_draw_opt3(doubleFormat *data);
#endif

int smart_watch_test_sd(void);
int smart_watch_test_display(void);
int smart_watch_test_mjpeg(void);
int smart_watch_test_accelerometer(fxls8974_i2c_sensorhandle_t *pSensorHandle);


#endif /* EXAMPLE_USER_CM7_SMART_WATCH_H_ */
