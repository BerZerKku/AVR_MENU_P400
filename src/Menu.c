/*****************************************
переходы между меню
*****************************************/
#include "Menu.h"

#define dSetUprItem(com,nameItem) sMenuUpr.punkt[num] = com; sMenuUpr.name[num++] = nameItem 
#define dSetACItem(com,nameItem)  sMenuAC.punkt[num] = com; sMenuAC.name[num++] = nameItem 

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
		case 8: 	// ПВЗ
		{
			sMenuGlbParam.punkt[num] = 0; 	sMenuGlbParam.name[num++] = 0;		// Совместимость
			sMenuGlbParam.punkt[num] = 2; 	sMenuGlbParam.name[num++] = 2;		// Uвых номинальное
			sMenuGlbParam.punkt[num] = 4;	sMenuGlbParam.name[num++] = 4;		// Сетевой адрес
			sMenuGlbParam.punkt[num] = 6;	sMenuGlbParam.name[num++] = 6;		// Частота
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
			sMenuGlbParam.punkt[num] = 6;	sMenuGlbParam.name[num++] = 6;		// Частота
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
			sMenuGlbParam.punkt[num] = 21; 	sMenuGlbParam.name[num++] = 21;		// Период беглого режима АК
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.periodAC[i] = MenuAllPorog[i];
				if (MenuAllPorog[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[num] = 22; 	sMenuGlbParam.name[num++] = 22;		/// Период повтора беглого режима АК
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.periodACre[i] = MenuAllPorog[i];
				if (MenuAllPorog[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[num] = 23; 	sMenuGlbParam.name[num++] = 23;		// Коррекция времени АК
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.timeCorrAC[i] = MenuAllTimeCorrAC[i];
				if (MenuAllTimeCorrAC[i] == 0)
					break;
			}
		}
		break;
		
		case 4:		// ПВЗЛ
		{
			sMenuGlbParam.punkt[num] = 0; 	sMenuGlbParam.name[num++] = 0;		// Совместимость
			sMenuGlbParam.punkt[num] = 2; 	sMenuGlbParam.name[num++] = 2;		// Uвых номинальное
			sMenuGlbParam.punkt[num] = 4;	sMenuGlbParam.name[num++] = 4;		// Сетевой адрес
			sMenuGlbParam.punkt[num] = 6;	sMenuGlbParam.name[num++] = 6;		// Частота
			sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;		// Номер аппарата
			sMenuGlbParam.punkt[num] = 8; 	sMenuGlbParam.name[num++] = 8;		// Контроль вых.сигнала
			sMenuGlbParam.punkt[num] = 9; 	sMenuGlbParam.name[num++] = NumParamGlb; // Порог ПРЕДУПР по РЗ
			sMenuGlbParam.punkt[num] = 20;	sMenuGlbParam.name[num++] = 20;		// Снижение ответа АК
			sMenuGlbParam.punkt[num] = 11; 	sMenuGlbParam.name[num++] = 11;		// Коррекция напряжения
			sMenuGlbParam.punkt[num] = 12; 	sMenuGlbParam.name[num++] = 12;		// Коррекция тока
		}
		break;
		
		case 7 : 	// ПВЗУ
		{
			sMenuGlbParam.punkt[num] = 0; 	sMenuGlbParam.name[num++] = 0;		// Совместимость
			sMenuGlbParam.punkt[num] = 2; 	sMenuGlbParam.name[num++] = 2;		// Uвых номинальное
			sMenuGlbParam.punkt[num] = 4;	sMenuGlbParam.name[num++] = 4;		// Сетевой адрес
			sMenuGlbParam.punkt[num] = 6;	sMenuGlbParam.name[num++] = 6;		// Частота
			sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;		// Номер аппарата
			sMenuGlbParam.punkt[num] = 8; 	sMenuGlbParam.name[num++] = 8;		// Контроль вых.сигнала
			sMenuGlbParam.punkt[num] = 9; 	sMenuGlbParam.name[num++] = NumParamGlb; // Порог ПРЕДУПР по РЗ
			sMenuGlbParam.punkt[num] = 15; 	sMenuGlbParam.name[num++] = 15;		// Допустимые провалы
			sMenuGlbParam.punkt[num] = 23; 	sMenuGlbParam.name[num++] = 23;		// Коррекция времени АК
			sMenuGlbParam.punkt[num] = 11; 	sMenuGlbParam.name[num++] = 11;		// Коррекция напряжения
			sMenuGlbParam.punkt[num] = 12; 	sMenuGlbParam.name[num++] = 12;		// Коррекция тока
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.timeCorrAC[i] = MenuAllTimeCorrAC[i];
				if (MenuAllTimeCorrAC[i] == 0)
					break;
			}
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
				if (cNumComR > 0)
					sMenuGlbParam.punkt[num] = 5;	sMenuGlbParam.name[num++] = 5;	// Время перезапуска
				sMenuGlbParam.punkt[num] = 19;	sMenuGlbParam.name[num++] = 19;	// Резервирование
			}			
		}
	}
	
	sMenuGlbParam.num = num;
}

