#include <ioavr.h>
#include <ina90.h>


#include "UartBsp.h"
#include "DataCenter.h"
#include "DataCenter1.h"
#include "UartLs.h"


char Sost=0;  //переменная ненулевое значение которой говорит об ошибке

unsigned char Rec_buf_data_uart [MaxLenghtRecBuf] ; //буфер принимаемых данных
unsigned char Tr_buf_data_uart [MaxLenghtTrBuf] ; //буфер передаваемых данных

unsigned char RecByteCounter=0; //счетчик принятых байт
signed char TrByteCounter=0;  //счетчик передаваемых данных
signed char NumberTransByte=0; //кол-во передаваемых байтов
unsigned char DataPause=0x00; //определяет время между принятыми байтами
unsigned char StartRec=0;   //разрешает прием сообщения
uint8_t cCurrLen0=0;  //счетчик принятых байт
uint8_t cMaxLen0=0; //кол-во ожидаемых байт в посылке



/// Флаг наличия принятой посылки (true) полученной по UART0.
bool uart0rxReady = false; 
unsigned char cNumRecByte = 0; //ко-во принятых байт

/// Инициализация и запуск работы приемопередатчика UART0.
void UARTBSP_setup(void) {
    UBRR0L=207;

    // PI_RXD
    DDRE  &= ~(1 << PORTE0);
    PORTE &= ~(1 << PORTE0);
    
    // PI_TXD
    DDRE  |= (1 << PORTE1);
    PORTE |= (1 << PORTE1);
    
    // два стоп-бита и формат посылки 8 разрядов
    UCSR0C = (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);
    
    // старт работы приемника и передатчика
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    EnableReceive;
    
    Tr_buf_data_uart[0]=0x55;
    Tr_buf_data_uart[1]=0xAA;
    Rec_buf_data_uart[0]=0x55;
    Rec_buf_data_uart[1]=0xAA;
}


#pragma vector=USART0_RXC_vect //адрес прерывания приема UART
__interrupt void UART_RX_interrupt(void){
    uint8_t tmp = UDR0;
    
    //FE-ошибка кадра, OVR - переполнение данных (флаги)
    if  (UCSR0A & (1 << FE0)) {
        cCurrLen0 = 0;
    } else {           
        switch (cCurrLen0){
            //прокерка 1-ого синхробайта
            case 0: if (tmp == 0x55) cCurrLen0 = 1; break;
            //проверка 2-ого синхробайта
            case 1: if (tmp == 0xAA) cCurrLen0 = 2; else cCurrLen0 = 0; break;
            //байт команды
            case 2: {
                Rec_buf_data_uart[2] = tmp;
                cCurrLen0 = 3;
            }break;
            //кол-во байт данных
            case 3:{
                Rec_buf_data_uart[3]=tmp;
                if (tmp > (MaxLenghtRecBuf - 5)) cCurrLen0 = 0;  //проверка на макс кол-во данных
                else cCurrLen0 = 4;
                cMaxLen0 = cCurrLen0 + tmp; //кол-во принимаемых данных
            }break;
            default:{//данные и КС
                Rec_buf_data_uart[cCurrLen0] = tmp;
                if (cCurrLen0 >= cMaxLen0){
                    uart0rxReady = true; // приняли все
                    cCurrLen0=0;
                    DisableReceive;  //остановим прием
                    cNumRecByte = cMaxLen0 + 1;
                }else cCurrLen0++;
            }
        }
    }
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
    	for(uint8_t i = 0; i < SizeMessage; i++) 
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



