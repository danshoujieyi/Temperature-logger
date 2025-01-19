///******************************************************************
// * �γ̣�����NXP LPC1114��Ƕ��ʽϵͳ���
// * ���������ο�
// * ѧ�ţ�20223004426
// * �ον�ʦ�����켪
// * �������ҵ
//******************************************************************/
///******************************************************************
// * ���뻷�����汾�� Keil MDK5 5.39
// * �������汾�� ARM Compiler version 5.06��960��
// * Ӳ���汾�� NXP LPC1114 DevKit V5.6
// * �������� DAPLink
// * ���ԣ� C����
// * ���ְ汾�� Chinese GB2312
//******************************************************************/
///* ����ͷ�ļ�"LPC11xx.h" */
// #include "AD_UART.h"   


// #define R_REFERENCE 10000.0 // ��֪�ο�����ֵ��Ϊ10k��
// #define B 3950 // B ���������� KNTC0603/10KF3950 �����ֲ���д
// uint16_t adc_value = 0; // ��ADC7 ��ȡ��ԭʼֵ
// double R = 0; // ��ADC7 ��ȡ��ת����NTC�¶ȵ���ֵ
// double temperature = 0; // ��NTC�¶ȵ���ֵ������¶�ֵ


// /******************************************************************
//  * ������: TIMER32_0_IRQHandler
//  * ����:��ʱ���жϴ��������ڶ�ʱ��0��ƥ���¼�����ʱ������ADCת������ȡADC7��ֵ
// ******************************************************************/
// void TIMER32_0_IRQHandler(void) {
//     if ((LPC_TMR32B0->IR |= 0x01) == 1) { // ���MR0�жϱ�־
//         LPC_ADC->CR |= (1 << 24); // ����ADCת��
// 		LPC_TMR32B0->IR = 0x01; // ���MR0�жϱ�־
//     }
// }

//   /******************************************************************
//  * ������: ADC_IRQHandler
//  * ����:ADC�жϴ�����
//  * ����: ��
// ******************************************************************/
//  void ADC_IRQHandler(void)
//  {
//      if (LPC_ADC->STAT & (1 << 7)) // ���AD7�Ƿ���ת�����
//      {
// 		while((LPC_ADC->DR[7]&0x80000000)==0);
// 		adc_value=LPC_ADC->DR[7];			//	��ȡADC7�Ĵ�����ֵ
// 		adc_value=(adc_value >> 6) & 0x3ff;	//��ȡ10λAD���
//		
//        uint8_t data_to_send[2]; // �������ݵ�����
//        data_to_send[0] = (adc_value & 0xFF);         // ��λ
//        data_to_send[1] = (adc_value >> 8) & 0xFF;   // ��λ
//        UARTSend(data_to_send, 2); // ���������ֽ�
// 		UARTSend("\r\n", 2);  // ��ӻس�����
// 		R = (adc_value * 10000) / (1024 - adc_value); // R����������ֵ=ADC7Value*10000/(1024-ADC7Value)
// 		temperature = calculate_temperature(R);
// 		send_temperature(temperature);
// 		UARTSend("����������ֵ��", 14); // �س�����
// 		send_resistance(R);
// 		UARTSend("\r\n", 2);  // ��ӻس�����
//      }
//  }

