/** ���������� ������� �� �� �����.
 * 
 */

#ifndef BOARD_H_
#define BOARD_H_

/// ����� ���������� ��������������� RS232(0, �������� � Vss) / RS485 (1). 
#define PIN_SWMUX PIND4

/// ����� ���������� �������� E_STR ���
#define PIN_ESTR PINB5

/// ����� ���������� �������� RS ���
#define PIN_RS PINB6

/// ������ ��� ������ � ����������� (��������� � Vdd).
#define PIN_ROW1 PINC0
#define PIN_ROW2 PINC1
#define PIN_ROW3 PINC2
#define PIN_ROW4 PINC3
#define PIN_COL1 PINC4
#define PIN_COL2 PINC5
#define PIN_COL3 PINC6
#define PIN_COL4 PINC7

#endif