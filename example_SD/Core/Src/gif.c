/*
 * gif.c
 *
 *  Created on: May 6, 2024
 *      Author: Fato
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "sd_ex.h"
#include "gif.h"



// read function support offset - top file
off_t offset_Gif = 0;

void read_Gif_Blocks(gd_GIF *imageGif, void *buf, size_t nbytes)
{

	UINT cnt;
	FRESULT fres;


    fres = f_read(imageGif->fp, buf, nbytes, &cnt);

    if(fres!=FR_OK)
    	ferror_handler(ERROR_READ_FILE);

    if(cnt!=nbytes)
    	ferror_handler(ERROR_READ_FEW_DATA);

    offset_Gif += cnt;

}


static off_t get_Gif_CurrPos(gd_GIF *imageGif)
{

    return offset_Gif;

}


static uint16_t read_num(gd_GIF *imageGif)
{

    uint8_t bytes[2];


    read_Gif_Blocks(imageGif, bytes, 2);

    return bytes[0] + (((uint16_t) bytes[1]) << 8);

}


void gif_init(gd_GIF *gif, FIL *fil, char *fName, const void (*drawFunc))
{

	gif->fp = fil;
	gif->name = fName;
	gif->draw = drawFunc;

	open_gif(gif);

}


void open_gif(gd_GIF *gif)
{

	FRESULT fres;
    uint8_t sigver[3];
    uint16_t width, height, depth;
    uint8_t fdsz, bgidx, aspect;
    int gct_sz;

	uint8_t bufRam[MX_BUF_GIF_RAM];


    fres = f_open(gif->fp, gif->name, FA_READ);

    if(fres!=FR_OK)
    	ferror_handler(ERROR_OPEN);

    /* Header */
    read_Gif_Blocks(gif, sigver, 3);

    if(memcmp(sigver, "GIF", 3) != 0)
    	ferror_handler(ERROR_GIF_HEADER);

    /* Version */
    read_Gif_Blocks(gif, sigver, 3);

    if(memcmp(sigver, "89a", 3) != 0)
    	ferror_handler(ERROR_GIF_VERSION);

    /* Width x Height */
    width  = read_num(gif);
    height = read_num(gif);

    /* FDSZ */
    read_Gif_Blocks(gif, &fdsz, 1);

    /* Presence of GCT */
    if(!(fdsz & 0x80))
    	ferror_handler(ERROR_GIF_GCT);

    /* Color Space's Depth */
    depth = ((fdsz >> 4) & 7) + 1;

    /* Ignore Sort Flag. */

    /* GCT Size */
    gct_sz = 1 << ((fdsz & 0x07) + 1);
    gif->gct.size = gct_sz;

    /* Background Color Index */
    read_Gif_Blocks(gif, &bgidx, 1);

    /* Aspect Ratio */
    read_Gif_Blocks(gif, &aspect, 1);

    gif->width  = width;
    gif->height = height;
    gif->depth  = depth;    // not used
    gif->bgindex = bgidx;

    /* Read GCT */
    read_Gif_Blocks(gif, gif->gct.colors, 3 * gif->gct.size);
    gif->palette = &gif->gct;
    gif->bgcolor = gif->palette->colors[gif->bgindex*3];

    gif->frame = bufRam;

    if (gif->bgindex)
        memset(gif->frame, gif->bgcolor, gif->width * gif->height); // render background

    gif->anim_start = get_Gif_CurrPos(gif);

}


void close_gif(gd_GIF *gif)
{

    f_close(gif->fp);
    free(gif->frame);

}


static void skip_sub_blocks(gd_GIF *gif)
{

    uint8_t size;
    uint8_t buff;
    int cnt;


    do
    {

        read_Gif_Blocks(gif, &size, 1);

        for(cnt = 0; cnt<size; cnt++)
            read_Gif_Blocks(gif, &buff, 1);

    }while(size);

}


static void read_plain_text_ext(gd_GIF *gif)
{

    uint8_t buff[13];


    read_Gif_Blocks(gif, &buff, 13);
    skip_sub_blocks(gif);

}


