//#include <LPC11xx.h>
//#define WREN    0X06         //д��ʹ��
//#define WRDI    0X04
//#define RDSR    0X05
//#define WRSR    0X01
//#define READ    0X03
//#define WRITE    0X02
//extern uint8_t src_addr[16]; //д
//extern uint8_t dest_addr[16];//��
//void XT25_WriteEnable();

//void UART_Send(uint8_t str[],int lenght);
//void UART_Send_Bit(uint8_t data);
//uint8_t XT25_ReadSR();
//uint8_t SPI1_comunication(uint8_t TxData);
//void XT25_Erase();
//void XT25_Write_Wait();
//void XT25_Read_Wait();
//void UARTInit();
//void I2CInit();
//void TMR16B0_Init();
//void SSPI1_Init();
//void Delay_1s(void);
//void I2c_Start();
//void I2C_Stop();
//void I2C_Send_Byte(uint8_t data);
////void UART_Send(uint8_t str[],int lenght);
//uint8_t I2C_Recieve_Byte();
////uint16_t temp_1;
//extern uint8_t buf[100]; //����¶�
//float temp_1;
//uint32_t Rcv_Buf[100]; //�������
//int buf_i=0;//���ݳ���
//void SPI1_Read_FLASH(uint8_t *data,uint8_t Length);
//void SPI1_Write_FLASH(uint8_t *data, uint8_t Length);
//uint8_t dest_addr[16];
//uint8_t src_addr[16];
//uint8_t XT25_ReadSR();
//uint8_t buf[100]; //����¶�
//uint8_t buf_1[100]; //����¶�
//void XT25_WriteEnable();
//void XT25_RUID();
//void XT25_Erase();
//void XT25_WriteSR(uint8_t sr);
//void XT25_EraseSector();
//void Delay_1s(void);
//void DS1307Init();
//void Delay_1s();
//void DS1307_Read(uint8_t *data);
//uint8_t I2C_Recieve_Byte();
//uint8_t data_1[100];
//void Ds1307_WriteByte(uint8_t WriteAddr,uint8_t WriteData);
//void DS1307_Write(uint8_t *data);

//uint32_t Rcv_Buf[100]; //�������
//void DS1307_Write(uint8_t *data);
//int i;
//void DS1307Init(){
////	Ds1307_WriteByte(0x00,0x01);  //��
////	Ds1307_WriteByte(0x01,0x01);  //��
////	Ds1307_WriteByte(0x02,0x01);  //ʱ
////	Ds1307_WriteByte(0x03,0x01);  //����
////	Ds1307_WriteByte(0x04,0x01);  //��
////	Ds1307_WriteByte(0x05,0x01);  //��
////	Ds1307_WriteByte(0x06,0x01);  //��
//	uint8_t time[7]={0x00,0x01,0x21,0x05,0x25,0x11,0x22};
//	DS1307_Write(time); 
//}

///**
//* �������ܣ�DS1307��
//*						ȫ��
//*/
//void DS1307_Read(uint8_t *data){
//	
//	Ds1307_WriteByte(0x3f,0x01);//��λds1307�ڲ�ָ�뵽0x3f(RAMβ��)��
//	I2c_Start();//start

//	I2C_Send_Byte(0xd1);//��

//	LPC_I2C->CONSET =(1<<2);//AA=1
//	
//	data[0]=I2C_Recieve_Byte();
//  data[1]=I2C_Recieve_Byte();
//	data[2]=I2C_Recieve_Byte();
//	data[3]=I2C_Recieve_Byte();
//	data[4]=I2C_Recieve_Byte();
//	data[5]=I2C_Recieve_Byte();
//	
//	
//	data_1[0]=data[2]/16+'0';
//	data_1[1]=data[2]%16+'0';
//	data_1[2]=':';
//	data_1[3]=data[1]/16+'0';
//	data_1[4]=data[1]%16+'0';
//	data_1[5]=':';
//	data_1[6]=data[0]/16+'0';
//	data_1[7]=data[0]%16+'0';
//	
//	LPC_I2C->CONCLR =(1<<2);//AA=0

//	data[6]=I2C_Recieve_Byte();

//	I2C_Stop();//STOP
//	
//}

