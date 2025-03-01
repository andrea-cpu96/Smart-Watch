/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

#include <stdio.h>
#include <string.h>

#include "main.h"

#include "fatfs.h"
#include "prj_conf.h"
#include "GC9A01.h"
#include "FXLS8974C.h"
#include "smart_watch.h"

/**
 * @defgroup Global_Variables Global Variables
 * @brief This section defines the global variables used in the program.
 * @{
 */

SD_HandleTypeDef hsd1;
SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;
JPEG_HandleTypeDef JPEG_Handle;
DMA2D_HandleTypeDef DMA2D_Handle;
JPEG_ConfTypeDef JPEG_Info;
RTC_HandleTypeDef hrtc;
I2C_HandleTypeDef hi2c1;
ADC_HandleTypeDef hadc1;
fxls8974_i2c_sensorhandle_t acc_Handle;

/** @} */ // end of Global_Variables group

/**
 * @defgroup Private_Functions_Proto Private Functions Proto
 * @brief This section defines the private functions prototypes.
 * @{
 */

/**
  * @brief  Initialize GPIO
  * @retval None
  */
static void MX_GPIO_Init(void);

/**
  * @brief  Initialize DMA2D
  * @retval None
  */
static void MX_DMA2D_Init(void);

/**
  * @brief  Initialize JPEG
  * @retval None
  */
static void MX_JPEG_Init(void);

/**
  * @brief  Initialize SDMMC1 SD
  * @retval None
  */
static void MX_SDMMC1_SD_Init(void);

/**
  * @brief  Initialize DMA
  * @retval None
  */
static void MX_DMA_Init(void);

/**
  * @brief  Initialize SPI1
  * @retval None
  */
static void MX_SPI1_Init(void);

/**
  * @brief  Initialize RTC
  * @retval None
  */
static void MX_RTC_Init(void);

/**
  * @brief  Initialize I2C1
  * @retval None
  */
static void MX_I2C1_Init(void);

/**
  * @brief  Test process
  * @retval int
  */
static int test_process(void);

/**
  * @brief  Print the log
  * @param  log_file: pointer to the log file
  * @param  status: status of the test
  * @param  test_name: name of the test
  * @retval int
  */
static int print_log(FIL *log_file, TEST_STATUS_t status, char *test_name);

/** @} */ // end of Private_Functions_Proto group

/**
 * @defgroup Global_Functions_Def Global Functions Def
 * @brief This section defines the global functions used in the program.
 * @{
 */

/**
 * @brief  Main program entry point
 * @retval int
 */
int main(void)
{
  /** Enable I-Cache */
  SCB_EnableICache();

  /** Initialize the HAL Library */
  HAL_Init();

  SystemClock_Config();

  HAL_Delay(500);

  /** Initialize all microcontroller peripherals */

  MX_GPIO_Init();
  MX_DMA2D_Init();
  MX_SDMMC1_SD_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_RTC_Init();
  MX_I2C1_Init();
#ifdef ENABLE_BATTERY_MON
  MX_ADC1_Init();
#endif
  JPEG_Handle.Instance = JPEG;
  MX_JPEG_Init();

  HAL_Delay(500);

  /* outputData init to a default value (0xff->white) */
  for (int i = 0; i < (LCD_X_SIZE * LCD_Y_SIZE * 2); i++)
    outputData[i] = 0xff;

  /** Initialize all the external peripherals */

  /* Display init */
  GC9A01_Init();
  lcd_draw(outputData); // White screen after the init

  HAL_Delay(500);

  /* Turn on the backlight */
  HAL_GPIO_WritePin(GC9A01_BL_GPIO_Port, GC9A01_BL_Pin, RESET);

  /* Accelerometer init */
  FXLS8974_I2C_Init(&acc_Handle, &hi2c1, HAL_I2C_Master_Seq_Transmit_IT, HAL_I2C_Master_Seq_Receive_IT, FXLS8974_DEVICE_ADDRESS_SA0_0);

  /** Digital watch initialization */

  if (smart_watch_init() != OK)
    Error_Handler();

  HAL_Delay(500);

  if (TEST == 0)
  {

    /* Test routine */

    if (smart_watch_process() != OK)
      Error_Handler();
  }
  else
  {

    /* Main routine */

    if (test_process() < 0)
      Error_Handler();
  }

  /** Infinite loop */

  while (1)
  {

    /* Should never enter here */
  }
}

/**
 * @brief  System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Enable all clocks */
  RCC->CKGAENR = 0xFFFFFFFF;

  /* Configure the power supply */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /* Configure the voltage scaling */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /* Wait until the voltage scaling is ready */
  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
  {
  }

  /* Initialize the RCC Oscillators according to the specified parameters */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSEState = RCC_HSI_ON;
  RCC_OscInitStruct.HSEState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = 64;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 22;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 6;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief  Initialize RTC
 * @retval None
 */
void MX_RTC_Init(void)
{

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  sTime.Hours = 0;
  sTime.Minutes = 0;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }

  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 1;
  sDate.Year = 0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief  Initialize ADC1
 * @retval None
 */