static void read_graphic_control_ext(gd_GIF *gif)
{

    uint8_t buff[2];


    read_Gif_Blocks(gif, &buff[0], 2);

    gif->gce.disposal = (buff[1] >> 2) & 3;
    gif->gce.transparency = buff[1] & 1;
    gif->gce.delay = read_num(gif);

    read_Gif_Blocks(gif, &buff[0], 2); // Clear code number; // Discard: tr[1], '0x00'
    gif->gce.tindex = buff[0];

}


static void read_comment_ext(gd_GIF *gif)
{

    skip_sub_blocks(gif);

}


static void read_application_ext(gd_GIF *gif)
{

    char app_id[8];
    char app_auth_code[3];
    uint8_t buff[2];


    /* Discard block size (always 0x0B). */
    read_Gif_Blocks(gif, &buff, 1);

    /* Application Identifier. */
    read_Gif_Blocks(gif, app_id, 8);

    /* Application Authentication Code. */
    read_Gif_Blocks(gif, app_auth_code, 3);

    if(strncmp(app_id, "NETSCAPE", sizeof(app_id)))
    {

        /* Discard block size (0x03) and constant byte (0x01). */
        read_Gif_Blocks(gif, &buff, 2);
        gif->loop_count = read_num(gif);

        /* Skip block terminator. */
        read_Gif_Blocks(gif, &buff, 1);

    }
    else
    {

        skip_sub_blocks(gif);

    }

}


static void read_ext(gd_GIF *gif)
{

    uint8_t label;


    read_Gif_Blocks(gif, &label, 1);

    switch(label)
    {

    case 0x01:

        read_plain_text_ext(gif);

        break;

    case 0xF9:

        read_graphic_control_ext(gif);

        break;

    case 0xFE:

        read_comment_ext(gif);

        break;

    case 0xFF:

        read_application_ext(gif);

        break;

    default:

        ferror_handler(ERROR_GENERIC);

    }

}


static Table *new_table(int key_size)
{

    int key;


    int init_bulk = MAX(1 << (key_size + 1), 0x100);

    Table *table = malloc(sizeof(*table) + sizeof(Entry) * init_bulk);
    if (table)
    {

        table->bulk = init_bulk;
        table->nentries = (1 << key_size) + 2;
        table->entries = (Entry *) &table[1];

        for (key = 0; key < (1 << key_size); key++)
            table->entries[key] = (Entry) {1, 0xFFF, key};

    }
    else
    {

    	ferror_handler(ERROR_GIF_TABLE);

    }

    return table;

}


/* Add table entry. Return value:
 *  0 on success
 *  +1 if key size must be incremented after this addition
 *  -1 if could not realloc table */
static int add_entry(Table **tablep, uint16_t length, uint16_t prefix, uint8_t suffix)
{

    Table *table = *tablep;


    if (table->nentries == table->bulk)
    {

        table->bulk *= 2;
        table = realloc(table, sizeof(*table) + sizeof(Entry) * table->bulk);
        if (!table)
        {

        	return -1;

        }

        table->entries = (Entry *) &table[1];
        *tablep = table;

    }

    table->entries[table->nentries] = (Entry) {length, prefix, suffix};
    table->nentries++;
    if((table->nentries & (table->nentries - 1)) == 0)
        return 1;

    return 0;

}


static uint16_t get_key(gd_GIF *gif, int key_size, uint8_t *sub_len, uint8_t *shift, uint8_t *byte)
{

    int bits_read;
    int rpad;
    int frag_size;
    uint16_t key;


    key = 0;
    for (bits_read = 0; bits_read < key_size; bits_read += frag_size)
    {

        rpad = (*shift + bits_read) % 8;
        if (rpad == 0)
        {

            /* Update byte. */
            if (*sub_len == 0)
                read_Gif_Blocks(gif, sub_len, 1); /* Must be nonzero! */

            read_Gif_Blocks(gif, byte, 1);
            (*sub_len)--;

        }

        frag_size = MIN(key_size - bits_read, 8 - rpad);
        key |= ((uint16_t) ((*byte) >> rpad)) << bits_read;

    }

    /* Clear extra bits to the left. */
    key &= (1 << key_size) - 1;
    *shift = (*shift + key_size) % 8;

    return key;

}


/* Decompress image pixels.
 * Return 0 on success or -1 on out-of-memory (w.r.t. LZW code table). */
