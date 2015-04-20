#ifndef __MY_FLASH
#define __MY_FLASH

#include "MyDef.h"
#include "Menu.h"

__flash unsigned char fNoIzmI[] = "I1= --- ";
__flash unsigned char fAC_0[] = "ошиб.АК ";
__flash unsigned char fAC_1[] = "авто.АК ";
__flash unsigned char fAC_2[] = "авто.АК ";
__flash unsigned char fAC_3[] = "уск.АК  ";
__flash unsigned char fAC_4[] = "выкл.АК ";
__flash unsigned char fAC_5[] = "пров.АК ";
__flash unsigned char fAC_6[] = "испыт.АК";
__flash unsigned char fAC_7[] = "пуск АК ";
__flash unsigned char fAC_8[] = "норм.АК ";
__flash unsigned char fAC_9[] = "бегл.АК ";
__flash unsigned char fAC_10[]= "однос.АК";
__flash unsigned __flash char *flAutoContorl[] = 
{
	fAC_0,
	fAC_1,
	fAC_2,
	fAC_3,
	fAC_4,
	fAC_5,
	fAC_6,
	fAC_7,
	fAC_8,
	fAC_9,
	fAC_10
};
__flash unsigned char fAC1_0[] = "ошиб.";
__flash unsigned char fAC1_1[] = "авто ";
__flash unsigned char fAC1_2[] = "авто ";
__flash unsigned char fAC1_3[] = "уск. ";
__flash unsigned char fAC1_4[] = "выкл.";
__flash unsigned char fAC1_5[] = "пров.";
__flash unsigned char fAC1_6[] = "испыт";
__flash unsigned char fAC1_7[] = "пуск ";
__flash unsigned char fAC1_8[] = "норм.";
__flash unsigned char fAC1_9[] = "бегл.";
__flash unsigned char fAC1_10[]= "однос";
__flash unsigned __flash char *flAutoContorl1[] =
{
	fAC1_0,
	fAC1_1,
	fAC1_2,
	fAC1_3,
	fAC1_4,
	fAC1_5,
	fAC1_6,
	fAC1_7,
	fAC1_8,
	fAC1_9,
	fAC1_10
};

__flash unsigned char fSinh_0[] = "ошиб.СХ ";
__flash unsigned char fSinh_1[] = "норм.СХ ";
__flash unsigned char fSinh_2[] = "уск.СХ  ";
__flash unsigned __flash char *flAutoSinch[]={fSinh_0, fSinh_1, fSinh_2};
__flash unsigned char fAk[] = "АК-";

__flash unsigned char LCDavarNoUSP[] =	"Нет связи с БСП     ";
__flash unsigned char fNoReadVers[] =	"  Инициализация     ";

__flash unsigned char Menu21[] = "1.Журнал.";
__flash unsigned char Menu22[] = "2.Дата/время.";
__flash unsigned char Menu23[] = "3.Управление.";
__flash unsigned char Menu24[] = "4.Установить.";
__flash unsigned char Menu25[] = "5.Просмотр парам.";
__flash unsigned char Menu26[] = "6.Автоконтроль.";
__flash unsigned char Menu27[] = "7.Протокол.";
__flash unsigned  __flash char *Menu2point[] = 
{
	Menu21,
	Menu22,
	Menu23,
	Menu24,
	Menu25,
	Menu26,
	Menu27
};

__flash unsigned char Menu31[] = "1. Дата.            ";
__flash unsigned char Menu32[] = "2. Время.           ";

//Архивы
__flash unsigned char Archive[] 	=	"Журнал ";
__flash unsigned char ArchiveEvent[]=	"событий";
__flash unsigned char ArchiveDef[] 	= 	"защиты";
__flash unsigned char ArchivePrm[] 	= 	"приемника";
__flash unsigned char ArchivePrd[] 	= 	"передатчика";
__flash unsigned __flash char *Menu4point[] = 
{
	ArchiveEvent,
	ArchivePrd,
	ArchivePrm,
	ArchiveDef
};
__flash unsigned char Menu21event[] =	"События.";
__flash unsigned char Menu2xRdArch[] = 	"Чтение архива.";

__flash unsigned char ArchPrm[] = "ПМ";
__flash unsigned char ArchPrd[] = "ПД";
__flash unsigned char ArchEvt[] = "СБ";
__flash unsigned char ArchDef[] = "ЗЩ";
__flash unsigned __flash char *Menu21e[]={ArchEvt, ArchPrd, ArchPrm, ArchDef};

__flash unsigned char Menu21g[] = "ОБЩ";

__flash unsigned char ArchEv11[] = "Перезапуск";
__flash unsigned char ArchEv12[] = "Изм.режима";
__flash unsigned char ArchEv13[] = "Потеря КЧ ";
__flash unsigned char ArchEv14[] = "Восст. КЧ ";
__flash unsigned char ArchEv15[] = "Нет КЧ 5с ";
__flash unsigned char ArchEv16[] = "Прев.д.  к";
__flash unsigned char ArchEv17[] = "Блок.к.  к";
__flash unsigned char ArchEv20[] = "Выключение";
__flash unsigned __flash char *Menu21ev[] = 
{
	ArchEv11,
	ArchEv12,
	ArchEv13,
	ArchEv14,
	ArchEv15,
	ArchEv16,
	ArchEv17,
	ArchEv20
};
__flash unsigned char ArchEvV[]		=	"Перез.";
__flash unsigned char ArchEvV1[] 	=	"Перезап ";
__flash unsigned char ArchEvStart[] =	"Начало ";
__flash unsigned char ArchEvEnd[] 	= 	"Конец ";
__flash unsigned char ArchEvCom[] 	=	"команды";


__flash unsigned char Menu51[] =	"1.Режим.";
__flash unsigned char Menu52[] =	"2.Параметры.";
__flash unsigned char Menu53[] = 	"3.Пароль.";
__flash unsigned char Menu54[] =	"4.Тест.";
__flash unsigned __flash char* Menu5point[] = {Menu51, Menu52, Menu53, Menu54};

__flash unsigned char Menu61[] =	"Защита.";
__flash unsigned char Menu62[] =	"Приемник.";
__flash unsigned char Menu63[] =	"Передатчик.";
__flash unsigned char Menu64[] =	"Общие.";
__flash unsigned char Menu62_1[] =	"Приемник 1.";
__flash unsigned char Menu62_2[] =	"Приемник 2.";

