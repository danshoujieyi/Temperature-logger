#ifndef __DELAY_H
#define __DELAY_H
#include "LPC11xx.h"

void T16B0_init(void);
void T16B0_delay_ms(uint16_t ms);
void T16B0_delay_us(uint16_t us);

#endif

