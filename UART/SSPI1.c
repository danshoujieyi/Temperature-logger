#include "SSPI1.h"

extern uint8_t Write_Addr[16]; //写
extern uint8_t Read_Addr[16];//读

/*
*函数功能：SSP1IO初始化
*/
void SSP1_IOConfig(void){
    LPC_SYSCON->SYSAHBCLKCTRL |=((1<<6)|(1<<16)); //IO 和GPIO
    LPC_IOCON->PIO2_2 &=~(0X07); //
    LPC_IOCON->PIO2_2 |=0X02;// MISO
    
    LPC_IOCON->PIO2_3 &=~(0X07); //
    LPC_IOCON->PIO2_3 |=0X02;//MOSI  此处可能出现问题

    LPC_IOCON->PIO2_1 &=~(0X07); //
    LPC_IOCON->PIO2_1 |=0X02;//CLK
    
    LPC_GPIO2->DIR |= (1<<0);
    LPC_GPIO2->DATA |= (1<<0); //拉高
}

/**
*函数功能：SSP1初始化
*/
void SSPI1_Init(void){
    uint8_t Dummy=Dummy; //随机数
    uint8_t i;
    
    LPC_SYSCON->PRESETCTRL |=1<<2; //复位ssp1
    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<18); //ssp1 时钟使能
    LPC_SYSCON->SSP1CLKDIV=0X02 ;  //分频值 2 48/2=24
    
    SSP1_IOConfig(); //初始化SSP1 IO口
    
    LPC_SSP1->CR0=0X0707;   //CPSR=7 DATAbit= 8 CPOL=0 CPHA=0 SCR=7  选择spi
    //LPC_SSP1->CR0=0X07c7;  //SPI模式3

    LPC_SSP1->CPSR=0X2;   //SCLK=48/(2*2*8)= 1.5M

    
    LPC_SSP1->CR1 &=~(1<<0);//LBM=0 :正常模式
    LPC_SSP1->CR1 &=~(1<<2);//MS=0 主机模式
    LPC_SSP1->CR1 |=1<<1; //SSE=1 开启ssp1
    
    //清空RXFIFO
    for(i=0 ; i<8 ;i++){
        Dummy = LPC_SSP1->DR;
    }
	
    for(i=0;i<16;i++){
        Read_Addr[i]=0;
        Write_Addr[i]=0;
    }
    
}

void SSP1_LOW(void){
    LPC_GPIO2->DATA &= ~(1<<0); //拉低
}
void SSP1_HIGH(void){
    LPC_GPIO2->DATA |= (1<<0); //拉高
}

/**
* 函数功能：SSP1通信
* 接受和发送一个字符
*/
uint8_t SPI1_Comunicate(uint8_t TxData){
    while(((LPC_SSP1->SR)&(1<<4))==(1<<4));//忙时等待
    LPC_SSP1->DR=TxData; //发送数据到TxFIFO
    while(((LPC_SSP1->SR)&(1<<2))!=(1<<2));//等待数据接受完
    return (LPC_SSP1->DR); //接受返回的数据
}

/**
*函数功能：SSP1发送
*/
void SSP1_Send(uint8_t *data,uint8_t Length){
    uint8_t i;
    for(i=0;i<Length;i++){
        SPI1_Comunicate(data[i]);
    }
}

/**
* 函数功能：SSP1接受
*/
void SSP1_Receive(uint8_t *data,int Length){
    uint8_t Dummy=Dummy; //随机数 用于产生时钟
    uint8_t i;
    for(i=0 ; i<Length ;i++){
        data[i]=SPI1_Comunicate(0xff);
    }
}