void MX_ADC1_Init(void)
{

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  sConfig.Channel = ADC_CHANNEL_16;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief Get the acc addr object
 * @retval void* 
 */
void *get_acc_addr(void)
{

  return &acc_Handle;
}

/**
 * @brief  Error Handler
 * @retval None
 */
void Error_Handler(void)
{

#ifdef DEBUG_MODE
  __disable_irq();
  while (1)
  {
  }
#else

  HAL_NVIC_SystemReset();

#endif
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */

/** @} */ // end of Global_Functions_Def group

/**
 * @defgroup Private_Functions_Def Private Functions Def
 * @brief This section defines the private functions used in the program.
 * @{
 */

/**
 * @brief  Initialize DMA2D
 * @retval None
 */
static void MX_DMA2D_Init(void)
{

  DMA2D_Handle.Instance = DMA2D;
  DMA2D_Handle.Init.Mode = DMA2D_M2M;
  DMA2D_Handle.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
  DMA2D_Handle.Init.OutputOffset = 0;
  DMA2D_Handle.LayerCfg[1].InputOffset = 0;
  DMA2D_Handle.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  DMA2D_Handle.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  DMA2D_Handle.LayerCfg[1].InputAlpha = 0;
  DMA2D_Handle.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA;
  DMA2D_Handle.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR;
  DMA2D_Handle.LayerCfg[1].ChromaSubSampling = DMA2D_NO_CSS;
  if (HAL_DMA2D_Init(&DMA2D_Handle) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&DMA2D_Handle, 1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief  Initialize JPEG
 * @retval None
 */
static void MX_JPEG_Init(void)
{

  JPEG_Handle.Instance = JPEG;
  if (HAL_JPEG_Init(&JPEG_Handle) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief  Initialize SDMMC1 SD
 * @retval None
 */
static void MX_SDMMC1_SD_Init(void)
{

  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_ENABLE;
  hsd1.Init.ClockDiv = 0;
}

/**
 * @brief  Initialize DMA
 * @retval None
 */
static void MX_DMA_Init(void)
{

  __HAL_RCC_DMA1_CLK_ENABLE();

  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
}

/**
 * @brief  Initialize SPI1
 * @retval None
 */
static void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 0x0;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi1.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi1.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief  Initialize I2C1
 * @retval None
 */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10B0C4FF;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief  GPIO initialization
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Pin startup status */
  HAL_GPIO_WritePin(GPIOB, GC9A01_CS_Pin | GC9A01_DC_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, GC9A01_RST_Pin | GC9A01_BL_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, PLUS_BTN_Pin | SET_BTN_Pin | MINUS_BTN_Pin, GPIO_PIN_SET);

  /* Configure GPIO pins : GC9A01_CS_Pin GC9A01_DC_Pin GC9A01_RST_Pin GC9A01_BL_Pin */
  GPIO_InitStruct.Pin = GC9A01_CS_Pin | GC9A01_DC_Pin | GC9A01_RST_Pin | GC9A01_BL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Configure GPIO pins : PLUS_BTN_Pin SET_BTN_Pin MINUS_BTN_Pin */
  GPIO_InitStruct.Pin = PLUS_BTN_Pin | SET_BTN_Pin | MINUS_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* Configure GPIO pins : FXLS8974CF_INT_Pin */
  GPIO_InitStruct.Pin = FXLS8974CF_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(FXLS8974CF_INT_Port, &GPIO_InitStruct);

  /* Enable interrupts on buttons */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  /* Enable interrupts from accelerometer */
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

/**
 * @brief  Test routine
 * @retval None
 */
static int test_process(void)
{

  test_pass_t pass = {0};
  FIL log;

  if (TEST_DISPLAY)
    /* Sends data to the display to show an image */
    pass.display_pass = (TEST_STATUS_t)smart_watch_test_display();
  else
    pass.display_pass = NA;

  if (TEST_SD)
    /* Reads all the data from a file caled a000.avi and re-writes them in out.avi
     * Requires few minutes to complete
     */
    pass.sd_pass = (TEST_STATUS_t)smart_watch_test_sd();
  else
    pass.sd_pass = NA;

  if (TEST_MJPEG)
    pass.mjpeg_pass = (TEST_STATUS_t)smart_watch_test_mjpeg();
  else
    pass.mjpeg_pass = NA;

  if (TEST_ACCELEROMETER)
    pass.mjpeg_pass = (TEST_STATUS_t)smart_watch_test_accelerometer(&acc_Handle);
  else
    pass.mjpeg_pass = NA;

#ifdef ENABLE_BATTERY_MON
  if (TEST_ADC)
    pass.mjpeg_pass = (TEST_STATUS_t)smart_watch_test_adc();
  else
    pass.mjpeg_pass = NA;
#endif

  if (f_open(&log, "log.txt", (FA_WRITE | FA_CREATE_ALWAYS)) != FR_OK)
    return -1;

  print_log(&log, pass.display_pass, "DISPLAY_TEST");
  print_log(&log, pass.sd_pass, "SD_TEST");
  print_log(&log, pass.mjpeg_pass, "MJPEG_TEST");

  f_close(&log);

  return 1;
}

/**
 * @brief  Print the log
 * @param  log_file: pointer to the log file
 * @param  status: status of the test
 * @param  test_name: name of the test
 * @retval int
 */
static int print_log(FIL *log_file, TEST_STATUS_t status, char *test_name)
{

  char buff[50];
  char res[20];
  unsigned int bw = 0;
  unsigned int btw = 0;

  if (status == NA)
  {

    snprintf(res, sizeof(res), "%s", "NA");
    snprintf(buff, sizeof(buff), "%-20s%20s\n\n", test_name, res);
  }
  else
  {

    snprintf(res, sizeof(res), "%s", (status == PASSED) ? "PASSED" : "NOT PASSED");
    snprintf(buff, sizeof(buff), "%-20s%20s\n\n", test_name, res);
  }

  btw = strlen(buff);
  if (f_write(log_file, buff, btw, &bw) != FR_OK)
    return -1;

  if (bw != btw)
    return -1;

  return 1;
}

/** @} */ // end of Private_Functions_Def group