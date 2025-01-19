/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: clkconfig.c
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/18/2010
* 描述  : NXP LPC11xx 系列处理器 clkconfig API 文件 
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LPC11xx.h"
#include "clkconfig.h"

/**
  * @函数名: WDT_CLK_Setup
  * @描述: 配置 WDT 时钟.
  * @参数: 时钟源: irc_osc(0), main_clk(1), wdt_osc(2).			  						
  * @返回值: 无
  */
void WDT_CLK_Setup ( uint32_t clksrc )
{
  /* Watchdog configuration. */
  /* Freq = 0.5Mhz, div_sel 为 0, 除以 2. WDT_OSC 是 250khz */
  LPC_SYSCON->WDTOSCCTRL = (0x1<<5)|0x00;
  /* 选择时钟源 */
  LPC_SYSCON->WDTCLKSEL = clksrc;   
  /* 更新时钟 */     
  LPC_SYSCON->WDTCLKUEN = 0x01;   
  /* 切换更新寄存器一次 */       
  LPC_SYSCON->WDTCLKUEN = 0x00;          
  LPC_SYSCON->WDTCLKUEN = 0x01;
  /* 等待直到更新完成 */
  while ( !(LPC_SYSCON->WDTCLKUEN & 0x01) ); 
   /* 除以 1 */   
  LPC_SYSCON->WDTCLKDIV = 1;        
  /* 使 WDT 时钟运行n */   
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<6);    
  return;
}

/**
  * @函数名:	CLKOUT_Setup
  * @描述:	CLKOUT的配置，以供参考时钟检查。
  * @参数:	时钟源: irc_osc(0), sys_osc(1), wdt_osc(2),
  *				main_clk(3).			 					
  * @返回值: 无
 */
void CLKOUT_Setup ( uint32_t clksrc )
{
  /* 配置完成调试 debug PLL . */
  
  /* 选择主时钟 */
  LPC_SYSCON->CLKOUTCLKSEL = clksrc;	
  /* 更新时钟 */
  LPC_SYSCON->CLKOUTUEN = 0x01;		
  /* 切换更新寄存器一次 */
  LPC_SYSCON->CLKOUTUEN = 0x00;		
  LPC_SYSCON->CLKOUTUEN = 0x01;
  /* 等待直到更新完成 */
  while ( !(LPC_SYSCON->CLKOUTUEN & 0x01) );	
  /* 除以 1 */	
  LPC_SYSCON->CLKOUTDIV = 1;			
  return;
}

/**
  * @}
  */ 

/**
  * @}
  */ 
/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****文件结束*******/
