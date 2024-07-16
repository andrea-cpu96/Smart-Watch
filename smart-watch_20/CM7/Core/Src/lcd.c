/*
 * lcd.c
 *
 *  Created on: Jun 1, 2024
 *      Author: Fato
 */

#include "main.h"
#include "lcd.h"
#include "bmp.h"
#include "AVI_parser.h"
#ifdef MJPEG_ON
#include "decode_DMA.h"
#else
#include "decode_polling.h"
#endif


static void triangle_ex(void);
static void rainbow_ex(void);
static void checkboard_ex(void);
static void swissFlag_ex(void);
static void sd_init(void);
static void sd_error_handler(void);
static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx);
//static void imageWindowed(doubleFormat *data);
static void DMA2D_Init(uint16_t xsize, uint16_t ysize, uint32_t ChromaSampling);
static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t xsize, uint16_t ysize);


// sd
FATFS SDFatFs;  												// File system object for SD card logical drive
FIL file;          												// File object
uint8_t rtext[_MAX_SS];											// File read buffer

// bmp
BMP *bmp;

//JPEG
DMA2D_HandleTypeDef DMA2D_Handle;
JPEG_ConfTypeDef JPEG_Info;										// Contains the JPEG file information

// AVI
AVI_CONTEXT AVI_Handel;  										// AVI Parser Handle

// lcd
uint8_t color[3];




/********************************************************************************
 * 																				*
 * 																				*
 * 																				*
 * 								GLOBAL FUNCTIONS								*
 * 																				*
 * 																				*
 * 																				*
 ********************************************************************************/




void lcd_init(void)
{

	// SD card initialization
	sd_init();

	// Initialize the YCbCr to RGB color conversion tables.
	JPEG_InitColorTables();

	// Display driver initialization
	GC9A01_init();

}


void lcd_process(void)
{

	// sd_image_demo();
	// lcd_demo();
	//jpeg_demo();

	mjpeg_demo();

}


void lcd_draw(uint16_t sx, uint16_t sy, uint16_t wd, uint16_t ht, uint8_t *data)
{

	for(int x = sx; x < ( wd + sx ) ; x++)
	{

		for(int y = sy; y < ( ht + sy ) ; y++)
		{

			if (x == sx && y == sy)
			{

				GC9A01_write(data, 2);

			}
			else
			{

				GC9A01_write_continue(data, 2);

			}

			data += 2;

		}

	}

}

#ifdef JPEG_ON

void jpeg_demo(void)
{

	uint8_t JPEG_OutputBuffer[MAX_BUFFER_SIZE]; 					// RAW buffer
	uint8_t DECODED_OutputBuffer[MAX_BUFFER_SIZE];					// Decoded buffer


    // File opening in reading
    if(f_open(&file, FILE_NAME, FA_READ) != FR_OK)
    	while(1);

    // JPEG decoding in polling mode
    JPEG_DecodePolling(&hjpeg, &file, (uint32_t)JPEG_OutputBuffer);

    // Wait until the end of the conversion
    while(!Jpeg_Decoding_End);

    // Get info from the JPEG file
    HAL_JPEG_GetInfo(&hjpeg, &JPEG_Info);

    uint16_t width = JPEG_Info.ImageWidth;
	uint16_t height = JPEG_Info.ImageHeight;

    uint16_t xPos = (LCD_WIDTH - width)/2;					// Center the image in x
    uint16_t yPos = (LCD_WIDTH - height)/2;					// Center the image in y

    // Convert the YCbCr format into the RGBB565 format
    DMA2D_Init(JPEG_Info.ImageWidth, JPEG_Info.ImageHeight, JPEG_Info.ChromaSubsampling);
    DMA2D_CopyBuffer((uint32_t *)JPEG_OutputBuffer, (uint32_t *)DECODED_OutputBuffer, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);

    doubleFormat pOut;
    pOut.u8Arr = DECODED_OutputBuffer;

    depth24To16(&pOut, width*height, 3);

    // Display the image
    lcd_draw(xPos, yPos, width, height, pOut.u8Arr);

    // Close file
    f_close(&file);

}

