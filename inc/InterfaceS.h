//���������� ������ � UART
#ifndef __MY_DEF
 #include "MyDef.h"
#endif
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


//����� �������� ������
void ClearPortError1(void);

//����� ��������� UART
char GetSostPort1(void);

//��������� �������� �� ������
void StartTrans1(char SizeMessage);

//����� UART
void StartUART1(void);

extern unsigned char Rec_buf_data_uart1 [MaxLenghtRecBuf] ; //����� ����������� ������
extern unsigned char Tr_buf_data_uart1 [MaxLenghtTrBuf1] ; //����� ������������ ������
extern char Sost1;
//extern unsigned char DataRec; //=1, ����� �������� ���������

extern unsigned char PCready;
extern unsigned char PCbyte;
extern unsigned char PCtime;

extern bool bUartRcReady1; //true - ������� �������, ���� ����������
extern unsigned char cNumRecByte;  //���-�� �������� ����

