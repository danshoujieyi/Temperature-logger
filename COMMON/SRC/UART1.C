/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: UART.c
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/22/2010
* 描述  : NXP LPC11xx 系列处理器 UART API 文件 
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LPC11xx.h"
#include "UART.h"

volatile uint32_t UARTStatus;
volatile uint8_t  UARTTxEmpty = 1;
volatile uint8_t  UARTBuffer[UART_BUFSIZE];
volatile uint32_t UARTCount = 0;

/**
  * @函数名:	 UART_IRQHandler
  * @描述:	 UART 中断处理程序 handler
  * @参数:	 无
  * @返回值: 无 
  */
void UART_IRQHandler(void)
{
  uint8_t IIRValue, LSRValue;
  uint8_t Dummy = Dummy;

  IIRValue = LPC_UART->IIR;
   
  /* 跳过 IIR 挂起位 */  
  IIRValue >>= 1;			
  IIRValue &= 0x07;			
  /* 检查  1~3  位, 确定中断  */
  /* 接收行状态 */
  if (IIRValue == IIR_RLS)		
  {
    LSRValue = LPC_UART->LSR;
    /* 接收行状态s */
    if (LSRValue & (LSR_OE | LSR_PE | LSR_FE | LSR_RXFE | LSR_BI))
    {
      /* 存在错误或产生了中断 */
      /* 读 LSR 将清除中断 */
      UARTStatus = LSRValue;
      Dummy = LPC_UART->RBR;	
      return;
    }
    if (LSRValue & LSR_RDR)	/* 接收数据准备好 */			
    {
      /* 如果 RLS 没有产生错误, 准备正常, 保存到数据缓冲区。 */
      /* 注意: 读 RBR 将清除中断 */
      UARTBuffer[UARTCount++] = LPC_UART->RBR;
      if (UARTCount == UART_BUFSIZE)
      {
        UARTCount = 0;		/* buffer overflow */
      }	
    }
  }
  /* 接收数据可用 */
  else if (IIRValue == IIR_RDA)	
  {
    /* 接收数据可用 */
    UARTBuffer[UARTCount++] = LPC_UART->RBR;
    if (UARTCount == UART_BUFSIZE)
    {
      /* 缓冲区溢出 */
      UARTCount = 0;		
    }
  }
  /* 字符超时指示 */
  else if (IIRValue == IIR_CTI)	
  {
    /* 字符超时指示 */
    /* 第 9 位 CTI 错误 */
    UARTStatus |= 0x100;		
  }
  /* THRE, 发送保持寄存器空 */
  else if (IIRValue == IIR_THRE)	
  {
    /* THRE interrupt */
    LSRValue = LPC_UART->LSR;		/* 检查 LSR 状态查看
	  U0THR 是否已经包含有效数据 */
    if (LSRValue & LSR_THRE)
    {
      UARTTxEmpty = 1;
    }
    else
    {
      UARTTxEmpty = 0;
    }
  }
  return;
}

/**
  * @函数名:	ModemInit
  * @描述:	初始化 UART0 端口为 modem, 设置选定的引脚。
  * @参数:	无
  * @返回值:	无
  */
