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

/************************** PRIVATE FUNCTIONS PROTOTPYES **************************/

static void DMA2D_Init(uint16_t xsize, uint16_t ysize, uint32_t ChromaSampling);
static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t ImageWidth, uint16_t ImageHeight);

static void SD_Initialize(void);

static void parameters_reset(void);

static void mjpeg_video_processing(void);
static void file_handler(uint8_t openFile);

static void battery_management(void);

static void clock_setting(void);
static void clock_normal(void);

static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx);
static void show_frame(uint32_t frame_num);

#ifdef DEBUG_TIME
FIL fileToWrite;
#endif

/************************** GLOBAL VARIABLES **************************/

char name[14];													// File name

FATFS SDFatFs;  												// File system object for SD card logical drive
FIL MJPEG_File;          										// MJPEG File object
AVI_CONTEXT AVI_Handel;  										// AVI Parser Handle

uint8_t MJPEG_VideoBuffer[MJPEG_VID_BUFFER_SIZE];
uint8_t MJPEG_AudioBuffer[MJPEG_AUD_BUFFER_SIZE];

video_t video;													// Video data structure

uint8_t	preElab_data[300*1024];									// Pre elaborated data buffer
uint8_t output_data1[200*1024];									// Output data buffer (format RGB565)
uint8_t output_data2[200*1024];
uint8_t *outputData = output_data1;

/************************** GLOBAL FUNCTIONS **************************/

void smart_watch_init(void)
{

	parameters_reset();


	for(int i = 0 ; i < 200*1024 ; i++)
	{

		output_data1[i] = 0x00;
		output_data2[i] = 0xff;

	}
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

		battery_management();

#ifdef DEBUG_TIME
		count++;
		if(count > 100)
			f_close(&fileToWrite);
#endif

	}

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


int lcd_draw_opt(uint16_t sx, uint16_t sy, uint16_t wd, uint16_t ht, uint8_t *data)
{

	   struct GC9A01_frame frame;
	   static uint16_t full_update = 0;
	   int ret = 0;

       frame.start.X = 0;
       frame.start.Y = 0;
       frame.end.X = 0;
       frame.end.Y = 0;

       uint16_t *data16 = (uint16_t *)data;
       uint16_t *buff16o1 = (uint16_t *)output_data1;
       uint16_t *buff16o2 = (uint16_t *)output_data2;

       uint16_t block_to_send[PX_PER_BLOCK_X*PX_PER_BLOCK_Y] = {0};

       uint8_t update_flag = 1;
       uint8_t equal_count = 0;

       uint32_t chunk_idx = 0;
       uint32_t block_idx = 0;
       uint32_t px_y_idx = 0;
       uint32_t idx = 0;

       uint8_t spare_flag = 0;


       if(full_update == 0)
       {


    	   ret = lcd_draw(sx, sy, wd, ht, data, 0);
    	   ret |= lcd_draw(sx, sy, wd, ht, data, 1);

    	   full_update = ( ( full_update + 1 ) % FULL_UPDATE_PERIOD );

    	   return ret;

       }

       full_update = ( ( full_update + 1 ) % FULL_UPDATE_PERIOD );

       for(int i = 0 ; i < CHUNKS_NUM ; i++)
       {

    	   chunk_idx = ( i * PX_PER_BLOCK_X * 240 );

    	   for(int j = 0 ; j < BLOCKS_PER_CHUNK ; j++)
    	   {

    		   block_idx = ( j * PX_PER_BLOCK_X );

   	    	   frame.start.X = ( j * PX_PER_BLOCK_X );
   	    	   frame.start.Y = ( i * PX_PER_BLOCK_Y );
   	    	   frame.end.X = ( frame.start.X + PX_PER_BLOCK_X - 1 );
    	       frame.end.Y = ( frame.start.Y + PX_PER_BLOCK_Y - 1 );

    		   for(int h = 0 ; h < PX_PER_BLOCK_Y ; h++)
    		   {

    			   px_y_idx = ( h * 240 );

   				   for(int z = 0 ; z < PX_PER_BLOCK_X ; z++)
   				   {

   					   idx = ( chunk_idx + block_idx + px_y_idx + z);

   					   block_to_send[(h*PX_PER_BLOCK_X)+z] = data16[idx];

   					   // Check if we are close to the boundaries
   	        	       if(( frame.start.X <= BORDER_START ) || ( frame.start.Y <= BORDER_START )
   	        	    		|| ( frame.end.X >= (PX_IN_A_RAW - BORDER_END ) ) || ( frame.end.Y >= ( PX_IN_A_RAW - BORDER_END ) ) )
   	        	       {

   	        	    	   // We are close to the boundaries

   	        	    	   // Always update here
   	        	    	   update_flag = 1;
   	        	    	   continue;

   	        	       }

   					   if(( spare_flag == 0 ) && ( buff16o1[idx] == buff16o2[idx] ))
   					   {

   						   equal_count++;

   						   if(equal_count >= MAX_EQU_NUM)
   						   {

   							   update_flag = 0;
   							   break;

   						   }

   					   }

   					   spare_flag = ( ( spare_flag + 1 ) % SPARE_DIV_FACT );

   				   }

   				   if(update_flag == 0)
   					   break;

    		   }

    		   if(update_flag)
    		   {

    			   GC9A01_set_frame(frame);
    			   GC9A01_write_command(MEM_WR);

    			   GC9A01_set_data_command(ON);
    			   GC9A01_set_chip_select(OFF);

    			   uint32_t total_bytes = ( BLOCK_SIZE * 2 );		// 2 byte per pixel
    			   ret = GC9A01_spi_tx((uint8_t *)block_to_send, total_bytes);

    			   GC9A01_set_chip_select(ON);

    		   }

    		   equal_count = 0;
    		   update_flag = 1;

    	   }

       }

	   return ret;

}