__flash unsigned __flash char *Menu6point1[] = {Menu61, Menu64}; 				//только пост
__flash unsigned __flash char *Menu6point2[] = {Menu62, Menu63, Menu64};  		//только команды
__flash unsigned __flash char *Menu6point3[] = {Menu61, Menu62, Menu63, Menu64};//все есть

//Параметры Поста
__flash unsigned char Menu70[] =	"Тип Защиты";
__flash unsigned char Menu71[] =	"Тип Линии";
__flash unsigned char Menu72[] =	"Доп. время без ман.";
__flash unsigned char Menu73[] =	"Задержка на линии   ";
__flash unsigned char Menu74[] =	"Перекрытие импульсов";
__flash unsigned char Menu75[] =	"Загр чувствит по  РЗ";
__flash unsigned char Menu76[] =	"Снижение уровня АК  ";
__flash unsigned char Menu77[] =	"Частота ПРД";
__flash unsigned char Menu78[] =	"Частота ПРМ";
__flash unsigned char Menu79[] = 	"Сдвиг пер.фронта ПРД";
__flash unsigned char Menu710[] = 	"Сдвиг зад.фронта ПРД";
__flash unsigned char Menu711[] = 	"Сдвиг ПРМ";
__flash unsigned char Menu712[] = 	"Сдвиг ВЧ ПРД от ПУСК";
__flash unsigned __flash char *Menu7paramPOST[] = 
{
	Menu70,
	Menu71,
	Menu72,
	Menu73,
	Menu74,
	Menu75,
	Menu76,
	Menu77,
	Menu78,
	Menu79,
	Menu710,
	Menu711,
	Menu712
};
// кол-во параметров поста
#define NumParamDef (sizeof(Menu7paramPOST) / sizeof(Menu7paramPOST[0]))


//Параметры Приемника
__flash unsigned char Menu81[]= "Задержка на вкл.    ";
__flash unsigned char Menu82[]= "Длительность команды";
__flash unsigned char Menu83[]= "Задержка на выкл.  к";
__flash unsigned char Menu84[]= "Блок. команды  ?..? ";
__flash unsigned char Menu85[]= "Длит. команды  ?..? ";
__flash unsigned __flash char *Menu8paramPRM[] =
{
	Menu81, 
	Menu82, 
	Menu83, 
	Menu84, 
	Menu85
};
// кол-во параметров приемника
#define NumParamPrm (sizeof(Menu8paramPRM) / sizeof(Menu8paramPRM[0]))

//Параметры Передатчика
__flash unsigned char Menu93[] = "Время на повт. ком. ";
__flash unsigned char Menu94[] = "Блок. команды  ?..? ";
__flash unsigned char Menu95[] = "Длит. команды  ?..? ";
__flash unsigned __flash char *Menu9paramPRD[] =
{
	Menu81, 
	Menu82, 
	Menu93, 
	Menu94, 
	Menu95
};
// кол-во параметров передатчика
#define NumParamPrd (sizeof(Menu9paramPRD) / sizeof(Menu9paramPRD[0]))

//Общие параметры
__flash unsigned char Menu100[] =	"Совместимость";
__flash unsigned char Menu101[] =	"Cинхронизация часов";
__flash unsigned char Menu102[] =	"Uвых номинальное";		
__flash unsigned char Menu103[] =	"Удержание реле ПРД";
__flash unsigned char Menu104[] =	"Сетевой адрес";
__flash unsigned char Menu105[] =	"Время перезапуска";
__flash unsigned char Menu106[] =	"Частота";
__flash unsigned char Menu107[]	=	"Номер аппарата";
__flash unsigned char Menu108[] =	"Контроль вых.сигнала";
__flash unsigned char Menu109[]	=	"Порог ПРЕДУПР по КЧ ";
__flash unsigned char Menu1010[] =	"Загр чувствит по  КЧ";
__flash unsigned char Menu1011[] =	"Коррекция напряжения";
__flash unsigned char Menu1012[] =	"Коррекция тока";
__flash unsigned char Menu109_1[]=	"Порог ПРЕДУПР по РЗ ";	// номер NumParamGlb
__flash unsigned char Menu1013[] =	"Протокол обмена";		// ПВЗУ-Е
__flash unsigned char Menu1014[] =	"Признак четности"; 	// ПВЗУ-Е
__flash unsigned char Menu1015[] =	"Допустимые провалы"; 	// ПВЗУ-Е 
__flash unsigned char Menu1016[] =	"Порог по помехе";		// ПВЗУ-Е
__flash unsigned char Menu1017[] =	"Допустимая помеха";	// ПВЗУ-Е
__flash unsigned char Menu1018[] =	"Тип автоконтроля";		// ПВЗУ-Е
__flash unsigned char Menu1019[] =	"Резервирование";		// оптика
__flash unsigned char Menu1020[] = 	"Снижение ответа АК  ";	// ПВЗЛ				
__flash unsigned char Menu1021[] =	"Период беглого АК";	// ПВЗУ-Е
__flash unsigned char Menu1022[] =	"Период повт.бегл. АК";	// ПВЗУ-Е
__flash unsigned __flash char *Menu10paramAll[] = 
{	
	Menu100, 
	Menu101, 
	Menu102, 
	Menu103, 
	Menu104, 
	Menu105, 
	Menu106, 
	Menu107, 
	Menu108, 
	Menu109, 
	Menu1010,
	Menu1011,
	Menu1012,
	Menu1013, 
	Menu1014, 
	Menu1015, 
	Menu1016, 
	Menu1017, 
	Menu1018,	
	Menu1019,
	Menu1020,
	Menu1021,
	Menu1022,
	Menu109_1
};
// кол-во общих параметров
// - 1 , т.к. 109_1 - просто подбена текста
#define NumParamGlb ( (sizeof(Menu10paramAll) / sizeof(Menu10paramAll[0])) - 1)

