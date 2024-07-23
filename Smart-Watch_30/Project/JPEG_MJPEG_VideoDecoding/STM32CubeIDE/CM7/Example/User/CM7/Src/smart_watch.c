/*
 * smart_watch.c
 *
 *  Created on: Jul 22, 2024
 *      Author: andre
 */

#include "main.h"
#include "smart_watch.h"
#include "decode_dma.h"
#include "GC9A01.h"


#define MJPEG_VID_BUFFER_SIZE ((uint32_t)(1024 *96))
#define MJPEG_AUD_BUFFER_SIZE ((uint32_t)(1024 *0))


static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx);
static void lcd_draw(uint16_t sx, uint16_t sy, uint16_t wd, uint16_t ht, uint8_t *data);
static void DMA2D_Init(uint16_t xsize, uint16_t ysize, uint32_t ChromaSampling);
static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t ImageWidth, uint16_t ImageHeight);
static void SD_Initialize(void);


uint32_t isfirstFrame =0;
uint32_t file_error = 0, sd_detection_error = 0;
uint32_t jpegOutDataAdreess = JPEG_OUTPUT_DATA_BUFFER0;
uint32_t FrameType = 0;

uint8_t MJPEG_VideoBuffer[MJPEG_VID_BUFFER_SIZE] ;
uint8_t MJPEG_AudioBuffer[MJPEG_AUD_BUFFER_SIZE] ;

uint32_t LCD_X_Size = 240, LCD_Y_Size = 240;

extern __IO uint32_t Jpeg_HWDecodingEnd;

FATFS SDFatFs;  /* File system object for SD card logical drive */
char SDPath[4]; /* SD card logical drive path */

FIL MJPEG_File;          /* MJPEG File object */
AVI_CONTEXT AVI_Handel;  /* AVI Parser Handle*/


