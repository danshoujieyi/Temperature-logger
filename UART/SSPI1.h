#ifndef __SSPI1_H
#define __SSPI1_H

#include "LPC11xx.h"

void SSP1_IOConfig(void);
void SSPI1_Init(void);
void SSP1_LOW(void);
void SSP1_HIGH(void);

uint8_t SPI1_Comunicate(uint8_t TxData);
void SSP1_Send(uint8_t *data,uint8_t Length);
void SSP1_Receive(uint8_t *data,int Length);


#endif
