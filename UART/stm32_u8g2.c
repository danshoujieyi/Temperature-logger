#include "stm32_u8g2.h"
 #include "lpc11xx.h"
 #include "Music.h"
 
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
	 LPC_IOCON->PIO0_4 |= (0x1<<9);
	 LPC_IOCON->PIO0_5 |= (0x1<<9);
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
   uint16_t TimeOut;
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

void I2C_Send_NByte(uint8_t *data ,uint8_t lenth)
{
	    uint8_t i;
       for(i=0;i < lenth;i++)	
	    {
           I2C_Send_Byte(data[i]);
      }
}


uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    /* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
    static uint8_t buffer[128];
    static uint8_t buf_idx;
    uint8_t *data;
 
    switch (msg)
    {
    case U8X8_MSG_BYTE_INIT:
    {
        /* add your custom code to init i2c subsystem */
        I2C_Init(1); //I2C��ʼ��
    }
    break;
 
    case U8X8_MSG_BYTE_START_TRANSFER:
    {
        buf_idx = 0;
    }
    break;
 
    case U8X8_MSG_BYTE_SEND:
    {
        data = (uint8_t *)arg_ptr;
 
        while (arg_int > 0)
        {
            buffer[buf_idx++] = *data;
            data++;
            arg_int--;
        }
    }
    break;
 
    case U8X8_MSG_BYTE_END_TRANSFER:
    {
//        if (HAL_I2C_Master_Transmit(&hi2c2, OLED_ADDRESS, buffer, buf_idx, 1000) != HAL_OK)
//            return 0;
		I2C_Send_NByte(buffer,buf_idx);
		return 0;
    }
    break;
 
    case U8X8_MSG_BYTE_SET_DC:
        break;
 
    default:
        return 0;
    }
 
    return 1;
}



uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
    case U8X8_MSG_DELAY_100NANO: // delay arg_int * 100 nano seconds
        __NOP();
        break;
    case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
        for (uint16_t n = 0; n < 320; n++)
        {
            __NOP();
        }
        break;
    case U8X8_MSG_DELAY_MILLI: // delay arg_int * 1 milli second
        T16B0_delay_ms(1);
        break;
    case U8X8_MSG_DELAY_I2C: // arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
        T16B0_delay_us(5);
        break;                    // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
    case U8X8_MSG_GPIO_I2C_CLOCK: // arg_int=0: Output low at I2C clock pin
        break;                    // arg_int=1: Input dir with pullup high for I2C clock pin
    case U8X8_MSG_GPIO_I2C_DATA:  // arg_int=0: Output low at I2C data pin
        break;                    // arg_int=1: Input dir with pullup high for I2C data pin
    case U8X8_MSG_GPIO_MENU_SELECT:
        u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
        break;
    case U8X8_MSG_GPIO_MENU_NEXT:
        u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
        break;
    case U8X8_MSG_GPIO_MENU_PREV:
        u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
        break;
    case U8X8_MSG_GPIO_MENU_HOME:
        u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
        break;
    default:
        u8x8_SetGPIOResult(u8x8, 1); // default return value
        break;
    }
    return 1;
}
void u8g2Init(u8g2_t *u8g2)
{
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay); // ��ʼ��u8g2 �ṹ��
	u8g2_InitDisplay(u8g2);                                                                       // 
	u8g2_SetPowerSave(u8g2, 0);                                                                   // 
	u8g2_ClearBuffer(u8g2);
}


void draw(u8g2_t *u8g2)
{
	u8g2_ClearBuffer(u8g2); 
	
    u8g2_SetFontMode(u8g2, 1); /*����ģʽѡ��*/
    u8g2_SetFontDirection(u8g2, 0); /*���巽��ѡ��*/
    u8g2_SetFont(u8g2, u8g2_font_inb24_mf); /*�ֿ�ѡ��*/
    u8g2_DrawStr(u8g2, 0, 20, "U");
    
    u8g2_SetFontDirection(u8g2, 1);
    u8g2_SetFont(u8g2, u8g2_font_inb30_mn);
    u8g2_DrawStr(u8g2, 21,8,"8");
        
    u8g2_SetFontDirection(u8g2, 0);
    u8g2_SetFont(u8g2, u8g2_font_inb24_mf);
    u8g2_DrawStr(u8g2, 51,30,"g");
    u8g2_DrawStr(u8g2, 67,30,"\xb2");
    
    u8g2_DrawHLine(u8g2, 2, 35, 47);
    u8g2_DrawHLine(u8g2, 3, 36, 47);
    u8g2_DrawVLine(u8g2, 45, 32, 12);
    u8g2_DrawVLine(u8g2, 46, 33, 12);
  
    u8g2_SetFont(u8g2, u8g2_font_4x6_tr);
    u8g2_DrawStr(u8g2, 1,54,"github.com/olikraus/u8g2");
		
	u8g2_SendBuffer(u8g2);
	T16B0_delay_ms(1000);
}

//�������
void testDrawPixelToFillScreen(u8g2_t *u8g2)
{
  int t = 1000;
	u8g2_ClearBuffer(u8g2);

  for (int j = 0; j < 64; j++)
  {
    for (int i = 0; i < 128; i++)
    {
      u8g2_DrawPixel(u8g2,i, j);
    }
  }
  T16B0_delay_ms(1000);
}