__flash uchar TypeUdDev0[] = "АВАНТ Р400";
__flash uchar TypeUdDev1[] = "ПВЗ-90";
__flash uchar TypeUdDev2[] = "АВЗК-80";
__flash uchar TypeUdDev3[] = "ПВЗУ-Е";
__flash uchar TypeUdDev4[] = "ПВЗЛ";
__flash uchar TypeUdDevX[] = "ошибка";
__flash unsigned __flash char *fmTypeUdDev[] = 
{
	TypeUdDev0, 
	TypeUdDev1, 
	TypeUdDev2, 
	TypeUdDev3,
	TypeUdDev4,
	TypeUdDevX
};
// Кол-во типов совместимости,
// -1, т.к. последний в списке - ошибка
#define NumTypeUdDev ( (sizeof(fmTypeUdDev) / sizeof(fmTypeUdDev[0])) - 1)

__flash unsigned char Menu11d[]	=	"ЗАЩ";
__flash unsigned char Menu11r[]	=	"ПРМ";
__flash unsigned char Menu11r1[]=	"ПМ1";
__flash unsigned char Menu11r2[]=	"ПМ2";
__flash unsigned char Menu11t[]	=	"ПРД";

__flash unsigned char Menu11var1[] = "Вывед ";
__flash unsigned char Menu11var2[] = "Готов ";
__flash unsigned char Menu11var3[] = "Введен";
__flash unsigned char Menu11var4[] = "Речь  ";
__flash unsigned char Menu11var5[] = "Тест 1";
__flash unsigned char Menu11var6[] = "Тест 2";
__flash unsigned char Menu11var7[] = "Тест 3";
__flash unsigned __flash char *Menu11var[] = 
{
	Menu11var1, 
	Menu11var2, 
	Menu11var3,
	Menu11var4,
	Menu11var5,
	Menu11var6,
	Menu11var7
};
__flash unsigned char Menu11Err[] = "????";

__flash unsigned char TestDelayMline2[] = "   Запуск теста     ";
__flash unsigned char TestDelayMline3[] = "  Подождите ? сек   ";

//меню/4.Протокол.
__flash unsigned char Menu18[]			= "Протокол";
__flash unsigned char Menu18protocol1[]	= "Стандарт";
__flash unsigned char Menu18protocol2[]	= "ModBus";
__flash unsigned __flash char *Menu18Param[] = {Menu18protocol1, Menu18protocol2};

//меню Установить
__flash unsigned char Menu1Def[]	= "ЗАЩ:";
__flash unsigned char Menu1Rec[]	= "ПРМ:";
__flash unsigned char Menu1Rec1[]	= "ПМ1:";
__flash unsigned char Menu1Rec2[]	= "ПМ2:";
__flash unsigned char Menu1Tran[]	= "ПРД:";
__flash unsigned char Menu1Err[]	= "????    ";
__flash unsigned char Menu1disrepair[] 	= "Неиспр  ";
__flash unsigned char Menu1warning[]	= "Предупр ";

__flash unsigned char Menu1Disc[]	= "Выведен ";
__flash unsigned char Menu1Ready[]	= "Готов   ";
__flash unsigned char Menu1Work[]	= "Введен  ";
__flash unsigned char Menu1Talk[]	= "Речь    ";
__flash unsigned char Menu1Test1[]	= "Тест1   ";
__flash unsigned char Menu1Test2[]	= "Тест2   ";
__flash unsigned char Menu1Test3[]	= "Тест3   ";
__flash unsigned __flash char *Menu1regime[] 	= {Menu1Disc, Menu1Ready, Menu1Work, Menu1Talk, Menu1Test1, Menu1Test2};
__flash unsigned __flash char *Menu1regimeInp[]	= {Menu1Disc, Menu1Work};
__flash unsigned __flash char *Menu1regimeInp1[]= {Menu1Disc, Menu1Test1, Menu1Test2, Menu1Test3};
__flash unsigned __flash char *Menu1regimeInp2[]= {Menu1Disc, Menu1Work, Menu1Test1, Menu1Test2, Menu1Test3};

//состояния Поста
__flash unsigned char Menu1post00[]	= "Исходн. ";
__flash unsigned char Menu1post01[]	= "Контроль";
__flash unsigned char Menu1post02[]	= "Пуск    ";
__flash unsigned char Menu1post03[]	= "Работа  ";
__flash unsigned char Menu1post04[]	= "Неиспр. ";
__flash unsigned char Menu1post05[]	= "П.неиспр";
__flash unsigned char Menu1post06[]	= "Ожидание";
__flash unsigned char Menu1post07[]	= "Нал.пуск";
__flash unsigned char Menu1post08[]	= "Уд.пуск ";
__flash unsigned char Menu1post09[]	= "Нет РЗ  ";
__flash unsigned char Menu1post0A[]	= "Речь    ";
__flash unsigned char Menu1post0B[]	= "Тест    ";
__flash unsigned __flash char *Menu1condPOST[] = 
{
	Menu1post00,
	Menu1post01,
	Menu1post02,
	Menu1post03,
	Menu1post04,
	Menu1post05,
	Menu1post06,
	Menu1post07,
	Menu1post08,
	Menu1post09,
	Menu1post0A,
	Menu1post0B
};

//состояния ПРМ
__flash unsigned char Menu1prm00[]	= "Исходн. ";
__flash unsigned char Menu1prm01[] 	= "ПРМ КЧ  ";
__flash unsigned char Menu1prm02[]	= "ПРМ ПА  ";
__flash unsigned char Menu1prm03[]	= "Нет КЧ  ";
__flash unsigned char Menu1prm04[]	= "Неиспр. ";
__flash unsigned char Menu1prm05[]	= "П.неиспр";
__flash unsigned char Menu1prm06[]	= "Ожидание";
__flash unsigned char Menu1prm07[]	= "БЛК КМ  ";
__flash unsigned char Menu1prm08[]	= "?0x08?  ";
__flash unsigned char Menu1prm09[]	= "?0x09?  ";
__flash unsigned char Menu1prm0A[]	= "?0x0A?  ";
__flash unsigned char Menu1prm0B[]	= "Тест    ";
__flash unsigned __flash char *Menu1condPRM[] = 
{
	Menu1prm00,
	Menu1prm01,
	Menu1prm02,
	Menu1prm03,
	Menu1prm04,
	Menu1prm05,
	Menu1prm06,
	Menu1prm07,
	Menu1prm08,
	Menu1prm09,
	Menu1prm0A,
	Menu1prm0B
};