void ModemInit( void )
{
  LPC_IOCON->PIO2_0 &= ~0x07;    /* UART I/O 配置 */
  LPC_IOCON->PIO2_0 |= 0x01;     /* UART DTR */
  LPC_IOCON->PIO0_7 &= ~0x07;    /* UART I/O 配置 */
  LPC_IOCON->PIO0_7 |= 0x01;     /* UART CTS */
  LPC_IOCON->PIO1_5 &= ~0x07;    /* UART I/O 配置 */
  LPC_IOCON->PIO1_5 |= 0x01;     /* UART RTS */
#if 1 
  LPC_IOCON->DSRLOC	= 0;
  LPC_IOCON->PIO2_1 &= ~0x07;    /* UART I/O 配置 */
  LPC_IOCON->PIO2_1 |= 0x01;     /* UART DSR */

  LPC_IOCON->DCDLOC	= 0;
  LPC_IOCON->PIO2_2 &= ~0x07;    /* UART I/O 配置 */
  LPC_IOCON->PIO2_2 |= 0x01;     /* UART DCD */

  LPC_IOCON->RILOC	= 0;
  LPC_IOCON->PIO2_3 &= ~0x07;    /* UART I/O 配置 */
  LPC_IOCON->PIO2_3 |= 0x01;     /* UART RI */

#else
  LPC_IOCON->DSRLOC = 1;
  LPC_IOCON->PIO3_1 &= ~0x07;    /* UART I/O 配置 */
  LPC_IOCON->PIO3_1 |= 0x01;     /* UART DSR */

  LPC_IOCON->DCDLOC = 1;
  LPC_IOCON->PIO3_2 &= ~0x07;    /* UART I/O 配置 */
  LPC_IOCON->PIO3_2 |= 0x01;     /* UART DCD */

  LPC_IOCON->RILOC = 1;
  LPC_IOCON->PIO3_3 &= ~0x07;    /* UART I/O 配置 */
  LPC_IOCON->PIO3_3 |= 0x01;     /* UART RI */
#endif
  LPC_UART->MCR = 0xC0;          /* 使能 Auto RTS 和 Auto CTS. */			
  return;
}

/**
  * @函数名:	UARTInit
  * @描述:	初始化 UART0 端口，设置选中引脚、
  *			时钟，校验、停止位、FIFO、等等。
  * @参数:	UART 波特率
  * @返回值:	无
  */

void UARTInit(uint32_t baudrate)
{
    uint16_t usFdiv;uint16_t regVal;
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);                             /* 使能IOCON时钟               */
    LPC_IOCON->PIO1_6 |= 0x01;                                          /* 将P1.6 1.7配置为RXD和TXD    */
    LPC_IOCON->PIO1_7 |= 0x01;

    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);                               /* 打开UART功能部件时钟         */
    LPC_SYSCON->UARTCLKDIV       = 0x01;                                /* UART时钟分频                 */

    LPC_UART->LCR  = 0x83;                                              /* 允许设置波特率               */
    usFdiv = ((SystemAHBFrequency/regVal)/16)/baudrate;      /* 设置波特率                   */
    LPC_UART->DLM  = usFdiv / 256;
    LPC_UART->DLL  = usFdiv % 256;
    LPC_UART->LCR  = 0x03;                                              /* 锁定波特率                   */
    LPC_UART->FCR  = 0x87;                                              /* 使能FIFO，设置8个字节触发点  */
    
    NVIC_EnableIRQ(UART_IRQn);                                          /* 使能UART中断，并配置优先级   */
    NVIC_SetPriority(UART_IRQn, 1);

    LPC_UART->IER  = 0x01;   
}

/**
  * @函数名:	UARTSend
  * @描述:	根据数据长度发送一串数据到 UART 0 端口
  * @参数:	buffer pointer, and data length
  * @返回值:	无
  */
void UARTSend(uint8_t *BufferPtr, uint32_t Length)
{
  
  while ( Length != 0 )
  {
	  /* THRE 状态, 包含有效数据 */
#if !TX_INTERRUPT
	  while ( !(LPC_UART->LSR & LSR_THRE) );
	  LPC_UART->THR = *BufferPtr;
#else
	  /* 以下数据在中断处理程序中设置当 THRE 产生时。 */
      while ( !(UARTTxEmpty & 0x01) );
	  LPC_UART->THR = *BufferPtr;
      UARTTxEmpty = 0;	/* not empty in the THR until it shifts out */
#endif
      BufferPtr++;
      Length--;
  }
  return;
}

/**
  * @}
  */ 

/**
  * @}
  */ 
/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****文件结束*******/
