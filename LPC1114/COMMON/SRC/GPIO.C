/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: gpio.c
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/18/2010
* 描述  : NXP LPC11xx 系列处理器 GPIO API 文件
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "LPC11xx.h"			/* LPC11xx 外设寄存器 */
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
volatile uint32_t gpio0_counter = 0;
volatile uint32_t gpio1_counter = 0;
volatile uint32_t gpio2_counter = 0;
volatile uint32_t gpio3_counter = 0;
volatile uint32_t p0_1_counter  = 0;
volatile uint32_t p1_1_counter  = 0;
volatile uint32_t p2_1_counter  = 0;
volatile uint32_t p3_1_counter  = 0;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @函数名：PIOINT0_IRQHandler
  * @描述：使用GPIO一个管脚（端口0的管脚1）作为中断源 
  * @参数： 无
  * @返回值：无
  */
  /*
void PIOINT0_IRQHandler(void)
{
  uint32_t regVal;

  gpio0_counter++;
  regVal = GPIOIntStatus( PORT0, 1 );
  if ( regVal )
  {
	p0_1_counter++;
	GPIOSetDir( 1, 8, 1 );
	GPIOIntClear( PORT0, 1 );
  }	  
  printf("\n\r PIOINT0_IRQHandler! \n\r");		
  return;
}

*
  * @函数名：PIOINT1_IRQHandler
  * @描述：使用GPIO一个管脚（端口1的管脚1）作为中断源
  * @参数：无
  * @返回值：无
 
void PIOINT1_IRQHandler(void)
{
  uint32_t regVal;

  gpio1_counter++;
  regVal = GPIOIntStatus( PORT1, 1 );
  if ( regVal )
  {
	GPIOSetValue(PORT1,8,1);
	GPIOIntClear( PORT1, 0);
  }		
  return;
}
 */

/**
  * @函数名：PIOINT2_IRQHandler
  * @描述：使用GPIO一个管脚（端口2的管脚1）作为中断源 interrupt source
  * @参数：无
  * @返回值：无
  
void PIOINT2_IRQHandler(void)
{
  uint32_t regVal;

  gpio2_counter++;
  regVal = GPIOIntStatus( PORT1, 0 );
  if ( regVal )
  {
	GPIOSetValue(PORT1,8,1);
	GPIOIntClear( PORT1, 0);
  }		
  return;
}
*/

/**
  * @函数名：PIOINT3_IRQHandler
  * @描述：使用GPIO一个管脚（端口3的管脚1）作为中断源 interrupt source
  * @参数： 无
  * @返回值：无

void PIOINT3_IRQHandler(void)
{
  uint32_t regVal;

  gpio3_counter++;
  regVal = GPIOIntStatus( PORT3, 1 );
  if ( regVal )
  {
	p3_1_counter++;
	GPIOIntClear( PORT3, 1 );
  }		
  return;
}
  */
/**
  * @函数名：GPIOInit
  * @描述：初始化GPIO，设置GPIO的中断例程
  * @参数： 无
  * @返回值：真或假，如果VIC表已满并且GPIO中断例程已经设置了则返回假。
  */
void GPIOInit( void )
{
  /* 使能AHB时钟到GPIO域。*/
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

#ifdef __JTAG_DISABLED  
  LPC_IOCON->JTAG_TDO_PIO1_1  &= ~0x07;
  LPC_IOCON->JTAG_TDO_PIO1_1  |= 0x01;
#endif

  /* 当I/O管脚被配置为外部中断时，建立NVIC。*/
  NVIC_EnableIRQ(EINT0_IRQn);
  NVIC_EnableIRQ(EINT1_IRQn);
  NVIC_EnableIRQ(EINT2_IRQn);
  NVIC_EnableIRQ(EINT3_IRQn);
  return;
}

/**
  * @函数名：GPIOSetDir
  * @描述：设置GPIO端口方向
  * @参数：端口号，管脚位置，方向（1为输出，0为输入）
  * @返回值：无
  */
