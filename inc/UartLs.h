/** Функции работы с UART локальной сети.
 *  
 *  Работа ведется по UART1.    
 */
#ifndef UART_LS_H_
#define UART_LS_H_

#include <stdint.h>
#include "MyDef.h"   

// Буфер принимаемых по UART данных.
extern unsigned char UARTLS_rxBuf[]; 

// Буфер передаваемых по UART данных.
extern unsigned char UARTLS_txBuf[]; 

// Проверка наличия принятого сообщения.
extern bool UARTLS_isRxData(void);

// Возвращает количество принятых байт данных.
extern uint8_t UARTLS_getDataLen(void);

// Запуск работы приемника UART.
extern void UARTLS_rxStart(void);

// Настройка UART.
extern void UARTLS_setup(void);

// Счетчик паузы между принятыми байтами.
extern void UARTLS_tick(void);

// Старт передачи данных.
extern void UARTLS_txStart(uint8_t len);

#endif