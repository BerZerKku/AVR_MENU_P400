/*****************************************
переходы между меню
*****************************************/
#include "Menu.h"

#define dSetUprItem(com,nameItem) sMenuUpr.punkt[num] = com; sMenuUpr.name[num++] = nameItem 

void MenuParamGlbCreate	(void);
void MenuParamDefCreate	(void);
void MenuUprCreate 		(uint8_t act);
void MenuAKCreate		(void);
void MenuTestCreate		(void);

static void Menu_Start				(void);
static void Menu_Second				(void);
static void Menu_DataTime			(void);
static void Menu_Journal			(void);
static void Menu_Setup				(void);
static void Menu_ParamSetup			(eMENUlvl Menu);
static void Menu_ParamSetup_Def		(eMENUlvl lvl);
static void Menu_ParamSetup_Prm		(eMENUlvl lvl);
static void Menu_ParamSetup_Prd 	(eMENUlvl lvl);
static void Menu_ParamSetup_Global	(eMENUlvl lvl);
static void Menu_Setup_Regime		(void);
static void Menu_Protocol			(void);
static void Menu_Info				(void);
static void Menu_Setup_Test			(void);
static void PressInMenuJournal		(char Key);
static void Menu_Upr				(void);
static void PressInMenuDataTime		(char Key);
static void PressInMenuReset		(char key);


