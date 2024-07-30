/*
 * smart_watch.c
 *
 *  Created on: Jul 22, 2024
 *      Author: Fato
 */

#include "main.h"
#include "smart_watch.h"
#include "decode_dma.h"
#include "GC9A01.h"


static void DMA2D_Init(uint16_t xsize, uint16_t ysize, uint32_t ChromaSampling);
static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t ImageWidth, uint16_t ImageHeight);

static void SD_Initialize(void);

static void mjpeg_video_processing(void);
static void file_handler(uint8_t openFile);
static void user_buttons_handler(void);

static void parameters_reset(void);

static void clock_setting(void);
static void clock_normal(void);

static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx);
static void lcd_draw(uint16_t sx, uint16_t sy, uint16_t wd, uint16_t ht, uint8_t *data);
static void show_frame(uint32_t frame_num);


// FATFS can't handle huge files a time,
// so I separated it into multiple video
// of 30 minutes each one
const char *file_name[24];
const char *name;

uint8_t MJPEG_VideoBuffer[MJPEG_VID_BUFFER_SIZE];
uint8_t MJPEG_AudioBuffer[MJPEG_AUD_BUFFER_SIZE];

FATFS SDFatFs;  												// File system object for SD card logical drive
char SDPath[4]; 												// SD card logical drive path

FIL MJPEG_File;          										// MJPEG File object
AVI_CONTEXT AVI_Handel;  										// AVI Parser Handle

video_t video;													// Video data structure


