#define csx      0 
#define sclk     3 
#define sdata    6 
#define dc       2
#define res      7 
#define Reset1()	(LPC_GPIO2->DATA|=(1<<res))
#define CSX1()		(LPC_GPIO2->DATA|=(1<<csx))
#define SData1()	(LPC_GPIO2->DATA|=(1<<sdata))
#define DC1()		(LPC_GPIO2->DATA|=(1<<dc))
#define SClk1()		(LPC_GPIO2->DATA|=(1<<sclk))

#define Reset0()	(LPC_GPIO2->DATA&=~(1<<res))
#define CSX0()		(LPC_GPIO2->DATA&=~(1<<csx))
#define SData0()	(LPC_GPIO2->DATA&=~(1<<sdata))
#define DC0()		(LPC_GPIO2->DATA&=~(1<<dc))
#define SClk0()		(LPC_GPIO2->DATA&=~(1<<sclk))



void LDS183DisplayOn(void);

//******************************************************************
//  		COMMANDS SET  		 
//******************************************************************
#define NOP								0x00
#define SW_RESET						0x01	//SWRESET	software Reset
#define BOOSTER_OFF						0x02    //BSTROFF	booster Off
#define BOOSTER_ON						0x03	//BSTRON	booster On
#define READ_DISPLAY_ID					0x04	//RDDID		return ID1,ID2,ID3
#define READ_DISPLAY_STATUS				0x09	//RDDST		return 4bytes

