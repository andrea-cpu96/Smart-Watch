/*
 * smart_watch.c
 *
 *  Created on: Jul 22, 2024
 *      Author: Fato
 */

#include "main.h"
#include "decode_dma.h"
#include "AVI_parser.h"
#include "fatfs.h"

#include "GC9A01.h"

#include "smart_watch.h"

#include <stdio.h>

static void DMA2D_Init(uint16_t xsize, uint16_t ysize, uint32_t ChromaSampling);
static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t ImageWidth, uint16_t ImageHeight);

static void SD_Initialize(void);

static void mjpeg_video_processing(void);
static void file_handler(uint8_t openFile);

static void clock_normal(void);

static void parameters_reset(void);

static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx, uint8_t swap);

// FATFS can't handle huge files a time,
// so I separated it into multiple video
// of 30 minutes each one
//char *file_name[720];
char name[14];

uint8_t MJPEG_VideoBuffer[MJPEG_VID_BUFFER_SIZE];
uint8_t MJPEG_AudioBuffer[MJPEG_AUD_BUFFER_SIZE];

FATFS SDFatFs;  												// File system object for SD card logical drive
//char SDPath[4]; 												// SD card logical drive path

FIL MJPEG_File;          										// MJPEG File object
AVI_CONTEXT AVI_Handel;  										// AVI Parser Handle

video_t video;													// Video data structure


// Pre elaborated data buffer
uint8_t	preElab_data[300*1024];
// Output data buffer (format RGB565)
uint8_t output_data[200*1024];


void smart_watch_init(void)
{

	parameters_reset();

	// First time setting
	video.video_mode = SETTING_MODE;

	// SD card initialization
	// Link the micro SD disk I/O driver
	if(FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
	{

		// Init the SD Card
	    SD_Initialize();

	    // Register the file system object to the FatFs module
	    if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) != FR_OK)
	    {

	    	while(1);

	    }

  	}
	else
	{

		while(1);

	}

}

FIL fileToWrite;
void smart_watch_process(void)
{

#ifdef DEBUG_TIME
	static uint8_t count = 0;
	if(f_open(&fileToWrite, "time.txt", ( FA_WRITE | FA_CREATE_ALWAYS )) != FR_OK)
		while(1);
#endif

	while(1)
	{

		// Check if new file needs to be open
		file_handler(0);

		// Video processing unit
		mjpeg_video_processing();

#ifdef DEBUG_TIME
		count++;
		if(count > 100)
			f_close(&fileToWrite);
#endif

	}

}


int smart_watch_test_sd(void)
{

	FIL fileToRead;
	FIL fileToWrite;
	uint8_t buff[10500];

	unsigned int br = 0;
	unsigned int bw = 0;


	if(f_open(&fileToRead, "a000.avi", FA_READ) != FR_OK)
		return -1;

	HAL_Delay(1000);

	if(f_open(&fileToWrite, "out.avi", ( FA_WRITE | FA_CREATE_ALWAYS )) != FR_OK)
	{

		f_close(&fileToRead);

		return -1;

	}

	HAL_Delay(1000);

	uint32_t fsize = f_size(&fileToRead);

	while(f_read(&fileToRead, buff, 10000, &br) == FR_OK)
	{

		HAL_Delay(10);

		bw = 0;
		f_write(&fileToWrite, buff, br, &bw);

		if(bw != br)
		{

			f_close(&fileToRead);
			f_close(&fileToWrite);
			return -1;

		}

		if( fsize <= 0 )
			break;
		else
			fsize -= br;

	}

	f_close(&fileToRead);
	f_close(&fileToWrite);

	return 1;

}


int smart_watch_test_display(void)
{

	uint8_t data1[2*240*240+10];
	uint8_t data2[2*240*240+10];


	for(int i = 0 ; i < 2*240*240 + 10 ; i++)
	{
		data1[i] = 0xf8;
		data2[i] = 0x25;
	}

	if(lcd_draw(0, 0, 240, 240, data1, 0) < 0)
		return -1;
	if(lcd_draw(0, 0, 240, 240, data1, 1) < 0)
		return -1;

	if(lcd_draw(0, 0, 240, 240, data2, 0) < 0)
		return -1;
	if(lcd_draw(0, 0, 240, 240, data2, 1) < 0)
		return -1;

	return 1;

}


