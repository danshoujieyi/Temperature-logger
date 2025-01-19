///******************************************************************
// * 课程：基于NXP LPC1114的嵌入式系统设计
// * 姓名：刘嘉俊
// * 学号：20223004426
// * 任课教师：王庆吉
// * 第五次作业
//******************************************************************/
///******************************************************************
// * 编译环境及版本： Keil MDK5 5.39
// * 编译器版本： ARM Compiler version 5.06（960）
// * 硬件版本： NXP LPC1114 DevKit V5.6
// * 调试器： DAPLink
// * 语言： C语言
// * 文字版本： Chinese GB2312
//******************************************************************/
///* 引入头文件"LPC11xx.h" */
// #include "AD_UART.h"   


// #define R_REFERENCE 10000.0 // 已知参考电阻值，为10kΩ
// #define B 3950 // B 常数，根据 KNTC0603/10KF3950 数据手册填写
// uint16_t adc_value = 0; // 从ADC7 读取的原始值
// double R = 0; // 从ADC7 读取的转换后NTC温度电阻值
// double temperature = 0; // 从NTC温度电阻值计算的温度值


// /******************************************************************
//  * 函数名: TIMER32_0_IRQHandler
//  * 描述:定时器中断处理函数，在定时器0的匹配事件发生时，启动ADC转换，读取ADC7的值
// ******************************************************************/
// void TIMER32_0_IRQHandler(void) {
//     if ((LPC_TMR32B0->IR |= 0x01) == 1) { // 检查MR0中断标志
//         LPC_ADC->CR |= (1 << 24); // 启动ADC转换
// 		LPC_TMR32B0->IR = 0x01; // 清除MR0中断标志
//     }
// }

//   /******************************************************************
//  * 函数名: ADC_IRQHandler
//  * 描述:ADC中断处理函数
//  * 参数: 无
// ******************************************************************/
//  void ADC_IRQHandler(void)
//  {
//      if (LPC_ADC->STAT & (1 << 7)) // 检查AD7是否有转换完成
//      {
// 		while((LPC_ADC->DR[7]&0x80000000)==0);
// 		adc_value=LPC_ADC->DR[7];			//	读取ADC7寄存器的值
// 		adc_value=(adc_value >> 6) & 0x3ff;	//提取10位AD结果
//		
//        uint8_t data_to_send[2]; // 发送数据到串口
//        data_to_send[0] = (adc_value & 0xFF);         // 低位
//        data_to_send[1] = (adc_value >> 8) & 0xFF;   // 高位
//        UARTSend(data_to_send, 2); // 发送两个字节
// 		UARTSend("\r\n", 2);  // 添加回车换行
// 		R = (adc_value * 10000) / (1024 - adc_value); // R光敏电阻阻值=ADC7Value*10000/(1024-ADC7Value)
// 		temperature = calculate_temperature(R);
// 		send_temperature(temperature);
// 		UARTSend("光敏电阻阻值：", 14); // 回车换行
// 		send_resistance(R);
// 		UARTSend("\r\n", 2);  // 添加回车换行
//      }
//  }

// /******************************************************************
//  * 函数名: UARTInit
//  * 描述: 初始化 UART0 端口，设置选中引脚、时钟，校验、停止位、FIFO、等等。
//  * 参数: UART 波特率
//  * 返回值: 无
// ******************************************************************/
//  void UARTInit(uint32_t baudrate)
//  {
//  	uint32_t Fdiv; // 分频值
//  	uint32_t regVal = regVal; // 临时变量
//  	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);  // 使能 IOCON 模块的时钟
//  	LPC_IOCON->PIO1_6 &= ~0x07;  // UART I/O 配置，设置 PIO1_6 为 UART RXD 
//  	LPC_IOCON->PIO1_6 |= 0x01; 
//  	LPC_IOCON->PIO1_7 &= ~0x07; // 设置 PIO1_7 为 UART TXD 
//  	LPC_IOCON->PIO1_7 |= 0x01; 
//  	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 16); // 关闭 IOCON 模块的时钟
//  	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12); // 使能 UART 时钟
//  	LPC_SYSCON->UARTCLKDIV = 0x1; // 分频值 1
//  	LPC_UART->LCR = 0x83; // 设置 UART 线控制寄存器 (LCR)，配置为 8 位数据，奇校验位，1 停止位 	
//  	Fdiv = (SystemCoreClock / 16) / baudrate; // 计算波特率分频值
//  	LPC_UART->DLM = Fdiv / 256; // 设置波特率低字节和高字节
//  	LPC_UART->DLL = Fdiv % 256; 
//  	LPC_UART->LCR = 0x03; // 重置 LCR，禁用 DLAB 
//  	LPC_UART->FCR = 0x07; // 使能并复位 TX 和 RX FIFO	
//  	regVal = LPC_UART->LSR; // 读取并清除行状态寄存器 (LSR)
//  	// 确保正常开始，TX 和 RX FIFO 中没有数据
//  	while ((LPC_UART->LSR & (0x20 | 0x40)) != (0x20 | 0x40));
//  	while (LPC_UART->LSR & 0x01)
//  	{
//  		regVal = LPC_UART->RBR; // 从 RX FIFO 中转储数据
//  	}
//  }

