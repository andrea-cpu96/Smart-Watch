/*
 * prj_conf.h
 *
 *  Created on: Nov 17, 2024
 *      Author: andre
 */

#ifndef INC_PRJ_CONF_H_
#define INC_PRJ_CONF_H_

#define OPT							1		// Substitute with NOTOPT if you want no optimizations

#define TEST						0
#define TEST_SD						0
#define TEST_DISPLAY				0
#define TEST_MJPEG					0


typedef enum test_status
{

	NA = 0,
	PASSED = 1,
	NOT_PASSED = -1,

}TEST_STATUS_t;

typedef struct
{

	TEST_STATUS_t sd_pass;
	TEST_STATUS_t display_pass;
	TEST_STATUS_t mjpeg_pass;

}test_pass_t;


#endif /* INC_PRJ_CONF_H_ */
