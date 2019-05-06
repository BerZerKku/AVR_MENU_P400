/** Функции работы с UART БСП.
 *  
 *  Работа ведется по UART0.    
 */
#ifndef UART_BSP_H_
#define UART_BSP_H_

#include <stdint.h>
#include "MyDef.h"

//сброс регистра ошибок
void ClearPortError(void);

//опрос состояния UART
char GetSostPort(void);

//запустить передачу из буфера
void StartTrans(char SizeMessage);

//старт UART
void StartUART(void);

extern unsigned char Rec_buf_data_uart [MaxLenghtRecBuf] ; //буфер принимаемых данных
extern unsigned char Tr_buf_data_uart [MaxLenghtTrBuf] ; //буфер передаваемых данных
extern char Sost;
//extern unsigned char DataRec; //=1, когда получено сообщение

extern unsigned char PCready;
extern unsigned char PCbyte;
extern unsigned char PCtime;

extern bool uart0rxReady; //true - принята посылка, надо обработать
extern unsigned char cNumRecByte;  //кол-во принятых байт

#endif