#endif

uint8_t isfirstFrame = 1;
uint8_t FrameRate = 0;
uint32_t startTime = 0;

#ifdef MJPEG_ON

uint8_t MJPEG_VideoBuffer[MJPEG_VID_BUFFER_SIZE];
uint8_t MJPEG_AudioBuffer[MJPEG_AUD_BUFFER_SIZE];
uint8_t JPEG_OutputBuffer_0[MAX_BUFFER_SIZE];
uint8_t DECODED_OutputBuffer[MAX_BUFFER_SIZE];

void mjpeg_demo(void)
{
					// RAW buffer 0
	//uint8_t JPEG_OutputBuffer_1[MAX_BUFFER_SIZE]; 				// RAW buffer 1

	uint32_t jpegOutDataAdreess = (uint32_t)JPEG_OutputBuffer_0;
	uint32_t FrameType = 0;

	memset(MJPEG_VideoBuffer, 255, MJPEG_VID_BUFFER_SIZE*sizeof(uint8_t));
	memset(MJPEG_AudioBuffer, 255, MJPEG_AUD_BUFFER_SIZE*sizeof(uint8_t));
	memset(JPEG_OutputBuffer_0, 255, MAX_BUFFER_SIZE*sizeof(uint8_t));

	// Open the MJPEG avi file with read access
    if(f_open(&file, FILE_NAME, FA_READ) == FR_OK)
    {

    	isfirstFrame = 1; // First frame flag
    	FrameRate = 0;

    	// Parse the AVI file Header
    	if(AVI_ParserInit(&AVI_Handel, &file, MJPEG_VideoBuffer, MJPEG_VID_BUFFER_SIZE, MJPEG_AudioBuffer, MJPEG_AUD_BUFFER_SIZE) != 0)
    		while(1);

    	// Get current tick to track the frame time
    	startTime = HAL_GetTick();

    	do
    	{

    		FrameType = AVI_GetFrame(&AVI_Handel, &file);

    		if(FrameType == AVI_VIDEO_FRAME)
    		{

    			AVI_Handel.CurrentImage ++;

    			// Start decoding the current JPEG frame with DMA (Not Blocking ) Method
    			JPEG_Decode_DMA(&hjpeg,(uint32_t) MJPEG_VideoBuffer ,AVI_Handel.FrameSize, jpegOutDataAdreess );

    			// Wait till end of JPEG decoding
    			while(Jpeg_HWDecodingEnd == 0);

    			if(isfirstFrame == 1)
    			{

    				// First time

    				isfirstFrame = 0;

    				// Get JPEG Info
    				HAL_JPEG_GetInfo(&hjpeg, &JPEG_Info);

    				// Initialize the DMA2D
    				DMA2D_Init(JPEG_Info.ImageWidth, JPEG_Info.ImageHeight, JPEG_Info.ChromaSubsampling);

    			}


    			// Copy the Decoded frame to the display frame buffer using the DMA2D
    			DMA2D_CopyBuffer((uint32_t *)jpegOutDataAdreess, (uint32_t *)DECODED_OutputBuffer, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);

    			// Change frame buffer
    			//jpegOutDataAdreess = (jpegOutDataAdreess == (uint32_t)JPEG_OutputBuffer_0) ? (uint32_t)JPEG_OutputBuffer_1 : (uint32_t)JPEG_OutputBuffer_0;
    			jpegOutDataAdreess = (uint32_t)JPEG_OutputBuffer_0;

//
    		    uint16_t width = JPEG_Info.ImageWidth;
    			uint16_t height = JPEG_Info.ImageHeight;

    		    uint16_t xPos = (LCD_WIDTH - width)/2;					// Center the image in x
    		    uint16_t yPos = (LCD_WIDTH - height)/2;					// Center the image in y

    		    doubleFormat pOut;
    		    pOut.u8Arr = DECODED_OutputBuffer;

    		    depth24To16(&pOut, width*height, 3);

    		    // Display the image
    		    lcd_draw(xPos, yPos, width, height, pOut.u8Arr);
//

    		}

#ifdef USE_FRAMERATE_REGULATION

              // Regulate the frame rate to the video native frame rate by inserting delays
              FrameRate =  (HAL_GetTick() - startTime) + 1;

              if(FrameRate < ((AVI_Handel.aviInfo.SecPerFrame/1000) * AVI_Handel.CurrentImage))
                HAL_Delay(((AVI_Handel.aviInfo.SecPerFrame /1000) * AVI_Handel.CurrentImage) - FrameRate);

#endif /* USE_FRAMERATE_REGULATION */

    	}while(AVI_Handel.CurrentImage  <  AVI_Handel.aviInfo.TotalFrame);

    	HAL_DMA2D_PollForTransfer(&DMA2D_Handle, 50);


      f_close(&file);

    }
    else
    {

      while(1);

    }

}

