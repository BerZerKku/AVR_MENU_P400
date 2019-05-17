#ifndef MY_DEF_H_
#define MY_DEF_H_

#include <stdint.h>

// версия прошивки, если первый ноль - то убираем
#define Insertion 0x0766
// вариант прошивки 'f' - полная, ' ' - урезанная
#define VARIANT ' '	

// выставочный вариант
// отключение неисправностей, отключение контроля версии
// константные измеряемые параметры
//#define EXHIBITION

#define DEB false/*работа(false)/отладка(true)*/
#if DEB // подключение файла "debug.h" 
	#warning "DEBUG MODE ON!!!"
	#include "debug.h"
#endif

#define SIZE_OF(mas) (sizeof(mas) / sizeof(mas[0]))

#define SetBit(Port,Bit) Port|=(1<<Bit)
#define ClrBit(Port,Bit) Port&=~(1<<Bit)
#define TestBit(Port,Bit) Port&(1<<Bit)

//флаг показывает что идет прием или передача сообщения
#define CurSost 0x10

//размер буфера передаваемых по UART данных
#define MaxLenghtRecBuf 128
#define MaxLenghtTrBuf 128

//запретить прерывание приема
#define DisableReceive ClrBit(UCSR0B,RXEN0); ClrBit(UCSR0B,RXCIE0)
//разрешить прерывание приема
#define EnableReceive SetBit(UCSR0B,RXEN0); SetBit(UCSR0B,RXCIE0)
//запретить прерывание по освобождению буфера передачи, остановка передачи
#define StopTrans ClrBit(UCSR0B,TXEN0); ClrBit(UCSR0B,UDRIE0)

//*100мс , время ожидания запроса с ПК
#define PC_wait 15

struct strArchive{
  unsigned char NumDev; 	//кол-во устройств
  unsigned char CurrDev;  	//выбранное устройство
  unsigned char Dev[5]; 	//массив номеров устройств: 0 байт нужен для выода инфы на дисплей =0х00 всегда!
                       		//значния: 0 - события , 1 - прд, 2- прм, 3- защ
  int RecCount; 			//кол-во записей в текущем архиве
  char CurCount;  			//адрес самой старой записи архива
  unsigned char Data[16];
};

struct strCorrParam {
    unsigned char Print[7]; //массив для выода коррекции на экран
    signed int Corr;  //текущая коррекция
};

struct strMenuGlbParam {
	uint8_t dev;			// тип удаленного аппарата
	uint8_t num;			// кол-во пунктов
	uint8_t punkt[20];	    // номера пунктов, по номерам совпадают с порядком массива во flash
	uint8_t name[20];		// номер названия , из списка во флэш
};

/** Список поддерживаемых протоколов работы по локальной сети.
 *
 *  Список должен соответстовать Menu18Param.
 */
typedef enum {
    PROTOCOL_S = 0,     // Стандартный протокол
    PROTOCOL_MODBUS,    // ModBus
    PROTOCOL_MAX        // Количество элементов перечисления. 
} protocol_t;

/** Список удаленных аппаратов.
 *
 *  Список должен соответствовать fmTypeUdDev.
 */
typedef enum {
    TYPE_UD_DEV_AVANT   = 0,
    TYPE_UD_DEV_PVZ90   = 1,
    TYPE_UD_DEV_AVZK80  = 2,
    TYPE_UD_DEV_PVZUE   = 3,
    TYPE_UD_DEV_PVZL    = 4,
    TYPE_UD_DEV_LINER   = 5,
    TYPE_UD_DEV_PVZK    = 6,
    TYPE_UD_DEV_PVZU    = 7,
    TYPE_UD_DEV_PVZ     = 8,
    TYPE_UD_DEV_MAX
} typeUdDev_t;

/// Список используемых команд.
typedef enum {
    COM_GET_MEAS 			= 0x34,
    COM_PRM_ENTER 			= 0x51,	
    COM_SET_CONTROL 		= 0x72,
    COM_SET_PASSWORD 		= 0x73,	// только с ПК
	COM_GET_PASSWORD 		= 0x74,	// только с ПК
    COM_DEF_SET_TYPE_AC 	= 0x8A,	
    COM_PRM_RES_IND			= 0x9A,
    COM_PRD_RES_IND 		= 0xAA
} com_t;

