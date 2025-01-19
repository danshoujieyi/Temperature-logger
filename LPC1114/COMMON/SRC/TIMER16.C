/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: timer16.c
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/18/2010
* 描述  : 16位定时器相关的函数实现
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LPC11xx.h"
#include "timer16.h"

volatile uint32_t timer16_0_counter = 0;
volatile uint32_t timer16_1_counter = 0;



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @函数名：delayMs
  * @描述：以间隔毫秒启动定时器直到时间耗完
  * @参数：定时器号，以毫秒为单位的延迟时间
  * @返回值：无
  */
void delayMs(uint8_t timer_num, uint32_t delayInMs)
{
  if (timer_num == 0)
  {
    /* 建立定时器0的延迟 */
    /* 复位定时器 */
	LPC_TMR16B0->TCR = 0x02;	
    /* 设置预分频器为0 */
	LPC_TMR16B0->PR  = 0x00;		
    LPC_TMR16B0->MR0 = delayInMs * (SystemAHBFrequency / 1000);
    /* 复位所有的中断 */
	LPC_TMR16B0->IR  = 0xff;		
    /* 停止定时器匹配 */
	LPC_TMR16B0->MCR = 0x04;		
    	/* 启动定时器 */
	LPC_TMR16B0->TCR = 0x01;	
    /* 等待直到延迟时间消耗完 */
    while (LPC_TMR16B0->TCR & 0x01);
  }
  else if (timer_num == 1)
  {
    /* 建立定时器1的延迟 */
    /* 复位定时器 */
    LPC_TMR16B1->TCR = 0x02;
    /* 设置预分频器为0 */		
    LPC_TMR16B1->PR  = 0x00;		
    LPC_TMR16B1->MR0 = delayInMs * (SystemAHBFrequency / 1000);
    /* 复位所有的中断 */
    LPC_TMR16B1->IR  = 0xff;		
    /* 停止定时器匹配 */
    LPC_TMR16B1->MCR = 0x04;		
    /* 启动定时器 */
    LPC_TMR16B1->TCR = 0x01;		
     /* 等待直到延迟时间消耗完 */
    while (LPC_TMR16B1->TCR & 0x01);
  }
  return;
}


/**
  * @函数名：TIMER_0_IRQHandler
  * @描述：定时器/计数器0中断例程在60 MHz CPU时钟下每10ms执行一次
  * @参数：无
  * @返回值：无
  */
void TIMER16_0_IRQHandler(void)
{ 
	/* 清中断标志位 */	  
  LPC_TMR16B0->IR = 1;			
  timer16_0_counter++;
  return;
}


/**
  * @函数名：TIMER_1_IRQHandler
  * @描述：定时器/计数器1中断例程在60 MHz CPU时钟下每10ms执行一次
  * @参数：无
  * @返回值：无
  */
void TIMER16_1_IRQHandler(void)
{  
  LPC_TMR16B1->IR = 1;			/* clear interrupt flag */
  timer16_1_counter++;
  return;
}

/**
  * @函数名：enable_timer
  * @描述：使能定时器
  * @参数：定时器号：0 或 1
  * @返回值：无
  */
void enable_timer16(uint8_t timer_num)
{
  if ( timer_num == 0 )
  {
    LPC_TMR16B0->TCR = 1;
  }
  else
  {
    LPC_TMR16B1->TCR = 1;
  }
  return;
}


/**
  * @函数名：disable_timer
  * @描述：禁止定时器
  * @参数：定时器号：0 或 1
  * @返回值：无
  */
void disable_timer16(uint8_t timer_num)
{
  if ( timer_num == 0 )
  {
    LPC_TMR16B0->TCR = 0;
  }
  else
  {
    LPC_TMR16B1->TCR = 0;
  }
  return;
}


/**
  * @函数名：reset_timer
  * @描述：重启定时器
  * @参数：定时器号：0 或 1
  * @返回值：无
  */
void reset_timer16(uint8_t timer_num)
{
  uint32_t regVal;

  if ( timer_num == 0 )
  {
    regVal = LPC_TMR16B0->TCR;
    regVal |= 0x02;
    LPC_TMR16B0->TCR = regVal;
  }
  else
  {
    regVal = LPC_TMR16B1->TCR;
    regVal |= 0x02;
    LPC_TMR16B1->TCR = regVal;
  }
  return;
}


/**
  * @函数名：init_timer
  * @描述：初始化定时器，设置定时器间隔，复位定时器设置定时器中断例程
  * @参数：定时器号和定时器间隔
  * @返回值：无
  */
void init_timer16(uint8_t timer_num, uint32_t TimerInterval) 
{
  if ( timer_num == 0 )
  {
    /* 因为JTAG和定时器CAP/MAT管脚是混合使用的如果在使用了该模块是一些 I/O 管脚语言仔细的配置。 */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
    /*  Timer0_16 I/O 配置 */
		/* Timer0_16 CAP0 */
	LPC_IOCON->PIO0_2           &= ~0x07;	
    LPC_IOCON->PIO0_2           |= 0x02;	
    	/* Timer0_16 MAT0 */
	LPC_IOCON->PIO0_8           &= ~0x07;	
    LPC_IOCON->PIO0_8           |= 0x02;	
    	/* Timer0_16 MAT1 */
	LPC_IOCON->PIO0_9           &= ~0x07;
    LPC_IOCON->PIO0_9           |= 0x02;	
#ifdef __JTAG_DISABLED
   	/* Timer0_16 MAT2 */
    LPC_IOCON->JTAG_TCK_PIO0_10 &= ~0x07;
    LPC_IOCON->JTAG_TCK_PIO0_10 |= 0x03;		
#endif	

    timer16_0_counter = 0;
    LPC_TMR16B0->MR0 = TimerInterval;
//	LPC_TMR16B0->EMR &= ~(0xFF<<4);
//	LPC_TMR16B0->EMR |= ((0x3<<4)|(0x3<<6));
   		/* MR0上的中断和复位  */
    LPC_TMR16B0->MCR = 3;			

    /* 使能TIMER0中断 */
    NVIC_EnableIRQ(TIMER_16_0_IRQn);
  }
  else if ( timer_num == 1 )
  {
    /* 因为JTAG和定时器CAP/MAT管脚是混合使用的如果在使用了该模块是一些 I/O 管脚语言仔细的配置。 */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<8);
    	/*  Timer1_16 I/O 配置 */
		/* Timer1_16 CAP0 */
	LPC_IOCON->PIO1_8           &= ~0x07;
    LPC_IOCON->PIO1_8           |= 0x01;	
    	/* Timer1_16 MAT0 */
	LPC_IOCON->PIO1_9           &= ~0x07;	
    LPC_IOCON->PIO1_9           |= 0x01;	
    	/* Timer1_16 MAT1 */
	LPC_IOCON->PIO1_10          &= ~0x07;
    LPC_IOCON->PIO1_10          |= 0x02;		

    timer16_1_counter = 0;
    LPC_TMR16B1->MR0 = TimerInterval;
//	LPC_TMR16B1->EMR &= ~(0xFF<<4);
//	LPC_TMR16B1->EMR |= ((0x3<<4)|(0x3<<6));
    /* MR0上的中断和复位  */
	LPC_TMR16B1->MCR = 3;				

    /* 使能TIMER0中断 */
    NVIC_EnableIRQ(TIMER_16_1_IRQn);
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
