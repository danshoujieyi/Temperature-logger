#include "LPC11xx.h"
#include "Music.h"
#include "I2C.h"
#include "DS1307.h"
#include "LM75BD.h"
#include "OLED.h"
#include "UART.h"
#include "DS18B20.h"
#include "SSPI1.h"
#include "XT25F02.h"
#include "Delay.h"
#include "LED.h"

#include "stdio.h"  // 使用串口重定向，把UART_Send（）函数定向给stdio.h库中的printf，方便使用printf进行串口调试
float Temp_LM75BD = 0;
uint8_t Temp_Buf[8] = {0};

uint8_t Date[10] = {0};
uint8_t Time_Data[10] = {0};
uint8_t Week[1] = {0};
uint8_t Time[7] = {0x50, 0x13, 0x15, 0x05, 0x27, 0x12, 0x24}; // 秒，分，时，星期，日，月，年
uint8_t data[7] = {0};

uint8_t Write_Addr[16] = {0}; //写
uint8_t Read_Addr[16] = {0};//读

uint8_t Music_Flag = 0;

void Menu(void)
{	
    /*OLED显示*/
	// OLED_Clear();
	OLED_ShowString(1, 4, "LiuJiajun ! ");	//1行3列显示字符串HelloWorld!
	OLED_ShowString(2, 1, "DATE: ");
    OLED_ShowChar(2, 7, Date[0]);
	OLED_ShowChar(2, 8, Date[1]);
	OLED_ShowChar(2, 9, Date[2]);
	OLED_ShowChar(2, 10, Date[3]);
	OLED_ShowChar(2, 11, Date[4]);
	OLED_ShowChar(2, 12, Date[5]);
	OLED_ShowChar(2, 13, Date[6]);
	OLED_ShowChar(2, 14, Date[7]);
	OLED_ShowChar(2, 15, Date[8]);
	OLED_ShowChar(2, 16, Date[9]);	
	OLED_ShowString(3, 1, "TIME:  ");
    OLED_ShowChar(3, 8, Time_Data[0]);
	OLED_ShowChar(3, 9, Time_Data[1]);
	OLED_ShowChar(3, 10, Time_Data[2]);
	OLED_ShowChar(3, 11, Time_Data[3]);
	OLED_ShowChar(3, 12, Time_Data[4]);
	OLED_ShowChar(3, 13, Time_Data[5]);
	OLED_ShowChar(3, 14, Time_Data[6]);
	OLED_ShowChar(3, 15, Time_Data[7]);
	OLED_ShowString(4, 1, "Temp:  ");
    OLED_ShowChar(4, 8, Temp_Buf[0]);
	OLED_ShowChar(4, 9, Temp_Buf[1]);
	OLED_ShowChar(4, 10, Temp_Buf[2]);
	OLED_ShowChar(4, 11, Temp_Buf[3]);
	OLED_ShowChar(4, 12, Temp_Buf[4]);
	OLED_ShowChar(4, 13, Temp_Buf[5]);
	OLED_ShowString(4, 15, "C");
}


void Temperature_Judgment(float T)
{
	if (T>28){
		PassiveBuzzer_ON();
		LPC_GPIO2->DATA &= ~(1UL << 10); // 将对应位设置为高电平，点亮 LED
		LPC_GPIO2->DATA &= ~(1UL << 9); // 将对应位设置为高电平，点亮 LED
		LPC_GPIO2->DATA &= ~(1UL << 8); // 将对应位设置为高电平，点亮 LED
		LPC_GPIO1->DATA &= ~(1UL << 10); // 将对应位设置为高电平，点亮 LED
        
	}
	else if(0< T <=10){
		LPC_GPIO2->DATA |= (1UL << 10); // 将对应位设置为高电平，点亮 LED
		LPC_GPIO2->DATA |= (1UL << 9); // 将对应位设置为高电平，点亮 LED
		// LPC_GPIO2->DATA |= (1UL << 8); // 将对应位设置为高电平，点亮 LED
		PassiveBuzzer_OFF();
		RGB_Green_Toggle();
	}
	else if(10< T <=20){
		// LPC_GPIO2->DATA |= (1UL << 10); // 将对应位设置为高电平，点亮 LED
		LPC_GPIO2->DATA |= (1UL << 9); // 将对应位设置为高电平，点亮 LED
		LPC_GPIO2->DATA |= (1UL << 8); // 将对应位设置为高电平，点亮 LED
		PassiveBuzzer_OFF();
		RGB_Blue_Toggle();
	}
	else if(20< T <=30){
		LPC_GPIO2->DATA |= (1UL << 10); // 将对应位设置为高电平，点亮 LED
		// LPC_GPIO2->DATA |= (1UL << 9); // 将对应位设置为高电平，点亮 LED
		LPC_GPIO2->DATA |= (1UL << 8); // 将对应位设置为高电平，点亮 LED
		PassiveBuzzer_OFF();
		RGB_Red_Toggle();
	}
}

