/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:       MX25L1602.c
** Descriptions:    SST25VF016B����
**
**------------------------------------------------------------------------------------------------------
** Created by:      Litiantian
** Created date:    2007-04-16
** Version:         1.0
** Descriptions:    The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:     
** Modified date:   
** Version:         
** Descriptions:    
********************************************************************************************************/
#include   "MX25L1602Drv.h"

/*
 * ��ֲ�������ʱ��Ҫ�޸����µĺ������ 
 */
#define     CE_Low()    LPC_GPIO0->DATA &= ~SPI_CS;   
#define     CE_High()   LPC_GPIO0->DATA |=  SPI_CS;

/*********************************************************************************************************
** �������ƣ�SPIInit
** ����˵������ʼ��SPI
** �����������
** �����������
*********************************************************************************************************/
void  SSP_Init (void)
{  
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);                             /* ����IOCONģ��ʱ��            */
    LPC_IOCON->PIO0_2 &= ~0x07;                                         /* ��ʼ��SPI0����               */
    LPC_GPIO0->DIR    |= SPI_CS;

    LPC_IOCON->PIO0_6 |= 0x02;
    LPC_IOCON->PIO0_8 |= 0x01;
    LPC_IOCON->PIO0_9 |= 0x01;

    LPC_SYSCON->PRESETCTRL    |= 0x01;                                  /* ��ֹSPI0��λ                 */

    LPC_IOCON->SCK_LOC         = 0x02;                                  /* P0.6����ΪSCK                */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 11);                             /* ��SPI0����                 */
    LPC_SYSCON->SSP0CLKDIV     = 0x01;                                  /* SSPʱ�ӷ�Ƶ                  */
   
    LPC_SSP0->CR0 = (0x01 << 8) |                                       /* SCR  ����SPIʱ�ӷ�Ƶ         */
                    (0x00 << 7) |                                       /* CPHA ʱ�������λ,           */
                                                                        /* ��SPIģʽ��Ч                */
                    (0x00 << 6) |                                       /* CPOL ʱ���������,           */
                                                                        /* ��SPIģʽ��Ч                */
                    (0x00 << 4) |                                       /* FRF  ֡��ʽ 00=SPI,01=SSI,   */
                                                                        /* 10=Microwire,11=����         */
                    (0x07 << 0);                                        /* DSS  ���ݳ���,0000-0010=����,*/
                                                                        /* 0011=4λ,0111=8λ,1111=16λ  */

    LPC_SSP0->CR1 = (0x00 << 3) |                                       /* SOD  �ӻ��������,1=��ֹ     */
                    (0x00 << 2) |                                       /* MS   ����ѡ��,0=����,1=�ӻ�  */
                    (0x01 << 1) |                                       /* SSE  SSPʹ��                 */
                    (0x00 << 0);                                        /* LBM  ��дģʽ                */
             
    LPC_SSP0->CPSR = 2;                                                 /* PCLK��Ƶֵ                   */
    LPC_SSP0->ICR  = 0x03;                                              /* �ж�����Ĵ���               */
}

/*********************************************************************************************************
** ��������: Send_Byte
** �������ܣ�ͨ��Ӳ��SPI����һ���ֽڵ�MX25L1602
** �������: data
** �������: ��
** �� �� ֵ����
*********************************************************************************************************/
void Send_Byte (INT8U data)
{
    LPC_SSP0->DR = data;
    while( (LPC_SSP0->SR & 0x10) == 0x10);                              /* �ȴ�TFE��λ��������FIFO��    */
    data = LPC_SSP0->DR;   
}

/*********************************************************************************************************
** ��������:Get_Byte
** ��������:ͨ��Ӳ��SPI�ӿڽ���һ���ֽڵ�������
** �������:��
** �������:��
*********************************************************************************************************/
INT8U Get_Byte (void)
{
    LPC_SSP0->DR = 0xFF;                                                /* ���͸��������Բ���ʱ��       */
    while ( 0 == (LPC_SSP0->SR & 0x01));                                /* �ȴ����ݷ������             */
   /*
    * �жϵ�ǰ�Ƿ���У��Ƿ���TX Or RX��
    */
    while( LPC_SSP0->SR & (1 << 4));
   /*
    * �ж��Ƿ��ѽ��յ����ݣ������ж��Ƿ�������,����
    * �µ�TX�����ٴ�д��LPC_SSP0->DR�Ĵ���
    */
   while( LPC_SSP0->SR & (1 << 2) == 0x00); 
   return (INT8U)(LPC_SSP0->DR);                                        /* ���ؽ��յ�������             */
}
 
