//#include <LPC11xx.h>
//#define WREN    0X06         //写入使能
//#define WRDI    0X04
//#define RDSR    0X05
//#define WRSR    0X01
//#define READ    0X03
//#define WRITE    0X02
//extern uint8_t src_addr[16]; //写
//extern uint8_t dest_addr[16];//读
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
//extern uint8_t buf[100]; //存放温度
//float temp_1;
//uint32_t Rcv_Buf[100]; //存放数据
//int buf_i=0;//数据长度
//void SPI1_Read_FLASH(uint8_t *data,uint8_t Length);
//void SPI1_Write_FLASH(uint8_t *data, uint8_t Length);
//uint8_t dest_addr[16];
//uint8_t src_addr[16];
//uint8_t XT25_ReadSR();
//uint8_t buf[100]; //存放温度
//uint8_t buf_1[100]; //存放温度
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

//uint32_t Rcv_Buf[100]; //存放数据
//void DS1307_Write(uint8_t *data);
//int i;
//void DS1307Init(){
////	Ds1307_WriteByte(0x00,0x01);  //秒
////	Ds1307_WriteByte(0x01,0x01);  //分
////	Ds1307_WriteByte(0x02,0x01);  //时
////	Ds1307_WriteByte(0x03,0x01);  //星期
////	Ds1307_WriteByte(0x04,0x01);  //日
////	Ds1307_WriteByte(0x05,0x01);  //月
////	Ds1307_WriteByte(0x06,0x01);  //年
//	uint8_t time[7]={0x00,0x01,0x21,0x05,0x25,0x11,0x22};
//	DS1307_Write(time); 
//}

///**
//* 函数功能：DS1307读
//*						全读
//*/
//void DS1307_Read(uint8_t *data){
//	
//	Ds1307_WriteByte(0x3f,0x01);//定位ds1307内部指针到0x3f(RAM尾部)处
//	I2c_Start();//start

//	I2C_Send_Byte(0xd1);//读

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
//* 函数功能：DS1307写
//*						全写
//*/
//void DS1307_Write(uint8_t *data){
//	
//	
//	I2c_Start();//start

//	I2C_Send_Byte(0xd0);//读

//	LPC_I2C->CONSET =(1<<2);//AA=1
//	I2C_Send_Byte(0x00);//从0x00开始写入
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
//*函数功能：DS1307写一个字节
//*/
//void Ds1307_WriteByte(uint8_t WriteAddr,uint8_t WriteData)
//{
//			//I2C_Start();     
//	  I2c_Start();//start
//		
//    I2C_Send_Byte(0xd0);    // Device Addr + Write (operation) 
//    I2C_Send_Byte(WriteAddr);
//	

//		LPC_I2C->CONCLR =(1<<2);//AA=0    接受完下一个字节后返回非应答信号
//    I2C_Send_Byte(WriteData);
//   
//    I2C_Stop();   
//    
//}


///*
//* 函数功能：DS1307读一个字节
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
//*uart初始化
//*clk 12MHZ
//*115200 8 1 N
//*FIFO 深度8
//*/
//void UARTInit(){
//  //配置引脚
//    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);//使能IO
//        LPC_SYSCON->SYSAHBCLKCTRL |=(1<<6) ;//使能GPIO
//    LPC_IOCON->PIO1_6 |= 0x01; //设置成RXD 引脚
//    LPC_IOCON->PIO1_7 |= 0x01; //设置成TXD 引脚

//    LPC_UART->LCR=3; //数据8 停止1 无校验

//    //设置波特率115384  近似115200
//    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<12);//使能UART
//    LPC_SYSCON->UARTCLKDIV=4;  //设置分频值4  获得UART时钟为12Mhz
//    LPC_UART->LCR=0X83; //DLAB=1
//    LPC_UART->DLL=4;
//    LPC_UART->DLM=0;
//    LPC_UART->LCR=0x03; //DLAB=0
//    LPC_UART->FDR=0X85; //MIV=8 DIV=5
//    
//    
//    LPC_UART->FCR  =0X81; //使能FIFO 深度设置为8
//    LPC_UART->IER |=1<<0; //使能接受中断
//    NVIC_EnableIRQ(UART_IRQn); //启动中断
//    
//}

