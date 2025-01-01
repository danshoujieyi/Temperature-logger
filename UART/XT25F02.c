#include "XT25F02.h"
#include "SSPI1.h"
#include "Delay.h"


extern uint8_t Write_Addr[16]; //写
extern uint8_t Read_Addr[16];//读

/**
* 函数功能：写入使能
*/
void XT25_WriteEnable(void){
    SSP1_LOW();
    SPI1_Comunicate(WREN);
    SSP1_HIGH();
}
/**
* 函数功能：读状态寄存器
*/
uint8_t XT25_ReadSR(void){
    uint8_t sr;
    SSP1_LOW();
    SPI1_Comunicate(RDSR);//发送读取命令
    sr=SPI1_Comunicate(0xff);//得到寄存器数据
    SSP1_HIGH();
    return  sr;
}

/*
*函数功能：忙碌等待 写入等待
*/
void XT25_Write_Wait(void){
    int stat_code=0;
    while(1){
        stat_code = XT25_ReadSR();
        if(((stat_code&1<<1)==0x02)&&(stat_code&1)==0){
            break;
        }
    }
}
/*
*函数功能：忙碌等待 读出等待
*/
void XT25_Read_Wait(void){
    int stat_code=0;
    while(1){
        stat_code=XT25_ReadSR();
        if((stat_code&1)==0){
            break;
        }
    }
}

/**
* 函数功能：写入状态寄存器
*/
void XT25_WriteSR(uint8_t sr){
    XT25_WriteEnable();//写入使能
    T16B0_delay_ms(50);//延时1秒
    SSP1_LOW();
    SPI1_Comunicate(0X01);
    SPI1_Comunicate(sr);//
    SSP1_HIGH();
}
/**
* 函数功能：读唯一ID
*/
void XT25_RUID(void){
    
    Write_Addr[0]=0X4B;
    Write_Addr[1]=0x00;
    Write_Addr[2]=0x00;
    Write_Addr[3]=0x00;
    SSP1_LOW();
    SSP1_Receive((uint8_t *)Read_Addr,16);
    SSP1_HIGH();
}

/**
*函数功能：全部擦除
*/
void XT25_EraseAll(void){


    XT25_WriteSR(0x00);//BP1=0 BP0=0
    T16B0_delay_ms(50);//延时1秒
    XT25_WriteEnable();//写入使能 WEL=1
    T16B0_delay_ms(50);//延时1秒
    SSP1_LOW();
    SPI1_Comunicate(0X60);
    SSP1_HIGH();
}
/**
*函数功能：扇区擦除
*/
void XT25_EraseSector(void){
    XT25_WriteSR(0x00);//BP1=0 BP0=0
    T16B0_delay_ms(50);//延时1秒
    
    XT25_WriteEnable();//写入使能
    T16B0_delay_ms(50);//延时0.1秒
    SSP1_LOW();
    SPI1_Comunicate(0X20);
    SPI1_Comunicate(0x22);//
    SPI1_Comunicate(0x22);//
    SPI1_Comunicate(0x22);//
    SSP1_HIGH();
    T16B0_delay_ms(100);//延时0.1秒，等待擦除完成
}


/*
*函数功能：写FLASH
*/
void SPI1_Write_FLASH(uint8_t *data, uint8_t Length){
    XT25_WriteEnable();//写入使能
    T16B0_delay_ms(50);//延时1秒

    Write_Addr[0]=WRITE;//页面编程开始
    //地址1~3
    Write_Addr[1]=0x22;
    Write_Addr[2]=0x22;
    Write_Addr[3]=0x22;
    //写入的数据
    for(int i=0;i<Length;i++){
        Write_Addr[i+4]=data[i];
    }
    XT25_Write_Wait(); //忙时等待
    SSP1_LOW();//使能
    SSP1_Send((uint8_t *)Write_Addr,4+Length);
    SSP1_HIGH();//拉高
}
/**
* 函数功能：读flash
*/
void SPI1_Read_FLASH(uint8_t *data,uint8_t Length){
    Write_Addr[0]=READ;
    //读取的地址
    Write_Addr[1]=0x22;
    Write_Addr[2]=0x22;
    Write_Addr[3]=0x22;
    XT25_Read_Wait();
    SSP1_LOW();
    SSP1_Send((uint8_t *)Write_Addr,4);
    SSP1_Receive((uint8_t *)Read_Addr,Length);//接受温度
    SSP1_HIGH();
    for(int i=0;i<Length;i++){ //温度为3个整数 1个小数点 2个小数
            data[i] = Read_Addr[i];
    }
}