/******************************************************************
 * 函数名: 
 * 描述: 
 * 参数: 
******************************************************************/
void Transfor(uint8_t *Temp_Str, float T) {
    sprintf((char *)Temp_Str, "%.3f", T); // 将浮点数转换为字符串，保留三位小数
}

float MedianFilter(void) {
    float measurements[7];
    float temp;
    // 进行7次温度测量
    for (unsigned int i = 0; i < 7; i++) {
        measurements[i] = Read_Temp_LM75BD();
    }
    // 冒泡排序，找出中位数
    for (unsigned int i = 0; i < 7 - 1; i++) {
        for (unsigned int j = 0; j < 7 - i - 1; j++) {
            if (measurements[j] > measurements[j + 1]) {
                // 交换
                temp = measurements[j];
                measurements[j] = measurements[j + 1];
                measurements[j + 1] = temp;
            }
        }
    }
    // 去掉最大值和最小值
    float sum = 0;
    for (unsigned int i = 1; i < 7 - 1; i++) { // 从1到N-2，即中间5个数
        sum += measurements[i];
    }
    // 计算平均值
    return (sum/(7 - 2)); // 去掉2个值，所以用(N - 2)
}

void UART_Send_Date(void)
{	
	UART_Send("Date: ",6);
	UART_Send(Date,10);
	UART_Send(" \n",2);
	UART_Send("Time: ",6);
	UART_Send(Time_Data,8);
	UART_Send(" \n",2);
	UART_Send("Week: ",6);
	UART_Send(Week,1);
	UART_Send(" \n",2);
}

/******************************************************************
 * 函数名: TMR32B0_Init
 * 描述:初始化32位定时器0，开启定时器匹配中断。
******************************************************************/
void TMR32B0_Init(void) {
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 9); // 使能定时器0时钟
	LPC_TMR32B0->IR = 0x1F; // 清除所有中断标志
    LPC_TMR32B0->PR = 0; // 不分频
	LPC_TMR32B0->MCR = 3; // 当匹配MR0时，重置定时器和产生中断
    LPC_TMR32B0->MR0 = SystemCoreClock - 1; // 设置匹配寄存器为系统时钟频率-1(1秒)
    LPC_TMR32B0->TCR = 0x01; // 启动定时器
	NVIC_EnableIRQ(TIMER_32_0_IRQn); // 使能定时器0中断
}

/******************************************************************
 * 函数名: TIMER32_0_IRQHandler
 * 描述:定时器中断处理函数，在定时器0的匹配事件发生时，启动ADC转换，读取ADC7的值
******************************************************************/
void TIMER32_0_IRQHandler(void) {
    if ((LPC_TMR32B0->IR |= 0x01) == 1) { // 检查MR0中断标志

		SPI1_Read_FLASH(Temp_Buf,8);
		
		printf("Hainan University\n");
		printf("Teacher: Wang Qingji\n");		
		printf("Liu Jiajun\n");
        printf("20223004426\n");		
		DS1307_Read();
		Temp_LM75BD = MedianFilter();
		Transfor(Temp_Buf,Temp_LM75BD);		
		UART_Send_Date();
		printf("Temperature: %s\n",Temp_Buf);
		printf(" \n");
		Menu();
		Temperature_Judgment(Temp_LM75BD);
		
		XT25_EraseSector();//芯片擦除
        SPI1_Write_FLASH(Temp_Buf,8); //  发送温度 以转换好的数组的形式发送 到xt52

		LPC_TMR32B0->IR = 0x01; // 清除MR0中断标志
    }
}


/**********************************************/
/*   主函数  */
/**********************************************/
int main()
{
	SystemInit();   // 系统时钟初始化 
	I2C_Init(1);  // IIC初始化--模式:快速+I2C通信 
	SSPI1_Init();
	UART_Init(115200);  // 把串口波特率配置为9600
    T16B1_PWM_init();
	T16B0_init();
	TMR32B0_Init();  //中断子程序
	RGB_LED_Init();
	 // DS1307Init(); 	// 第一次烧录时调用，用于校准时间
	DS1307_Read();
	SPI1_Read_FLASH(Temp_Buf,8);
	OLED_Init();
	OLED_Clear();
	DS18B20_Init();
    PassiveBuzzer_Init();
	T16B0_delay_ms(200);  // 初始化延时----等待相关器件配置完成
	Read_Temp_LM75BD();  //进行一次读取(过滤第一个数据)--第一次读取的数据温度不准确
    PassiveBuzzer_OFF();
	while(1)
	{

	}
}


