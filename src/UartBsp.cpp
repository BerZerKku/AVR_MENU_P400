#include <ioavr.h>
#include <ina90.h>


#include "UartBsp.h"
#include "DataCenter.h"
#include "DataCenter1.h"
#include "UartLs.h"

#define StartTimer0 TCNT0=5;TCCR0=0x04; //������ ������� 0
#define InitTimer0 TIFR&=0xFD;TIMSK|=(1<<TOIE0); //������������� �������0

extern void SetStopBit(void);
extern unsigned char InquiryKeyboard(void);
extern unsigned char PressKey;
unsigned char TempPressKey, NewPressKey;
int TimerPressKey;

char Sost=0;  //���������� ��������� �������� ������� ������� �� ������

unsigned char Rec_buf_data_uart [MaxLenghtRecBuf] ; //����� ����������� ������
unsigned char Tr_buf_data_uart [MaxLenghtTrBuf] ; //����� ������������ ������

unsigned char RecByteCounter=0; //������� �������� ����
signed char TrByteCounter=0;  //������� ������������ ������
signed char NumberTransByte=0; //���-�� ������������ ������
unsigned char DataPause=0x00; //���������� ����� ����� ��������� �������
unsigned char StartRec=0;   //��������� ����� ���������
uchar cCurrLen0=0;  //������� �������� ����
uchar cMaxLen0=0; //���-�� ��������� ���� � �������

//���������� ������� � EEPROM
unsigned char ew,er;
unsigned char eWrite, eRead;
unsigned char* eMassiveWrite;
unsigned char* eMassiveRead;
unsigned int eAddressWrite, eAddressRead;

unsigned char PCready=0;
unsigned char PCtime=20;
unsigned char PCbyte=0;

/// ���� ������� �������� ������� (true) ���������� �� UART0.
bool uart0rxReady = false; 
unsigned char cNumRecByte = 0; //��-�� �������� ����

//����� UART
void StartUART(void) {
    //��������� ��������� UART
    //  StUART();
    //��������� ��� UART1
    //��������� ��� UART0
    UBRR0L=207;
    //  UBRR0L=103;
    
    DDRE&=~(1<<PORTE0);
    DDRE|=(1<<PORTE1);
    PORTE&=~(1<<PORTE0);
    PORTE|=(1<<PORTE1);
    UCSR0C=(1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
    UCSR0B=(1<<RXEN0)|(1<<TXEN0);
    EnableReceive;
    InitTimer0;
    StartTimer0;
    Tr_buf_data_uart[0]=0x55;
    Tr_buf_data_uart[1]=0xAA;
    Rec_buf_data_uart[0]=0x55;
    Rec_buf_data_uart[1]=0xAA;
}



#pragma vector=USART0_RXC_vect //����� ���������� ������ UART
__interrupt void UART_RX_interrupt(void){
  char temp_rec;
  temp_rec=UDR0;
  if  (UCSR0A&(1<<FE1)) return;  //FE-������ �����, OVR - ������������ ������ (�����)

  switch (cCurrLen0){
  //�������� 1-��� �����������
    case 0: if (temp_rec == 0x55) cCurrLen0 = 1; break;
    //�������� 2-��� �����������
    case 1: if (temp_rec == 0xAA) cCurrLen0 = 2; else cCurrLen0 = 0; break;
    //���� �������
    case 2: {
      Rec_buf_data_uart[2] = temp_rec;
      cCurrLen0 = 3;
    }break;
    //���-�� ���� ������
    case 3:{
      Rec_buf_data_uart[3]=temp_rec;
      if (temp_rec > (MaxLenghtRecBuf - 5)) cCurrLen0 = 0;  //�������� �� ���� ���-�� ������
      else cCurrLen0 = 4;
      cMaxLen0 = cCurrLen0 + temp_rec; //���-�� ����������� ������
    }break;
    default:{//������ � ��
      Rec_buf_data_uart[cCurrLen0] = temp_rec;
      if (cCurrLen0 >= cMaxLen0){
        uart0rxReady = true; // ������� ���
        cCurrLen0=0;
        DisableReceive;  //��������� �����
        cNumRecByte = cMaxLen0 + 1;
      }else cCurrLen0++;
    }
  }//end switch(cCurrLen0)
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

#pragma vector=TIMER0_OVF_vect  //����� ���������� �������/�������� 0 �� ������������
__interrupt void Timer0_overflowed_interrupt(void){   
    // ����� ����������, ������ 1 ��
    if ((PressKey==0xF0)&&(PCready==0)) {
        NewPressKey=InquiryKeyboard();
        if ((NewPressKey==TempPressKey)||(NewPressKey==0xF0)) {
            TimerPressKey++;
            if (TimerPressKey>400) {TimerPressKey=400; TempPressKey=0xF0;}
        }
        else TimerPressKey=0;
        if ((NewPressKey!=TempPressKey)&&(NewPressKey!=0xF0)) {PressKey=NewPressKey; TempPressKey=NewPressKey;}
    }
        
    UARTLS_tick();
    
    //������ � EEPROM
    if (((EECR&(1<<EEWE))==0)&&(eWrite==1)){
        _CLI();
        EEAR=eAddressWrite;
        EEDR=eMassiveWrite[ew];
        EECR|=(1<<EEMWE);
        EECR|=(1<<EEWE);
        _SEI();
        ew++;
        eAddressWrite++;
        if (eMassiveWrite[ew-1]==0) {eWrite=0; ew=0;}
    }
    //������ �� EEPROM
    if (((EECR&(1<<EEWE))==0)&&(eRead==1)){
        EEAR=eAddressRead;
        EECR|=(1<<EERE);
        eMassiveRead[er]=EEDR;
        if (eMassiveRead[er]==0xFF) eMassiveRead[er]=0x00;
        eAddressRead++;
        er++;
        if (eMassiveRead[er-1]==0) {eRead=0; er=0;}
    }
    
}//end_Timer0_overflowed_interrupt

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
    	for(uchar i = 0; i < SizeMessage; i++) 
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



