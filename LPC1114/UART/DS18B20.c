#include "DS18B20.h"
#include "Delay.h"
/******************************************************************
 * �� �� �� �ƣ�bsp_ds18b20_GPIO_Init
 * �� �� ˵ ����MLX90614�����ų�ʼ��
 * �� �� �� �Σ���
 * �� �� �� �أ�1δ��⵽����   0��⵽����
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
char DS18B20_Init(void)
{
    unsigned char ret = 255;

    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // ʹ�� GPIO ʱ��
    LPC_GPIO0->DIR |= (1UL << 6); // ���� PIO1_10 Ϊ���

	
    ret = DS18B20_Check();//��������Ƿ����
    return ret;
}

void DQ_OUT(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // ʹ�� GPIO ʱ��
	LPC_GPIO0->DIR |= (1UL << 6); // ���� PIO1_10 Ϊ���
}

void DQ_IN(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // ʹ�� GPIO ʱ��
	LPC_GPIO0->DIR &= ~(1UL << 6); // �� P3.5 ����Ϊ���루������
}

uint8_t DQ_GET(void)
{
	uint8_t bitVal = 0;			
	bitVal= (LPC_GPIO0->DATA>>6)&0x01;
	return	bitVal;
} 
/**
  * @��������GPIOSetValue
  * @����������/���һ����GPIO�˿�X��X�Ƕ˿ںţ��ϵ�һЩ�ض��ܽ��ϵ�λֵ�� 
  * @�������˿ںţ�λ��ַ��λֵ
  * @����ֵ����
  */
void DQ( uint8_t bitVal )
{
   /* ���ֵ�ǣ����� GPIOx_DAT û�����ã����� DATA
  Ϊ 1�� ���ֵ�� 0������ GPIOx_DAT �Ѿ������ˣ� ���
  DATA Ϊ 0���������������ԡ��ڶ˿�3�ϣ�ֻ��0��3λ�������λֵ�����˷�Χ��û�д��󱣻�	�� */

	  if ( !(LPC_GPIO0->DATA & (0x1<<6)) && (bitVal == 1) )
	  {
		LPC_GPIO0->DATA |= (0x1<<6);
	  }
	  else if ( (LPC_GPIO0->DATA & (0x1<<6)) && (bitVal == 0) )
	  {
		LPC_GPIO0->DATA &= ~(0x1<<6);
	  }	  	
}

/******************************************************************
 * �� �� �� �ƣ�DS18B20_Read_Byte
 * �� �� ˵ ������DS18B20��ȡһ���ֽ�
 * �� �� �� �Σ���
 * �� �� �� �أ���ȡ�����ֽ�����
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
uint8_t DS18B20_Read_Byte(void)
{
        uint8_t i=0,dat=0;

        for (i=0;i<8;i++)
        {
        DQ_OUT();//����Ϊ����ģʽ
        DQ(0); //����
        T16B0_delay_us(2);
        DQ(1); //�ͷ�����
        DQ_IN();//����Ϊ����ģʽ
        T16B0_delay_us(12);
        dat>>=1;
        if( DQ_GET() )
        {
            dat=dat|0x80;
        }
        T16B0_delay_us(50);
     }
        return dat;
}

void DS18B20_Write_Byte(uint8_t dat)
{
        uint8_t i;
        DQ_OUT();//�������ģʽ
        for (i=0;i<8;i++)
        {
                if ( (dat&0x01) ) //д1
                {
                        DQ(0);
                        T16B0_delay_us(2);
                        DQ(1);
                        T16B0_delay_us(60);
                }
                else //д0
                {
                        DQ(0);//����60us
                        T16B0_delay_us(60);
                        DQ(1);//�ͷ�����
                        T16B0_delay_us(2);
                }
        dat=dat>>1;//������һλ
        }
}

uint8_t DS18B20_Check(void)
{
        uint8_t timeout=0;
    //��λDS18B20
        DQ_OUT(); //����Ϊ���ģʽ
        DQ(0); //����DQ
        T16B0_delay_us(750); //����750us
        DQ(1); //����DQ
        T16B0_delay_us(15);  //15us

    //����Ϊ����ģʽ
        DQ_IN();
    //�ȴ����ͣ�����˵����Ӧ��
        while ( DQ_GET() &&timeout<200)
        {
                timeout++;//��ʱ�ж�
                T16B0_delay_us(1);
        };
        //�豸δӦ��
        if(timeout>=200)
                return 1;
        else
                timeout=0;

        //�ȴ�18B20�ͷ�����
        while ( !DQ_GET() &&timeout<240)
        {
                timeout++;//��ʱ�ж�
                T16B0_delay_us(1);
        };
    //�ͷ�����ʧ��
        if(timeout>=240)
                return 1;

        return 0;
}

void DS18B20_Start(void)
{
        DS18B20_Check();                //��ѯ�Ƿ����豸Ӧ��
        DS18B20_Write_Byte(0xcc);   //�������������豸����Ѱַ
        DS18B20_Write_Byte(0x44);   //�����¶�ת��
}

float DS18B20_GetTemperture(void)
{
        uint16_t temp;
        uint8_t dataL=0,dataH=0;
        float value;

        DS18B20_Start();
        DS18B20_Check();
        DS18B20_Write_Byte(0xcc);//�������������豸����Ѱַ
        DS18B20_Write_Byte(0xbe);// ��ȡ��������
        dataL=DS18B20_Read_Byte(); //LSB
        dataH=DS18B20_Read_Byte(); //MSB
        temp=(dataH<<8)+dataL;//��������

        if(dataH&0X80)//��λΪ1��˵���Ǹ��¶�
        {
                temp=(~temp)+1;
                value=temp*(-0.0625);
        }
        else
        {
                value=temp*0.0625;
        }
        return value;
}

//uint32_t GPIOGetbit(uint32_t portNum,uint32_t bitPosi)
//{
//	uint32_t bitVal;
//	switch(portNum)
//	{
//		case PORT0:
//			bitVal=(LPC_GPIO0->DATA>>bitPosi)&0x01;
//			return	bitVal;
//			break;
//		case PORT1:
//			bitVal=(LPC_GPIO1->DATA>>bitPosi)&0x01;
//			return	bitVal;
//			break;
//		case PORT2:
//			bitVal=(LPC_GPIO2->DATA>>bitPosi)&0x01;
//			return	bitVal;
//			break;
//		case PORT3:
//			bitVal=(LPC_GPIO3->DATA>>bitPosi)&0x01;
//			return	bitVal;
//			break;
//	}	
//} 