#define SLEEP_IN				        0x10	//SLPIN		Sleep in & booster off
#define SLEEP_OUT				        0x11	//SLPOUT	Sleep out & booster on
#define PARTIAL_DISPLAY_MODE_ON         0x12	//PTLON
#define NORMAL_DISPLAY_MODE_ON          0x13	//NORON		partial mode off
#define DISPLAY_INVERSION_OFF           0x20	//INVOFF
#define DISPLAY_INVERSION_ON            0x21	//INVON
#define ALL_PIXELS_OFF				    0x22	//APOFF
#define ALL_PIXELS_ON				    0x23	//APON
#define WRITE_CONTRAST				    0x25	//WRCNTR	EV[6:0]
#define DISPLAY_OFF				        0x28	//DISPOFF
#define DISPLAY_ON					    0x29	//DISPON
#define COLUMN_ADDRESS_SET			    0x2A	//CASET		XS[6:0],XE[6:0]
#define ROW_ADDRESS_SET				    0x2B	//RASET		YS[6:0],YE[6:0]
#define MEMORY_WRITE			        0x2C	//RAMWR		Display RAM Data Writing
#define COLOUR_SET_LUT				    0x2D	//RGBSET	LUT for 8bit/12bit conversation
#define	MEMORY_READ						0x2E	//RAMRD		Display RAM Data Reading
#define PARTIAL_AREA				    0x30	//PTLAR		PSL[6:0],PEL[6:0]
#define SCROLL_AREA					    0x33	//SCRLAR	TFA[6:0],VSA[6:0],BFA[6:0]
#define TEARING_EFFECT_LINE_OFF		    0x34	//TEOFF
#define TEARING_EFFECT_LINE_ON		    0x35	//TEON
#define MEMORY_DATA_ACCESS_CONTROL	    0x36	//MADCTR	MY,MX,MV,ML,RGB
#define VERTICAL_SCROLL_START_ADDRESS   0x37	//VSCSAD	SSA[6:0]
#define IDLE_MODE_OFF				    0x38	//IDMOFF
#define IDLE_MODE_ON				    0x39	//IDMON
#define INTERFACE_PIXEL_FORMAT          0x3A	//COLMOD	P[2:0]:256/4K/64K
#define READ_ID1_VALUE	                0xDA	//RDID1
#define READ_ID2_VALUE				    0xDB	//RDID2
#define READ_ID3_VALUE				    0xDC	//RDID3
#define INTERNAL_OSCILLATOR			    0xB0	//CLKINT
#define EXTERNAL_OSCILLATOR		        0xB1	//CLKEXT
#define FRAME_FREQ_NORMAL_MODE		    0xB4	//FRMSEL	FA,FB,FC,FD
#define FRAME_FREQ_IDLE_MODE		    0xB5	//FRM8SEL	Frame freq at 8color mode
#define TEMP_RANGE_FOR_FFREQ_ADJ	    0xB6	//TMPRNG	TA,TB,TC;temperature range set for frame frequency adjustment
#define TEMP_HYSTERESIS_FOR_FFREQ_ADJ   0xB7	//TMPHYS	TH[3:0]
#define TEMP_READ_BACK				    0xB8	//TMPREAD
#define DISPLAY_CONTROL				    0xBA	//DISCTR	FS[2:0],FINV[1:0],NL[3:0]
#define EV_SET_EEPROM				    0xBB	//EPVOL		offset of EV and RR
#define EEPROM_WRITE_END			    0xD0	//EPWROUT
#define EEPROM_WRITE_START			    0xD1	//EPWRIN
#define READ_EV_VALUE				    0xD4	//RDEV		EV_IN[6:0]
#define READ_RR_VALUE					0xD5	//RDRR		RR_IN[2:0]
//#define delay_1us()			 (_nop_())
/*********************************************************************************************************
����LCM����С��Χ
*********************************************************************************************************/
#define  Gus_LCM_XMAX        128                                        /* ����Һ��x��ĵ���            */
#define  Gus_LCM_YMAX        128   
//��ɫ�궨��
#define   BLACK        0x0000                                           /* ��ɫ�� 0, 0, 0               */
#define   NAVY         0x000F                                           /* ����ɫ�� 0, 0, 128           */
#define   DGREEN       0x03E0                                           /* ����ɫ�� 0, 128, 0           */
#define   DCYAN        0x03EF                                           /* ����ɫ�� 0, 128, 128         */
#define   MAROON       0x7800                                           /* ���ɫ��128, 0, 0            */
#define   PURPLE       0x780F                                           /* ��ɫ�� 128, 0, 128           */
#define   OLIVE        0x7BE0                                           /* ����̣�128, 128, 0          */
#define   LGRAY        0xC618                                           /* �Ұ�ɫ��192, 192, 192        */
#define   DGRAY        0x7BEF                                           /* ���ɫ��128, 128, 128        */
#define   BLUE         0x001F                                           /* ��ɫ�� 0, 0, 255             */
#define   GREEN        0x07E0                                           /* ��ɫ�� 0, 255, 0             */
#define   CYAN         0x07FF                                           /* ��ɫ�� 0, 255, 255           */
#define   RED          0xF800                                           /* ��ɫ�� 255, 0, 0             */
#define   MAGENTA      0xF81F                                           /* Ʒ�죺 255, 0, 255           */
#define   YELLOW       0xFFE0                                           /* ��ɫ�� 255, 255, 0           */
#define   WHITE        0xFFFF                                           /* ��ɫ�� 255, 255, 255         */
#define   IDMCOLOR(color) (((color & 0x001F) << 11) | ((color & 0xF800) >> 11) | (color & 0x07E0))
#define  GusBACKCOLOR  BLACK  


void delay_nms(uint32_t a)	//��ʱ1ms����
{
uint32_t i;
while( --a != 0){
   for(i = 0; i<5500; i++);
}  
}

void delay_1us(uint32_t count)
{
	while(count--);
} 

void CSX_H(void) { 
   CSX1();    // CSX=1 
 //  delay_1us(1);
} 

void CSX_L(void) { 
   CSX0();   // CSX=0 
   delay_1us(1);
} 


