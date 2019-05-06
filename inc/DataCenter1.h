// Обработка принятого сообщения по UART1

#ifndef DATA_CENTER_1_H_
#define DATA_CENTER_1_H_

#include <stdint.h>
#include "MyDef.h"

//подпрограмма обработки полученного сообщения
extern void DC1_dataProc(protocol_t protocol, uint8_t adr, uint8_t num);

#endif
