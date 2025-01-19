/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			MX25L1602.c
** Descriptions:		SPI�µ�SST25VF016B���������� 
**
**------------------------------------------------------------------------------------------------------
** Created by:			Litiantian
** Created date:		2007-04-16
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:		
********************************************************************************************************/
#include <stdio.h>
#include "LPC11xx.h"			/* LPC11xx ����Ĵ��� */
#include "MX25L1605Drv.h"
/* ��ֲ�������ʱ��Ҫ�޸����µĺ������ */
#define		CE_Low()		LPC_GPIO0->DATA &= ~(0x1<<7)			//P0.7=0
#define     CE_High()		LPC_GPIO0->DATA |= (0x1<<7);			//P0.7=0

/* SPI��ʼ�� */
/*******************************************************************************************
** �������ƣ�SPIInit															
** ����˵������ʼ��SPI��				
** ��ڲ�������																
** ���ڲ�������																
*******************************************************************************************/
void  SPIInit(void)
{  
	LPC_SYSCON->PRESETCTRL|=0x01;  		//ȡ��SSP0��λ
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<11);	//��SSP����
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);	//ʹ��IO���ÿ�ʱ��
	LPC_SYSCON->SSP0CLKDIV =0x01;		//ʱ�Ӳ���Ƶ
//	LPC_IOCON->PIO0_7=0x01;				//����CS	Ƭѡ
	LPC_IOCON->PIO0_7=0x00;				//����GPIO
	LPC_GPIO0->DIR	|=0x080;			//����P0_7Ϊ���	
	LPC_SSP0->CR0 =(0x01<<8)|			//SCRʱ�ӷ�Ƶ 	f=PCLK/(CPSDVSRX[SCR+1])
				  (0x00<<7)|			//ʱ�������λ
				  (0x00<<6)|			//ʱ���������
				  (0x00<<4)|			// FRF֡��ʽ 00=SPI,01=SSI 10=Microwire,11=����
				  (0x07<<0);			//0111=8bit,0011=4bit,1111=16bit			  
				  
	LPC_SSP0->CR1 =(0x00<<3)|	//�ӻ�������ܣ�1=��ֹ
				  (0x00<<2)|	//MSѡ��0=������1=�ӻ���
				  (0x01<<1)|	//SSPʹ��
				  (0x00<<0);	//����ģʽ
	LPC_SSP0->CPSR=0x02;			//PCLK��Ƶֵ
	LPC_SSP0->ICR=0x03;			//�ж����
}

/************************************************************************
** ��������: Send_Byte													
** �������ܣ�ͨ��Ӳ��SPI����һ���ֽڵ�MX25L1602					
** ��ڲ���:data															
** ���ڲ���:��																
************************************************************************/
void Send_Byte(uint8_t data)
{
    LPC_SSP0->DR = data;
    while (LPC_SSP0->SR&0x010!=0);			// �ȴ�BSY=0�����ȴ����ݷ���
}

/************************************************************************
** ��������:Get_Byte														
** ��������:ͨ��Ӳ��SPI�ӿڽ���һ���ֽڵ�������						
** ��ڲ���:��																
** ���ڲ���:��																
************************************************************************/
uint8_t Get_Byte(void)
{
	LPC_SSP0->DR = 0xff;			// ���͸��������Բ���ʱ��,���ݱ���û���ô�
    while (LPC_SSP0->SR&0x010!=0);	// �ȴ�BSY=0�����ȴ����ݷ���
    return (LPC_SSP0->DR);		// ���ؽ��յ�������
}


/* ���º�������ֲʱ�����޸� */
/************************************************************************
** ��������:MX25L1602_RD																										
** ��������:MX25L1602�Ķ�����,��ѡ���ID�Ͷ����ݲ���				
** ��ڲ���:
**			INT32U Dst��Ŀ���ַ,��Χ 0x0 - MAX_ADDR��MAX_ADDR = 0x1FFFFF��				
**      	INT32U NByte:	Ҫ��ȡ�������ֽ���
**			INT8U* RcvBufPt:���ջ����ָ��			
** ���ڲ���:�����ɹ��򷵻�OK,ʧ���򷵻�ERROR		
** ע	 ��:��ĳ������,ĳһ��ڲ�����Ч,���ڸ���ڲ�������Invalid���ò�����������
************************************************************************/
uint8_t MX25L1602_RD(uint32_t Dst, uint32_t NByte,uint8_t* RcvBufPt)
{
	uint32_t i = 0;
	if ((Dst+NByte > MAX_ADDR)||(NByte == 0))	return (ERROR);	 //	�����ڲ���
	
	CE_Low();			
	Send_Byte(0x0B); 						// ���Ͷ�����
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	// ���͵�ַ��Ϣ:�õ�ַ��3���ֽ����
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(0xFF);						// ����һ�����ֽ��Զ�ȡ����
	for (i = 0; i < NByte; i++)		
	{
		RcvBufPt[i] = Get_Byte();		
	}
	CE_High();			
	return (OK);
}

