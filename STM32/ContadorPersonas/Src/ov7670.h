#ifndef _OV7660_H
#define _OV7660_H


#include "SCCB.h"


unsigned char wrOV7670Reg(unsigned char regID, unsigned char regDat);
unsigned char rdOV7670Reg(unsigned char regID, unsigned char *regDat);
void OV7670_config_window(unsigned int startx,unsigned int starty,unsigned int width, unsigned int height);
unsigned char OV7670_init(void);
void set_OV7670reg(void);
void OV7670_config(void);

#endif /* _OV7660_H */



