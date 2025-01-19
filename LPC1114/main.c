/******************************************************************
 * 课程：基于NXP LPC1114的嵌入式系统设计
 * 姓名：刘嘉俊
 * 学号：20223004426
 * 任课教师：王庆吉
 * 嵌入式系统课程设计大作业
******************************************************************/
/******************************************************************
 * 编译环境及版本： Keil MDK5 5.39
 * 编译器版本： ARM Compiler version 5.06（960）
 * 硬件版本： NXP LPC1114 DevKit V5.6
 * 调试器： DAPLink
 * 语言： C语言
 * 文字版本： Chinese GB2312
******************************************************************/
/******************************************************************
 * 基于NXP LPC1114微控制器的温度监控系统，具备以下主要功能：
 * 温度读取与显示：使用LM75BD温度传感器读取环境温度，并通过中位数滤波算法处理数据以获得更稳定的温度值。
		通过UART接口与外部设备进行数据通信，定期发送当前的日期、时间和温度数据。
		同时温度数据可以通过0.96寸OLED显示屏实时显示，显示内容包括日期、时间、温度等信息。
 * 报警功能：根据实时温度，系统会进行判断并触发相应的报警机制。温度超过设定阈值时，会启动蜂鸣器报警，
		并控制RGB LED的颜色变化，以便用户可以通过视觉和听觉感知温度异常。
 * 数据存储：通过SPI接口与XT25闪存进行数据交互，系统会定期将温度数据存储到闪存中。
		支持对闪存的擦除、写入和读取操作，确保数据的持久存储。
 * 时钟与日期管理：集成了DS1307 RTC模块，提供准确的时间和日期功能。
		系统可以读取并显示当前的时间和日期，并在每次操作时同步时间数据。
 * 串口通信与调试：通过UART接口与外部设备进行数据通信，定期发送当前的日期、时间和温度数据，便于外部设备获取信息或调试。
******************************************************************/
/******************************************************************
 * 编译成功后，烧入代码到口袋开发板 NXP LPC1114 DevKit V5.6
       开发板初始会先滴一声。
 * 声光显示
	   当前设置   温度0-10℃ 开发板绿灯闪烁
				   温度10-20℃ 开发板蓝灯闪烁
				   温度20-30℃ 开发板红灯闪烁
				   当温度超过30℃，开发板所有的灯常量并且蜂鸣器开始报警
 * 通过IIC的SCL和SDA外接一个
       0.96寸OLED显示屏
	   OLED显示内容如下
					  LiuJiajun ！
					DATE： 2025-01-03
					TIME：  15:13:51
					Temp:  27.625 ℃
 * UART串口输出如下
					Hainan University
					Teacher: Wang Qingji
					Liu Jiajun
					20223004426
					Date: 2025-01-03 
					Time: 15:13:51 
					Week: 5 
					Temperature: 27.625
******************************************************************/
/* 引入头文件"LPC11xx.h" */
#include "LPC11xx.h"
#include "stdio.h"  // 使用串口重定向，把UART_Send（）函数定向给stdio.h库中的printf，方便使用printf进行串口调试
/******************************************************************************/
/* I2C 控制寄存器 */  
#define I2CONSET_AA			0x00000004  // 是否产生应答信号允许位，即是否设置为从机模式
#define I2CONSET_SI			0x00000008  // I2C中断标志位
#define I2CONSET_STO		0x00000010 // 停止标志位
#define I2CONSET_STA		0x00000020  // 开始标志位
#define I2CONSET_I2EN		0x00000040   // I2C接口允许位
/* I2C “清控制寄存器位”寄存器 */
#define I2CONCLR_AAC		0x00000004    // 清应答信号允许位
#define I2CONCLR_SIC		0x00000008  // 清I2C中断标志位
#define I2CONCLR_STAC		0x00000020  // 清开始标志位
#define I2CONCLR_I2ENC		0x00000040  // 清I2C接口允许位
/* I2C 通信速率宏定义 */ 
#define I2SCLH_SCLH			0x00000180  /* I2C SCL Duty Cycle High Reg */
#define I2SCLL_SCLL			0x00000180  /* I2C SCL Duty Cycle Low Reg */
#define I2SCLH_HS_SCLH		0x00000030  /* Fast Plus I2C SCL Duty Cycle High Reg */
#define I2SCLL_HS_SCLL		0x00000030  /* Fast Plus I2C SCL Duty Cycle Low Reg */
/* XT25存储宏定义 */  
#define WRITE    0X02
#define WREN    0X06         //写入使能
#define WRDI    0X04
#define RDSR    0X05
#define WRSR    0X01
#define READ    0X03

#define TRUE 1
#define FALSE 0
/******************************************************************************/
// 变量声明
/******************************************************************************/
float Temp_LM75BD = 0;  // 存储从LM75BD温度传感器读取的温度值
uint8_t Temp_Buf[8] = {0};  // 存储温度数据的缓冲区

uint8_t Date[10] = {0};  // 存储当前日期（格式：YYYY-MM-DD）
uint8_t Time_Data[10] = {0};  // 存储当前时间（格式：HH:MM:SS）
uint8_t Week[1] = {0};  // 存储当前星期（1~7，1表示星期一）
uint8_t Time[7] = {0x50, 0x13, 0x15, 0x05, 0x03, 0x01, 0x25};  // 时间（秒、分、时、星期、日、月、年）
uint8_t data[7] = {0};  // 用于存储读取的时间和日期数据

uint8_t Write_Addr[16] = {0};  // 用于SPI写操作的地址
uint8_t Read_Addr[16] = {0};   // 用于SPI读操作的地址

uint8_t Music_Flag = 0;  // 音乐播放标志，控制音乐播放状态

/******************************************************************************/
// OLED显示相关函数声明
/******************************************************************************/
void OLED_Init(void);  // 初始化OLED显示屏
void OLED_Clear(void);  // 清空OLED显示内容
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);  // 在指定行列显示一个字符
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);  // 在指定行列显示字符串
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);  // 显示数字
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);  // 显示带符号的数字
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);  // 显示16进制数
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);  // 显示二进制数

/******************************************************************************/
// 16位定时器相关函数声明
/******************************************************************************/
void T16B0_init(void);  // 初始化16位定时器0
void T16B0_delay_ms(uint16_t ms);  // 毫秒级延时函数
void T16B0_delay_us(uint16_t us);  // 微秒级延时函数

/******************************************************************************/
// 16位定时器1 PWM相关函数声明
/******************************************************************************/
void T16B1_PWM_init(void);  // 初始化16位定时器1为PWM模式
void PassiveBuzzer_Init(void);  // 初始化蜂鸣器
void PassiveBuzzer_OFF(void);  // 关闭蜂鸣器
void PassiveBuzzer_ON(void);  // 启动蜂鸣器

/******************************************************************************/
// UART串口通信相关函数声明
/******************************************************************************/
void UART_Init(uint32_t baudrate);  // 初始化UART，设置波特率
uint8_t UART_Recive(void);  // 接收一个字节数据
void UART_Send_Byte(uint8_t byte);  // 发送一个字节数据
void UART_Send(uint8_t *BufferPtr, uint32_t Length);  // 发送指定长度的数据