/************************************************************************
** ��������:MX25L1602_RdID																										
** ��������:MX25L1602�Ķ�ID����,��ѡ���ID�Ͷ����ݲ���				
** ��ڲ���:
**			idtype IDType:ID���͡��û�����Jedec_ID,Dev_ID,Manu_ID������ѡ��
**			INT32U* RcvbufPt:�洢ID������ָ��
** ���ڲ���:�����ɹ��򷵻�OK,ʧ���򷵻�ERROR		
** ע	 ��:������Ĳ���������Ҫ���򷵻�ERROR
************************************************************************/
uint8_t MX25L1602_RdID(idtype IDType, uint32_t* RcvbufPt)
{
	uint32_t temp = 0;
	if (IDType == Jedec_ID)
	{
		CE_Low();			
		Send_Byte(0x9F);		 		// ���Ͷ�JEDEC ID����(9Fh)
    	temp = (temp | Get_Byte()) << 8;// �������� 
		temp = (temp | Get_Byte()) << 8;	
		temp = (temp | Get_Byte()); 	// �ڱ�����,temp��ֵӦΪ0xBF2541
		CE_High();			
		*RcvbufPt = temp;
		return (OK);
	}
	
	if ((IDType == Manu_ID) || (IDType == Dev_ID) )
	{
		CE_Low();			
		Send_Byte(0x90);				// ���Ͷ�ID���� (90h or ABh)
    	Send_Byte(0x00);				// ���͵�ַ
		Send_Byte(0x00);				// ���͵�ַ
		Send_Byte(IDType);				// ���͵�ַ - ����00H����01H
		temp = Get_Byte();				// ���ջ�ȡ�������ֽ�
		CE_High();			
		*RcvbufPt = temp;
		return (OK);
	}
	else
	{
		return (ERROR);	
	}
}

/************************************************************************
** ��������:MX25L1602_WR											
** ��������:MX25L1602��д��������д1���Ͷ�����ݵ�ָ����ַ									
** ��ڲ���:
**			INT32U Dst��Ŀ���ַ,��Χ 0x0 - MAX_ADDR��MAX_ADDR = 0x1FFFFF��				
**			INT8U* SndbufPt:���ͻ�����ָ��
**      	INT32U NByte:Ҫд�������ֽ���
** ���ڲ���:�����ɹ��򷵻�OK,ʧ���򷵻�ERROR		
** ע	 ��:��ĳ������,ĳһ��ڲ�����Ч,���ڸ���ڲ�������Invalid���ò�����������
************************************************************************/
uint8_t MX25L1602_WR(uint32_t Dst, uint8_t* SndbufPt, uint32_t NByte)
{
	uint32_t temp = 0,i = 0,StatRgVal = 0;
	if (( (Dst+NByte-1 > MAX_ADDR)||(NByte == 0) ))
	{
		return (ERROR);	 //	�����ڲ���
	}
   	CE_Low();			 
	Send_Byte(0x05);							// ���Ͷ�״̬�Ĵ�������
	temp = Get_Byte();							// ������õ�״̬�Ĵ���ֵ
	CE_High();								

	CE_Low();			
	Send_Byte(0x50);							// ʹ״̬�Ĵ�����д
	CE_High();			
	CE_Low();			
	Send_Byte(0x01);							// ����д״̬�Ĵ���ָ��
	Send_Byte(0);								// ��0BPxλ��ʹFlashоƬȫ����д 
	CE_High();			

		
	for(i = 0; i < NByte; i++)
	{
		CE_Low();			
		Send_Byte(0x06);						// ����дʹ������
		CE_High();			

		CE_Low();			
		Send_Byte(0x02); 						// �����ֽ�������д����
		Send_Byte((((Dst+i) & 0xFFFFFF) >> 16));// ����3���ֽڵĵ�ַ��Ϣ 
		Send_Byte((((Dst+i) & 0xFFFF) >> 8));
		Send_Byte((Dst+i) & 0xFF);
		Send_Byte(SndbufPt[i]);					// ���ͱ���д������
		CE_High();			

		do
		{
		  	CE_Low();			 
			Send_Byte(0x05);					// ���Ͷ�״̬�Ĵ�������
			StatRgVal = Get_Byte();				// ������õ�״̬�Ĵ���ֵ
			CE_High();								
  		}
		while (StatRgVal == 0x03);				// һֱ�ȴ���ֱ��оƬ����
	}

	CE_Low();			
	Send_Byte(0x06);							// ����дʹ������
	CE_High();			

	CE_Low();			
	Send_Byte(0x50);							// ʹ״̬�Ĵ�����д
	CE_High();			
	CE_Low();			
	Send_Byte(0x01);							// ����д״̬�Ĵ���ָ��
	Send_Byte(temp);							// �ָ�״̬�Ĵ���������Ϣ 
	CE_High();

	return (OK);		
}