void send_data(uint8_t dat) 
{ 			
   unsigned char i=0,j=7;
   
   SClk0();   //  SClk =0
   CSX_L();               //  CSX  =0
  
    for (i=0;i<8;i++)
	{ 
	  SClk0();;   //  SClk =0
	 
	  if (((dat>>j)&0x01))
	    SData1();    // SData=1
	  else
	    SData0();    // SData=0
	  j--;
	  if(i==7)
        DC1();      // DC=1
   	  SClk1();    // SClk =1; 
    
	}
    CSX_H();        //CSX =1;
} 

void send_command(uint8_t dat) 
{ 	
   char i;char j=7;
   
   SClk0();   //  SClk =0
   CSX_L();               //  CSX  =0
  
    for (i=0;i<8;i++)
	{ 
	  SClk0();   //  SClk =0
	 
	  if (((dat>>j)&0x01))
	    SData1();    // SData=1
	  else
	    SData0();    // SData=0
	  j--;
	  if(i==7)
        DC0();     // DC=0
   	  SClk1();    // SClk =1; 
    
	}
    CSX_H();        //CSX =1;
} 


//******************************************************************
// 			 	DRIVER LDS183 DEPENDANT FUNCTIONS
//******************************************************************
uint32_t i,j,k,m,l,n,Ys,Xs,Sc; 

 				 
void LDS183SleepOut(void)
{		   
	send_command(SLEEP_OUT);				// Leave sleepmode
//	Wait(120);								// Wait 10ms
    delay_nms(10);	

	LDS183DisplayOn();						// Set registers in good mode
}

void LDS183SleepIn(void)
{
//	Wait(120);								// Wait 120ms(100ms startup time + buffer) as in demoboard
    delay_nms(10);
    send_command(SLEEP_IN);					// Turn booster & display OFF
//	Wait(10);								// Wait 10ms
    
}

void LDS183IdleOn(void)
{
//	Wait(10);								// Wait 10ms
    delay_nms(10);
	send_command(IDLE_MODE_ON);				// 8 Color Display
}

void LDS183IdleOff(void)
{
//	 Wait(10);								// Wait 10ms
	 delay_nms(10);
	 send_command(IDLE_MODE_OFF);			
}

void LDS183DisplayOn(void)
{
	//Send_Command(SLEEP_OUT);				// Set booster ON
	//Wait(120);								// Wait 10ms
   	send_command(DISPLAY_ON);				// Display ON
            delay_nms(10);
}

void LDS183PowerOff(void)
{
	send_command(DISPLAY_OFF);				// Display OFF
	send_command(SLEEP_IN);					// Turn booster & display OFF
//	Wait(10);								// Wait 10ms
	delay_nms(10);
}

void LDS183NormtoPart(void)
{
	send_command(PARTIAL_AREA);						// PSL,PEL
	send_data(0x18);								// COM 54
	send_data(0x70);								// COM 75

  	send_command(PARTIAL_DISPLAY_MODE_ON);
}

void LDS183ParttoNorm(void)					//return to normal mode
{
	send_command(NORMAL_DISPLAY_MODE_ON);			// Set normal mode: partial mode/scroll mode off
}


void LDS183AdjustEV(uint8_t EV)
{
	send_command(WRITE_CONTRAST);
	send_data(EV);
}	

void LDS183VScrollOn(void)
{		   
 	for (Sc=0;Sc<5;Sc++)
	{
//		char str[7];
		send_command(SCROLL_AREA);
		send_data(0x08);					//TFA
		send_data(0x5F);					//VSA
		send_data(0x18);					//BFA
	   	
	   	send_command(COLUMN_ADDRESS_SET);				//XS,XE
		send_data(0x00);								//0~97
		send_data(0x7F);	 
	   	send_command(ROW_ADDRESS_SET);					//YS,YE
		send_data(0x25);								//0~69
		send_data(0x77);

		send_command(MEMORY_DATA_ACCESS_CONTROL);		// Set write direction col/rows		
		send_data(0x98);			// MY=1,MX=0,MV=0,ML=1,RGB=1--change color
	
		 
		 }
}
//*/


