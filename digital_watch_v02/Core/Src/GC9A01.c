#include "main.h"
#include "GC9A01.h"

#define MAX_ITERATIONS_NUM				1000000


uint8_t volatile spi_dma_not_ready = 0;


//////////////////////////////////////////////// GLOBAL FUNCTIONS


void GC9A01_set_reset(uint8_t val)
{

	uint32_t count_iter = 0;


#ifdef DMA_MODE
	while(spi_dma_not_ready)
	{

		count_iter++;

		if(count_iter >= MAX_ITERATIONS_NUM)
			break;

	}
#endif

	if(val==0)
    	HAL_GPIO_WritePin(GC9A01_RST_GPIO_Port, GC9A01_RST_Pin, RESET);
    else
        HAL_GPIO_WritePin(GC9A01_RST_GPIO_Port, GC9A01_RST_Pin, SET);

}

void GC9A01_set_data_command(uint8_t val)
{

	uint32_t count_iter = 0;

#ifdef DMA_MODE
	while(spi_dma_not_ready)
	{

		count_iter++;

		if(count_iter >= MAX_ITERATIONS_NUM)
			break;

	}
#endif

	if(val==0)
    	HAL_GPIO_WritePin(GC9A01_DC_GPIO_Port, GC9A01_DC_Pin, RESET);
    else
        HAL_GPIO_WritePin(GC9A01_DC_GPIO_Port, GC9A01_DC_Pin, SET);

}

void GC9A01_set_chip_select(uint8_t val)
{

	uint32_t count_iter = 0;


#ifdef DMA_MODE
	while(spi_dma_not_ready)
	{

		count_iter++;

		if(count_iter >= MAX_ITERATIONS_NUM)
			break;

	}
#endif

    if (val==0)
    	HAL_GPIO_WritePin(GC9A01_CS_GPIO_Port, GC9A01_CS_Pin, RESET);
    else
    	HAL_GPIO_WritePin(GC9A01_CS_GPIO_Port, GC9A01_CS_Pin, SET);

}

int GC9A01_write_command(uint8_t cmd)
{

	int ret = 1;


    GC9A01_set_data_command(OFF);
    GC9A01_set_chip_select(OFF);
    ret = GC9A01_spi_tx(&cmd, sizeof(cmd), 0);
    GC9A01_set_chip_select(ON);

    return ret;

}

int GC9A01_write_data(uint8_t *data, size_t len)
{

	int ret;


    GC9A01_set_data_command(ON);
    GC9A01_set_chip_select(OFF);
    ret = GC9A01_spi_tx(data, len, 0);
    GC9A01_set_chip_select(ON);

    return ret;

}

static inline int GC9A01_write_byte(uint8_t val)
{

    return GC9A01_write_data(&val, sizeof(val));

}

int GC9A01_write(uint8_t *data, size_t len)
{

	if(GC9A01_write_command(MEM_WR) != 1)
		return -1;
    if(GC9A01_write_data(data, len) != 1)
    	return -1;

    return 1;

}

int GC9A01_write_continue(uint8_t *data, size_t len)
{

    if(GC9A01_write_command(MEM_WR_CONT) != 1)
    	return -1;
    if(GC9A01_write_data(data, len) != 1)
    	return -1;

    return 1;

}

