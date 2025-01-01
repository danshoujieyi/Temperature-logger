/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:       MX25L1602.c
** Descriptions:    SST25VF016B驱动
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
 * 移植本软件包时需要修改以下的函数或宏 
 */
#define     CE_Low()    LPC_GPIO0->DATA &= ~SPI_CS;   
#define     CE_High()   LPC_GPIO0->DATA |=  SPI_CS;

/*********************************************************************************************************
** 函数名称：SPIInit
** 功能说明：初始化SPI
** 输入参数：无
** 输出参数：无
*********************************************************************************************************/
void  SSP_Init (void)
{  
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);                             /* 配置IOCON模块时钟            */
    LPC_IOCON->PIO0_2 &= ~0x07;                                         /* 初始化SPI0引脚               */
    LPC_GPIO0->DIR    |= SPI_CS;

    LPC_IOCON->PIO0_6 |= 0x02;
    LPC_IOCON->PIO0_8 |= 0x01;
    LPC_IOCON->PIO0_9 |= 0x01;

    LPC_SYSCON->PRESETCTRL    |= 0x01;                                  /* 禁止SPI0复位                 */

    LPC_IOCON->SCK_LOC         = 0x02;                                  /* P0.6配置为SCK                */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 11);                             /* 打开SPI0外设                 */
    LPC_SYSCON->SSP0CLKDIV     = 0x01;                                  /* SSP时钟分频                  */
   
    LPC_SSP0->CR0 = (0x01 << 8) |                                       /* SCR  设置SPI时钟分频         */
                    (0x00 << 7) |                                       /* CPHA 时钟输出相位,           */
                                                                        /* 仅SPI模式有效                */
                    (0x00 << 6) |                                       /* CPOL 时钟输出极性,           */
                                                                        /* 仅SPI模式有效                */
                    (0x00 << 4) |                                       /* FRF  帧格式 00=SPI,01=SSI,   */
                                                                        /* 10=Microwire,11=保留         */
                    (0x07 << 0);                                        /* DSS  数据长度,0000-0010=保留,*/
                                                                        /* 0011=4位,0111=8位,1111=16位  */

    LPC_SSP0->CR1 = (0x00 << 3) |                                       /* SOD  从机输出禁能,1=禁止     */
                    (0x00 << 2) |                                       /* MS   主从选择,0=主机,1=从机  */
                    (0x01 << 1) |                                       /* SSE  SSP使能                 */
                    (0x00 << 0);                                        /* LBM  回写模式                */
             
    LPC_SSP0->CPSR = 2;                                                 /* PCLK分频值                   */
    LPC_SSP0->ICR  = 0x03;                                              /* 中断清除寄存器               */
}

/*********************************************************************************************************
** 函数名称: Send_Byte
** 函数功能：通过硬件SPI发送一个字节到MX25L1602
** 输入参数: data
** 输出参数: 无
** 返 回 值：无
*********************************************************************************************************/
void Send_Byte (INT8U data)
{
    LPC_SSP0->DR = data;
    while( (LPC_SSP0->SR & 0x10) == 0x10);                              /* 等待TFE置位，即发送FIFO空    */
    data = LPC_SSP0->DR;   
}

/*********************************************************************************************************
** 函数名称:Get_Byte
** 函数功能:通过硬件SPI接口接收一个字节到处理器
** 输入参数:无
** 输出参数:无
*********************************************************************************************************/
INT8U Get_Byte (void)
{
    LPC_SSP0->DR = 0xFF;                                                /* 发送该数据用以产生时钟       */
    while ( 0 == (LPC_SSP0->SR & 0x01));                                /* 等待数据发送完毕             */
   /*
    * 判断当前是否空闲（是否处于TX Or RX）
    */
    while( LPC_SSP0->SR & (1 << 4));
   /*
    * 判断是否已接收到数据，必须判断是否接收完成,否则
    * 新的TX发送再次写入LPC_SSP0->DR寄存器
    */
   while( LPC_SSP0->SR & (1 << 2) == 0x00); 
   return (INT8U)(LPC_SSP0->DR);                                        /* 返回接收到的数据             */
}
 
