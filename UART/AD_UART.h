//#ifndef __AD_UART_H__
//#define __AD_UART_H__

//// #include "LPC11xx.h"   
//// #include <math.h> // ���ڼ���log�������Բ�ֵ������������¶�ֵ
//// #include <stdio.h>  // ����sprintf
//// #include <string.h> // ����strlen

//// �Զ��庯��ͷ�����ܼ򵥽���
//// �������ҵ
//void UARTInit(uint32_t baudrate); //  ��ʼ�� UART�����ò������Լ���ؼĴ������á�
//void UARTSend(uint8_t *BufferPtr, uint32_t Length); //  ����ָ�����ȵ������� UART��ȷ�����ݵ�˳��������ԡ�
//void delay_ms(uint32_t a); //  ʵ�ֺ��뼶��ʱ�����ڿ���ʱ������
//void ADC7_Init(void); //  ���� ADC7 ͨ��������������ã�ȷ�� ADC ���Գɹ�����ģ���źŶ�ȡ��
//uint32_t Read_AD7(void); //  ��ȡ ADC7 �ĵ�ǰ����������10λ�����ֻ����������ʹ��ADC7���ж϶�ȡ��û��ʹ�����ֱ�Ӷ�ȡ����
//void TMR32B0_Init(void); //  ����32λ��ʱ��0��ƥ���ж����ü��жϣ�ʹ�ܶ�ʱ�����ڶ�ʱ�¼���
//void TIMER32_0_IRQHandler(void); //  ����ʱ��0�жϣ�ִ����Ӧ��������������ADCת����
//void send_resistance(double resistance); //  ��������ĵ���ֵͨ�� UART ���͵����ڼ�ء�
//double calculate_temperature(double resistance); //  ʹ�õ���ֵ�����¶ȣ��������϶�ֵ��
//void send_temperature(float temperature); //  ���¶�ֵͨ�� UART ���ͣ��Ա�ʵʱ��ء�
//void ADC_IRQHandler(void); //  �� ADC ת�����ʱ��ȡֵ���������������������ֵ�����ڡ�

//// ���Ĵ���ҵ
//void LED_Toggle(void); // LED ��˸����
//void TMR16B1_Init(void); // 16 λ��ʱ����ʼ������
//void TIMER16_1_IRQHandler(void); // ��ʱ���жϴ�����
//void TMR16B1_COUNT_Init(void); // 16 λ��ʱ����ʼ������

//// ��������ҵ
//void RGB_Blue_Toggle(void); /* ��תRGB_Blue���� */
//void RGB_Green_Toggle(void); /* ��תRGB_Green�̵� */
//void Key_Init(void);
//void PIOINT3_IRQHandler(void);
//void PIOINT1_IRQHandler(void);
//void SysTick_Handler(void); // SysTick �жϴ�����

//#endif 