void GC9A01_init(void) {
    
    GC9A01_set_chip_select(ON);
    HAL_Delay(5);
    GC9A01_set_reset(OFF);
    HAL_Delay(10);
    GC9A01_set_reset(ON);
    HAL_Delay(120);
    
    /* Initial Sequence */ 
    
    GC9A01_write_command(0xEF);
    
    GC9A01_write_command(0xEB);
    GC9A01_write_byte(0x14);
    
    GC9A01_write_command(0xFE);
    GC9A01_write_command(0xEF);
    
    GC9A01_write_command(0xEB);
    GC9A01_write_byte(0x14);
    
    GC9A01_write_command(0x84);
    GC9A01_write_byte(0x40);
    
    GC9A01_write_command(0x85);
    GC9A01_write_byte(0xFF);
    
    GC9A01_write_command(0x86);
    GC9A01_write_byte(0xFF);
    
    GC9A01_write_command(0x87);
    GC9A01_write_byte(0xFF);
    
    GC9A01_write_command(0x88);
    GC9A01_write_byte(0x0A);
    
    GC9A01_write_command(0x89);
    GC9A01_write_byte(0x21);
    
    GC9A01_write_command(0x8A);
    GC9A01_write_byte(0x00);
    
    GC9A01_write_command(0x8B);
    GC9A01_write_byte(0x80);
    
    GC9A01_write_command(0x8C);
    GC9A01_write_byte(0x01);
    
    GC9A01_write_command(0x8D);
    GC9A01_write_byte(0x01);
    
    GC9A01_write_command(0x8E);
    GC9A01_write_byte(0xFF);
    
    GC9A01_write_command(0x8F);
    GC9A01_write_byte(0xFF);
    
    
    GC9A01_write_command(0xB6);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    
    GC9A01_write_command(0x36);
    
#if ORIENTATION == 0
    GC9A01_write_byte(0x18);
#elif ORIENTATION == 1
    GC9A01_write_byte(0x28);
#elif ORIENTATION == 2
    GC9A01_write_byte(0x48);
#else
    GC9A01_write_byte(0x88);
#endif
    
    GC9A01_write_command(COLOR_MODE);
    GC9A01_write_byte(COLOR_MODE__16_BIT);
    
    GC9A01_write_command(0x90);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    
    GC9A01_write_command(0xBD);
    GC9A01_write_byte(0x06);
    
    GC9A01_write_command(0xBC);
    GC9A01_write_byte(0x00);
    
    GC9A01_write_command(0xFF);
    GC9A01_write_byte(0x60);
    GC9A01_write_byte(0x01);
    GC9A01_write_byte(0x04);
    
    GC9A01_write_command(0xC3);
    GC9A01_write_byte(0x13);
    GC9A01_write_command(0xC4);
    GC9A01_write_byte(0x13);
    
    GC9A01_write_command(0xC9);
    GC9A01_write_byte(0x22);
    
    GC9A01_write_command(0xBE);
    GC9A01_write_byte(0x11);
    
    GC9A01_write_command(0xE1);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x0E);
    
    GC9A01_write_command(0xDF);
    GC9A01_write_byte(0x21);
    GC9A01_write_byte(0x0c);
    GC9A01_write_byte(0x02);
    
    GC9A01_write_command(0xF0);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x09);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x26);
    GC9A01_write_byte(0x2A);
    
    GC9A01_write_command(0xF1);
    GC9A01_write_byte(0x43);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x72);
    GC9A01_write_byte(0x36);
    GC9A01_write_byte(0x37);
    GC9A01_write_byte(0x6F);
    
    GC9A01_write_command(0xF2);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x09);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x26);
    GC9A01_write_byte(0x2A);
    
    GC9A01_write_command(0xF3);
    GC9A01_write_byte(0x43);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x72);
    GC9A01_write_byte(0x36);
    GC9A01_write_byte(0x37);
    GC9A01_write_byte(0x6F);
    
    GC9A01_write_command(0xED);
    GC9A01_write_byte(0x1B);
    GC9A01_write_byte(0x0B);
    
    GC9A01_write_command(0xAE);
    GC9A01_write_byte(0x77);
    
    GC9A01_write_command(0xCD);
    GC9A01_write_byte(0x63);
    
    GC9A01_write_command(0x70);
    GC9A01_write_byte(0x07);
    GC9A01_write_byte(0x07);
    GC9A01_write_byte(0x04);
    GC9A01_write_byte(0x0E);
    GC9A01_write_byte(0x0F);
    GC9A01_write_byte(0x09);
    GC9A01_write_byte(0x07);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x03);
    
    GC9A01_write_command(0xE8);
    GC9A01_write_byte(0x34);
    
    GC9A01_write_command(0x62);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x0D);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xED);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x0F);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xEF);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);
    
    GC9A01_write_command(0x63);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x11);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xF1);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x13);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xF3);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);
    
    GC9A01_write_command(0x64);
    GC9A01_write_byte(0x28);
    GC9A01_write_byte(0x29);
    GC9A01_write_byte(0xF1);
    GC9A01_write_byte(0x01);
    GC9A01_write_byte(0xF1);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x07);
    
    GC9A01_write_command(0x66);
    GC9A01_write_byte(0x3C);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0xCD);
    GC9A01_write_byte(0x67);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    
    GC9A01_write_command(0x67);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x3C);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x01);
    GC9A01_write_byte(0x54);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x32);
    GC9A01_write_byte(0x98);
    
    GC9A01_write_command(0x74);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x85);
    GC9A01_write_byte(0x80);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x4E);
    GC9A01_write_byte(0x00);
    
    GC9A01_write_command(0x98);
    GC9A01_write_byte(0x3e);
    GC9A01_write_byte(0x07);
    
    GC9A01_write_command(0x35);
    GC9A01_write_command(0x21);
    
    GC9A01_write_command(0x11);
    HAL_Delay(120);
    GC9A01_write_command(0x29);
    HAL_Delay(20);
    
}

int GC9A01_set_frame(struct GC9A01_frame frame)
{

    uint8_t data[4];
    

    if(GC9A01_write_command(COL_ADDR_SET) != 1)
    	return -1;

    data[0] = (frame.start.X >> 8) & 0xFF;
    data[1] = frame.start.X & 0xFF;
    data[2] = (frame.end.X >> 8) & 0xFF;
    data[3] = frame.end.X & 0xFF;

    if(GC9A01_write_data(data, sizeof(data)) != 1)
    	return -1;

    if(GC9A01_write_command(ROW_ADDR_SET) != 1)
    	return -1;

    data[0] = (frame.start.Y >> 8) & 0xFF;
    data[1] = frame.start.Y & 0xFF;
    data[2] = (frame.end.Y >> 8) & 0xFF;
    data[3] = frame.end.Y & 0xFF;
    
    if(GC9A01_write_data(data, sizeof(data)) != 1)
    	return -1;

    return 1;

}


int GC9A01_sleep_mode(uint8_t command)
{

	int ret;


	if(command)
		ret = GC9A01_write_command(SLEEP_MODE_ON);
	else
		ret = GC9A01_write_command(SLEEP_MODE_OFF);

	HAL_Delay(120);

	return ret;

}

//////////////////////////////////////////////// PRIVATE FUNCTIONS

int GC9A01_spi_tx(uint8_t *data, uint16_t size, uint8_t join)
{

	HAL_StatusTypeDef ret;
	static uint32_t count_iter = 0;


#ifdef DMA_MODE
	while(spi_dma_not_ready && !join)
	{

		count_iter++;

		if(count_iter >= MAX_ITERATIONS_NUM)
			return -1;

	}

	count_iter = 0;

	spi_dma_not_ready = 1;
	ret = HAL_SPI_Transmit_DMA(&hspi1, data, size);

#else
	ret = HAL_SPI_Transmit(&hspi1, data, size, HAL_MAX_DELAY);
#endif

	if(ret != HAL_OK)
		return -1;

	return 1;

}


////////////////////////////////////////////////