/************************************************************************
** ��������:MX25L1602_Erase												
** ��������:����ָ����������ѡȡ���Ч���㷨����								
** ��ڲ���:
**			INT32U sec1����ʼ������,��Χ(0~499)
**			INT32U sec2����ֹ������,��Χ(0~499)
** ���ڲ���:�����ɹ��򷵻�OK,ʧ���򷵻�ERROR		
************************************************************************/
uint8_t MX25L1605_Erase(uint32_t uiStartSect, uint32_t uiEndSect)
{
	uint32_t temp=0;
    uint32_t ucStatus = 0;	  			
	
	/*  �����ڲ��� */
	if ((uiStartSect > SEC_MAX)||(uiEndSect > SEC_MAX))	
	{
		return (ERROR);	
	}
   	if(uiStartSect>uiEndSect)
	{
		temp=uiEndSect;
		uiEndSect=uiStartSect;
	   	uiStartSect=temp;
	}
	ucStatus=_MX25L1605_RDStat();
	__MX25L1605_WrStat(0);
	if(uiStartSect==uiEndSect)
	{
		
	}

   	CE_Low();			 
	Send_Byte(0x05);								// ���Ͷ�״̬�Ĵ�������
	temp1 = Get_Byte();								// ������õ�״̬�Ĵ���ֵ
	CE_High();								

	CE_Low();			
	Send_Byte(0x50);								// ʹ״̬�Ĵ�����д
	CE_High();			
	CE_Low();								  	
	Send_Byte(0x01);								// ����д״̬�Ĵ���ָ��
	Send_Byte(0);									// ��0BPxλ��ʹFlashоƬȫ����д 
	CE_High();
	
	CE_Low();			
	Send_Byte(0x06);								// ����дʹ������
	CE_High();			

	/* ����û��������ʼ�����Ŵ�����ֹ�����ţ������ڲ��������� */
	if (sec1 > sec2)
	{
	   temp2 = sec1;
	   sec1  = sec2;
	   sec2  = temp2;
	} 
	/* ����ֹ���������������������� */
	if (sec1 == sec2)	
	{
	    SecnHdAddr = SEC_SIZE * sec1;				// ������������ʼ��ַ
	    CE_Low();	
    	Send_Byte(0x20);							// ������������ָ��
	    Send_Byte(((SecnHdAddr & 0xFFFFFF) >> 16)); // ����3���ֽڵĵ�ַ��Ϣ
   		Send_Byte(((SecnHdAddr & 0xFFFF) >> 8));
   		Send_Byte(SecnHdAddr & 0xFF);
  		CE_High();			
		do
		{
		  	CE_Low();			 
			Send_Byte(0x05);						// ���Ͷ�״̬�Ĵ�������
			StatRgVal = Get_Byte();					// ������õ�״̬�Ĵ���ֵ
			CE_High();								
  		}
		while (StatRgVal == 0x03);					// һֱ�ȴ���ֱ��оƬ����
		return (OK);			
	}
	
                     /* 		������ʼ��������ֹ��������������ٵĲ������� 							*/	
	
	if (sec2 - sec1 == SEC_MAX)	
	{
		CE_Low();			
		Send_Byte(0x60);							// ����оƬ����ָ��(60h or C7h)
		CE_High();			
		do
		{
		  	CE_Low();			 
			Send_Byte(0x05);						// ���Ͷ�״̬�Ĵ�������
			StatRgVal = Get_Byte();					// ������õ�״̬�Ĵ���ֵ
			CE_High();								
  		}
		while (StatRgVal == 0x03);					// һֱ�ȴ���ֱ��оƬ����
   		return (OK);
	}
	
	no_SecsToEr = sec2 - sec1 +1;					// ��ȡҪ������������Ŀ
	CurSecToEr  = sec1;								// ����ʼ������ʼ����
	
	/* ����������֮��ļ���������ȡ16���������㷨 */
	while (no_SecsToEr >= 16)
	{
	    SecnHdAddr = SEC_SIZE * CurSecToEr;			// ������������ʼ��ַ
	    CE_Low();	
	    Send_Byte(0xD8);							// ����64KB�����ָ��
	    Send_Byte(((SecnHdAddr & 0xFFFFFF) >> 16)); // ����3���ֽڵĵ�ַ��Ϣ
   		Send_Byte(((SecnHdAddr & 0xFFFF) >> 8));
   		Send_Byte(SecnHdAddr & 0xFF);
  		CE_High();			
		do
		{
		  	CE_Low();			 
			Send_Byte(0x05);						// ���Ͷ�״̬�Ĵ�������
			StatRgVal = Get_Byte();					// ������õ�״̬�Ĵ���ֵ
			CE_High();								
  		}
		while (StatRgVal == 0x03);					// һֱ�ȴ���ֱ��оƬ����
		CurSecToEr  += 16;							// ���������16��������,�Ͳ����������ڵĴ�����������
		no_SecsToEr -=  16;							// �������������������������
	}
	/* ����������֮��ļ���������ȡ8���������㷨 */
	while (no_SecsToEr >= 8)
	{
	    SecnHdAddr = SEC_SIZE * CurSecToEr;			// ������������ʼ��ַ
	    CE_Low();	
	    Send_Byte(0x52);							// ����32KB����ָ��
	    Send_Byte(((SecnHdAddr & 0xFFFFFF) >> 16)); // ����3���ֽڵĵ�ַ��Ϣ
   		Send_Byte(((SecnHdAddr & 0xFFFF) >> 8));
   		Send_Byte(SecnHdAddr & 0xFF);
  		CE_High();			
		do
		{
		  	CE_Low();			 
			Send_Byte(0x05);						// ���Ͷ�״̬�Ĵ�������
			StatRgVal = Get_Byte();					// ������õ�״̬�Ĵ���ֵ
			CE_High();								
  		}
		while (StatRgVal == 0x03);					// һֱ�ȴ���ֱ��оƬ����	
		CurSecToEr  += 8;
		no_SecsToEr -=  8;
	}
	/* �������������㷨����ʣ������� */
	while (no_SecsToEr >= 1)
	{
	    SecnHdAddr = SEC_SIZE * CurSecToEr;			// ������������ʼ��ַ
	    CE_Low();	
    	Send_Byte(0x20);							// ������������ָ��
	    Send_Byte(((SecnHdAddr & 0xFFFFFF) >> 16)); // ����3���ֽڵĵ�ַ��Ϣ
   		Send_Byte(((SecnHdAddr & 0xFFFF) >> 8));
   		Send_Byte(SecnHdAddr & 0xFF);
  		CE_High();			
		do
		{
		  	CE_Low();			 
			Send_Byte(0x05);						// ���Ͷ�״̬�Ĵ�������
			StatRgVal = Get_Byte();					// ������õ�״̬�Ĵ���ֵ
			CE_High();								
  		}
		while (StatRgVal == 0x03);					// һֱ�ȴ���ֱ��оƬ����
		CurSecToEr  += 1;
		no_SecsToEr -=  1;
	}
   /* ��������,�ָ�״̬�Ĵ�����Ϣ							*/
	CE_Low();			
	Send_Byte(0x06);								// ����дʹ������
	CE_High();			

	CE_Low();			
	Send_Byte(0x50);								// ʹ״̬�Ĵ�����д
	CE_High();			
	CE_Low();			
	Send_Byte(0x01);								// ����д״̬�Ĵ���ָ��
	Send_Byte(temp1);								// �ָ�״̬�Ĵ���������Ϣ 
	CE_High();    
	return (OK);
}




























