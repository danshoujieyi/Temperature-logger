#include "Delay.h"

void T16B0_init(void)
{
            
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);	//那1?邦TIM16B0那㊣?車
	LPC_TMR16B0->IR  = 0x01;		//MR0?D???∩??,?∩???D??㏒“bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0㏒?
	LPC_TMR16B0->MCR = 0x04;		//MR0?D??2迆谷迆那㊣赤㏒?1TCo赤PC㏒?2⊿那1TCR[0]=0, 赤㏒?1?“那㊣?¯1∟℅¯
}

void T16B0_delay_ms(uint16_t ms)
{
            
	LPC_TMR16B0->TCR = 0x02;		//?∩???“那㊣?¯㏒“bit1㏒oD∩1?∩??㏒?
	LPC_TMR16B0->PR  = SystemCoreClock/1000-1;		// 1o芍??TC+1
	LPC_TMR16B0->MR0 = ms;	// ℅⊿辰a㏒oMR0那?16????∩??¯㏒??米2?辰a3?1y65535
	LPC_TMR16B0->TCR = 0x01;		//???‘?“那㊣?¯㏒oTCR[0]=1;	  
	LPC_TMR16B0->TCR = 0x01;		//???‘?“那㊣?¯㏒oTCR[0]=1;	 
	while (LPC_TMR16B0->TCR & 0x01);//米豕∩y?“那㊣?¯??那㊣那㊣??米?
}

void T16B0_delay_us(uint16_t us)
{
            
	LPC_TMR16B0->TCR = 0x02;		//?∩???“那㊣?¯㏒“bit1㏒oD∩1?∩??㏒?
	LPC_TMR16B0->PR  = SystemCoreClock/1000000-1;		// 1?⊿??TC+1
	LPC_TMR16B0->MR0 = us;	// ℅⊿辰a㏒oMR0那?16????∩??¯㏒??米2?辰a3?1y65535
	LPC_TMR16B0->TCR = 0x01;		//???‘?“那㊣?¯㏒oTCR[0]=1;	  
	while (LPC_TMR16B0->TCR & 0x01);//米豕∩y?“那㊣?¯??那㊣那㊣??米?
}