static int read_image_data(gd_GIF *gif)
{

    uint8_t sub_len, shift, byte;
    int init_key_size, key_size, table_is_full;
    int frm_off, str_len, p;
    uint16_t key, clear, stop;
    int ret;
    Table *table;
    Entry entry;


    read_Gif_Blocks(gif, &byte, 1);
    key_size = (int) byte;
    clear = 1 << key_size;
    stop = clear + 1;
    table = new_table(key_size);
    key_size++;
    init_key_size = key_size;
    sub_len = shift = 0;
    key = get_key(gif, key_size, &sub_len, &shift, &byte); /* clear code */
    frm_off = 0;
    ret = 0;

    while(1)
    {

        if (key == clear)
        {

            key_size = init_key_size;
            table->nentries = (1 << (key_size - 1)) + 2;
            table_is_full = 0;

        }
        else if (!table_is_full)
        {

            ret = add_entry(&table, str_len + 1, key, entry.suffix);
            if (ret == -1)
            {

                free(table);
                return -1;

            }

            if (table->nentries == 0x1000)
            {

                ret = 0;
                table_is_full = 1;

            }

        }

        key = get_key(gif, key_size, &sub_len, &shift, &byte);
        if (key == clear) continue;
        if (key == stop) break;
        if (ret == 1) key_size++;
        entry = table->entries[key];
        str_len = entry.length;

        while(1)
        {

            p = frm_off + entry.length - 1;
            gif->frame[(gif->fy + p / gif->fw) * gif->width + gif->fx + p % gif->fw] = entry.suffix;

            if(entry.prefix == 0xFFF)
                break;
            else
                entry = table->entries[entry.prefix];

        }

        frm_off += str_len;
        if(key < table->nentries - 1 && !table_is_full)
            table->entries[table->nentries - 1].suffix = entry.suffix;

    }

    free(table);
    read_Gif_Blocks(gif, &sub_len, 1); /* Must be zero! */

    return 0;

}


static int read_image(gd_GIF *gif)
{

    uint8_t fisrz;


    /* Image Descriptor. */
    gif->fx = read_num(gif);
    gif->fy = read_num(gif);
    gif->fw = read_num(gif);
    gif->fh = read_num(gif);

    read_Gif_Blocks(gif, &fisrz, 1);

    /* Ignore Sort Flag. */
    /* Local Color Table? */
    if(fisrz & 0x80)
    {

        //printf("local color table!!!\n");
        /* Read LCT */

        gif->lct.size = 1 << ((fisrz & 0x07) + 1);
        read_Gif_Blocks(gif, gif->lct.colors, 3 * gif->lct.size);
        gif->palette = &gif->lct;

    }
    else
    {

        gif->palette = &gif->gct;

    }

    /* Image Data. */
    return read_image_data(gif);

}


/* Return 1 if got a frame; 0 if got GIF trailer; -1 if error. */
int getGifFrame(gd_GIF *gif)
{

    char sep = 0x00;
    read_Gif_Blocks(gif, &sep, 1);


    while (sep != 0x2C)
    {

    	// 0x2C – Image block

        if (sep == 0x3B)     // 0x3B – Gif completing
            return 0;

        if (sep == 0x21)     // 0x21 – Extension
            read_ext(gif);

        else return -1;
        read_Gif_Blocks(gif, &sep, 1);

    }

    if (read_image(gif) == -1)
        return -1;

    return 1;

}


static void render_frame_rect(gd_GIF *gif, uint8_t *buffer)
{

    int i, j, k;
    uint8_t index, *color;


    i = gif->fy * gif->width + gif->fx;

    for (j = 0; j < gif->fh; j++)
    {

        for (k = 0; k < gif->fw; k++)
        {

            index = gif->frame[(gif->fy + j) * gif->width + gif->fx + k];
            color = &gif->palette->colors[index*3];

            if (!gif->gce.transparency || index != gif->gce.tindex)
                memcpy(&buffer[(i+k)*3], color, 3);

        }

        i += gif->width;

    }

}


void renderGifFrame(gd_GIF *gif, uint8_t *buffer)
{

    if(gif->gce.disposal == 2)
    	memset(buffer, (uint8_t)gif->bgcolor, gif->width * gif->height * 3); // render background

    render_frame_rect(gif, buffer);                             // render image

}


void rewindGif(gd_GIF *gif)
{

    f_lseek(gif->fp, gif->anim_start);

}