///**
//* �������ܣ�DS1307д
//*						ȫд
//*/
//void DS1307_Write(uint8_t *data){
//	
//	
//	I2c_Start();//start

//	I2C_Send_Byte(0xd0);//��

//	LPC_I2C->CONSET =(1<<2);//AA=1
//	I2C_Send_Byte(0x00);//��0x00��ʼд��
//	I2C_Send_Byte(data[0]);
//  I2C_Send_Byte(data[1]);
//  I2C_Send_Byte(data[2]);
//  I2C_Send_Byte(data[3]);
//  I2C_Send_Byte(data[4]);
//  I2C_Send_Byte(data[5]);	
//	
//	LPC_I2C->CONCLR =(1<<2);//AA=0
//	I2C_Send_Byte(data[6]);

//	I2C_Stop();//STOP
//	
//}


///*
//*�������ܣ�DS1307дһ���ֽ�
//*/
//void Ds1307_WriteByte(uint8_t WriteAddr,uint8_t WriteData)
//{
//			//I2C_Start();     
//	  I2c_Start();//start
//		
//    I2C_Send_Byte(0xd0);    // Device Addr + Write (operation) 
//    I2C_Send_Byte(WriteAddr);
//	

//		LPC_I2C->CONCLR =(1<<2);//AA=0    ��������һ���ֽں󷵻ط�Ӧ���ź�
//    I2C_Send_Byte(WriteData);
//   
//    I2C_Stop();   
//    
//}


///*
//* �������ܣ�DS1307��һ���ֽ�
//*/
//uint8_t Ds1307_ReadByte()
//{
//  uint8_t RevData;
//  
//  I2c_Start();//start               
//  I2C_Send_Byte(0xD1);     // Device Addr + Write (operation)   
//  
//	LPC_I2C->CONCLR =(1<<2);//AA=0
//  RevData = I2C_Recieve_Byte();    
//  
// 
//  I2C_Stop();   
//  
//  return RevData;
//}
////

///*
//*uart��ʼ��
//*clk 12MHZ
//*115200 8 1 N
//*FIFO ���8
//*/
//void UARTInit(){
//  //��������
//    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);//ʹ��IO
//        LPC_SYSCON->SYSAHBCLKCTRL |=(1<<6) ;//ʹ��GPIO
//    LPC_IOCON->PIO1_6 |= 0x01; //���ó�RXD ����
//    LPC_IOCON->PIO1_7 |= 0x01; //���ó�TXD ����

//    LPC_UART->LCR=3; //����8 ֹͣ1 ��У��

//    //���ò�����115384  ����115200
//    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<12);//ʹ��UART
//    LPC_SYSCON->UARTCLKDIV=4;  //���÷�Ƶֵ4  ���UARTʱ��Ϊ12Mhz
//    LPC_UART->LCR=0X83; //DLAB=1
//    LPC_UART->DLL=4;
//    LPC_UART->DLM=0;
//    LPC_UART->LCR=0x03; //DLAB=0
//    LPC_UART->FDR=0X85; //MIV=8 DIV=5
//    
//    
//    LPC_UART->FCR  =0X81; //ʹ��FIFO �������Ϊ8
//    LPC_UART->IER |=1<<0; //ʹ�ܽ����ж�
//    NVIC_EnableIRQ(UART_IRQn); //�����ж�
//    
//}

///*
//*�����ַ���
//*/
//void UART_Send(uint8_t str[],int lenght){
//    int i;
//    for(i=0;i<lenght;i++){
//        LPC_UART->THR= str[i];
//            while((LPC_UART->LSR&0X40)==0);//�ȴ����ݷ������
//    }
//}
///*
//*���� һ���ֽ�
//*/
//void UART_Send_Bit(uint8_t data){
//    LPC_UART->THR= data;
//            while((LPC_UART->LSR&0X40)==0);//�ȴ����ݷ������
//}