int smart_watch_test_mjpeg(void)
{

	static uint8_t swap = 0;

	unsigned long tempStart;
	unsigned long tempStop;
	unsigned long tempDiff[3];

	FIL fileToWrite;

	file_handler(0);

	if(f_open(&fileToWrite, "time.avi", ( FA_WRITE | FA_CREATE_ALWAYS )) != FR_OK)
		return -1;

	unsigned int bw = 0;
	char buff[50];

	for(int i = 0 ; i < 200 ; i++)
	{

		video.FrameType = AVI_GetFrame(&AVI_Handel, &MJPEG_File, 0);

		if(video.FrameType == AVI_VIDEO_FRAME)
		{

			AVI_Handel.CurrentImage++;
			video.frameCount++;

			// Decode the frame inside MJPEG_VideoBuffer and put it into jpegOutDataAdreess in the format YCrCb
			if(JPEG_Decode_DMA(&JPEG_Handle, (uint32_t)MJPEG_VideoBuffer, AVI_Handel.FrameSize, video.jpegOutDataAdreess) < 0)
			{

				f_close(&MJPEG_File);

				return -1;

			}

			while(Jpeg_HWDecodingEnd == 0);

			if(video.isfirstFrame == 1)
			{

				video.isfirstFrame = 0;

				HAL_JPEG_GetInfo(&JPEG_Handle, &JPEG_Info);

				DMA2D_Init(JPEG_Info.ImageWidth, JPEG_Info.ImageHeight, JPEG_Info.ChromaSubsampling);

				video.width = JPEG_Info.ImageWidth;
				video.height = JPEG_Info.ImageHeight;
				video.xPos =  ( ( LCD_Y_SIZE - video.width ) / 2 );					// Center the image in x
				video.yPos = ( ( LCD_Y_SIZE - video.height ) / 2 );					// Center the image in y

				video.frame_time = AVI_Handel.aviInfo.SecPerFrame;

			}

			// Copies the output frame into LCD_FRAME_BUFFER and does the conversion from YCrCb to RGB888
			DMA2D_CopyBuffer((uint32_t *)video.jpegOutDataAdreess, (uint32_t *)output_data, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);

			doubleFormat pOut;
			pOut.u8Arr = (uint8_t *)output_data;

			tempStart = HAL_GetTick();

			depth24To16(&pOut, ( video.width * video.height ), 3, swap);

			tempStop = HAL_GetTick();
			tempDiff[0] = ( ( tempStop - tempStart ) );

			if(lcd_draw(video.xPos, video.yPos, video.width, video.height, pOut.u8Arr, swap) < 0)
			{

				f_close(&MJPEG_File);

				return -1;

			}

			swap = ( ( swap ) ? 0 : 1 );

		}
		else
		{

			f_close(&MJPEG_File);

			return -1;

		}

		tempStop = HAL_GetTick();
		tempDiff[1] = ( ( tempStop - tempStart ) - tempDiff[0]);

		snprintf(buff, sizeof(buff), "SPI time = %.2ld\n", tempDiff[1]);
		f_write(&fileToWrite, buff, sizeof(buff), &bw);

		tempDiff[2] = 0;

	}

	f_close(&MJPEG_File);
	f_close(&fileToWrite);

	return 1;

}


