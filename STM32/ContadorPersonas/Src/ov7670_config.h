/*
 * ov7670_config.h
 *
 *  Created on: 1 may. 2019
 *      Author: almustafa
 */

#ifndef OV7670_CONFIG_H_
#define OV7670_CONFIG_H_

#include "ov7670.h"
#include "dwt_delay.h"
#include "main.h"


void init_rgb565_qvga_25fps_new(void);
void init_rgb565_qvga_25fps(void);
void init_rgb565_qvga_12fps(void);
void init_yuv_12fps(void);
void init_yuv_25fps(void);


#endif /* OV7670_CONFIG_H_ */