/*********************************************************************************************************
** �û��ӿڲ�
** ���º�������ֲʱ�����޸�
*********************************************************************************************************/
/********************************************************************************************************
** ��������:MX25L1602_RD
** ��������:MX25L1602�Ķ�����,��ѡ���ID�Ͷ����ݲ���
** �������:
**          INT32U Dst��Ŀ���ַ,��Χ 0x0 - MAX_ADDR��MAX_ADDR = 0x1FFFFF��
**          INT32U NByte:  Ҫ��ȡ�������ֽ���
**          INT8U* RcvBufPt:���ջ����ָ��
** �������:�����ɹ��򷵻�OK,ʧ���򷵻�ERROR
** ����˵��:��ĳ������,ĳһ��ڲ�����Ч,���ڸ���ڲ�������Invalid���ò�����������
**********************************************************************************************************/
INT8U MX25L1602_RD(INT32U Dst, INT32U NByte,INT8U* RcvBufPt)
{
  INT32U i = 0;
  if ((Dst+NByte > MAX_ADDR)||(NByte == 0))  return (ERROR);            /*  �����ڲ���                */
  
  CE_Low();
  Send_Byte(0x0B);                                                      /* ���Ͷ�����                   */
  Send_Byte(((Dst & 0xFFFFFF) >> 16));                                  /* ���͵�ַ��Ϣ:�õ�ַΪ3���ֽ� */
  Send_Byte(((Dst & 0xFFFF) >> 8));
  Send_Byte(Dst & 0xFF);
  Send_Byte(0xFF);                                                      /* ����һ�����ֽ��Զ�ȡ����     */
  for (i = 0; i < NByte; i++) {
    RcvBufPt[i] = Get_Byte();
  }
  CE_High();
  return (OK);
}

/*********************************************************************************************************
** ��������:MX25L1602_RdID
** ��������:MX25L1602�Ķ�ID����,��ѡ���ID�Ͷ����ݲ���
** �������:
**          idtype IDType:ID���͡��û�����Jedec_ID,Dev_ID,Manu_ID������ѡ��
**          INT32U* RcvbufPt:�洢ID������ָ��
** �������:�����ɹ��򷵻�OK,ʧ���򷵻�ERROR
** ����˵��:������Ĳ���������Ҫ���򷵻�ERROR
*********************************************************************************************************/
INT8U MX25L1602_RdID(idtype IDType, INT32U* RcvbufPt)
{
  INT32U temp = 0;
  if (IDType == Jedec_ID) {
    CE_Low();
    Send_Byte(0x9F);                                                    /* ���Ͷ�JEDEC ID����(9Fh)      */
    temp = (temp | Get_Byte()) << 8;                                    /* ��������                     */
    temp = (temp | Get_Byte()) << 8;
    temp = (temp | Get_Byte());                                         /* �ڱ�����,temp��ֵӦΪ0xBF2541*/
    CE_High();
    *RcvbufPt = temp;
    return (OK);
  }

  if ((IDType == Manu_ID) || (IDType == Dev_ID) ) {
    CE_Low();
    Send_Byte(0x90);                                                    /* ���Ͷ�ID���� (90h or ABh)    */
    Send_Byte(0x00);                                                    /* ���͵�ַ                     */
    Send_Byte(0x00);                                                    /* ���͵�ַ                     */
    Send_Byte(IDType);                                                  /* ���͵�ַ - ����00H����01H    */
    temp = Get_Byte();                                                  /* ���ջ�ȡ�������ֽ�           */
    CE_High();
    *RcvbufPt = temp;
    return (OK);
  } else {
    return (ERROR);
  }
}

