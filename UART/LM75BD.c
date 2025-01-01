#include "LM75BD.h"
#include "I2C.h"
#include "UART.h"
#include <stdio.h>  // ����sprintf
#include <string.h> // ����strlen

/**********************************************/
/*  �¶ȴ�����LM75BD�����ݶ�ȡ����  */
/**********************************************/
float Read_Temp_LM75BD(void)
{  
  uint16_t Temputerature_8,Temputerature_16;  //�¶�ֵ��1�ν���8λ
  float Temputerature;   //�洢��õ��¶�ֵ
  //IIC����---Ĭ�������¶�ģʽ
	  //����(0x91)1001 0001��1001,Ӳ�����ߣ� 0001���ӻ���ַ--000   ��ģʽ--1
  I2C_Start();
  I2C_Send_Byte(0x91);
  Temputerature_8 = I2C_Recieve_Byte();//��LM75BD�¶ȼĴ����ĸ߰�λ����   
  Temputerature_16 = (Temputerature_8 <<8)+(I2C_Recieve_Byte());
  I2C_Stop();  

  Temputerature_16 = Temputerature_16 >> 5;//1LSB=0.125��---����λΪ��Ч����(�Ƴ�)
  /* Temputerature_16:�¶ȼĴ���������D0--D10:����D10Ϊ�¶ȵ���������*/
	
  //���¶�
  if(Temputerature_16&0x0400)
  Temputerature = -(~(Temputerature_16&0x03FF)+1)*0.125;//���¶ȵ����ݵ�ת��(�����ƵĲ���+1)
  //���¶�
  else 
  Temputerature = 0.125*(float)Temputerature_16;
  
  //�����¶�ֵ 1LSB=0.01��
  return Temputerature;
}

///******************************************************************
// * ������: send_temperature
// * ����:�����¶�ֵ�����ڣ����϶ȣ�
// * ����: temperature�¶�ֵ
//******************************************************************/
//void Send_Temp_LM75BD(float temperature) {
//    char Temp_Str[16];  // ���ڴ洢ת������ַ���
//    sprintf(Temp_Str, "%.3f", temperature); // ��������ת��Ϊ�ַ�����������λС��
//    // �����ַ���������
//    UART_Send((uint8_t *)Temp_Str, strlen(Temp_Str));  // �����¶��ַ���
//    UART_Send((uint8_t *)" C", 2);  // ��ӻس�����
//	UART_Send(" \n",2);
//}