/******************************************************************************/
// I2C总线通信相关函数声明
/******************************************************************************/
void I2C_Init(uint8_t Mode);  // 初始化I2C通信，选择模式（标准/快速）
void I2C_Start(void);  // 启动I2C通信
void I2C_Stop(void);  // 停止I2C通信
void I2C_Send_Byte(uint8_t dat);  // 发送一个字节数据
uint8_t I2C_Recieve_Byte(void);  // 接收一个字节数据

/******************************************************************************/
// SPI通信相关函数声明
/******************************************************************************/
void SSP1_IOConfig(void);  // 配置SPI1接口的IO
void SSPI1_Init(void);  // 初始化SPI1接口
void SSP1_LOW(void);  // 设置SPI1片选低电平
void SSP1_HIGH(void);  // 设置SPI1片选高电平
uint8_t SPI1_Comunicate(uint8_t TxData);  // 发送一个字节数据，并接收响应
void SSP1_Send(uint8_t *data, uint8_t Length);  // 发送指定长度的数据
void SSP1_Receive(uint8_t *data, int Length);  // 接收指定长度的数据

/******************************************************************************/
// XT25闪存相关函数声明
/******************************************************************************/
void XT25_WriteEnable(void);  // 启用XT25写入
uint8_t XT25_ReadSR(void);  // 读取XT25状态寄存器
void XT25_Write_Wait(void);  // 等待XT25写入完成
void XT25_Read_Wait(void);  // 等待XT25读取完成
void XT25_WriteSR(uint8_t sr);  // 写入XT25状态寄存器
void XT25_RUID(void);  // 读取XT25唯一ID
void XT25_EraseAll(void);  // 擦除XT25闪存
void XT25_EraseSector(void);  // 擦除XT25闪存的扇区
void SPI1_Write_FLASH(uint8_t *data, uint8_t Length);  // 向XT25写入数据
void SPI1_Read_FLASH(uint8_t *data, uint8_t Length);  // 从XT25读取数据

/******************************************************************************/
// DS1307 RTC时钟相关函数声明
/******************************************************************************/
void DS1307Init(void);  // 初始化DS1307时钟（第一次烧录时使用）
void DS1307_Read(void);  // 读取DS1307时间和日期
void DS1307_Write(uint8_t *data);  // 向DS1307写入时间和日期
void Ds1307_WriteByte(uint8_t WriteAddr, uint8_t WriteData);  // 向DS1307写入一个字节数据
uint8_t Ds1307_ReadByte(void);  // 从DS1307读取一个字节数据

/******************************************************************************/
// RGB LED控制函数声明
/******************************************************************************/
void RGB_LED_Init(void);  // 初始化RGB LED
void LED_Toggle(void);  // 切换LED状态
void RGB_Blue_Toggle(void);  // 切换蓝色LED状态
void RGB_Green_Toggle(void);  // 切换绿色LED状态
void RGB_Red_Toggle(void);  // 切换红色LED状态

/******************************************************************************/
// 温度读取和处理函数声明
/******************************************************************************/
float Read_Temp_LM75BD(void);  // 读取LM75BD温度传感器的数据
void Menu(void);  // 显示菜单（日期、时间、温度）
void Temperature_Judgment(float T);  // 根据温度判断是否需要报警
void Transfor(uint8_t *Temp_Str, float T);  // 将温度转换为字符串
float MedianFilter(void);  // 中位数滤波算法，去除极端值
void UART_Send_Date(void);  // 通过UART发送日期、时间和温度数据

/******************************************************************************/
// 定时器初始化及中断处理函数声明
/******************************************************************************/
void TMR32B0_Init(void);  // 初始化32位定时器0
void TIMER32_0_IRQHandler(void);  // 32位定时器0的中断处理函数

/******************************************************************************/
 /**
 * 函数功能：重定向printf到UART
 * 描述：此函数实现了printf的底层重定向，使得所有的printf输出都通过UART进行发送。
 * 参数：
 *      ch - 要输出的字符
 *      f  - 文件指针（对于此函数不使用，仅作为printf的标准接口）
 * 返回值：
 *      返回输出的字符（保持原始格式）
 */
int fputc(int ch, FILE *f)
{
    UART_Send_Byte(ch);  // 将字符通过UART发送
    return ch;           // 返回输出字符
}

/**********************************************/
/*               主函数                       */
/**********************************************/
int main()
{
    SystemInit();    // 系统时钟初始化
    I2C_Init(1);     // 初始化I2C通信（快速模式）
    SSPI1_Init();    // 初始化SPI接口
    UART_Init(115200);  // 初始化UART，波特率为115200
    T16B1_PWM_init();  // 初始化16位定时器1为PWM模式，控制蜂鸣器
    T16B0_init();      // 初始化16位定时器0
    TMR32B0_Init();    // 初始化32位定时器0（用于中断处理），1秒钟在串口打印一次数据并且在OLED屏幕上显示
    RGB_LED_Init();    // 初始化RGB LED
    DS1307Init();    // 仅第一次烧录时用来校准时间
    DS1307_Read();     // 读取DS1307时间
    SPI1_Read_FLASH(Temp_Buf, 8); // 从SPI闪存读取温度数据
    OLED_Init();       // 初始化OLED显示屏
    OLED_Clear();      // 清除OLED屏幕内容
    PassiveBuzzer_Init();  // 初始化蜂鸣器
    T16B0_delay_ms(200);  // 延时200ms，等待硬件初始化完成
    Read_Temp_LM75BD();   // 第一次读取温度（过滤掉初始不准确的值）
    PassiveBuzzer_OFF();  // 关闭蜂鸣器
    while(1)
    {
        
    }
}

/******************************************************************
 * 函数名: TIMER32_0_IRQHandler
 * 描述: 定时器0中断处理函数，触发时进行温度数据读取与处理，1秒钟在串口打印一次数据并且在OLED屏幕上显示
 * 在定时器0的匹配事件发生时，启动ADC转换，读取ADC7的值，处理温度数据并更新显示。
 ******************************************************************/
void TIMER32_0_IRQHandler(void) {
    // 检查定时器0的匹配中断标志（MR0）
    if ((LPC_TMR32B0->IR |= 0x01) == 1) { 

        // 从SPI闪存读取温度数据
        SPI1_Read_FLASH(Temp_Buf, 8);

        // 打印调试信息，输出到串口
        printf("Hainan University\n");
        printf("Teacher: Wang Qingji\n");
        printf("Liu Jiajun\n");
        printf("20223004426\n");

        // 读取DS1307时间
        DS1307_Read();
        
        // 进行温度中位数滤波处理
        Temp_LM75BD = MedianFilter();

        // 将温度数据转换为字符串
        Transfor(Temp_Buf, Temp_LM75BD);

        // 通过UART发送日期、时间和温度数据
        UART_Send_Date();

        // 打印当前温度
        printf("Temperature: %s\n", Temp_Buf);
        printf(" \n");

        // 显示日期、时间和温度在OLED屏幕
        Menu();

        // 根据当前温度执行判断操作（例如触发报警或控制RGB灯）
        Temperature_Judgment(Temp_LM75BD);

        // 执行XT25芯片的扇区擦除操作
        XT25_EraseSector();

        // 将温度数据写入到XT25闪存
        SPI1_Write_FLASH(Temp_Buf, 8);

        // 清除定时器0的匹配中断标志
        LPC_TMR32B0->IR = 0x01;
    }
}