//состояния ПРД
__flash unsigned char Menu1prd00[]	= "Исходн. ";
__flash unsigned char Menu1prd01[]	= "ПРД КЧ  ";
__flash unsigned char Menu1prd02[]	= "ПРД ПА  ";
__flash unsigned char Menu1prd03[]	= "Нет КЧ  ";
__flash unsigned char Menu1prd04[]	= "Неиспр. ";
__flash unsigned char Menu1prd05[]	= "П.неиспр";
__flash unsigned char Menu1prd06[]	= "Ожидание";
__flash unsigned char Menu1prd07[]	= "?0x07?  ";
__flash unsigned char Menu1prd08[]	= "?0x08?  ";
__flash unsigned char Menu1prd09[]	= "Систем. ";
__flash unsigned char Menu1prd0A[]	= "?0x0A?  ";
__flash unsigned char Menu1prd0B[]	= "Тест    ";
__flash unsigned __flash char *Menu1condPRD[] = 
{
	Menu1prd00,
	Menu1prd01,
	Menu1prd02,
	Menu1prd03,
	Menu1prd04,
	Menu1prd05,
	Menu1prd06,
	Menu1prd07,
	Menu1prd08,
	Menu1prd09,
	Menu1prd0A,
	Menu1prd0B
};

__flash unsigned char GlobalAvar[]	= "g-";
__flash unsigned char LocalAvar[]	= "l-";

__flash unsigned char MenuInputData[]		= "Ввод:";
__flash unsigned char MenuInputOldPassword[]= "Пароль:";
__flash unsigned char MenuInputNewPassword[]= "Новый пароль:";


__flash unsigned char MenuValue[] = "Значение: ";
__flash unsigned char MenuState[] = "Сотояние: ";

__flash unsigned char MenuTypeDefend0[]	= "ДФЗ-ПрПд  ";
__flash unsigned char MenuTypeDefend1[]	= "ДФЗ-ПрмМК1";
__flash unsigned char MenuTypeDefend2[]	= "ДФЗ-ПрмМК2";
__flash unsigned char MenuTypeDefend3[]	= "ДФЗ-L60   ";
__flash unsigned char MenuTypeDefend4[]	= "НЗ-ПрПд   ";
__flash unsigned char MenuTypeDefend5[]	= "НЗ-Прм-МК ";
__flash unsigned char MenuTypeDefend6[]	= "ППЗ-ПрПд  ";
__flash unsigned char MenuTypeDefend7[]	= "ППЗ-Прм-МК";
__flash unsigned char MenuTypeDefend8[]	= "ошибка    ";
#define MaxNumTypeDefend 7 /*максимальный номер массива в списке*/
__flash unsigned __flash char *MenuTypeDefendNum[] = 
{
	MenuTypeDefend0, 
	MenuTypeDefend1, 
	MenuTypeDefend2, 
	MenuTypeDefend3, 
	MenuTypeDefend4, 
	MenuTypeDefend5, 
	MenuTypeDefend6, 
	MenuTypeDefend7, 
	MenuTypeDefend8
};

__flash unsigned char MenuAllSynchrTimer0[]	= "выкл.";
__flash unsigned char MenuAllSynchrTimer1[]	= "вкл.";
__flash unsigned char MenuAllSynchrTimer2[]	= "????";
__flash unsigned __flash char *MenuAllSynchrTimerNum[] =
{
	MenuAllSynchrTimer0, 
	MenuAllSynchrTimer1, 
	MenuAllSynchrTimer2
};

/***********************/
/* ПВЗУ-Е	*/
__flash unsigned char MenuAllProtocol0[] = "????";
__flash unsigned char MenuAllProtocol1[] = "быстрый";
__flash unsigned char MenuAllProtocol2[] = "медленный";
__flash unsigned __flash char *MenuAllProtocolNum[] = 
{
	MenuAllProtocol0, 
	MenuAllProtocol1, 
	MenuAllProtocol2, 
	MenuAllProtocol0
};

__flash unsigned char MenuAllParity0[] = "????";
__flash unsigned char MenuAllParity1[] = "вкл.";
__flash unsigned char MenuAllParity2[] = "выкл.";
__flash unsigned __flash char *MenuAllParityNum[] = 
{
	MenuAllParity0, 
	MenuAllParity1, 
	MenuAllParity2, 
	MenuAllParity0
};

__flash unsigned char MenuAllProval[] 	= "??? град";
__flash unsigned char MenuAllPorog[]	= "??? сек";
__flash unsigned char MenuAllNoise[] 	= "?? град";

__flash unsigned char MenuAllControl0[] = "????";
__flash unsigned char MenuAllControl1[] = "тревожный";
__flash unsigned char MenuAllControl2[] = "нормальный";
__flash unsigned char MenuAllControl3[] = "спокойный";
__flash unsigned __flash char *MenuAllControlNum[] = 
{
	MenuAllControl0, 
	MenuAllControl1, 
	MenuAllControl2, 
	MenuAllControl3, 
	MenuAllControl0
};

/*************************/
__flash uchar MenuAllFreq0[] = "-1000 Гц";
__flash uchar MenuAllFreq1[] = "-500 Гц";
__flash uchar MenuAllFreq2[] = "+0 Гц";
__flash uchar MenuAllFreq3[] = "+500 Гц";
__flash uchar MenuAllFreq4[] = "+1000 Гц";
__flash uchar MenuAllFreq5[] = "ошибка";
#define dMaxMenuAllFreq 5
__flash unsigned __flash char *fmMenuAllFreq[] = 
{
	MenuAllFreq0, 
	MenuAllFreq1, 
	MenuAllFreq2, 
	MenuAllFreq3, 
	MenuAllFreq4, 
	MenuAllFreq5
};

__flash unsigned char ParamRange[] 	= "Диапазон: ";
__flash unsigned char NoData[]		= "нет данных";
__flash unsigned char List[]		= "список";

