#ifndef __MY_DEF
#define __MY_DEF

#include <stdint.h>

//версия прошивки, если первый ноль - то убираем
#define Insertion 0x0854

// выставочный вариант
// отключение неисправностей, отключение контроля версии
// константные измеряемые параметры
//#define EXHIBITION

#define DEB false /*работа(false)/отладка(true)*/
#if DEB // подключение файла "debug.h" 
	#warning "DEBUG MODE ON!!!"
	#include "debug.h"
#endif

//Взять старший байт int
#define Hi(a) (unsigned char) (a>>8)
//Взять младший байт Int
#define Lo(a) (unsigned char) (a)

#define SetBit(Port,Bit) Port|=(1<<Bit)
#define ClrBit(Port,Bit) Port&=~(1<<Bit)
#define TestBit(Port,Bit) Port&(1<<Bit)

//макрос записи в старший байт инта байта
#define LoadHiByte(ints,chars) (((ints)&0x00ff)|((chars)<<8))
#define LoadLoByte(ints,chars) (((ints)&0xff00)|((chars)))
//флаг показывает разрешение приема UART
#define EnRead 0x02
// флаг показывает разрешение передачи UART
#define EnWrite 0x04
//флаг показывает что идет прием или передача сообщения
#define CurSost 0x10
//флаг показывает, что сообщение принято
#define DataRead  0x08

#define AddressDevice 0x01

//размер буфера принимаемых по UART данных
#define MaxLenghtRecBuf 64
//размер буфера передаваемых по UART данных
#define MaxLenghtTrBuf 64
#define MaxLenghtTrBuf1 255
//5 //максимальное расстояние между байтами *1000мкс
#define MaxPause 30
#define MaxPause1 5
//наличие аппаратных ошибок приема
#define HardError 0x01
  //запретить прерывание приема
  #define DisableReceive ClrBit(UCSR0B,RXEN0); ClrBit(UCSR0B,RXCIE0)
  //разрешить прерывание приема
  #define EnableReceive SetBit(UCSR0B,RXEN0); SetBit(UCSR0B,RXCIE0)
  //проверка на разрешение прерывания приема
  #define TestReceive TestBit(UCSR0B,RXCIE0)
  //разрешить прерывание по освобождению буфера передачи, начать передачу
  #define GoTrans SetBit(UCSR0B,TXEN0); SetBit(UCSR0B,UDRIE0)
  //запретить прерывание по освобождению буфера передачи, остановка передачи
  #define StopTrans ClrBit(UCSR0B,TXEN0); ClrBit(UCSR0B,UDRIE0)
  //проверка на разрешение прерывания передачи
  #define TestTrans TestBit(UCSR0B,UDRIE0)
  //запретить прерывание приема
  #define DisableReceive1 ClrBit(UCSR1B,RXEN1); ClrBit(UCSR1B,RXCIE1)
  //разрешить прерывание приема
  #define EnableReceive1 SetBit(UCSR1B,RXEN1); SetBit(UCSR1B,RXCIE1)
  //проверка на разрешение прерывания приема
  #define TestReceive1 TestBit(UCSR1B,RXCIE1)
  //разрешить прерывание по освобождению буфера передачи, начать передачу
  #define GoTrans1 SetBit(UCSR1B,TXEN1); SetBit(UCSR1B,UDRIE1)
  //запретить прерывание по освобождению буфера передачи, остановка передачи
  #define StopTrans1 ClrBit(UCSR1B,TXEN1); ClrBit(UCSR1B,UDRIE1)
  //проверка на разрешение прерывания передачи
  #define TestTrans1 TestBit(UCSR1B,UDRIE1)
//остановка таймера 0
#define StopT0 TCCR0=0

//*100мс , время ожидания запроса с ПК
#define PC_wait 15

#define uchar 	unsigned char
#define schar 	signed char
#define uint  	unsigned int
#define sint 	signed int


struct strArchiveDevice
{
	unsigned char typeDev;			// eMENUarchDevices
	int maxNumEntries;				// максимальное кол-во записей в архиве
	unsigned char __flash *name;	// имя пункта журнала
	unsigned char __flash *nameJrn;	// имя текущего журнала
	
	strArchiveDevice(	uchar type,  
					 	unsigned char __flash *punkt,
						unsigned char __flash *title,
						int max = 256)
	{
		typeDev = type;
		maxNumEntries = max;
		name = punkt;
		nameJrn = title;
	}
	
};

struct strArchives
{
	bool refresh;						// true - получена новая инф-ия
	uint8_t numArchives;				// кол-во архивов устройств
	strArchiveDevice *curArchive;		// номер в listArchives
	strArchiveDevice *listArchives[4];	// указатели на архивы устройств
	
	bool ovf;							// флаг переполнения архива
	uint16_t oldestEntry;				// номер самой старой записи при переполнении
										// и макс. записей без переполнения
	uint16_t curEntry;					// номер текущей записи
	uint8_t subNum;
	
	// данные
	uint8_t regime;
	uint8_t bytes[4];
	
	// время события
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
	uint16_t milliseconds;
	
	// дата события
	uint8_t day;
	uint8_t month;
	uint8_t year;
	
	strArchives()
	{
		refresh = true;
		numArchives = 0;
		oldestEntry = 0;
		curEntry = 0;
		subNum = 0;
		ovf = false;
	}
};

struct strCorrParam
{
	unsigned char Print[7]; 	// массив для выода коррекции на экран
	signed int Corr;  			// текущая коррекция
};

struct strMenuGlbParam
{
	uchar dev;					// тип удаленного аппарата
	uchar num;					// кол-во пунктов
	uchar punkt[20];			// номера пунктов, по номерам совпадают с порядком массива во flash
	uchar name[20];				// номер названия , из списка во флэш
};

struct strNameToVal
{
	uchar __flash *name;
	uchar val;
};

struct strMenuTest
{
	uchar gr_items[2];			// имеющиеся группы сигналов
	uchar gr_items_max;			// кол-во групп сишналов
			
	uchar def_items[2];			// массив имя сигнала защиты <-> значение 
	uchar def_items_max;		// максимальное кол-во эл-ов защиты
	uchar def_val;				// текущее значение сигнала защиты		
	
	uchar cf_items[40];			// массив имя сигнала кч <-> значение 
	uchar cf_items_max;			// максимальное кол-во эл-ов кч
	uchar cf_val;				// текущее значение сигнала КЧ
};

struct strParamPVZUE
{
	uchar protocol;				// протокол обмена
	uchar parity;				// признак четности
	uchar proval[10];			// допустимые провалы
	uchar porog[10];			// порог по помехе
	uchar noise[10];			// допустимая помеха
	uchar autocontrol;			// тип автоконтроля
};

struct strParamOpt
{
	uchar reserv;				// резервирование (вкл = 1/выкл = 0)
};

struct strParam
{
	uchar 	min;				// минимальное значение
	uint	max;				// максимальное значение
	uchar 	div;				// делитель (т.е. реальное значение = пар-р * делитель)
	uchar 	dis;				// дискретность ввода (т.е. реальное значение = (введеноме / дискрет) * дискрет
	uchar	var;				// вид параметра / подсказки ( 0 - неизвестно,
								// 1 - список, 2 - целое число, 3 - дробное число 1 знак после запятой)
};		
#endif