void GPIOSetDir( uint32_t portNum, uint32_t bitPosi, uint32_t dir )
{
  /* 如果方向是输出（1），但是GPIOx_DIR的方向没有设置，设置方向为输出（1）；
  如果方向是输入（0），但是GPIOx_DIR已经设置了，清方向后在设置为输入（0）。
  其他条件都忽略。在端口3上（只有0至3位），如果位值超出了范围，没有错误保护	。 */
  switch ( portNum )
  {
	case PORT0:
	  if ( !(LPC_GPIO0->DIR & (0x1<<bitPosi)) && (dir == 1) )
	  {
		LPC_GPIO0->DIR |= (0x1<<bitPosi);
	  }
	  else if ( (LPC_GPIO0->DIR & (0x1<<bitPosi)) && (dir == 0) )
	  {
		LPC_GPIO0->DIR &= ~(0x1<<bitPosi);
	  }	  
	  break;
 	case PORT1:
	  if ( !(LPC_GPIO1->DIR & (0x1<<bitPosi)) && (dir == 1) )
	  {
		LPC_GPIO1->DIR |= (0x1<<bitPosi);
	  }
	  else if ( (LPC_GPIO1->DIR & (0x1<<bitPosi)) && (dir == 0) )
	  {
		LPC_GPIO1->DIR &= ~(0x1<<bitPosi);
	  }	  
	  break;
	case PORT2:
	  if ( !(LPC_GPIO2->DIR & (0x1<<bitPosi)) && (dir == 1) )
	  {
		LPC_GPIO2->DIR |= (0x1<<bitPosi);
	  }
	  else if ( (LPC_GPIO2->DIR & (0x1<<bitPosi)) && (dir == 0) )
	  {
		LPC_GPIO2->DIR &= ~(0x1<<bitPosi);
	  }	  
	  break;
	case PORT3:
	  if ( !(LPC_GPIO3->DIR & (0x1<<bitPosi)) && (dir == 1) )
	  {
		LPC_GPIO3->DIR |= (0x1<<bitPosi);
	  }
	  else if ( (LPC_GPIO3->DIR & (0x1<<bitPosi)) && (dir == 0) )
	  {
		LPC_GPIO3->DIR &= ~(0x1<<bitPosi);
	  }	  
	  break;
	default:
	  break;
  }
}
/*
uint32_t GPIOGetbit(uint32_t portNum,uint32_t bitPosi)
{
	uint32_t bitVal;
	switch(portNum)
	{
		case PORT0:
			bitVal=(LPC_GPIO0->DATA>>bitPosi)&0x01;
			return	bitVal;
			break;
		case PORT1:
			bitVal=(LPC_GPIO1->DATA>>bitPosi)&0x01;
			return	bitVal;
			break;
		case PORT2:
			bitVal=(LPC_GPIO2->DATA>>bitPosi)&0x01;
			return	bitVal;
			break;
		case PORT3:
			bitVal=(LPC_GPIO3->DATA>>bitPosi)&0x01;
			return	bitVal;
			break;
	}	
} */
/**
  * @函数名：GPIOSetValue
  * @描述：设置/清除一个在GPIO端口X（X是端口号）上的一些特定管脚上的位值。 
  * @参数：端口号，位地址，位值
  * @返回值：无
  */
