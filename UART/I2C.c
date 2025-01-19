#include "I2C.h"

void I2C_Init(uint8_t Mode)
{
  LPC_SYSCON->PRESETCTRL |= (1<<1);   //ʹI2C�ϵ� I2Cģ�飨������I2Cģ��֮ǰ���������λд1��
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);   //ʹ��I2Cʱ��
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);   // ʹ��IOCONʱ��
  LPC_IOCON->PIO0_4 &= ~0x3F;  
  LPC_IOCON->PIO0_4 |= 0x01;   //��P0.4������Ϊ I2C SCL 
  LPC_IOCON->PIO0_5 &= ~0x3F;  
  LPC_IOCON->PIO0_5 |= 0x01;   //��P0.5������Ϊ I2C SDA 
	
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
	   
  LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);   // ����IOCONʱ�� 
  LPC_I2C->CONSET |= I2CONSET_I2EN;  // ʹ��I2C�ӿ�
}


void I2C_Start(void)
{
  LPC_I2C->CONSET |= I2CONSET_STA;  // ʹ�ܷ��Ϳ�ʼ�ź�
  while(!(LPC_I2C->CONSET & I2CONSET_SI));  // �ȴ���ʼ�źŷ������
  LPC_I2C->CONCLR = I2CONCLR_STAC | I2CONCLR_SIC; // �����ʼSTARTλ��SIλ 
}


void I2C_Stop(void)
{
   LPC_I2C->CONCLR = I2CONCLR_SIC;  // ��SI��־λ
   LPC_I2C->CONSET |= I2CONSET_STO;  // ����ֹͣ�ź�
   while( LPC_I2C->CONSET & I2CONSET_STO );  // �ȴ�ֹͣ�źŷ������ 
}

/****************************************************/
/* �������ܣ�I2C����һ�ֽ�����  */
/* ��ڲ�����dat : Ҫ���͵��ֽ�  */
/***************************************************/
void I2C_Send_Byte(uint8_t dat)
{
   LPC_I2C->DAT = dat;  // ���ֽ�д��DAT�Ĵ���
   LPC_I2C->CONCLR = I2CONSET_SI;  // ���SI��־(1<<3)
   while(!(LPC_I2C->CONSET & I2CONSET_SI));  // �ȴ����ݷ������
}


/***************************************************/
/* �������ܣ�I2C����һ�ֽ�����  */
/* ��ڲ�����rebyte : Ҫ���յ��ֽ�  */
/***************************************************/
uint8_t I2C_Recieve_Byte(void)
{
  uint8_t ReByte;
  LPC_I2C->CONCLR = I2CONCLR_SIC;   // ��AA��SI��־
  while(!(LPC_I2C->CONSET & I2CONSET_SI));  // �ȴ������������
  ReByte = (uint8_t)LPC_I2C->DAT;  // �ѽ��յ������ݸ���rebyte
  return ReByte;
}
