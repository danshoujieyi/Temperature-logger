#ifndef __XT25F02_H
#define __XT25F02_H

#include "LPC11xx.h"

#define WRITE    0X02
#define WREN    0X06         //–¥»Î πƒ‹
#define WRDI    0X04
#define RDSR    0X05
#define WRSR    0X01
#define READ    0X03

void XT25_WriteEnable(void);
uint8_t XT25_ReadSR(void);
void XT25_Write_Wait(void);
void XT25_Read_Wait(void);
void XT25_WriteSR(uint8_t sr);
void XT25_RUID(void);
void XT25_EraseAll(void);
void XT25_EraseSector(void);
void SPI1_Write_FLASH(uint8_t *data, uint8_t Length);
void SPI1_Read_FLASH(uint8_t *data,uint8_t Length);

#endif
