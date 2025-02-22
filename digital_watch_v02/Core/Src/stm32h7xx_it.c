/**
 ******************************************************************************
 * @file    stm32h7xx_it.c
 * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/

#include "stm32h7xx_it.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/

/**
 * @brief NMI_Handler
 *
 */
void NMI_Handler(void)
{
  while (1)
  {
  }
}

/**
 * @brief HardFault_Handler
 *
 */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
 * @brief MemManage_Handler
 *
 */
void MemManage_Handler(void)
{
  while (1)
  {
  }
}

/**
 * @brief BusFault_Handler
 *
 */
void BusFault_Handler(void)
{
  while (1)
  {
  }
}

/**
 * @brief UsageFault_Handler
 *
 */
void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

/**
 * @brief SVC_Handler
 *
 */
void SVC_Handler(void)
{
}

/**
 * @brief DebugMon_Handler
 *
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief PendSV_Handler
 *
 */
void PendSV_Handler(void)
{
}

/**
 * @brief SysTick_Handler
 *
 */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/**
 * @brief JPEG_IRQHandler
 *
 */
void JPEG_IRQHandler(void)
{
  HAL_JPEG_IRQHandler(&JPEG_Handle);
}

/**
 * @brief MDMA_IRQHandler
 *
 */
void MDMA_IRQHandler()
{
  HAL_MDMA_IRQHandler(JPEG_Handle.hdmain);
  HAL_MDMA_IRQHandler(JPEG_Handle.hdmaout);
}

/**
 * @brief DMA1_Stream0_IRQHandler
 *
 */
void DMA1_Stream0_IRQHandler()
{
  HAL_DMA_IRQHandler(&hdma_spi1_tx);
}

/**
 * @brief SPI1_IRQHandler
 *
 */
void SPI1_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&hspi1);
}

/**
 * @brief I2C1_EV_IRQHandler
 *
 */
void I2C1_EV_IRQHandler(void)
{
  HAL_I2C_EV_IRQHandler(&hi2c1);
}

/**
 * @brief EXTI0_IRQHandler
 *
 */
void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(MINUS_BTN_Pin);
}

/**
 * @brief EXTI1_IRQHandler
 *
 */
void EXTI1_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(SET_BTN_Pin);
}

/**
 * @brief EXTI2_IRQHandler
 *
 */
void EXTI2_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(PLUS_BTN_Pin);
}

/**
 * @brief EXTI9_5_IRQHandler
 *
 */
void EXTI9_5_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(FXLS8974CF_INT_Pin);
}
