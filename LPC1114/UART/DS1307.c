#include "DS1307.h"
#include "I2C.h"

extern uint8_t Time_Data[10];
extern uint8_t Date[10];
extern uint8_t Time[7];
extern uint8_t Week[1];
extern 	uint8_t data[7];

void DS1307Init(void)
{
	DS1307_Write(Time); 
}

/**
* 函数功能：DS1307读
*						全读
*/
void DS1307_Read(void)
{
	Ds1307_WriteByte(0x3f,0x01);//定位ds1307内部指针到0x3f(RAM尾部)处
	I2C_Start();//starts
	I2C_Send_Byte(0xd1);//读
	LPC_I2C->CONSET =(1<<2);//AA=1	
	data[0]=I2C_Recieve_Byte();
    data[1]=I2C_Recieve_Byte();
	data[2]=I2C_Recieve_Byte();
	data[3]=I2C_Recieve_Byte();
	data[4]=I2C_Recieve_Byte();
	data[5]=I2C_Recieve_Byte();
	LPC_I2C->CONCLR =(1<<2);//AA=0
	data[6]=I2C_Recieve_Byte();
	
	Time_Data[0]=data[2]/16+'0';  // 时
	Time_Data[1]=data[2]%16+'0';
	Time_Data[2]=':';
	Time_Data[3]=data[1]/16+'0';  // 分
	Time_Data[4]=data[1]%16+'0';
	Time_Data[5]=':';
	Time_Data[6]=data[0]/16+'0';  // 秒
	Time_Data[7]=data[0]%16+'0';

    Date[0]=2+'0';
	Date[1]=0+'0';
	Date[2]=data[6]/16+'0'; // 年
	Date[3]=data[6]%16+'0';
	Date[4]='-';
	Date[5]=data[5]/16+'0'; // 月
	Date[6]=data[5]%16+'0';
	Date[7]='-';
	Date[8]=data[4]/16+'0'; // 日
	Date[9]=data[4]%16+'0';
	
	Week[0] = data[3]%16+'0';
	
	I2C_Stop();//STOP
	
}

/**
* 函数功能：DS1307写
*						全写
*/
void DS1307_Write(uint8_t *data)
{
	I2C_Start();//start
	I2C_Send_Byte(0xd0);//读
	LPC_I2C->CONSET =(1<<2);//AA=1
	I2C_Send_Byte(0x00);//从0x00开始写入
	I2C_Send_Byte(data[0]);
	I2C_Send_Byte(data[1]);
	I2C_Send_Byte(data[2]);
	I2C_Send_Byte(data[3]);
	I2C_Send_Byte(data[4]);
	I2C_Send_Byte(data[5]);	
	LPC_I2C->CONCLR =(1<<2);//AA=0
	I2C_Send_Byte(data[6]);
	I2C_Stop();//STOP
}


/*
*函数功能：DS1307写一个字节
*/

void Ds1307_WriteByte(uint8_t WriteAddr,uint8_t WriteData)
{   
	I2C_Start();//start	
    I2C_Send_Byte(0xd0);    // Device Addr + Write (operation) 
    I2C_Send_Byte(WriteAddr);
    LPC_I2C->CONCLR =(1<<2);//AA=0    接受完下一个字节后返回非应答信号
    I2C_Send_Byte(WriteData);
    I2C_Stop();    
}


/*
* 函数功能：DS1307读一个字节
*/
uint8_t Ds1307_ReadByte(void)
{
	uint8_t RevData;

	I2C_Start();//start               
	I2C_Send_Byte(0xD1);     // Device Addr + Write (operation)   
	LPC_I2C->CONCLR =(1<<2);//AA=0
	RevData = I2C_Recieve_Byte();    
	I2C_Stop();   

	return RevData;
}
