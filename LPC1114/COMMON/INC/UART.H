/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: uart.h
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/18/2010
* 描述  : NXP LPC13xx 系列处理器 UART 头文件
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/

#ifndef __UART_H 
#define __UART_H


//#define RS485_ENABLED		0
//#define TX_INTERRUPT		0		/* 0 如果 TX 使用 polling, 1 中断驱动. */
//#define MODEM_TEST			0

//#define IER_RBR		0x01
//#define IER_THRE	0x02
//#define IER_RLS		0x04

//#define IIR_PEND	0x01
//#define IIR_RLS		0x03
//#define IIR_RDA		0x02
//#define IIR_CTI		0x06
//#define IIR_THRE	0x01

//#define LSR_RDR		0x01
//#define LSR_OE		0x02
//#define LSR_PE		0x04
//#define LSR_FE		0x08
//#define LSR_BI		0x10
//#define LSR_THRE	0x20
//#define LSR_TEMT	0x40
//#define LSR_RXFE	0x80

//#define UART_BUFSIZE		0x40

///* RS485 mode definition. */
//#define RS485_NMMEN		(0x1<<0)
//#define RS485_RXDIS		(0x1<<1)
//#define RS485_AADEN		(0x1<<2)
//#define RS485_SEL		(0x1<<3)
//#define RS485_DCTRL		(0x1<<4)
//#define RS485_OINV		(0x1<<5)

//void ModemInit( void );
//void UARTInit(uint32_t Baudrate);
//void UART_IRQHandler(void);
//void UARTSend(uint8_t *BufferPtr, uint32_t Length);

#endif /* end __UART_H */


/**
  * @}
  */ 

/**
  * @}
  */ 
/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****文件结束*******/





