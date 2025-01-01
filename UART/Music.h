#ifndef __MUSIC_H
#define __MUSIC_H

#include "LPC11xx.h"
#include "Delay.h"

void T16B1_PWM_init(void);
void PassiveBuzzer_Init(void);
void PassiveBuzzer_OFF(void);
void PassiveBuzzer_ON(void);
void PassiveBuzzer_Set_Freq_Duty(int freq, int duty);
void MUSIC_Brave_Lone(void);
void MUSIC_Two_Tigers(void);

#endif
