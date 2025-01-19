#ifndef __DS1307_H
#define __DS1307_H

#include "LPC11xx.h"

void DS1307Init(void);
void DS1307_Read(void);
void DS1307_Write(uint8_t *data);
void Ds1307_WriteByte(uint8_t WriteAddr,uint8_t WriteData);
uint8_t Ds1307_ReadByte(void);


#endif