void LDS183VScrollOff(void)
{
		send_command(DISPLAY_OFF);				// Display OFF
		send_command(NORMAL_DISPLAY_MODE_ON);	// Set normal mode: partial mode/scroll mode off
	 	send_command(SCROLL_AREA);			//must recover its setting,otherwise abnormal
		send_data(0x00);					//TFA  recover normal setting
		send_data(0x7F);					//VSA  recover normal setting
		send_data(0x00);					//BFA  recover normal setting
	    LDS183DisplayOn(); //due to above display off acco. exit scrol off procedure
		send_command(MEMORY_DATA_ACCESS_CONTROL);		// Set write direction col/rows		
		send_data(0x10);			// MY=0,MX=0,MV=0,ML=1--change direc,RGB=0

}

void LDS183SetColumnAddress(uint8_t nStart, uint8_t nStop)
{
	send_command(COLUMN_ADDRESS_SET);
	send_data(nStart);
	send_data(nStop);	
}

void LDS183SetRowAddress(uint8_t nStart, uint8_t nStop)
{
	send_command(ROW_ADDRESS_SET);
	send_data(nStart);
	send_data(nStop);	
}

void LDS183WriteToMemory(void)
{
	send_command(MEMORY_WRITE);
}




void Initial(void)
{ send_command(DISPLAY_INVERSION_OFF);			// Set the normal mode, partial and scroll mode are left.
 	send_command(IDLE_MODE_OFF);					// Idle mode OFF, 64K colour mode
	send_command(NORMAL_DISPLAY_MODE_ON);			// Set normal mode: partial mode/scroll mode off
	

    send_command(MEMORY_DATA_ACCESS_CONTROL);		// Set write direction col/rows		
	send_data(0x00);								// MY=0,MX=0,MV=0,ML=0,RGB=0
	
	send_command(INTERFACE_PIXEL_FORMAT);  			// 64k color (16Bit/pixel)
	send_data(0x05);
	send_command(COLUMN_ADDRESS_SET);				//XS,XE
	send_data(0x00);								//0~128
	send_data(0x7F);   
	send_command(ROW_ADDRESS_SET);					//YS,YE
	send_data(0x00);								//0~128
	send_data(0x7F);
}

void White(void)
{   uint8_t Xs=0,Ys=0;
    send_command(COLUMN_ADDRESS_SET);			//XS,XE
	send_data(Xs);								//0~128
	send_data(0x7f);   
	send_command(ROW_ADDRESS_SET);				//YS,YE
	send_data(Ys);								//0~128
	send_data(0x7f);
   send_command(MEMORY_WRITE); 	
   for (i= 0; i<128;i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0xff);
				send_data(0xff);
				}
		}
}

void Black_64line(void)
{   uint8_t Xs=0,Ys=64;
    send_command(COLUMN_ADDRESS_SET);			//XS,XE
	send_data(Xs);								//0~128
	send_data(0x7f);   
	send_command(ROW_ADDRESS_SET);				//YS,YE
	send_data(Ys);								//0~128
	send_data(0x7f);
   send_command(MEMORY_WRITE); 	
   for (i= 0; i<64; i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0x00);
				send_data(0x00);
				}
		}
}

void Blue_nline(uint8_t Ys,int8_t n)
{   uint8_t Xs=20;
    send_command(COLUMN_ADDRESS_SET);			//XS,XE
	send_data(Xs);								//0~128
	send_data(0x7f);   
	send_command(ROW_ADDRESS_SET);				//YS,YE
	send_data(Ys);								//0~128
	send_data(Ys+n-1);
   send_command(MEMORY_WRITE); 	
   for (i= 0; i<n; i++)
		{
			for (j=0;j<80;j++)
				{
		      	send_data(0x00);
				send_data(0x1f);
				}
		}
}


//*******************************************************************		
void Red(void)
 {	
    send_command(MEMORY_WRITE);
	for (i= 0; i<128;i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0xf8);
				send_data(0x00);
				}
		} 
		delay_nms(500);
  }