//	диапазон значений для Поста //меню 13
__flash uint RangPost[NumParamDef + 1] [3] = 
{  /* +1  - это автоконтроль, который всегда будет находится в конце*/
	0,	MaxNumTypeDefend,	1,  /*тип защиты*/ /*тут не диапазон значений, а мах и мин номер массива"*/
	2,	3,		1,  	// тип линии
	0,	99,		1,  	// доп время без манипуляции
	0,	18,		1,  	// задержка на линии
	18,	54,		1,  	// перекрытие импульсов
	0,	22,		1,  	// загр. чувств. по РЗ
	0,	1,		1,  	// снижение уровня АК
	0,	4,		1,		// частота ПРД
	0,	4,		1,		// частота ПРМ
	0,	72,		1,		// сдвиг переднего фронта ПРД
	0,	72,		1,		// сдвиг заднего фронта ПРД
	0,	72,		1,		// сдвиг ПРМ
	0,	72,		1,		// сдвиг ВЧ ПРД от ПУСК
	1,	9,		1   	// автоконтроль, всегда в конце  !!! Не забыть исправить в DataCener и StudyATmega162 (обработчик нажатия 'C')!!!*/
};

//диапазон значений для Приемника
__flash uint RangPrm[NumParamPrm] [3] = 
{
	0 , 10,   	1,    	// задержка на включение
	1,  50,   	10,   	// длительность команды
	0,  100,  	10,   	// задержка на выключение
	0,  255,  	1,    	// блокированные команды
	0,  255,  	1 		// длительные команды
};  	

//диапазон значений для Передатчика
__flash uint RangPrd[NumParamPrd] [3] = 
{
	0 , 10,   	1,  	// задержка на выкл
	1,  50,  	10,  	// длительность команды
	1,  50,  	10,  	// время на повторение
	0,  255,  	1,  	// блокированные команды
	0,  255,  	1		// длительные команды
}; 	

//диапазон значение для Общих параметров
__flash uint RangGlb[NumParamGlb] [3] = 
{	
	0,	4,		1,		// 0  тип уд.аппарата	
	0,	1,    	1,		// 1  синхронизация часов  
	8, 	50,		1,  	// 2  Uвых номинальное 
	0,  2,    	1,  	// 3  удержание реле ПРД 
	0,  255,  	1,  	// 4  сетевой адрес 
	0,  5,    	1,  	// 5  время перезапуска  
	16, 1000,  	1,  	// 6  частота  
	1,  3,    	1,  	// 7  номер аппарата  
	0,  1,   	1,  	// 8  контроль выходного сигнала  
	0,  22,  	1,  	// 9  порог предупреждения по КЧ  
	0,  22,   	1,  	// 10 загрубление чувствительности по КЧ  
	0,  999,  	1,  	// 11 коррекция напряжения  
	0,  999,	1,  	// 12 коррекция тока 
	1,	2,		1,		// 13 протокол обмена	
	1,	2,		1,		// 14 признак четности	
	0,	80,		1,		// 15 допустимые провалы	
	0,	255,	1,		// 16 порог по помехе	
	20,	80,		1,		// 17 допустимая помеха	
	1,	3,		1,		// 18 тип автоконтроля	
	0,	1,		1,		// 19 Резервирование (оптика)
	0,	20, 	1,		// 20 снижение ответа АК (пвзл)
	1, 	255,	1,		// 21 Период беглого режима АК (пвзу-е)
	1, 	255,	1		// 22 Период повтора беглого режима АК (пвзу-е)	
};		

__flash unsigned char Menu16Shift10[] = "0.0..99.9";

//Прошивки
__flash unsigned char Menu19Shift0[] = "Прошивка ПИ MCU  ";
__flash unsigned char Menu19Shift1[] = "Прошивка БСП MCU ";
__flash unsigned char Menu19Shift2[] = "Прошивка БСП DSP ";
__flash unsigned char Menu19Shift3[] = "Прошивка БСЗ ПЛИС";
__flash unsigned char Menu19Shift4[] = "Дополн. параметры"; 
__flash unsigned char Menu19Shift5[] = "Вид параметра";		
__flash unsigned __flash char *Menu19Param[] = 
{
	Menu19Shift0, 
	Menu19Shift1, 
	Menu19Shift2, 
	Menu19Shift3,
	Menu19Shift4,
	Menu19Shift5
};

__flash unsigned char fDopParamViewTrue[] 	="Есть";
__flash unsigned char fDopParamViewFalse[] 	= "Нет";
__flash unsigned __flash char *fDopParamView[] = {fDopParamViewFalse, fDopParamViewTrue};
__flash unsigned char fDopParamValueTrue[]	= "стандарт";
__flash unsigned char fDopParamValueFalse[]	= "HEX";
__flash unsigned __flash char *fDopParamValue[] = {fDopParamValueFalse, fDopParamValueTrue};

