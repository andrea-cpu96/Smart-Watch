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

#define TIMER_MAX_COUNT				9999.0
#define TIMER_TIME					10.0


extern uint16_t frame_time;
extern uint16_t frameToSkip;
extern AVI_CONTEXT AVI_Handel;

extern __IO uint32_t Jpeg_HWDecodingEnd;


void smart_watch_process(void);


#endif /* EXAMPLE_USER_CM7_SMART_WATCH_H_ */
