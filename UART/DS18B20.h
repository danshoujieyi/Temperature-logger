#ifndef __DS18B20_H
#define __DS18B20_H

#include "LPC11xx.h"

char DS18B20_Init(void);
void DQ_OUT(void);
void DQ_IN(void);
uint8_t DQ_GET(void);
void DQ( uint8_t bitVal );
uint8_t DS18B20_Read_Byte(void);
void DS18B20_Write_Byte(uint8_t dat);
uint8_t DS18B20_Check(void);
void DS18B20_Start(void);
float DS18B20_GetTemperture(void);

#endif