//void UART_IRQHandler(){
//    int i;
//    uint8_t data[16]={0};
//    uint8_t sr;
//    for(i=0;i<16;i++){
//        data[i]=0x11;
//    }
//    switch(LPC_UART->IIR&0X0F){
//        
//        case 0x04: //RDA
//            for(i=0;i<8;i++){
//              Rcv_Buf[buf_i++]=LPC_UART->RBR; //��������
//                    
//            }
//        break;
//            
//        case 0x0c: //CTI
//            while((LPC_UART->LSR&0X01)==1){
//              Rcv_Buf[buf_i]=LPC_UART->RBR;//��������
//                if( Rcv_Buf[buf_i]==0xff){//��XT52�����ȡ�Ѿ�����õ��¶�        
//                    SPI1_Read_FLASH(data,7);
//                    UART_Send("Temputerature=",14);
//                    UART_Send(data,7);  //�����¶ȵ�pc
//                    //���ͻ���
//                  UART_Send_Bit(0x0d);
//                  UART_Send_Bit(0x0a);

//                }
//                    
//                buf_i++;
//            }
//        break;
//    }  
//}
////
//uint16_t Temputerature_Test(){
//    uint16_t Temputerature_8,Temputerature_16;
//    
//    float Temputerature;
//    I2c_Start();//start
//    I2C_Send_Byte(0x91);//��
//    LPC_I2C->CONSET =(1<<2);//AA=1
//    Temputerature_8=I2C_Recieve_Byte();//�߰�λ
//    LPC_I2C->CONCLR =(1<<2);//AA=0
//    Temputerature_16=(Temputerature_8<<8)+I2C_Recieve_Byte();//�ϳ��¶�
//    I2C_Stop();//STOP
//    //�¶�ת��
//    Temputerature_16=Temputerature_16>>5;
//    if(Temputerature_16&0x0400){
//        Temputerature=-(~(Temputerature_16&0x03ff)+1)*0.125;
//    }else{
//        Temputerature=0.125*(float)(Temputerature_16);
//    }
//    return (uint16_t)(Temputerature*1000);
//}

//void Get_temputerature(){
//    uint16_t temp;
//    temp=Temputerature_Test();//����¶�
//   
//    //��int תΪchar ͬʱ'0'��Ӧ00000000 ����ֵ��Ӱ��
//    buf[0]=temp/100000+'0';//
//    if((temp/100000)==0)
//            buf[0]=' ';//����ʾ0
//    buf[1]=temp/10000%10+'0';
//    buf[2]=temp/1000%10+'0';
//    buf[3]='.';
//    buf[4]=temp/100%10+'0';
//    buf[5]=temp/10%10+'0';
//    buf[6]=temp%10+'0';
//     temp_1=temp/1000;
//}

////

///*
//*�������ܣ�I2C ��ʼ��
//*/
//void I2CInit(){
//    LPC_SYSCON->PRESETCTRL |= (1<<1); //��λȡ��
//    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<5);//ʹ��I2C
//    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);//ʹ��IO���ÿ�
//    
//  //ѡ�����ģʽ
//    LPC_IOCON->PIO0_4 &=~(0X3F); //ѡ�����ģʽ
//    LPC_IOCON->PIO0_4 |=0X01;//ѡ��SCL
//    LPC_IOCON->PIO0_5 &=~(0X3F); //ѡ�����ģʽ
//    LPC_IOCON->PIO0_5 |=0X01;//ѡ��SDA
//    
//    //����SCLƵ��Ϊ400kHZ
//    LPC_I2C->SCLH=40;
//    LPC_I2C->SCLL=80;
//    
//    //ʹ��I2C ͬʱ����������λ��0
//    LPC_I2C->CONCLR=0XFF;
//    LPC_I2C->CONSET |=(1<<6);
//}
///*
//*�������ܣ����Ϳ�ʼ�ź�
//*/
//void I2c_Start(){
//    LPC_I2C->CONSET =(1<<5);// ���Ϳ�ʼ�ź�
//    while(!(LPC_I2C->CONSET&(1<<3))){//�ȴ���ʼ�źŷ������ SI��λ
//    }
//    LPC_I2C->CONCLR =(1<<5|1<<3); //����START ��SI
//}

