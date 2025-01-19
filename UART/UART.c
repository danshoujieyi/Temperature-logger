#include "UART.h"
#include <stdio.h>
/******************************************************************
 * ������: UARTInit
 * ����: ��ʼ�� UART0 �˿ڣ�����ѡ�����š�ʱ�ӣ�У�顢ֹͣλ��FIFO���ȵȡ�
 * ����: UART ������
 * ����ֵ: ��
******************************************************************/
  void UART_Init(uint32_t baudrate)
  {
  	uint32_t Fdiv; // ��Ƶֵ
  	uint32_t regVal = regVal; // ��ʱ����
  	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);  // ʹ�� IOCON ģ���ʱ��
  	LPC_IOCON->PIO1_6 &= ~0x07;  // UART I/O ���ã����� PIO1_6 Ϊ UART RXD 
  	LPC_IOCON->PIO1_6 |= 0x01; 
  	LPC_IOCON->PIO1_7 &= ~0x07; // ���� PIO1_7 Ϊ UART TXD 
  	LPC_IOCON->PIO1_7 |= 0x01; 
  	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 16); // �ر� IOCON ģ���ʱ��
  	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12); // ʹ�� UART ʱ��
  	LPC_SYSCON->UARTCLKDIV = 0x1; // ��Ƶֵ 1
  	LPC_UART->LCR = 0x83; // ���� UART �߿��ƼĴ��� (LCR)������Ϊ 8 λ���ݣ���У��λ��1 ֹͣλ 	
  	Fdiv = (SystemCoreClock / 16) / baudrate; // ���㲨���ʷ�Ƶֵ
  	LPC_UART->DLM = Fdiv / 256; // ���ò����ʵ��ֽں͸��ֽ�
  	LPC_UART->DLL = Fdiv % 256; 
  	LPC_UART->LCR = 0x03; // ���� LCR������ DLAB 
  	LPC_UART->FCR = 0x07; // ʹ�ܲ���λ TX �� RX FIFO	
  	regVal = LPC_UART->LSR; // ��ȡ�������״̬�Ĵ��� (LSR)
  	// ȷ��������ʼ��TX �� RX FIFO ��û������
  	while ((LPC_UART->LSR & (0x20 | 0x40)) != (0x20 | 0x40));
  	while (LPC_UART->LSR & 0x01)
  	{
  		regVal = LPC_UART->RBR; // �� RX FIFO ��ת������
  	}
	LPC_UART->IER |=1<<0; //ʹ�ܽ����ж�
    NVIC_EnableIRQ(UART_IRQn); //�����ж�
  }


/************************************************/
/* �������ܣ����ڽ����ֽ�����  */
/************************************************/
uint8_t UART_Recive(void)
{  
  while(!(LPC_UART->LSR & (1<<0)));   //�ȴ����յ�����
  return(LPC_UART->RBR);   //��������
}

/************************************************/
/* �������ܣ����ڷ����ֽ�����  */
/************************************************/
void UART_Send_Byte(uint8_t byte)
{
    LPC_UART->THR = byte;
  while ( !(LPC_UART->LSR & (1<<5)) );//�ȴ�������

}

/******************************************************************
 * ������: UARTSend
 * ����: �������ݳ��ȷ���һ�����ݵ� UART 0 �˿ڡ�
 * ����: buffer pointer, and data length
 * ����ֵ: ��
******************************************************************/
 void UART_Send(uint8_t *BufferPtr, uint32_t Length)
 {
 	while (Length != 0) // �ж����ݳ��ȣ���Ϊ0��������
 	{
 		while (!(LPC_UART->LSR & (1 << 5))); // �ȴ�ֱ���������ݼĴ�����
 		LPC_UART->THR = *BufferPtr; // ���͵�ǰ�ֽ�
 		BufferPtr++; // �ƶ�����һ���ֽ�
 		Length--; // �ݼ����ݳ���
 	}
 }
 
 /**
  * ��    ����ʹ��printf��Ҫ�ض���ĵײ㺯��
  * ��    ��������ԭʼ��ʽ���ɣ�����䶯
  * �� �� ֵ������ԭʼ��ʽ���ɣ�����䶯
  */
int fputc(int ch, FILE *f)
{
	UART_Send_Byte(ch);			//��printf�ĵײ��ض����Լ��ķ����ֽں���
	return ch;
}


