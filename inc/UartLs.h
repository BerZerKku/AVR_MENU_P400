/** ������� ������ � UART ��������� ����.
 *  
 *  ������ ������� �� UART1.    
 */
#ifndef UART_LS_H_
#define UART_LS_H_

#include <stdint.h>
#include "MyDef.h"   

// ����� ����������� �� UART ������.
extern unsigned char UARTLS_rxBuf[]; 

// ����� ������������ �� UART ������.
extern unsigned char UARTLS_txBuf[]; 

// �������� ������� ��������� ���������.
extern bool UARTLS_isRxData(void);

// ���������� ���������� �������� ���� ������.
extern uint8_t UARTLS_getDataLen(void);

// ������ ������ ��������� UART.
extern void UARTLS_rxStart(void);

// ��������� UART.
extern void UARTLS_setup(void);

// ������� ����� ����� ��������� �������.
extern void UARTLS_tick(void);

// ����� �������� ������.
extern void UARTLS_txStart(uint8_t len);

#endif