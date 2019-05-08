/** ������� ������ � UART ���.
 *  
 *  ������ ������� �� UART0.    
 */
#ifndef UART_BSP_H_
#define UART_BSP_H_

#include <stdint.h>
#include "MyDef.h"

//����� �������� ������
void ClearPortError(void);

//����� ��������� UART
char GetSostPort(void);

//��������� �������� �� ������
void StartTrans(char SizeMessage);

//����� UART
void StartUART(void);

extern unsigned char Rec_buf_data_uart [MaxLenghtRecBuf] ; //����� ����������� ������
extern unsigned char Tr_buf_data_uart [MaxLenghtTrBuf] ; //����� ������������ ������
extern char Sost;
//extern unsigned char DataRec; //=1, ����� �������� ���������

extern bool uart0rxReady; //true - ������� �������, ���� ����������
extern unsigned char cNumRecByte;  //���-�� �������� ����

//// ����� ����������� �� UART ������.
//extern unsigned char UARTBSP_rxBuf[]; 
//
//// ����� ������������ �� UART ������.
//extern unsigned char UARTBSP_txBuf[]; 
//
//// �������� ������� ��������� ���������.
//extern bool UARTBSP_isRxData(void);
//
//// ���������� ���������� �������� ���� ������.
//extern uint8_t UARTBSP_getDataLen(void);
//
//// ������ ������ ��������� UART.
//extern void UARTBSP_rxStart(void);

// ��������� UART.
extern void UARTBSP_setup(void);

//// ������� ����� ����� ��������� �������.
//extern void UARTBSP_tick(void);
//
//// ����� �������� ������.
//extern void UARTBSP_txStart(uint8_t len);

#endif