// /******************************************************************
//  * 函数名: UARTSend
//  * 描述: 根据数据长度发送一串数据到 UART 0 端口。
//  * 参数: buffer pointer, and data length
//  * 返回值: 无
// ******************************************************************/
//  void UARTSend(uint8_t *BufferPtr, uint32_t Length)
//  {
//  	while (Length != 0) // 判断数据长度，不为0则发送数据
//  	{
//  		while (!(LPC_UART->LSR & (1 << 5))); // 等待直到发送数据寄存器空
//  		LPC_UART->THR = *BufferPtr; // 发送当前字节
//  		BufferPtr++; // 移动到下一个字节
//  		Length--; // 递减数据长度
//  	}
//  }

// /******************************************************************
//  * 函数名: 延时函数
//  * 描述: 毫秒级延时函数。
//  * 参数: 延时时间
// ******************************************************************/
//  void delay_ms(uint32_t a) // 1ms延时函数
//  {
// 	 uint32_t i;	  // 循环计数
// 	 while (--a != 0) // 直到延时时间为零
// 	 {
// 		 for (i = 0; i < 5500; i++); // 大约延时的循环1ms
// 	 }
//  }

// /******************************************************************
//  * 函数名: ADC7_Init
//  * 描述: ADC7 初始化函数，配置 ADC 控制寄存器，使能 ADC 电源和时钟。
//  * 参数: 无
// ******************************************************************/
//void ADC7_Init(void)
//{
//    LPC_SYSCON->PDRUNCFG &= ~(1UL << 4);		// 使能ADC电源
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 13);   // 使能ADC时钟，以便ADC能够进行转换
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);   // 使能IOCON模块时钟，以配置相应的引脚
//    LPC_IOCON->PIO1_11 &= ~(0x01 << 7);       // 清除P1.11的功能设置，为设置AD7做准备
//    LPC_IOCON->PIO1_11 |= 0x01;                // 将P1.11配置为ADC输入通道AD7
//    LPC_IOCON->PIO1_11 &= ~(3 << 3);           // 清除相关的功能配置，确保无其他功能干扰
//    LPC_IOCON->PIO1_11 &= ~(1 << 7);           // 再次清除与引脚相关的其他配置
//    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 16);  	// 关闭IOCON模块的时钟，节省功耗

//    // 配置ADC控制寄存器（CR）
//    LPC_ADC->CR = (1UL << 7) |        // 使能AD7通道，以便读取该通道的电压
//                  (23UL << 8) |       // 设置ADC时钟，配置为2MHz（实际ADC输入为48MHz时，使用分频50/(24+1)）
//                  (0 << 16) |        // 选择软件控制模式来启动ADC转换
//                  (0 << 17) |        // 设置转换时钟为11时钟周期，确保10位有效精度
//                  (0 << 24) |        // 关闭ADC转换，等到32位定时器0的匹配事件触发启动
//                  (0 << 27);         // 预留的无效设置，不影响功能
//                  
//    LPC_ADC->INTEN = (1UL << 8);       // 使能AD7通道的中断，允许在ADC转换完成时触发中断
//    NVIC_EnableIRQ(ADC_IRQn);          // 启用ADC中断，允许中断控制器响应ADC转换完成事件
//}

