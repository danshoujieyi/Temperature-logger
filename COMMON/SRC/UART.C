// /******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
// * 文件名: UART.c
// * 作者  : Wuhan R&D Center, Embest
// * 日期  : 01/22/2010
// * 描述  : NXP LPC11xx 系列处理器 UART API 文件 
// *******************************************************************************
// *******************************************************************************
// * 历史:
// * 01/18/2010		 : V1.0		   初始版本
// *******************************************************************************/
// /* Includes ------------------------------------------------------------------*/
// #include "LPC11xx.h"
// #include "UART.h"

// volatile uint32_t UARTStatus;
// volatile uint8_t  UARTTxEmpty = 1;
// volatile uint8_t  UARTBuffer[UART_BUFSIZE];
// volatile uint32_t UARTCount = 0;

// /**
//   * @函数名:	 UART_IRQHandler
//   * @描述:	 UART 中断处理程序 handler
//   * @参数:	 无
//   * @返回值: 无 
//   */
// void UART_IRQHandler(void)
// {
//   uint8_t IIRValue, LSRValue;
//   uint8_t Dummy = Dummy;

//   IIRValue = LPC_UART->IIR;
   
//   /* 跳过 IIR 挂起位 */  
//   IIRValue >>= 1;			
//   IIRValue &= 0x07;			
//   /* 检查  1~3  位, 确定中断  */
//   /* 接收行状态 */
//   if (IIRValue == IIR_RLS)		
//   {
//     LSRValue = LPC_UART->LSR;
//     /* 接收行状态s */
//     if (LSRValue & (LSR_OE | LSR_PE | LSR_FE | LSR_RXFE | LSR_BI))
//     {
//       /* 存在错误或产生了中断 */
//       /* 读 LSR 将清除中断 */
//       UARTStatus = LSRValue;
//       Dummy = LPC_UART->RBR;	
//       return;
//     }
//     if (LSRValue & LSR_RDR)	/* 接收数据准备好 */			
//     {
//       /* 如果 RLS 没有产生错误, 准备正常, 保存到数据缓冲区。 */
//       /* 注意: 读 RBR 将清除中断 */
//       UARTBuffer[UARTCount++] = LPC_UART->RBR;
//       if (UARTCount == UART_BUFSIZE)
//       {
//         UARTCount = 0;		/* buffer overflow */
//       }	
//     }
//   }
//   /* 接收数据可用 */
//   else if (IIRValue == IIR_RDA)	
//   {
//     /* 接收数据可用 */
//     UARTBuffer[UARTCount++] = LPC_UART->RBR;
//     if (UARTCount == UART_BUFSIZE)
//     {
//       /* 缓冲区溢出 */
//       UARTCount = 0;		
//     }
//   }
//   /* 字符超时指示 */
//   else if (IIRValue == IIR_CTI)	
//   {
//     /* 字符超时指示 */
//     /* 第 9 位 CTI 错误 */
//     UARTStatus |= 0x100;		
//   }
//   /* THRE, 发送保持寄存器空 */
//   else if (IIRValue == IIR_THRE)	
//   {
//     /* THRE interrupt */
//     LSRValue = LPC_UART->LSR;		/* 检查 LSR 状态查看
// 	  U0THR 是否已经包含有效数据 */
//     if (LSRValue & LSR_THRE)
//     {
//       UARTTxEmpty = 1;
//     }
//     else
//     {
//       UARTTxEmpty = 0;
//     }
//   }
//   return;
// }

// /**
//   * @函数名:	ModemInit
//   * @描述:	初始化 UART0 端口为 modem, 设置选定的引脚。
//   * @参数:	无
//   * @返回值:	无
//   */
// void ModemInit( void )
// {
//   LPC_IOCON->PIO2_0 &= ~0x07;    /* UART I/O 配置 */
//   LPC_IOCON->PIO2_0 |= 0x01;     /* UART DTR */
//   LPC_IOCON->PIO0_7 &= ~0x07;    /* UART I/O 配置 */
//   LPC_IOCON->PIO0_7 |= 0x01;     /* UART CTS */
//   LPC_IOCON->PIO1_5 &= ~0x07;    /* UART I/O 配置 */
//   LPC_IOCON->PIO1_5 |= 0x01;     /* UART RTS */
// #if 1 
//   LPC_IOCON->DSRLOC	= 0;
//   LPC_IOCON->PIO2_1 &= ~0x07;    /* UART I/O 配置 */
//   LPC_IOCON->PIO2_1 |= 0x01;     /* UART DSR */

//   LPC_IOCON->DCDLOC	= 0;
//   LPC_IOCON->PIO2_2 &= ~0x07;    /* UART I/O 配置 */
//   LPC_IOCON->PIO2_2 |= 0x01;     /* UART DCD */