/**
 * 函数功能：显示当前信息到OLED屏幕
 * 描述：在OLED屏幕上依次显示当前日期、时间和温度。日期、时间和温度的数据通过全局变量传递。
 * OLED显示的位置和数据格式固定，显示日期、时间和温度值。
 */
void Menu(void)
{   
    /*OLED显示*/
    // OLED_Clear(); // 清除OLED显示屏（注释掉了此行）
    OLED_ShowString(1, 4, "LiuJiajun ! ");    // 在第1行第4列显示字符串"LiuJiajun !"
    OLED_ShowString(2, 1, "DATE: ");          // 在第2行第1列显示"DATE: "
    // 显示日期（Date[]数组保存了日期数据）
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
    
    OLED_ShowString(3, 1, "TIME:  ");        // 在第3行第1列显示"TIME: "
    // 显示时间（Time_Data[]数组保存了时间数据）
    OLED_ShowChar(3, 8, Time_Data[0]);
    OLED_ShowChar(3, 9, Time_Data[1]);
    OLED_ShowChar(3, 10, Time_Data[2]);
    OLED_ShowChar(3, 11, Time_Data[3]);
    OLED_ShowChar(3, 12, Time_Data[4]);
    OLED_ShowChar(3, 13, Time_Data[5]);
    OLED_ShowChar(3, 14, Time_Data[6]);
    OLED_ShowChar(3, 15, Time_Data[7]);
    
    OLED_ShowString(4, 1, "Temp:  ");        // 在第4行第1列显示"Temp: "
    // 显示温度（Temp_Buf[]数组保存了温度数据）
    OLED_ShowChar(4, 8, Temp_Buf[0]);
    OLED_ShowChar(4, 9, Temp_Buf[1]);
    OLED_ShowChar(4, 10, Temp_Buf[2]);
    OLED_ShowChar(4, 11, Temp_Buf[3]);
    OLED_ShowChar(4, 12, Temp_Buf[4]);
    OLED_ShowChar(4, 13, Temp_Buf[5]);
    OLED_ShowString(4, 15, "C");             // 在温度后显示"℃"
}

/**
 * 函数功能：根据温度判断是否报警，并控制RGB灯和蜂鸣器
 * 描述：根据温度T值的不同，控制蜂鸣器和RGB灯的状态。
 *       温度高于30℃时启动蜂鸣器，并熄灭RGB灯；温度在不同范围内时，控制RGB灯的颜色。
 * 参数：
 *      T - 当前温度（单位：摄氏度）
 */
void Temperature_Judgment(float T)
{
    if (T > 30) {
        PassiveBuzzer_ON(); // 启动蜂鸣器
        // 打开所有RGB灯（根据GPIO控制灯的开关状态）
        LPC_GPIO2->DATA &= ~(1UL << 10); 
        LPC_GPIO2->DATA &= ~(1UL << 9); 
        LPC_GPIO2->DATA &= ~(1UL << 8); 
        LPC_GPIO1->DATA &= ~(1UL << 10); 
    }
    else if (0 < T && T <= 10) {
        LPC_GPIO2->DATA |= (1UL << 10);
        LPC_GPIO2->DATA |= (1UL << 9);
        PassiveBuzzer_OFF();  // 关闭蜂鸣器
        RGB_Green_Toggle();   // 切换绿色RGB灯
    }
    else if (10 < T && T <= 20) {
        LPC_GPIO2->DATA |= (1UL << 9);
        LPC_GPIO2->DATA |= (1UL << 8);
        PassiveBuzzer_OFF();  // 关闭蜂鸣器
        RGB_Blue_Toggle();    // 切换蓝色RGB灯
    }
    else if (20 < T && T <= 30) {
        LPC_GPIO2->DATA |= (1UL << 10);
        LPC_GPIO2->DATA |= (1UL << 8);
        PassiveBuzzer_OFF();  // 关闭蜂鸣器
        RGB_Red_Toggle();     // 切换红色RGB灯
    }
}

/**
 * 函数功能：将浮动温度值转换为字符串
 * 描述：将传入的浮动温度值转换为字符串格式，保留三位小数。
 * 参数：
 *      Temp_Str - 用于保存温度字符串的缓冲区
 *      T - 当前温度（浮动类型）
 */
void Transfor(uint8_t *Temp_Str, float T) {
    sprintf((char *)Temp_Str, "%.3f", T); // 将浮动温度T转换为字符串，保留三位小数
}

/**
 * 函数功能：中位数滤波
 * 描述：通过多次温度测量并采用中位数滤波算法，去除极端值，得到更加平稳的温度值。
 * 返回值：
 *      返回去除极端值后的温度值（单位：摄氏度）
 */