// /******************************************************************
//  * 函数名: Read_AD7
//  * 描述: 读取端口ADC7的值。
//  * 返回值: 返回电压值ADC_Data
// ******************************************************************/
// uint32_t Read_AD7(void)
// {
// 	uint32_t ADC_Data;
// 	LPC_ADC->CR|=(1<<24);			//启动ADC
// 	while((LPC_ADC->DR[7]&0x80000000)==0);
// 	LPC_ADC->CR|=(1<<24);			//使用第二次转换，丢弃第一次
// 	while((LPC_ADC->DR[7]&0x80000000)==0);
// 	ADC_Data=LPC_ADC->DR[7];			//	读取ADC7寄存器的值
// 	ADC_Data=(ADC_Data>>6)&0x3ff;	//提取10位AD结果
// 	return(ADC_Data);
// }

// /******************************************************************
//  * 函数名: TMR32B0_Init
//  * 描述:初始化32位定时器0，开启定时器匹配中断。
// ******************************************************************/
// void TMR32B0_Init(void) {
//     LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 9); // 使能定时器0时钟
// 	LPC_TMR32B0->IR = 0x1F; // 清除所有中断标志
//     LPC_TMR32B0->PR = 0; // 不分频
// 	LPC_TMR32B0->MCR = 3; // 当匹配MR0时，重置定时器和产生中断
//     LPC_TMR32B0->MR0 = SystemCoreClock - 1; // 设置匹配寄存器为系统时钟频率 - 1 (1秒)
//     LPC_TMR32B0->TCR = 0x01; // 启动定时器
// 	NVIC_EnableIRQ(TIMER_32_0_IRQn); // 使能定时器0中断
// }

// /******************************************************************
//  * 函数名: send_resistance
//  * 描述:发送电阻值到串口
//  * 参数: resistance电阻阻值
// ******************************************************************/
// void send_resistance(double resistance) {
//    char res_str[32];  // 用于存储转换后的字符串，保证足够大以容纳浮点数和标识符
//    sprintf(res_str, "%.2f Ω\r\n", resistance); // 格式化字符串，保留两位小数
//    // 通过 UART 发送字符串
//    UARTSend((uint8_t *)res_str, strlen(res_str));  // 发送电阻字符串
//}

//  /******************************************************************
//  * 函数名: calculate_temperature
//  * 描述:将温度电阻阻值转换为温度值摄氏度
//  * 参数: resistance电阻阻值
// ******************************************************************/
// double calculate_temperature(double resistance) {
//   // 3950是NTC的B值，298.15是25°C的绝对温度（K）
//   temperature = (1 / (log(resistance / R_REFERENCE) / 3950 + (1 / 298.15))) - 273.15; // 将阻值转换为温度，摄氏度
//   return temperature; // 返回温度值（摄氏度）
// }

// /******************************************************************
//  * 函数名: send_temperature
//  * 描述:发送温度值到串口（摄氏度）
//  * 参数: temperature温度值
// ******************************************************************/
// void send_temperature(float temperature) {
//     char temp_str[16];  // 用于存储转换后的字符串
//     sprintf(temp_str, "%.2f", temperature); // 将浮点数转换为字符串，保留两位小数
//     // 发送字符串到串口
//     UARTSend((uint8_t *)temp_str, strlen(temp_str));  // 发送温度字符串
//     UARTSend((uint8_t *)"摄氏度\r\n", 8);  // 添加回车换行
// }
// 
// 
///*第四次作业*/ 
// 
// // LED 初始化函数
//void LED_init(void) 
//{
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // 使能 GPIO 模块的时钟
//    LPC_GPIO1->DIR |= (1UL << 9); // 设置 GPIO1.9 为输出模式
//    LPC_GPIO1->DATA &= ~(1UL << 9); // 将 GPIO1.9 初始化为低电平（点亮 LED）
//}

//// LED 闪烁函数
//void LED_Toggle(void) 
//{
//    LPC_GPIO1->DATA ^= (1UL << 9); // 通过异或操作翻转 GPIO1.9 的输出电平
//}

//// 16 位定时器初始化函数
//void TMR16B1_Init(void) 
//{
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8); // 使能 16 位定时器的时钟
//    LPC_TMR16B1->IR = 0x1F; // 清除所有定时器中断标志
//    LPC_TMR16B1->PR = 1000 - 1; // 设置定时器分频系数为 1000，实际分频为 1000
//    LPC_TMR16B1->MCR = 3; // 设置：匹配后复位 TC 并产生中断
//    LPC_TMR16B1->MR0 = SystemCoreClock / 1000; // 配置匹配寄存器，使定时器每 1ms 产生一个匹配
//    LPC_TMR16B1->TCR = 0x01; // 启动定时器
//    NVIC_EnableIRQ(TIMER_16_1_IRQn); // 使能 16 位定时器1的中断
//}

