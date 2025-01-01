#include "LM75BD.h"
#include "I2C.h"
#include "UART.h"
#include <stdio.h>  // 用于sprintf
#include <string.h> // 用于strlen

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
  Temputerature_8 = I2C_Recieve_Byte();//读LM75BD温度寄存器的高八位数据   
  Temputerature_16 = (Temputerature_8 <<8)+(I2C_Recieve_Byte());
  I2C_Stop();  

  Temputerature_16 = Temputerature_16 >> 5;//1LSB=0.125℃---低五位为无效数据(移出)
  /* Temputerature_16:温度寄存器的数据D0--D10:其中D10为温度的正负数据*/
	
  //负温度
  if(Temputerature_16&0x0400)
  Temputerature = -(~(Temputerature_16&0x03FF)+1)*0.125;//负温度的数据的转换(二进制的补码+1)
  //正温度
  else 
  Temputerature = 0.125*(float)Temputerature_16;
  
  //返回温度值 1LSB=0.01℃
  return Temputerature;
}

///******************************************************************
// * 函数名: send_temperature
// * 描述:发送温度值到串口（摄氏度）
// * 参数: temperature温度值
//******************************************************************/
//void Send_Temp_LM75BD(float temperature) {
//    char Temp_Str[16];  // 用于存储转换后的字符串
//    sprintf(Temp_Str, "%.3f", temperature); // 将浮点数转换为字符串，保留三位小数
//    // 发送字符串到串口
//    UART_Send((uint8_t *)Temp_Str, strlen(Temp_Str));  // 发送温度字符串
//    UART_Send((uint8_t *)" C", 2);  // 添加回车换行
//	UART_Send(" \n",2);
//}
