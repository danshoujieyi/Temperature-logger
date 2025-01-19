#ifndef __UART_H
#define __UART_H

#include "LPC11xx.h"

void UART_Init(uint32_t baudrate);
uint8_t UART_Recive(void);
void UART_Send_Byte(uint8_t byte);
void UART_Send(uint8_t *BufferPtr, uint32_t Length);

#endif
