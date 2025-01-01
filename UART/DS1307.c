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
* �������ܣ�DS1307��
*						ȫ��
*/
void DS1307_Read(void)
{
	Ds1307_WriteByte(0x3f,0x01);//��λds1307�ڲ�ָ�뵽0x3f(RAMβ��)��
	I2C_Start();//starts
	I2C_Send_Byte(0xd1);//��
	LPC_I2C->CONSET =(1<<2);//AA=1	
	data[0]=I2C_Recieve_Byte();
    data[1]=I2C_Recieve_Byte();
	data[2]=I2C_Recieve_Byte();
	data[3]=I2C_Recieve_Byte();
	data[4]=I2C_Recieve_Byte();
	data[5]=I2C_Recieve_Byte();
	LPC_I2C->CONCLR =(1<<2);//AA=0
	data[6]=I2C_Recieve_Byte();
	
	Time_Data[0]=data[2]/16+'0';  // ʱ
	Time_Data[1]=data[2]%16+'0';
	Time_Data[2]=':';
	Time_Data[3]=data[1]/16+'0';  // ��
	Time_Data[4]=data[1]%16+'0';
	Time_Data[5]=':';
	Time_Data[6]=data[0]/16+'0';  // ��
	Time_Data[7]=data[0]%16+'0';

    Date[0]=2+'0';
	Date[1]=0+'0';
	Date[2]=data[6]/16+'0'; // ��
	Date[3]=data[6]%16+'0';
	Date[4]='-';
	Date[5]=data[5]/16+'0'; // ��
	Date[6]=data[5]%16+'0';
	Date[7]='-';
	Date[8]=data[4]/16+'0'; // ��
	Date[9]=data[4]%16+'0';
	
	Week[0] = data[3]%16+'0';
	
	I2C_Stop();//STOP
	
}

/**
* �������ܣ�DS1307д
*						ȫд
*/
void DS1307_Write(uint8_t *data)
{
	I2C_Start();//start
	I2C_Send_Byte(0xd0);//��
	LPC_I2C->CONSET =(1<<2);//AA=1
	I2C_Send_Byte(0x00);//��0x00��ʼд��
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
*�������ܣ�DS1307дһ���ֽ�
*/

void Ds1307_WriteByte(uint8_t WriteAddr,uint8_t WriteData)
{   
	I2C_Start();//start	
    I2C_Send_Byte(0xd0);    // Device Addr + Write (operation) 
    I2C_Send_Byte(WriteAddr);
    LPC_I2C->CONCLR =(1<<2);//AA=0    ��������һ���ֽں󷵻ط�Ӧ���ź�
    I2C_Send_Byte(WriteData);
    I2C_Stop();    
}


/*
* �������ܣ�DS1307��һ���ֽ�
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
