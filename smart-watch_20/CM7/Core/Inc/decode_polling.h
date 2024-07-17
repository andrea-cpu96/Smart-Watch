/**
  ******************************************************************************
  * @file    JPEG/JPEG_DecodingUsingFs_Polling/Inc/decode_polling.h
  * @author  MCD Application Team
  * @brief   Header for decode_polling.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DECODE_POLLING_H
#define __DECODE_POLLING_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "AVI_parser.h"
#include "lcd.h"


#define CHUNK_SIZE_IN  			((uint32_t)(40 * 1024))
#define CHUNK_SIZE_OUT 			((uint32_t)(40 * 1024))


extern uint32_t Jpeg_Decoding_End;


/* Exported variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint32_t JPEG_DecodePolling(JPEG_HandleTypeDef *hjpeg, AVI_CONTEXT* AVI_Handel, uint32_t DestAddress);

#endif /* __DECODE_POLLING_H */