#endif


void lcd_demo(void)
{

    // Triangle //

	triangle_ex();

    HAL_Delay(1000);

    // Rainbow //

    rainbow_ex();

    HAL_Delay(1000);

    // Checkerboard //

    checkboard_ex();

    HAL_Delay(1000);

    // Swiss flag //

    swissFlag_ex();

    GC9A01_write_command(0x20); // Change colours

    HAL_Delay(1000);

}


void sd_image_demo(void)
{

	showImageBmp(bmp);

	HAL_Delay(2000);

}




/********************************************************************************
 * 																				*
 * 																				*
 * 																				*
 * 								PRIVATE FUNCTIONS								*
 * 																				*
 * 																				*
 * 																				*
 ********************************************************************************/



static void triangle_ex(void)
{

	color[0] = 0xFF;
	color[1] = 0xFF;

	for(int x = 0 ; x < LCD_WIDTH ; x++)
	{

		for(int y = 0 ; y < LCD_WIDTH ; y++)
		{

			if(x < y)
			{

				color[2] = 0xFF;

			}
			else
			{

				color[2] = 0x00;

			}

			if(x == 0 && y == 0)
			{

				GC9A01_write(color, sizeof(color));

			}
			else
			{

				GC9A01_write_continue(color, sizeof(color));

			}

		}

	}

}


static void rainbow_ex(void)
{

	float frequency = 0.026;

	for(int x = 0 ; x < LCD_WIDTH ; x++)
	{

		color[0] = sin(frequency*x + 0) * 127 + 128;
		color[1] = sin(frequency*x + 2) * 127 + 128;
		color[2] = sin(frequency*x + 4) * 127 + 128;
		for(int y = 0 ; y < LCD_WIDTH ; y++)
		{

			if (x == 0 && y == 0)
			{

				GC9A01_write(color, sizeof(color));

			}
			else
			{

				GC9A01_write_continue(color, sizeof(color));

			}

		}

	}

}


static void checkboard_ex(void)
{

	for(int x = 0 ; x < LCD_WIDTH ; x++)
	{

		for(int y = 0 ; y < LCD_WIDTH ; y++)
		{

			if((x / 10) % 2 ==  (y / 10) % 2)
			{

				color[0] = 0xFF;
				color[1] = 0xFF;
				color[2] = 0xFF;

			}
			else
			{

				color[0] = 0x00;
				color[1] = 0x00;
				color[2] = 0x00;

			}
			if(x == 0 && y == 0)
			{

				GC9A01_write(color, sizeof(color));

			}
			else
			{

				GC9A01_write_continue(color, sizeof(color));

			}

		}

	}

}


