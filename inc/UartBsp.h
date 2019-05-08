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

extern bool uart0rxReady; //true - принята посылка, надо обработать
extern unsigned char cNumRecByte;  //кол-во принятых байт

//// Буфер принимаемых по UART данных.
//extern unsigned char UARTBSP_rxBuf[]; 
//
//// Буфер передаваемых по UART данных.
//extern unsigned char UARTBSP_txBuf[]; 
//
//// Проверка наличия принятого сообщения.
//extern bool UARTBSP_isRxData(void);
//
//// Возвращает количество принятых байт данных.
//extern uint8_t UARTBSP_getDataLen(void);
//
//// Запуск работы приемника UART.
//extern void UARTBSP_rxStart(void);

// Настройка UART.
extern void UARTBSP_setup(void);

//// Счетчик паузы между принятыми байтами.
//extern void UARTBSP_tick(void);
//
//// Старт передачи данных.
//extern void UARTBSP_txStart(uint8_t len);

#endif
