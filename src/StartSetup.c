//��������� ��������� ATmega162
#include "ioavr.h"

void StartSetup(void)
{

    //��������� ������
    //��� ����� ��������� �� ���� � ��������� � Z-���������

    DDRA = 0xFF; //
    PORTA = 0x00; //����� ���������� � 0

    DDRB = 0x70; //
    PORTB = 0x20; //���� �������� �� �����, PE.5 - ���������� � 1

    DDRC = 0x00;
    PORTC = 0x00; //PC.0-PC.3 ����� 1, PC.4-PC.7 ���� Z-���������

    DDRD = 0x00;
    PORTD = 0x00;

    TIMSK |= (1 << TOIE2);
    TCNT2 = 130;

    TIMSK |= (1 << TOIE1);
    TCCR1A = 0x00;
    TCCR1B = 0x00; //0x05 - �������� �� 1024
    TCNT1H = 0xF9; //
    TCNT1L = 0xE5; //��������� 0.1� ��� �������� 1024
}