static void swissFlag_ex(void)
{

	color[0] = 0xFF;

	for(int x = 0 ; x < LCD_WIDTH ; x++)
	{

		for(int y = 0 ; y < LCD_WIDTH ; y++)
		{

			if((x >= 1*48 && x < 4*48 && y >= 2*48 && y < 3*48) ||
				(x >= 2*48 && x < 3*48 && y >= 1*48 && y < 4*48))
			{

				color[1] = 0xFF;
				color[2] = 0xFF;

			}
			else
			{

				color[1] = 0x00;
				color[2] = 0x00;

			}
			if(x == 0 && y == 0)
			{

				GC9A01_write(color, sizeof(color));

			}
			else
			{

				GC9A01_write_continue(color, sizeof(color));

			}

		}

	}

}


// SD

static void sd_init(void)
{

    if(f_mount(&SDFatFs, "", 1) != FR_OK)
    	sd_error_handler();

    //if(f_mkfs((TCHAR const*)SDPath, FM_ANY, 0, rtext, sizeof(rtext)) != FR_OK)
		//sd_error_handler();

}


static void sd_error_handler(void)
{

	while(1);

}


static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx)
{

	uint8_t b;
	uint8_t g;
	uint8_t r;


	for(int i = 0 ; i < length ; i++)
	{

		b = pxArr->u8Arr[i*bpx];
		g = pxArr->u8Arr[i*bpx+1];
		r = pxArr->u8Arr[i*bpx+2];

		pxArr->u16Arr[i] = color565(r, g, b);
		pxArr->u16Arr[i] = ( ( ( pxArr->u16Arr[i] & 0x00ff ) << 8 ) | (( pxArr->u16Arr[i] & 0xff00 ) >> 8) );

	}

}

/*
static void imageWindowed(doubleFormat *data)
{

	uint16_t tmp;


	for(int i = 0 ; i < LCD_WIDTH ; i++)
	{

		for(int j = 0 ; j < 120 ; j++)
		{

			tmp = data->u16Arr[j+(i*LCD_WIDTH)];
			data->u16Arr[j+(i*LCD_WIDTH)] = data->u16Arr[(LCD_WIDTH-1-j)+(i*LCD_WIDTH)];
			data->u16Arr[(LCD_WIDTH-1-j)+(i*LCD_WIDTH)] = tmp;

		}

	}

}
*/


/**
  * @brief  Copy the Decoded image to the display Frame buffer.
  * @param  pSrc: Pointer to source buffer
  * @param  pDst: Pointer to destination buffer
  * @param  x: destination horizenatl offset.
  * @param  y: destination Vertical offset.
  * @param  xSize: image width
  * @param  ysize: image Height
  * @retval None
  */
static void DMA2D_Init(uint16_t xsize, uint16_t ysize, uint32_t ChromaSampling)
{

  uint32_t cssMode = DMA2D_CSS_420, inputLineOffset = 0;


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
  DMA2D_Handle.Init.OutputOffset = LCD_WIDTH - xsize;
  DMA2D_Handle.Init.AlphaInverted = DMA2D_REGULAR_ALPHA;  /* No Output Alpha Inversion*/
  DMA2D_Handle.Init.RedBlueSwap   = DMA2D_RB_REGULAR;     /* No Output Red & Blue swap */

  /*##-2- DMA2D Callbacks Configuration ######################################*/
  DMA2D_Handle.XferCpltCallback  = NULL;

  /*##-3- Foreground Configuration ###########################################*/
  DMA2D_Handle.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
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


static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t xsize, uint16_t ysize)
{

  uint32_t destination = 0;


  uint16_t x =  ( (LCD_WIDTH - xsize) / 2 );
  uint16_t y = ( (LCD_HEIGHT - ysize) / 2 );

  /*##-5-  copy the new decoded frame to the LCD Frame buffer ################*/
  destination = (uint32_t)pDst + ((y * LCD_WIDTH) + x) * 4;

  HAL_DMA2D_Start(&DMA2D_Handle, (uint32_t)pSrc, destination, xsize, ysize);
  HAL_DMA2D_PollForTransfer(&DMA2D_Handle, 25);  /* wait for the previous DMA2D transfer to ends */

}
