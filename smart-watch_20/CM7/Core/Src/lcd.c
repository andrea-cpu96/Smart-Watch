/*
 * lcd.c
 *
 *  Created on: Jun 1, 2024
 *      Author: Fato
 */

#include "main.h"
#include "lcd.h"
#include "bmp.h"

#include "decode_polling.h"

//#include "decode_polling.h"


static void triangle_ex(void);
static void rainbow_ex(void);
static void checkboard_ex(void);
static void swissFlag_ex(void);
static void sd_init(void);
static void sd_error_handler(void);
static void depth24To16(doubleFormat *pxArr, uint16_t length, uint8_t bpx);
static void imageWindowed(doubleFormat *data);
static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize, uint32_t width_offset);


// sd
FATFS SDFatFs;  				// File system object for SD card logical drive
FIL file;          				// MJPEG File object
char fName[] = "image.jpeg";
uint8_t rtext[_MAX_SS];			// File read buffer

// bmp
BMP *bmp;

// lcd
uint8_t color[3];


void lcd_init(void)
{

	GC9A01_init();
	sd_init();

	//JPEG_InitColorTables();
	//bmp_init(bmp, &file, fName, lcd_draw);

}


void lcd_process(void)
{

	// sd_image_demo();
	// lcd_demo();
	jpeg_demo();

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


void jpeg_demo(void)
{

    JPEG_ConfTypeDef JPEG_Info;

    if(f_open(&file, "image.jpg", FA_READ) != FR_OK)
    	while(1);

    uint8_t JPEG_OutputBuffer[240*240*2]; 		// RAW buffer
    uint8_t DECODED_OutputBuffer[240*240*2];	// Decoded buffer

    // Decodifica JPEG
    JPEG_DecodePolling(&hjpeg, &file, (uint32_t)JPEG_OutputBuffer);

    while(!Jpeg_Decoding_End);

    // Ottieni informazioni sull'immagine JPEG
    HAL_JPEG_GetInfo(&hjpeg, &JPEG_Info);

    uint32_t width = JPEG_Info.ImageWidth;
    uint32_t height = JPEG_Info.ImageHeight;

    //DMA2D_CopyBuffer((uint32_t *)JPEG_OutputBuffer, (uint32_t *)DECODED_OutputBuffer, 0, 0, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight, 0);

    lcd_draw(0, 0, width, height, JPEG_OutputBuffer);

}


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


///////////////////////////////////////////////////////// PRIVATE FUNCTIONS


static void triangle_ex(void)
{

	color[0] = 0xFF;
	color[1] = 0xFF;

	for(int x = 0; x < 240; x++)
	{

		for(int y = 0; y < 240; y++)
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

	for(int x = 0; x < 240; x++)
	{

		color[0] = sin(frequency*x + 0) * 127 + 128;
		color[1] = sin(frequency*x + 2) * 127 + 128;
		color[2] = sin(frequency*x + 4) * 127 + 128;
		for(int y = 0; y < 240; y++)
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

	for(int x = 0; x < 240; x++)
	{

		for(int y = 0; y < 240; y++)
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

	for(int x = 0; x < 240; x++)
	{

		for(int y = 0; y < 240; y++)
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

		pxArr->u16Arr[i] = color565(b, r, g);
		//pxArr->u16Arr[i] = ( ( ( pxArr->u16Arr[i] & 0x00ff ) << 8 ) | (( pxArr->u16Arr[i] & 0xff00 ) >> 8) );

	}

}


static void imageWindowed(doubleFormat *data)
{

	uint16_t tmp;


	for(int i = 0 ; i < 240 ; i++)
	{

		for(int j = 0 ; j < 120 ; j++)
		{

			tmp = data->u16Arr[j+(i*240)];
			data->u16Arr[j+(i*240)] = data->u16Arr[(240-1-j)+(i*240)];
			data->u16Arr[(240-1-j)+(i*240)] = tmp;

		}

	}

}


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
static DMA2D_HandleTypeDef    DMA2D_Handle;
static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize, uint32_t width_offset)
{

  uint32_t destination = (uint32_t)pDst;
  uint32_t source      = (uint32_t)pSrc;

  /*##-1- Configure the DMA2D Mode, Color Mode and output offset #############*/
  DMA2D_Handle.Init.Mode          = DMA2D_M2M_PFC;
  DMA2D_Handle.Init.ColorMode     = DMA2D_OUTPUT_RGB565;
  DMA2D_Handle.Init.OutputOffset  = 240 - xsize;
  DMA2D_Handle.Init.AlphaInverted = DMA2D_REGULAR_ALPHA;  /* No Output Alpha Inversion*/
  DMA2D_Handle.Init.RedBlueSwap   = DMA2D_RB_REGULAR;     /* No Output Red & Blue swap */

  /*##-2- DMA2D Callbacks Configuration ######################################*/
  DMA2D_Handle.XferCpltCallback  = NULL;

  /*##-3- Foreground Configuration ###########################################*/
  DMA2D_Handle.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
  DMA2D_Handle.LayerCfg[1].InputAlpha = 0xFF;

#if (JPEG_RGB_FORMAT == JPEG_ARGB8888)
  DMA2D_Handle.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;

#elif (JPEG_RGB_FORMAT == JPEG_RGB888)
  DMA2D_Handle.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB888;

#elif (JPEG_RGB_FORMAT == JPEG_RGB565)
  DMA2D_Handle.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;

#endif /* JPEG_RGB_FORMAT * */


  DMA2D_Handle.LayerCfg[1].InputOffset = width_offset;
  DMA2D_Handle.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */
  DMA2D_Handle.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */

  DMA2D_Handle.Instance          = DMA2D;

  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&DMA2D_Handle) == HAL_OK)
  {
    if(HAL_DMA2D_ConfigLayer(&DMA2D_Handle, 1) == HAL_OK)
    {
      if (HAL_DMA2D_Start(&DMA2D_Handle, source, destination, xsize, ysize) == HAL_OK)
      {
        /* Polling For DMA transfer */
        HAL_DMA2D_PollForTransfer(&DMA2D_Handle, 100);
      }
    }
  }
}
