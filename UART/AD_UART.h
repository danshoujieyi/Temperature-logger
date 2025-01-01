//#ifndef __AD_UART_H__
//#define __AD_UART_H__

//// #include "LPC11xx.h"   
//// #include <math.h> // 用于计算log进行线性插值求解热敏电阻温度值
//// #include <stdio.h>  // 用于sprintf
//// #include <string.h> // 用于strlen

//// 自定义函数头，功能简单介绍
//// 第五次作业
//void UARTInit(uint32_t baudrate); //  初始化 UART，配置波特率以及相关寄存器设置。
//void UARTSend(uint8_t *BufferPtr, uint32_t Length); //  发送指定长度的数据至 UART，确保数据的顺序和完整性。
//void delay_ms(uint32_t a); //  实现毫秒级延时，用于控制时间间隔。
//void ADC7_Init(void); //  配置 ADC7 通道的软件触发设置，确保 ADC 可以成功进行模拟信号读取。
//uint32_t Read_AD7(void); //  获取 ADC7 的当前读数，返回10位的数字化结果。这里使用ADC7的中断读取，没有使用这个直接读取函数
//void TMR32B0_Init(void); //  设置32位定时器0的匹配中断配置及中断，使能定时器用于定时事件。
//void TIMER32_0_IRQHandler(void); //  处理定时器0中断，执行相应操作，例如启动ADC转换。
//void send_resistance(double resistance); //  将计算出的电阻值通过 UART 发送到串口监控。
//double calculate_temperature(double resistance); //  使用电阻值计算温度，返回摄氏度值。
//void send_temperature(float temperature); //  将温度值通过 UART 发送，以便实时监控。
//void ADC_IRQHandler(void); //  在 ADC 转换完成时读取值，并处理后续操作，发送值到串口。

//// 第四次作业
//void LED_Toggle(void); // LED 闪烁函数
//void TMR16B1_Init(void); // 16 位定时器初始化函数
//void TIMER16_1_IRQHandler(void); // 定时器中断处理函数
//void TMR16B1_COUNT_Init(void); // 16 位定时器初始化函数

//// 第三次作业
//void RGB_Blue_Toggle(void); /* 翻转RGB_Blue蓝灯 */
//void RGB_Green_Toggle(void); /* 翻转RGB_Green绿灯 */
//void Key_Init(void);
//void PIOINT3_IRQHandler(void);
//void PIOINT1_IRQHandler(void);
//void SysTick_Handler(void); // SysTick 中断处理函数

//#endif 