// Пункты меню управления
__flash unsigned char Menu22Shift0[]	= ".Сброс своего.     ";
__flash unsigned char Menu22Shift1[]	= ".Сброс удаленного. ";
__flash unsigned char Menu22Shift2[]	= ".Сброс удаленного 1";
__flash unsigned char Menu22Shift3[]	= ".Сброс удаленного 2";
__flash unsigned char Menu22Shift3x[]	= ".Сброс удаленного 3";
__flash unsigned char Menu22Shift4[]	= ".Пуск удаленного.  ";
__flash unsigned char Menu22Shift5[]	= ".Пуск удаленного 1 ";
__flash unsigned char Menu22Shift6[]	= ".Пуск удаленного 2 ";
__flash unsigned char Menu22Shift6x[]	= ".Пуск удаленного 3 ";
__flash unsigned char Menu22Shift7[]	= ".Пуск удаленных    ";
__flash unsigned char Menu22Shift8[]	= ".АК автоматический ";
__flash unsigned char Menu22Shift9[]	= ".АК ускоренный     ";
__flash unsigned char Menu22Shift10[]	= ".АК выключен       ";
__flash unsigned char Menu22Shift11[]	= ".АК контр.проверка ";
__flash unsigned char Menu22Shift12[]	= ".АК испытания      ";
__flash unsigned char Menu22Shift13[]	= ".АК пуск           ";
__flash unsigned char Menu22Shift14[]	= ".Вызов             ";
__flash unsigned char Menu22Shift15[]	= ".АК нормальный     ";	
__flash unsigned char Menu22Shift16[]	= ".АК беглый         ";	
__flash unsigned char Menu22Shift17[]	= ".Пуск удален. МАН  ";	
__flash unsigned char Menu22Shift18[]	= ".АК односторонний  ";
__flash unsigned char Menu22Shift19[]	= ".Сброс АК          ";
__flash unsigned char Menu22Shift20[]	= ".Пуск АК свой      ";
__flash unsigned char Menu22Shift21[]	= ".Пуск АК удаленный ";
__flash unsigned char Menu22Shift22[]	= ".Пуск ПРД          ";
__flash unsigned char Menu22Shift23[]	= ".Пуск налад. вкл.  ";
__flash unsigned char Menu22Shift24[]	= ".Пуск налад. выкл. ";
__flash unsigned char Menu22Shift25[] 	= ".Пуск удал. МАН 1  ";
__flash unsigned char Menu22Shift26[] 	= ".Пуск удал. МАН 2  ";
__flash unsigned char Menu22Shift27[] 	= ".Пуск удал. МАН 3  ";
__flash unsigned char Menu22Shift28[] 	= ".Пуск удал-ых МАН  ";
// Пункты меню управления
// должно совпадать с eMENUctrlName
__flash unsigned __flash char* Menu22upr[] = 
{
	Menu22Shift0,
	Menu22Shift1,
	Menu22Shift2,
	Menu22Shift3,
	Menu22Shift3x,
	Menu22Shift4,
	Menu22Shift5,
	Menu22Shift6,
	Menu22Shift6x,
	Menu22Shift7,
	Menu22Shift8,
	Menu22Shift9,
	Menu22Shift10,
	Menu22Shift11,
	Menu22Shift12,
	Menu22Shift13,
	Menu22Shift14,
	Menu22Shift15,
	Menu22Shift16,
	Menu22Shift17,
	Menu22Shift18,
	Menu22Shift19,
	Menu22Shift20,
	Menu22Shift21,
	Menu22Shift22,
	Menu22Shift23,
	Menu22Shift24,
	Menu22Shift25,
	Menu22Shift26,
	Menu22Shift27,
	Menu22Shift28
};

//__flash unsigned char fRes[]	= "Сброс";
//__flash unsigned char fPusk[]	= "Пуск";
//__flash unsigned char fEnter[]	= "Ввод";
//__flash unsigned char fCall[]	= "Вызов";
//__flash unsigned char fOn[] 	= "Вкл.";
//__flash unsigned char fOff[]	= "Выкл.";
//__flash unsigned __flash char *fReset[] = {fRes, fPusk, fEnter, fCall, fOn, fOff};
__flash unsigned char fEnter[] = "Выполнить";
__flash unsigned __flash char *fReset[] = {fEnter};


//Неизвестная ошибка
__flash unsigned char UnknownErrorT[]		= "     Error      ";

//ошибки глобальные
__flash unsigned char Menu1GlobalError1[]	= "Неиспр.чт. FLASH";
__flash unsigned char Menu1GlobalError2[]   = "Неиспр.зап.FLASH";
__flash unsigned char Menu1GlobalError4[]   = "Неиспр.чт. PLIS ";
__flash unsigned char Menu1GlobalError8[]   = "Неиспр.зап.PLIS ";
__flash unsigned char Menu1GlobalError10[]  = "Неиспр.зап.2RAM ";
__flash unsigned char Menu1GlobalError20[]  = "Нет сигнала ПРМ ";
__flash unsigned char Menu1GlobalError40[]  = "АК-Снижен.запаса";
__flash unsigned char Menu1GlobalError80[] 	= "Помеха в линии  ";
__flash unsigned char Menu1GlobalError100[] = "Неиспр.DSP 2RAM ";
__flash unsigned char Menu1GlobalError200[] = "Неиспр.чт. 2RAM ";
__flash unsigned char Menu1GlobalError400[] = "Ток покоя       ";
__flash unsigned char Menu1GlobalError800[] = "Низкое напр.вых.";
__flash unsigned char Menu1GlobalError1000[]= "Высокое напр.вых";
__flash unsigned char Menu1GlobalError2000[]= "Неиспр. МК УМ   ";
__flash unsigned char Menu1GlobalError4000[]= "ВЧ тракт восст. ";
__flash unsigned __flash char *Menu1GlobalErrorT[] =
{
	Menu1GlobalError1, 
	Menu1GlobalError2, 
	Menu1GlobalError4, 
	Menu1GlobalError8, 
	Menu1GlobalError10,
	Menu1GlobalError20,
	Menu1GlobalError40,
	Menu1GlobalError80,
    Menu1GlobalError100, 
	Menu1GlobalError200,
	Menu1GlobalError400,
	Menu1GlobalError800,
	Menu1GlobalError1000,
	Menu1GlobalError2000,
	Menu1GlobalError4000,
	UnknownErrorT
};
//в чистой защите вместо "Нет сигнала ПРМ", выведем другое сообщение
__flash unsigned char Menu1GLobalError20_1[] 	= "АК-Нет ответа   ";

//общие предупреждения
__flash unsigned char Menu1GlobalWarning1[] 	= "Установите часы ";
__flash unsigned char Menu1GlobalWarning2[]		= "Отказ резерв.лин";
__flash unsigned char Menu1GlobalWarning10[]	= "Удал.пост неиспр";
__flash unsigned char Menu1GlobalWarning20[] 	= "Удал.ПРД неиспр.";
__flash unsigned char Menu1GlobalWarning40[] 	= "Удал.ПРМ неиспр.";
__flash unsigned __flash char *Menu1GlobalWarningT[] =
{	
	Menu1GlobalWarning1,
	Menu1GlobalWarning2,
	UnknownErrorT,
	UnknownErrorT,
	Menu1GlobalWarning10,
	Menu1GlobalWarning20,
	Menu1GlobalWarning40,
	UnknownErrorT
};

__flash unsigned char Menu1PostErrorDop000[] = "   ";
__flash unsigned char Menu1PostErrorDop001[] = " 1 ";
__flash unsigned char Menu1PostErrorDop010[] = " 2 ";
__flash unsigned char Menu1PostErrorDop011[] = "1 2";
__flash unsigned char Menu1PostErrorDop100[] = " 3 ";
__flash unsigned char Menu1PostErrorDop101[] = "1 3";
__flash unsigned char Menu1PostErrorDop110[] = "2 3";
__flash unsigned char Menu1PostErrorDop111[] = " ? ";
__flash unsigned __flash char *Menu1PostErrorDopT[] = {
	Menu1PostErrorDop000,
	Menu1PostErrorDop001,
	Menu1PostErrorDop010,
	Menu1PostErrorDop011,
	Menu1PostErrorDop100,
	Menu1PostErrorDop101,
	Menu1PostErrorDop110,
	Menu1PostErrorDop111
};

