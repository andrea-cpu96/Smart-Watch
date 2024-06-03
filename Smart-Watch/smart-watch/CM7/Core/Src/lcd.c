/*
 * lcd.c
 *
 *  Created on: Jun 1, 2024
 *      Author: Fato
 */

#include "main.h"
#include "lcd.h"


static void triangle_ex(void);
static void rainbow_ex(void);
static void checkboard_ex(void);
static void swissFlag_ex(void);


uint8_t color[3];


void lcd_init(void)
{

	GC9A01_init();

}


void lcd_process(void)
{

	lcd_demo();

}


void lcd_demo(void)
{

    // Triangle //

	triangle_ex();

    //setPWM(1);

    HAL_Delay(1000);

    // setPWM(0);

    // Rainbow //

    rainbow_ex();

    // setPWM(1);

    HAL_Delay(1000);

    // setPWM(0);

    // Checkerboard //

    checkboard_ex();

    // setPWM(1);

    HAL_Delay(1000);

    // setPWM(0);

    // Swiss flag //

    swissFlag_ex();

    // setPWM(1);

    GC9A01_write_command(0x20);

    HAL_Delay(1000);

    // setPWM(0);

}


/****************************************** PRIVATE FUNCTIONS */




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