/** Формирование списка параметров Общих в зависимости от совместимости
*	@param Нет
*	@return Нет
*/
void MenuParamGlbCreate(void)
{
	char num = 0;
	
	switch(TypeUdDev)
	{
		
		case 1:		// ПВЗ-90
		case 2:		// АВЗК-80	
		{
			sMenuGlbParam.punkt[num] = 0; 	sMenuGlbParam.name[num++] = 0;		// Совместимость
			sMenuGlbParam.punkt[num] = 2; 	sMenuGlbParam.name[num++] = 2;		// Uвых номинальное
			sMenuGlbParam.punkt[num] = 4;	sMenuGlbParam.name[num++] = 4;		// Сетевой адрес
			sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;		// Номер аппарата
			sMenuGlbParam.punkt[num] = 8; 	sMenuGlbParam.name[num++] = 8;		// Контроль вых.сигнала
			sMenuGlbParam.punkt[num] = 9; 	sMenuGlbParam.name[num++] = NumParamGlb; // Порог ПРЕДУПР по РЗ
			sMenuGlbParam.punkt[num] = 11; 	sMenuGlbParam.name[num++] = 11;		// Коррекция напряжения
			sMenuGlbParam.punkt[num] = 12; 	sMenuGlbParam.name[num++] = 12;		// Коррекция тока
		}
		break;
		
		case 3:		// ПВЗУ-Е
		{
			sMenuGlbParam.punkt[num] = 0; 	sMenuGlbParam.name[num++] = 0;		// Совместимость
			sMenuGlbParam.punkt[num] = 2; 	sMenuGlbParam.name[num++] = 2;		// Uвых номинальное
			sMenuGlbParam.punkt[num] = 4; 	sMenuGlbParam.name[num++] = 4;		// Сетевой адрес
			sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;		// Номер аппарата
			sMenuGlbParam.punkt[num] = 8; 	sMenuGlbParam.name[num++] = 8;		// Контроль вых.сигнала
			sMenuGlbParam.punkt[num] = 9; 	sMenuGlbParam.name[num++] = NumParamGlb; // Порог ПРЕДУПР по РЗ
			sMenuGlbParam.punkt[num] = 11; 	sMenuGlbParam.name[num++] = 11;		// Коррекция напряжения
			sMenuGlbParam.punkt[num] = 12; 	sMenuGlbParam.name[num++] = 12;		// Коррекция тока
			sMenuGlbParam.punkt[num] = 13; 	sMenuGlbParam.name[num++] = 13;		// Протокол обмена
			sMenuGlbParam.punkt[num] = 14; 	sMenuGlbParam.name[num++] = 14;		// Признак четности
			sMenuGlbParam.punkt[num] = 15; 	sMenuGlbParam.name[num++] = 15;		// Допустимые провалы
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.proval[i] = MenuAllProval[i];
				if (MenuAllProval[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[num] = 16;	sMenuGlbParam.name[num++] = 16;		// Порог по помехе
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.porog[i] = MenuAllPorog[i];
				if (MenuAllPorog[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[num] = 17;	sMenuGlbParam.name[num++] = 17;		// Допустимая помеха
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.noise[i] = MenuAllNoise[i];
				if (MenuAllNoise[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[num] = 18; 	sMenuGlbParam.name[num++] = 18;		// Тип автоконтроля
			
		}
		break;
		
		case 4:		// ПВЗЛ
		{
			sMenuGlbParam.punkt[num] = 0; 	sMenuGlbParam.name[num++] = 0;		// Совместимость
			sMenuGlbParam.punkt[num] = 2; 	sMenuGlbParam.name[num++] = 2;		// Uвых номинальное
			sMenuGlbParam.punkt[num] = 4;	sMenuGlbParam.name[num++] = 4;		// Сетевой адрес
			sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;		// Номер аппарата
			sMenuGlbParam.punkt[num] = 8; 	sMenuGlbParam.name[num++] = 8;		// Контроль вых.сигнала
			sMenuGlbParam.punkt[num] = 9; 	sMenuGlbParam.name[num++] = NumParamGlb; // Порог ПРЕДУПР по РЗ
			sMenuGlbParam.punkt[num] = 20;	sMenuGlbParam.name[num++] = 20;		// Снижение ответа АК
			sMenuGlbParam.punkt[num] = 11; 	sMenuGlbParam.name[num++] = 11;		// Коррекция напряжения
			sMenuGlbParam.punkt[num] = 12; 	sMenuGlbParam.name[num++] = 12;		// Коррекция тока
		}
		break;
		
		default: 	// АВАНТ
		{
			if (cTypeLine == 1)													
			{
				sMenuGlbParam.punkt[num] = 0;	sMenuGlbParam.name[num++] = 0;	// Совместимость
				sMenuGlbParam.punkt[num] = 1;	sMenuGlbParam.name[num++] = 1;	// Cинхронизация часов
				sMenuGlbParam.punkt[num] = 2;	sMenuGlbParam.name[num++] = 2;	// Uвых номинальное
				sMenuGlbParam.punkt[num] = 4;	sMenuGlbParam.name[num++] = 4;	// Сетевой адрес
				//				sMenuGlbParam.punkt[num] = 5; 	sMenuGlbParam.name[num++] = 5;	// Время перезапуска
				sMenuGlbParam.punkt[num] = 6;	sMenuGlbParam.name[num++] = 6;	// Частота
				sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;	// Номер аппарата
				sMenuGlbParam.punkt[num] = 8; 	sMenuGlbParam.name[num++] = 8;	// Контроль вых.сигнала
				sMenuGlbParam.punkt[num] = 9; 	sMenuGlbParam.name[num++] = 9;	// Порог ПРЕДУПР по КЧ
				sMenuGlbParam.punkt[num] = 11; 	sMenuGlbParam.name[num++] = 11;	// Коррекция напряжения
				sMenuGlbParam.punkt[num] = 12; 	sMenuGlbParam.name[num++] = 12;	// Коррекция тока
			}
			else
			{
				sMenuGlbParam.punkt[num] = 1; 	sMenuGlbParam.name[num++] = 1;	// Cинхронизация часов
				sMenuGlbParam.punkt[num] = 4; 	sMenuGlbParam.name[num++] = 4;	// Сетевой адрес
				sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;	// Номер аппарата
				sMenuGlbParam.punkt[num] = 5;	sMenuGlbParam.name[num++] = 5;	// Время перезапуска
				sMenuGlbParam.punkt[num] = 19;	sMenuGlbParam.name[num++] = 19;	// Резервирование
			}			
		}
	}
	
	sMenuGlbParam.num = num;
}

/** Формирование списка параметров Защиты в зависимости от совместимости
*	@param Нет
*	@return Нет
*/
void MenuParamDefCreate(void)
{
	char num = 0;
	
	switch(TypeUdDev)
	{
		case 1:		// ПВЗ-90 
		case 2:		// АВЗК-80
		case 3:		// ПВЗУ-Е
		{
			sMenuDefParam.punkt[num++] = 0;		// Тип Защиты
			sMenuDefParam.punkt[num++] = 1;		// Тип Линии
			sMenuDefParam.punkt[num++] = 2;		// Доп. время без ман.
			sMenuDefParam.punkt[num++] = 3;		// Задержка на линии
			sMenuDefParam.punkt[num++] = 4;		// Перекрытие импульсов
			sMenuDefParam.punkt[num++] = 5;		// Загр чувствит по  РЗ
			sMenuDefParam.punkt[num++] = 7;		// Частота ПРД
			sMenuDefParam.punkt[num++] = 8;		// Частота ПРМ
		}
		break;
		
		case 4:		// ПВЗЛ
		{
			sMenuDefParam.punkt[num++] = 0;		// Тип Защиты
			sMenuDefParam.punkt[num++] = 2;		// Доп. время без ман.
			sMenuDefParam.punkt[num++] = 3;		// Задержка на линии
			sMenuDefParam.punkt[num++] = 4;		// Перекрытие импульсов
			sMenuDefParam.punkt[num++] = 5;		// Загр чувствит по  РЗ
			sMenuDefParam.punkt[num++] = 7;		// Частота ПРД
			sMenuDefParam.punkt[num++] = 8;		// Частота ПРМ
		}
		break;
		
		default:	// АВАНТ
		{
			sMenuDefParam.punkt[num++] = 0;		// Тип Защиты
			sMenuDefParam.punkt[num++] = 1;		// Тип Линии
			sMenuDefParam.punkt[num++] = 2;		// Доп. время без ман.
			sMenuDefParam.punkt[num++] = 3;		// Задержка на линии
			sMenuDefParam.punkt[num++] = 4;		// Перекрытие импульсов
			
			if (cTypeLine == 1)						// в ВЛ есть дополнительные параметры
			{
				sMenuDefParam.punkt[num++] = 5;	// Загр чувствит по  РЗ						 	
				sMenuDefParam.punkt[num++] = 6;	// Снижение уровня АК
			}
		}
	}	
	
	sMenuDefParam.num = num;
}

/** Формирование списка команд управления в зависимости от совместимости
 *	@param act действие
 *	@arg 0 обновить только пуск наладочный
 *	@arg 1 обновить полностью
 *	@return Нет
 */
void MenuUprCreate(uint8_t act)
{
	if (act == 0 )
	{
		// Только если есть защита
		if (bDef)
		{
			if (CurrentState[1] == 7)
			{
				sMenuUpr.punkt[0] = CTRL_COM_START_OFF; 
				sMenuUpr.name[0] = CTRL_NAME_START_OFF;
			}
			else
			{
				sMenuUpr.punkt[0] = CTRL_COM_START_ON; 
				sMenuUpr.name[0] = CTRL_NAME_START_ON;
			}
		}
	}
	else if (act == 1)
	{
		char num = 0;
		
		// Только если есть защита
		if (bDef)
		{
			if (CurrentState[1] == 7)
			{
				dSetUprItem(CTRL_COM_START_OFF, 	CTRL_NAME_START_OFF);
			}
			else
			{
				dSetUprItem(CTRL_COM_START_ON, 		CTRL_NAME_START_ON);
			}
		}
	
		
		switch(TypeUdDev)
		{
			case 1:		// ПВЗ-90	
			{
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				dSetUprItem(CTRL_COM_RESET_REMOTE, 		CTRL_NAME_RESET_REMOTE);	
				dSetUprItem(CTRL_COM_AC_AUTO_NORMAL,	CTRL_NAME_AC_NORMAL);
				dSetUprItem(CTRL_COM_AC_ACCELERATED,	CTRL_NAME_AC_ACCELERATED);
				dSetUprItem(CTRL_COM_AC_OFF,			CTRL_NAME_AC_OFF);
				dSetUprItem(CTRL_COM_AC_TEST,			CTRL_NAME_AC_TEST);
				dSetUprItem(CTRL_COM_AC_START,			CTRL_NAME_AC_START);
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 2:		// АВЗК-80		
			{		
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				dSetUprItem(CTRL_COM_AC_AUTO_NORMAL,	CTRL_NAME_AC_NORMAL);
				dSetUprItem(CTRL_COM_AC_ACCELERATED,	CTRL_NAME_AC_ACCELERATED);
				dSetUprItem(CTRL_COM_AC_OFF,			CTRL_NAME_AC_OFF);
				dSetUprItem(CTRL_COM_AC_TEST,			CTRL_NAME_AC_TEST);
				dSetUprItem(CTRL_COM_AC_START,			CTRL_NAME_AC_START);
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 3:		// ПВЗУ-Е
			{
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				dSetUprItem(CTRL_COM_START_REMOTE,		CTRL_NAME_START_REMOTE);
				dSetUprItem(CTRL_COM_START_REMOTE_12,	CTRL_NAME_START_REMOTE_MAN);
				dSetUprItem(CTRL_COM_AC_AUTO_NORMAL,	CTRL_NAME_AC_NORMAL);
				dSetUprItem(CTRL_COM_AC_ACCELERATED,	CTRL_NAME_AC_ACCELERATED);
				dSetUprItem(CTRL_COM_AC_CHECK, 			CTRL_NAME_AC_QUICK);
				dSetUprItem(CTRL_COM_AC_TEST,			CTRL_NAME_AC_CHECK);
				dSetUprItem(CTRL_COM_AC_OFF,			CTRL_NAME_AC_OFF);
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 4: 	// ПВЗЛ
			{
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				dSetUprItem(CTRL_COM_AC_AUTO_NORMAL,	CTRL_NAME_AC_NORMAL);
				dSetUprItem(CTRL_COM_AC_CHECK,			CTRL_NAME_AC_ONE_SIDE);
				dSetUprItem(CTRL_COM_AC_OFF,			CTRL_NAME_AC_OFF);
				dSetUprItem(CTRL_COM_RESET_REMOTE,		CTRL_NAME_AC_RESET);
				dSetUprItem(CTRL_COM_AC_TEST,			CTRL_NAME_AC_START_SELF);
				dSetUprItem(CTRL_COM_START_REMOTE_2,	CTRL_NAME_AC_START_REMOTE);
				dSetUprItem(CTRL_COM_START_REMOTE_12, 	CTRL_NAME_START_PRD);
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			default:	// АВАНТ
			{
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				
				if (cNumLine == 3)
				{
					dSetUprItem(CTRL_COM_RESET_REMOTE, 		CTRL_NAME_RESET_REMOTE_1);
					dSetUprItem(CTRL_COM_RESET_REMOTE_2,	CTRL_NAME_RESET_REMOTE_2);			
					
					if (bDef)
					{
						dSetUprItem(CTRL_COM_START_REMOTE,		CTRL_NAME_START_REMOTE_1);
						dSetUprItem(CTRL_COM_START_REMOTE_2,	CTRL_NAME_START_REMOTE_2);
						dSetUprItem(CTRL_COM_START_REMOTE_12,	CTRL_NAME_START_REMOTE_12);
						
						if (cTypeLine == 1)													
						{
							// в ВЛ есть смена АК
							dSetUprItem(CTRL_COM_AC_AUTO_ACCELERATED, 	CTRL_NAME_AC_AUTO);
							dSetUprItem(CTRL_COM_AC_ACCELERATED,		CTRL_NAME_AC_ACCELERATED);
							dSetUprItem(CTRL_COM_AC_OFF,				CTRL_NAME_AC_OFF);
						}
					}
				}
				else
				{
					dSetUprItem(CTRL_COM_RESET_REMOTE,		CTRL_NAME_RESET_REMOTE);
					
					if (bDef)
					{
						dSetUprItem(CTRL_COM_START_REMOTE,		CTRL_NAME_START_REMOTE);
						
						if (cTypeLine == 1)													
						{
							// в ВЛ есть смена АК и вызов
							dSetUprItem(CTRL_COM_AC_AUTO_ACCELERATED, 	CTRL_NAME_AC_AUTO);
							dSetUprItem(CTRL_COM_AC_ACCELERATED,		CTRL_NAME_AC_ACCELERATED);
							dSetUprItem(CTRL_COM_AC_OFF,				CTRL_NAME_AC_OFF);
							dSetUprItem(CTRL_COM_CALL,					CTRL_NAME_CALL);
						}
					}
				}
			}
		}
		
		sMenuUpr.num = num;	
	}
}


/** Формирование списка типов АК в зависимости от типа совместимости
*	@param Нет
*	@return Нет
*/
void MenuAKCreate(void)
{
	char i = 0;
	
	param4[i++] = 0;
	
	if (TypeUdDev > 0)			// ПВЗ-90, АВЗК-80, ПВЗЕ-У, ПВЗЛ 
	{	
		param4[i++] = 8;	// норм.АК
		param4[i++] = 8;	// норм.АК
	}
	else						// АВАНТ
	{
		param4[i++] = 1;	// авто.АК
		param4[i++] = 2;	// авто.АК
	}
	
	param4[i++] = 3;		// уск.АК
	param4[i++] = 4;		// выкл.АК
	
	if (TypeUdDev == 3) 		// ПВЗУ-Е
	{
		param4[i++] = 9;	// бегл.АК
		param4[i++] = 5;	// пров.АК
	}
	else if (TypeUdDev == 4)	// ПВЗЛ
	{
		param4[i++] = 10;	// однос.АК
		param4[i++] = 5;	// пров.АК
	}
	else						// АВАНТ, ПВЗ-90, АВЗК
	{
		param4[i++] = 5;	// пров.АК
		param4[i++] = 6;	// испыт.АК
	}
}

/** Формирование меню Тест
*	@param Нет
* 	@return Нет
*/
void MenuTestCreate(void)
{	
	switch(TypeUdDev)
	{
		case 1:		// ПВЗ-90
		case 2:		// АВЗК-80
		case 3:		// ПВЗУ-Е
		case 4:		// ПВЗЛ
		{
			sMenuTest.num = 1;
			sMenuTest.numTr = 1; // передача КЧ и РЗ
			sMenuTest.sT[0].type = 2;	// РЗ
			sMenuTest.sT[0].name = Menu20line2test12;
			sMenuTest.sT[0].sp = Menu20gr2;
			sMenuTest.sT[0].val = sNumGrRZ;
			sMenuTest.sT[0].num = 0;
			sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 0;
			sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 1;
		}
		break;
		default:	// АВАНТ
		{	
			if (cNumLine == 3)
			{	//трехконцевая версия пост
				sMenuTest.num = 4;
				sMenuTest.numTr = 2;	//передача КЧ и РЗ
				sMenuTest.sT[0].type = 1;	// 1 КЧ
				sMenuTest.sT[0].sp = Menu20gr1;
				sMenuTest.sT[0].name = Menu20line2test13;
				sMenuTest.sT[0].val = dNumGrCH;
				sMenuTest.sT[0].num = 0;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 0;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 1;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 2;
				
				sMenuTest.sT[1].type = 2;	// 1 РЗ
				sMenuTest.sT[1].name = Menu20line2test15;
				sMenuTest.sT[1].sp = Menu20gr2;
				sMenuTest.sT[1].val = sNumGrRZ;
				sMenuTest.sT[1].num = 0;
				sMenuTest.sT[1].punkt[sMenuTest.sT[1].num++] = 0;
				sMenuTest.sT[1].punkt[sMenuTest.sT[1].num++] = 1;
				
				sMenuTest.sT[2].type = 3;	// 2 КЧ
				sMenuTest.sT[2].sp = Menu20gr1;
				sMenuTest.sT[2].name = Menu20line2test14;
				sMenuTest.sT[2].val = dNumGrCH;
				sMenuTest.sT[2].num = 0;
				sMenuTest.sT[2].punkt[sMenuTest.sT[2].num++] = 0;
				sMenuTest.sT[2].punkt[sMenuTest.sT[2].num++] = 1;
				sMenuTest.sT[2].punkt[sMenuTest.sT[2].num++] = 2;
				
				sMenuTest.sT[3].type = 4;	// 1 РЗ
				sMenuTest.sT[3].name = Menu20line2test16;
				sMenuTest.sT[3].sp = Menu20gr2;
				sMenuTest.sT[3].val = sNumGrRZ;
				sMenuTest.sT[3].num = 0;
				sMenuTest.sT[3].punkt[sMenuTest.sT[3].num++] = 0;
				sMenuTest.sT[3].punkt[sMenuTest.sT[3].num++] = 1;
				
			}
			else
			{	//двухконцевая версия
				sMenuTest.num = 2;
				sMenuTest.numTr = 2;	//передача КЧ и РЗ
				sMenuTest.sT[0].type = 1;	// КЧ
				sMenuTest.sT[0].num = 0;
				sMenuTest.sT[0].sp = Menu20gr1;
				sMenuTest.sT[0].name = Menu20line2test11;
				sMenuTest.sT[0].val = dNumGrCH;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 0;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 1;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 2;
				
				sMenuTest.sT[1].type = 2;	// РЗ
				sMenuTest.sT[1].name = Menu20line2test12;
				sMenuTest.sT[1].sp = Menu20gr2;
				sMenuTest.sT[1].val = sNumGrRZ;
				sMenuTest.sT[1].num = 0;
				sMenuTest.sT[1].punkt[sMenuTest.sT[1].num++] = 0;
				sMenuTest.sT[1].punkt[sMenuTest.sT[1].num++] = 1;
			}
		}
	}
}


static void Menu_Start(void)
{
	MenuLevel = LVL_START;
	LCDbufClMenu();
	LCDtimerNew=1;
	ShiftMenu=0;
	MaxDisplayLine=0;
	ValueVsRange=0;
	NumberCom=1;
	if (bAllDevice) MaxShiftMenu=1;
	else MaxShiftMenu=0;
}

static void Menu_Second(void)
{
	MenuLevel = LVL_MENU;
	LCDbufClMenu();
	LCDtimerNew=1;
	ShiftMenu=0;
	MaxShiftMenu=3;
	MaxDisplayLine=3;
	LCD2new=1;
}

static void Menu_DataTime(void)
{
	MenuLevel = LVL_DATA_TIME;
	LCDbufClMenu();
	LCD2new=1;
}

static void Menu_Journal(void)
{
	MenuLevel = LVL_JOURNAL;
	LCDbufClMenu();
	ShiftMenu=0;
	MaxDisplayLine=3;
	if (sArchive.NumDev>2) MaxShiftMenu=1;
	else MaxShiftMenu=0;
	sArchive.Data[12]=0;
	FuncClearCharLCD(2,1,40);
	sArchive.RecCount=0;
	LCD2new=1;
}

static void Menu_Setup(void)
{
	MenuLevel = LVL_SETUP;
	LCDbufClMenu();
	ShiftMenu=0;
	MaxDisplayLine=3;
	MaxShiftMenu=1;
	if ((cNumComR>0)&&(CurrentState[2]<0x04)) MaxShiftMenu=0;   //если есть приемник, и он не в Тест
	if ((cNumComT>0)&&(CurrentState[4]<0x04)) MaxShiftMenu=0;  //если есть передатчик, и он не в Тест
	if ((bDef)&&(CurrentState[0]<0x04)) MaxShiftMenu=0; //если есть Пост, и он не в Тест
	LCD2new=1;
}

//меню/просмотр параметров
static void Menu_ParamSetup(eMENUlvl Menu)
{
	MenuLevel = Menu; // 6 и 12
	LCDbufClMenu();
	ShiftMenu=0;
	ValueVsRange=0;
	NumberCom=1;
	if (LineInMenu6 <= 3){ //если 3 или менее строк
		MaxShiftMenu=0;
		MaxDisplayLine = LineInMenu6;
	}else{
		MaxShiftMenu = LineInMenu6-3;
		MaxDisplayLine=3;
	}
	LCD2new=1;
}

static void Menu_ParamSetup_Def(eMENUlvl lvl)
{
  	MenuLevel = lvl; 
  	LCDbufClMenu();
  	ShiftMenu = 0;
  	MaxDisplayLine = 1;
  	MaxShiftMenu = sMenuDefParam.num - 1;
  	LCD2new = 1;
  	cNumParam = 0x20;
}

static void Menu_ParamSetup_Prm(eMENUlvl lvl)
{
	MenuLevel = lvl; 
	LCDbufClMenu();
	ShiftMenu=0;
	MaxDisplayLine = 1;
	NumberCom = 1;
	MaxShiftMenu = NumParamPrm - 1 - 1;	// на данный момент нет последнего пар-ра
	LCD2new=1;
	cNumParam=0x40;
}

static void Menu_ParamSetup_Prd(eMENUlvl lvl)
{
	MenuLevel = lvl; 
	LCDbufClMenu();
	ShiftMenu=0;
	MaxShiftMenu=4;
	MaxDisplayLine=1;
	MaxShiftMenu=NumParamPrd-1;
	LCD2new=1;
	cNumParam=0x60;
}

static void Menu_ParamSetup_Global(eMENUlvl lvl)
{
  	MenuLevel = lvl; 
  	LCDbufClMenu();
  	ShiftMenu = 0;
  	MaxDisplayLine = 1;
  	NumberCom = 1;
  	MaxShiftMenu = sMenuGlbParam.num - 1;
  	LCD2new = 1;
  	cNumParam = 0x80;
}

static void Menu_Setup_Regime(void)
{
	MenuLevel = LVL_REGIME;
	LCDbufClMenu();
	ShiftMenu=0;
	MaxShiftMenu=0;
	MaxDisplayLine=1;
	LCD2new=1;
}

static void Menu_Protocol(void)
{
	MenuLevel = LVL_PROTOCOL;
	LCDbufClMenu();
	ShiftMenu=0;
	MaxShiftMenu=0;
	MaxDisplayLine=1;
	LCD2new=1;
}

static void Menu_Info(void)
{
	MenuLevel = LVL_INFO;
	LCDbufClMenu();
	ShiftMenu=0;
	MaxShiftMenu=3;
	MaxDisplayLine=1;
	LCD2new=1;
}

static void Menu_Setup_Test(void)
{
	if ( (cNumComR) && (CurrentState[2] < 0x04) )
		return;   //если есть приемник, и он не в Тест
  	if ( (cNumComT) && (CurrentState[4]  <0x04) )
		return;  //если есть передатчик, и он не в Тест
  	if ( (bDef) && (CurrentState[0] < 0x04) )
	 	return;  //если есть Защита, и она не в Тест
	
   	MenuLevel = LVL_TEST;
   	LCDbufClMenu();
   	ShiftMenu = 0;
	MaxDisplayLine = 3;
	MaxShiftMenu = sMenuTest.numTr - 1;
	
   	if ((cNumComR>0)&&(CurrentState[2]==5)) MaxShiftMenu=0;   //если есть приемник, и он в Тест2
   	if ((cNumComT>0)&&(CurrentState[4]==5)) MaxShiftMenu=0;  //если есть передатчик, и он в Тест2
   	if ((bDef)&&(CurrentState[0]==5)) MaxShiftMenu=0;  //если есть Защита, и она в Тест2
   	LCD2new=1;
}

static void PressInMenuJournal(char Key)
{  //нажатие в меню Журна -> переход в подпункты журнала
	Key-=0x31;
	if (sArchive.NumDev>=Key)
	{ //если есть устройство
		MenuLevel = LVL_JRN_VIEW;
		LCDbufClMenu();
		ShiftMenu=0;
		MaxDisplayLine=2;
		sArchive.CurrDev=Key;
		sArchive.RecCount=0;  //для начала сбросим кол-во данных
		
		LCD2new=1;
	}
}

static void Menu_Upr(void)
{
	MenuLevel = LVL_UPR;
  	LCDbufClMenu();
  	ShiftMenu = 0;
  	MaxDisplayLine = 3;
	if (sMenuUpr.num > 3)
  		MaxShiftMenu = sMenuUpr.num - 3;
	else
		MaxShiftMenu = 0;
  	LCD2new=1;
}

static void PressInMenuDataTime(char Key)
{ //нажатеи в меню Дата/Время
	WorkRate=0x03;
	InputParameter=Key;
	if (Key==1) ChangeMass=DataLCD;
	else ChangeMass=TimeLCD;
	Discret=1;  //дискрет 1
	for (char i=0; i<=8; i++) InputDataTime[i]=ChangeMass[i];
}

/** Выбор пункта в меню Установить
*	@param key Код нажатой кнопки
*	@return Нет
*/
static void PressInMenuReset(char key)
{  
	if (key > sMenuUpr.num)
		return;
	
	char value = sMenuUpr.punkt[key];
	
	if (value & 0x80)
	{
		// управление
		TrValue = 0x72;
	}
	else
	{
		// автоконтроль
		TrValue = 0x8A;
	}
	
	SelectValue = value & 0x7F;
	ShiftMenu = key;
  	WorkRate = 2; 		
	MaxValue = MinValue = InputSelectValue = 0;
  	MassSelectValue = fReset; 
}


