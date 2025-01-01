/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: clkconfig.h
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/18/2010
* 描述  : NXP LPC13xx 系列处理器 clk 头文件
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/
#ifndef __CLKCONFIG_H 
#define __CLKCONFIG_H

#define WDTCLK_SRC_IRC_OSC			0
#define WDTCLK_SRC_MAIN_CLK			1
#define WDTCLK_SRC_WDT_OSC			2

#define CLKOUTCLK_SRC_IRC_OSC		0
#define CLKOUTCLK_SRC_SYS_OSC		1
#define CLKOUTCLK_SRC_WDT_OSC		2
#define CLKOUTCLK_SRC_MAIN_CLK		3

void WDT_CLK_Setup(uint32_t timer_num);
void CLKOUT_Setup(uint32_t timer_num);
#endif /* end __CLKCONFIG_H */


/**
  * @}
  */ 

/**
  * @}
  */ 
/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****文件结束*******/