void Green(void)
 {
    send_command(MEMORY_WRITE);
	for (i= 0; i<128;i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0x07);
				send_data(0xe0);
				}
		} 
		delay_nms(500);
  }

void Blue(void)
 {  uint8_t Xs=0,Ys=0;
    send_command(COLUMN_ADDRESS_SET);			//XS,XE
	send_data(Xs);								//0~128
	send_data(0x7f);   
	send_command(ROW_ADDRESS_SET);				//YS,YE
	send_data(Ys);								//0~128
	send_data(0x7f);
    send_command(MEMORY_WRITE);
	for (i= 0; i<128;i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0x00);
				send_data(0x1f);
				}
		} 
		delay_nms(500);
  }

void BlackBar(void)
 {
    send_command(MEMORY_WRITE);
	for (i= 0; i<16;i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0x00);
				send_data(0x00);
				}
		} 
		delay_nms(500);
  }

void ThreeColourBar(void)
 {
    send_command(MEMORY_WRITE);
	for (i= 0; i<42;i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0xf8);
				send_data(0x00);
				}
		} 
	for (i= 0; i<43;i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0x07);
				send_data(0xe0);
				}
		} 
	for (i= 0; i<43;i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0x00);
				send_data(0x1f);
				}
		} 
		delay_nms(500);
  }

void ThreeColourBar1(void)
 {
    send_command(MEMORY_WRITE);
	for (i= 0; i<128;i++)
		{
			for (j=0;j<42;j++)
				{
		      	send_data(0xf8);
				send_data(0x00);
				}
			for (j=0;j<43;j++)
				{
		      	send_data(0x07);
				send_data(0xe0);
				}
			for (j=0;j<43;j++)
				{
		      	send_data(0x00);
				send_data(0x1f);
				}
		}  
		delay_nms(500);
  }

void B_Grey_W(void)
 {
    send_command(MEMORY_WRITE);
	for (i= 0; i<42;i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0xff);
				send_data(0xff);
				}
		} 
	for (i= 0; i<43;i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0x84);
				send_data(0x10);
				}
		} 
	for (i= 0; i<43;i++)
		{
			for (j=0;j<128;j++)
				{
		      	send_data(0x00);
				send_data(0x00);
				}
		} 
		delay_nms(500);
  }	 

