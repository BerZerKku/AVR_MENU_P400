#include <ioavr.h>
#include <ina90.h>


#include "UartBsp.h"
#include "DataCenter.h"
#include "DataCenter1.h"
#include "UartLs.h"


char Sost=0;  //���������� ��������� �������� ������� ������� �� ������

unsigned char Rec_buf_data_uart [MaxLenghtRecBuf] ; //����� ����������� ������
unsigned char Tr_buf_data_uart [MaxLenghtTrBuf] ; //����� ������������ ������

unsigned char RecByteCounter=0; //������� �������� ����
signed char TrByteCounter=0;  //������� ������������ ������
signed char NumberTransByte=0; //���-�� ������������ ������
unsigned char DataPause=0x00; //���������� ����� ����� ��������� �������
unsigned char StartRec=0;   //��������� ����� ���������
uint8_t cCurrLen0=0;  //������� �������� ����
uint8_t cMaxLen0=0; //���-�� ��������� ���� � �������



/// ���� ������� �������� ������� (true) ���������� �� UART0.
bool uart0rxReady = false; 
unsigned char cNumRecByte = 0; //��-�� �������� ����

/// ������������� � ������ ������ ����������������� UART0.
void UARTBSP_setup(void) {
    UBRR0L=207;

    // PI_RXD
    DDRE  &= ~(1 << PORTE0);
    PORTE &= ~(1 << PORTE0);
    
    // PI_TXD
    DDRE  |= (1 << PORTE1);
    PORTE |= (1 << PORTE1);
    
    // ��� ����-���� � ������ ������� 8 ��������
    UCSR0C = (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);
    
    // ����� ������ ��������� � �����������
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    EnableReceive;
    
    Tr_buf_data_uart[0]=0x55;
    Tr_buf_data_uart[1]=0xAA;
    Rec_buf_data_uart[0]=0x55;
    Rec_buf_data_uart[1]=0xAA;
}


#pragma vector=USART0_RXC_vect //����� ���������� ������ UART
__interrupt void UART_RX_interrupt(void){
    uint8_t tmp = UDR0;
    
    //FE-������ �����, OVR - ������������ ������ (�����)
    if  (UCSR0A & (1 << FE0)) {
        cCurrLen0 = 0;
    } else {           
        switch (cCurrLen0){
            //�������� 1-��� �����������
            case 0: if (tmp == 0x55) cCurrLen0 = 1; break;
            //�������� 2-��� �����������
            case 1: if (tmp == 0xAA) cCurrLen0 = 2; else cCurrLen0 = 0; break;
            //���� �������
            case 2: {
                Rec_buf_data_uart[2] = tmp;
                cCurrLen0 = 3;
            }break;
            //���-�� ���� ������
            case 3:{
                Rec_buf_data_uart[3]=tmp;
                if (tmp > (MaxLenghtRecBuf - 5)) cCurrLen0 = 0;  //�������� �� ���� ���-�� ������
                else cCurrLen0 = 4;
                cMaxLen0 = cCurrLen0 + tmp; //���-�� ����������� ������
            }break;
            default:{//������ � ��
                Rec_buf_data_uart[cCurrLen0] = tmp;
                if (cCurrLen0 >= cMaxLen0){
                    uart0rxReady = true; // ������� ���
                    cCurrLen0=0;
                    DisableReceive;  //��������� �����
                    cNumRecByte = cMaxLen0 + 1;
                }else cCurrLen0++;
            }
        }
    }
}


#pragma vector=USART0_UDRE_vect //����� ���������� �������� � ����� UART
__interrupt void UART_UDRE_interrupt(void){
//  char temp_tr;
  if (TrByteCounter<NumberTransByte)   //���� �� ��� �������� �� ��� �����, �� ���������� ����������
    {
      UDR0=Tr_buf_data_uart[TrByteCounter];
      ++TrByteCounter;
    }
  else    //���� �� �� ��� ��������, �� ������������� �������� � ���������� ������������ ����������
    {
      StopTrans;
      NumberTransByte=0;
      TrByteCounter=0;
      EnableReceive;
      Sost&=~(CurSost);
    }
}

//���������� �������� �� UART, � ��������� ��-�� ������������ ������
void StartTrans(char SizeMessage)
{
#if ( (DEB) && (PK) )	// ��������� ��������� ��� ��� �� ��
	#warning �������� ��������� ��������� ��� ��� �� ��!!!  
	if ((ALT) ||
	   	(Tr_buf_data_uart[2] == CT1) || 
		(Tr_buf_data_uart[2] == CT2) || 
		(Tr_buf_data_uart[2] == CT3) || 
		(Tr_buf_data_uart[2] == CT4) || 
		((Tr_buf_data_uart[2] & 0xF0) == MST)
		)
	{
    	for(uint8_t i = 0; i < SizeMessage; i++) 
			Tr_buf_data_uart1[i] = Tr_buf_data_uart[i];
    	NumberTransByte1 = SizeMessage;
        startTxUart1();
	}
#endif
    
	NumberTransByte = SizeMessage;
    UCSR0B |=  (1 << TXEN0) | (1 << UDRIE0);
}

//����� ��������� UART
void ClearPortError(void)
{
	Sost=0;
}