// TEST FUNCTIONS //

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

			}

			// Copies the output frame into LCD_FRAME_BUFFER and does the conversion from YCrCb to RGB888
			DMA2D_CopyBuffer((uint32_t *)video.jpegOutDataAdreess, (uint32_t *)outputData, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);

			doubleFormat pOut;
			pOut.u8Arr = (uint8_t *)outputData;

			tempStart = HAL_GetTick();

			depth24To16(&pOut, ( video.width * video.height ), 3);

			tempStop = HAL_GetTick();
			tempDiff[0] = ( ( tempStop - tempStart ) );

			if(lcd_draw(video.xPos, video.yPos, video.width, video.height, pOut.u8Arr, swap) < 0)
			{

				f_close(&MJPEG_File);

				return -1;

			}

			swap = ( ( swap ) ? 0 : 1 );
			outputData = ( outputData == output_data1 ) ? output_data2 : output_data1;

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

/************************** PRIVATE FUNCTIONS **************************/

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

static void clock_normal(void)
{

#ifdef DEBUG_TIME
	static uint8_t swap = 0;
#endif


	// Save the frame into MJPEG_VideoBuffer
	video.FrameType = AVI_GetFrame(&AVI_Handel, &MJPEG_File, 0);

	if(video.frameToSkip > 0)
	{

		// Skip frames until the the watch time is
		// synchronized with the actual time

		video.frameToSkip--;
		AVI_Handel.CurrentImage++;
		video.frameCount++;

	}
	else if(video.FrameType == AVI_VIDEO_FRAME)
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

			video.frame_time = ( AVI_Handel.aviInfo.SecPerFrame / 1000.0 );
			video.tick_offset = HAL_GetTick();									// Tick offset from 0

			video.frameCount = 1;												// Reset the count here for every first frame of the minute chunk

			HAL_RTC_SetTime(&hrtc, &video.time, RTC_FORMAT_BIN);

		}

		// Copies the output frame into LCD_FRAME_BUFFER and does the conversion from YCrCb to RGB888
		DMA2D_CopyBuffer((uint32_t *)video.jpegOutDataAdreess, (uint32_t *)outputData, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);

		// Implements the data conversion from RGB888 to RGB565
		doubleFormat pOut;
		pOut.u8Arr = (uint8_t *)outputData;

		depth24To16(&pOut, ( video.width * video.height ), 3);