/*********************************************************************************************************
** 用户接口层
** 以下函数在移植时无需修改
*********************************************************************************************************/
/********************************************************************************************************
** 函数名称:MX25L1602_RD
** 函数功能:MX25L1602的读函数,可选择读ID和读数据操作
** 输入参数:
**          INT32U Dst：目标地址,范围 0x0 - MAX_ADDR（MAX_ADDR = 0x1FFFFF）
**          INT32U NByte:  要读取的数据字节数
**          INT8U* RcvBufPt:接收缓存的指针
** 输出参数:操作成功则返回OK,失败则返回ERROR
** 特殊说明:若某功能下,某一入口参数无效,可在该入口参数处填Invalid，该参数将被忽略
**********************************************************************************************************/
INT8U MX25L1602_RD(INT32U Dst, INT32U NByte,INT8U* RcvBufPt)
{
  INT32U i = 0;
  if ((Dst+NByte > MAX_ADDR)||(NByte == 0))  return (ERROR);            /*  检查入口参数                */
  
  CE_Low();
  Send_Byte(0x0B);                                                      /* 发送读命令                   */
  Send_Byte(((Dst & 0xFFFFFF) >> 16));                                  /* 发送地址信息:该地址为3个字节 */
  Send_Byte(((Dst & 0xFFFF) >> 8));
  Send_Byte(Dst & 0xFF);
  Send_Byte(0xFF);                                                      /* 发送一个哑字节以读取数据     */
  for (i = 0; i < NByte; i++) {
    RcvBufPt[i] = Get_Byte();
  }
  CE_High();
  return (OK);
}

/*********************************************************************************************************
** 函数名称:MX25L1602_RdID
** 函数功能:MX25L1602的读ID函数,可选择读ID和读数据操作
** 输入参数:
**          idtype IDType:ID类型。用户可在Jedec_ID,Dev_ID,Manu_ID三者里选择
**          INT32U* RcvbufPt:存储ID变量的指针
** 输出参数:操作成功则返回OK,失败则返回ERROR
** 特殊说明:若填入的参数不符合要求，则返回ERROR
*********************************************************************************************************/
INT8U MX25L1602_RdID(idtype IDType, INT32U* RcvbufPt)
{
  INT32U temp = 0;
  if (IDType == Jedec_ID) {
    CE_Low();
    Send_Byte(0x9F);                                                    /* 发送读JEDEC ID命令(9Fh)      */
    temp = (temp | Get_Byte()) << 8;                                    /* 接收数据                     */
    temp = (temp | Get_Byte()) << 8;
    temp = (temp | Get_Byte());                                         /* 在本例中,temp的值应为0xBF2541*/
    CE_High();
    *RcvbufPt = temp;
    return (OK);
  }

  if ((IDType == Manu_ID) || (IDType == Dev_ID) ) {
    CE_Low();
    Send_Byte(0x90);                                                    /* 发送读ID命令 (90h or ABh)    */
    Send_Byte(0x00);                                                    /* 发送地址                     */
    Send_Byte(0x00);                                                    /* 发送地址                     */
    Send_Byte(IDType);                                                  /* 发送地址 - 不是00H就是01H    */
    temp = Get_Byte();                                                  /* 接收获取的数据字节           */
    CE_High();
    *RcvbufPt = temp;
    return (OK);
  } else {
    return (ERROR);
  }
}