// /******************************************************************
//  * ������: UARTInit
//  * ����: ��ʼ�� UART0 �˿ڣ�����ѡ�����š�ʱ�ӣ�У�顢ֹͣλ��FIFO���ȵȡ�
//  * ����: UART ������
//  * ����ֵ: ��
// ******************************************************************/
//  void UARTInit(uint32_t baudrate)
//  {
//  	uint32_t Fdiv; // ��Ƶֵ
//  	uint32_t regVal = regVal; // ��ʱ����
//  	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);  // ʹ�� IOCON ģ���ʱ��
//  	LPC_IOCON->PIO1_6 &= ~0x07;  // UART I/O ���ã����� PIO1_6 Ϊ UART RXD 
//  	LPC_IOCON->PIO1_6 |= 0x01; 
//  	LPC_IOCON->PIO1_7 &= ~0x07; // ���� PIO1_7 Ϊ UART TXD 
//  	LPC_IOCON->PIO1_7 |= 0x01; 
//  	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 16); // �ر� IOCON ģ���ʱ��
//  	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12); // ʹ�� UART ʱ��
//  	LPC_SYSCON->UARTCLKDIV = 0x1; // ��Ƶֵ 1
//  	LPC_UART->LCR = 0x83; // ���� UART �߿��ƼĴ��� (LCR)������Ϊ 8 λ���ݣ���У��λ��1 ֹͣλ 	
//  	Fdiv = (SystemCoreClock / 16) / baudrate; // ���㲨���ʷ�Ƶֵ
//  	LPC_UART->DLM = Fdiv / 256; // ���ò����ʵ��ֽں͸��ֽ�
//  	LPC_UART->DLL = Fdiv % 256; 
//  	LPC_UART->LCR = 0x03; // ���� LCR������ DLAB 
//  	LPC_UART->FCR = 0x07; // ʹ�ܲ���λ TX �� RX FIFO	
//  	regVal = LPC_UART->LSR; // ��ȡ�������״̬�Ĵ��� (LSR)
//  	// ȷ��������ʼ��TX �� RX FIFO ��û������
//  	while ((LPC_UART->LSR & (0x20 | 0x40)) != (0x20 | 0x40));
//  	while (LPC_UART->LSR & 0x01)
//  	{
//  		regVal = LPC_UART->RBR; // �� RX FIFO ��ת������
//  	}
//  }

// /******************************************************************
//  * ������: UARTSend
//  * ����: �������ݳ��ȷ���һ�����ݵ� UART 0 �˿ڡ�
//  * ����: buffer pointer, and data length
//  * ����ֵ: ��
// ******************************************************************/
//  void UARTSend(uint8_t *BufferPtr, uint32_t Length)
//  {
//  	while (Length != 0) // �ж����ݳ��ȣ���Ϊ0��������
//  	{
//  		while (!(LPC_UART->LSR & (1 << 5))); // �ȴ�ֱ���������ݼĴ�����
//  		LPC_UART->THR = *BufferPtr; // ���͵�ǰ�ֽ�
//  		BufferPtr++; // �ƶ�����һ���ֽ�
//  		Length--; // �ݼ����ݳ���
//  	}
//  }

// /******************************************************************
//  * ������: ��ʱ����
//  * ����: ���뼶��ʱ������
//  * ����: ��ʱʱ��
// ******************************************************************/
//  void delay_ms(uint32_t a) // 1ms��ʱ����
//  {
// 	 uint32_t i;	  // ѭ������
// 	 while (--a != 0) // ֱ����ʱʱ��Ϊ��
// 	 {
// 		 for (i = 0; i < 5500; i++); // ��Լ��ʱ��ѭ��1ms
// 	 }
//  }

// /******************************************************************
//  * ������: ADC7_Init
//  * ����: ADC7 ��ʼ������������ ADC ���ƼĴ�����ʹ�� ADC ��Դ��ʱ�ӡ�
//  * ����: ��
// ******************************************************************/
//void ADC7_Init(void)
//{
//    LPC_SYSCON->PDRUNCFG &= ~(1UL << 4);		// ʹ��ADC��Դ
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 13);   // ʹ��ADCʱ�ӣ��Ա�ADC�ܹ�����ת��
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);   // ʹ��IOCONģ��ʱ�ӣ���������Ӧ������
//    LPC_IOCON->PIO1_11 &= ~(0x01 << 7);       // ���P1.11�Ĺ������ã�Ϊ����AD7��׼��
//    LPC_IOCON->PIO1_11 |= 0x01;                // ��P1.11����ΪADC����ͨ��AD7
//    LPC_IOCON->PIO1_11 &= ~(3 << 3);           // �����صĹ������ã�ȷ�����������ܸ���
//    LPC_IOCON->PIO1_11 &= ~(1 << 7);           // �ٴ������������ص���������
//    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 16);  	// �ر�IOCONģ���ʱ�ӣ���ʡ����

//    // ����ADC���ƼĴ�����CR��
//    LPC_ADC->CR = (1UL << 7) |        // ʹ��AD7ͨ�����Ա��ȡ��ͨ���ĵ�ѹ
//                  (23UL << 8) |       // ����ADCʱ�ӣ�����Ϊ2MHz��ʵ��ADC����Ϊ48MHzʱ��ʹ�÷�Ƶ50/(24+1)��
//                  (0 << 16) |        // ѡ���������ģʽ������ADCת��
//                  (0 << 17) |        // ����ת��ʱ��Ϊ11ʱ�����ڣ�ȷ��10λ��Ч����
//                  (0 << 24) |        // �ر�ADCת�����ȵ�32λ��ʱ��0��ƥ���¼���������
//                  (0 << 27);         // Ԥ������Ч���ã���Ӱ�칦��
//                  
//    LPC_ADC->INTEN = (1UL << 8);       // ʹ��AD7ͨ�����жϣ�������ADCת�����ʱ�����ж�
//    NVIC_EnableIRQ(ADC_IRQn);          // ����ADC�жϣ������жϿ�������ӦADCת������¼�
//}

// /******************************************************************
//  * ������: Read_AD7
//  * ����: ��ȡ�˿�ADC7��ֵ��
//  * ����ֵ: ���ص�ѹֵADC_Data
// ******************************************************************/
// uint32_t Read_AD7(void)
// {
// 	uint32_t ADC_Data;
// 	LPC_ADC->CR|=(1<<24);			//����ADC
// 	while((LPC_ADC->DR[7]&0x80000000)==0);
// 	LPC_ADC->CR|=(1<<24);			//ʹ�õڶ���ת����������һ��
// 	while((LPC_ADC->DR[7]&0x80000000)==0);
// 	ADC_Data=LPC_ADC->DR[7];			//	��ȡADC7�Ĵ�����ֵ
// 	ADC_Data=(ADC_Data>>6)&0x3ff;	//��ȡ10λAD���
// 	return(ADC_Data);
// }

// /******************************************************************
//  * ������: TMR32B0_Init
//  * ����:��ʼ��32λ��ʱ��0��������ʱ��ƥ���жϡ�
// ******************************************************************/
// void TMR32B0_Init(void) {
//     LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 9); // ʹ�ܶ�ʱ��0ʱ��
// 	LPC_TMR32B0->IR = 0x1F; // ��������жϱ�־
//     LPC_TMR32B0->PR = 0; // ����Ƶ
// 	LPC_TMR32B0->MCR = 3; // ��ƥ��MR0ʱ�����ö�ʱ���Ͳ����ж�
//     LPC_TMR32B0->MR0 = SystemCoreClock - 1; // ����ƥ��Ĵ���Ϊϵͳʱ��Ƶ�� - 1 (1��)
//     LPC_TMR32B0->TCR = 0x01; // ������ʱ��
// 	NVIC_EnableIRQ(TIMER_32_0_IRQn); // ʹ�ܶ�ʱ��0�ж�
// }

// /******************************************************************
//  * ������: send_resistance
//  * ����:���͵���ֵ������
//  * ����: resistance������ֵ
// ******************************************************************/
// void send_resistance(double resistance) {
//    char res_str[32];  // ���ڴ洢ת������ַ�������֤�㹻�������ɸ������ͱ�ʶ��
//    sprintf(res_str, "%.2f ��\r\n", resistance); // ��ʽ���ַ�����������λС��
//    // ͨ�� UART �����ַ���
//    UARTSend((uint8_t *)res_str, strlen(res_str));  // ���͵����ַ���
//}

//  /******************************************************************
//  * ������: calculate_temperature
//  * ����:���¶ȵ�����ֵת��Ϊ�¶�ֵ���϶�
//  * ����: resistance������ֵ
// ******************************************************************/
// double calculate_temperature(double resistance) {
//   // 3950��NTC��Bֵ��298.15��25��C�ľ����¶ȣ�K��
//   temperature = (1 / (log(resistance / R_REFERENCE) / 3950 + (1 / 298.15))) - 273.15; // ����ֵת��Ϊ�¶ȣ����϶�
//   return temperature; // �����¶�ֵ�����϶ȣ�
// }