/*********************************************************************************************************
** ��������:MX25L1602_WR
** ��������:MX25L1602��д��������д1���Ͷ�����ݵ�ָ����ַ
** �������:
**          INT32U Dst��Ŀ���ַ,��Χ 0x0 - MAX_ADDR��MAX_ADDR = 0x1FFFFF��
**          INT8U* SndbufPt:���ͻ�����ָ��
**          INT32U NByte:Ҫд�������ֽ���
** �������:�����ɹ��򷵻�OK,ʧ���򷵻�ERROR
** ����˵��:��ĳ������,ĳһ��ڲ�����Ч,���ڸ���ڲ�������Invalid���ò�����������
*********************************************************************************************************/
INT8U MX25L1602_WR(INT32U Dst, INT8U* SndbufPt, INT32U NByte)
{
  INT32U temp = 0,i = 0,StatRgVal = 0;
  if (( (Dst+NByte-1 > MAX_ADDR)||(NByte == 0) )) {
    return (ERROR);                                                     /*  �����ڲ���                */
  }
  CE_Low();
  Send_Byte(0x05);                                                      /* ���Ͷ�״̬�Ĵ�������         */
  temp = Get_Byte();                                                    /* ������õ�״̬�Ĵ���ֵ       */
  CE_High();

  CE_Low();
  Send_Byte(0x50);                                                      /* ʹ״̬�Ĵ�����д             */
  CE_High();
  CE_Low();
  Send_Byte(0x01);                                                      /* ����д״̬�Ĵ���ָ��         */
  Send_Byte(0);                                                         /* ��0BPxλ��ʹFlashоƬȫ����д*/
  CE_High();

  for(i = 0; i < NByte; i++) {
    CE_Low();
    Send_Byte(0x06);                                                    /* ����дʹ������               */
    CE_High();

    CE_Low();
    Send_Byte(0x02);                                                    /* �����ֽ�������д����         */
    Send_Byte((((Dst+i) & 0xFFFFFF) >> 16));                            /* ����3���ֽڵĵ�ַ��Ϣ        */
    Send_Byte((((Dst+i) & 0xFFFF) >> 8));
    Send_Byte((Dst+i) & 0xFF);
    Send_Byte(SndbufPt[i]);                                             /* ���ͱ���д������             */
    CE_High();

    do {
      CE_Low();
      Send_Byte(0x05);                                                  /* ���Ͷ�״̬�Ĵ�������         */
      StatRgVal = Get_Byte();                                           /* ������õ�״̬�Ĵ���ֵ       */
      CE_High();
    } while (StatRgVal == 0x03);                                        /* һֱ�ȴ���ֱ��оƬ����       */
  }

  CE_Low();
  Send_Byte(0x06);                                                      /* ����дʹ������               */
  CE_High();

  CE_Low();
  Send_Byte(0x50);                                                      /* ʹ״̬�Ĵ�����д             */
  CE_High();
  CE_Low();
  Send_Byte(0x01);                                                      /* ����д״̬�Ĵ���ָ��         */
  Send_Byte(temp);                                                      /* �ָ�״̬�Ĵ���������Ϣ       */
  CE_High();

  return (OK);
}

