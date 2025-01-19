/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* �ļ���: timer32.c
* ����  : Wuhan R&D Center, Embest
* ����  : 01/18/2010
* ����  : 32λ��ʱ����صĺ���ʵ��
*******************************************************************************
*******************************************************************************
* ��ʷ:
* 01/18/2010		 : V1.0		   ��ʼ�汾
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LPC11xx.h"
#include "timer32.h"

volatile uint32_t timer32_0_counter = 0;
volatile uint32_t timer32_1_counter = 0;



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @��������delay32Ms
  * @�������Լ������������ʱ��ֱ��ʱ����� 
  * @��������ʱ���ţ��Ժ���Ϊ��λ���ӳ�ʱ��
  * @����ֵ����
  */
void delay32Ms(uint8_t timer_num, uint32_t delayInMs)
{
  if (timer_num == 0)
  {
    /* ������ʱ��0���ӳ� */
    /* ��λ��ʱ�� */
	LPC_TMR32B0->TCR = 0x02;		
    /* ����Ԥ��Ƶ��Ϊ0 */
	LPC_TMR32B0->PR  = 0x00;		
    LPC_TMR32B0->MR0 = delayInMs * (SystemAHBFrequency / 1000);
    /* ��λ���е��ж� */
	LPC_TMR32B0->IR  = 0xff;		
    /* ֹͣ��ʱ��ƥ�� */
	LPC_TMR32B0->MCR = 0x04;		
    /* ������ʱ�� */
	LPC_TMR32B0->TCR = 0x01;		
  
    /* �ȴ�ֱ���ӳ�ʱ�������� */
    while (LPC_TMR32B0->TCR & 0x01);
  }
  else if (timer_num == 1)
  {
    /* ������ʱ��1���ӳ� */
    /* ��λ��ʱ�� */
	LPC_TMR32B1->TCR = 0x02;		
    /* ����Ԥ��Ƶ��Ϊ0 */
	LPC_TMR32B1->PR  = 0x00;		
    LPC_TMR32B1->MR0 = delayInMs * (SystemAHBFrequency / 1000);
    /* ��λ���е��ж� */
	LPC_TMR32B1->IR  = 0xff;		
    /* ֹͣ��ʱ��ƥ�� */
	LPC_TMR32B1->MCR = 0x04;		
    /* ������ʱ�� */
	LPC_TMR32B1->TCR = 0x01;		
  
    /* �ȴ�ֱ���ӳ�ʱ�������� */
    while (LPC_TMR32B1->TCR & 0x01);
  }
  return;
}

/**
  * @��������TIMER32_0_IRQHandler
  * @��������ʱ��/������0�ж�������60 MHz CPUʱ����ÿ10msִ��һ��
  * @��������
  * @����ֵ����
  */
void TIMER32_0_IRQHandler(void)
{
  /* ���жϱ�־λ */	 
  LPC_TMR32B0->IR = 1;			
  timer32_0_counter++;
  return;
}

/**
  * @��������TIMER32_1_IRQHandler
  * @��������ʱ��/������1�ж�������60 MHz CPUʱ����ÿ10msִ��һ��
  * @��������
  * @����ֵ����
  */
void TIMER32_1_IRQHandler(void)
{
	/* ���жϱ�־λ */  
  LPC_TMR32B1->IR = 1;			
  timer32_1_counter++;
  return;
}

/**
  * @��������enable_timer
  * @������ʹ�ܶ�ʱ��
  * @��������ʱ���ţ�0 �� 1
  * @����ֵ����
  */
void enable_timer32(uint8_t timer_num)
{
  if ( timer_num == 0 )
  {
    LPC_TMR32B0->TCR = 1;
  }
  else
  {
    LPC_TMR32B1->TCR = 1;
  }
  return;
}


/**
  * @��������disable_timer
  * @��������ֹ��ʱ��
  * @��������ʱ���ţ�0 �� 1
  * @����ֵ����
  */
void disable_timer32(uint8_t timer_num)
{
  if ( timer_num == 0 )
  {
    LPC_TMR32B0->TCR = 0;
  }
  else
  {
    LPC_TMR32B1->TCR = 0;
  }
  return;
}


/**
  * @��������reset_timer
  * @������������ʱ��
  * @��������ʱ���ţ�0 �� 1
  * @����ֵ����
  */