float MedianFilter(void) {
    float measurements[7]; // 用于存储7次温度测量值
    float temp;
    
    // 进行7次温度测量
    for (unsigned int i = 0; i < 7; i++) {
        measurements[i] = Read_Temp_LM75BD(); // 读取传感器温度值
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
    
    // 去掉最大值和最小值，计算中间5个值的平均值
    float sum = 0;
    for (unsigned int i = 1; i < 7 - 1; i++) { // 从1到N-2，即中间5个数
        sum += measurements[i];
    }
    
    // 计算并返回平均值
    return (sum / (7 - 2)); // 去掉2个值，所以用(N - 2)
}

/**
 * 函数功能：发送日期、时间和星期数据通过UART
 * 描述：将日期、时间和星期信息通过UART发送到串口，便于外部设备查看。
 */
void UART_Send_Date(void)
{   
    UART_Send("Date: ", 6);        // 发送日期前缀
    UART_Send(Date, 10);           // 发送日期数据
    UART_Send(" \n", 2);           // 换行
    UART_Send("Time: ", 6);        // 发送时间前缀
    UART_Send(Time_Data, 8);       // 发送时间数据
    UART_Send(" \n", 2);           // 换行
    UART_Send("Week: ", 6);        // 发送星期前缀
    UART_Send(Week, 1);            // 发送星期数据
    UART_Send(" \n", 2);           // 换行
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

/******************************************************************************/
/**********************************************/
/*  温度传感器LM75BD的数据读取函数  */
/**********************************************/
float Read_Temp_LM75BD(void)
{  
  uint16_t Temputerature_8,Temputerature_16;  //温度值，1次接收8位
  float Temputerature;   //存储获得的温度值
  //IIC启动---默认配置温度模式
	  //发送(0x91)1001 0001：1001,硬件布线； 0001，从机地址--000   读模式--1
  I2C_Start();
  I2C_Send_Byte(0x91);
	LPC_I2C->CONSET =(1<<2);//AA=1
  Temputerature_8 = I2C_Recieve_Byte();//读LM75BD温度寄存器的高八位数据 
LPC_I2C->CONCLR =(1<<2);//AA=0	
  Temputerature_16 = (Temputerature_8 <<8)+(I2C_Recieve_Byte());
  I2C_Stop();  

  Temputerature_16 = Temputerature_16 >> 5;//1LSB=0.125℃---低五位为无效数据(移出)
  /* Temputerature_16:温度寄存器的数据D0--D10:其中D10为温度的正负数据*/
	
  //负温度
  if(Temputerature_16&0x0400)
  Temputerature = (-(~(Temputerature_16&0x03FF)+1)*0.125);//负温度的数据的转换(二进制的补码+1)
  //正温度
  else 
  Temputerature = (0.125*(float)(Temputerature_16));
  
  //返回温度值 1LSB=0.01℃
  return Temputerature;
}
/******************************************************************************/
/**
 * 函数功能：初始化16位定时器0
 * 描述：配置并初始化16位定时器0，设置定时器的时钟源、计数器模式和匹配寄存器，确保定时器可以正常工作。
 */
void T16B0_init(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 7);  // 使能16位定时器0的时钟（TIM16B0）
    LPC_TMR16B0->IR = 0x01;                 // 清除定时器0的中断标志，设置中断源为MR0（匹配0寄存器）
    LPC_TMR16B0->MCR = 0x04;                // 配置匹配控制寄存器（MCR）：匹配0后重置TC，不生成中断（TCR[0]=0）
}

/**
 * 函数功能：延时函数（毫秒级）
 * 描述：使用16位定时器0生成精确的毫秒级延时。
 * 参数：
 *      ms - 延迟的毫秒数（最大65535ms，即65.535秒）。
 */
void T16B0_delay_ms(uint16_t ms)
{
    LPC_TMR16B0->TCR = 0x02;                    // 重置定时器（TCR[1] = 1），停止定时器
    LPC_TMR16B0->PR = SystemCoreClock / 1000 - 1; // 设置定时器预分频器，确保定时器计数器按1ms递增
    LPC_TMR16B0->MR0 = ms;                      // 设置MR0为目标延时值（单位：毫秒）
    LPC_TMR16B0->TCR = 0x01;                    // 启动定时器（TCR[0] = 1）
    LPC_TMR16B0->TCR = 0x01;                    // 启动定时器（TCR[0] = 1），重新启动
    while (LPC_TMR16B0->TCR & 0x01);            // 等待定时器计数完成，直到TCR[0]为0，表示延时结束
}

/**
 * 函数功能：延时函数（微秒级）
 * 描述：使用16位定时器0生成精确的微秒级延时。
 * 参数：
 *      us - 延迟的微秒数（最大65535us，即65.535ms）。
 */
void T16B0_delay_us(uint16_t us)
{
    LPC_TMR16B0->TCR = 0x02;                    // 重置定时器（TCR[1] = 1），停止定时器
    LPC_TMR16B0->PR = SystemCoreClock / 1000000 - 1; // 设置定时器预分频器，确保定时器计数器按1us递增
    LPC_TMR16B0->MR0 = us;                      // 设置MR0为目标延时值（单位：微秒）
    LPC_TMR16B0->TCR = 0x01;                    // 启动定时器（TCR[0] = 1）
    while (LPC_TMR16B0->TCR & 0x01);            // 等待定时器计数完成，直到TCR[0]为0，表示延时结束
}
/******************************************************************************/
/**
 * 函数功能：初始化16位定时器1为PWM模式
 * 描述：配置定时器1的PWM功能，使其能够生成PWM信号，输出到PIO1_10管脚，控制被动蜂鸣器的频率和占空比。
 */
void T16B1_PWM_init(void)  
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8) | (1UL << 16); // 使能16位定时器1和IOCON的时钟
    LPC_IOCON->PIO1_10 |= 0x02;  // 将PIO1_10复用为MAT1（PWM输出功能）
    LPC_TMR16B1->TCR = 0x02;  // 复位16位定时器1
    LPC_TMR16B1->PR = 0;  // 设置预分频寄存器为0，不分频，计数频率等于系统时钟频率
    LPC_TMR16B1->PWMC = 0x02;  // 配置MAT1为PWM模式
    LPC_TMR16B1->MCR = (0x02 << 9);  // 设置匹配寄存器3（MR3）匹配后重置计数器TC，且不产生中断
    LPC_TMR16B1->MR3 = SystemCoreClock / 1000;  // 设置MR3为1ms（PWM周期为1ms）
    LPC_TMR16B1->MR1 = LPC_TMR16B1->MR3; // MR1控制PWM的占空比，默认与MR3相等，占空比为100%
    LPC_TMR16B1->TCR = 0x01;  // 使能16位定时器1
}

/**
 * 函数功能：初始化被动蜂鸣器的GPIO
 * 描述：配置PIO1_10为GPIO输出模式，默认关闭GPIO时钟以降低功耗。
 */
void PassiveBuzzer_Init(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // 使能GPIO时钟
    LPC_GPIO1->DIR |= (1UL << 10); // 设置PIO1_10为输出模式
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 16);   // 禁用IOCON时钟，确保低功耗
}

/**
 * 函数功能：关闭被动蜂鸣器
 * 描述：关闭定时器1的PWM功能，复位相关寄存器，关闭IOCON和定时器时钟以降低功耗。
 */
void PassiveBuzzer_OFF(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 16); // 使能IOCON时钟
    LPC_IOCON->PIO1_10 &= ~0x3F;  // 清除PIO1_10的功能设置
    LPC_GPIO1->DIR &= ~(1UL << 10); // 将PIO1_10设置为输入模式
    LPC_TMR16B1->MR1 = 0;  // 将MR1设为0，停止PWM输出
    LPC_TMR16B1->TCR = 0x00; // 停止16位定时器1
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1UL << 8); // 关闭定时器1的时钟
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 16); // 禁用IOCON时钟以降低功耗
}

/**
 * 函数功能：开启被动蜂鸣器
 * 描述：配置并启用定时器1的PWM功能，以MAT1输出PWM信号控制蜂鸣器发声。
 */