/// Значения команды управления (COM_SET_CONTROL).
typedef enum {
	CONTROL_RESET_SELF 	= 1,	///< сброс своего
    CONTROL_RESET_UD_1	= 2,	///< сброс удаленного 1
	CONTROL_RESET_UD_2	= 3,	///< сброс удаленного 2
    CONTROL_PUSK_UD_1 	= 4,	///< пуск удаленного (1)
	CONTROL_PUSK_UD_2 	= 5,	///< пуск удаленного 2
    CONTROL_PUSK_UD_ALL = 6,	///< пуск удаленных
    CONTROL_CALL 		= 7,	///< вызов
    CONTROL_PUSK_ON 	= 8,	///< пуск наладочный вкл.
	CONTROL_PUSK_OFF 	= 9,	///< пуск наладочный выкл.
    CONTROL_MAN_1 		= 10,	///< пуск МАН удаленного (1)
	CONTROL_MAN_2 		= 11,	///< пуск МАН удаленного 2
    CONTROL_MAN_ALL 	= 12,	///< пуск МАН удаленных
    CONTROL_PUSK_UD_3 	= 13,	///< пуск удаленного 3
    CONTROL_MAN_3 		= 14,	///< пуск МАН удаленного 3
    CONTROL_RESET_AC	= 15,	///< сброс АК
    //
	CONTROL_MAX					///<
} control_t;

/// Значения команды автоконтроля (COM_DEF_SET_TYPE_AC)
typedef enum {
    AC_NORM_FAST    = 1,    ///< Авто-ускоренный.    
    AC_NORM         = 2,    ///< Авто-нормальный.
    AC_FAST         = 3,    ///< Ускоренный.
    AC_OFF          = 4,    ///< Выключен.
    AC_CHECK        = 5,    ///< Контрольная проверка (в ПВЗУ-Е быстрая проверка).
    AC_TEST         = 6,    ///< Испытание (контрольная проверка в ПВЗУ-Е).
    AC_PUSK         = 7,    ///< Пуск.
    //
    AC_MAX                  ///<
} ac_t;

//struct strTest
//{
//	uint8_t type;					//тип
//	uint8_t val;					//значение
//	uint8_t __flash* __flash* sp;	//перечень
//	uint8_t __flash* name;		//имя пункта
//	uint8_t num;					//кол-во записей в группе
//	uint8_t punkt[3];				//номера пунктов
//};
//
//struct strMenuTest
//{
//	strTest sT[2];		//структуры групп
//	uint8_t num;			//кол-во групп на прием
//	uint8_t numTr;		//кол-во групп на передачу
//};

struct strNameToVal
{
	uint8_t __flash *name;
	uint8_t val;
};

struct strMenuTest
{
	uint8_t gr_items[2];			// имеющиеся группы сигналов
	uint8_t gr_items_max;			// кол-во групп сишналов
			
	
	uint8_t def_items[2];			// массив имя сигнала защиты <-> значение 
	uint8_t def_items_max;		// максимальное кол-во эл-ов защиты
	uint8_t def_val;				// текущее значение сигнала защиты		
	
	uint8_t cf_items[40];			// массив имя сигнала кч <-> значение 
	uint8_t cf_items_max;			// максимальное кол-во эл-ов кч
	uint8_t cf_val;				// текущее значение сигнала КЧ
};

struct strParamPVZUE
{
	uint8_t protocol;		// протокол обмена
	uint8_t parity;		// признак четности
	uint8_t proval[10];	// допустимые провалы
	uint8_t porog[10];	// порог по помехе
	uint8_t noise[10];	// допустимая помеха
	uint8_t autocontrol;	// тип автоконтроля
	uint8_t periodAC[10];	// период беглого режима АК
	uint8_t periodACre[10];// период повтора беглого режима АК
	uint8_t timeCorrAC[10];// время коррекции АК
};

struct strParamOpt
{
	uint8_t reserv;		// резервирование (вкл = 1/выкл = 0)
};
#endif