//ошибки Защиты
__flash unsigned char Menu1PostError1[]		= "Нет блока БСЗ   ";
__flash unsigned char Menu1PostError2[]		= "Неиспр.верс.БСЗ ";
__flash unsigned char Menu1PostError4[]		= "Неиспр.перекл.  ";
__flash unsigned char Menu1PostError8[]		= "Неиспр.зап. БСЗ ";
__flash unsigned char Menu1PostError10[]	= "Нет сигнала ПРМ ";
__flash unsigned char Menu1PostError20[]	= "Низкий ур. РЗ   ";
__flash unsigned char Menu1PostError40[]	= "Неиспр.уд.ДФЗ";	// ПВЗУ-Е (+ номер)
__flash unsigned char Menu1PostError80[]	= "Неиспр.уд.ВЫХ";	// ПВЗУ-Е (+ номер)
__flash unsigned char Menu1PostError100[]	= "Неиспр.вход.ПУСК";
__flash unsigned char Menu1PostError200[]	= "Неиспр.вход.СТОП";
__flash unsigned char Menu1PostError400[]	= "Удал.без отв.";	// ПВЗУ-Е (+ номер)
__flash unsigned char Menu1PostError800[]	= "Неиспр.цепь.ВЫХ ";
__flash unsigned char Menu1PostError1000[]	= "Удал.обн.пом.";	// ПВЗУ-Е (+ номер)
__flash unsigned char Menu1PostError2000[]	= "Неиспр.зап. ВЫХ ";
__flash unsigned char Menu1PostError4000[]	= "Длит. помеха ";	// ПВЗУ-Е
__flash unsigned char Menu1PostError8000[]	= "Неиспр. ДФЗ  ";	// ПВЗУ-Е
__flash unsigned __flash char *Menu1PostErrorT[] =
{	Menu1PostError1,
	Menu1PostError2,
	Menu1PostError4,
	Menu1PostError8,
	Menu1PostError10,
	Menu1PostError20,
	Menu1PostError40,
	Menu1PostError80,
	Menu1PostError100,
	Menu1PostError200,
	Menu1PostError400,
	Menu1PostError800,
	Menu1PostError1000,
	Menu1PostError2000,
	Menu1PostError4000,
	Menu1PostError8000
};
//в чистой защите вместо "Нет сигнала ПРМ", выведем другое сообщение// ПВЗУ-Е (+ номер)
__flash unsigned char Menu1PostError10_1[] 	= "АК-Нет ответа";

//предупреждения Защиты
__flash unsigned char Menu1PostWarning1[]	= "АК-Сн.запаса ";	// ПВЗУ-Е (+ номер)
__flash unsigned char Menu1PostWarning2[] 	= "Нет сигнала МАН ";
__flash unsigned char Menu1PostWarning4[] 	= "Порог по помехе ";
__flash unsigned char Menu1PostWarning8[]	= "Автоконтроль    ";

//ошибки Приемника
__flash unsigned char Menu1PrmError1[]		= "Нет блока БСК   ";
__flash unsigned char Menu1PrmError2[]		= "Неиспр.верс.БСК ";
__flash unsigned char Menu1PrmError4[] 		= "Нет КЧ          ";
__flash unsigned char Menu1PrmError8[]		= "Прев.дл-сти.ком.";
__flash unsigned char Menu1PrmError100[]	= "Неиспр.зап. БСК ";
__flash unsigned char Menu1PrmError200[]	= "Неиспр.выкл.КСК ";
__flash unsigned char Menu1PrmError400[]	= "Неиспр.вкл. КСК ";
__flash unsigned char Menu1PrmError800[]	= "Неиспр.контр.КСК";
__flash unsigned char Menu1PrmError1000[] 	= "Предупр.нет КЧ1 ";
__flash unsigned char Menu1PrmError8000[] 	= "Прием блок. Ком.";
__flash unsigned __flash char *Menu1PrmErrorT[] =
{
	Menu1PrmError1,
	Menu1PrmError2,
	Menu1PrmError4,
	Menu1PrmError8,
	UnknownErrorT,
	UnknownErrorT,
	UnknownErrorT,
	UnknownErrorT,
    Menu1PrmError100,
	Menu1PrmError200,
	Menu1PrmError400,
	Menu1PrmError800,
	Menu1PrmError1000,
	UnknownErrorT,
	UnknownErrorT,
	Menu1PrmError8000
};

//предупреждения Приемника
__flash unsigned char Menu1PrmWarning1[] = "Сниж. уровня ПРМ";

//ошибки Передатчика
__flash unsigned char Menu1PrdError1[]	= "Нет блока БСК   ";
__flash unsigned char Menu1PrdError2[]	= "Неиспр.верс.БСК ";
__flash unsigned char Menu1PrdError100[]= "Неиспр.чт.команд";
__flash unsigned char Menu1PrdError200[]= "Неиспр.выкл.Тест";
__flash unsigned char Menu1PrdError400[]= "Неиспр.вкл. Тест";
__flash unsigned char Menu1PrdError800[]= "Неиспр.вход.КСК ";
__flash unsigned __flash char *Menu1PrdErrorT[] = 
{
	Menu1PrdError1,
	Menu1PrdError2,
	UnknownErrorT,
	UnknownErrorT,
	UnknownErrorT,
	UnknownErrorT,
	UnknownErrorT,
	UnknownErrorT,
	Menu1PrdError100,
	Menu1PrdError200,
	Menu1PrdError400,
	Menu1PrdError800,
	UnknownErrorT,
	UnknownErrorT,
	UnknownErrorT,
	UnknownErrorT
};

//Тестовый режим 1
__flash unsigned char Menu20gr1n[] = "Гр1:";
__flash unsigned char Menu20gr2n[] = "Гр2:";
__flash unsigned char Menu20grName1[] = "Группа 1";
__flash unsigned char Menu20grName2[] = "Группа 2";
__flash strNameToVal Menu20grName[] = 
{
	{Menu20grName1, 1},
	{Menu20grName2, 2}
};

