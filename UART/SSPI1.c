#include "SSPI1.h"

extern uint8_t Write_Addr[16]; //д
extern uint8_t Read_Addr[16];//��

/*
*�������ܣ�SSP1IO��ʼ��
*/
void SSP1_IOConfig(void){
    LPC_SYSCON->SYSAHBCLKCTRL |=((1<<6)|(1<<16)); //IO ��GPIO
    LPC_IOCON->PIO2_2 &=~(0X07); //
    LPC_IOCON->PIO2_2 |=0X02;// MISO
    
    LPC_IOCON->PIO2_3 &=~(0X07); //
    LPC_IOCON->PIO2_3 |=0X02;//MOSI  �˴����ܳ�������

    LPC_IOCON->PIO2_1 &=~(0X07); //
    LPC_IOCON->PIO2_1 |=0X02;//CLK
    
    LPC_GPIO2->DIR |= (1<<0);
    LPC_GPIO2->DATA |= (1<<0); //����
}

/**
*�������ܣ�SSP1��ʼ��
*/
void SSPI1_Init(void){
    uint8_t Dummy=Dummy; //�����
    uint8_t i;
    
    LPC_SYSCON->PRESETCTRL |=1<<2; //��λssp1
    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<18); //ssp1 ʱ��ʹ��
    LPC_SYSCON->SSP1CLKDIV=0X02 ;  //��Ƶֵ 2 48/2=24
    
    SSP1_IOConfig(); //��ʼ��SSP1 IO��
    
    LPC_SSP1->CR0=0X0707;   //CPSR=7 DATAbit= 8 CPOL=0 CPHA=0 SCR=7  ѡ��spi
    //LPC_SSP1->CR0=0X07c7;  //SPIģʽ3

    LPC_SSP1->CPSR=0X2;   //SCLK=48/(2*2*8)= 1.5M

    
    LPC_SSP1->CR1 &=~(1<<0);//LBM=0 :����ģʽ
    LPC_SSP1->CR1 &=~(1<<2);//MS=0 ����ģʽ
    LPC_SSP1->CR1 |=1<<1; //SSE=1 ����ssp1
    
    //���RXFIFO
    for(i=0 ; i<8 ;i++){
        Dummy = LPC_SSP1->DR;
    }
	
    for(i=0;i<16;i++){
        Read_Addr[i]=0;
        Write_Addr[i]=0;
    }
    
}

void SSP1_LOW(void){
    LPC_GPIO2->DATA &= ~(1<<0); //����
}
void SSP1_HIGH(void){
    LPC_GPIO2->DATA |= (1<<0); //����
}

/**
* �������ܣ�SSP1ͨ��
* ���ܺͷ���һ���ַ�
*/
uint8_t SPI1_Comunicate(uint8_t TxData){
    while(((LPC_SSP1->SR)&(1<<4))==(1<<4));//æʱ�ȴ�
    LPC_SSP1->DR=TxData; //�������ݵ�TxFIFO
    while(((LPC_SSP1->SR)&(1<<2))!=(1<<2));//�ȴ����ݽ�����
    return (LPC_SSP1->DR); //���ܷ��ص�����
}

/**
*�������ܣ�SSP1����
*/
void SSP1_Send(uint8_t *data,uint8_t Length){
    uint8_t i;
    for(i=0;i<Length;i++){
        SPI1_Comunicate(data[i]);
    }
}

/**
* �������ܣ�SSP1����
*/
void SSP1_Receive(uint8_t *data,int Length){
    uint8_t Dummy=Dummy; //����� ���ڲ���ʱ��
    uint8_t i;
    for(i=0 ; i<Length ;i++){
        data[i]=SPI1_Comunicate(0xff);
    }
}
