#ifndef __GC9A01_H
#define __GC9A01_H

#include <stdint.h>
#include <stddef.h>

#define DMA_MODE // When defined, it enables the DMA mode for the SPI data communication

#define ORIENTATION 0   // Set the display orientation 0,1,2,3

// Command codes:
#define COL_ADDR_SET        0x2A
#define ROW_ADDR_SET        0x2B
#define MEM_WR              0x2C
#define COLOR_MODE          0x3A
#define COLOR_MODE__12_BIT  0x03
#define COLOR_MODE__16_BIT  0x05
#define COLOR_MODE__18_BIT  0x06
#define MEM_WR_CONT         0x3C
#define ON                  1
#define OFF                 0

#define SLEEP_MODE_ON		0x10
#define SLEEP_MODE_OFF		0x11

extern uint8_t volatile spi_dma_not_ready;

struct GC9A01_point {
    uint16_t X, Y;
};

struct GC9A01_frame {
    struct GC9A01_point start, end;
};

void GC9A01_init(void);
int GC9A01_set_frame(struct GC9A01_frame frame);
int GC9A01_write(uint8_t *data, size_t len);
int GC9A01_write_continue(uint8_t *data, size_t len);

int GC9A01_write_data(uint8_t *data, size_t len);
int GC9A01_write_command(uint8_t cmd);
int GC9A01_spi_tx(uint8_t *data, uint16_t size, uint8_t join);

void GC9A01_set_reset(uint8_t val);
void GC9A01_set_data_command(uint8_t val);
void GC9A01_set_chip_select(uint8_t val);

int GC9A01_sleep_mode(uint8_t command);

#endif