///*
//*发送字符串
//*/
//void UART_Send(uint8_t str[],int lenght){
//    int i;
//    for(i=0;i<lenght;i++){
//        LPC_UART->THR= str[i];
//            while((LPC_UART->LSR&0X40)==0);//等待数据发送完成
//    }
//}
///*
//*发送 一个字节
//*/
//void UART_Send_Bit(uint8_t data){
//    LPC_UART->THR= data;
//            while((LPC_UART->LSR&0X40)==0);//等待数据发送完成
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
//              Rcv_Buf[buf_i++]=LPC_UART->RBR; //接受数据
//                    
//            }
//        break;
//            
//        case 0x0c: //CTI
//            while((LPC_UART->LSR&0X01)==1){
//              Rcv_Buf[buf_i]=LPC_UART->RBR;//接受数据
//                if( Rcv_Buf[buf_i]==0xff){//从XT52里面读取已经保存好的温度        
//                    SPI1_Read_FLASH(data,7);
//                    UART_Send("Temputerature=",14);
//                    UART_Send(data,7);  //发送温度到pc
//                    //发送换行
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
//    I2C_Send_Byte(0x91);//读
//    LPC_I2C->CONSET =(1<<2);//AA=1
//    Temputerature_8=I2C_Recieve_Byte();//高八位
//    LPC_I2C->CONCLR =(1<<2);//AA=0
//    Temputerature_16=(Temputerature_8<<8)+I2C_Recieve_Byte();//合成温度
//    I2C_Stop();//STOP
//    //温度转换
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
//    temp=Temputerature_Test();//获得温度
//   
//    //将int 转为char 同时'0'对应00000000 对数值无影响
//    buf[0]=temp/100000+'0';//
//    if((temp/100000)==0)
//            buf[0]=' ';//不显示0
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
//*函数功能：I2C 初始化
//*/
//void I2CInit(){
//    LPC_SYSCON->PRESETCTRL |= (1<<1); //复位取消
//    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<5);//使能I2C
//    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);//使能IO配置块
//    
//  //选择快速模式
//    LPC_IOCON->PIO0_4 &=~(0X3F); //选择快速模式
//    LPC_IOCON->PIO0_4 |=0X01;//选择SCL
//    LPC_IOCON->PIO0_5 &=~(0X3F); //选择快速模式
//    LPC_IOCON->PIO0_5 |=0X01;//选择SDA
//    
//    //设置SCL频率为400kHZ
//    LPC_I2C->SCLH=40;
//    LPC_I2C->SCLL=80;
//    
//    //使能I2C 同时将其他控制位清0
//    LPC_I2C->CONCLR=0XFF;
//    LPC_I2C->CONSET |=(1<<6);
//}
///*
//*函数功能：发送开始信号
//*/
//void I2c_Start(){
//    LPC_I2C->CONSET =(1<<5);// 发送开始信号
//    while(!(LPC_I2C->CONSET&(1<<3))){//等待开始信号发送完成 SI置位
//    }
//    LPC_I2C->CONCLR =(1<<5|1<<3); //清零START 和SI
//}

///*
//*函数功能：发送停止信号
//*/
//void I2C_Stop(){
//    LPC_I2C->CONCLR =(1<<3);
//    LPC_I2C->CONSET =(1<<4);// 发送停止信号
//    while((LPC_I2C->CONSET&(1<<4))){//等待停止信号发送完成 SI置位
//    }
//}
///*
//*函数功能：发送一个字节
//*/
//void I2C_Send_Byte(uint8_t data){
//    LPC_I2C->DAT=data;
//    LPC_I2C->CONCLR =(1<<3); //开始发送数据 清SI
//        while(!(LPC_I2C->CONSET&(1<<3))){//等待数据发送完成 SI置位
//    }
//}
///*
//*函数功能：接受一个字节
//*/
//uint8_t I2C_Recieve_Byte(){
//    LPC_I2C->CONCLR =(1<<3);//开始接受数据  清SI
//    while(!(LPC_I2C->CONSET&(1<<3))){//等待接受数据完成 SI置位
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
//*函数功能：16B0 初始化?
//*计时1s
//*/
//void TMR16B0_Init(){//定时器初始化 定时5s
//    LPC_SYSCON->SYSAHBCLKCTRL |=(1<<7);//使能16B0
//    LPC_TMR16B0->MCR =3; //匹配MR0时复位TC且中断
//    LPC_TMR16B0->PR=799;   //预分频值 
//    LPC_TMR16B0->MR0=SystemCoreClock/800; //  设置周期为5秒
//    LPC_TMR16B0->TCR=0X01;  //启动定时
//    NVIC_EnableIRQ(TIMER_16_0_IRQn); //启动中断
//}

///*
//*16B0中断函数
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
//		}//小灯闪烁,
//    LPC_GPIO1->DATA|=(1UL<<9);
//    LPC_GPIO1->DATA|=(1UL<<10); 
//   
//     UART_Send("fasongwendu",14);

//		SPI1_Write_FLASH(data_1,8);//  发送温度 以转换好的数组的形式发送 到xt52
//        UART_Send("Temputerature=",14);
//            UART_Send(data,7);
//						UART_Send("time is:",12);
//						UART_Send(data_1,8);
//     LPC_TMR16B0->IR |=0X01; //清中断
//}

////

//void Led_init(){
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6); // 使能时钟?
//    LPC_GPIO1->DIR |= (1<<9);
////      LPC_GPIO1->DIR |= (1<<10);
//    LPC_GPIO1->DATA &= ~(1<<9); //拉低
//}
//int main(){
//    
//     SystemInit();//  主时钟设置成48Mhz
//	
//  UARTInit(); //UART初始化
//    I2CInit();  //I2C 初始化
//    SSPI1_Init();
//    Delay_1s();
//	  DS1307Init();
//    Led_init();
//    TMR16B0_Init();  //开启定时器
//    while(1){
//    }
//}
