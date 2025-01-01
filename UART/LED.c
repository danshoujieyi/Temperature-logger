#include "LED.h"
#include "Delay.h"

void RGB_LED_Init(void)
{
   LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); /* GPIO Ê±ÖÓÊ¹ÄÜ */
   LPC_GPIO1->DIR |= (1UL << 9); /*½« GPIO1_9 ×÷ÎªÊä³ö¿Ú*/
   LPC_GPIO2->DIR |= (1UL << 8); /*ÅäÖÃGPIO2_8ÎªÊä³öÄ£Ê½ */  // RGB_Green
   LPC_GPIO2->DIR |= (1UL << 9); /*ÅäÖÃGPIO2_8ÎªÊä³öÄ£Ê½ */  // RGB_Red
   LPC_GPIO2->DIR |= (1UL << 10); /*ÅäÖÃGPIO2_10ÎªÊä³öÄ£Ê½ */ // RGB_Blue
}


void LED_Toggle(void)
{
	LPC_GPIO1->DATA ^= (1UL <<9);/* LED ÉÁË¸ÇÐ»» */
	T16B0_delay_ms(50);
}

/* ·­×ªRGB_BlueÀ¶µÆ */
void RGB_Blue_Toggle(void)
{
	LPC_GPIO2->DATA  ^=  (1UL <<10); /* LED ÉÁË¸ÇÐ»» */
	T16B0_delay_ms(50);
}
/* ·­×ªRGB_GreenÂÌµÆ */
void RGB_Green_Toggle(void)
{
	LPC_GPIO2->DATA ^= (1UL <<8);/* LED ÉÁË¸ÇÐ»» */
	T16B0_delay_ms(50);
}

/* ·­×ªRGB_GreenÂÌµÆ */
void RGB_Red_Toggle(void)
{
	LPC_GPIO2->DATA ^= (1UL <<9);/* LED ÉÁË¸ÇÐ»» */
	T16B0_delay_ms(50);
}