#ifdef DEBUG_TIME
		uint32_t tempStart = HAL_GetTick();
#endif

		// Display the image
		lcd_draw_opt(video.xPos, video.yPos, video.width, video.height, pOut.u8Arr);

#ifdef  NOTOPT
		lcd_draw(video.xPos, video.yPos, video.width, video.height, swap);
		swap = ( ( swap ) ? 0 : 1 );
#endif

		outputData = ( outputData == output_data1 ) ? output_data2 : output_data1;

#ifdef DEBUG_TIME
		unsigned int bw = 0;
		char buff[50];
		long unsigned int tempStop = HAL_GetTick();
		long unsigned int tempDiff = ( ( tempStop - tempStart ) );
		snprintf(buff, sizeof(buff), "SPI time = %ld\n", tempDiff);
		f_write(&fileToWrite, buff, sizeof(buff), &bw);
#endif


/************************* Synchronization ************************/

		video.actual_time = ( HAL_GetTick() - video.tick_offset );
		float watch_time = ( video.frameCount * video.frame_time );
		video.frameToSkip = ( ( video.actual_time - watch_time ) / video.frame_time );

		if(video.frameToSkip < 0)
			video.frameToSkip = 0;

/******************************************************************/

		RTC_DateTypeDef sDate = {0};
		HAL_RTC_GetTime(&hrtc, &video.time, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	}

}