void writeData16(unsigned int usData)                                       /* д16λ���ݺ���               */
{
	send_data((char)((usData>>8)&0xff));
	send_data((char)(usData&0xff));

}
 /*********************************************************************************************************
** ��������: setCoordinate
** ��������: д��ͼ����
** ��  ����: x ��������е�λ��
**           y ��������е�λ��
** �䡡  ��: ��
** ȫ�ֱ���: ��
** ��    �أ���
**------------------------------------------------------------------------------------------------------
** �� �� ��:
** �ա�  ��:
**------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void setCoordinate(unsigned short Xs, unsigned short Ys)
{
    send_command(COLUMN_ADDRESS_SET);			//XS,XE
	send_data(Xs);								//0~128
	send_data(0x7f);   
	send_command(ROW_ADDRESS_SET);				//YS,YE
	send_data(Ys);								//0~128
	send_data(Ys+n-1);
    send_command(MEMORY_WRITE); 
}
/*********************************************************************************************************
** ��������: writeOneHzChar
** ��������: ��ָ������ʼ���괦дһ������
** ��  ����: pucMsk ָ������ģ��ŵ���ʼ��ַ
**           x0 ��ʼ���������е�λ��
**           y0 ��ʼ���������е�λ��
**           color �ַ���ʾ����ɫ
** �䡡  ��: ��
** ȫ�ֱ���: ��
**------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
unsigned long writeOneHzChar(unsigned char  *pucMsk,
                               unsigned short x0,
                               unsigned short y0,
                               unsigned short color)
{
    unsigned long i,j;
    unsigned short mod[16];                                             /* ��ǰ��ģ                     */
    unsigned short *pusMsk;                                             /* ��ǰ�ֿ��ַ                 */
    unsigned short y;   
    pusMsk = (unsigned short *)pucMsk;
    for(i=0; i<16; i++)                                                 /* ���浱ǰ���ֵ���ʽ��ģ       */
    {
        mod[i] = *pusMsk++;                                             /* ȡ�õ�ǰ��ģ�����ֶ������   */
        mod[i] = ((mod[i] & 0xff00) >> 8) | ((mod[i] & 0x00ff) << 8);   /* ��ģ�����ߵ��ֽڣ�Ϊ����ʾ   */
                                                                        /* ��Ҫ��                       */
    }
    y = y0;
    for(i=0; i<16; i++) {                                               /* 16��                         */
        #ifdef __DISPLAY_BUFFER                                         /* ʹ���Դ���ʾ                 */
        for(j=0; j<16; j++) {                                           /* 16��                         */
            if((mod[i] << j)& 0x8000) {                                 /* ��ʾ��ģ                     */
                DispBuf[128*(y0+i) + x0+j] = color;
            }
        }
        #else                                                           /* ֱ����ʾ                     */
        
        setCoordinate(x0, y);                                           /* ����д���ݵ�ַָ��           */
        send_command(MEMORY_WRITE); //data write command
		for(j=0; j<16; j++) {                                           /* 16��                         */
            if((mod[i] << j) & 0x8000) {                                /* ��ʾ��ģ                     */
                writeData16(color);
            } else {
            	writeData16(WHITE);                                       /* �ö���ʽ����д�հ׵������   */
            }
        }
        y++;
        #endif
    }
    return (16);                                                        /* ����16λ�п�                 */
}

/*********************************************************************************************************
** ��������: writeOneASCII
** ��������: ��ָ������ʼ���괦дһ��ASCII���ַ�
** ��  ����: pucMsk ָ��ASCII���ַ���ģ��ŵ���ʼ��ַ
**           x0 ��ʼ���������е�λ��
**           y0 ��ʼ���������е�λ��
**           color �ַ���ʾ����ɫ
** �䡡  ��: ��
** ȫ�ֱ���: ��
** ����ģ��: setCoordinate()��__writeData16()��__readData16()
** ��    �أ���д�ַ����п�8
**------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
unsigned long writeOneASCII(unsigned char *pucMsk,
                              unsigned int x0,
                              unsigned int y0,
                              unsigned int color)
{
    unsigned int i,j;
    unsigned int y;
    unsigned char ucChar; 
    y = y0;
    for(i=0; i<16; i++) {                                               /* 16��                         */
        ucChar = *pucMsk++;
        #ifdef __DISPLAY_BUFFER                                         /* ʹ���Դ���ʾ                 */
        for(j=0; j<8; j++) {                                            /* 8��                          */
            if((ucChar << j)& 0x80) {                                   /* ��ʾ��ģ                     */
                DispBuf[128*(y0+i) + x0+j] = color;
            }
        }
        #else                                                           /* ֱ����ʾ                     */
        
        setCoordinate(x0, y);                                           /* ����д���ݵ�ַָ��           */
        send_command(MEMORY_WRITE); //data write command
		for(j=0; j<8; j++) {                                            /* 8��                          */
            if((ucChar << j) & 0x80) {                                  /* ��ʾ��ģ                     */
               	writeData16(color);
            } else {
				writeData16(WHITE); 
            }
        }
        y++;
        #endif
    }
    return (8);                                                         /* ����16λ�п�                 */
}