//   LPC_IOCON->RILOC	= 0;
//   LPC_IOCON->PIO2_3 &= ~0x07;    /* UART I/O 配置 */
//   LPC_IOCON->PIO2_3 |= 0x01;     /* UART RI */

// #else
//   LPC_IOCON->DSRLOC = 1;
//   LPC_IOCON->PIO3_1 &= ~0x07;    /* UART I/O 配置 */
//   LPC_IOCON->PIO3_1 |= 0x01;     /* UART DSR */

//   LPC_IOCON->DCDLOC = 1;
//   LPC_IOCON->PIO3_2 &= ~0x07;    /* UART I/O 配置 */
//   LPC_IOCON->PIO3_2 |= 0x01;     /* UART DCD */

//   LPC_IOCON->RILOC = 1;
//   LPC_IOCON->PIO3_3 &= ~0x07;    /* UART I/O 配置 */
//   LPC_IOCON->PIO3_3 |= 0x01;     /* UART RI */
// #endif
//   LPC_UART->MCR = 0xC0;          /* 使能 Auto RTS 和 Auto CTS. */			
//   return;
// }

// /**
//   * @函数名:	UARTInit
//   * @描述:	初始化 UART0 端口，设置选中引脚、
//   *			时钟，校验、停止位、FIFO、等等。
//   * @参数:	UART 波特率
//   * @返回值:	无
//   */
// void UARTInit(uint32_t baudrate)
// {
//   uint32_t Fdiv;
//   uint32_t regVal;

//   UARTTxEmpty = 1;
//   UARTCount = 0;
  
//   NVIC_DisableIRQ(UART_IRQn);

//   LPC_IOCON->PIO1_6 &= ~0x07;    /*  UART I/O config */
//   LPC_IOCON->PIO1_6 |= 0x01;     /* UART RXD */
//   LPC_IOCON->PIO1_7 &= ~0x07;	
//   LPC_IOCON->PIO1_7 |= 0x01;     /* UART TXD */

//   /* Enable UART clock */
//   LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
//   LPC_SYSCON->UARTCLKDIV = 0x1;     /* 分频值 1 */

//   LPC_UART->LCR = 0x83;             /* 8 位数据, 无校验, 1 停止位 */
//   regVal = LPC_SYSCON->UARTCLKDIV;
//   Fdiv = ((SystemAHBFrequency/regVal)/16)/baudrate ;	/*波特率 */

//   LPC_UART->DLM = Fdiv / 256;							
//   LPC_UART->DLL = Fdiv % 256;
//   LPC_UART->LCR = 0x03;		/* DLAB = 0 */
//   LPC_UART->FCR = 0x07;		/* 使能并复位 TX 和 RX FIFO. */

//   /* 读取并清除 line 状态. */
//   regVal = LPC_UART->LSR;

//   /* 确保正常开始, TX 和 RX FIFO 中没有数据. */
//   while ( LPC_UART->LSR & (LSR_THRE|LSR_TEMT) != (LSR_THRE|LSR_TEMT) );
//   while ( LPC_UART->LSR & LSR_RDR )
//   {
// 	regVal = LPC_UART->RBR;	/* 从 RX FIFO 中转储数据 */
//   }
 
//   /* 使能 UART 中断 */
//   NVIC_EnableIRQ(UART_IRQn);

// #if TX_INTERRUPT
//   LPC_UART->IER = IER_RBR | IER_THRE | IER_RLS;	/* 使能 UART 中断 */
// #else
//   LPC_UART->IER = IER_RBR | IER_RLS;	/* 使能 UART 中断 */
// #endif
//   return;
// }

// /**
//   * @函数名:	UARTSend
//   * @描述:	根据数据长度发送一串数据到 UART 0 端口
//   * @参数:	buffer pointer, and data length
//   * @返回值:	无
//   */
// void UARTSend(uint8_t *BufferPtr, uint32_t Length)
// {
  
//   while ( Length != 0 )
//   {
// 	  /* THRE 状态, 包含有效数据 */
// #if !TX_INTERRUPT
// 	  while ( !(LPC_UART->LSR & LSR_THRE) );
// 	  LPC_UART->THR = *BufferPtr;
// #else
// 	  /* 以下数据在中断处理程序中设置当 THRE 产生时。 */
//       while ( !(UARTTxEmpty & 0x01) );
// 	  LPC_UART->THR = *BufferPtr;
//       UARTTxEmpty = 0;	/* not empty in the THR until it shifts out */
// #endif
//       BufferPtr++;
//       Length--;
//   }
//   return;
// }

// /**
//   * @}
//   */ 

// /**
//   * @}
//   */ 
// /************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****文件结束*******/
