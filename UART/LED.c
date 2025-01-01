#include "LED.h"
#include "Delay.h"

void RGB_LED_Init(void)
{
   LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); /* GPIO ʱ��ʹ�� */
   LPC_GPIO1->DIR |= (1UL << 9); /*�� GPIO1_9 ��Ϊ�����*/
   LPC_GPIO2->DIR |= (1UL << 8); /*����GPIO2_8Ϊ���ģʽ */  // RGB_Green
   LPC_GPIO2->DIR |= (1UL << 9); /*����GPIO2_8Ϊ���ģʽ */  // RGB_Red
   LPC_GPIO2->DIR |= (1UL << 10); /*����GPIO2_10Ϊ���ģʽ */ // RGB_Blue
}


void LED_Toggle(void)
{
	LPC_GPIO1->DATA ^= (1UL <<9);/* LED ��˸�л� */
	T16B0_delay_ms(50);
}

/* ��תRGB_Blue���� */
void RGB_Blue_Toggle(void)
{
	LPC_GPIO2->DATA  ^=  (1UL <<10); /* LED ��˸�л� */
	T16B0_delay_ms(50);
}
/* ��תRGB_Green�̵� */
void RGB_Green_Toggle(void)
{
	LPC_GPIO2->DATA ^= (1UL <<8);/* LED ��˸�л� */
	T16B0_delay_ms(50);
}

/* ��תRGB_Green�̵� */
void RGB_Red_Toggle(void)
{
	LPC_GPIO2->DATA ^= (1UL <<9);/* LED ��˸�л� */
	T16B0_delay_ms(50);
}