//// 定时器中断处理函数
//void TIMER16_1_IRQHandler(void) 
//{
//    // 检查定时器匹配中断
//    if ((LPC_TMR16B1->IR & 0x01) == 1) // 使用按位与操作检查是否为匹配中断
//    {
//        LED_Toggle(); // 调用 LED 闪烁函数
//        LPC_TMR16B1->IR |= 0x01; // 清除匹配中断标志
//    }
//}

//// 16 位定时器初始化函数
//void TMR16B1_COUNT_Init(void) 
//{
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8) | (1UL << 16); // 使能 16 位定时器和 IOCON 的时钟
//    LPC_IOCON->PIO1_9 |= 0x01; // 配置PIO1.9
//    LPC_TMR16B1->PWMC = 0x00; // 清除 PWM 匹配寄存器标志
//    LPC_TMR16B1->PR = 1000 - 1; // 设置定时器分频系数为 1000
//    LPC_TMR16B1->MCR = 3; // 设置匹配后复位 TC 并生成中断
//    LPC_TMR16B1->MR0 = SystemCoreClock / 1000; // 将匹配寄存器 MR0 设置为 1ms
//    LPC_TMR16B1->TCR = 0x01; // 使能 16 位定时器
//    LPC_TMR16B1->EMR |= (3UL << 4); // 设置 PWM 输出模式
//}


//#define MAX_BRIGHTNESS  100 // 最大亮度（占空比100%）
//#define MIN_BRIGHTNESS  0   // 最小亮度（占空比0%）
//#define BRIGHTNESS_STEP 1   // 亮度增减步长（1%）

///* 初始化 LED 灯 */
//void InitializeLED(void)   
//{
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // 使能 GPIO 时钟
//    LPC_GPIO1->DIR |= (1UL << 9); // 设置 PIO1_9 为输出
//}

///* 初始化 16 位定时器1为 PWM 模式 */
//void InitPWM16BitTimer(void)  
//{
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8) | (1UL << 16); // 使能 16 位定时器1 和 IOCON 的时钟
//    LPC_IOCON->PIO1_9 |= 0x01;  // 将 PIO1_9 复用为 MAT0（PWM 功能）
//    LPC_TMR16B1->TCR = 0x02;  // 复位 16 位定时器1
//    LPC_TMR16B1->PR = 0;  // 无分频, 设置为 1
//    LPC_TMR16B1->PWMC = 0x01;  // 配置 MAT0 为 PWM 模式
//    LPC_TMR16B1->MCR = (0x02 << 9);  // 设置匹配后 TC 复位且不中断
//    LPC_TMR16B1->MR3 = SystemCoreClock / 1000;  // 设置 MR3 为 1ms
//    LPC_TMR16B1->MR0 = LPC_TMR16B1->MR3; // MR0 用于 PWM 输出
//    LPC_TMR16B1->TCR = 0x01;  // 使能 16 位定时器1
//}

///* 初始化 32 位定时器0 */
//void Init32BitTimer(void)  
//{  
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 9); // 使能 32 位定时器0 时钟
//    LPC_TMR32B0->IR = 0x1F; // 清除所有中断标志
//    LPC_TMR32B0->PR = 0; // 无分频, 设置为 1
//    LPC_TMR32B0->MCR = 3; // 匹配后复位 TC 并产生中断
//    LPC_TMR32B0->MR0 = SystemCoreClock / 100; // 设置 MR0 以产生 0.01s 中断
//    LPC_TMR32B0->TCR = 0x01; // 使能 32 位定时器0
//    NVIC_EnableIRQ(TIMER_32_0_IRQn); // 注册并使能 32 位定时器0 中断
//}

//volatile uint8_t brightnessLevel = 0; // 当前亮度级别
//volatile uint8_t isIncreasing = 1; // 指示占空比是否在增加

///* 32 位定时器0的中断服务程序 */
//void TIMER32_0_IRQHandler(void)
//{
//    LPC_TMR32B0->IR = 0x1F; // 清除所有中断标志

