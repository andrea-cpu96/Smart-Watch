/**
  ******************************************************************************
  * @file    JPEG/JPEG_DecodingUsingFs_Polling/CM7/Src/decode_polling.c
  * @author  MCD Application Team
  * @brief   This file provides routines for JPEG decoding with polling method.
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

#include "decode_polling.h"


typedef struct
{

  uint8_t *DataBuffer;
  uint32_t DataBufferSize;

}JPEG_Data_BufferTypeDef;


uint8_t MCU_Data_OutBuffer[CHUNK_SIZE_OUT];
uint8_t JPEG_Data_InBuffer[CHUNK_SIZE_IN];

JPEG_Data_BufferTypeDef JPEG_InBuffer = { JPEG_Data_InBuffer , 0};

uint32_t MCU_TotalNb = 0;
uint32_t MCU_BlockIndex = 0;
uint32_t Inputfile_Offset = 0;
uint32_t Jpeg_Decoding_End = 0;

uint32_t FrameBufferAddress;

uint8_t *startSourceAddress;
uint8_t *pVideoBuffer;


/**
  * @brief  Decode_Polling
  * @param hjpeg: JPEG handle pointer
  * @param  file   : pointer to file object
  * @param  DestAddress : ARGB destination Frame Buffer Address.
  * @retval None
  */
uint32_t JPEG_DecodePolling(JPEG_HandleTypeDef *hjpeg, AVI_CONTEXT* AVI_Handel, uint32_t DestAddress)
{


  startSourceAddress = AVI_Handel->pVideoBuffer;
  FrameBufferAddress = DestAddress;
  pVideoBuffer = AVI_Handel->pVideoBuffer;

  // Read from JPG file and fill the input buffer
  memcpy(JPEG_InBuffer.DataBuffer, AVI_Handel->pVideoBuffer, CHUNK_SIZE_IN*sizeof(uint8_t));

  // Increment the input buffer pointer
  pVideoBuffer += CHUNK_SIZE_IN;

  // Update the file Offset
  Inputfile_Offset = JPEG_InBuffer.DataBufferSize;

  //Start JPEG decoding with polling (Blocking) method
  HAL_JPEG_Decode(hjpeg ,JPEG_InBuffer.DataBuffer ,JPEG_InBuffer.DataBufferSize ,(uint8_t *)FrameBufferAddress ,CHUNK_SIZE_OUT,HAL_MAX_DELAY);

  return 0;

}


/**
  * @brief  JPEG Info ready callback
  * @param hjpeg: JPEG handle pointer
  * @param pInfo: JPEG Info Struct pointer
  * @retval None
  */
void HAL_JPEG_InfoReadyCallback(JPEG_HandleTypeDef *hjpeg, JPEG_ConfTypeDef *pInfo)
{
}

/**
  * @brief  JPEG Get Data callback
  * @param hjpeg: JPEG handle pointer
  * @param NbDecodedData: Number of decoded (consumed) bytes from input buffer
  * @retval None
  */
void HAL_JPEG_GetDataCallback(JPEG_HandleTypeDef *hjpeg, uint32_t NbDecodedData)
{

  if(NbDecodedData != JPEG_InBuffer.DataBufferSize)
  {

    Inputfile_Offset = Inputfile_Offset - JPEG_InBuffer.DataBufferSize + NbDecodedData;
    pVideoBuffer = ( startSourceAddress + Inputfile_Offset );

  }

  // Read from JPG file and fill the input buffer
  memcpy(JPEG_InBuffer.DataBuffer, pVideoBuffer, CHUNK_SIZE_IN*sizeof(uint8_t));

  Inputfile_Offset += JPEG_InBuffer.DataBufferSize;
  HAL_JPEG_ConfigInputBuffer(hjpeg, JPEG_InBuffer.DataBuffer, JPEG_InBuffer.DataBufferSize);

}

/**
  * @brief  JPEG Data Ready callback
  * @param hjpeg: JPEG handle pointer
  * @param pDataOut: pointer to the output data buffer
  * @param OutDataLength: length of output buffer in bytes
  * @retval None
  */
void HAL_JPEG_DataReadyCallback (JPEG_HandleTypeDef *hjpeg, uint8_t *pDataOut, uint32_t OutDataLength)
{
  /* Update JPEG encoder output buffer address*/
  FrameBufferAddress += OutDataLength;

  HAL_JPEG_ConfigOutputBuffer(hjpeg, (uint8_t *)FrameBufferAddress, CHUNK_SIZE_OUT);

}

/**
  * @brief  JPEG Error callback
  * @param hjpeg: JPEG handle pointer
  * @retval None
  */
void HAL_JPEG_ErrorCallback(JPEG_HandleTypeDef *hjpeg)
{

  while(1);

}

/**
  * @brief  JPEG Decode complete callback
  * @param hjpeg: JPEG handle pointer
  * @retval None
  */
void HAL_JPEG_DecodeCpltCallback(JPEG_HandleTypeDef *hjpeg)
{

  Jpeg_Decoding_End = 1;

}

