/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ff.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern JPEG_HandleTypeDef    			JPEG_Handle;
extern DMA2D_HandleTypeDef    			DMA2D_Handle;
extern JPEG_ConfTypeDef  		     	JPEG_Info;
extern uint32_t LCD_X_Size;
extern uint32_t LCD_Y_Size;
extern SPI_HandleTypeDef hspi1;
extern RTC_HandleTypeDef hrtc;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define GC9A01_CS_Pin GPIO_PIN_0
#define GC9A01_CS_GPIO_Port GPIOB
#define GC9A01_DC_Pin GPIO_PIN_1
#define GC9A01_DC_GPIO_Port GPIOB
#define GC9A01_RST_Pin GPIO_PIN_2
#define GC9A01_RST_GPIO_Port GPIOB
#define GC9A01_BL_Pin GPIO_PIN_10
#define GC9A01_BL_GPIO_Port GPIOB

#define PLUS_BTN_Pin GPIO_PIN_2
#define PLUS_BTN_GPIO_Port GPIOC
#define SET_BTN_Pin GPIO_PIN_1
#define SET_BTN_GPIO_Port GPIOC
#define MINUS_BTN_Pin GPIO_PIN_0
#define MINUS_BTN_GPIO_Port GPIOC
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN EFP */
typedef union
{

	uint16_t *u16Arr;
	uint8_t *u8Arr;

}doubleFormat;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
#define color565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