void reset_timer32(uint8_t timer_num)
{
  uint32_t regVal;

  if ( timer_num == 0 )
  {
    regVal = LPC_TMR32B0->TCR;
    regVal |= 0x02;
    LPC_TMR32B0->TCR = regVal;
  }
  else
  {
    regVal = LPC_TMR32B1->TCR;
    regVal |= 0x02;
    LPC_TMR32B1->TCR = regVal;
  }
  return;
}


/**
  * @��������init_timer
  * @��������ʼ����ʱ�������ö�ʱ���������λ��ʱ�����ö�ʱ���ж�����
  * @��������ʱ���źͶ�ʱ�����
  * @����ֵ����
  */
void init_timer32(uint8_t timer_num, uint32_t TimerInterval) 
{
  if ( timer_num == 0 )
  {
    /* ��ΪJTAG�Ͷ�ʱ��CAP/MAT�ܽ��ǻ��ʹ�õ������ʹ���˸�ģ����һЩ I/O �ܽ�������ϸ�����á� */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
    
	/*  Timer0_32 I/O ���� */
	/* Timer0_32 CAP0 */
	LPC_IOCON->PIO1_5 &= ~0x07;	
    LPC_IOCON->PIO1_5 |= 0x02;	
    /* Timer0_32 MAT0 */
	LPC_IOCON->PIO1_6 &= ~0x07;
    LPC_IOCON->PIO1_6 |= 0x02;	
    /* Timer0_32 MAT1 */
	LPC_IOCON->PIO1_7 &= ~0x07;
    LPC_IOCON->PIO1_7 |= 0x02;	
    /* Timer0_32 MAT2 */
	LPC_IOCON->PIO0_1 &= ~0x07;	
    LPC_IOCON->PIO0_1 |= 0x02;	
#ifdef __JTAG_DISABLED
    /* Timer0_32 MAT3 */
	LPC_IOCON->JTAG_TDI_PIO0_11 &= ~0x07;	
    LPC_IOCON->JTAG_TDI_PIO0_11 |= 0x03;	
#endif

    timer32_0_counter = 0;
    LPC_TMR32B0->MR0 = TimerInterval;
//	LPC_TMR32B0->EMR &= ~(0xFF<<4);
//	LPC_TMR32B0->EMR |= ((0x3<<4)|(0x3<<6)|(0x3<<8)|(0x3<<10));	/* MR0/1/2/3 Toggle */
    /* MR0�ϵ��жϺ͸�λ  */
	LPC_TMR32B0->MCR = 3;			

    /* ʹ��TIMER0�ж� */
    NVIC_EnableIRQ(TIMER_32_0_IRQn);
  }
  else if ( timer_num == 1 )
  {
    /* ��ΪJTAG�Ͷ�ʱ��CAP/MAT�ܽ��ǻ��ʹ�õ������ʹ���˸�ģ����һЩ I/O �ܽ�������ϸ�����á� */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);
#ifdef __JTAG_DISABLED
    /*  Timer1_32 I/O ���� */
	/* Timer1_32 CAP0 */
	LPC_IOCON->JTAG_TMS_PIO1_0  &= ~0x07;	
    LPC_IOCON->JTAG_TMS_PIO1_0  |= 0x03;	
    /* Timer1_32 MAT0 */
	LPC_IOCON->JTAG_TDO_PIO1_1  &= ~0x07;	
    LPC_IOCON->JTAG_TDO_PIO1_1  |= 0x03;	
    /* Timer1_32 MAT1 */
	LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~0x07;
    LPC_IOCON->JTAG_nTRST_PIO1_2 |= 0x03;	
    /* Timer1_32 MAT2 */
	LPC_IOCON->ARM_SWDIO_PIO1_3  &= ~0x07;
    LPC_IOCON->ARM_SWDIO_PIO1_3  |= 0x03;	
#endif
    /* Timer0_32 MAT3 */
	LPC_IOCON->PIO1_4 &= ~0x07;
    LPC_IOCON->PIO1_4 |= 0x02;		

    timer32_1_counter = 0;
    LPC_TMR32B1->MR0 = TimerInterval;
//	LPC_TMR32B1->EMR &= ~(0xFF<<4);
//	LPC_TMR32B1->EMR |= ((0x3<<4)|(0x3<<6)|(0x3<<8));	/* MR0/1/2 Toggle */
    	/* MR0�ϵ��жϺ͸�λ  */
	LPC_TMR32B1->MCR = 3;		

    /* ʹ��TIMER1�ж� */
    NVIC_EnableIRQ(TIMER_32_1_IRQn);
  }
  return;
}
/**
  * @}
  */ 

/**
  * @}
  */ 
/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****�ļ�����*******/