// /******************************************************************
//  * ������: send_temperature
//  * ����:�����¶�ֵ�����ڣ����϶ȣ�
//  * ����: temperature�¶�ֵ
// ******************************************************************/
// void send_temperature(float temperature) {
//     char temp_str[16];  // ���ڴ洢ת������ַ���
//     sprintf(temp_str, "%.2f", temperature); // ��������ת��Ϊ�ַ�����������λС��
//     // �����ַ���������
//     UARTSend((uint8_t *)temp_str, strlen(temp_str));  // �����¶��ַ���
//     UARTSend((uint8_t *)"���϶�\r\n", 8);  // ��ӻس�����
// }
// 
// 
///*���Ĵ���ҵ*/ 
// 
// // LED ��ʼ������
//void LED_init(void) 
//{
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // ʹ�� GPIO ģ���ʱ��
//    LPC_GPIO1->DIR |= (1UL << 9); // ���� GPIO1.9 Ϊ���ģʽ
//    LPC_GPIO1->DATA &= ~(1UL << 9); // �� GPIO1.9 ��ʼ��Ϊ�͵�ƽ������ LED��
//}

//// LED ��˸����
//void LED_Toggle(void) 
//{
//    LPC_GPIO1->DATA ^= (1UL << 9); // ͨ����������ת GPIO1.9 �������ƽ
//}

//// 16 λ��ʱ����ʼ������
//void TMR16B1_Init(void) 
//{
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8); // ʹ�� 16 λ��ʱ����ʱ��
//    LPC_TMR16B1->IR = 0x1F; // ������ж�ʱ���жϱ�־
//    LPC_TMR16B1->PR = 1000 - 1; // ���ö�ʱ����Ƶϵ��Ϊ 1000��ʵ�ʷ�ƵΪ 1000
//    LPC_TMR16B1->MCR = 3; // ���ã�ƥ���λ TC �������ж�
//    LPC_TMR16B1->MR0 = SystemCoreClock / 1000; // ����ƥ��Ĵ�����ʹ��ʱ��ÿ 1ms ����һ��ƥ��
//    LPC_TMR16B1->TCR = 0x01; // ������ʱ��
//    NVIC_EnableIRQ(TIMER_16_1_IRQn); // ʹ�� 16 λ��ʱ��1���ж�
//}

//// ��ʱ���жϴ�����
//void TIMER16_1_IRQHandler(void) 
//{
//    // ��鶨ʱ��ƥ���ж�
//    if ((LPC_TMR16B1->IR & 0x01) == 1) // ʹ�ð�λ���������Ƿ�Ϊƥ���ж�
//    {
//        LED_Toggle(); // ���� LED ��˸����
//        LPC_TMR16B1->IR |= 0x01; // ���ƥ���жϱ�־
//    }
//}

//// 16 λ��ʱ����ʼ������
//void TMR16B1_COUNT_Init(void) 
//{
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8) | (1UL << 16); // ʹ�� 16 λ��ʱ���� IOCON ��ʱ��
//    LPC_IOCON->PIO1_9 |= 0x01; // ����PIO1.9
//    LPC_TMR16B1->PWMC = 0x00; // ��� PWM ƥ��Ĵ�����־
//    LPC_TMR16B1->PR = 1000 - 1; // ���ö�ʱ����Ƶϵ��Ϊ 1000
//    LPC_TMR16B1->MCR = 3; // ����ƥ���λ TC �������ж�
//    LPC_TMR16B1->MR0 = SystemCoreClock / 1000; // ��ƥ��Ĵ��� MR0 ����Ϊ 1ms
//    LPC_TMR16B1->TCR = 0x01; // ʹ�� 16 λ��ʱ��
//    LPC_TMR16B1->EMR |= (3UL << 4); // ���� PWM ���ģʽ
//}


//#define MAX_BRIGHTNESS  100 // ������ȣ�ռ�ձ�100%��
//#define MIN_BRIGHTNESS  0   // ��С���ȣ�ռ�ձ�0%��
//#define BRIGHTNESS_STEP 1   // ��������������1%��

