/**
 ******************************************************************************
 * @file         stm32h7xx_hal_msp.c
 * @brief        This file provides code for the MSP Initialization
 *               and de-Initialization codes.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* External functions --------------------------------------------------------*/

/**
 * @brief HAL_MspInit
 *
 */
void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
}

/**
 * @brief HAL_DMA2D_MspInit
 *
 * @param hdma2d
 */
void HAL_DMA2D_MspInit(DMA2D_HandleTypeDef *hdma2d)
{
  if (hdma2d->Instance == DMA2D)
  {
    /* Peripheral clock enable */
    __HAL_RCC_DMA2D_CLK_ENABLE();
  }
}

/**
 * @brief HAL_DMA2D_MspDeInit
 *
 * @param hdma2d
 */
void HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef *hdma2d)
{
  if (hdma2d->Instance == DMA2D)
  {
    /* Peripheral clock disable */
    __HAL_RCC_DMA2D_CLK_DISABLE();
  }
}

/**
 * @brief HAL_JPEG_MspInit
 *
 * @param hjpeg
 */
void HAL_JPEG_MspInit(JPEG_HandleTypeDef *hjpeg)
{
  static MDMA_HandleTypeDef hmdmaIn;
  static MDMA_HandleTypeDef hmdmaOut;

  __HAL_RCC_JPGDECEN_CLK_ENABLE();

  __HAL_RCC_MDMA_CLK_ENABLE();

  HAL_NVIC_SetPriority(JPEG_IRQn, 0x07, 0x0F);
  HAL_NVIC_EnableIRQ(JPEG_IRQn);

  hmdmaIn.Init.Priority = MDMA_PRIORITY_HIGH;
  hmdmaIn.Init.Endianness = MDMA_LITTLE_ENDIANNESS_PRESERVE;
  hmdmaIn.Init.SourceInc = MDMA_SRC_INC_BYTE;
  hmdmaIn.Init.DestinationInc = MDMA_DEST_INC_DISABLE;
  hmdmaIn.Init.SourceDataSize = MDMA_SRC_DATASIZE_BYTE;
  hmdmaIn.Init.DestDataSize = MDMA_DEST_DATASIZE_WORD;
  hmdmaIn.Init.DataAlignment = MDMA_DATAALIGN_PACKENABLE;
  hmdmaIn.Init.SourceBurst = MDMA_SOURCE_BURST_32BEATS;
  hmdmaIn.Init.DestBurst = MDMA_DEST_BURST_16BEATS;
  hmdmaIn.Init.SourceBlockAddressOffset = 0;
  hmdmaIn.Init.DestBlockAddressOffset = 0;

  hmdmaIn.Init.Request = MDMA_REQUEST_JPEG_INFIFO_TH;
  hmdmaIn.Init.TransferTriggerMode = MDMA_BUFFER_TRANSFER;
  hmdmaIn.Init.BufferTransferLength = 32;

  hmdmaIn.Instance = MDMA_Channel1;

  __HAL_LINKDMA(hjpeg, hdmain, hmdmaIn);

  HAL_MDMA_DeInit(&hmdmaIn);

  HAL_MDMA_Init(&hmdmaIn);

  hmdmaOut.Init.Priority = MDMA_PRIORITY_VERY_HIGH;
  hmdmaOut.Init.Endianness = MDMA_LITTLE_ENDIANNESS_PRESERVE;
  hmdmaOut.Init.SourceInc = MDMA_SRC_INC_DISABLE;
  hmdmaOut.Init.DestinationInc = MDMA_DEST_INC_BYTE;
  hmdmaOut.Init.SourceDataSize = MDMA_SRC_DATASIZE_WORD;
  hmdmaOut.Init.DestDataSize = MDMA_DEST_DATASIZE_BYTE;
  hmdmaOut.Init.DataAlignment = MDMA_DATAALIGN_PACKENABLE;
  hmdmaOut.Init.SourceBurst = MDMA_SOURCE_BURST_32BEATS;
  hmdmaOut.Init.DestBurst = MDMA_DEST_BURST_32BEATS;
  hmdmaOut.Init.SourceBlockAddressOffset = 0;
  hmdmaOut.Init.DestBlockAddressOffset = 0;

  hmdmaOut.Init.Request = MDMA_REQUEST_JPEG_OUTFIFO_TH;
  hmdmaOut.Init.TransferTriggerMode = MDMA_BUFFER_TRANSFER;
  hmdmaOut.Init.BufferTransferLength = 32;

  hmdmaOut.Instance = MDMA_Channel0;

  HAL_MDMA_DeInit(&hmdmaOut);

  HAL_MDMA_Init(&hmdmaOut);

  __HAL_LINKDMA(hjpeg, hdmaout, hmdmaOut);

  HAL_NVIC_SetPriority(MDMA_IRQn, 0x08, 0x0F);
  HAL_NVIC_EnableIRQ(MDMA_IRQn);
}

