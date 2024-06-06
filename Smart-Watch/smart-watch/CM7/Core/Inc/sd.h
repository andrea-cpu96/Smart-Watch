/*
 * sd.h
 *
 *  Created on: Jun 6, 2024
 *      Author: Fato
 */

#ifndef INC_SD_H_
#define INC_SD_H_

#include "fatfs.h"

void sd_init(void);
void sd_open(FIL *file, char *fileName, char rw);

#endif /* INC_SD_H_ */