/*********************************************************************************************************
** 函数名称:MX25L1602_WR
** 函数功能:MX25L1602的写函数，可写1个和多个数据到指定地址
** 输入参数:
**          INT32U Dst：目标地址,范围 0x0 - MAX_ADDR（MAX_ADDR = 0x1FFFFF）
**          INT8U* SndbufPt:发送缓存区指针
**          INT32U NByte:要写的数据字节数
** 输出参数:操作成功则返回OK,失败则返回ERROR
** 特殊说明:若某功能下,某一入口参数无效,可在该入口参数处填Invalid，该参数将被忽略
*********************************************************************************************************/
INT8U MX25L1602_WR(INT32U Dst, INT8U* SndbufPt, INT32U NByte)
{
  INT32U temp = 0,i = 0,StatRgVal = 0;
  if (( (Dst+NByte-1 > MAX_ADDR)||(NByte == 0) )) {
    return (ERROR);                                                     /*  检查入口参数                */
  }
  CE_Low();
  Send_Byte(0x05);                                                      /* 发送读状态寄存器命令         */
  temp = Get_Byte();                                                    /* 保存读得的状态寄存器值       */
  CE_High();

  CE_Low();
  Send_Byte(0x50);                                                      /* 使状态寄存器可写             */
  CE_High();
  CE_Low();
  Send_Byte(0x01);                                                      /* 发送写状态寄存器指令         */
  Send_Byte(0);                                                         /* 清0BPx位，使Flash芯片全区可写*/
  CE_High();

  for(i = 0; i < NByte; i++) {
    CE_Low();
    Send_Byte(0x06);                                                    /* 发送写使能命令               */
    CE_High();

    CE_Low();
    Send_Byte(0x02);                                                    /* 发送字节数据烧写命令         */
    Send_Byte((((Dst+i) & 0xFFFFFF) >> 16));                            /* 发送3个字节的地址信息        */
    Send_Byte((((Dst+i) & 0xFFFF) >> 8));
    Send_Byte((Dst+i) & 0xFF);
    Send_Byte(SndbufPt[i]);                                             /* 发送被烧写的数据             */
    CE_High();

    do {
      CE_Low();
      Send_Byte(0x05);                                                  /* 发送读状态寄存器命令         */
      StatRgVal = Get_Byte();                                           /* 保存读得的状态寄存器值       */
      CE_High();
    } while (StatRgVal == 0x03);                                        /* 一直等待，直到芯片空闲       */
  }

  CE_Low();
  Send_Byte(0x06);                                                      /* 发送写使能命令               */
  CE_High();

  CE_Low();
  Send_Byte(0x50);                                                      /* 使状态寄存器可写             */
  CE_High();
  CE_Low();
  Send_Byte(0x01);                                                      /* 发送写状态寄存器指令         */
  Send_Byte(temp);                                                      /* 恢复状态寄存器设置信息       */
  CE_High();

  return (OK);
}