///*
//*�������ܣ�����ֹͣ�ź�
//*/
//void I2C_Stop(){
//    LPC_I2C->CONCLR =(1<<3);
//    LPC_I2C->CONSET =(1<<4);// ����ֹͣ�ź�
//    while((LPC_I2C->CONSET&(1<<4))){//�ȴ�ֹͣ�źŷ������ SI��λ
//    }
//}
///*
//*�������ܣ�����һ���ֽ�
//*/
//void I2C_Send_Byte(uint8_t data){
//    LPC_I2C->DAT=data;
//    LPC_I2C->CONCLR =(1<<3); //��ʼ�������� ��SI
//        while(!(LPC_I2C->CONSET&(1<<3))){//�ȴ����ݷ������ SI��λ
//    }
//}
///*
//*�������ܣ�����һ���ֽ�
//*/
//uint8_t I2C_Recieve_Byte(){
//    LPC_I2C->CONCLR =(1<<3);//��ʼ��������  ��SI
//    while(!(LPC_I2C->CONSET&(1<<3))){//�ȴ������������ SI��λ
//    }
//    return (uint8_t)LPC_I2C->DAT;
//}

////


//void Delay_1s(void){

//    int i=SystemCoreClock/500;//0.01s

//        while(--i);

//}



////

////uint16_t temp_1;
//void dealy()
//{
//int i=SystemCoreClock/100;
//while(--i);
//}
////uint16_t temp_1;
////void LED_Init(void) {
////LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); /*enable clock for GPIO*/
////LPC_GPIO1->DIR |= (1UL << 9); /*configure GPIO1_9 as output*/
////}
//void LED_Toggle(void) {
//LPC_GPIO1->DATA &=~(1UL <<9); /* Toggle the  BLINKY LED */
//LPC_GPIO1->DATA|=(1UL<<10); 
//dealy();
//LPC_GPIO1->DATA|=(1UL<<9);
//LPC_GPIO1->DATA &=~(1UL<<10);
//}


///*
//*�������ܣ�16B0 ��ʼ��?
//*��ʱ1s
//*/
//void TMR16B0_Init(){//��ʱ����ʼ�� ��ʱ5s
//    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<7);//ʹ��16B0
//    LPC_TMR16B0->MCR =3; //ƥ��MR0ʱ��λTC���ж�
//    LPC_TMR16B0->PR=799;   //Ԥ��Ƶֵ 
//    LPC_TMR16B0->MR0=SystemCoreClock/800; //  ��������Ϊ5��
//    LPC_TMR16B0->TCR=0X01;  //������ʱ
//    NVIC_EnableIRQ(TIMER_16_0_IRQn); //�����ж�
//}

///*
//*16B0�жϺ���
//*/
//void TIMER16_0_IRQHandler(){
//        temp_1=Temputerature_Text();
//		uint8_t data[7];
//		DS1307_Read(data);
//		Get_temputerature();
//    LPC_GPIO1->DATA|=(1UL<<9);
//    LPC_GPIO1->DATA|=(1UL<<10); 
//    if(temp_1>=25.0)
//		{for(i=1;i<11;i++)
//		{LED_Toggle();dealy();}
//		}//С����˸,
//    LPC_GPIO1->DATA|=(1UL<<9);
//    LPC_GPIO1->DATA|=(1UL<<10); 
//   
//     UART_Send("fasongwendu",14);

//		SPI1_Write_FLASH(data_1,8);//  �����¶� ��ת���õ��������ʽ���� ��xt52
//        UART_Send("Temputerature=",14);
//            UART_Send(data,7);
//						UART_Send("time is:",12);
//						UART_Send(data_1,8);
//     LPC_TMR16B0->IR |=0X01; //���ж�
//}

////

//void Led_init(){
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6); // ʹ��ʱ��?
//    LPC_GPIO1->DIR |= (1<<9);
////      LPC_GPIO1->DIR |= (1<<10);
//    LPC_GPIO1->DATA &= ~(1<<9); //����
//}
//int main(){
//    
//     SystemInit();//  ��ʱ�����ó�48Mhz
//	
//  UARTInit(); //UART��ʼ��
//    I2CInit();  //I2C ��ʼ��
//    SSPI1_Init();
//    Delay_1s();
//	  DS1307Init();
//    Led_init();
//    TMR16B0_Init();  //������ʱ��
//    while(1){
//    }
//}
