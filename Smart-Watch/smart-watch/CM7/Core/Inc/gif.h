/*
 * gif.h
 *
 *  Created on: May 6, 2024
 *      Author: Fato
 */

#ifndef GIF_H_
#define GIF_H_


#include <stdint.h>
#include <sys/types.h>
#include "ff.h"


#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))


#define MX_BUF_GIF_RAM						( 128 * 160 )

typedef struct Entry
{

    uint16_t length;
    uint16_t prefix;
    uint8_t  suffix;

}Entry;


typedef struct Table
{

	int bulk;
    int nentries;
    Entry *entries;

}Table;


typedef struct gd_Palette
{

	int size;
    uint8_t colors[0x100 * 3];

}gd_Palette;


typedef struct gd_GCE
{

    uint16_t delay;
    uint8_t tindex;
    uint8_t disposal;
    int transparency;

}gd_GCE;


typedef struct gd_GIF
{

	FIL *fp;
	char *name;
    off_t anim_start;
    uint16_t width, height;
    uint16_t depth;
    uint16_t loop_count;

    gd_GCE gce;
    gd_Palette *palette;
    gd_Palette lct, gct;

    uint16_t fx, fy, fw, fh;
    uint8_t bgindex;
    uint8_t bgcolor;
    uint8_t *frame;

}gd_GIF;


void gif_init(gd_GIF *gif, FIL *fil, char *fName);
void open_gif(gd_GIF *gif);
int getGifFrame(gd_GIF *gif);
void renderGifFrame(gd_GIF *gif, uint8_t *buffer);
void rewindGif(gd_GIF *gif);
void close_gif(gd_GIF *gif);

#endif