//    // 更新 PWM 占空比
//    if (isIncreasing) {
//        brightnessLevel += BRIGHTNESS_STEP; // 增加亮度
//        if (brightnessLevel >= MAX_BRIGHTNESS) {
//            brightnessLevel = MAX_BRIGHTNESS; // 达到最大值
//            isIncreasing = 0; // 切换为减小亮度
//        }
//    } else {
//        brightnessLevel -= BRIGHTNESS_STEP; // 减小亮度
//        if (brightnessLevel <= MIN_BRIGHTNESS) {
//            brightnessLevel = MIN_BRIGHTNESS; // 达到最小值
//            isIncreasing = 1; // 切换为增加亮度
//        }
//    }
//    
//    LPC_TMR16B1->MR0 = (brightnessLevel * LPC_TMR16B1->MR3) / 100; // 更新 PWM 输出
//}




//// 第三次作业
//#define DEBOUNCE_TIME 50 // 消抖时间，单位是毫秒
//#define FREQUENCY_0_5HZ (2000/2) // 0.5Hz 对应的周期（毫秒）,除以2表示亮灭持续时间各占一半
//#define FREQUENCY_1HZ (1000/2) // 1Hz 对应的周期（毫秒）,除以2表示亮灭持续时间各占一半
//#define FREQUENCY_2HZ (500/2) // 2Hz 对应的周期（毫秒）,除以2表示亮灭持续时间各占一半
//volatile uint8_t ledState = 0; // LED 状态变量，0: 关，1: 开
//int blinkFrequency = FREQUENCY_0_5HZ; // 默认闪烁频率为 0.5Hz
// 
///* 翻转RGB_Blue蓝灯 */
//void RGB_Blue_Toggle(void)
//{
//LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); /* GPIO 时钟使能 */
//LPC_GPIO2->DIR |= (1UL << 10); /*配置GPIO2_10为输出模式 */
//LPC_GPIO2->DATA  ^=  (1UL <<10); /* LED 闪烁切换 */
//}
///* 翻转RGB_Green绿灯 */
//void RGB_Green_Toggle(void)
//{
//LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); /* GPIO 时钟使能 */
//LPC_GPIO2->DIR |= (1UL << 8); /*配置GPIO2_8为输出模式 */
//LPC_GPIO2->DATA ^= (1UL <<8);/* LED 闪烁切换 */
//}
//void Key_Init(void) {
//    // 使能 IOCON 相关时钟
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 16); /* IOCON 时钟使能 */
//    // 设置 PIO3_5 为 GPIO 功能
//    LPC_IOCON->PIO3_5 &= ~0x3F; 
//    LPC_IOCON->PIO3_5 |= (1 << 4 | 1 << 5); // 配置 P3.5 为 GPIO 功能，上拉电阻，使能滞后模式
//    LPC_GPIO3->DIR &= ~(1UL << 5); // 将 P3.5 设置为输入（按键）
//    // 设置 PIO1_4 为 GPIO 功能
//    LPC_IOCON->PIO1_4 &= ~0x3F; 
//    LPC_IOCON->PIO1_4 |= (1 << 4 | 1 << 5); // 配置 P1.4 为 GPIO 功能，上拉电阻，使能滞后模式
//    LPC_GPIO1->DIR &= ~(1UL << 4); // 将 P1.4 设置为输入（按键）
//    // GPIO3 中断初始化
//    LPC_GPIO3->IS &= ~(1UL << 5); // 清除 P3.5 中断状态选择（设置为边缘触发）
//    LPC_GPIO3->IBE &= ~(1UL << 5); // 禁用双边沿触发
//    LPC_GPIO3->IEV &= ~(1UL << 5); /* 设置为下降沿触发 */
//    LPC_GPIO3->IE |= (1UL << 5); /* 使能 GPIO3 的 P3.5 中断功能 */
//    NVIC_EnableIRQ(EINT3_IRQn); /* 使能 EINT3 中断 */
//    NVIC_SetPriority(EINT3_IRQn, 1); // 设置 EINT3 中断优先级为 1
//    // GPIO1 中断初始化
//    LPC_GPIO1->IS &= ~(1UL << 4); // 清除 P1.4 中断状态选择（设置为边缘触发）
//    LPC_GPIO1->IBE &= ~(1UL << 4); // 禁用双边沿触发
//    LPC_GPIO1->IEV &= ~(1UL << 4); /* 设置为下降沿触发 */
//    LPC_GPIO1->IE |= (1UL << 4); /* 使能 GPIO1 的 P1.4 中断功能 */
//    NVIC_EnableIRQ(EINT1_IRQn); /* 使能 EINT1 中断 */
//    NVIC_SetPriority(EINT1_IRQn, 2); // 设置 EINT1 中断优先级为 2
//}
//void PIOINT3_IRQHandler(void)
//{
//    RGB_Blue_Toggle(); // 翻转 RGB_Blue 蓝灯，用于指示是否进入了 GPIO3 中断
//    uint32_t regVal = 0; // 定义变量用于存储按键状态
//    // 检查 PIO3_5（按键）是否被按下
//    if ((LPC_GPIO3->DATA & (1 << 5)) == 0) 
//    {
//        delay_ms(DEBOUNCE_TIME); // 调用消抖延时函数，避免抖动影响
//        // 等待按键释放
//        while ((LPC_GPIO3->DATA & (1 << 5)) == 0); 
//        
//        // 检查中断状态寄存器，确定是否是有效的按键事件
//        if (LPC_GPIO3->MIS & (0x1 << 5)) 
//        {
//            regVal = 1; // 设置标志，表示按键被有效按下
//        }
//    }
//    
//    // 如果有效按键事件被检测到
//    if (regVal)
//    {
//        // 切换闪烁频率
//        if (blinkFrequency == FREQUENCY_0_5HZ) {
//            blinkFrequency = FREQUENCY_1HZ; // 变为 1Hz
//        } 
//        else if (blinkFrequency == FREQUENCY_1HZ) {
//            blinkFrequency = FREQUENCY_0_5HZ; // 恢复为 0.5Hz
//        } 
//        else {
//            blinkFrequency = FREQUENCY_0_5HZ; // 当为 2Hz 时自动恢复为 0.5Hz
//        }
//    }
//    // 清除 GPIO3 的中断标志，以便可以响应下一次中断
//    LPC_GPIO3->IC |= (0x1 << 5);
//}
//void PIOINT1_IRQHandler(void)
//{
//    RGB_Green_Toggle(); // 翻转 RGB_Green 绿灯，用于指示是否进入了 GPIO1 中断
//    uint32_t regVal = 0; // 定义变量用于存储按键状态
//    // 检查 PIO1_4（WEAKUP 按键）是否被按下
//    if ((LPC_GPIO1->DATA & (1 << 4)) == 0) 
//    {
//        delay_ms(DEBOUNCE_TIME); // 调用消抖延时函数，去除因机械按键抖动引起的多次触发
//        // 等待按键释放
//        while ((LPC_GPIO1->DATA & (1 << 4)) == 0); 
//        
//        // 检查中断状态寄存器，确认是否是有效的按键事件
//        if (LPC_GPIO1->MIS & (0x1 << 4)) 
//        {
//            regVal = 1; // 设置标志，表示按键被有效按下
//        }
//    }
//    
//    // 如果有效按键事件被检测到
//    if (regVal)
//    {
//        // 切换闪烁频率
//        if (blinkFrequency == FREQUENCY_0_5HZ) {
//            blinkFrequency = FREQUENCY_2HZ; // 将闪烁频率改为 2Hz
//        } 
//        else if (blinkFrequency == FREQUENCY_2HZ) {
//            blinkFrequency = FREQUENCY_0_5HZ; // 恢复到 0.5Hz
//        } 
//        else {
//            blinkFrequency = FREQUENCY_0_5HZ; // 当为 1Hz 时自动恢复为 0.5Hz
//        }
//    }
//    // 清除 GPIO1 的中断标志，以便可以响应下一次中断
//    LPC_GPIO1->IC |= (0x1 << 4);
//}
//// SysTick 中断处理函数
//void SysTick_Handler(void) {
//    static uint32_t ledCounter = 0; // LED 计数器
//    ledCounter++;
//    if (ledCounter >= blinkFrequency) { // 如果计数达到设置的频率
//     LED_Toggle(); // 翻转GPIO1_9，改变灯的状态
//        ledCounter = 0; // 重置计数器
//    }
//}
//int main (void) {
//    /* 配置系统节拍定时器，每1ms触发一次系统节拍中断 */
//    SysTick_Config(SystemCoreClock / 1000);  /* 定时器以1ms为周期中断一次 */
//    LED_Init();  /* 初始化LED */
//   Key_Init();  /* 初始化Key */
//    while (1) 
//{ 
//    }
//}