void PassiveBuzzer_ON(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 16); // 使能IOCON时钟
    LPC_IOCON->PIO1_10 |= 0x02;  // 将PIO1_10复用为MAT1（PWM功能）
    LPC_TMR16B1->TCR = 0x01;  // 使能16位定时器1
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8);  // 使能定时器1的时钟
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 16); // 禁用IOCON时钟以降低功耗
    LPC_TMR16B1->MR3 = SystemCoreClock / 1000 - 1;  // 设置MR3为1ms（PWM周期为1ms）
    LPC_TMR16B1->MR1 = LPC_TMR16B1->MR3 * 50 / 100; // 设置MR1为50%占空比
}
/******************************************************************************/
/******************************************************************
 * 函数名: UARTInit
 * 描述: 初始化 UART0 端口，设置选中引脚、时钟，校验、停止位、FIFO、等等。
 * 参数: UART 波特率
 * 返回值: 无
******************************************************************/
  void UART_Init(uint32_t baudrate)
  {
  	uint32_t Fdiv; // 分频值
  	uint32_t regVal = regVal; // 临时变量
  	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);  // 使能 IOCON 模块的时钟
  	LPC_IOCON->PIO1_6 &= ~0x07;  // UART I/O 配置，设置 PIO1_6 为 UART RXD 
  	LPC_IOCON->PIO1_6 |= 0x01; 
  	LPC_IOCON->PIO1_7 &= ~0x07; // 设置 PIO1_7 为 UART TXD 
  	LPC_IOCON->PIO1_7 |= 0x01; 
  	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 16); // 关闭 IOCON 模块的时钟
  	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12); // 使能 UART 时钟
  	LPC_SYSCON->UARTCLKDIV = 0x1; // 分频值 1
  	LPC_UART->LCR = 0x83; // 设置 UART 线控制寄存器 (LCR)，配置为 8 位数据，奇校验位，1 停止位 	
  	Fdiv = (SystemCoreClock / 16) / baudrate; // 计算波特率分频值
  	LPC_UART->DLM = Fdiv / 256; // 设置波特率低字节和高字节
  	LPC_UART->DLL = Fdiv % 256; 
  	LPC_UART->LCR = 0x03; // 重置 LCR，禁用 DLAB 
  	LPC_UART->FCR = 0x07; // 使能并复位 TX 和 RX FIFO	
  	regVal = LPC_UART->LSR; // 读取并清除行状态寄存器 (LSR)
  	// 确保正常开始，TX 和 RX FIFO 中没有数据
  	while ((LPC_UART->LSR & (0x20 | 0x40)) != (0x20 | 0x40));
  	while (LPC_UART->LSR & 0x01)
  	{
  		regVal = LPC_UART->RBR; // 从 RX FIFO 中转储数据
  	}
	LPC_UART->IER |=1<<0; //使能接受中断
    NVIC_EnableIRQ(UART_IRQn); //启动中断
  }


/************************************************/
/* 函数功能：串口接收字节数据  */
/************************************************/
uint8_t UART_Recive(void)
{  
  while(!(LPC_UART->LSR & (1<<0)));   //等待接收到数据
  return(LPC_UART->RBR);   //读出数据
}

/************************************************/
/* 函数功能：串口发送字节数据  */
/************************************************/
void UART_Send_Byte(uint8_t byte)
{
    LPC_UART->THR = byte;
  while ( !(LPC_UART->LSR & (1<<5)) );//等待发送完

}

/******************************************************************
 * 函数名: UARTSend
 * 描述: 根据数据长度发送一串数据到 UART 0 端口。
 * 参数: buffer pointer, and data length
 * 返回值: 无
******************************************************************/
 void UART_Send(uint8_t *BufferPtr, uint32_t Length)
 {
 	while (Length != 0) // 判断数据长度，不为0则发送数据
 	{
 		while (!(LPC_UART->LSR & (1 << 5))); // 等待直到发送数据寄存器空
 		LPC_UART->THR = *BufferPtr; // 发送当前字节
 		BufferPtr++; // 移动到下一个字节
 		Length--; // 递减数据长度
 	}
 }
/******************************************************************************/
void I2C_Init(uint8_t Mode)
{
  LPC_SYSCON->PRESETCTRL |= (1<<1);   //使I2C上电 I2C模块（在启动I2C模块之前，必须向该位写1）
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);   //使能I2C时钟
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);   // 使能IOCON时钟
  LPC_IOCON->PIO0_4 &= ~0x3F;  
  LPC_IOCON->PIO0_4 |= 0x01;   //把P0.4脚配置为 I2C SCL 
  LPC_IOCON->PIO0_5 &= ~0x3F;  
  LPC_IOCON->PIO0_5 |= 0x01;   //把P0.5脚配置为 I2C SDA 
	
	 /*--- Reset registers ---*/
	if(Mode == 1)
	{
	 LPC_I2C->SCLL   = I2SCLL_HS_SCLL;
	 LPC_I2C->SCLH   = I2SCLH_HS_SCLH;
	}
	else
	{
    LPC_I2C->SCLH = I2SCLH_SCLH;
    LPC_I2C->SCLL = I2SCLL_SCLL;
	}
 /*--- Clear flags ---*/
  LPC_I2C->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;      
	   
  LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);   // 禁能IOCON时钟 
  LPC_I2C->CONSET |= I2CONSET_I2EN;  // 使能I2C接口
}


void I2C_Start(void)
{
  LPC_I2C->CONSET |= I2CONSET_STA;  // 使能发送开始信号
  while(!(LPC_I2C->CONSET & I2CONSET_SI));  // 等待开始信号发送完成
  LPC_I2C->CONCLR = I2CONCLR_STAC | I2CONCLR_SIC; // 清除开始START位和SI位 
}


void I2C_Stop(void)
{
   LPC_I2C->CONCLR = I2CONCLR_SIC;  // 清SI标志位
   LPC_I2C->CONSET |= I2CONSET_STO;  // 发送停止信号
   while( LPC_I2C->CONSET & I2CONSET_STO );  // 等待停止信号发送完成 
}

/****************************************************/
/* 函数功能：I2C发送一字节数据  */
/* 入口参数：dat : 要发送的字节  */
/***************************************************/
void I2C_Send_Byte(uint8_t dat)
{
   LPC_I2C->DAT = dat;  // 把字节写入DAT寄存器
   LPC_I2C->CONCLR = I2CONSET_SI;  // 清除SI标志(1<<3)
   while(!(LPC_I2C->CONSET & I2CONSET_SI));  // 等待数据发送完成
}


/***************************************************/
/* 函数功能：I2C接收一字节数据  */
/* 入口参数：rebyte : 要接收的字节  */
/***************************************************/
uint8_t I2C_Recieve_Byte(void)
{
  uint8_t ReByte;
  LPC_I2C->CONCLR = I2CONCLR_SIC;   // 清AA和SI标志
  while(!(LPC_I2C->CONSET & I2CONSET_SI));  // 等待接收数据完成
  ReByte = (uint8_t)LPC_I2C->DAT;  // 把接收到的数据给了rebyte
  return ReByte;
}
/******************************************************************************/
/*
*函数功能：SSP1IO初始化
*/
void SSP1_IOConfig(void){
    LPC_SYSCON->SYSAHBCLKCTRL |=((1<<6)|(1<<16)); //IO 和GPIO
    LPC_IOCON->PIO2_2 &=~(0X07); //
    LPC_IOCON->PIO2_2 |=0X02;// MISO
    LPC_IOCON->PIO2_3 &=~(0X07); //
    LPC_IOCON->PIO2_3 |=0X02;//MOSI  此处可能出现问题
    LPC_IOCON->PIO2_1 &=~(0X07); //
    LPC_IOCON->PIO2_1 |=0X02;//CLK   
    LPC_GPIO2->DIR |= (1<<0);
    LPC_GPIO2->DATA |= (1<<0); //拉高
}

/**
*函数功能：SSP1初始化
*/
void SSPI1_Init(void){
    uint8_t Dummy=Dummy; //随机数
    uint8_t i;
    
    LPC_SYSCON->PRESETCTRL |=1<<2; //复位ssp1
    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<18); //ssp1 时钟使能
    LPC_SYSCON->SSP1CLKDIV=0X02 ;  //分频值 2 48/2=24
    
    SSP1_IOConfig(); //初始化SSP1 IO口   
    LPC_SSP1->CR0=0X0707;   //CPSR=7 DATAbit= 8 CPOL=0 CPHA=0 SCR=7  选择spi
    LPC_SSP1->CPSR=0X2;   //SCLK=48/(2*2*8)= 1.5M   
    LPC_SSP1->CR1 &=~(1<<0);//LBM=0 :正常模式
    LPC_SSP1->CR1 &=~(1<<2);//MS=0 主机模式
    LPC_SSP1->CR1 |=1<<1; //SSE=1 开启ssp1    
    //清空RXFIFO
    for(i=0 ; i<8 ;i++){
        Dummy = LPC_SSP1->DR;
    }
	
    for(i=0;i<16;i++){
        Read_Addr[i]=0;
        Write_Addr[i]=0;
    }
    
}

