/*****************************************************************************
 *   uarttest.c:  UART test C file for NXP LPC11xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.20  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "LPC11xx.h"
#include "uart.h"
#include "gpio.h"
#define BUFSIZE	  10
extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];

int main (void) {

  SystemInit();
  GPIOInit();
  /* NVIC is installed inside UARTInit file. */
  UARTInit(115200);
  GPIOSetDir( PORT0, 1, 1 );	  //P0.1 is output(LED2)
  GPIOSetDir( PORT1, 8, 1 );	  //P1.8 is output(LED1)
  GPIOSetValue( PORT0, 1, 0);
#if MODEM_TEST
  ModemInit();
#endif

  while (1) 
  {				/* Loop forever */
	if ( UARTCount != 0 )
	{
	  LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  UARTSend( (uint8_t *)UARTBuffer, UARTCount );
	  UARTCount = 0;
	  LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	}
  }
}
