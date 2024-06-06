/*
 * sd.c
 *
 *  Created on: Jun 6, 2024
 *      Author: Fato
 */

#include "main.h"
#include "sd.h"


FATFS SDFatFs;  /* File system object for SD card logical drive */
char SDPath[4]; /* SD card logical drive path */
FIL MJPEG_File;          /* MJPEG File object */

static void SD_Initialize(void);