int lcd_draw(uint16_t sx, uint16_t sy, uint16_t wd, uint16_t ht, uint8_t *data, uint8_t swap)
{

	   struct GC9A01_frame frame;

	   int ret = 0;


	   // Only half of the frame is handled per time
	   // Alternate the top and bottom half every cycle
	   if(swap)
	   {

	       frame.start.X = 0;
	       frame.start.Y = 0;
	       frame.end.X = 239;
	       frame.end.Y = 119;

	   }
	   else
	   {

		   data += ( 240 * 240 ) ;

	       frame.start.X = 0;
	       frame.start.Y = 120;
	       frame.end.X = 239;
	       frame.end.Y = 239;

	   }

	   // Sends the block of data in a single time

	   GC9A01_set_frame(frame);
	   GC9A01_write_command(MEM_WR);

	   GC9A01_set_data_command(ON);
	   GC9A01_set_chip_select(OFF);

	   uint32_t total_bytes = wd * ht;		// 2 byte per pixel
	   ret = GC9A01_spi_tx(data, total_bytes);

	   GC9A01_set_chip_select(ON);

	   return ret;

}


////////////////////////////////////////////////////// PRIVATE FUNCTIONS

static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx, uint8_t swap)
{

	uint8_t b;
	uint8_t g;
	uint8_t r;

	int i = 0;

	// Only half of the frame is handled per time
	// Alternate the top and bottom half every cycle
    if(swap)
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


static void mjpeg_video_processing(void)
{

	clock_normal();

}


static void clock_normal(void)
{

	static uint8_t swap = 0;


	// Save the frame into MJPEG_VideoBuffer
	video.FrameType = AVI_GetFrame(&AVI_Handel, &MJPEG_File, 0);

	if(video.FrameType == AVI_VIDEO_FRAME)
	{

		AVI_Handel.CurrentImage++;
		video.frameCount++;

		// Decode the frame inside MJPEG_VideoBuffer and put it into jpegOutDataAdreess in the format YCrCb
		JPEG_Decode_DMA(&JPEG_Handle, (uint32_t)MJPEG_VideoBuffer, AVI_Handel.FrameSize, video.jpegOutDataAdreess);

		while(Jpeg_HWDecodingEnd == 0);

		if(video.isfirstFrame == 1)
		{

			video.isfirstFrame = 0;

			HAL_JPEG_GetInfo(&JPEG_Handle, &JPEG_Info);

			DMA2D_Init(JPEG_Info.ImageWidth, JPEG_Info.ImageHeight, JPEG_Info.ChromaSubsampling);

			video.width = JPEG_Info.ImageWidth;
			video.height = JPEG_Info.ImageHeight;
			video.xPos =  ( ( LCD_Y_SIZE - video.width ) / 2 );					// Center the image in x
			video.yPos = ( ( LCD_Y_SIZE - video.height ) / 2 );					// Center the image in y

		}

		// Copies the output frame into LCD_FRAME_BUFFER and does the conversion from YCrCb to RGB888
		DMA2D_CopyBuffer((uint32_t *)video.jpegOutDataAdreess, (uint32_t *)output_data, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);

		// Implements the data conversion from RGB888 to RGB565
		doubleFormat pOut;
		pOut.u8Arr = (uint8_t *)output_data;
		depth24To16(&pOut, ( video.width * video.height ), 3, swap);

#ifdef DEBUG_TIME
		uint32_t tempStart = HAL_GetTick();
#endif

		// Display the image
		lcd_draw(video.xPos, video.yPos, video.width, video.height, pOut.u8Arr, swap);

		swap = ( ( swap ) ? 0 : 1 );

#ifdef DEBUG_TIME
		unsigned int bw = 0;
		char buff[50];
		long unsigned int tempStop = HAL_GetTick();
		long unsigned int tempDiff = ( ( tempStop - tempStart ) );
		snprintf(buff, sizeof(buff), "SPI time = %ld\n", tempDiff);
		f_write(&fileToWrite, buff, sizeof(buff), &bw);
#endif

	}

}


static void file_handler(uint8_t openFile)
{

   // Each file takes 1m

   static uint8_t  new_file_flag = 1;


   if(new_file_flag || openFile)
   {

  	 if(openFile)
  		 f_close(&MJPEG_File);

  	 new_file_flag = 0;

  	 char file_idx_str[4];
  	 snprintf(file_idx_str, sizeof(file_idx_str), "%03d", video.file_idx);
  	 snprintf(name, sizeof(name), "a%s.avi", file_idx_str);

  	 // Open the MJPEG avi file with read access
  	 if(f_open(&MJPEG_File, name, FA_READ) == FR_OK)
  	 {

  		 video.isfirstFrame = 1;

  		 // parse the AVI file Header
  		 if(AVI_ParserInit(&AVI_Handel, &MJPEG_File, MJPEG_VideoBuffer, MJPEG_VID_BUFFER_SIZE, MJPEG_AudioBuffer, MJPEG_AUD_BUFFER_SIZE) != 0)
  			 while(1);

  	 }
  	 else
  	 {

  		 while(1);

  	 }

   }

   // Check for the end of the video
   if(AVI_Handel.CurrentImage  >=  AVI_Handel.aviInfo.TotalFrame)
   {

  	 video.file_idx++;
		 video.file_idx %= 720;	// Restart the index every 24 files ( 12h )

		 //  wait for the Last DMA2D transfer to ends
		 HAL_DMA2D_PollForTransfer(&DMA2D_Handle, 50);

		 f_close(&MJPEG_File);

		 new_file_flag = 1;

   }

}


static void parameters_reset(void)
{

	video.width = 0;
	video.height = 0;
	video.xPos = 0;
	video.yPos = 0;

	video.file_idx = 0;
	video.FrameType = 0;

	video.frameToSkip = 0;
	video.frame_time = 0;
	video.actual_time = 0;
	video.tick_offset = 0;
	video.jpegOutDataAdreess = (uint32_t)preElab_data;

	video.display_status = DISPLAY_ON;

	video.frameCount = 0;

	//video.video_mode = NORMAL_MODE;
	video.set = SET_IDLE;

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

  // Configure the DMA2D Mode, Color Mode and output offset
  DMA2D_Handle.Init.Mode         = DMA2D_M2M_PFC;
  DMA2D_Handle.Init.ColorMode    = DMA2D_OUTPUT_RGB888;
  DMA2D_Handle.Init.OutputOffset = LCD_X_SIZE - xsize;
  DMA2D_Handle.Init.AlphaInverted = DMA2D_REGULAR_ALPHA;  // No Output Alpha Inversion
  DMA2D_Handle.Init.RedBlueSwap   = DMA2D_RB_REGULAR;     // No Output Red & Blue swap

  // DMA2D Callbacks Configuration
  DMA2D_Handle.XferCpltCallback  = NULL;

  // Foreground Configuration
  DMA2D_Handle.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
  DMA2D_Handle.LayerCfg[1].InputAlpha = 0xFF;
  DMA2D_Handle.LayerCfg[1].InputColorMode = DMA2D_INPUT_YCBCR;
  DMA2D_Handle.LayerCfg[1].ChromaSubSampling = cssMode;
  DMA2D_Handle.LayerCfg[1].InputOffset = inputLineOffset;
  DMA2D_Handle.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR; 		// No ForeGround Red/Blue swap
  DMA2D_Handle.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA; // No ForeGround Alpha inversion

  DMA2D_Handle.Instance = DMA2D;

  // DMA2D Initialization
  HAL_DMA2D_Init(&DMA2D_Handle);
  HAL_DMA2D_ConfigLayer(&DMA2D_Handle, 1);

}


static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t ImageWidth, uint16_t ImageHeight)
{

  uint32_t xPos, yPos, destination;


  // calculate the destination transfer address
  xPos = (LCD_X_SIZE - JPEG_Info.ImageWidth)/2;
  yPos = (LCD_Y_SIZE - JPEG_Info.ImageHeight)/2;

  destination = (uint32_t)pDst + ((yPos * LCD_X_SIZE) + xPos) * 4;

  // wait for the DMA2D transfer to ends
  HAL_DMA2D_PollForTransfer(&DMA2D_Handle, HAL_MAX_DELAY);
  // copy the new decoded frame to the LCD Frame buffer
  HAL_DMA2D_Start(&DMA2D_Handle, (uint32_t)pSrc, destination, ImageWidth, ImageHeight);

}


static void SD_Initialize(void)
{

  BSP_SD_Init();

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

}

//////////////////////////////////////////////////////////////////////////////////////////