/** Формирование списка параметров Защиты в зависимости от совместимости
 *	В оптике совместимостей нет, поэтому устанавливаются пар-ры АВАНТа
 *	@param Нет
 *	@return Нет
 */
void MenuParamDefCreate(void)
{
	char num = 0;
	char type = TypeUdDev;
	
	// В оптике нет совместимостей
	if (cTypeLine == 2)
		type = 0;
	
	switch(type)
	{
		case 1:		// ПВЗ-90 
		case 2:		// АВЗК-80
		case 3:		// ПВЗУ-Е
		case 8:
		{
			sMenuDefParam.punkt[num++] = 0;		// Тип Защиты
			sMenuDefParam.punkt[num++] = 1;		// Тип Линии
			sMenuDefParam.punkt[num++] = 2;		// Доп. время без ман.
//			sMenuDefParam.punkt[num++] = 3;		// Задержка на линии
//			sMenuDefParam.punkt[num++] = 4;		// Перекрытие импульсов
			sMenuDefParam.punkt[num++] = 5;		// Загр чувствит по  РЗ
			sMenuDefParam.punkt[num++] = 7;		// Частота ПРД
			sMenuDefParam.punkt[num++] = 8;		// Частота ПРМ
		}
		break;
		
		case 4:		// ПВЗЛ
		{
			sMenuDefParam.punkt[num++] = 0;		// Тип Защиты
			sMenuDefParam.punkt[num++] = 2;		// Доп. время без ман.
//			sMenuDefParam.punkt[num++] = 3;		// Задержка на линии
//			sMenuDefParam.punkt[num++] = 4;		// Перекрытие импульсов
			sMenuDefParam.punkt[num++] = 5;		// Загр чувствит по  РЗ
			sMenuDefParam.punkt[num++] = 7;		// Частота ПРД
			sMenuDefParam.punkt[num++] = 8;		// Частота ПРМ
		}
		break;
		
		case 7: 	// ПВЗУ
		{
			sMenuDefParam.punkt[num++] = 0;		// Тип Защиты
			sMenuDefParam.punkt[num++] = 1;		// Тип Линии
			sMenuDefParam.punkt[num++] = 2;		// Доп. время без ман.
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
//			sMenuDefParam.punkt[num++] = 3;		// Задержка на линии
//			sMenuDefParam.punkt[num++] = 4;		// Перекрытие импульсов
			if (cTypeLine == 1)						// в ВЛ есть дополнительные параметры
			{
				sMenuDefParam.punkt[num++] = 5;	// Загр чувствит по  РЗ						 	
				sMenuDefParam.punkt[num++] = 6;	// Снижение уровня АК
			}
		}
	}	
	sMenuDefParam.punkt[num++] = 9;	// Сдвиг пер.фронта ПРД
	sMenuDefParam.punkt[num++] = 10;// Сдвиг зад.фронта ПРД
	sMenuDefParam.punkt[num++] = 11;// Сдвиг ПРМ
	sMenuDefParam.punkt[num++] = 12;// Сдвиг ВЧ ПРД от ПУСК
	
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
			
			if (cNumLine == 3) {
				uint8_t num = MenuAllNumDevice[0];
				if (num != '?') {
					num -= '0';
					
					for(uint8_t i = 0; i < sMenuUpr.num; i++) {
						if ((sMenuUpr.name[i] == CTRL_NAME_START_REMOTE_1) ||
							(sMenuUpr.name[i] == CTRL_NAME_START_REMOTE_2))
						{
							sMenuUpr.name[i] = (num == 1) ? 
								CTRL_NAME_START_REMOTE_2 :
								CTRL_NAME_START_REMOTE_1;
							sMenuUpr.name[i + 1] = (num == 3) ? 
								CTRL_NAME_START_REMOTE_2 :
								CTRL_NAME_START_REMOTE_3;		
							break;
						}
					}
					
					for(uint8_t i = 0; i < sMenuUpr.num; i++) {
						if ((sMenuUpr.name[i] == CTRL_NAME_RESET_REMOTE_1) ||
							(sMenuUpr.name[i] == CTRL_NAME_RESET_REMOTE_2))
						{
							sMenuUpr.name[i] = (num == 1) ? 
								CTRL_NAME_RESET_REMOTE_2 :
								CTRL_NAME_RESET_REMOTE_1;
							sMenuUpr.name[i + 1] = (num == 3) ? 
								CTRL_NAME_RESET_REMOTE_2 :
								CTRL_NAME_RESET_REMOTE_3;		
							break;
						}
					}
					
					for(uint8_t i = 0; i < sMenuUpr.num; i++) {
						if ((sMenuUpr.name[i] == CTRL_NAME_REMOTE_MAN_1) ||
							(sMenuUpr.name[i] == CTRL_NAME_REMOTE_MAN_2))
						{
							sMenuUpr.name[i] = (num == 1) ? 
								CTRL_NAME_REMOTE_MAN_2 :
								CTRL_NAME_REMOTE_MAN_1;
							sMenuUpr.name[i + 1] = (num == 3) ? 
								CTRL_NAME_REMOTE_MAN_2 :
								CTRL_NAME_REMOTE_MAN_3;		
							break;
						}
					}
				}
			} else if ((cNumLine == 4) && (TypeUdDev == 3)) {
				uint8_t num = MenuAllNumDevice[0];
				if (num != '?') {
					num -= '0';
					for(uint8_t i = 0; i < sMenuUpr.num; i++) {
						if ((sMenuUpr.name[i] == CTRL_NAME_START_REMOTE_1) ||
							(sMenuUpr.name[i] == CTRL_NAME_START_REMOTE_2))
						{
							sMenuUpr.name[i] = (num == 1) ? 
							CTRL_NAME_START_REMOTE_2 :
							CTRL_NAME_START_REMOTE_1;
							sMenuUpr.name[i + 1] = (num <= 2) ? 
							CTRL_NAME_START_REMOTE_3 :
							CTRL_NAME_START_REMOTE_2;		
							sMenuUpr.name[i + 2] = (num == 4) ? 
							CTRL_NAME_START_REMOTE_3 :
							CTRL_NAME_START_REMOTE_4;
							break;
						}
					}
					
					for(uint8_t i = 0; i < sMenuUpr.num; i++) {
						if ((sMenuUpr.name[i] == CTRL_NAME_REMOTE_MAN_1) ||
							(sMenuUpr.name[i] == CTRL_NAME_REMOTE_MAN_2))
						{
							sMenuUpr.name[i] = (num == 1) ? 
							CTRL_NAME_REMOTE_MAN_2 :
							CTRL_NAME_REMOTE_MAN_1;
							sMenuUpr.name[i + 1] = (num <= 2) ? 
							CTRL_NAME_REMOTE_MAN_3 :
							CTRL_NAME_REMOTE_MAN_2;		
							sMenuUpr.name[i + 2] = (num == 4) ? 
							CTRL_NAME_REMOTE_MAN_3 :
							CTRL_NAME_REMOTE_MAN_4;	
							break;
						}
					}
				}
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
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 2:		// АВЗК-80		
			{		
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 3:		// ПВЗУ-Е
			{
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				if (cNumLine == 3) {
					dSetUprItem(CTRL_COM_START_REMOTE,	CTRL_NAME_START_REMOTE_1);
					dSetUprItem(CTRL_COM_START_REMOTE_2,CTRL_NAME_START_REMOTE_2);
//					dSetUprItem(CTRL_COM_START_REMOTE_12,CTRL_NAME_START_REMOTE_12);
					dSetUprItem(CTRL_COM_MAN_REMOTE_1,	CTRL_NAME_REMOTE_MAN_1);
					dSetUprItem(CTRL_COM_MAN_REMOTE_2,	CTRL_NAME_REMOTE_MAN_2);
					dSetUprItem(CTRL_COM_MAN_REMOTE_12,	CTRL_NAME_REMOTE_MAN_12);
				} else if (cNumLine > 3) {
					dSetUprItem(CTRL_COM_START_REMOTE,	CTRL_NAME_START_REMOTE_1);
					dSetUprItem(CTRL_COM_START_REMOTE_2,CTRL_NAME_START_REMOTE_2);
					dSetUprItem(CTRL_COM_START_REMOTE_3,CTRL_NAME_START_REMOTE_3);
//					dSetUprItem(CTRL_COM_START_REMOTE_12,CTRL_NAME_START_REMOTE_12);
					dSetUprItem(CTRL_COM_MAN_REMOTE_1,	CTRL_NAME_REMOTE_MAN_1);
					dSetUprItem(CTRL_COM_MAN_REMOTE_2,	CTRL_NAME_REMOTE_MAN_2);
					dSetUprItem(CTRL_COM_MAN_REMOTE_3,	CTRL_NAME_REMOTE_MAN_3);
					dSetUprItem(CTRL_COM_MAN_REMOTE_12,	CTRL_NAME_REMOTE_MAN_12);
				} else {
					dSetUprItem(CTRL_COM_START_REMOTE,	CTRL_NAME_START_REMOTE);
					dSetUprItem(CTRL_COM_MAN_REMOTE_1,	CTRL_NAME_START_REMOTE_MAN);	
					dSetUprItem(CTRL_COM_MAN_REMOTE_12,	CTRL_NAME_REMOTE_MAN_12);
				}
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 4: 	// ПВЗЛ
			{
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				dSetUprItem(CTRL_COM_START_REMOTE_2,	CTRL_NAME_AC_START_REMOTE);
				dSetUprItem(CTRL_COM_START_REMOTE_12, 	CTRL_NAME_START_PRD);
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 7: 	// ПВЗУ
			{	
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 8:		// ПВЗ
			{
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
			}
			break;
			
			default:	// АВАНТ
			{
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				
				if (cNumLine == 3)
				{
					dSetUprItem(CTRL_COM_RESET_REMOTE, 	CTRL_NAME_RESET_REMOTE_1);
					dSetUprItem(CTRL_COM_RESET_REMOTE_2,CTRL_NAME_RESET_REMOTE_2);			
					
					if (bDef)
					{
						dSetUprItem(CTRL_COM_START_REMOTE,	 CTRL_NAME_START_REMOTE_1);
						dSetUprItem(CTRL_COM_START_REMOTE_2, CTRL_NAME_START_REMOTE_2);
						dSetUprItem(CTRL_COM_START_REMOTE_12,CTRL_NAME_START_REMOTE_12);
					}
				}
				else
				{
					dSetUprItem(CTRL_COM_RESET_REMOTE, CTRL_NAME_RESET_REMOTE);
					
					if (bDef)
					{
						dSetUprItem(CTRL_COM_START_REMOTE, CTRL_NAME_START_REMOTE);
						
						if (cTypeLine == 1)													
						{
							// в ВЛ есть и вызов
							dSetUprItem(CTRL_COM_CALL, CTRL_NAME_CALL);
						}
					}
				}
			}
		}
		
		sMenuUpr.num = num;	
	}
}

/** Формирование списка команд управления АК в зависимости от совместимости.
 *	
 *	@return Нет
 */
void MenuACCreate(void)
{
	char num = 0;
	
	switch(TypeUdDev)
	{
		case 1:		// ПВЗ-90	
		{	
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_ACCELERATED,			CTRL_NAME_AC_ACCELERATED);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_TEST);
			dSetACItem(CTRL_COM_AC_START,				CTRL_NAME_AC_START);
		}
		break;
		
		case 2:		// АВЗК-80		
		{		
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_ACCELERATED,			CTRL_NAME_AC_ACCELERATED);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_TEST);
			dSetACItem(CTRL_COM_AC_START,				CTRL_NAME_AC_START);
		}
		break;
		
		case 3:		// ПВЗУ-Е
		{
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_ACCELERATED,			CTRL_NAME_AC_ACCELERATED);
			dSetACItem(CTRL_COM_AC_CHECK, 				CTRL_NAME_AC_QUICK);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_CHECK);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
		}
		break;
		
		case 4: 	// ПВЗЛ
		{
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_CHECK,				CTRL_NAME_AC_ONE_SIDE);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
			dSetACItem(CTRL_COM_RESET_REMOTE,			CTRL_NAME_AC_RESET);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_START_SELF);
		}
		break;

		case 7: 	// ПВЗУ
		{
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_ACCELERATED,			CTRL_NAME_AC_ACCELERATED);
			dSetACItem(CTRL_COM_AC_CHECK, 				CTRL_NAME_AC_QUICK);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_CHECK);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
		}
		break;
		
		case 8:		// ПВЗ
		{
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_ACCELERATED,			CTRL_NAME_AC_ACCELERATED);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_START);
		}
		break;
		
		default:	// АВАНТ
		{
			if (cTypeLine == 1)													
			{
				// в ВЛ есть смена АК и вызов
				dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,CTRL_NAME_AC_AUTO);
				dSetACItem(CTRL_COM_AC_ACCELERATED,		CTRL_NAME_AC_ACCELERATED);
				dSetACItem(CTRL_COM_AC_OFF,				CTRL_NAME_AC_OFF);
			}
		}
	}
	
	sMenuAC.num = num;	
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
	
	if ((TypeUdDev == 3) || (TypeUdDev == 7))	// ПВЗУ-Е
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
	uint8_t num = 0;
	
	// сбросим кол-во имеющихся групп сигналов
	sMenuTest.gr_items_max = 0;
	
	// Наличие сигналов группы 1 определяется:
	// В оптике - только КЧ1
	// В ВЧ чистый пост, совместимость не АВАНТ - нет сигналов
	// В ВЧ 2-концевой совместимость АВАНТ Р400 - КЧ1, КЧ2
	// В ВЧ 3-концевой совместимость АВАНТ Р400 - КЧ1, КЧ2, КЧ3, КЧ4
	//
	// Далее добавляются коды команд, при их наличии
	// при этом могут быть только КЧ1, КЧ2
	
	sMenuTest.cf_val = SIGN_ERROR;
	num = 0;
	if ( (cNumComR != 0) || (cNumComT != 0) || (TypeUdDev == 0) )
	{		
		uint8_t num_com = (cNumComR > cNumComR) ? cNumComR : cNumComT;
		
		// Добавим Группу 1
		sMenuTest.gr_items[sMenuTest.gr_items_max++] = 1;
		
		sMenuTest.cf_items[num++] = SIGN_OFF;
		sMenuTest.cf_items[num++] = SIGN_CF1;
		
		// в оптике есть только КЧ1
		// в 2-х концевой ВЧ КЧ1, КЧ2
		// в 3-х концевой ВЧ КЧ1, КЧ2, КЧ3, КЧ4
		if (cTypeLine != 2)
		{
			sMenuTest.cf_items[num++] = SIGN_CF2;
			
			if (cNumLine == 3)
			{
				sMenuTest.cf_items[num++] = SIGN_CF3;
				sMenuTest.cf_items[num++] = SIGN_CF4;
			}
		}
		
		// добление команд, при их наличии
		for(char i = 0 ; i < num_com; i++)
		{
			sMenuTest.cf_items[num++] = SIGN_COM1 + i;
		}
	}
	sMenuTest.cf_items_max = num;
	
	// Наличие сигнала защиты, определяется только наличием поста
	sMenuTest.def_val = SIGN_ERROR;
	num = 0;
	if (bDef)
	{
		// добавим Группу 2
		sMenuTest.gr_items[sMenuTest.gr_items_max++] = 2;
		
		sMenuTest.def_items[num++] = SIGN_OFF;
		sMenuTest.def_items[num++] = SIGN_DEF;	
	}
	sMenuTest.def_items_max = num;
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
	MaxShiftMenu=4;
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
	MaxShiftMenu=4;
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
	MaxShiftMenu = sMenuTest.gr_items_max - 1;
	
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

static void Menu_AC(void)
{
	MenuLevel = LVL_AC;
  	LCDbufClMenu();
  	ShiftMenu = 0;
  	MaxDisplayLine = 3;
	if (sMenuAC.num > 3)
  		MaxShiftMenu = sMenuAC.num - 3;
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
	if (key >= sMenuUpr.num)
		return;
	
	char value = sMenuUpr.punkt[key];
	
	TrValue = (value & 0x80) ? 	 0x72 : 0x8A;
	
	SelectValue = value & 0x7F;
	ShiftMenu = key;
  	WorkRate = 2; 		
	MaxValue = MinValue = InputSelectValue = 0;
  	MassSelectValue = fReset; 
}

/** Выбор пункта в меню Автоконтроль
*	@param key Код нажатой кнопки
*	@return Нет
*/
static void PressInMenuAC(char key)
{  	
	key--;
	if (key >= sMenuAC.num)
		return;
	
	char value = sMenuAC.punkt[key];
	
	TrValue = (value & 0x80) ? 	 0x72 : 0x8A;
	
	SelectValue = value & 0x7F;
	ShiftMenu = key;
  	WorkRate = 2; 		
	MaxValue = MinValue = InputSelectValue = 0;
  	MassSelectValue = fReset;  
}