void SSP1_LOW(void){
    LPC_GPIO2->DATA &= ~(1<<0); //拉低
}
void SSP1_HIGH(void){
    LPC_GPIO2->DATA |= (1<<0); //拉高
}

/**
* 函数功能：SSP1通信
* 接受和发送一个字符
*/
uint8_t SPI1_Comunicate(uint8_t TxData){
    while(((LPC_SSP1->SR)&(1<<4))==(1<<4));//忙时等待
    LPC_SSP1->DR=TxData; // 发送数据到TxFIFO
    while(((LPC_SSP1->SR)&(1<<2))!=(1<<2));// 等待数据接受完
    return (LPC_SSP1->DR); // 接受返回的数据
}

/**
*函数功能：SSP1发送
*/
void SSP1_Send(uint8_t *data,uint8_t Length){
    uint8_t i;
    for(i=0;i<Length;i++){
        SPI1_Comunicate(data[i]);
    }
}

/**
* 函数功能：SSP1接受
*/
void SSP1_Receive(uint8_t *data,int Length){
    uint8_t Dummy=Dummy; // 随机数用于产生时钟
    uint8_t i;
    for(i=0 ; i<Length ;i++){
        data[i]=SPI1_Comunicate(0xff);
    }
}
/******************************************************************************/
/**
 * 函数功能：写入使能
 * 描述：向XT25芯片发送写入使能命令（WREN），
 *       设置写入使能位（WEL=1），以允许后续的写入操作。
 */
void XT25_WriteEnable(void) {
    SSP1_LOW();               // 拉低片选信号，使能SPI通信
    SPI1_Comunicate(WREN);    // 发送写入使能命令（WREN）
    SSP1_HIGH();              // 拉高片选信号，结束通信
}

/**
 * 函数功能：读取状态寄存器
 * 描述：通过SPI读取XT25的状态寄存器，获取当前芯片的状态信息。
 * 返回值：
 *      uint8_t - 状态寄存器的值。
 */
uint8_t XT25_ReadSR(void) {
    uint8_t sr;
    SSP1_LOW();                    // 拉低片选信号，使能SPI通信
    SPI1_Comunicate(RDSR);         // 发送读取状态寄存器命令（RDSR）
    sr = SPI1_Comunicate(0xFF);    // 接收状态寄存器数据
    SSP1_HIGH();                   // 拉高片选信号，结束通信
    return sr;                     // 返回状态寄存器值
}

/**
 * 函数功能：忙碌等待 - 写入等待
 * 描述：检查XT25的状态寄存器，等待写入操作完成（WIP=0，写操作完成）。
 */
void XT25_Write_Wait(void) {
    int stat_code = 0;
    while (1) {
        stat_code = XT25_ReadSR(); // 读取状态寄存器
        if (((stat_code & (1 << 1)) == 0x02) && (stat_code & 1) == 0) { // 检查WIP=0且写保护位
            break; // 写入完成，退出等待
        }
    }
}

/**
 * 函数功能：忙碌等待 - 读出等待
 * 描述：检查XT25的状态寄存器，等待芯片准备完成（WIP=0）。
 */
void XT25_Read_Wait(void) {
    int stat_code = 0;
    while (1) {
        stat_code = XT25_ReadSR(); // 读取状态寄存器
        if ((stat_code & 1) == 0) { // 检查WIP=0（芯片不忙）
            break; // 芯片准备完成，退出等待
        }
    }
}

/**
 * 函数功能：写入状态寄存器
 * 描述：通过SPI向XT25的状态寄存器写入数据，用于配置芯片的状态。
 * 参数：
 *      sr - 要写入状态寄存器的数据。
 */
void XT25_WriteSR(uint8_t sr) {
    XT25_WriteEnable();       // 使能写入操作
    T16B0_delay_ms(50);       // 延时50ms，确保稳定
    SSP1_LOW();               // 拉低片选信号，使能SPI通信
    SPI1_Comunicate(0x01);    // 发送写入状态寄存器命令
    SPI1_Comunicate(sr);      // 写入状态寄存器数据
    SSP1_HIGH();              // 拉高片选信号，结束通信
}

/**
 * 函数功能：读取唯一ID
 * 描述：通过SPI读取XT25芯片的唯一ID，用于芯片唯一性标识。
 */
void XT25_RUID(void) {
    Write_Addr[0] = 0x4B;     // 设置读取唯一ID命令
    Write_Addr[1] = 0x00;     // 保留字节
    Write_Addr[2] = 0x00;     // 保留字节
    Write_Addr[3] = 0x00;     // 保留字节
    SSP1_LOW();               // 拉低片选信号，使能SPI通信
    SSP1_Receive((uint8_t *)Read_Addr, 16); // 接收16字节唯一ID数据
    SSP1_HIGH();              // 拉高片选信号，结束通信
}

/**
 * 函数功能：擦除整个芯片
 * 描述：通过SPI向XT25发送擦除全部存储区的命令。
 */
void XT25_EraseAll(void) {
    XT25_WriteSR(0x00);       // 清除写保护位（BP1=0, BP0=0）
    T16B0_delay_ms(50);       // 延时50ms，确保稳定
    XT25_WriteEnable();       // 使能写入操作
    T16B0_delay_ms(50);       // 延时50ms，确保稳定
    SSP1_LOW();               // 拉低片选信号，使能SPI通信
    SPI1_Comunicate(0x60);    // 发送芯片擦除命令
    SSP1_HIGH();              // 拉高片选信号，结束通信
}

/**
 * 函数功能：扇区擦除
 * 描述：通过SPI擦除XT25的指定扇区，释放存储空间。
 */
void XT25_EraseSector(void) {
    XT25_WriteSR(0x00);       // 清除写保护位（BP1=0, BP0=0）
    T16B0_delay_ms(50);       // 延时50ms，确保稳定
    XT25_WriteEnable();       // 使能写入操作
    T16B0_delay_ms(50);       // 延时50ms，确保稳定
    SSP1_LOW();               // 拉低片选信号，使能SPI通信
    SPI1_Comunicate(0x20);    // 发送扇区擦除命令
    SPI1_Comunicate(0x22);    // 指定扇区地址（示例地址0x222222）
    SPI1_Comunicate(0x22);
    SPI1_Comunicate(0x22);
    SSP1_HIGH();              // 拉高片选信号，结束通信
    T16B0_delay_ms(100);      // 延时100ms，等待擦除完成
}

/**
 * 函数功能：写入数据到FLASH
 * 描述：通过SPI将数据写入XT25芯片的指定地址。
 * 参数：
 *      data - 要写入的数据指针。
 *      Length - 要写入的数据长度。
 */