/*********************************************************************************************************
** ��������: writeString
** ��������: ��ָ�������괦��ʼ��ʾ�ַ���
** ��  ����: pcStr �ַ�������׵�ַ
**           x0 ��ʼ���������е�λ��
**           y0 ��ʼ���������е�λ��
**           color �ַ�������ʾ��ɫ
** �䡡  ��: ��
** ȫ�ֱ���: GBHZ_16 �Զ��庺�ֿ���ģ����
**           ASCII   �Զ����ASCII���ֿ���ģ����
** ����ģ��: findHzIndex()��__writeOneHzChar()��__writeOneASCII()
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void writeString(uint8_t *pcStr, unsigned short x0, unsigned short y0, unsigned short color)
{
    unsigned short usIndex;
    unsigned short usWidth = 0;
    FNT_GB16 *ptGb16 = 0;
    
    ptGb16 = (FNT_GB16 *)GBHZ_16;                                       /*                              */
    while(1)
    {
        if(*pcStr == 0) {
            break;                                                      /* �ַ�������                   */
        }
        
        x0 = x0 + (usWidth);                                            /* �����ַ�����ʾ�ɽ���         */
        if(*pcStr > 0x80) {                                             /* �ж�Ϊ����                   */
            if((x0 + 16) >= Gus_LCM_XMAX) {                             /* ���ʣ��ռ��Ƿ��㹻         */
                x0 = 0;
                y0 = y0 + 16;                                           /* �ı���ʾ����                 */
                if(y0 >= Gus_LCM_YMAX) {                                /* �����곬��                   */
                    y0 = 0;
                }
            }
            usIndex = findHzIndex(pcStr);
            usWidth = writeOneHzChar((unsigned char *)&(ptGb16[usIndex].Msk[0]), x0, y0, color);
                                                                        /* ��ʾ�ַ�                     */
            pcStr += 2;
        } else {                                                        /* �ж�Ϊ�Ǻ���                 */
            if (*pcStr == '\r') {                                       /* ����                         */
                y0 = y0 + 16;                                           /* �ı���ʾ����                 */
                if(y0 >= Gus_LCM_YMAX) {                                /* �����곬��                   */
                    y0 = 0;
                }
                pcStr++;
                usWidth = 0;
                continue;
            } else if (*pcStr == '\n') {                                /* ���뵽���                   */
                x0 = 0;
                pcStr++;
                usWidth = 0;
                continue;
            } else {
                if((x0 + 8) >= Gus_LCM_XMAX) {                          /* ���ʣ��ռ��Ƿ��㹻         */
                    x0 = 0;
                    y0 = y0 + 16;                                       /* �ı���ʾ����                 */
                    if(y0 >= Gus_LCM_YMAX) {                            /* �����곬��                   */
                        y0 = 0;
                    }
                }
                usWidth = writeOneASCII((unsigned char *)&ASCII[(*pcStr - 0x20)][0], x0, y0, color);                                                              /* ASCII���21H��ֵ��Ӧ��λ��3��*/
                pcStr += 1;
            }
        }
    }
}

//�����ߣ�������ʼX���꣬���ȣ��߶�,��ɫ�Ϳ����ǰ����
void Xline(unsigned char Xs,unsigned char Ys,unsigned char len,unsigned int color)
{   
/*   send_command(COLUMN_ADDRESS_SET);			//XS,XE
	send_data(Xs);								//0~128
	send_data(0x7f);   
	send_command(ROW_ADDRESS_SET);				//YS,YE
	send_data(Ys);								//0~128
	send_data(Ys+n-1);
    send_command(MEMORY_WRITE); 		  */
	setCoordinate(Xs,Ys);
	for (j=0;j<len;j++)
	{
	//	send_data(0x00);
	//	send_data(0x00);
		writeData16(color);
	}
}

//�����ߣ�������ʼY���꣬���ȣ��߶�,��ɫ�Ϳ����ǰ����
void Yline(unsigned char Xs,unsigned char Ys,unsigned char len,unsigned int color)
{   
//	setCoordinate(Xs,Ys);
	for (j=0;j<len;j++)
	{
	//	send_data(0x00);
	//	send_data(0x00);
		setCoordinate(Xs,Ys+j);
		writeData16(color);
	}
}

