/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: timer16.h
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/18/2010
* 描述  : 16位定时器相关宏定义和函数原型
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/
#ifndef __TIMER16_H 
#define __TIMER16_H


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TIME_INTERVAL	(SystemAHBFrequency/100 - 1)
/* 依赖于系统时钟频率和系统AHB时钟频率，如果系统频率 = 60Mhz, AHB频率 = 1/4 系统频率, 
10mSec = 150.000-1 计数*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void delayMs(uint8_t timer_num, uint32_t delayInMs);
void TIMER16_0_IRQHandler(void);
void TIMER16_1_IRQHandler(void);
void enable_timer16(uint8_t timer_num);
void disable_timer16(uint8_t timer_num);
void reset_timer16(uint8_t timer_num);
void init_timer16(uint8_t timer_num, uint32_t timerInterval);
/* Private functions ---------------------------------------------------------*/

#endif /* end __TIMER16_H */
/**
  * @}
  */ 

/**
  * @}
  */ 
/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****文件结束*******/
