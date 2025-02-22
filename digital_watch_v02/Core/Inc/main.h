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

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32h7xx_hal.h"

/**
 * @brief GC9A01 pin and port macros
 *
 */
#define GC9A01_CS_Pin GPIO_PIN_0
#define GC9A01_CS_GPIO_Port GPIOB
#define GC9A01_DC_Pin GPIO_PIN_1
#define GC9A01_DC_GPIO_Port GPIOB
#define GC9A01_RST_Pin GPIO_PIN_2
#define GC9A01_RST_GPIO_Port GPIOB
#define GC9A01_BL_Pin GPIO_PIN_10
#define GC9A01_BL_GPIO_Port GPIOB

/**
 * @brief FXLS8974CF pin and port macros
 *
 */
#define FXLS8974CF_INT_Pin GPIO_PIN_5
#define FXLS8974CF_INT_Port GPIOB

/**
 * @brief Buttons pin and port macros
 *
 */
#define PLUS_BTN_Pin GPIO_PIN_2
#define PLUS_BTN_GPIO_Port GPIOC
#define SET_BTN_Pin GPIO_PIN_1
#define SET_BTN_GPIO_Port GPIOC
#define MINUS_BTN_Pin GPIO_PIN_0
#define MINUS_BTN_GPIO_Port GPIOC

/**
 * @brief Converts 24 depth into 16 (565) depth
 *
 */
#define color565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

  /**
   * @brief Result enumeration
   */
  enum res
  {

    NOT_OK = 0,
    OK

  };

  /**
   * @brief Union for double format
   */
  typedef union
  {

    uint16_t *u16Arr;
    uint8_t *u8Arr;

  } doubleFormat;

  /**
   * @brief JPEG handle
   */
  extern JPEG_HandleTypeDef JPEG_Handle;

  /**
   * @brief DMA2D handle
   */
  extern DMA2D_HandleTypeDef DMA2D_Handle;

  /**
   * @brief JPEG configuration info
   */
  extern JPEG_ConfTypeDef JPEG_Info;

  /**
   * @brief SPI1 handle
   */
  extern SPI_HandleTypeDef hspi1;

  /**
   * @brief DMA handle for SPI1 TX
   */
  extern DMA_HandleTypeDef hdma_spi1_tx;

  /**
   * @brief RTC handle
   */
  extern RTC_HandleTypeDef hrtc;

  /**
   * @brief I2C1 handle
   */
  extern I2C_HandleTypeDef hi2c1;

  /**
   * @brief ADC1 handle
   */
  extern ADC_HandleTypeDef hadc1;

  /**
   * @brief Configures the system clock
   */
  void SystemClock_Config(void);

  /**
   * @brief Initializes ADC1
   */
  void MX_ADC1_Init(void);

  /**
   * @brief Handles errors
   */
  void Error_Handler(void);

  /**
   * @brief Get the acc addr object
   */
  void *get_acc_addr(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
