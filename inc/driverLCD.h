//������������ ������ � ��-�����������
//��� ���� ����� ������� ������ ���� ������ ��������� ��������:
//LCDprint(Line, AddressInLine, LCDstatus, ���_�������, convers)
//, ��� Line - ����� ������, AddressInLine -��������� �������,
//LCDstatus - 1(�������),  2(������)
//���_������� - ��������� ������� ������ �������� ����� ��������� �� ��������� (signed char)
//��������� ��������� ������� ������ ���� 0x00 (�.�. ��������� ������ � ��).
//������� ��-����������:
//0x01 - ������� ������, ������� ������� � ������� �������
//0�20 - ������ � ����, ������ DDRAM � ����
//���� ���� �������������� ������� ����� Windows � ������� ����� LCD ���� convers=1, ����� 0

//������������ ������ 2
#define LCDclear FuncCommandLCD(0x01) //������� ������ LCD
#define LCDinit FuncInitLCD //���������

extern unsigned char LCDstat;

//
extern void LCDprint(unsigned char Line, unsigned char AddressInLine, unsigned char* bufer, unsigned char convers);
extern void LCDprintf(unsigned char Line, unsigned char AddressInLine, unsigned char __flash* buferf, unsigned char convers);
extern void FuncCommandLCD(unsigned char com);
extern void FuncInitLCD(void);
extern void LCDbufClear(void);
extern void LCDbufClMenu(void);
extern void LCDprintHEX(unsigned char Line, unsigned char AddressInLine, unsigned char CodePrint);
extern void FuncClearCharLCD(unsigned char Line, unsigned char AddressInLine, unsigned char NumberChar);
extern void LCDprintDEC(unsigned char Line, unsigned char AddressInLine, unsigned char CodePrint);
extern void LCDprintDEC1(unsigned char Line, unsigned char AddressInLine, unsigned char CodePrint);
extern void LCDprintDEC2(unsigned char Line, unsigned char AddressInLine, unsigned char CodePrint);
extern void LCDprintBits(unsigned char Line, unsigned char AddressLine, unsigned char CodePrint);
extern void LCDprintInsertion(unsigned char Line, unsigned char AddressInLine, unsigned int CodePrint);
extern void LCDprintTetr(unsigned char Line, unsigned char AddressInLine, unsigned char CodePrint);
extern void LCDprintChar(unsigned char Line, unsigned char AddressInLine, unsigned int CodePrint); //����� �� ����� 1 �������
extern void LCDptinrArchCount(unsigned char AddressInLine, unsigned int Count, unsigned char Shift);
extern void LCDprintData(unsigned char Adr, unsigned char* Mass);
extern void LCDprintTime(unsigned char Adr, unsigned char* Mass);
extern void LCDprintBitMask(unsigned char Adr, unsigned char Val, unsigned char Mask);
extern void LCDprintTimeAK(unsigned char AK, uchar dev, unsigned char Num, unsigned char* Time);
extern void LCDprintUkDef(unsigned char AKdecrease);
