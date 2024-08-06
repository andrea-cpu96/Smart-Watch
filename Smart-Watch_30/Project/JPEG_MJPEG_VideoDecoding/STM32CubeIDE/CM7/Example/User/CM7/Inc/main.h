/**
  ******************************************************************************
  * @file    JPEG/JPEG_MJPEG_VideoDecoding/CM7/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module for Cortex-M7
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "stm32h747i_discovery_sdram.h"
#include "stm32h747i_discovery_sd.h"

#include "ff_gen_drv.h"
#include "sd_diskio.h"

#include "AVI_parser.h"


#define MDMA_INSTANCE MDMA_Channel0

#define LCD_FRAME_BUFFER         0xD0000000
#define JPEG_OUTPUT_DATA_BUFFER0 0xD0600000
#define JPEG_OUTPUT_DATA_BUFFER1 0xD0800000

#define VIDEO_BUFFER			 LCD_FRAME_BUFFER

// SD
#define SDIO1_D2_Pin GPIO_PIN_10
#define SDIO1_D2_GPIO_Port GPIOC
#define SDIO1_D3_Pin GPIO_PIN_11
#define SDIO1_D3_GPIO_Port GPIOC
#define SDIO1_CK_Pin GPIO_PIN_12
#define SDIO1_CK_GPIO_Port GPIOC
#define SDIO1_CMD_Pin GPIO_PIN_2
#define SDIO1_CMD_GPIO_Port GPIOD
#define SDIO1_D0_Pin GPIO_PIN_8
#define SDIO1_D0_GPIO_Port GPIOC
#define SDIO1_D1_Pin GPIO_PIN_9
#define SDIO1_D1_GPIO_Port GPIOC
// OSCILLATOR 32kHz
#define OSC32_OUT_Pin GPIO_PIN_15
#define OSC32_OUT_GPIO_Port GPIOC
#define OSC32_IN_Pin GPIO_PIN_14
#define OSC32_IN_GPIO_Port GPIOC
// OSCILLATOR
#define OSC_OUT_Pin GPIO_PIN_1
#define OSC_OUT_GPIO_Port GPIOH
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOH
// STLINK
#define STLINK_TX_Pin GPIO_PIN_10
#define STLINK_TX_GPIO_Port GPIOA
#define STLINK_RX_Pin GPIO_PIN_9
#define STLINK_RX_GPIO_Port GPIOA
// SPI
#define ARD_D13_Pin GPIO_PIN_0
#define ARD_D13_GPIO_Port GPIOK
#define ARD_D12_Pin GPIO_PIN_11
#define ARD_D12_GPIO_Port GPIOJ
#define ARD_D11_Pin GPIO_PIN_10
#define ARD_D11_GPIO_Port GPIOJ
// DISPLAY LCD
#define GC9A01_CS_Pin GPIO_PIN_1
#define GC9A01_CS_GPIO_Port GPIOK
#define GC9A01_BL_Pin GPIO_PIN_0
#define GC9A01_BL_GPIO_Port GPIOJ
#define GC9A01_DC_Pin GPIO_PIN_6
#define GC9A01_DC_GPIO_Port GPIOJ
#define GC9A01_RST_Pin GPIO_PIN_5
#define GC9A01_RST_GPIO_Port GPIOJ
// WATCH BUTTONS
#define BUTTON_MINUS_Pin GPIO_PIN_0
#define BUTTON_MINUS_GPIO_Port GPIOJ
#define BUTTON_PLUS_Pin GPIO_PIN_7
#define BUTTON_PLUS_GPIO_Port GPIOJ
#define BUTTON_SETTING_Pin GPIO_PIN_3
#define BUTTON_SETTING_GPIO_Port GPIOJ



#define color565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))


typedef union
{

	uint16_t *u16Arr;
	uint8_t *u8Arr;

}doubleFormat;


extern JPEG_HandleTypeDef    			JPEG_Handle;
extern DMA2D_HandleTypeDef    			DMA2D_Handle;
extern JPEG_ConfTypeDef  		     	JPEG_Info;

extern uint32_t LCD_X_Size;
extern uint32_t LCD_Y_Size;

extern FATFS SDFatFs;  					// File system object for SD card logical drive
extern char SDPath[4]; 					// SD card logical drive path

extern FIL MJPEG_File;          		// MJPEG File object

extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi5;


void SystemClock_Config(void);
void MPU_Config(void);
void CPU_CACHE_Enable(void);
void MX_RTC_Init(void);
void MX_SPI5_Init(void);
void MX_GPIO_Init(uint8_t it_en);
void Error_Handler(void);

#endif /* __MAIN_H */

