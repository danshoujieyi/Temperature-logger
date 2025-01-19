#ifndef __I2C_H
#define __I2C_H

#include "LPC11xx.h"

 /* I2C ���ƼĴ��� */  
#define I2CONSET_AA			0x00000004  // �Ƿ����Ӧ���ź�����λ�����Ƿ�����Ϊ�ӻ�ģʽ
#define I2CONSET_SI			0x00000008  // I2C�жϱ�־λ
#define I2CONSET_STO		0x00000010 // ֹͣ��־λ
#define I2CONSET_STA		0x00000020  // ��ʼ��־λ
#define I2CONSET_I2EN		0x00000040   // I2C�ӿ�����λ
/* I2C ������ƼĴ���λ���Ĵ��� */
#define I2CONCLR_AAC		0x00000004    // ��Ӧ���ź�����λ
#define I2CONCLR_SIC		0x00000008  // ��I2C�жϱ�־λ
#define I2CONCLR_STAC		0x00000020  // �忪ʼ��־λ
#define I2CONCLR_I2ENC		0x00000040  // ��I2C�ӿ�����λ

#define I2SCLH_SCLH			0x00000180  /* I2C SCL Duty Cycle High Reg */
#define I2SCLL_SCLL			0x00000180  /* I2C SCL Duty Cycle Low Reg */
#define I2SCLH_HS_SCLH		0x00000030  /* Fast Plus I2C SCL Duty Cycle High Reg */
#define I2SCLL_HS_SCLL		0x00000030  /* Fast Plus I2C SCL Duty Cycle Low Reg */

#define TRUE 1
#define FALSE 0
 
void I2C_Init(uint8_t Mode);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Send_Byte(uint8_t dat);
uint8_t I2C_Recieve_Byte(void);


#endif
