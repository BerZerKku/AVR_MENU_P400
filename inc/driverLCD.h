//подпрограмма работы с ЖК-индикатором
//для того чтобы вывести данные надо ввести следующие значения:
//LCDprint(Line, AddressInLine, LCDstatus, имя_массива, convers)
//, где Line - номер строки, AddressInLine -начальная позиция,
//LCDstatus - 1(команда),  2(данные)
//имя_массива - указатель массива данные которого будут выводится на индикатор (signed char)
//последним элементом массива должен быть 0x00 (т.е. окончание строки в Си).
//Команды ЖК-индикатора:
//0x01 - очистка экрана, установ курсора в нулевую позицию
//0х20 - курсор в нуле, память DDRAM с нуля
//если надо перекодировать русские буквы Windows в русские буквы LCD надо convers=1, иначе 0

//используется таймер 2
#define LCDclear FuncCommandLCD(0x01) //очистка экрана LCD
#define LCDinit FuncInitLCD //начальная

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
extern void LCDprintChar(unsigned char Line, unsigned char AddressInLine, unsigned int CodePrint); //вывод на экран 1 символа
extern void LCDptinrArchCount(unsigned char AddressInLine, unsigned int Count, unsigned char Shift);
extern void LCDprintData(unsigned char Adr, unsigned char* Mass);
extern void LCDprintTime(unsigned char Adr, unsigned char* Mass);
extern void LCDprintBitMask(unsigned char Adr, unsigned char Val, unsigned char Mask);
extern void LCDprintTimeAK(unsigned char AK, uchar dev, unsigned char Num, unsigned char* Time);
extern void LCDprintUkDef(unsigned char AKdecrease);