void SPI1_Write_FLASH(uint8_t *data, uint8_t Length) {
    XT25_WriteEnable();       // 使能写入操作
    T16B0_delay_ms(50);       // 延时50ms，确保稳定
    Write_Addr[0] = WRITE;    // 页面编程命令
    Write_Addr[1] = 0x22;     // 指定地址（示例地址0x222222）
    Write_Addr[2] = 0x22;
    Write_Addr[3] = 0x22;

    // 填充要写入的数据
    for (int i = 0; i < Length; i++) {
        Write_Addr[i + 4] = data[i];
    }

    XT25_Write_Wait();        // 等待写入完成
    SSP1_LOW();               // 拉低片选信号，使能SPI通信
    SSP1_Send((uint8_t *)Write_Addr, 4 + Length); // 发送写入命令和数据
    SSP1_HIGH();              // 拉高片选信号，结束通信
}

/**
 * 函数功能：读取FLASH中的数据
 * 描述：通过SPI从XT25芯片的指定地址读取数据。
 * 参数：
 *      data - 用于存储读取数据的指针。
 *      Length - 要读取的数据长度。
 */
void SPI1_Read_FLASH(uint8_t *data, uint8_t Length) {
    Write_Addr[0] = READ;     // 读取命令
    Write_Addr[1] = 0x22;     // 指定地址（示例地址0x222222）
    Write_Addr[2] = 0x22;
    Write_Addr[3] = 0x22;

    XT25_Read_Wait();         // 等待芯片准备完成
    SSP1_LOW();               // 拉低片选信号，使能SPI通信
    SSP1_Send((uint8_t *)Write_Addr, 4);         // 发送读取命令和地址
    SSP1_Receive((uint8_t *)Read_Addr, Length); // 接收读取的数据
    SSP1_HIGH();              // 拉高片选信号，结束通信

    // 将读取的数据拷贝到目标缓冲区
    for (int i = 0; i < Length; i++) {
        data[i] = Read_Addr[i];
    }
}
/******************************************************************************/
/**
 * 函数功能：初始化DS1307并设置时间
 * 描述：通过调用写函数将初始时间数据写入DS1307模块，
 *       从而完成时钟芯片的初始化。
 */
void DS1307Init(void)
{
    DS1307_Write(Time); // 将时间数据写入DS1307芯片的寄存器中
}

/**
 * 函数功能：读取DS1307的时间和日期
 * 描述：通过I2C接口读取DS1307的内部寄存器内容，
 *       并提取时间和日期数据，同时进行格式化处理。
 */
void DS1307_Read(void)
{
    // 定位DS1307的内部指针到RAM尾部0x3f地址
    Ds1307_WriteByte(0x3f, 0x01);
    
    I2C_Start(); // 发送I2C起始信号
    I2C_Send_Byte(0xD1); // 发送设备地址（读操作，地址为0xD1）
    LPC_I2C->CONSET = (1 << 2); // 设置ACK（AA=1）以应答下一个字节的数据

    // 从DS1307读取7个字节数据，依次为秒、分、时、星期、日、月、年
    data[0] = I2C_Recieve_Byte(); // 秒
    data[1] = I2C_Recieve_Byte(); // 分
    data[2] = I2C_Recieve_Byte(); // 时
    data[3] = I2C_Recieve_Byte(); // 星期
    data[4] = I2C_Recieve_Byte(); // 日
    data[5] = I2C_Recieve_Byte(); // 月
    LPC_I2C->CONCLR = (1 << 2);   // 清除ACK（AA=0）
    data[6] = I2C_Recieve_Byte(); // 年

    // 将读取的时间数据格式化为字符串（例如：12:34:56）
    Time_Data[0] = data[2] / 16 + '0';  // 时的十位
    Time_Data[1] = data[2] % 16 + '0';  // 时的个位
    Time_Data[2] = ':';
    Time_Data[3] = data[1] / 16 + '0';  // 分的十位
    Time_Data[4] = data[1] % 16 + '0';  // 分的个位
    Time_Data[5] = ':';
    Time_Data[6] = data[0] / 16 + '0';  // 秒的十位
    Time_Data[7] = data[0] % 16 + '0';  // 秒的个位

    // 将读取的日期数据格式化为字符串（例如：2023-01-03）
    Date[0] = '2';
    Date[1] = '0';
    Date[2] = data[6] / 16 + '0'; // 年的十位
    Date[3] = data[6] % 16 + '0'; // 年的个位
    Date[4] = '-';
    Date[5] = data[5] / 16 + '0'; // 月的十位
    Date[6] = data[5] % 16 + '0'; // 月的个位
    Date[7] = '-';
    Date[8] = data[4] / 16 + '0'; // 日的十位
    Date[9] = data[4] % 16 + '0'; // 日的个位

    // 星期数据（格式化为数字字符串，例如：1表示星期一）
    Week[0] = data[3] % 16 + '0';

    I2C_Stop(); // 发送I2C停止信号
}

/**
 * 函数功能：向DS1307写入时间和日期数据
 * 描述：通过I2C接口将时间和日期数据写入DS1307寄存器，
 *       覆盖其当前时间。
 * 参数：
 *      data - 包含时间和日期数据的数组，长度为7字节。
 */
void DS1307_Write(uint8_t *data)
{
    I2C_Start(); // 发送I2C起始信号
    I2C_Send_Byte(0xD0); // 发送设备地址（写操作，地址为0xD0）
    LPC_I2C->CONSET = (1 << 2); // 设置ACK（AA=1）

    I2C_Send_Byte(0x00); // 设置DS1307内部指针到地址0x00
    // 依次写入秒、分、时、星期、日、月、年
    I2C_Send_Byte(data[0]); // 秒
    I2C_Send_Byte(data[1]); // 分
    I2C_Send_Byte(data[2]); // 时
    I2C_Send_Byte(data[3]); // 星期
    I2C_Send_Byte(data[4]); // 日
    I2C_Send_Byte(data[5]); // 月
    LPC_I2C->CONCLR = (1 << 2); // 清除ACK（AA=0）
    I2C_Send_Byte(data[6]); // 年

    I2C_Stop(); // 发送I2C停止信号
}

/**
 * 函数功能：向DS1307写入一个字节数据
 * 描述：通过I2C接口在指定地址写入一个字节数据。
 * 参数：
 *      WriteAddr - 要写入的寄存器地址。
 *      WriteData - 要写入的数据。
 */
void Ds1307_WriteByte(uint8_t WriteAddr, uint8_t WriteData)
{
    I2C_Start(); // 发送I2C起始信号
    I2C_Send_Byte(0xD0); // 发送设备地址（写操作，地址为0xD0）
    I2C_Send_Byte(WriteAddr); // 指定写入的寄存器地址
    LPC_I2C->CONCLR = (1 << 2); // 清除ACK（AA=0）
    I2C_Send_Byte(WriteData); // 写入数据
    I2C_Stop(); // 发送I2C停止信号
}

/**
 * 函数功能：从DS1307读取一个字节数据
 * 描述：通过I2C接口从DS1307的当前地址读取一个字节数据。
 * 返回值：
 *      uint8_t - 读取到的数据。
 */