/**
 * @brief HAL_JPEG_MspDeInit
 *
 * @param hjpeg
 */
void HAL_JPEG_MspDeInit(JPEG_HandleTypeDef *hjpeg)
{
  HAL_NVIC_DisableIRQ(MDMA_IRQn);

  HAL_MDMA_DeInit(hjpeg->hdmain);

  HAL_MDMA_DeInit(hjpeg->hdmaout);
}

/**
 * @brief HAL_SD_MspInit
 *
 * @param hsd
 */
void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if (hsd->Instance == SDMMC1)
  {
    /* Initializes the peripherals clock*/
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDMMC;
    PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_SDMMC1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**SDMMC1 GPIO Configuration
    PB13     ------> SDMMC1_D0
    PC9     ------> SDMMC1_D1
    PC10     ------> SDMMC1_D2
    PC11     ------> SDMMC1_D3
    PC12     ------> SDMMC1_CK
    PD2     ------> SDMMC1_CMD
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  }
}

/**
 * @brief HAL_SD_MspDeInit
 *
 * @param hsd
 */
void HAL_SD_MspDeInit(SD_HandleTypeDef *hsd)
{
  if (hsd->Instance == SDMMC1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_SDMMC1_CLK_DISABLE();

    /**SDMMC1 GPIO Configuration
    PB13     ------> SDMMC1_D0
    PC9     ------> SDMMC1_D1
    PC10     ------> SDMMC1_D2
    PC11     ------> SDMMC1_D3
    PC12     ------> SDMMC1_CK
    PD2     ------> SDMMC1_CMD
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);
  }
}

/**
 * @brief HAL_SPI_MspInit
 *
 * @param hspi
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if (hspi->Instance == SPI1)
  {
    /* Initializes the peripherals clock*/
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI1;
    PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA7     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    hdma_spi1_tx.Instance = DMA1_Stream0;
    hdma_spi1_tx.Init.Request = DMA_REQUEST_SPI1_TX;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hspi, hdmatx, hdma_spi1_tx);

    /* SPI1 interrupt Init */
    HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SPI1_IRQn);
  }
}

/**
 * @brief HAL_SPI_MspDeInit
 *
 * @param hspi
 */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
  if (hspi->Instance == SPI1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA7     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5 | GPIO_PIN_7);

    /* SPI1 DMA DeInit */
    HAL_DMA_DeInit(hspi->hdmatx);

    /* SPI1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(SPI1_IRQn);
  }
}

/**
 * @brief HAL_RTC_MspInit
 *
 * @param hrtc
 */
void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if (hrtc->Instance == RTC)
  {

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_RTC_ENABLE();
  }
}

/**
 * @brief HAL_RTC_MspDeInit
 *
 * @param hrtc
 */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc)
{
  if (hrtc->Instance == RTC)
  {

    __HAL_RCC_RTC_DISABLE();
  }
}

/**
 * @brief HAL_I2C_MspInit
 *
 * @param hi2c
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if (hi2c->Instance == I2C1)
  {
    /* Initializes the peripherals clock */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
    PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C123CLKSOURCE_D2PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
    /* I2C1 interrupt Init */
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
  }
}

/**
 * @brief HAL_I2C_MspDeInit
 *
 * @param hi2c
 */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
  if (hi2c->Instance == I2C1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

    /* I2C1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
  }
}

/**
 * @brief HAL_ADC_MspInit
 *
 * @param hadc
 */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if (hadc->Instance == ADC1)
  {
    /** Initializes the peripherals clock
     */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInitStruct.PLL2.PLL2M = 4;
    PeriphClkInitStruct.PLL2.PLL2N = 16;
    PeriphClkInitStruct.PLL2.PLL2P = 8;
    PeriphClkInitStruct.PLL2.PLL2Q = 2;
    PeriphClkInitStruct.PLL2.PLL2R = 2;
    PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
    PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
    PeriphClkInitStruct.PLL2.PLL2FRACN = 0.0;
    PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_ADC12_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0     ------> ADC1_INP16
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

/**
 * @brief HAL_ADC_MspDeInit
 *
 * @param hadc
 */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_ADC12_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA0     ------> ADC1_INP16
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);
  }
}