///* ��ʼ�� LED �� */
//void InitializeLED(void)   
//{
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // ʹ�� GPIO ʱ��
//    LPC_GPIO1->DIR |= (1UL << 9); // ���� PIO1_9 Ϊ���
//}

///* ��ʼ�� 16 λ��ʱ��1Ϊ PWM ģʽ */
//void InitPWM16BitTimer(void)  
//{
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8) | (1UL << 16); // ʹ�� 16 λ��ʱ��1 �� IOCON ��ʱ��
//    LPC_IOCON->PIO1_9 |= 0x01;  // �� PIO1_9 ����Ϊ MAT0��PWM ���ܣ�
//    LPC_TMR16B1->TCR = 0x02;  // ��λ 16 λ��ʱ��1
//    LPC_TMR16B1->PR = 0;  // �޷�Ƶ, ����Ϊ 1
//    LPC_TMR16B1->PWMC = 0x01;  // ���� MAT0 Ϊ PWM ģʽ
//    LPC_TMR16B1->MCR = (0x02 << 9);  // ����ƥ��� TC ��λ�Ҳ��ж�
//    LPC_TMR16B1->MR3 = SystemCoreClock / 1000;  // ���� MR3 Ϊ 1ms
//    LPC_TMR16B1->MR0 = LPC_TMR16B1->MR3; // MR0 ���� PWM ���
//    LPC_TMR16B1->TCR = 0x01;  // ʹ�� 16 λ��ʱ��1
//}

///* ��ʼ�� 32 λ��ʱ��0 */
//void Init32BitTimer(void)  
//{  
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 9); // ʹ�� 32 λ��ʱ��0 ʱ��
//    LPC_TMR32B0->IR = 0x1F; // ��������жϱ�־
//    LPC_TMR32B0->PR = 0; // �޷�Ƶ, ����Ϊ 1
//    LPC_TMR32B0->MCR = 3; // ƥ���λ TC �������ж�
//    LPC_TMR32B0->MR0 = SystemCoreClock / 100; // ���� MR0 �Բ��� 0.01s �ж�
//    LPC_TMR32B0->TCR = 0x01; // ʹ�� 32 λ��ʱ��0
//    NVIC_EnableIRQ(TIMER_32_0_IRQn); // ע�Ტʹ�� 32 λ��ʱ��0 �ж�
//}

//volatile uint8_t brightnessLevel = 0; // ��ǰ���ȼ���
//volatile uint8_t isIncreasing = 1; // ָʾռ�ձ��Ƿ�������

///* 32 λ��ʱ��0���жϷ������ */
//void TIMER32_0_IRQHandler(void)
//{
//    LPC_TMR32B0->IR = 0x1F; // ��������жϱ�־

//    // ���� PWM ռ�ձ�
//    if (isIncreasing) {
//        brightnessLevel += BRIGHTNESS_STEP; // ��������
//        if (brightnessLevel >= MAX_BRIGHTNESS) {
//            brightnessLevel = MAX_BRIGHTNESS; // �ﵽ���ֵ
//            isIncreasing = 0; // �л�Ϊ��С����
//        }
//    } else {
//        brightnessLevel -= BRIGHTNESS_STEP; // ��С����
//        if (brightnessLevel <= MIN_BRIGHTNESS) {
//            brightnessLevel = MIN_BRIGHTNESS; // �ﵽ��Сֵ
//            isIncreasing = 1; // �л�Ϊ��������
//        }
//    }
//    
//    LPC_TMR16B1->MR0 = (brightnessLevel * LPC_TMR16B1->MR3) / 100; // ���� PWM ���
//}