void smart_watch_process(void)
{

  char *file_name[24];
  file_name[0] = "video_000.avi";
  file_name[1] = "video_001.avi";
  file_name[2] = "video_002.avi";
  file_name[3] = "video_003.avi";
  file_name[4] = "video_004.avi";
  file_name[5] = "video_005.avi";
  file_name[6] = "video_006.avi";
  file_name[7] = "video_007.avi";
  file_name[8] = "video_008.avi";
  file_name[9] = "video_009.avi";
  file_name[10] = "video_010.avi";
  file_name[11] = "video_011.avi";
  file_name[12] = "video_012.avi";
  file_name[13] = "video_013.avi";
  file_name[14] = "video_014.avi";
  file_name[15] = "video_015.avi";
  file_name[16] = "video_016.avi";
  file_name[17] = "video_017.avi";
  file_name[18] = "video_018.avi";
  file_name[19] = "video_019.avi";
  file_name[20] = "video_020.avi";
  file_name[21] = "video_021.avi";
  file_name[22] = "video_022.avi";
  file_name[23] = "video_023.avi";


  /*##-3- Link the micro SD disk I/O driver ##################################*/
  if(FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
  {
    /*##-4- Init the SD Card #################################################*/
    SD_Initialize();

    if(BSP_SD_IsDetected(0))
    {
      /*##-5- Register the file system object to the FatFs module ##############*/
      if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) == FR_OK)
      {

    	for(int i = 0 ; i < 24 ; i++)
    	{

    		char *name = file_name[i];

    		/*##-6- Open the MJPEG avi file with read access #######################*/
    		if(f_open(&MJPEG_File, name, FA_READ) == FR_OK)
    		{

    			isfirstFrame = 1;

    			/* parse the AVI file Header*/
    			if(AVI_ParserInit(&AVI_Handel, &MJPEG_File, MJPEG_VideoBuffer, MJPEG_VID_BUFFER_SIZE, MJPEG_AudioBuffer, MJPEG_AUD_BUFFER_SIZE) != 0)
    			{

    				while(1);

    			}

    			do
    			{

    				//uint32_t oldTime = HAL_GetTick();

    				FrameType = AVI_GetFrame(&AVI_Handel, &MJPEG_File);

    				if(FrameType == AVI_VIDEO_FRAME)
    				{

    					AVI_Handel.CurrentImage ++;


    					JPEG_Decode_DMA(&JPEG_Handle,(uint32_t) MJPEG_VideoBuffer ,AVI_Handel.FrameSize, jpegOutDataAdreess );

    					while(Jpeg_HWDecodingEnd == 0);

    					if(isfirstFrame == 1)
    					{

    						isfirstFrame = 0;

    						HAL_JPEG_GetInfo(&JPEG_Handle, &JPEG_Info);

    						DMA2D_Init(JPEG_Info.ImageWidth, JPEG_Info.ImageHeight, JPEG_Info.ChromaSubsampling);

    					}

    					DMA2D_CopyBuffer((uint32_t *)jpegOutDataAdreess, (uint32_t *)LCD_FRAME_BUFFER, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);

    					jpegOutDataAdreess = (jpegOutDataAdreess == JPEG_OUTPUT_DATA_BUFFER0) ? JPEG_OUTPUT_DATA_BUFFER1 : JPEG_OUTPUT_DATA_BUFFER0;

    				}

    				uint16_t width = JPEG_Info.ImageWidth;
    				uint16_t height = JPEG_Info.ImageHeight;

    				uint16_t xPos = (LCD_X_Size - width)/2;					// Center the image in x
    				uint16_t yPos = (LCD_Y_Size - height)/2;					// Center the image in y

    				doubleFormat pOut;
    				pOut.u8Arr = (uint8_t *)LCD_FRAME_BUFFER;

    				depth24To16(&pOut, ( width * height ), 3);

    				//uint32_t newTime = 0;
    				//uint32_t elapsed = 0;

    				// Display the image
    				lcd_draw(xPos, yPos, width, height, pOut.u8Arr);

    				//newTime = HAL_GetTick();

    				//elapsed = newTime - oldTime;

    				//HAL_Delay(1);

    			}while(AVI_Handel.CurrentImage  <  AVI_Handel.aviInfo.TotalFrame);

    			HAL_DMA2D_PollForTransfer(&DMA2D_Handle, 50);  /* wait for the Last DMA2D transfer to ends */

    			/*Close the avi file*/
    			f_close(&MJPEG_File);

    		}
    		else /* Can't Open avi file*/
    		{

    			file_error = 1;

    		}

    	}

      }

    }
    else
    {

      sd_detection_error = 1;

    }

    if((file_error != 0) || (sd_detection_error != 0))
    {

      while(1);

    }

  }

}


static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx)
{

	uint8_t b;
	uint8_t g;
	uint8_t r;

	int i = 0;

    if(AVI_Handel.CurrentImage % 2)
    {

    	i = 0;
    	length /= 2;
    	length += 1000;

    }
    else
    {

    	i = ( length / 2 ) - 2000;

    }

	for( ; i < length ; i++)
	{

		b = pxArr->u8Arr[i*bpx];
		g = pxArr->u8Arr[i*bpx+1];
		r = pxArr->u8Arr[i*bpx+2];

		pxArr->u16Arr[i] = color565(r, g, b);
		pxArr->u16Arr[i] = ( ( ( pxArr->u16Arr[i] & 0x00ff ) << 8 ) | (( pxArr->u16Arr[i] & 0xff00 ) >> 8) );

	}

}


static void lcd_draw(uint16_t sx, uint16_t sy, uint16_t wd, uint16_t ht, uint8_t *data)
{

	   struct GC9A01_frame frame;

	    // Imposta il frame per l'intera area specificata
	   	if(AVI_Handel.CurrentImage%2)
	   	{

	        frame.start.X = 0;
	        frame.start.Y = 0;
	        frame.end.X = 239;
	        frame.end.Y = 119;

	   	}
	   	else
	   	{

	   		data += ( 240 * 240 );

	        frame.start.X = 0;
	        frame.start.Y = 120;
	        frame.end.X = 239;
	        frame.end.Y = 239;

	   	}

	    GC9A01_set_frame(frame);

	    // Invia il comando per iniziare la scrittura della memoria
	    GC9A01_write_command(MEM_WR);

	    // Imposta modalità dati e chip select basso per la trasmissione
	    GC9A01_set_data_command(ON);
	    GC9A01_set_chip_select(OFF);

	    // Invia tutti i dati dell'immagine in un unico blocco
	    uint32_t total_bytes = wd * ht; // 2 byte per pixel

	    GC9A01_spi_tx(data, total_bytes);

	    // Riporta chip select alto dopo la trasmissione
	    GC9A01_set_chip_select(ON);

}