/*********************************************************************************************************
** ��������:MX25L1602_Erase
** ��������:����ָ����������ѡȡ���Ч���㷨����
** �������:
**          INT32U sec1����ʼ������,��Χ(0~499)
**          INT32U sec2����ֹ������,��Χ(0~499)
** �������:�����ɹ��򷵻�OK,ʧ���򷵻�ERROR
*********************************************************************************************************/
INT8U MX25L1602_Erase(INT32U sec1, INT32U sec2)
{
  INT8U  temp1 = 0,temp2 = 0,StatRgVal = 0;
  INT32U SecnHdAddr = 0;
  INT32U no_SecsToEr = 0;                                               /* Ҫ������������Ŀ             */
  INT32U CurSecToEr = 0;                                                /* ��ǰҪ������������           */

  /*
   *  �����ڲ���
   */
  if ((sec1 > SEC_MAX)||(sec2 > SEC_MAX)) {
    return (ERROR);
  }

  CE_Low();
  Send_Byte(0x05);                                                     /* ���Ͷ�״̬�Ĵ�������          */
  temp1 = Get_Byte();                                                  /* ������õ�״̬�Ĵ���ֵ        */
  CE_High();

  CE_Low();
  Send_Byte(0x50);                                                     /* ʹ״̬�Ĵ�����д              */
  CE_High();

  CE_Low();
  Send_Byte(0x01);                                                     /* ����д״̬�Ĵ���ָ��          */
  Send_Byte(0);                                                        /* ��0BPxλ��ʹFlashоƬȫ����д */
  CE_High();

  CE_Low();
  Send_Byte(0x06);                                                      /* ����дʹ������               */
  CE_High();

  /*
   * ����û��������ʼ�����Ŵ�����ֹ�����ţ������ڲ���������
   */
  if (sec1 > sec2)
  {
    temp2 = sec1;
    sec1  = sec2;
    sec2  = temp2;
  }
  /*
   * ����ֹ����������������������
   */
  if (sec1 == sec2)
  {
    SecnHdAddr = SEC_SIZE * sec1;                                       /* ������������ʼ��ַ           */
    CE_Low();
    Send_Byte(0x20);                                                    /* ������������ָ��             */
    Send_Byte(((SecnHdAddr & 0xFFFFFF) >> 16));                         /* ����3���ֽڵĵ�ַ��Ϣ        */
    Send_Byte(((SecnHdAddr & 0xFFFF) >> 8));
    Send_Byte(SecnHdAddr & 0xFF);
    CE_High();
    do {
      CE_Low();
      Send_Byte(0x05);                                                  /* ���Ͷ�״̬�Ĵ�������        */
      StatRgVal = Get_Byte();                                           /* ������õ�״̬�Ĵ���ֵ      */
      CE_High();
    } while (StatRgVal & 0x01);                                         /* һֱ�ȴ���ֱ��оƬ����      */
    return (OK);
  }

  /*
   * ������ʼ��������ֹ��������������ٵĲ�������
   */

  if (sec2 - sec1 == SEC_MAX) {
    CE_Low();
    Send_Byte(0x60);                                                    /* ����оƬ����ָ��(60h or C7h) */
    CE_High();
    do {
      CE_Low();
      Send_Byte(0x05);                                                  /* ���Ͷ�״̬�Ĵ�������         */
      StatRgVal = Get_Byte();                                           /* ������õ�״̬�Ĵ���ֵ       */
      CE_High();
    } while (StatRgVal & 0x01);                                         /* һֱ�ȴ���ֱ��оƬ����       */
    return (OK);
  }

  no_SecsToEr = sec2 - sec1 +1;                                         /* ��ȡҪ������������Ŀ         */
  CurSecToEr  = sec1;                                                   /* ����ʼ������ʼ����           */

  /*
   * ����������֮��ļ���������ȡ16���������㷨
   */
  while (no_SecsToEr >= 16)
  {
    CE_Low();
    Send_Byte(0x06);                                                     /* ��������д����              */
    CE_High();

    SecnHdAddr = SEC_SIZE * CurSecToEr;                                  /* ������������ʼ��ַ          */
    CE_Low();
    Send_Byte(0xD8);                                                     /* ����64KB�����ָ��          */
    Send_Byte(((SecnHdAddr & 0xFFFFFF) >> 16));                          /* ����3���ֽڵĵ�ַ��Ϣ       */
    Send_Byte(((SecnHdAddr & 0xFFFF) >> 8));
    Send_Byte(SecnHdAddr & 0xFF);
    CE_High();
    do {
      CE_Low();
      Send_Byte(0x05);                                                  /* ���Ͷ�״̬�Ĵ�������        */
      StatRgVal = Get_Byte();                                           /* ������õ�״̬�Ĵ���ֵ      */
      CE_High();
    } while (StatRgVal & 0x01);                                         /* һֱ�ȴ���ֱ��оƬ����      */
    CurSecToEr  += 16;                                                  /* ���������16��������Ͳ�����*/
                                                                        /* �����ڵĴ�����������        */
    no_SecsToEr -=  16;                                                 /* �������������������������  */
  }

  /*
   * �������������㷨����ʣ�������
   */
  while (no_SecsToEr >= 1) {
    CE_Low();
    Send_Byte(0x06);                                                   /* ��������д����              */
    CE_High();

    SecnHdAddr = SEC_SIZE * CurSecToEr;                                /* ������������ʼ��ַ          */
    CE_Low();
    Send_Byte(0x20);                                                   /* ������������ָ��            */
    Send_Byte(((SecnHdAddr & 0xFFFFFF) >> 16));                        /* ����3���ֽڵĵ�ַ��Ϣ       */
    Send_Byte(((SecnHdAddr & 0xFFFF) >> 8));
    Send_Byte(SecnHdAddr & 0xFF);
    CE_High();
    do {
      CE_Low();
      Send_Byte(0x05);                                                 /* ���Ͷ�״̬�Ĵ�������        */
      StatRgVal = Get_Byte();                                          /* ������õ�״̬�Ĵ���ֵ      */
      CE_High();
    } while (StatRgVal & 0x01 );                                       /* һֱ�ȴ���ֱ��оƬ����      */
    CurSecToEr  += 1;
    no_SecsToEr -=  1;
  }
  /*
   * ��������,�ָ�״̬�Ĵ�����Ϣ
   */
  CE_Low();
  Send_Byte(0x06);                                                    /* ����дʹ������               */
  CE_High();

  CE_Low();
  Send_Byte(0x50);                                                    /* ʹ״̬�Ĵ�����д             */
  CE_High();
  CE_Low();
  Send_Byte(0x01);                                                    /* ����д״̬�Ĵ���ָ��         */
  Send_Byte(temp1);                                                   /* �ָ�״̬�Ĵ���������Ϣ       */
  CE_High();
  return (OK);
}

/*********************************************************************************************************
** End Of File
*********************************************************************************************************/