//// ��������ҵ
//#define DEBOUNCE_TIME 50 // ����ʱ�䣬��λ�Ǻ���
//#define FREQUENCY_0_5HZ (2000/2) // 0.5Hz ��Ӧ�����ڣ����룩,����2��ʾ�������ʱ���ռһ��
//#define FREQUENCY_1HZ (1000/2) // 1Hz ��Ӧ�����ڣ����룩,����2��ʾ�������ʱ���ռһ��
//#define FREQUENCY_2HZ (500/2) // 2Hz ��Ӧ�����ڣ����룩,����2��ʾ�������ʱ���ռһ��
//volatile uint8_t ledState = 0; // LED ״̬������0: �أ�1: ��
//int blinkFrequency = FREQUENCY_0_5HZ; // Ĭ����˸Ƶ��Ϊ 0.5Hz
// 
///* ��תRGB_Blue���� */
//void RGB_Blue_Toggle(void)
//{
//LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); /* GPIO ʱ��ʹ�� */
//LPC_GPIO2->DIR |= (1UL << 10); /*����GPIO2_10Ϊ���ģʽ */
//LPC_GPIO2->DATA  ^=  (1UL <<10); /* LED ��˸�л� */
//}
///* ��תRGB_Green�̵� */
//void RGB_Green_Toggle(void)
//{
//LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); /* GPIO ʱ��ʹ�� */
//LPC_GPIO2->DIR |= (1UL << 8); /*����GPIO2_8Ϊ���ģʽ */
//LPC_GPIO2->DATA ^= (1UL <<8);/* LED ��˸�л� */
//}
//void Key_Init(void) {
//    // ʹ�� IOCON ���ʱ��
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 16); /* IOCON ʱ��ʹ�� */
//    // ���� PIO3_5 Ϊ GPIO ����
//    LPC_IOCON->PIO3_5 &= ~0x3F; 
//    LPC_IOCON->PIO3_5 |= (1 << 4 | 1 << 5); // ���� P3.5 Ϊ GPIO ���ܣ��������裬ʹ���ͺ�ģʽ
//    LPC_GPIO3->DIR &= ~(1UL << 5); // �� P3.5 ����Ϊ���루������
//    // ���� PIO1_4 Ϊ GPIO ����
//    LPC_IOCON->PIO1_4 &= ~0x3F; 
//    LPC_IOCON->PIO1_4 |= (1 << 4 | 1 << 5); // ���� P1.4 Ϊ GPIO ���ܣ��������裬ʹ���ͺ�ģʽ
//    LPC_GPIO1->DIR &= ~(1UL << 4); // �� P1.4 ����Ϊ���루������
//    // GPIO3 �жϳ�ʼ��
//    LPC_GPIO3->IS &= ~(1UL << 5); // ��� P3.5 �ж�״̬ѡ������Ϊ��Ե������
//    LPC_GPIO3->IBE &= ~(1UL << 5); // ����˫���ش���
//    LPC_GPIO3->IEV &= ~(1UL << 5); /* ����Ϊ�½��ش��� */
//    LPC_GPIO3->IE |= (1UL << 5); /* ʹ�� GPIO3 �� P3.5 �жϹ��� */
//    NVIC_EnableIRQ(EINT3_IRQn); /* ʹ�� EINT3 �ж� */
//    NVIC_SetPriority(EINT3_IRQn, 1); // ���� EINT3 �ж����ȼ�Ϊ 1
//    // GPIO1 �жϳ�ʼ��
//    LPC_GPIO1->IS &= ~(1UL << 4); // ��� P1.4 �ж�״̬ѡ������Ϊ��Ե������
//    LPC_GPIO1->IBE &= ~(1UL << 4); // ����˫���ش���
//    LPC_GPIO1->IEV &= ~(1UL << 4); /* ����Ϊ�½��ش��� */
//    LPC_GPIO1->IE |= (1UL << 4); /* ʹ�� GPIO1 �� P1.4 �жϹ��� */
//    NVIC_EnableIRQ(EINT1_IRQn); /* ʹ�� EINT1 �ж� */
//    NVIC_SetPriority(EINT1_IRQn, 2); // ���� EINT1 �ж����ȼ�Ϊ 2
//}
//void PIOINT3_IRQHandler(void)
//{
//    RGB_Blue_Toggle(); // ��ת RGB_Blue ���ƣ�����ָʾ�Ƿ������ GPIO3 �ж�
//    uint32_t regVal = 0; // ����������ڴ洢����״̬
//    // ��� PIO3_5���������Ƿ񱻰���
//    if ((LPC_GPIO3->DATA & (1 << 5)) == 0) 
//    {
//        delay_ms(DEBOUNCE_TIME); // ����������ʱ���������ⶶ��Ӱ��
//        // �ȴ������ͷ�
//        while ((LPC_GPIO3->DATA & (1 << 5)) == 0); 
//        
//        // ����ж�״̬�Ĵ�����ȷ���Ƿ�����Ч�İ����¼�
//        if (LPC_GPIO3->MIS & (0x1 << 5)) 
//        {
//            regVal = 1; // ���ñ�־����ʾ��������Ч����
//        }
//    }
//    
//    // �����Ч�����¼�����⵽
//    if (regVal)
//    {
//        // �л���˸Ƶ��
//        if (blinkFrequency == FREQUENCY_0_5HZ) {
//            blinkFrequency = FREQUENCY_1HZ; // ��Ϊ 1Hz
//        } 
//        else if (blinkFrequency == FREQUENCY_1HZ) {
//            blinkFrequency = FREQUENCY_0_5HZ; // �ָ�Ϊ 0.5Hz
//        } 
//        else {
//            blinkFrequency = FREQUENCY_0_5HZ; // ��Ϊ 2Hz ʱ�Զ��ָ�Ϊ 0.5Hz
//        }
//    }
//    // ��� GPIO3 ���жϱ�־���Ա������Ӧ��һ���ж�
//    LPC_GPIO3->IC |= (0x1 << 5);
//}
//void PIOINT1_IRQHandler(void)
//{
//    RGB_Green_Toggle(); // ��ת RGB_Green �̵ƣ�����ָʾ�Ƿ������ GPIO1 �ж�
//    uint32_t regVal = 0; // ����������ڴ洢����״̬
//    // ��� PIO1_4��WEAKUP �������Ƿ񱻰���
//    if ((LPC_GPIO1->DATA & (1 << 4)) == 0) 
//    {
//        delay_ms(DEBOUNCE_TIME); // ����������ʱ������ȥ�����е������������Ķ�δ���
//        // �ȴ������ͷ�
//        while ((LPC_GPIO1->DATA & (1 << 4)) == 0); 
//        
//        // ����ж�״̬�Ĵ�����ȷ���Ƿ�����Ч�İ����¼�
//        if (LPC_GPIO1->MIS & (0x1 << 4)) 
//        {
//            regVal = 1; // ���ñ�־����ʾ��������Ч����
//        }
//    }
//    
//    // �����Ч�����¼�����⵽
//    if (regVal)
//    {
//        // �л���˸Ƶ��
//        if (blinkFrequency == FREQUENCY_0_5HZ) {
//            blinkFrequency = FREQUENCY_2HZ; // ����˸Ƶ�ʸ�Ϊ 2Hz
//        } 
//        else if (blinkFrequency == FREQUENCY_2HZ) {
//            blinkFrequency = FREQUENCY_0_5HZ; // �ָ��� 0.5Hz
//        } 
//        else {
//            blinkFrequency = FREQUENCY_0_5HZ; // ��Ϊ 1Hz ʱ�Զ��ָ�Ϊ 0.5Hz
//        }
//    }
//    // ��� GPIO1 ���жϱ�־���Ա������Ӧ��һ���ж�
//    LPC_GPIO1->IC |= (0x1 << 4);
//}
//// SysTick �жϴ�����
//void SysTick_Handler(void) {
//    static uint32_t ledCounter = 0; // LED ������
//    ledCounter++;
//    if (ledCounter >= blinkFrequency) { // ��������ﵽ���õ�Ƶ��
//     LED_Toggle(); // ��תGPIO1_9���ı�Ƶ�״̬
//        ledCounter = 0; // ���ü�����
//    }
//}
//int main (void) {
//    /* ����ϵͳ���Ķ�ʱ����ÿ1ms����һ��ϵͳ�����ж� */
//    SysTick_Config(SystemCoreClock / 1000);  /* ��ʱ����1msΪ�����ж�һ�� */
//    LED_Init();  /* ��ʼ��LED */
//   Key_Init();  /* ��ʼ��Key */
//    while (1) 
//{ 
//    }
//}
