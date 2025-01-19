#include "Delay.h"

void T16B0_init(void)
{
            
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);	//��1?��TIM16B0����?��
	LPC_TMR16B0->IR  = 0x01;		//MR0?D???��??,?��???D??�ꡧbit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0��?
	LPC_TMR16B0->MCR = 0x04;		//MR0?D??2��������������?1TCo��PC��?2�騺1TCR[0]=0, ����?1?������?��1�����
}

void T16B0_delay_ms(uint16_t ms)
{
            
	LPC_TMR16B0->TCR = 0x02;		//?��???������?�¡ꡧbit1��oD��1?��??��?
	LPC_TMR16B0->PR  = SystemCoreClock/1000-1;		// 1o��??TC+1
	LPC_TMR16B0->MR0 = ms;	// ���騰a��oMR0��?16????��??�¡�??��2?��a3?1y65535
	LPC_TMR16B0->TCR = 0x01;		//???��?������?�¡�oTCR[0]=1;	  
	LPC_TMR16B0->TCR = 0x01;		//???��?������?�¡�oTCR[0]=1;	 
	while (LPC_TMR16B0->TCR & 0x01);//�̨���y?������?��??��������??��?
}

void T16B0_delay_us(uint16_t us)
{
            
	LPC_TMR16B0->TCR = 0x02;		//?��???������?�¡ꡧbit1��oD��1?��??��?
	LPC_TMR16B0->PR  = SystemCoreClock/1000000-1;		// 1?��??TC+1
	LPC_TMR16B0->MR0 = us;	// ���騰a��oMR0��?16????��??�¡�??��2?��a3?1y65535
	LPC_TMR16B0->TCR = 0x01;		//???��?������?�¡�oTCR[0]=1;	  
	while (LPC_TMR16B0->TCR & 0x01);//�̨���y?������?��??��������??��?
}
