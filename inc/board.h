/** Назначение выводов МК на схеме.
 * 
 */

#ifndef BOARD_H_
#define BOARD_H_

/// Выход управления мультиплексором RS232(0, подтянут к Vss) / RS485 (1). 
#define PIN_SWMUX PIND4

/// Выход управления сигналом E_STR ЖКИ
#define PIN_ESTR PINB5

/// Выход управления сигналом RS ЖКИ
#define PIN_RS PINB6

/// Выводы для работы с клавиатурой (подтянуты к Vdd).
#define PIN_ROW1 PINC0
#define PIN_ROW2 PINC1
#define PIN_ROW3 PINC2
#define PIN_ROW4 PINC3
#define PIN_COL1 PINC4
#define PIN_COL2 PINC5
#define PIN_COL3 PINC6
#define PIN_COL4 PINC7

#endif