uint8_t Ds1307_ReadByte(void)
{
    uint8_t RevData;

    I2C_Start(); // 发送I2C起始信号
    I2C_Send_Byte(0xD1); // 发送设备地址（读操作，地址为0xD1）
    LPC_I2C->CONCLR = (1 << 2); // 清除ACK（AA=0）
    RevData = I2C_Recieve_Byte(); // 读取数据
    I2C_Stop(); // 发送I2C停止信号

    return RevData; // 返回读取到的数据
}
/******************************************************************************/
/*OLED字模库，宽8像素，高16像素*/
const uint8_t OLED_F8x16[][16]=
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//  0
	
	0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,//! 1
	
	0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//" 2
	
	0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,
	0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,//# 3
	
	0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,
	0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,//$ 4
	
	0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,
	0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,//% 5
	
	0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,
	0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,//& 6
	
	0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//' 7
	
	0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,
	0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,//( 8
	
	0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,
	0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,//) 9
	
	0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,
	0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//* 10
	
	0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,
	0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,//+ 11
	
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,//, 12
	
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//- 13
	
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,//. 14
	
	0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,
	0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,/// 15
	
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,
	0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//0 16
	
	0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//1 17
	
	0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,
	0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//2 18
	
	0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,
	0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,//3 19
	
	0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,
	0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,//4 20
	
	0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,
	0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,//5 21
	
	0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,
	0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,//6 22
	
	0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,
	0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,//7 23
	
	0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,
	0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//8 24
	
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,
	0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,//9 25
	
	0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//: 26
	
	0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,
	0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,//; 27
	
	0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,
	0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,//< 28
	
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//= 29
	
	0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,
	0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,//> 30
	
	0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,
	0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00,//? 31
	
	0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,
	0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,//@ 32
	
	0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,
	0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A 33
	
	0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,
	0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B 34
	
	0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,
	0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C 35
	
	0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,
	0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D 36
	
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,
	0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E 37
	
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,
	0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F 38
	
	0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,
	0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,//G 39
	
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,
	0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//H 40
	
	0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//I 41
	
	0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,
	0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,//J 42
	
	0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,
	0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K 43
	
	0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,
	0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,//L 44
	
	0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,
	0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,//M 45
	
	0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,
	0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,//N 46
	
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,
	0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,//O 47
	
	0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,
	0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,//P 48
	
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,
	0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,//Q 49
	
	0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,
	0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,//R 50
	
	0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,
	0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,//S 51
	
	0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,
	0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//T 52
	
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,
	0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//U 53
	
	0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,
	0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V 54
	
	0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,
	0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,//W 55
	
	0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,
	0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,//X 56
	
	0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,
	0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//Y 57
	
	0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,
	0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,//Z 58
	
	0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,
	0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,//[ 59
	
	0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,//\ 60
	
	0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,
	0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,//] 61
	
	0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//^ 62
	
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_ 63
	
	0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//` 64
	
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,
	0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,//a 65
	
	0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,
	0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,//b 66
	
	0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,
	0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,//c 67
	
	0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,
	0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,//d 68
	
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,
	0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,//e 69
	
	0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//f 70
	
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,
	0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,//g 71
	
	0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,
	0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//h 72
	
	0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//i 73
	
	0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,
	0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,//j 74
	
	0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,
	0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,//k 75
	
	0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//l 76
	
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
	0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,//m 77
	
	0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,
	0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//n 78
	
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,
	0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//o 79
	
	0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,
	0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,//p 80
	
	0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,
	0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,//q 81
	
	0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,
	0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,//r 82
	
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,
	0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,//s 83
	
	0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,
	0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,//t 84
	
	0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,
	0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//u 85
	
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,
	0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,//v 86
	
	0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,
	0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,//w 87
	
	0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,
	0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,//x 88
	
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,
	0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,//y 89
	
	0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
	0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,//z 90
	
	0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,
	0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,//{ 91
	
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,//| 92
	
	0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,
	0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,//} 93
	
	0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//~ 94
};

void OLED_WriteCommand(uint8_t Command)
{
	I2C_Start();
	I2C_Send_Byte(0x78);		//从机地址
	I2C_Send_Byte(0x00);		//写命令
	I2C_Send_Byte(Command); 
	I2C_Stop();
}

void OLED_WriteData(uint8_t Data)
{
	I2C_Start();
	I2C_Send_Byte(0x78);		//从机地址
	I2C_Send_Byte(0x40);		//写数据
	I2C_Send_Byte(Data);
	I2C_Stop();
}

/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//设置Y位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置高4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X位置低4位
}

/**
  * @brief  OLED清屏
  * @param  无
  * @retval 无
  */
void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

/**
  * @brief  OLED显示一个字符
  * @param  Line 行位置，范围：1~4
  * @param  Column 列位置，范围：1~16
  * @param  Char 要显示的一个字符，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{      	
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//设置光标位置在上半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//显示上半部分内容
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置光标位置在下半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//显示下半部分内容
	}
}

/**
  * @brief  OLED显示字符串
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}

/**
  * @brief  OLED次方函数
  * @retval 返回值等于X的Y次方
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

/**
  * @brief  OLED显示数字（十进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十进制，带符号数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(Line, Column, '+');
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(Line, Column, '-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十六进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @retval 无
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)							
	{
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			OLED_ShowChar(Line, Column + i, SingleNumber + '0');
		}
		else
		{
			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

/**
  * @brief  OLED显示数字（二进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
	}
}

void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//上电延时
	{
		for (j = 0; j < 1000; j++);
	}
	
	I2C_Init(1);			//端口初始化
	
	OLED_WriteCommand(0xAE);	//关闭显示
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//设置显示开始行
	
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度控制
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/倒转显示

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开启显示
		
	OLED_Clear();				//OLED清屏
}
/******************************************************************************/
void RGB_LED_Init(void)
{
   LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); /* GPIO 时钟使能 */
   LPC_GPIO1->DIR |= (1UL << 9); /*将 GPIO1_9 作为输出口*/
   LPC_GPIO2->DIR |= (1UL << 8); /*配置GPIO2_8为输出模式 */  // RGB_Green
   LPC_GPIO2->DIR |= (1UL << 9); /*配置GPIO2_8为输出模式 */  // RGB_Red
   LPC_GPIO2->DIR |= (1UL << 10); /*配置GPIO2_10为输出模式 */ // RGB_Blue
}

void LED_Toggle(void)
{
	LPC_GPIO1->DATA ^= (1UL <<9);/* LED 闪烁切换 */
	T16B0_delay_ms(50);
}

/* 翻转RGB_Blue蓝灯 */
void RGB_Blue_Toggle(void)
{
	LPC_GPIO2->DATA  ^=  (1UL <<10); /* LED 闪烁切换 */
	T16B0_delay_ms(50);
}
/* 翻转RGB_Green绿灯 */
void RGB_Green_Toggle(void)
{
	LPC_GPIO2->DATA ^= (1UL <<8);/* LED 闪烁切换 */
	T16B0_delay_ms(50);
}

/* 翻转RGB_Green绿灯 */
void RGB_Red_Toggle(void)
{
	LPC_GPIO2->DATA ^= (1UL <<9);/* LED 闪烁切换 */
	T16B0_delay_ms(50);
}
/******************************************************************************/
