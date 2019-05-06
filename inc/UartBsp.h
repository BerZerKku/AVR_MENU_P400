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

extern unsigned char PCready;
extern unsigned char PCbyte;
extern unsigned char PCtime;

extern bool uart0rxReady; //true - ������� �������, ���� ����������
extern unsigned char cNumRecByte;  //���-�� �������� ����

#endif