void GPIOSetValue( uint32_t portNum, uint32_t bitPosi, uint32_t bitVal )
{
   /* 如果值是，但是 GPIOx_DAT 没有设置，设置 DATA
  为 1； 如果值是 0，但是 GPIOx_DAT 已经设置了， 清除
  DATA 为 0。其他条件都忽略。在端口3上（只有0至3位），如果位值超出了范围，没有错误保护	。 */
  switch ( portNum )
  {
	case PORT0:
	  if ( !(LPC_GPIO0->DATA & (0x1<<bitPosi)) && (bitVal == 1) )
	  {
		LPC_GPIO0->DATA |= (0x1<<bitPosi);
	  }
	  else if ( (LPC_GPIO0->DATA & (0x1<<bitPosi)) && (bitVal == 0) )
	  {
		LPC_GPIO0->DATA &= ~(0x1<<bitPosi);
	  }	  
	  break;
 	case PORT1:
	  if ( !(LPC_GPIO1->DATA & (0x1<<bitPosi)) && (bitVal == 1) )
	  {
		LPC_GPIO1->DATA |= (0x1<<bitPosi);
	  }
	  else if ( (LPC_GPIO1->DATA & (0x1<<bitPosi)) && (bitVal == 0) )
	  {
		LPC_GPIO1->DATA &= ~(0x1<<bitPosi);
	  }	  
	  break;
	case PORT2:
	  if ( !(LPC_GPIO2->DATA & (0x1<<bitPosi)) && (bitVal == 1) )
	  {
		LPC_GPIO2->DATA |= (0x1<<bitPosi);
      }
	  else if ( (LPC_GPIO2->DATA & (0x1<<bitPosi)) && (bitVal == 0) )
	  {
		LPC_GPIO2->DATA &= ~(0x1<<bitPosi);
	  }	  
	  break;
	case PORT3:
	  if ( !(LPC_GPIO3->DATA & (0x1<<bitPosi)) && (bitVal == 1) )
	  {
		LPC_GPIO3->DATA |= (0x1<<bitPosi);
	  }
	  else if ( (LPC_GPIO3->DATA & (0x1<<bitPosi)) && (bitVal == 0) )
	  {
		LPC_GPIO3->DATA &= ~(0x1<<bitPosi);
	  }	  
	  break;
	default:
	  break;
  }
}

/**
  * @函数名：GPIOSetInterrupt
  * @描述：设置中断侦测，事件等。边沿或层次，0为边沿，1为层次
  *			  单边沿或双边沿，0为单边沿，1为双边沿高或低有效等。
  * @参数：端口号, 位地址, sense, single/doube, polarity
  * @返回值：无
  */				
void GPIOSetInterrupt( uint32_t portNum, uint32_t bitPosi, uint32_t sense,
			uint32_t single, uint32_t event )
{
  switch ( portNum )
  {
	case PORT0:
	  if ( sense == 0 )
	  {
		LPC_GPIO0->IS &= ~(0x1<<bitPosi);
		/* single or double only applies when sense is 0(边沿触发) */
		if ( single == 0 )
		  LPC_GPIO0->IBE &= ~(0x1<<bitPosi);
		else
		  LPC_GPIO0->IBE |= (0x1<<bitPosi);
	  }
	  else
	  	LPC_GPIO0->IS |= (0x1<<bitPosi);
	  if ( event == 0 )
		LPC_GPIO0->IEV &= ~(0x1<<bitPosi);
	  else
		LPC_GPIO0->IEV |= (0x1<<bitPosi);
	break;
 	case PORT1:
	  if ( sense == 0 )
	  {
		LPC_GPIO1->IS &= ~(0x1<<bitPosi);
		/* single or double only applies when sense is 0(edge trigger). */
		if ( single == 0 )
		  LPC_GPIO1->IBE &= ~(0x1<<bitPosi);
		else
		  LPC_GPIO1->IBE |= (0x1<<bitPosi);
	  }
	  else
	  	LPC_GPIO1->IS |= (0x1<<bitPosi);
	  if ( event == 0 )
		LPC_GPIO1->IEV &= ~(0x1<<bitPosi);
	  else
		LPC_GPIO1->IEV |= (0x1<<bitPosi);  
	break;
	case PORT2:
	  if ( sense == 0 )
	  {
		LPC_GPIO2->IS &= ~(0x1<<bitPosi);
		/* single 或 double 只在 sense 为 0 时应用(edge trigger). */
		if ( single == 0 )
		  LPC_GPIO2->IBE &= ~(0x1<<bitPosi);
		else
		  LPC_GPIO2->IBE |= (0x1<<bitPosi);
	  }
	  else
	  	LPC_GPIO2->IS |= (0x1<<bitPosi);
	  if ( event == 0 )
		LPC_GPIO2->IEV &= ~(0x1<<bitPosi);
	  else
		LPC_GPIO2->IEV |= (0x1<<bitPosi);  
	break;
	case PORT3:
	  if ( sense == 0 )
	  {
		LPC_GPIO3->IS &= ~(0x1<<bitPosi);
		/* single 或 double 只在 sense 为 0 时应用(edge trigger). */
		if ( single == 0 )
		  LPC_GPIO3->IBE &= ~(0x1<<bitPosi);
		else
		  LPC_GPIO3->IBE |= (0x1<<bitPosi);
	  }
	  else
	  	LPC_GPIO3->IS |= (0x1<<bitPosi);
	  if ( event == 0 )
		LPC_GPIO3->IEV &= ~(0x1<<bitPosi);
	  else
		LPC_GPIO3->IEV |= (0x1<<bitPosi);	  
	break;
	default:
	  break;
  }
  return;
}