void smart_watch_init(void)
{

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


	parameters_reset();

	// First time setting
	video.video_mode = SETTING_MODE;

	// SD card initialization
	// Link the micro SD disk I/O driver
	if(FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
	{

		// Init the SD Card
	    SD_Initialize();

	    if(BSP_SD_IsDetected(0))
	    {

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
	else
	{

		while(1);

	}

}


void smart_watch_process(void)
{

	// Here there are all the modules

	while(1)
	{

		// Check if new file needs to be open
		file_handler(0);

		// Video processing unit
		mjpeg_video_processing();

		// Check for user buttons pressed
		user_buttons_handler();

	}

}


////////////////////////////////////////////////////// PRIVATE FUNCTIONS


static void mjpeg_video_processing(void)
{

	switch(video.video_mode)
	{

		default:
		case SETTING_MODE:

			clock_setting();

			break;

		case NORMAL_MODE:

			clock_normal();

			break;

	}

}


static void clock_setting(void)
{

	static uint8_t minutes_count = 0;


	switch(video.set)
	{

		default:
		case SET_IDLE:

			while(!HAL_GPIO_ReadPin(BUTTON_SETTING_GPIO_Port, BUTTON_SETTING_Pin));

			video.set = SET_HOURS;

			break;

		case SET_HOURS:

			show_frame(0);

			// If button plus
			if(!HAL_GPIO_ReadPin(BUTTON_PLUS_GPIO_Port, BUTTON_PLUS_Pin))
			{

				HAL_Delay(200);

				video.time.Hours++;
				video.time.Hours %= 12;

				if(video.file_idx % 2)
					video.file_idx += 1;
				else
					video.file_idx += 2;

				video.file_idx %= 24;

				file_handler(1);

			}

			// If button minus
			if(!HAL_GPIO_ReadPin(BUTTON_MINUS_GPIO_Port, BUTTON_MINUS_Pin))
			{

				HAL_Delay(200);

				if(video.time.Hours > 0)
					video.time.Hours--;
				else
					video.time.Hours = 11;

				if(video.file_idx >= 2)
					video.file_idx -= 2;
				else
					video.file_idx = 22;

				file_handler(1);

			}

			// If button settings
			if(!HAL_GPIO_ReadPin(BUTTON_SETTING_GPIO_Port, BUTTON_SETTING_Pin))
			{

				HAL_Delay(200);

				video.set = SET_MINUTES;

			}

			break;

		case SET_MINUTES:

			show_frame(0);

			// If button plus
			if(!HAL_GPIO_ReadPin(BUTTON_PLUS_GPIO_Port, BUTTON_PLUS_Pin))
			{

				HAL_Delay(200);

				video.time.Minutes++;
				video.time.Minutes %= 60;

				minutes_count++;

				if(minutes_count > 29)
				{

					minutes_count = 0;

					video.file_idx += 1;
					video.file_idx %= 24;

					file_handler(1);

				}
				else
				{

					show_frame(1800);

				}

			}

			// If button minus
			if(!HAL_GPIO_ReadPin(BUTTON_MINUS_GPIO_Port, BUTTON_MINUS_Pin))
			{

				HAL_Delay(200);

				if(video.file_idx % 2)
				{

					video.time.Minutes = 30;
					minutes_count = 30;

				}
				else
				{

					video.time.Minutes = 0;
					minutes_count = 0;

				}

				file_handler(1);

			}

			// If button settings
			if(!HAL_GPIO_ReadPin(BUTTON_SETTING_GPIO_Port, BUTTON_SETTING_Pin))
			{

				HAL_Delay(200);

				video.isfirstFrame = 1;

				video.set = SET_START;

			}

			break;

		case SET_START:

			video.set = SET_IDLE;
			video.video_mode = NORMAL_MODE;

			break;

	}

}


static void clock_normal(void)
{

	// Save the frame into MJPEG_VideoBuffer
	video.FrameType = AVI_GetFrame(&AVI_Handel, &MJPEG_File, 0);

	if(video.frameToSkip > 0)
	{

		// Skip frames until the the watch time is
		// synchronized with the actual time

		video.frameToSkip--;
		AVI_Handel.CurrentImage++;

	}
	else if(video.FrameType == AVI_VIDEO_FRAME)
	{

		AVI_Handel.CurrentImage++;

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

			video.frame_time = AVI_Handel.aviInfo.SecPerFrame;

			video.tick_offset = HAL_GetTick();

			video.watch_offset = (uint32_t)( ( AVI_Handel.CurrentImage - 1 ) * ( video.frame_time / 1000.0 ) );

			video.time.Seconds = ( (uint32_t)( ( AVI_Handel.CurrentImage - 1 ) * ( video.frame_time / 1000000.0 ) ) % 60 );
			HAL_RTC_SetTime(&hrtc, &video.time, RTC_FORMAT_BIN);

		}

		// Copies the output frame into LCD_FRAME_BUFFER and does the conversion from YCrCb to RGB888
		DMA2D_CopyBuffer((uint32_t *)video.jpegOutDataAdreess, (uint32_t *)LCD_FRAME_BUFFER, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);

		video.jpegOutDataAdreess = (video.jpegOutDataAdreess == JPEG_OUTPUT_DATA_BUFFER0) ? JPEG_OUTPUT_DATA_BUFFER1 : JPEG_OUTPUT_DATA_BUFFER0;

		// Implements the data conversion from RGB888 to RGB565
		doubleFormat pOut;
		pOut.u8Arr = (uint8_t *)LCD_FRAME_BUFFER;
		depth24To16(&pOut, ( video.width * video.height ), 3);

		// Display the image
		lcd_draw(video.xPos, video.yPos, video.width, video.height, pOut.u8Arr);

		// Obtain the number of frames to skip the next cycle
		video.actual_time = ( HAL_GetTick() - video.tick_offset );
		float watch_time = ( AVI_Handel.CurrentImage * ( video.frame_time / 1000.0 ) - video.watch_offset );
		video.frameToSkip = ( ( video.actual_time - watch_time ) / ( video.frame_time / 1000.0 ) );

		if(video.frameToSkip < 0)
			video.frameToSkip = 0;

	    RTC_DateTypeDef sDate = {0};
	    HAL_RTC_GetTime(&hrtc, &video.time, RTC_FORMAT_BIN);
	    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	}

}


static void show_frame(uint32_t frame_num)
{

	for(int i = 0 ; i < frame_num ; i++)
	{

		AVI_GetFrame(&AVI_Handel, &MJPEG_File, 1);

		AVI_Handel.CurrentImage++;

	}

	for(int i = 0 ; i < 2 ; i++)
	{

		// Save the frame into MJPEG_VideoBuffer
		video.FrameType = AVI_GetFrame(&AVI_Handel, &MJPEG_File, 0);

		if(video.FrameType == AVI_VIDEO_FRAME)
		{

			AVI_Handel.CurrentImage++;

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
				video.xPos = ( ( LCD_X_SIZE - video.width ) / 2 );					// Center the image in x
				video.yPos = ( ( LCD_Y_SIZE - video.height ) / 2 );					// Center the image in y

				video.frame_time = AVI_Handel.aviInfo.SecPerFrame;

			}

			// Copies the output frame into LCD_FRAME_BUFFER and does the conversion from YCrCb to RGB888
			DMA2D_CopyBuffer((uint32_t *)video.jpegOutDataAdreess, (uint32_t *)LCD_FRAME_BUFFER, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);

			video.jpegOutDataAdreess = (video.jpegOutDataAdreess == JPEG_OUTPUT_DATA_BUFFER0) ? JPEG_OUTPUT_DATA_BUFFER1 : JPEG_OUTPUT_DATA_BUFFER0;

			// Implements the data conversion from RGB888 to RGB565
			doubleFormat pOut;
			pOut.u8Arr = (uint8_t *)LCD_FRAME_BUFFER;
			depth24To16(&pOut, ( video.width * video.height ), 3);

			lcd_draw(video.xPos, video.yPos, video.width, video.height, pOut.u8Arr);

		}

	}

}


static void file_handler(uint8_t openFile)
{

	  // Each file takes 30m

     static uint8_t  new_file_flag = 1;


     if(new_file_flag || openFile)
     {

    	 if(openFile)
    		 f_close(&MJPEG_File);

    	 new_file_flag = 0;

    	 name = file_name[video.file_idx];

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
		 video.file_idx %= 24;	// Restart the index every 24 files ( 12h )

		 //  wait for the Last DMA2D transfer to ends
		 HAL_DMA2D_PollForTransfer(&DMA2D_Handle, 50);

		 f_close(&MJPEG_File);

		 parameters_reset();

		 new_file_flag = 1;

     }

}


static void user_buttons_handler(void)
{

	static uint8_t first = 1;
	static uint32_t button_timer = 0;


	// Long press enters in setting mode
	if(!HAL_GPIO_ReadPin(BUTTON_SETTING_GPIO_Port, BUTTON_SETTING_Pin))
	{

		if(first)
		{

			first = 0;
			button_timer = HAL_GetTick();

		}

		if(abs( HAL_GetTick() - button_timer ) >= 3000)
		{

			video.video_mode = SETTING_MODE;
			video.set = SET_IDLE;

		}

	}
	else
	{

		first = 1;

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
	video.jpegOutDataAdreess = JPEG_OUTPUT_DATA_BUFFER0;

	//video.video_mode = NORMAL_MODE;
	video.set = SET_IDLE;

}


static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx)
{

	static uint8_t swap = 0;

	uint8_t b;
	uint8_t g;
	uint8_t r;

	int i = 0;


	// Only half of the frame is handled per time
	// Alternate the top and bottom half every cycle
    if(swap)
    {

    	swap = 0;

    	i = 0;
    	length /= 2;
    	length += 1000;

    }
    else
    {

    	swap = 1;

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

	   static uint8_t swap = 0;
	   struct GC9A01_frame frame;


		// Only half of the frame is handled per time
		// Alternate the top and bottom half every cycle
	   	if(swap)
	   	{

	   		swap = 0;

	        frame.start.X = 0;
	        frame.start.Y = 0;
	        frame.end.X = 239;
	        frame.end.Y = 119;

	   	}
	   	else
	   	{

	   		swap = 1;

	   		data += ( 240 * 240 );

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
	    GC9A01_spi_tx(data, total_bytes);

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

  BSP_SD_Init(0);

}
