#include "DS18B20.h"
#include "Delay.h"
/******************************************************************
 * 函 数 名 称：bsp_ds18b20_GPIO_Init
 * 函 数 说 明：MLX90614的引脚初始化
 * 函 数 形 参：无
 * 函 数 返 回：1未检测到器件   0检测到器件
 * 作       者：LC
 * 备       注：无
******************************************************************/
char DS18B20_Init(void)
{
    unsigned char ret = 255;

    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // 使能 GPIO 时钟
    LPC_GPIO0->DIR |= (1UL << 6); // 设置 PIO1_10 为输出

	
    ret = DS18B20_Check();//检测器件是否存在
    return ret;
}

void DQ_OUT(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // 使能 GPIO 时钟
	LPC_GPIO0->DIR |= (1UL << 6); // 设置 PIO1_10 为输出
}

void DQ_IN(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // 使能 GPIO 时钟
	LPC_GPIO0->DIR &= ~(1UL << 6); // 将 P3.5 设置为输入（按键）
}

uint8_t DQ_GET(void)
{
	uint8_t bitVal = 0;			
	bitVal= (LPC_GPIO0->DATA>>6)&0x01;
	return	bitVal;
} 
/**
  * @函数名：GPIOSetValue
  * @描述：设置/清除一个在GPIO端口X（X是端口号）上的一些特定管脚上的位值。 
  * @参数：端口号，位地址，位值
  * @返回值：无
  */
void DQ( uint8_t bitVal )
{
   /* 如果值是，但是 GPIOx_DAT 没有设置，设置 DATA
  为 1； 如果值是 0，但是 GPIOx_DAT 已经设置了， 清除
  DATA 为 0。其他条件都忽略。在端口3上（只有0至3位），如果位值超出了范围，没有错误保护	。 */

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
 * 函 数 名 称：DS18B20_Read_Byte
 * 函 数 说 明：从DS18B20读取一个字节
 * 函 数 形 参：无
 * 函 数 返 回：读取到的字节数据
 * 作       者：LC
 * 备       注：无
******************************************************************/
uint8_t DS18B20_Read_Byte(void)
{
        uint8_t i=0,dat=0;

        for (i=0;i<8;i++)
        {
        DQ_OUT();//设置为输入模式
        DQ(0); //拉低
        T16B0_delay_us(2);
        DQ(1); //释放总线
        DQ_IN();//设置为输入模式
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
        DQ_OUT();//设置输出模式
        for (i=0;i<8;i++)
        {
                if ( (dat&0x01) ) //写1
                {
                        DQ(0);
                        T16B0_delay_us(2);
                        DQ(1);
                        T16B0_delay_us(60);
                }
                else //写0
                {
                        DQ(0);//拉低60us
                        T16B0_delay_us(60);
                        DQ(1);//释放总线
                        T16B0_delay_us(2);
                }
        dat=dat>>1;//传输下一位
        }
}

uint8_t DS18B20_Check(void)
{
        uint8_t timeout=0;
    //复位DS18B20
        DQ_OUT(); //设置为输出模式
        DQ(0); //拉低DQ
        T16B0_delay_us(750); //拉低750us
        DQ(1); //拉高DQ
        T16B0_delay_us(15);  //15us

    //设置为输入模式
        DQ_IN();
    //等待拉低，拉低说明有应答
        while ( DQ_GET() &&timeout<200)
        {
                timeout++;//超时判断
                T16B0_delay_us(1);
        };
        //设备未应答
        if(timeout>=200)
                return 1;
        else
                timeout=0;

        //等待18B20释放总线
        while ( !DQ_GET() &&timeout<240)
        {
                timeout++;//超时判断
                T16B0_delay_us(1);
        };
    //释放总线失败
        if(timeout>=240)
                return 1;

        return 0;
}

void DS18B20_Start(void)
{
        DS18B20_Check();                //查询是否有设备应答
        DS18B20_Write_Byte(0xcc);   //对总线上所有设备进行寻址
        DS18B20_Write_Byte(0x44);   //启动温度转换
}

float DS18B20_GetTemperture(void)
{
        uint16_t temp;
        uint8_t dataL=0,dataH=0;
        float value;

        DS18B20_Start();
        DS18B20_Check();
        DS18B20_Write_Byte(0xcc);//对总线上所有设备进行寻址
        DS18B20_Write_Byte(0xbe);// 读取数据命令
        dataL=DS18B20_Read_Byte(); //LSB
        dataH=DS18B20_Read_Byte(); //MSB
        temp=(dataH<<8)+dataL;//整合数据

        if(dataH&0X80)//高位为1，说明是负温度
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