static void DMA2D_Init(uint16_t xsize, uint16_t ysize, uint32_t ChromaSampling)
{
  uint32_t cssMode = JPEG_420_SUBSAMPLING, inputLineOffset = 0;

  HAL_DMA2D_MspInit(&DMA2D_Handle);

  if(ChromaSampling == JPEG_420_SUBSAMPLING)
  {
    cssMode = DMA2D_CSS_420;

    inputLineOffset = xsize % 16;
    if(inputLineOffset != 0)
    {
      inputLineOffset = 16 - inputLineOffset;
    }
  }
  else if(ChromaSampling == JPEG_444_SUBSAMPLING)
  {
    cssMode = DMA2D_NO_CSS;

    inputLineOffset = xsize % 8;
    if(inputLineOffset != 0)
    {
      inputLineOffset = 8 - inputLineOffset;
    }
  }
  else if(ChromaSampling == JPEG_422_SUBSAMPLING)
  {
    cssMode = DMA2D_CSS_422;

    inputLineOffset = xsize % 16;
    if(inputLineOffset != 0)
    {
      inputLineOffset = 16 - inputLineOffset;
    }
  }

  /*##-1- Configure the DMA2D Mode, Color Mode and output offset #############*/
  DMA2D_Handle.Init.Mode         = DMA2D_M2M_PFC;
  DMA2D_Handle.Init.ColorMode    = DMA2D_OUTPUT_RGB888;
  DMA2D_Handle.Init.OutputOffset = LCD_X_Size - xsize;
  DMA2D_Handle.Init.AlphaInverted = DMA2D_REGULAR_ALPHA;  /* No Output Alpha Inversion*/
  DMA2D_Handle.Init.RedBlueSwap   = DMA2D_RB_REGULAR;     /* No Output Red & Blue swap */

  /*##-2- DMA2D Callbacks Configuration ######################################*/
  DMA2D_Handle.XferCpltCallback  = NULL;

  /*##-3- Foreground Configuration ###########################################*/
  DMA2D_Handle.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
  DMA2D_Handle.LayerCfg[1].InputAlpha = 0xFF;
  DMA2D_Handle.LayerCfg[1].InputColorMode = DMA2D_INPUT_YCBCR;
  DMA2D_Handle.LayerCfg[1].ChromaSubSampling = cssMode;
  DMA2D_Handle.LayerCfg[1].InputOffset = inputLineOffset;
  DMA2D_Handle.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */
  DMA2D_Handle.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */

  DMA2D_Handle.Instance          = DMA2D;

  /*##-4- DMA2D Initialization     ###########################################*/
  HAL_DMA2D_Init(&DMA2D_Handle);
  HAL_DMA2D_ConfigLayer(&DMA2D_Handle, 1);

}


static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t ImageWidth, uint16_t ImageHeight)
{

  uint32_t xPos, yPos, destination;


  /*##-1- calculate the destination transfer address  ############*/
  xPos = (LCD_X_Size - JPEG_Info.ImageWidth)/2;
  yPos = (LCD_Y_Size - JPEG_Info.ImageHeight)/2;

  destination = (uint32_t)pDst + ((yPos * LCD_X_Size) + xPos) * 4;

  /* wait for the DMA2D transfer to ends */
  HAL_DMA2D_PollForTransfer(&DMA2D_Handle, HAL_MAX_DELAY);
  /* copy the new decoded frame to the LCD Frame buffer*/
  HAL_DMA2D_Start(&DMA2D_Handle, (uint32_t)pSrc, destination, ImageWidth, ImageHeight);

}


static void SD_Initialize(void)
{
  BSP_SD_Init(0);
}
