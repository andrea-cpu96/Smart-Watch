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

uint32_t Input_frameIndex;
uint32_t Input_frameIndex;



/**
  * @brief  Decode_Polling
  * @param hjpeg: JPEG handle pointer
  * @param  file   : pointer to file object
  * @param  DestAddress : ARGB destination Frame Buffer Address.
  * @retval None
  */
uint32_t JPEG_DecodePolling(JPEG_HandleTypeDef *hjpeg, AVI_CONTEXT* AVI_Handel, uint32_t DestAddress)
{


  Jpeg_Decoding_End = 0;

  Input_frameIndex = 0;
  Input_frameSize = AVI_Handel->VideoBufferSize;

  startSourceAddress = AVI_Handel->pVideoBuffer;
  FrameBufferAddress = DestAddress;

  // Read from JPG file and fill the input buffer

  //memcpy(JPEG_InBuffer.DataBuffer, AVI_Handel->pVideoBuffer, Input_frameSize*sizeof(uint8_t));
  JPEG_InBuffer.DataBuffer = AVI_Handel->pVideoBuffer;
  JPEG_InBuffer.DataBufferSize = Input_frameSize;

  //Start JPEG decoding with polling (Blocking) method
  HAL_JPEG_Decode(hjpeg ,JPEG_InBuffer.DataBuffer, Input_frameSize, (uint8_t *)FrameBufferAddress, CHUNK_SIZE_OUT, 500);

  Jpeg_Decoding_End = 1;

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

	  uint32_t inDataLength;


	  Input_frameIndex += NbDecodedData;

	  if( Input_frameIndex < Input_frameSize)
	  {

		  JPEG_InBuffer.DataBuffer = JPEG_InBuffer.DataBuffer + NbDecodedData;

	    if((Input_frameSize - Input_frameIndex) >= CHUNK_SIZE_IN)
	      inDataLength = CHUNK_SIZE_IN;
	    else
	      inDataLength = Input_frameSize - Input_frameIndex;

	  }
	  else
	  {

	    inDataLength = 0;

	  }

	  HAL_JPEG_ConfigInputBuffer(hjpeg, (uint8_t *)JPEG_InBuffer.DataBuffer, inDataLength);

	  //startSourceAddress += inDataLength;
	  //JPEG_InBuffer.DataBuffer = startSourceAddress;

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
	if(JPEG->DOR == 0x80808080)
	{

		//HAL_JPEG_Abort(hjpeg);
		//Jpeg_Decoding_End = 1;

		while(1);

	}
	else
	{

		FrameBufferAddress += OutDataLength;
		HAL_JPEG_ConfigOutputBuffer(hjpeg, (uint8_t *)FrameBufferAddress, CHUNK_SIZE_OUT);

	}

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