__flash unsigned char Menu20gr_off[] = "выкл";
__flash unsigned char Menu20gr_err[] = "ошиб";
__flash unsigned char Menu20gr_def[] = "РЗ";
__flash unsigned char Menu20gr_cf1[] = "КЧ1";
__flash unsigned char Menu20gr_cf2[] = "КЧ2";
__flash unsigned char Menu20gr_cf3[] = "КЧ3";
__flash unsigned char Menu20gr_cf4[] = "КЧ4";
__flash unsigned char Menu20gr_com1[] = "Ком1";
__flash unsigned char Menu20gr_com2[] = "Ком2";
__flash unsigned char Menu20gr_com3[] = "Ком3";
__flash unsigned char Menu20gr_com4[] = "Ком4";
__flash unsigned char Menu20gr_com5[] = "Ком5";
__flash unsigned char Menu20gr_com6[] = "Ком6";
__flash unsigned char Menu20gr_com7[] = "Ком7";
__flash unsigned char Menu20gr_com8[] = "Ком8";
__flash unsigned char Menu20gr_com9[] = "Ком9";
__flash unsigned char Menu20gr_com10[] = "Км10";
__flash unsigned char Menu20gr_com11[] = "Км11";
__flash unsigned char Menu20gr_com12[] = "Км12";
__flash unsigned char Menu20gr_com13[] = "Км13";
__flash unsigned char Menu20gr_com14[] = "Км14";
__flash unsigned char Menu20gr_com15[] = "Км15";
__flash unsigned char Menu20gr_com16[] = "Км16";
__flash unsigned char Menu20gr_com17[] = "Км17";
__flash unsigned char Menu20gr_com18[] = "Км18";
__flash unsigned char Menu20gr_com19[] = "Км19";
__flash unsigned char Menu20gr_com20[] = "Км20";
__flash unsigned char Menu20gr_com21[] = "Км21";
__flash unsigned char Menu20gr_com22[] = "Км22";
__flash unsigned char Menu20gr_com23[] = "Км23";
__flash unsigned char Menu20gr_com24[] = "Км24";
__flash unsigned char Menu20gr_com25[] = "Км25";
__flash unsigned char Menu20gr_com26[] = "Км26";
__flash unsigned char Menu20gr_com27[] = "Км27";
__flash unsigned char Menu20gr_com28[] = "Км28";
__flash unsigned char Menu20gr_com29[] = "Км29";
__flash unsigned char Menu20gr_com30[] = "Км30";
__flash unsigned char Menu20gr_com31[] = "Км31";
__flash unsigned char Menu20gr_com32[] = "Км32";

// начальные номера для сигналов
// защиты
#define NDEF 0
// контрольных частот
#define NCF (1 - 1)
// команд
#define NCOM (3 - 1)

// массив сигналов в Тестах 1, 2
// strNameToVal.name - имя сигнала
// strNameToVal.val - номер отправляемый в БСП при смене сигнала в Тест 1
__flash strNameToVal Menu20gr[] = 
{
	{Menu20gr_err, 0xFF},
	{Menu20gr_off, 0},
	{Menu20gr_def, NDEF + 1},
	{Menu20gr_cf1, NCF + 1},
	{Menu20gr_cf2, NCF + 2},
	{Menu20gr_cf3, NCF + 3},
	{Menu20gr_cf4, NCF + 4},
	{Menu20gr_com1, NCOM + 1},
	{Menu20gr_com2, NCOM + 2},
	{Menu20gr_com3, NCOM + 3},
	{Menu20gr_com4, NCOM + 4},
	{Menu20gr_com5, NCOM + 5},
	{Menu20gr_com6, NCOM + 6},
	{Menu20gr_com7, NCOM + 7},
	{Menu20gr_com8,	NCOM + 8},
	{Menu20gr_com9, NCOM + 9},
	{Menu20gr_com10, NCOM + 10},
	{Menu20gr_com11, NCOM + 11},
	{Menu20gr_com12, NCOM + 12},
	{Menu20gr_com13, NCOM + 13},
	{Menu20gr_com14, NCOM + 14},
	{Menu20gr_com15, NCOM + 15},
	{Menu20gr_com16, NCOM + 16},
	{Menu20gr_com17, NCOM + 17},
	{Menu20gr_com18, NCOM + 18},
	{Menu20gr_com19, NCOM + 19},
	{Menu20gr_com20, NCOM + 20},
	{Menu20gr_com21, NCOM + 21},
	{Menu20gr_com22, NCOM + 22},
	{Menu20gr_com23, NCOM + 23},
	{Menu20gr_com24, NCOM + 24},
	{Menu20gr_com25, NCOM + 25},
	{Menu20gr_com26, NCOM + 26},
	{Menu20gr_com27, NCOM + 27},
	{Menu20gr_com28, NCOM + 28},
	{Menu20gr_com29, NCOM + 29},
	{Menu20gr_com30, NCOM + 30},
	{Menu20gr_com31, NCOM + 31},
	{Menu20gr_com32, NCOM + 32}
};

__flash unsigned char Menu201line4[] = "Тест 1";
__flash unsigned char Menu202line4[] = "Тест 2";
__flash unsigned __flash char *Menu20line4[] = {Menu201line4, Menu202line4};

__flash unsigned char Menu20no[] = "Тест не запущен";

#define dNumSob 25
__flash unsigned char ArchSob[dNumSob] [11] =
{	
	"Н.чт.FLASH",
	"Н.зп.FLASH",
	"Н.чт.PLIS ",
	"Н.зп.PLIS ",
	"Н.зп.2RAM ",
	"Н.чт.2RAM ",
	"Н.раб.DSP ",
	"Вост.р.DSP",
	"Низк. Uвых",
	"Выс. Uвых ",
	"Н.св. с УМ",
	"Н. часов  ",
	"Нет бл.БСЗ",
	"Н.верс.БСЗ",
	"Н.пер. БСЗ",
	"Нет с. МАН",
	"Перезапуск",
	"Изм.режима",
	"Ош.записи ",
	"Ош.контр. ",
	"Сниж.у.ПРМ",
	"Нет с. ПРМ",
	"Нет с.ПУСК",
	"нет с.СТОП",
	"Выключение"
};											
#endif