/*********************************************************************************************************
** 函数名称:MX25L1602_Erase
** 函数功能:根据指定的扇区号选取最高效的算法擦除
** 输入参数:
**          INT32U sec1：起始扇区号,范围(0~499)
**          INT32U sec2：终止扇区号,范围(0~499)
** 输出参数:操作成功则返回OK,失败则返回ERROR
*********************************************************************************************************/
INT8U MX25L1602_Erase(INT32U sec1, INT32U sec2)
{
  INT8U  temp1 = 0,temp2 = 0,StatRgVal = 0;
  INT32U SecnHdAddr = 0;
  INT32U no_SecsToEr = 0;                                               /* 要擦除的扇区数目             */
  INT32U CurSecToEr = 0;                                                /* 当前要擦除的扇区号           */

  /*
   *  检查入口参数
   */
  if ((sec1 > SEC_MAX)||(sec2 > SEC_MAX)) {
    return (ERROR);
  }

  CE_Low();
  Send_Byte(0x05);                                                     /* 发送读状态寄存器命令          */
  temp1 = Get_Byte();                                                  /* 保存读得的状态寄存器值        */
  CE_High();

  CE_Low();
  Send_Byte(0x50);                                                     /* 使状态寄存器可写              */
  CE_High();

  CE_Low();
  Send_Byte(0x01);                                                     /* 发送写状态寄存器指令          */
  Send_Byte(0);                                                        /* 清0BPx位，使Flash芯片全区可写 */
  CE_High();

  CE_Low();
  Send_Byte(0x06);                                                      /* 发送写使能命令               */
  CE_High();

  /*
   * 如果用户输入的起始扇区号大于终止扇区号，则在内部作出调整
   */
  if (sec1 > sec2)
  {
    temp2 = sec1;
    sec1  = sec2;
    sec2  = temp2;
  }
  /*
   * 若起止扇区号相等则擦除单个扇区
   */
  if (sec1 == sec2)
  {
    SecnHdAddr = SEC_SIZE * sec1;                                       /* 计算扇区的起始地址           */
    CE_Low();
    Send_Byte(0x20);                                                    /* 发送扇区擦除指令             */
    Send_Byte(((SecnHdAddr & 0xFFFFFF) >> 16));                         /* 发送3个字节的地址信息        */
    Send_Byte(((SecnHdAddr & 0xFFFF) >> 8));
    Send_Byte(SecnHdAddr & 0xFF);
    CE_High();
    do {
      CE_Low();
      Send_Byte(0x05);                                                  /* 发送读状态寄存器命令        */
      StatRgVal = Get_Byte();                                           /* 保存读得的状态寄存器值      */
      CE_High();
    } while (StatRgVal & 0x01);                                         /* 一直等待，直到芯片空闲      */
    return (OK);
  }

  /*
   * 根据起始扇区和终止扇区间距调用最快速的擦除功能
   */

  if (sec2 - sec1 == SEC_MAX) {
    CE_Low();
    Send_Byte(0x60);                                                    /* 发送芯片擦除指令(60h or C7h) */
    CE_High();
    do {
      CE_Low();
      Send_Byte(0x05);                                                  /* 发送读状态寄存器命令         */
      StatRgVal = Get_Byte();                                           /* 保存读得的状态寄存器值       */
      CE_High();
    } while (StatRgVal & 0x01);                                         /* 一直等待，直到芯片空闲       */
    return (OK);
  }

  no_SecsToEr = sec2 - sec1 +1;                                         /* 获取要擦除的扇区数目         */
  CurSecToEr  = sec1;                                                   /* 从起始扇区开始擦除           */

  /*
   * 若两个扇区之间的间隔够大，则采取16扇区擦除算法
   */
  while (no_SecsToEr >= 16)
  {
    CE_Low();
    Send_Byte(0x06);                                                     /* 发送允许写命令              */
    CE_High();

    SecnHdAddr = SEC_SIZE * CurSecToEr;                                  /* 计算扇区的起始地址          */
    CE_Low();
    Send_Byte(0xD8);                                                     /* 发送64KB块擦除指令          */
    Send_Byte(((SecnHdAddr & 0xFFFFFF) >> 16));                          /* 发送3个字节的地址信息       */
    Send_Byte(((SecnHdAddr & 0xFFFF) >> 8));
    Send_Byte(SecnHdAddr & 0xFF);
    CE_High();
    do {
      CE_Low();
      Send_Byte(0x05);                                                  /* 发送读状态寄存器命令        */
      StatRgVal = Get_Byte();                                           /* 保存读得的状态寄存器值      */
      CE_High();
    } while (StatRgVal & 0x01);                                         /* 一直等待，直到芯片空闲      */
    CurSecToEr  += 16;                                                  /* 计算擦除了16个扇区后和擦除区*/
                                                                        /* 域相邻的待擦除扇区号        */
    no_SecsToEr -=  16;                                                 /* 对需擦除的扇区总数作出调整  */
  }

  /*
   * 采用扇区擦除算法擦除剩余的扇区
   */
  while (no_SecsToEr >= 1) {
    CE_Low();
    Send_Byte(0x06);                                                   /* 发送允许写命令              */
    CE_High();

    SecnHdAddr = SEC_SIZE * CurSecToEr;                                /* 计算扇区的起始地址          */
    CE_Low();
    Send_Byte(0x20);                                                   /* 发送扇区擦除指令            */
    Send_Byte(((SecnHdAddr & 0xFFFFFF) >> 16));                        /* 发送3个字节的地址信息       */
    Send_Byte(((SecnHdAddr & 0xFFFF) >> 8));
    Send_Byte(SecnHdAddr & 0xFF);
    CE_High();
    do {
      CE_Low();
      Send_Byte(0x05);                                                 /* 发送读状态寄存器命令        */
      StatRgVal = Get_Byte();                                          /* 保存读得的状态寄存器值      */
      CE_High();
    } while (StatRgVal & 0x01 );                                       /* 一直等待，直到芯片空闲      */
    CurSecToEr  += 1;
    no_SecsToEr -=  1;
  }
  /*
   * 擦除结束,恢复状态寄存器信息
   */
  CE_Low();
  Send_Byte(0x06);                                                    /* 发送写使能命令               */
  CE_High();

  CE_Low();
  Send_Byte(0x50);                                                    /* 使状态寄存器可写             */
  CE_High();
  CE_Low();
  Send_Byte(0x01);                                                    /* 发送写状态寄存器指令         */
  Send_Byte(temp1);                                                   /* 恢复状态寄存器设置信息       */
  CE_High();
  return (OK);
}

/*********************************************************************************************************
** End Of File
*********************************************************************************************************/