static void clock_setting(void)
{

	switch(video.set)
	{

		default:
		case SET_IDLE:

			while(!HAL_GPIO_ReadPin(SET_BTN_GPIO_Port, SET_BTN_Pin));

			video.set = SET_HOURS;

			break;

		case SET_HOURS:

			show_frame(0);

			// If button plus
			if(!HAL_GPIO_ReadPin(PLUS_BTN_GPIO_Port, PLUS_BTN_Pin))
			{

				HAL_Delay(100);

				video.time.Hours++;
				video.time.Hours %= 12;

				video.file_idx = ( video.time.Hours * 60 );

				file_handler(1);

			}

			// If button minus
			if(!HAL_GPIO_ReadPin(MINUS_BTN_GPIO_Port, MINUS_BTN_Pin))
			{

				HAL_Delay(100);

				if(video.time.Hours > 0)
					video.time.Hours--;
				else
					video.time.Hours = 11;

				video.file_idx = ( video.time.Hours * 60 );

				file_handler(1);

			}

			// If button settings
			if(!HAL_GPIO_ReadPin(SET_BTN_GPIO_Port, SET_BTN_Pin))
			{

				HAL_Delay(100);

				video.set = SET_MINUTES;

			}

			break;

		case SET_MINUTES:

			show_frame(0);

			// If button plus
			if(!HAL_GPIO_ReadPin(PLUS_BTN_GPIO_Port, PLUS_BTN_Pin))
			{

				HAL_Delay(100);

				video.time.Minutes++;
				video.time.Minutes %= 60;

				video.file_idx += video.time.Minutes;

				file_handler(1);

				video.file_idx -= video.time.Minutes;


			}

			// If button minus
			if(!HAL_GPIO_ReadPin(MINUS_BTN_GPIO_Port, MINUS_BTN_Pin))
			{

				HAL_Delay(100);

				if(video.time.Minutes > 0)
					video.time.Minutes--;
				else
					video.time.Minutes = 59;

				video.file_idx += video.time.Minutes;

				file_handler(1);

				video.file_idx -= video.time.Minutes;

			}

			// If button settings
			if(!HAL_GPIO_ReadPin(SET_BTN_GPIO_Port, SET_BTN_Pin))
			{

				HAL_Delay(100);

				video.file_idx += video.time.Minutes;

				video.isfirstFrame = 1;

				video.set = SET_START;

			}

			break;

		case SET_START:

			file_handler(1);							// Start froma the first frame

			video.set = SET_IDLE;
			video.video_mode = NORMAL_MODE;

			break;

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

static void battery_management(void)
{


	if(video.display_status == DISPLAY_ON)
	{

		if(video.time.Seconds >= DISPLAY_STANDBY_TIMER)
		{

			parameters_reset();

			GC9A01_sleep_mode(ON);
			video.display_status = DISPLAY_OFF;

			// Stop mode

			HAL_SuspendTick();

			__disable_irq();

			HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

			// Wake up

			__enable_irq();

			HAL_ResumeTick();

			SystemClock_Config();

			GC9A01_init();
			video.display_status = DISPLAY_ON;

			// Clock setting

			RTC_DateTypeDef sDate = {0};
			HAL_RTC_GetTime(&hrtc, &video.time, RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

			video.file_idx = ( ( video.time.Hours % 12 ) * 60 );
			video.file_idx += video.time.Minutes;

			file_handler(1);

			video.display_ts = video.time.Seconds;

		}

	}

}

static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx)
{

	uint8_t b;
	uint8_t g;
	uint8_t r;

	int i = 0;


	for( ; i < length ; i++)
	{

		b = pxArr->u8Arr[i*bpx];
		g = pxArr->u8Arr[i*bpx+1];
		r = pxArr->u8Arr[i*bpx+2];

		pxArr->u16Arr[i] = color565(r, g, b);
		pxArr->u16Arr[i] = ( ( ( pxArr->u16Arr[i] & 0x00ff ) << 8 ) | (( pxArr->u16Arr[i] & 0xff00 ) >> 8) );

	}

}

static void show_frame(uint32_t frame_num)
{

	static uint8_t swap = 0;


	for(int i = 0 ; i < frame_num ; i++)
	{

		AVI_GetFrame(&AVI_Handel, &MJPEG_File, 1);

		AVI_Handel.CurrentImage++;
		video.frameCount++;

	}

	for(int i = 0 ; i < 2 ; i++)
	{

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
				video.xPos = ( ( LCD_X_SIZE - video.width ) / 2 );					// Center the image in x
				video.yPos = ( ( LCD_Y_SIZE - video.height ) / 2 );					// Center the image in y

			}

			// Copies the output frame into LCD_FRAME_BUFFER and does the conversion from YCrCb to RGB888
			DMA2D_CopyBuffer((uint32_t *)video.jpegOutDataAdreess, (uint32_t *)outputData, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);

			//video.jpegOutDataAdreess = (video.jpegOutDataAdreess == JPEG_OUTPUT_DATA_BUFFER0) ? JPEG_OUTPUT_DATA_BUFFER1 : JPEG_OUTPUT_DATA_BUFFER0;

			// Implements the data conversion from RGB888 to RGB565
			doubleFormat pOut;
			pOut.u8Arr = (uint8_t *)outputData;
			depth24To16(&pOut, ( video.width * video.height ), 3);

			lcd_draw(video.xPos, video.yPos, video.width, video.height, pOut.u8Arr, swap);

			swap = ( ( swap ) ? 0 : 1 );
			outputData = ( outputData == output_data1 ) ? output_data2 : output_data1;

		}

	}

}

static void parameters_reset(void)
{

	video.width = 0;
	video.height = 0;
	video.xPos = 0;
	video.yPos = 0;

	video.time.Hours = 0;
	video.time.Minutes = 0;
	video.time.Seconds = 0;

	video.file_idx = 0;
	video.FrameType = 0;

	video.frameToSkip = 0;
	video.frame_time = 0.0;
	video.actual_time = 0;
	video.tick_offset = 0;
	video.jpegOutDataAdreess = (uint32_t)preElab_data;

	video.display_ts = video.time.Seconds;

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

/************************** CALLBACK FUNCTIONS **************************/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

}

//////////////////////////////////////////////////////////////////////////////////////////
