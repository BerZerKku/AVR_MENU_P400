#include <ioavr.h>
#include <ina90.h>


#include "UartBsp.h"
#include "DataCenter.h"
#include "DataCenter1.h"
#include "UartLs.h"

#define StartTimer0 TCNT0=5;TCCR0=0x04; //запуск таймера 0
#define InitTimer0 TIFR&=0xFD;TIMSK|=(1<<TOIE0); //инициализация таймера0

extern void SetStopBit(void);
extern unsigned char InquiryKeyboard(void);
extern unsigned char PressKey;
unsigned char TempPressKey, NewPressKey;
int TimerPressKey;

char Sost=0;  //переменная ненулевое значение которой говорит об ошибке

unsigned char Rec_buf_data_uart [MaxLenghtRecBuf] ; //буфер принимаемых данных
unsigned char Tr_buf_data_uart [MaxLenghtTrBuf] ; //буфер передаваемых данных

unsigned char RecByteCounter=0; //счетчик принятых байт
signed char TrByteCounter=0;  //счетчик передаваемых данных
signed char NumberTransByte=0; //кол-во передаваемых байтов
unsigned char DataPause=0x00; //определяет время между принятыми байтами
unsigned char StartRec=0;   //разрешает прием сообщения
uchar cCurrLen0=0;  //счетчик принятых байт
uchar cMaxLen0=0; //кол-во ожидаемых байт в посылке

//переменные общения с EEPROM
unsigned char ew,er;
unsigned char eWrite, eRead;
unsigned char* eMassiveWrite;
unsigned char* eMassiveRead;
unsigned int eAddressWrite, eAddressRead;

unsigned char PCready=0;
unsigned char PCtime=20;
unsigned char PCbyte=0;

/// Флаг наличия принятой посылки (true) полученной по UART0.
bool uart0rxReady = false; 
unsigned char cNumRecByte = 0; //ко-во принятых байт

//старт UART
void StartUART(void) {
    //НАчальная установка UART
    //  StUART();
    //настройки для UART1
    //настройки для UART0
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



#pragma vector=USART0_RXC_vect //адрес прерывания приема UART
__interrupt void UART_RX_interrupt(void){
  char temp_rec;
  temp_rec=UDR0;
  if  (UCSR0A&(1<<FE1)) return;  //FE-ошибка кадра, OVR - переполнение данных (флаги)

  switch (cCurrLen0){
  //прокерка 1-ого синхробайта
    case 0: if (temp_rec == 0x55) cCurrLen0 = 1; break;
    //проверка 2-ого синхробайта
    case 1: if (temp_rec == 0xAA) cCurrLen0 = 2; else cCurrLen0 = 0; break;
    //байт команды
    case 2: {
      Rec_buf_data_uart[2] = temp_rec;
      cCurrLen0 = 3;
    }break;
    //кол-во байт данных
    case 3:{
      Rec_buf_data_uart[3]=temp_rec;
      if (temp_rec > (MaxLenghtRecBuf - 5)) cCurrLen0 = 0;  //проверка на макс кол-во данных
      else cCurrLen0 = 4;
      cMaxLen0 = cCurrLen0 + temp_rec; //кол-во принимаемых данных
    }break;
    default:{//данные и КС
      Rec_buf_data_uart[cCurrLen0] = temp_rec;
      if (cCurrLen0 >= cMaxLen0){
        uart0rxReady = true; // приняли все
        cCurrLen0=0;
        DisableReceive;  //остановим прием
        cNumRecByte = cMaxLen0 + 1;
      }else cCurrLen0++;
    }
  }//end switch(cCurrLen0)
}


#pragma vector=USART0_UDRE_vect //адрес прерывания передачи в буфер UART
__interrupt void UART_UDRE_interrupt(void){
//  char temp_tr;
  if (TrByteCounter<NumberTransByte)   //если мы еще передали не все байты, то продолжаем передовать
    {
      UDR0=Tr_buf_data_uart[TrByteCounter];
      ++TrByteCounter;
    }
  else    //если же мы все передали, то останавливаем передачу и сбрасываем используемые переменные
    {
      StopTrans;
      NumberTransByte=0;
      TrByteCounter=0;
      EnableReceive;
      Sost&=~(CurSost);
    }
}

#pragma vector=TIMER0_OVF_vect  //адрес прерывания таймера/счетчика 0 по переполнению
__interrupt void Timer0_overflowed_interrupt(void){   
    // опрос клавиатуры, каждую 1 мс
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
    
    //запись в EEPROM
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
    //чтение из EEPROM
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

//разрешение передачи по UART, с указанием ко-ва передаваемых байтов
void StartTrans(char SizeMessage)
{
#if ( (DEB) && (PK) )	// пересылка сообщений для БСП на ПК
	#warning Включена пересылка сообщений для БСП на ПК!!!  
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

//сброс состояния UART
void ClearPortError(void)
{
	Sost=0;
}



