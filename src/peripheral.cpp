//��������� ��������� ATmega162
#include <ioavr.h>
#include <ina90.h>
#include "peripheral.h"
#include "board.h"

/// ��������� ����������.
void PERIF_intrEnable(void) {
    __enable_interrupt();
}

/// ��������� ���������.
void PERIF_setup(void) {
    //��������� ������
    //��� ����� ��������� �� ���� � ��������� � Z-���������
    
    // ���� ������ D ��� ���������� ���
    DDRA  = 0xFF;   
    PORTA = 0x00;   
    
    DDRB  = (1 << PIN_RS) | (1 << PIN_ESTR);    
    PORTB = (1 << PIN_RS);   
    
    // ���� ��� ������ � ����������� 
    DDRC  = 0x00;
    PORTC = 0x00;  
    
    DDRD  = (1 << PIN_SWMUX);
    PORTD = (0 << PIN_SWMUX);
    
    // ������ 1
	// ����� ����� �� ���������� A
    TCCR1A  = (0 << WGM11) | (0 << WGM10);
    TCCR1B  = (0 << WGM13) | (1 << WGM12);
    // ��� = 1 / (F_CPU / N)
    // �������� N = 256 -> ��� = 1 / (16e6 / 256) = 16 ���
    // TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10); 
    TCCR1C  = 0;
    TCNT1   = 0;
    // ����� ������������ = ��� * (1 + OCR)
    // ���� �� 6250, �.�. ����� ������������ = 16 ��� * 6250 = 100 ��
    OCR1A   = 6250 - 1;    
    TIMSK  |= (1 << OCIE1A);
    
    // ������ 2
    // ����� �� ����������
    TCNT2 = (1 << WGM21) | (0 << WGM20);
    // �������� N = 64 -> ��� = 1 / (16e6 / 256) = 4 ���
    // TCNT2 |= (0 << CS22) | (1 << CS21) | (1 << CS20);
    // ����� ������������ = ��� * (1 + OCR)
    // ���� �� 250, �.�. ����� ������������ = 4 ��� * 250 = 1 ��
    OCR2 = 250 - 1;
    TIMSK |= (1 << TOIE2);
}

/// ������ �������1
void PERIF_timer1Start(void) {
    TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10); 
}

/// ������ �������2
void PERIF_timer2Start(void) {
    TCCR2 |= (0 << CS12) | (1 << CS11) | (1 << CS10); 
}

/** ����� ����������� �������.
 *
 *  ���������� �������� �� ���� ��� ��������� WD.
 */
void PERIF_wdReset(void) {
    __watchdog_reset();
}

/** ������ ����������� �������.
 *
 *  ����� ������������ ������� �������� 0.24 �������.
 */
void PERIF_wdStart(void) {
    __watchdog_reset();
    
    WDTCR  = (1 << WDE) | (1 << WDCE);    
    WDTCR |= (1 << WDP2) | (0 << WDP1) | (0 << WDP0); // Time-out ~ 0.24s
}




