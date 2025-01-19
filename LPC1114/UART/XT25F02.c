#include "XT25F02.h"
#include "SSPI1.h"
#include "Delay.h"


extern uint8_t Write_Addr[16]; //д
extern uint8_t Read_Addr[16];//��

/**
* �������ܣ�д��ʹ��
*/
void XT25_WriteEnable(void){
    SSP1_LOW();
    SPI1_Comunicate(WREN);
    SSP1_HIGH();
}
/**
* �������ܣ���״̬�Ĵ���
*/
uint8_t XT25_ReadSR(void){
    uint8_t sr;
    SSP1_LOW();
    SPI1_Comunicate(RDSR);//���Ͷ�ȡ����
    sr=SPI1_Comunicate(0xff);//�õ��Ĵ�������
    SSP1_HIGH();
    return  sr;
}

/*
*�������ܣ�æµ�ȴ� д��ȴ�
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
*�������ܣ�æµ�ȴ� �����ȴ�
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
* �������ܣ�д��״̬�Ĵ���
*/
void XT25_WriteSR(uint8_t sr){
    XT25_WriteEnable();//д��ʹ��
    T16B0_delay_ms(50);//��ʱ1��
    SSP1_LOW();
    SPI1_Comunicate(0X01);
    SPI1_Comunicate(sr);//
    SSP1_HIGH();
}
/**
* �������ܣ���ΨһID
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
*�������ܣ�ȫ������
*/
void XT25_EraseAll(void){


    XT25_WriteSR(0x00);//BP1=0 BP0=0
    T16B0_delay_ms(50);//��ʱ1��
    XT25_WriteEnable();//д��ʹ�� WEL=1
    T16B0_delay_ms(50);//��ʱ1��
    SSP1_LOW();
    SPI1_Comunicate(0X60);
    SSP1_HIGH();
}
/**
*�������ܣ���������
*/
void XT25_EraseSector(void){
    XT25_WriteSR(0x00);//BP1=0 BP0=0
    T16B0_delay_ms(50);//��ʱ1��
    
    XT25_WriteEnable();//д��ʹ��
    T16B0_delay_ms(50);//��ʱ0.1��
    SSP1_LOW();
    SPI1_Comunicate(0X20);
    SPI1_Comunicate(0x22);//
    SPI1_Comunicate(0x22);//
    SPI1_Comunicate(0x22);//
    SSP1_HIGH();
    T16B0_delay_ms(100);//��ʱ0.1�룬�ȴ��������
}


/*
*�������ܣ�дFLASH
*/
void SPI1_Write_FLASH(uint8_t *data, uint8_t Length){
    XT25_WriteEnable();//д��ʹ��
    T16B0_delay_ms(50);//��ʱ1��

    Write_Addr[0]=WRITE;//ҳ���̿�ʼ
    //��ַ1~3
    Write_Addr[1]=0x22;
    Write_Addr[2]=0x22;
    Write_Addr[3]=0x22;
    //д�������
    for(int i=0;i<Length;i++){
        Write_Addr[i+4]=data[i];
    }
    XT25_Write_Wait(); //æʱ�ȴ�
    SSP1_LOW();//ʹ��
    SSP1_Send((uint8_t *)Write_Addr,4+Length);
    SSP1_HIGH();//����
}
/**
* �������ܣ���flash
*/
void SPI1_Read_FLASH(uint8_t *data,uint8_t Length){
    Write_Addr[0]=READ;
    //��ȡ�ĵ�ַ
    Write_Addr[1]=0x22;
    Write_Addr[2]=0x22;
    Write_Addr[3]=0x22;
    XT25_Read_Wait();
    SSP1_LOW();
    SSP1_Send((uint8_t *)Write_Addr,4);
    SSP1_Receive((uint8_t *)Read_Addr,Length);//�����¶�
    SSP1_HIGH();
    for(int i=0;i<Length;i++){ //�¶�Ϊ3������ 1��С���� 2��С��
            data[i] = Read_Addr[i];
    }
}