/**
  * @函数名：GPIOIntEnable
  * @描述：使能相关端口管脚中断
  * @参数：端口号, 位地址
  * @返回值：无
  */
void GPIOIntEnable( uint32_t portNum, uint32_t bitPosi )
{
  switch ( portNum )
  {
	case PORT0:
	  LPC_GPIO0->IE |= (0x1<<bitPosi); 
	break;
 	case PORT1:
	  LPC_GPIO1->IE |= (0x1<<bitPosi);	
	break;
	case PORT2:
	  LPC_GPIO2->IE |= (0x1<<bitPosi);	    
	break;
	case PORT3:
	  LPC_GPIO3->IE |= (0x1<<bitPosi);	    
	break;
	default:
	  break;
  }
  return;
}

/**
  * @函数名:	GPIOIntDisable
  * @描述:	屏蔽相关端口管脚的中断
  * @参数:	端口号, 位地址
  * @返回值:	无 
  */
void GPIOIntDisable( uint32_t portNum, uint32_t bitPosi )
{
  switch ( portNum )
  {
	case PORT0:
	  LPC_GPIO0->IE &= ~(0x1<<bitPosi); 
	break;
 	case PORT1:
	  LPC_GPIO1->IE &= ~(0x1<<bitPosi);	
	break;
	case PORT2:
	  LPC_GPIO2->IE &= ~(0x1<<bitPosi);	    
	break;
	case PORT3:
	  LPC_GPIO3->IE &= ~(0x1<<bitPosi);	    
	break;
	default:
	  break;
  }
  return;
}

/**
  * @函数名：GPIOIntStatus
  * @描述：获得端口管脚的中断状态。 
  * @参数：端口号, 位地址
  * @返回值：无 
  */
uint32_t GPIOIntStatus( uint32_t portNum, uint32_t bitPosi )
{
  uint32_t regVal = 0;

  switch ( portNum )
  {
	case PORT0:
	  if ( LPC_GPIO0->MIS & (0x1<<bitPosi) )
		regVal = 1;
	break;
 	case PORT1:
	  if ( LPC_GPIO1->MIS & (0x1<<bitPosi) )
		regVal = 1;	
	break;
	case PORT2:
	  if ( LPC_GPIO2->MIS & (0x1<<bitPosi) )
		regVal = 1;		    
	break;
	case PORT3:
	  if ( LPC_GPIO3->MIS & (0x1<<bitPosi) )
		regVal = 1;		    
	break;
	default:
	  break;
  }
  return ( regVal );
}

/** 
  * @函数名:	GPIOIntClear
  * @描述:	清除端口管脚的中断。
  * @参数:	端口号, 位地址
  * @返回值:	无
  */
void GPIOIntClear( uint32_t portNum, uint32_t bitPosi )
{
  switch ( portNum )
  {
	case PORT0:
	  LPC_GPIO0->IC |= (0x1<<bitPosi); 
	break;
 	case PORT1:
	  LPC_GPIO1->IC |= (0x1<<bitPosi);	
	break;
	case PORT2:
	  LPC_GPIO2->IC |= (0x1<<bitPosi);	    
	break;
	case PORT3:
	  LPC_GPIO3->IC |= (0x1<<bitPosi);	    
	break;
	default:
	  break;
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
