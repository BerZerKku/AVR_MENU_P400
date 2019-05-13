#include <ioavr.h>
#include <ina90.h>
#include <stdint.h>

#include "MyDef.h"
#include "UartBsp.h"
#include "driverLCD.h"
#include "DataCenter1.h"
#include "Menu.h"
#include "UartLs.h"

extern strMenuGlbParam sMenuGlbParam, sMenuDefParam, sMenuUpr;
int CRCSum;

extern unsigned char PCready;
extern unsigned char PCbyte;
extern unsigned char PCtime;

extern unsigned char Temp_uart1[];

extern unsigned char DataLCD[];
extern unsigned char TimeLCD[];
extern unsigned char LCD2new;
extern unsigned char LCDtimerNew;
extern unsigned char GlobalCurrentState[];
extern unsigned char Mass1[];
extern unsigned char RecivVar;
extern unsigned char CurrentState[];
extern eMENUlvl MenuLevel;
extern unsigned char maxLCDtimer; //максимальное кол-во шагов параметра LCDtimer

//параметры ПОСТа
extern unsigned char MenuTypeDefend;
extern unsigned char MenuTypeLine[];
extern unsigned char MenuPossibleTimeNoMan[];
extern unsigned char MenuPossibleTimeSignal1[];
extern unsigned char MenuPossibleTimeSignal2[];
extern unsigned char MenuCoveringImpulse1[];
extern unsigned char MenuCoveringImpulse2[];
extern unsigned char MenuVoltageLimit1[];
extern unsigned char MenuVoltageLimit2[];
extern unsigned char cAutoControl;
extern unsigned int iTimeToAK, iTimeToAKnow;
extern unsigned char MenuAKdecrease;
extern uint8_t MenuFreqPRD, MenuFreqPRM;
extern unsigned char MenuDefShftFront[];
extern unsigned char MenuDefShftBack[];
extern unsigned char MenuDefShftPrm[];
extern unsigned char MenuDefShftPrd[];
extern unsigned char* MenuDefShft[];
extern unsigned char NumDevError;
extern unsigned char NumDfzError[];

extern __flash uint16_t RangPost[] [3];
//параметры ПРМ-ка
extern unsigned char MenuPrmTimeOn[];
extern unsigned char MenuPrmTimeCom[];
extern unsigned char MenuPrmTimeOff[];
extern unsigned char ValuePrmTimeOff[];
extern unsigned char ValuePrmBlockCom[];
extern unsigned char ValuePrmLongCom[];
extern unsigned char MenuVoltageLimitPRM1[];
extern unsigned char MenuVoltageLimitPRM2[];

extern unsigned char MenuPrmTimeOn2[];
extern unsigned char MenuPrmTimeCom2[];
extern unsigned char MenuPrmTimeOff2[];
extern unsigned char ValuePrmTimeOff2[];
extern unsigned char ValuePrmBlockCom2[];
extern unsigned char ValuePrmLongCom2[];
extern unsigned char MenuVoltageLimitPRM12[];
extern unsigned char MenuVoltageLimitPRM22[];

extern __flash uint16_t RangPrm[] [3];
//параметры ПРД-ка
extern unsigned char MenuPrdTimeOn[];
extern unsigned char MenuPrdTimeCom[];
extern unsigned char MenuPrdTimeRep[];
extern unsigned char MenuPrdBlockCom[];
extern unsigned char MenuPrdLongCom[];
extern unsigned char ValuePrdBlockCom[];
extern unsigned char ValuePrdLongCom[];
extern __flash uint16_t RangPrd[] [3];
//Параметры Общие
extern unsigned char MenuAllSynchrTimer;
extern unsigned char adrLan;
extern unsigned char MenuAllKeepComPRM[];
extern unsigned char MenuAllKeepComPRD;
extern unsigned char MenuAllTimeRerun[];
extern unsigned char MenuAllFreq[];
extern unsigned char MenuAllNumDevice[];
extern unsigned char MenuAllControlUout;
extern unsigned char MenuAllCF[];
extern unsigned char MenuAllLowCF[];
extern unsigned char MenuAllLowCFa[];
extern unsigned int MyInsertion[];
extern __flash uint16_t RangGlb[] [3];
extern typeUdDev_t TypeUdDev;
///// ПВЗУ-Е
extern strParamPVZUE sParamPVZE;	
/////

//extern unsigned char Iline1[], Iline2[], Uline[], Usigndef[], Uinkch[], Kd[], Kov[], Pk[];
extern unsigned char Iline1[], Iline2[], Uline[], Usigndef1[], Usigndef2[], Uinkch1[], Uinkch2[], Kd[], Kov[], Pk[];
extern unsigned char Uinkch3[], Uinkch4[], Uinkch5[],Uinkch6[],Uinkch7[],Uinkch8[];
extern unsigned char Iline1H[], PkH[], KovH[];
extern signed int UlineValue, IlineValue;
extern unsigned char LCDparam;
extern unsigned char FreqNum[];

extern unsigned char Mass1[];

extern unsigned char Dop_byte[];

//Архив
extern unsigned int NumberRecording;
extern unsigned char NumberRec;
extern unsigned char ReadArch;
extern unsigned char NumberRegister;
extern unsigned char StRegister;
extern strArchive sArchive;

//Тесты
extern unsigned char gr1, gr2, gr21, gr22;


//переменные проверки достоверности даты и времени
unsigned char TrDataTimeMass[]={0x30,0x30,0x30,0x30,0x30,0x30};
unsigned char DataError=9;
unsigned char TimeError=9;
unsigned int Pk_temp=0;

unsigned char TempMass[10];

//для единой версии
extern unsigned char cNumComR, cNumComT;
extern unsigned char cNumComR1, cNumComR2;
extern unsigned char cTypeLine;
extern unsigned char cNumLine;
extern bool bDef;
extern bool bReadVers; //true - версия была считана, false - ответ не пришел, продолжаем опрос
extern bool bViewParam[];
extern bool bAllDevice; //true - когда 3-х концевая и все 4 устройства
//для вывода информации в 0 меню
extern bool bDefAvar, bDefWarn;
extern bool bGlobalAvar, bGlobalWarn;
extern bool bRec1Avar, bRec1Warn;
extern bool bTrAvar, bTrWarn;
extern bool bRec2Avar, bRec2Warn;
extern __flash  unsigned char  Menu61[],Menu62[],Menu63[],Menu64[],Menu62_1[],Menu62_2[];
extern unsigned char LineInMenu6; //кол-во строк в меню просмотр параметров/ установить параметры
extern unsigned __flash char  *mMenu6point[]; //массив строк для меню просмотр параметров/ установить параметры
extern unsigned char  __flash* Param4;
extern __flash unsigned __flash char* flAutoSinch[];
extern __flash unsigned __flash char* flAutoContorl[];
extern  uint8_t   cNumKF;

extern unsigned char MaxShiftMenu, ShiftMenu;

extern int8_t ucf1;
extern int8_t ucf2;
extern int8_t udef1;
extern int8_t udef2;

void getNumDfzError(uint8_t val);

//функция вычисляет код CRC-16
//на входе указатель на начало буфера
//и количество байт сообщения (без принятого кода CRC-16)
//но при этом синхробайты не считаются
unsigned char GetCRCSum(unsigned char *buf, char bufsize)
{
	unsigned char CRCbuf;
	unsigned char k;
	
	CRCbuf=0;
	for (k=2; k<bufsize; k++)
	{
		CRCbuf+=buf[k];
	};
	return(CRCbuf);
}

//подпрограмма подготовки отпраки одного байта информации по UART
void TransDataByte(unsigned char ByteCommand, unsigned char ByteData)
{
	Sost|=CurSost;
    //байты синхронизации уже лежат в массиве
	Tr_buf_data_uart[2]=ByteCommand;//состояния Пост
	Tr_buf_data_uart[3]=0x01;
	Tr_buf_data_uart[4]=ByteData;
	CRCSum=GetCRCSum(Tr_buf_data_uart,5);
	Tr_buf_data_uart[5]=CRCSum;
	StartTrans(6);
}

void TransDataInf(unsigned char ByteCommand, unsigned char NumberTransByte)
{
	Sost|=CurSost;
    //байты синхронизации уже лежат в массиве
	Tr_buf_data_uart[2]=ByteCommand;
	Tr_buf_data_uart[3]=NumberTransByte;
	CRCSum=GetCRCSum(Tr_buf_data_uart,4+NumberTransByte);
	Tr_buf_data_uart[4+NumberTransByte]=CRCSum;
	StartTrans(5+NumberTransByte);
}

//возвращаем сообщение с ошибкой
void ErrorMessage(char code)
{
	Sost|=CurSost;
    //байты синхронизации уже лежат в массиве
	Tr_buf_data_uart[2]=code;
	Tr_buf_data_uart[3]=0x02; //т.е. посылается два байта данных
	CRCSum=GetCRCSum(Tr_buf_data_uart,6);
	Tr_buf_data_uart[6]=CRCSum;
	StartTrans(7);
}

void FParamDef(unsigned char command)
{
	uint8_t min, max;
	uint8_t tmp = Rec_buf_data_uart[4];
	
	switch(command)
	{
		case 0x01:
		{  //принято значение типа защиты (пост)
			if ((tmp < RangPost[0] [0]) || (tmp > RangPost[0] [1])) 
				MenuTypeDefend = RangPost[0] [1] + 1;
			else 
				MenuTypeDefend = tmp;
		}break;
		case 0x02:
		{ 
			// принято значение типа линии (пост) (кол-во концов)
			// проверим на допустимое значение
			// в случае, если тип линии не совпадает с имеющимся
			// настроим пункты меню с учетом выбранного значения
			
			tmp += 1;
			
			uint8_t min = RangPost[1] [0];
			uint8_t max = RangPost[1] [1];
			
			if (TypeUdDev == TYPE_UD_DEV_PVZUE)
				max = 8;
			
			if ((tmp < min) || (tmp > max)) 
				MenuTypeLine[0] = '?'; 
			else 
			{
				MenuTypeLine[0] = tmp + '0';
				if (cNumLine != tmp)
				{
					cNumLine = tmp;
					
					// включим нужные Uk и отключим лишние
					if ((TypeUdDev == TYPE_UD_DEV_PVZUE) && (cNumLine > 3)) {
						// в ПВЗУ-Е с кол-вом концов более 3, показывается
						// столько Uк сколько концов.
						for(uint8_t i = 1; i <= 8; i++) {
							bViewParam[4 + i] = (i <= cNumLine) ? true : false;
						}
					} else {			
						for(uint8_t i = 1; i <= 8; i++) {
							bViewParam[4 + i] = (i < cNumLine) ? true : false;
						}
					}
					
					MenuTestCreate();
					MenuParamGlbCreate();
					MenuParamDefCreate();
					MenuUprCreate(1);
					MenuACCreate();
					MenuAKCreate();
					MenuTestCreate();
				}
			}
			
			
		}break;
		case 0x03:
		{//принято значение допустимого времени без манипуляции (пост)
			if ((tmp < RangPost[2] [0]) || (tmp > RangPost[2] [1])) 
			{
				MenuPossibleTimeNoMan[0] = '?';
				MenuPossibleTimeNoMan[1] = '?';
			}
			else
			{
				MenuPossibleTimeNoMan[0] = tmp/10 + '0';
				MenuPossibleTimeNoMan[1] = tmp%10 + '0';
			}
		}break;
		case 0x04:
		{//принято значение допустимых провалов в сигнале приема (пост)
			if (cTypeLine == 1)
			{
				min = RangPost[3] [0];
				max = RangPost[3] [1];
			}
			else
			{
				min = 0;
				max = 54;
			}
			
			if ( (tmp < min) || (tmp > max)) 
			{
				MenuPossibleTimeSignal1[0] = '?';
				MenuPossibleTimeSignal1[1] = '?';
			}
			else
			{
				MenuPossibleTimeSignal1[0] = tmp/10 + '0';
				MenuPossibleTimeSignal1[1] = tmp%10 + '0';
			}
			
			if (cNumLine == 3)
			{
				tmp = Rec_buf_data_uart[5];
				if ((tmp < min) || (tmp > max)) 
				{
					MenuPossibleTimeSignal2[0] = '?';
					MenuPossibleTimeSignal2[1] = '?';
				}
				else
				{
					MenuPossibleTimeSignal2[0] = tmp/10 + '0';
					MenuPossibleTimeSignal2[1] = tmp%10 + '0';
				}
			}
		}break;
		case 0x05:{//принято значение перекрытия импульсов (пост)
			min = 0;
			max = 72; 
			for(unsigned char i = 0; i < 4; i++) {
				tmp = Rec_buf_data_uart[4 + i];
				
				if ((tmp < min) || (tmp > max)) {
					MenuDefShft[i] [0] = '?';
					MenuDefShft[i] [1] = '?';
				} else {
					MenuDefShft[i] [0] = tmp/10 + '0';
					MenuDefShft[i] [1] = tmp%10 + '0';
				}
			}
		}break;
		case 0x06:
		{//принято значение напряжения порога (пост)
			if ( (tmp < RangPost[5] [0]) || (tmp > RangPost[5] [1]) ) 
			{
				MenuVoltageLimit1[0] = '?';
				MenuVoltageLimit1[1] = '?';
			}
			else
			{
				MenuVoltageLimit1[0] = tmp/10 + '0';
				MenuVoltageLimit1[1] = tmp%10 + '0';
			}
			if (cNumLine == 3)
			{
				tmp = Rec_buf_data_uart[5];
				if ( (tmp < RangPost[5] [0]) || (tmp > RangPost[5] [1]) ) 
				{
					MenuVoltageLimit2[0] = '?';
					MenuVoltageLimit2[1] = '?';
				}
				else
				{
					MenuVoltageLimit2[0] = tmp/10 + '0';
					MenuVoltageLimit2[1] = tmp%10 + '0';
				}
			}
		}break;
		case 0x07:
		{
			if ( (tmp < RangPost[6] [0]) || (tmp > RangPost[6] [1]) ) 
				MenuAKdecrease = 2;
			else 
				MenuAKdecrease = tmp;
		}break;
		case 0x08:
		{
			if (tmp > RangPost[7] [1])
				MenuFreqPRD = RangPost[7] [1] + 1;
			else
				MenuFreqPRD = tmp;
		}
		break;
		case 0x09:
		{
			if (tmp > RangPost[8] [1])
				MenuFreqPRM = RangPost[8] [1] + 1;
			else
				MenuFreqPRM = tmp;
		}
		break;
		case 0x0A:
		{
			if ( (tmp < RangPost[13] [0]) || (tmp > RangPost[13] [1]) )
			{
				cAutoControl = 0;
			}
			else
			{
				cAutoControl = tmp;
				
				// если тип удаленного аппарата ПВЗ или АВЗК
				if ( (sMenuGlbParam.dev >= 1) || (sMenuGlbParam.dev <= 8) )
				{
					long a;
					
					a = Rec_buf_data_uart[5];
					a <<= 8;
					a += Rec_buf_data_uart[6];
					a <<= 8;
					a += Rec_buf_data_uart[7];
					a <<= 8;
					a += Rec_buf_data_uart[8];
					a = a / 1000;
					iTimeToAK = a;
				}
			}
			LCDtimerNew=1;
		}break;
	}
	RecivVar=1;
	LCD2new=1;
};

void FParamPrm(unsigned char command)
{
	unsigned char *TmpMass;
	
	switch(command){
		case 0x11:
		case 0x18:{ //Время включения (приемник)
			if (command==0x11) TmpMass=MenuPrmTimeOn;
			else TmpMass=MenuPrmTimeOn2;
			
			if ((Rec_buf_data_uart[4]<RangPrm[0] [0])||(Rec_buf_data_uart[4]>RangPrm[0] [1])) {TmpMass[0]='?';TmpMass[1]='?';}
			else{
				TmpMass[0]=Rec_buf_data_uart[4]/10+0x30;
				TmpMass[1]=Rec_buf_data_uart[4]%10+0x30;
			}
		}break;
		case 0x12:
		case 0x19:{ //длительность команды (приемник)
			if (command==0x12) TmpMass=MenuPrmTimeCom;
			else TmpMass=MenuPrmTimeCom2;
			
			if ((Rec_buf_data_uart[4]<RangPrm[1] [0])||(Rec_buf_data_uart[4]>RangPrm[1] [1])) {TmpMass[0]='?';TmpMass[1]='?';TmpMass[2]='?';}
			else{
				if (Rec_buf_data_uart[4]<10){
					TmpMass[0]=Rec_buf_data_uart[4]+0x30;
					TmpMass[1]='0';
					TmpMass[2]=' ';
				}else{
					TmpMass[0]=Rec_buf_data_uart[4]/10+0x30;
					TmpMass[1]=Rec_buf_data_uart[4]%10+0x30;
					TmpMass[2]='0';
				}
			}
		}break;
		case 0x13:
		case 0x1A:{ //задержка на выключение (приемник)
			if (command==0x13) TmpMass=ValuePrmTimeOff;
			else TmpMass=ValuePrmTimeOff2;
			
			for (uint8_t i = 0; i < Rec_buf_data_uart[3]; i++) {
				if ((Rec_buf_data_uart[4 + i]<RangPrm[2] [0]) || 
					(Rec_buf_data_uart[4 + i]>RangPrm[2] [1])) { 
					TmpMass[i]=0xFF;
				} else {
					TmpMass[i] = Rec_buf_data_uart[4 + i];
				}
			}
		}break;
		case 0x14:
		case 0x1B: { //блокировка команд на приеме
			if (command==0x14) TmpMass=ValuePrmBlockCom;
			else TmpMass=ValuePrmBlockCom2;
			
			for(uint8_t i = 0; i < Rec_buf_data_uart[3]; i++) { 
				TmpMass[i] = Rec_buf_data_uart[4 + i];
			}
		}break;
		case 0x15:
		case 0x1C:{ //длительные команды
			if (command==0x15) TmpMass=ValuePrmLongCom;
			else TmpMass=ValuePrmLongCom2;
			
			for(uint8_t i = 0; i < Rec_buf_data_uart[3]; i++) { 
				TmpMass[i] = Rec_buf_data_uart[4 + i];
			}
		}break;
	}
	RecivVar=1;
  	LCD2new=1;
};


void FParamPrd(unsigned char command){
	switch(command){
		case 0x21:
		{ //время включения (передатчик)
			if (Rec_buf_data_uart[4]>RangPrd[0] [1]){
				MenuPrdTimeOn[0]='?';MenuPrdTimeOn[1]='?';
			}else{
				MenuPrdTimeOn[0]=Rec_buf_data_uart[4]/10+0x30;
				MenuPrdTimeOn[1]=Rec_buf_data_uart[4]%10+0x30;
			}
		}break;
		case 0x22:{//длительность команды (передатчик)
			if ((Rec_buf_data_uart[4]<RangPrd[1] [0])||(Rec_buf_data_uart[4]>RangPrd[1] [1])){
				MenuPrdTimeCom[0]='?';
				MenuPrdTimeCom[1]='?';
				MenuPrdTimeCom[2]='?';
			}else{
				if (Rec_buf_data_uart[4]<10){
					MenuPrdTimeCom[0]=Rec_buf_data_uart[4]+0x30;
					MenuPrdTimeCom[1]='0';
					MenuPrdTimeCom[2]=' ';
				}else{
					MenuPrdTimeCom[0]=Rec_buf_data_uart[4]/10+0x30;
					MenuPrdTimeCom[1]=Rec_buf_data_uart[4]%10+0x30;
					MenuPrdTimeCom[2]='0';
				}
			}
		}break;
		case 0x23:{ //время на повторное формирование команды (передатчик)
			if ((Rec_buf_data_uart[4]<RangPrd[2] [0])||(Rec_buf_data_uart[4]>RangPrd[2] [1])){
				MenuPrdTimeRep[0]='?';
				MenuPrdTimeRep[1]='?';
				MenuPrdTimeRep[2]='?';
			}else{
				if (Rec_buf_data_uart[4]<10){
					MenuPrdTimeRep[0]=Rec_buf_data_uart[4]+0x30;
					MenuPrdTimeRep[1]='0';
					MenuPrdTimeRep[2]=' ';
				}else{
					MenuPrdTimeRep[0]=Rec_buf_data_uart[4]/10+0x30;
					MenuPrdTimeRep[1]=Rec_buf_data_uart[4]%10+0x30;
					MenuPrdTimeRep[2]='0';
				}
			}
		}break;
		case 0x24:{//блокировка команд (передатчик)
			for(uint8_t i = 0; i < Rec_buf_data_uart[3]; i++) { 
				ValuePrdBlockCom[i] = Rec_buf_data_uart[4 + i];
			}
		}break;
		case 0x25:{
			for(uint8_t i = 0; i < Rec_buf_data_uart[3]; i++) {
				ValuePrdLongCom[i] = Rec_buf_data_uart[4 + i];
			}
		}break;
	}
	RecivVar=1;
	LCD2new=1;
};


/**	Команда текущего состояния
 *	@param Нет
 *	@return Нет
 */
void FCurrentState(void)
{
#ifdef EXHIBITION
	Rec_buf_data_uart[4] = 2;
	Rec_buf_data_uart[5] = 1;
	for(char i = 6; i <= 15; i++)
		Rec_buf_data_uart[i] = 0;
#endif	
	
	for (char i = 0; i < 4; i++)
	{ //сделаем проверку принятого состояния и перепишем значение в массив
    	if (Rec_buf_data_uart[(i * 3) + 4] > 0x05)
			CurrentState[i * 2] = 0x4E;
    	else
			CurrentState[i * 2] = Rec_buf_data_uart[(i * 3) + 4];
		
    	if (Rec_buf_data_uart[(i * 3) + 5] > 0x0B)
			CurrentState[(i * 2) + 1] = 0x4E;
    	else
			CurrentState[(i * 2) + 1] = Rec_buf_data_uart[(i * 3) + 5];
		
    	Dop_byte[i] = Rec_buf_data_uart[(i * 3) + 6];
  	}
	
  	RecivVar=1;
}

/**	Команда общих неисправностей/предупреждений
 *	@param Нет
 *	@return Нет
 */
void FGlobalCurrentState(void)
{
#ifdef EXHIBITION
	for (char i = 4; i <= 23; i++)
		Rec_buf_data_uart[i] = 0;
#endif

	for (char i = 0; i < 20; i++) 
		GlobalCurrentState[i] = Rec_buf_data_uart[i + 4];

	/*
#if DEB // установка предупреждения/неисправности
	for (char i = 0; i <= 20; i++)
		GlobalCurrentState[i] = 0;
	
	GlobalCurrentState[14] = 0;
	GlobalCurrentState[15] = 0x40;
#endif
	*/
	bGlobalAvar = (GlobalCurrentState[12] != 0) || (GlobalCurrentState[13] != 0) ? true : false;
	bGlobalWarn = (GlobalCurrentState[14] != 0) || (GlobalCurrentState[15] != 0) ? true : false;
	
	bDefAvar = (GlobalCurrentState[0] != 0) || (GlobalCurrentState[1] != 0) ? true : false;
	bDefWarn = (GlobalCurrentState[2] != 0) || (GlobalCurrentState[3] != 0) ? true : false;
	
	// в случае Р400 ПВЗУ-Е используется доп.байт с номерами аппарата , передаются битами
	// 0 бит - 1 аппарат
	// 1 бит - 2 аппарат
	// 2 бит - 3 аппарат
	// ...
	// 8 бит - 8 аппарат
	uint8_t mask = 0;
	for(uint8_t i = 0; i < cNumLine; i++) {
		mask |= (1 << i);
	}
	NumDevError = GlobalCurrentState[4] & mask;
	
	// дополнительное значение используемое в неиспрановтси ДФЗ в совместимости ПВЗУ
	getNumDfzError(GlobalCurrentState[5]);
	
	
	bRec1Avar = (GlobalCurrentState[4] != 0) || (GlobalCurrentState[5] != 0) ? true : false;
	bRec1Warn = (GlobalCurrentState[6] != 0) || (GlobalCurrentState[7] != 0) ? true : false;
	
	bTrAvar = (GlobalCurrentState[8] != 0) || (GlobalCurrentState[9] != 0) ? true : false;
	bTrWarn = (GlobalCurrentState[10] != 0) || (GlobalCurrentState[11] != 0) ? true :false;
	
	bRec2Avar = (GlobalCurrentState[16] != 0) || (GlobalCurrentState[17]!=0) ? true : false;
	bRec2Warn = (GlobalCurrentState[18] != 0) || (GlobalCurrentState[19]!=0) ? true : false;
	
	RecivVar=1;
}

// заполнение переменной для вывода значения при неисправности ДФЗ в совместимости с ПВЗУ
// диапазон значений 0.255, выводится только нужное кол-во цифр (не менее 1).
void getNumDfzError(uint8_t val) {
	uint8_t i = 0;
	uint8_t tmp = val;
	if (val >= 100) {	
		NumDfzError[i++] = tmp / 100 + '0';
		tmp = tmp % 100;
	}
	if (val >= 10) {
		NumDfzError[i++] = tmp / 10 + '0';
	}
	NumDfzError[i++] = tmp % 10 + '0';
	
	while(i <= 3) {
		NumDfzError[i++] = ' ';
	}
}

void FDataTime(void){
	DataLCD[7] = (Rec_buf_data_uart[4]&0x0F)+0x30; //1-цы лет
	DataLCD[6] = (Rec_buf_data_uart[4]>>4)+0x30;  //10-ки лет
	DataLCD[4] = (Rec_buf_data_uart[5]&0x0F)+0x30;  //1-цы мес
	DataLCD[3] = (Rec_buf_data_uart[5]>>4)+0x30;  //10-и мес
	DataLCD[1] = (Rec_buf_data_uart[6]&0x0F)+0x30;  //1-цы дней
	DataLCD[0] = (Rec_buf_data_uart[6]>>4)+0x30;  //10-и дней
	
	TimeLCD[1] = (Rec_buf_data_uart[7]&0x0F)+0x30; //1-цы час
	TimeLCD[0] = (Rec_buf_data_uart[7]>>4)+0x30;  //10-ки час
	TimeLCD[4] = (Rec_buf_data_uart[8]&0x0F)+0x30;  //1-цы мин
	TimeLCD[3] = (Rec_buf_data_uart[8]>>4)+0x30;  //10-и мин
	TimeLCD[7] = (Rec_buf_data_uart[9]&0x0F)+0x30;  //1-цы сек
	TimeLCD[6] = (Rec_buf_data_uart[9]>>4)+0x30;  //10-и сек
	
	//Проверка на достовереность
	for (uint8_t i = 0; i < 8; i++){
		if (((DataLCD[i] > '9') || (DataLCD[i] < '0')) && (DataLCD[i]!='.')) { 
			DataError++; 
		} else {
			DataError=0;
		}
		if (((TimeLCD[i] > '9')||(TimeLCD[i] < '0')) && (TimeLCD[i]!=':')) {
			TimeError++; 
		} else {
			TimeError=0;
		}
	}
	
	if (((DataLCD[7]-0x30)+((DataLCD[6]-0x30)*10))>99)  DataError++;
	if (((DataLCD[4]-0x30)+((DataLCD[3]-0x30)*10))>12)  DataError++;
	if (((DataLCD[1]-0x30)+((DataLCD[0]-0x30)*10))>31)  DataError++;
	if (((TimeLCD[1]-0x30)+((TimeLCD[0]-0x30)*10))>24)  TimeError++;
	if (((TimeLCD[4]-0x30)+((TimeLCD[3]-0x30)*10))>60)  TimeError++;
	if (((TimeLCD[7]-0x30)+((TimeLCD[6]-0x30)*10))>60)  TimeError++;
	
	if (DataError !=0 ){
		DataLCD[7]='0'; //1-цы лет
		DataLCD[6]='0';  //10-ки лет
		DataLCD[4]='0';  //1-цы мес
		DataLCD[3]='0';  //10-и мес
		DataLCD[1]='0';  //1-цы дней
		DataLCD[0]='0';  //10-и дней
		DataError=0;
		for (uint8_t i = 0; i < 3; i++) { 
			TrDataTimeMass[i] = 0x00;
		}
	} else {
		for (uint8_t i = 0; i < 3; i++) { 
			TrDataTimeMass[i] = Rec_buf_data_uart[4 + i];
		}
	}
	
	if (TimeError!=0){
		TimeLCD[1]='0'; //1-цы час
		TimeLCD[0]='0';  //10-ки час
		TimeLCD[4]='0';  //1-цы мин
		TimeLCD[3]='0';  //10-и мин
		TimeLCD[7]='0';  //1-цы сек
		TimeLCD[6]='0';  //10-и сек
		TimeError=0;
		for (uint8_t i = 0; i < 3; i++) {
			TrDataTimeMass[i + 3] = 0x00;
		}
	} else {
		for (uint8_t i = 0; i < 3; i++) {
			TrDataTimeMass[i + 3] = Rec_buf_data_uart[4 + i + 3];
		}
	}
	
	RecivVar=1;
	LCDtimerNew=1; //говорим, что было получено новое время и дата
};

void fDopCodeToChar(unsigned char *Mass, unsigned char StartAddr, unsigned char Factor, unsigned char Param, unsigned char Value){  //массив, начальный адрес, множитель, параметр
	unsigned char i;
	//множитель 1 или 2, других значений быть не должно
	Factor--;
	
	for(i=StartAddr; i<8; i++) Mass[i]=' ';
	
	if (Value>127){ //проверка на отрицательное число
		Value=(Value^0xFF)+1;
		Mass[StartAddr]='-'; StartAddr++;
	}
	
	Value=Value<<Factor;
	
	if (Value<99){
		Mass[StartAddr]=Value/10+0x30; StartAddr++;
		Mass[StartAddr]=Value%10+0x30; StartAddr++;
	}else{
		Mass[StartAddr]='?'; StartAddr++;
		Mass[StartAddr]='?'; StartAddr++;
	}
	
	switch(Param){
		case 1:{
			Mass[StartAddr]='г';
		}break;
		case 2:{
			Mass[StartAddr]='д';
			Mass[StartAddr+1]='Б';
		}break;
	}
}

/** Преобразование целого числа в строку.
 *
 *	Если число больше максимума, будут записаны "??".
 *
 *	@param *Mass Указатель на начало строки.
 *	@param StartAddr Начальный символ в строке для записи числа.
 *  @param Param Тип параметра, для записи размерности.
 *	@arg 1 - "мА"
 *	@arg 2 - "%"
 *  @arg 3 - "г"
 *	@arg 4 - " сек"
 *	@param Value Число от 0 до 9999 включительно.
 *	@param Max Максимальное значение числа (включительно).
 */
void fIntCodeToChar(unsigned char *Mass, unsigned char StartAddr,  unsigned char Param, unsigned int Value, unsigned int Max){
	unsigned char i;
	
	for(i = StartAddr; i < 8; i++) 
		Mass[i]=' ';
	
	if (Value <= Max) {
		if (Value > 999){
			Mass[StartAddr] = Value/1000;
			Value = Value - Mass[StartAddr]*1000;
			Mass[StartAddr++] += '0'; 
		}
		if (Value > 99) {
			Mass[StartAddr] = Value/100;
			Value = Value - Mass[StartAddr]*100;
			Mass[StartAddr++] += '0'; 
		}
		Mass[StartAddr++] = Value/10 + '0'; 
		Mass[StartAddr++] = Value%10 + '0'; 
	} else {
		Mass[StartAddr++] = '?'; 
		Mass[StartAddr++] = '?'; 
	}
	
	switch(Param) {
		case 1: {
			Mass[StartAddr++]='м';
			Mass[StartAddr]  ='А';
		} break;
		
		case 2: {
			Mass[StartAddr]  ='%';
		} break;
		case 3: {
			Mass[StartAddr]  ='г';
		} break;
		case 4: {
			Mass[StartAddr++]=' ';
			Mass[StartAddr++]='с';
			Mass[StartAddr++]='е';
			Mass[StartAddr++]='к';
		} break;
		case 5: {
			Mass[StartAddr++]=' ';
			Mass[StartAddr++]='м';
			Mass[StartAddr++]='и';
			Mass[StartAddr++]='н';
		} break;
	}
}

/** Преобразование HEX кода в строку.
 *
 *	@param *Mass Указатель на начало строки.
 *	@param StartAddr Начальный символ в строке для записи числа.
 *	@param Hex Число от 0x00 до 0xFF включительно.
 */
void HexToViewHex(unsigned char *Mass, unsigned char StartAddr, unsigned char Hex)
{
	unsigned char t1;
	
  	t1=Hex >> 4;
  	t1 = ( t1 > 9) ? (t1 + 0x37) : (t1 + 0x30);
  	Mass[StartAddr] = t1;
  	t1 = Hex & 0x0F;
  	t1 = ( t1 > 9) ? (t1 + 0x37) : (t1 + 0x30);
  	Mass[StartAddr + 1] = t1;
}

extern strCorrParam sCorrParam[];

void FCorrParam(void){
	signed char temp1, temp2;
	signed int temp3;
	unsigned char step;
	//напряжение
	temp1=(signed char) Rec_buf_data_uart[4];
	temp2=(signed char) Rec_buf_data_uart[5];
	sCorrParam[0].Corr=0; //по умолчанию считаем коррекцию нулевой
	if ((temp1>99)||(temp1<-99)||(temp2>90)||temp2<-90){  //вне диапазона
		sCorrParam[0].Print[0]='?';
		sCorrParam[0].Print[1]='?';
		sCorrParam[0].Print[2]=0x00;
	}else{
		step=0;
		sCorrParam[0].Print[step++]= ((temp1|temp2)&0x80)? '-' : '+'; //знак числа;
		if (temp1<0) temp1=0x100 - temp1;
		if (temp2<0) temp2=0x100 - temp2;
		if (!(temp1|temp2)){  //если нулевая коррекция
			sCorrParam[0].Print[0]='0';
			sCorrParam[0].Print[1]=0x00;
		}
		if (temp1>9){
			sCorrParam[0].Print[step++]=(temp1/10) + 0x30;
		}
		sCorrParam[0].Print[step++]=(temp1%10) + 0x30;
		sCorrParam[0].Print[step++]='.';
		sCorrParam[0].Print[step++]=(temp2/10) + 0x30;
		sCorrParam[0].Print[step++]='В';
		sCorrParam[0].Print[step++]=0x00;
		
		sCorrParam[0].Corr=(temp1*10) + (temp2/10);
		if ( sCorrParam[0].Print[0] == '-' )  sCorrParam[0].Corr = 0x10000 - sCorrParam[0].Corr;
	}
	//ток 1 и 2
	for(char i=1; i<3; i++){
		temp3=(signed int) (Rec_buf_data_uart[4+2*i]<<8) + Rec_buf_data_uart[5+2*i];
		sCorrParam[i].Corr=0; //по умолчанию считаем коррекцию нулевой
		if ((temp3>999)||(temp3<-999)){//если ошибочное значение
			sCorrParam[i].Print[0]='?';
			sCorrParam[i].Print[1]='?';
			sCorrParam[i].Print[2]=0x00;
		}else{
			if (temp3==0){  //если нулевая коррекция
				sCorrParam[i].Print[0]='0';
				sCorrParam[i].Print[1]=0x00;
			}else{
				step=0;
				sCorrParam[i].Corr=temp3;
				sCorrParam[i].Print[step++]= (temp3>0)? '+' : '-';
				if (temp3<0) temp3=(temp3^0xFFFF) + 1;
				if (temp3>99){
					sCorrParam[i].Print[step]=(temp3/100);
					temp3=temp3 - (sCorrParam[i].Print[step]*100);
					sCorrParam[i].Print[step]+=0x30;
					step++;
				}
				if (temp3>9){
					sCorrParam[i].Print[step++]=(temp3/10) + 0x30;
				}
				sCorrParam[i].Print[step++]=(temp3%10) + 0x30;
				sCorrParam[i].Print[step++]='м';
				sCorrParam[i].Print[step++]='А';
				sCorrParam[i].Print[step++]=0x00;
				
			}
		}//end if(temp3>999 <-999)
	}//end for (i<2)
}

extern strParamOpt	sParamOpt;

void vfOptParam(void)
{
	uint8_t tmp;
	// протокол обмена
	
	tmp = Rec_buf_data_uart[4];
	if ( (tmp < RangGlb[19] [0]) || (tmp > RangGlb[19] [1]) )
		tmp = RangGlb[19] [1] + 1;
	sParamOpt.reserv = tmp;
}

void FMeasureParam(void)
{
#ifdef EXHIBITION
	for(char i = 5; i <= 18; i++)
		Rec_buf_data_uart[i] = 0;
#endif	
	
	unsigned int itmp;
	if (Rec_buf_data_uart[4]==0x00)
	{  //пришли все параметры
		//коэффициент перекрытия
		fDopCodeToChar(Iline1,2,2,1,Rec_buf_data_uart[5]);
		HexToViewHex(Iline1H,3,Rec_buf_data_uart[5]);
		HexToViewHex(Iline1H,5,Rec_buf_data_uart[6]);
		//ток первый
		IlineValue = (Rec_buf_data_uart[7] << 8) + Rec_buf_data_uart[8];  //значение для вычисления коррекции
		fIntCodeToChar(Iline2,3,1,IlineValue,999);
		//напряжение на линии
		Uline[5]=Rec_buf_data_uart[10] / 10;
		UlineValue=((signed int) Rec_buf_data_uart[9])*10 + Uline[5];  //значение для вычисления коррекции
		if ((UlineValue>999)||(UlineValue<0)||(Uline[5]>9)){
			UlineValue=0;
			Uline[2]='?';
			Uline[3]='?';
			Uline[5]='?';
		}else{
			Uline[2]=(Rec_buf_data_uart[9]/10)+0x30;
			Uline[3]=(Rec_buf_data_uart[9]%10)+0x30;
			Uline[5]+=0x30;
		}
		//напряжение защиты
        udef1 = Rec_buf_data_uart[11];
		fDopCodeToChar(Usigndef1, 3, 1, 2, udef1);        
		if (cNumLine==3) {
            udef2 = Rec_buf_data_uart[12];
			fDopCodeToChar(Usigndef2, 3, 1, 2, udef2);
        }
		
		//контрльная частота
		if ( (cAutoControl == 4) && (CurrentState[0] < 4) )
		{   //если АК выкл и не тест то Uk всегда 0
			Rec_buf_data_uart[13]=0;	// Uk1
			Rec_buf_data_uart[14]=0;	// Uk2
			Rec_buf_data_uart[19]=0;	// UK3
			Rec_buf_data_uart[20]=0;	// Uk4
			Rec_buf_data_uart[21]=0;	// Uk5
			Rec_buf_data_uart[22]=0;	// Uk6
			Rec_buf_data_uart[23]=0;	// Uk7
			Rec_buf_data_uart[24]=0;	// Uk8
		}
        
        ucf1 = Rec_buf_data_uart[13];
		fDopCodeToChar(Uinkch1, 3, 1, 2, ucf1);
		if (cNumLine == 3) {
            ucf2 = Rec_buf_data_uart[14];
			fDopCodeToChar(Uinkch2, 3, 1, 2, ucf2);
		} else if ((cNumLine > 3) && (TypeUdDev == TYPE_UD_DEV_PVZUE)) {
			// в ПВЗУ-Е может быть до 8 Uk
			fDopCodeToChar(Uinkch2,3,1,2,Rec_buf_data_uart[14]);
			fDopCodeToChar(Uinkch3,3,1,2,Rec_buf_data_uart[19]);
			fDopCodeToChar(Uinkch4,3,1,2,Rec_buf_data_uart[20]);
			fDopCodeToChar(Uinkch5,3,1,2,Rec_buf_data_uart[21]);
			fDopCodeToChar(Uinkch6,3,1,2,Rec_buf_data_uart[22]);
			fDopCodeToChar(Uinkch7,3,1,2,Rec_buf_data_uart[23]);
			fDopCodeToChar(Uinkch8,3,1,2,Rec_buf_data_uart[24]);
		}
		
		
		//использование динамического диапазона приемника
		fDopCodeToChar(Kd,3,1,2,Rec_buf_data_uart[15]);
		//коэффициент переполнения АЦП
		fIntCodeToChar(Kov,4,2,Rec_buf_data_uart[16],99);
		HexToViewHex(KovH,3,Rec_buf_data_uart[16]);
		// Длительность импульсов ВЧ блокировки
		itmp=(Rec_buf_data_uart[17]<<8)+Rec_buf_data_uart[18];
		fIntCodeToChar(Pk,3,3,itmp,360);
		HexToViewHex(PkH,3,Rec_buf_data_uart[17]);
		HexToViewHex(PkH,5,Rec_buf_data_uart[18]);
	}
	LCDparam=1;
	RecivVar=1;
}

void FParamGlobal(unsigned char command)
{
	switch(command)
	{
		case 0x35:{  //синхронизация часов (общие)
			if (Rec_buf_data_uart[4]>RangGlb[1] [1]) MenuAllSynchrTimer=0x02;
			else MenuAllSynchrTimer=Rec_buf_data_uart[4];
		}break;
		case 0x36:{ //удержание реле команд приемника (общие)
			if ( (Rec_buf_data_uart[4]<RangGlb[2] [0]) || (Rec_buf_data_uart[4]>RangGlb[2] [1]) )
			{
				MenuAllKeepComPRM[0] = '?';
				MenuAllKeepComPRM[1] = '?';
			}
			else
			{
				MenuAllKeepComPRM[0] = (Rec_buf_data_uart[4] / 10) + '0';
				MenuAllKeepComPRM[1] = (Rec_buf_data_uart[4] % 10) + '0';
			}
		}break;
		case 0x37:
		{ //тип удаленного аппарата
			if (Rec_buf_data_uart[4] > RangGlb[0] [1])
			{
				TypeUdDev = TYPE_UD_DEV_MAX;
				sMenuGlbParam.dev = 0xFF;
			}
			else
			{
				TypeUdDev = (typeUdDev_t) Rec_buf_data_uart[4];
				if (TypeUdDev != sMenuGlbParam.dev)
				{			
					sMenuGlbParam.dev = TypeUdDev;
					MenuParamGlbCreate();
					MenuParamDefCreate();
					MenuUprCreate(1);
					MenuACCreate();
					MenuAKCreate();
					MenuTestCreate();
					if ( (MenuLevel == LVL_GLB_VIEW) || (MenuLevel == LVL_GLB_SETUP) )
					{
						MaxShiftMenu = sMenuGlbParam.num - 1;
						if (ShiftMenu > MaxShiftMenu)
							ShiftMenu = MaxShiftMenu;
					}
					else if ( (MenuLevel == LVL_DEF_VIEW) || (MenuLevel == LVL_DEF_SETUP) )
					{
						MaxShiftMenu = sMenuDefParam.num - 1;
						if (ShiftMenu > MaxShiftMenu)
							ShiftMenu = MaxShiftMenu;
					}
					else if (MenuLevel == LVL_UPR)
					{
						MaxShiftMenu = sMenuUpr.num - 3;
						if (ShiftMenu > MaxShiftMenu)
							ShiftMenu = MaxShiftMenu;
					}
				}
			}
		}
		break;
		case 0x38: {
            //адрес аппарата в локальной сети (общие)
            adrLan = Rec_buf_data_uart[4];
		}break;
		case 0x39:
		{ 	// Оптика - "Время перезапуска"
			// ВЧ - параметры ПВЗУ-Е
			uint8_t tmp;
			
			if (cTypeLine == 2)
			{
				tmp = Rec_buf_data_uart[4];
				MenuAllTimeRerun[0] = (tmp > RangGlb[5] [1]) ? '0' : tmp + '0';
					
				return;
			}
			
			// В ПВЗЛ используется первый параметр
			// остальные в ПВЗУ-Е
			if (TypeUdDev == TYPE_UD_DEV_PVZL)
			{
				//снижение уровня АК
				tmp = Rec_buf_data_uart[4];
				if ( (tmp < RangGlb[20] [0] || (tmp > RangGlb[20] [1]) ) )
				{
					MenuAllLowCF[0] = '?';
					MenuAllLowCF[1] = '?';
				}
				else
				{
					MenuAllLowCF[0] = (tmp / 10) + '0';
					MenuAllLowCF[1] = (tmp % 10) + '0';
				}
			}
			else
			{
				// протокол обмена
				tmp = Rec_buf_data_uart[4];
				if ( (tmp < RangGlb[13] [0]) || (tmp > RangGlb[13] [1]) )
					tmp = RangGlb[13] [1] + 1;
				sParamPVZE.protocol = tmp;
				
				// признак четности
				tmp = Rec_buf_data_uart[5];
				if ( (tmp < RangGlb[14] [0]) || (tmp > RangGlb[14] [1]) )
					tmp = RangGlb[14] [1] + 1;
				sParamPVZE.parity = tmp;
				
				// допустимые провалы
				tmp = Rec_buf_data_uart[6];
				if ( (tmp < RangGlb[15] [0]) || (tmp > RangGlb[15] [1]) )
				{
					sParamPVZE.proval[0] = '?';
					sParamPVZE.proval[1] = '?';
					sParamPVZE.proval[2] = '?';
				}
				else
				{
					sParamPVZE.proval[2] = (tmp % 10) + '0';
					tmp = tmp / 10;
					sParamPVZE.proval[1] = (tmp % 10) + '0';
					sParamPVZE.proval[0] = (tmp / 10) + '0'; 
				}
				
				// порог по помехе
				tmp = Rec_buf_data_uart[7];
				sParamPVZE.porog[2] = (tmp % 10) + '0';
				tmp = tmp / 10;
				sParamPVZE.porog[1] = (tmp % 10) + '0';
				sParamPVZE.porog[0] = (tmp / 10) + '0';
				
				// допустимая помеха
				tmp = Rec_buf_data_uart[8];
				if ( (tmp < RangGlb[17] [0]) || (tmp > RangGlb[17] [1]) )
				{
					sParamPVZE.noise[0] = '?';
					sParamPVZE.noise[1] = '?';
				}
				else
				{
					sParamPVZE.noise[0] = (tmp / 10) + '0';
					sParamPVZE.noise[1] = (tmp % 10) + '0';
				}
				
				// тип автоконтроля
				tmp = Rec_buf_data_uart[9];
				if ( (tmp < RangGlb[18] [0]) || (tmp > RangGlb[18] [1]) )
					tmp = RangGlb[18] [1] + 1;
				sParamPVZE.autocontrol = tmp;
				
				// период беглого режима АК
				tmp = Rec_buf_data_uart[10];
				if ( (tmp < RangGlb[21] [0]) || (tmp > RangGlb[21] [1]) ) {
					sParamPVZE.periodAC[0] = '?';
					sParamPVZE.periodAC[1] = '?';
					sParamPVZE.periodAC[1] = '?';
				} else {
					fIntCodeToChar(sParamPVZE.periodAC, 0, 4, tmp, RangGlb[21] [1]);
				}
				
				// период повтора беглого режима АК
				tmp = Rec_buf_data_uart[11];
				if ( (tmp < RangGlb[22] [0]) || (tmp > RangGlb[22] [1]) ) {
					sParamPVZE.periodACre[0] = '?';
					sParamPVZE.periodACre[1] = '?';
					sParamPVZE.periodACre[2] = '?';
				} else {
					fIntCodeToChar(sParamPVZE.periodACre, 0, 4, tmp, RangGlb[22] [1]);
				}
				
				tmp = Rec_buf_data_uart[12];
				if ( (tmp < RangGlb[23] [0]) || (tmp > RangGlb[23] [1]) ) {
					sParamPVZE.timeCorrAC[0] = '?';
					sParamPVZE.timeCorrAC[1] = '?';
				} else {
					fIntCodeToChar(sParamPVZE.timeCorrAC, 0, 5, tmp, RangGlb[23] [1]);
				}
			}
			
		}
		break;
		case 0x3A:{ //частота (общие)
			Pk_temp = (Rec_buf_data_uart[4]<<8) + Rec_buf_data_uart[5];
			Rec_buf_data_uart[4]=0;
			
			if (Pk_temp<RangGlb[6] [0]) Rec_buf_data_uart[4]=1;
			else
				if (Pk_temp>RangGlb[6] [1]) Rec_buf_data_uart[4]=1;
			
			if (Rec_buf_data_uart[4]){
				MenuAllFreq[0] = '?';MenuAllFreq[1] = '?';MenuAllFreq[2] = '?';MenuAllFreq[3] = ' ';
				MenuAllFreq[4] = 'к';MenuAllFreq[5] = 'Г';MenuAllFreq[6] = 'ц';
				
				FreqNum[0]='?';FreqNum[1]='?';FreqNum[2]='?';
			}else{
				if (Pk_temp<100){
					MenuAllFreq[0] = Pk_temp/10 + '0';
					MenuAllFreq[1] = Pk_temp%10 + '0';
					MenuAllFreq[2] = ' ';
					MenuAllFreq[3] = 'к';
					MenuAllFreq[4] = 'Г';
					MenuAllFreq[5] = 'ц';
					MenuAllFreq[6] = ' ';
				} else if (Pk_temp < 1000) {
					MenuAllFreq[0] = Pk_temp/100 + '0'; Pk_temp %= 100;
					MenuAllFreq[1] = Pk_temp/10 + '0';
					MenuAllFreq[2] = Pk_temp%10 + '0';
					MenuAllFreq[3] = ' ';
					MenuAllFreq[4] = 'к';
					MenuAllFreq[5] = 'Г';
					MenuAllFreq[6] = 'ц';
				} else if (Pk_temp < 10000) {
					MenuAllFreq[0] = Pk_temp/1000 + '0'; Pk_temp %= 1000;
					MenuAllFreq[1] = Pk_temp/100 + '0'; Pk_temp %= 100;
					MenuAllFreq[2] = Pk_temp/10 + '0';
					MenuAllFreq[3] = Pk_temp%10 + '0';
					MenuAllFreq[4] = 'к';
					MenuAllFreq[5] = 'Г';
					MenuAllFreq[6] = 'ц';
				}
				
				
				
				FreqNum[0]=MenuAllFreq[0];
				FreqNum[1]=MenuAllFreq[1];
				FreqNum[2]=MenuAllFreq[2];
			}//end else if (Rec_buf_data_uart[4])
			LCDtimerNew=1;
		}break;
		case 0x3B:{ //номер аппарата (общие)
			
			uint8_t min = RangGlb[7] [0];
			uint8_t max = RangGlb[7] [1];
			
			if (TypeUdDev == TYPE_UD_DEV_PVZUE) {
				max = cNumLine;
			}
				
			if ((Rec_buf_data_uart[4] < min)||(Rec_buf_data_uart[4] > max)){
				MenuAllNumDevice[0] = '?';
				FreqNum[7]='?';
			} else {
				MenuAllNumDevice[0] = Rec_buf_data_uart[4] + '0';
				FreqNum[7] = MenuAllNumDevice[0];
			}
			LCDtimerNew=1;
		}break;
		case 0x3C:{ //пороги КЧ
			uint8_t tmp = 0;
			
			//Попрог предупреждения по КЧ
			tmp = Rec_buf_data_uart[4];
			if (tmp > RangGlb[9] [1]) {
				MenuAllCF[0] = 0x3F;
				MenuAllCF[1] = 0x3F;
			}
			else {
				MenuAllCF[0] = tmp/10 + '0';
				MenuAllCF[1] = tmp%10 + '0';
			}
			
			//снижение чувствительности по КЧ (КЧ1)
			tmp = Rec_buf_data_uart[5];
			if (tmp > RangGlb[10] [1]) {
				MenuVoltageLimitPRM1[0] = 0x3F;
				MenuVoltageLimitPRM1[1] = 0x3F;
			}
			else {
				MenuVoltageLimitPRM1[0] = tmp/10 + '0';
				MenuVoltageLimitPRM1[1] = tmp%10 + '0';
			}
			
			//снижение чувствительности по КЧ2
			if (cNumLine == 3) {
				tmp = Rec_buf_data_uart[6];
				if (tmp > RangGlb[10] [1]) {
					MenuVoltageLimitPRM2[0] = 0x3F;
					MenuVoltageLimitPRM2[1] = 0x3F;
				}
				else {
					MenuVoltageLimitPRM2[0] = tmp/10 + '0';
					MenuVoltageLimitPRM2[1] = tmp%10 + '0';
				}
			}
			
			//порог аварии по КЧ
			tmp = Rec_buf_data_uart[7];
			if (tmp > RangGlb[24] [1]) {
				MenuAllLowCFa[0] = '?';
				MenuAllLowCFa[1] = '?';
			}
			else {
				MenuAllLowCFa[0] = tmp/10 + '0';
				MenuAllLowCFa[1] = tmp%10 + '0';
			}
			
		}break;
		case 0x3D:{ //контроль выходного сигнала
			if (Rec_buf_data_uart[4] > RangGlb[8] [1]) { 
				MenuAllControlUout = 2;
			} 
			else {
				MenuAllControlUout = Rec_buf_data_uart[4];
			}
		}
	}
	RecivVar=1;
	LCD2new=1;
};

void FArchive(void){
	bool er=false;
	
	RecivVar=1;
	LCD2new=1;
	
	//проверка на соответствие принятой команды, текущему пункту меню
	if ((0x0F - (Rec_buf_data_uart[2]>>4)) == sArchive.Dev[sArchive.CurrDev])  er=true;
	
	if ((Rec_buf_data_uart[2]&0x0F)==0x01){ //кол-во записей архива
		if (er){  //если получена команда этого архива
			if (Rec_buf_data_uart[5]) {
				sArchive.RecCount=256;
				sArchive.CurCount=Rec_buf_data_uart[4];
			}else{
				sArchive.RecCount = Rec_buf_data_uart[4];
				sArchive.CurCount = 0;
			}
		}
	}
	
	if ((Rec_buf_data_uart[2]&0x0F)==0x02){ //записи архива
		unsigned char i;
		if(er){ //если получена команда этого архива
			for(i=0; i<16; i++) sArchive.Data[i]=Rec_buf_data_uart[4+i];
		}else{
			for(i=0; i<16; i++) sArchive.Data[i]=0x00;
		}
	}
}

extern strMenuTest sMenuTest;

/** Определение сигналов в тестовых режимах
 *	Определяет первый выставленный сигнал в каждой из групп
* 	Например: при наличии Ком1, Ком2, Ком10 - определена будет только Ком1
 * 	@param com Номер команды (на данный момент не используется)
 *	@return Нет
 */
void FTest1(unsigned char com)
{
	// 4-ый байт: 0x76543210 ;
	// 	бит 0 - кч1 
	//	бит 1 -	кч2
	//	бит 2 - кч3
	//	бит 3 - кч4
	//	бит 4 - РЗ1
	//	бит 5 - РЗ2
	// 5-ой байт: 0xhgfedcba ; a- 1ком, h- 8ком
	// 6-ой байт: 0xhgfedcba ; a- 9ком, h- 16ком
	// 7-ой байт: 0xhgfedcba ; a- 17ком, h- 24ком
	// 8-ой байт: 0xhgfedcba ; a- 25ком, h- 32ком
	uint8_t sign = 0;
	uint8_t tmp = 0;
	
	// Изначально проверим наличие сигналов КЧ
	// Если их нет и есть прм/прд,  проверим наличие сигналов команд
	sign = SIGN_OFF;
	tmp = Rec_buf_data_uart[4];
	if (tmp & 0x0F)
	{
		
		if (tmp & 0x01)
			sign = SIGN_CF1;	
		else if (tmp & 0x02)
			sign = SIGN_CF2;
		
		// В случае трехконцевой линии
		// проверим наличие КЧ3 и КЧ4 
		if ( (cNumLine == 3) && (sign == SIGN_OFF) )
		{
			if (tmp & 0x04)
				sign = SIGN_CF3;
			else if (tmp & 0x08)
				sign = SIGN_CF4;
		}
	}
	else if ( (cNumComR > 0) || (cNumComT > 0) )
	{
		// максимаьлное кол-во команд
		signed char num_com = (cNumComR > cNumComT) ? cNumComR : cNumComT;
		// указатель на байт данных с командами
		uint8_t *ptr = &Rec_buf_data_uart[5];
		// номер первой команды в текущем байте данных
		uint8_t cur_sign = SIGN_COM1;
		
		// Проверяем текущий байт данных на наличие команд
		// При первом обнаружении, завершаем поиск
		do
		{
			tmp = *ptr++;
			
			if (tmp > 0)
			{
				for(uint8_t i = 0; i < 8; i++)
				{
					if (tmp & (1 << i))
					{
						sign = cur_sign + i;
						break;
					}
				}
			}
			
			cur_sign += 8;		
			if (sign == SIGN_OFF)
				num_com -= 8;
			else
				num_com = 0;
		}
		while (num_com > 0);
		
	}
	sMenuTest.cf_val = sign;
	
	// Считаем сигнал группы 2, если есть защита
	if (bDef)
	{
		tmp = Rec_buf_data_uart[4];
		sign = (tmp & 0x10) ? SIGN_DEF : SIGN_OFF;
		
		sMenuTest.def_val = sign;
	}
	
	RecivVar=1;
	LCD2new=1;
}

/**	Определение типа устройства
 * 	В случае некорректного считанного значения, будет применена установка по умолчанию:
 *	пост : есть
 *  команды : нет
 *	тип линии связи : ВЧ
 * 	совместимость : АВАНТ - тут вообще не проверяется
 *  кол-во аппаратов в линии : 2
 * 	Ошибка при этом на данный момент не обрабатывается !!!
 *
 *	@param Нет
 *	@return True если в принятых данных нет ошибок, иначе false.
 */
bool VersDevice(void)
{
	bool CorrectVers = true;
	//происходит формирование пунтка меню: журнал
	sArchive.NumDev=0;  //изначально кол-во устройств=0:
	sArchive.Dev[0]=0;  //для вывода в архиве "события", всегда должно быть 0
	
#if ( (DEB) && (!AUT) ) // принудительная установка типа аппарата
	#warning Включена принудительная установка типа аппарата!!!
	Rec_buf_data_uart[4] = DEF;
	Rec_buf_data_uart[5] = PRM1;
	Rec_buf_data_uart[6] = PRM2;
	Rec_buf_data_uart[7] = PRD;
	Rec_buf_data_uart[8] = LIN;
	Rec_buf_data_uart[9] = TYP;
#endif
	
	// наличие ПОСТа	
	if (Rec_buf_data_uart[4]==1)
	{
		bDef = true;
		bViewParam[5] = true; 
		sArchive.Dev[++sArchive.NumDev] = 3; // Пост
	}
	else 
	{
		bDef = false; 
		bViewParam[3] = false;
		
		if (Rec_buf_data_uart[4] != 0)
			CorrectVers = false;
	}
	
	 //кол-во команд на ПРМ1
	// кратно 4-ем
	// 0, 4, 8, 16, 20, 24, 28, 32
	if ( (Rec_buf_data_uart[5] < 9) && (Rec_buf_data_uart[5] != 3) )
	{
		cNumComR1 = Rec_buf_data_uart[5] * 4; 
		bViewParam[5] = true;
	}
	else 
	{
		cNumComR1 = 0;
		CorrectVers = false;
	}
	
	// кол-во команд на ПРМ2
	// кратно 4-ем
	// 0, 4, 8, 16, 20, 24, 28, 32
	if ( (Rec_buf_data_uart[6] < 9) && (Rec_buf_data_uart[6] != 3) )
	{
		cNumComR2 = Rec_buf_data_uart[6] * 4;  
	}
	else 
	{
		cNumComR2 = 0;
		CorrectVers = false;
	}
	
	// кол-во кмнанд на ПРД
	// кратно 4-ем 
	// 0, 4, 8, 16, 20, 24, 28, 32
	if ( (Rec_buf_data_uart[7] < 9) && (Rec_buf_data_uart[7] != 3))
	{
		cNumComT = Rec_buf_data_uart[7] * 4;  
	}
	else 
	{
		cNumComT = 0;
		CorrectVers=false;
	}
	
	
	// проверим совместимость и если не корректная включим АВАНТ
	if (Rec_buf_data_uart[14] < TYPE_UD_DEV_MAX)	{ 
		TypeUdDev = (typeUdDev_t) Rec_buf_data_uart[14];
	}
	else
	{
		CorrectVers = false;
		TypeUdDev = TYPE_UD_DEV_AVANT;
	}
	
	// отключим сначала все Uk кроме Uk1
	for(uint8_t i = 1; i < 8; i++) {
		bViewParam[5 + i] = false; 
	}
	
	// Кол-во аппаратов в линии
	// 2 или 3
	// в звисимости от этого, корректируются некоторые параметры
	if (Rec_buf_data_uart[8] == 2) {
		cNumLine = 2; 
		cNumComR2 = 0;
		cNumComR = cNumComR1;
	} else if (Rec_buf_data_uart[8] == 3) {
		cNumLine = 3; 
		if ( (cNumComR2) || (bDef) )
			bViewParam[6] = true;  //если есть приемник по второй линии или защита
		if ((bDef)		&&
			(cNumComR1)	&&
			(cNumComR2)	&&
			(cNumComT)	)
		{
			bAllDevice=true;
		}
		
		cNumComR = cNumComR1 + cNumComR2;
		
		// архив для второго приемника. при необходимости
		if (cNumComR2 != 0)
			sArchive.Dev[++sArchive.NumDev] = 4;  // второй приемник
	} else if ((TypeUdDev == TYPE_UD_DEV_PVZUE) && (Rec_buf_data_uart[8] <= 8)) {
			cNumLine = Rec_buf_data_uart[8];
			
			// в ПВЗУ-Е может быть до 8 Uk
			for(uint8_t i = 1; i < cNumLine; i++) {
				bViewParam[5 + i] = true;
			}
	} else {
			cNumLine = 2; 
			cNumComR2 = 0;
			cNumComR = cNumComR1;
			
			CorrectVers = false;
	}
	
	// Архив приемника
	if (cNumComR != 0) 
		sArchive.Dev[++sArchive.NumDev] = 2; //приемник
	
	// Архив передатчика
	if (cNumComT != 0) 
		sArchive.Dev[++sArchive.NumDev] = 1; //передатчик
	
	// Тип линии
	// 1 - ВЧ
	// 2 - Оптика
	if (Rec_buf_data_uart[9] == 2)
		cTypeLine = 2;
	else
	{
		cTypeLine = 1;
		
		if (Rec_buf_data_uart[9] != 1)
			CorrectVers = false;
	}
	
	// Кол-во отображаемых параметров, в заивимости от типа линии	
	// если = 4, то это время/дата/частота/ак
	if (cTypeLine == 1)
    	maxLCDtimer = 4;  		
	else
		maxLCDtimer = 3;
	
	MyInsertion[1] = (Rec_buf_data_uart[10] << 8) + Rec_buf_data_uart[11];  //версия АТмега БСП
	MyInsertion[2] = (Rec_buf_data_uart[12] << 8) + Rec_buf_data_uart[13];  //версия DSP
	MyInsertion[3] = (Rec_buf_data_uart[19] << 4) & 0x0F00;  
	MyInsertion[3] += Rec_buf_data_uart[19] & 0x0F;	//версия БСЗ ПЛИС
	
	//подсичтаем кол-во параметров в меню тест, группа 1
	if (cTypeLine == 2)   // если ВОЛС
	{
		cNumKF = 1;
	}
	else if (cNumLine == 2)
	{
		cNumKF = 2;
	}
	else if (cNumLine == 3)
	{
		cNumKF = 4;
	}
	else
	{
		cNumKF=0;
	}
	
	//сформируем меню просмотр параметров/установимть параметры
	LineInMenu6 = 0;
	if (bDef)
		mMenu6point[LineInMenu6++] = Menu61; //пост
	if (cNumLine==2)
	{
		if (cNumComR>0)
			mMenu6point[LineInMenu6++] = Menu62;  //прм, в 2-х концевой
	}
	else
	{
		if (cNumComR1 > 0)
			mMenu6point[LineInMenu6++] = Menu62_1; //прм 1, в 3-х концевой
		if (cNumComR2 > 0)
			mMenu6point[LineInMenu6++] = Menu62_2; //прм 2, в 3-х концевой
	}
	
	if (cNumComT > 0)
		mMenu6point[LineInMenu6++] = Menu63;  //прд
	mMenu6point[LineInMenu6++] = Menu64;  //общ
	
	//сформируем меню общих параметров, до того как нам станет известным тип удаленного аппарата
	sMenuGlbParam.dev = 0xFF;
	MenuParamGlbCreate();
	MenuParamDefCreate();
	MenuUprCreate(1);
	MenuACCreate();
	MenuAKCreate();
	MenuTestCreate();
	
	bReadVers = true;
    
    return CorrectVers;
}

//обработка принятого сообщения
void DataModBus(unsigned char NumberByte) {
	//прверка принятого CRC
	CRCSum = GetCRCSum(Rec_buf_data_uart,NumberByte - 1);
	if (CRCSum != Rec_buf_data_uart[NumberByte - 1]) 
	{
		EnableReceive; 
	}
	else
	{
		//for (i_dc=0; i_dc<NumberByte; i_dc++) UARTLS_txBuf[i_dc]=Rec_buf_data_uart[i_dc];
		//TransDataInf1(UARTLS_txBuf[2], UARTLS_txBuf[3]);
		
#if ( (DEB) && (PK) )	// пересылка сообщений из БСП на ПК
	#warning Включена пересылка сообщений из БСП на ПК!!!
	if ( (ALR)	||
		 (Rec_buf_data_uart[2] == CR1)	||
		 (Rec_buf_data_uart[2] == CR2)	||
		 (Rec_buf_data_uart[2] == CR3)	||
		 (Rec_buf_data_uart[2] == CR4)	||
		 ((Rec_buf_data_uart[2] & 0xF0) == MSR)
		)
	{
		for (i_dc = 0; i_dc < NumberByte; i_dc++) 
			UARTLS_txBuf[i_dc] = Rec_buf_data_uart[i_dc];
		TransDataInf1(UARTLS_txBuf[2], UARTLS_txBuf[3]);
	}
#endif
		
		if (PCready==2)
		{ 
			// идет работа с ПК
			for (uint8_t i = 0; i < NumberByte; i++) {
				UARTLS_txBuf[i] = Rec_buf_data_uart[i];
			}
			
            // При передачи на ПК команды версии аппаратов, добавим версию ПИ
			if (UARTLS_txBuf[2] == 0x3F) {
				uint8_t crc = UARTLS_txBuf[NumberByte - 1];
				uint8_t num = UARTLS_txBuf[3];
				if (num < 19) {
					// если в посылке не зарезервировано место под версию ПИ
					// т.е. передается меньше байт данных, добавим нужное кол-во
					for(uint8_t i = num + 4; num < 19; i++, num++) {
						UARTLS_txBuf[i] = 0x00;
					}
					crc += 19 - UARTLS_txBuf[3];
					UARTLS_txBuf[3] = num;
					NumberByte = num + 5;
				} else {
					// если место под версию ПИ зарезервировано, на всякий случай
					// учтем изменение контрольной суммы.
					crc -= UARTLS_txBuf[21];
					crc -= UARTLS_txBuf[22];
				}
				crc += (UARTLS_txBuf[21] = (uint8_t) (Insertion >> 8));
				crc += (UARTLS_txBuf[22] = (uint8_t) Insertion);
				UARTLS_txBuf[num + 4] = crc;
				
			}
            
			PCready=3;
			PCbyte=NumberByte;
		}
		else if (PCready==0)
		{		
			switch(Rec_buf_data_uart[2] & 0xF0)
			{
				case 0x00:	// параметры защиты
				FParamDef(Rec_buf_data_uart[2]);
				break;
				
				case 0x10:	// параметры приемника
				FParamPrm(Rec_buf_data_uart[2]);
				break;
				
				case 0x20:	// параметры передатчика
				FParamPrd(Rec_buf_data_uart[2]);
				break;
				
				case 0x30:	// общ
				{ 
					switch(Rec_buf_data_uart[2])
					{
						case 0x30:  // принято текущее состояние
						FCurrentState();
						break; 
						
						case 0x31:	//принято общее текущее состояние
						FGlobalCurrentState(); 
						break;  
						
						case 0x32:	// пришли данные дата/время
						FDataTime(); 
						break;  
						
						case 0x33:	// коррекция тока/напряжения  
						{
							if (cTypeLine == 1)
								FCorrParam();
							else
								vfOptParam();
						} 
						break; 
						
						case 0x34:  // пришли измеряемые параметры
						{
							
							if (cTypeLine == 1) 
								FMeasureParam();
						}
						break; 
						
						case 0x3E:  // принято значение Теста1
						FTest1(Rec_buf_data_uart[4]);
						break; 
						
						case 0x3F:  // информация об аппарате
						VersDevice(); 
						break; 
						
						default:	// общие параметры
						FParamGlobal(Rec_buf_data_uart[2]);
					}
				}
				break;
				default:
				{
					switch(Rec_buf_data_uart[2])
					{
						case 0xC1:	// кол-во записей в архиве
						case 0xD1:
						case 0xE1:
						case 0xF1: 
						FArchive();
						break;
						
						case 0xC2:	// запись архива
						case 0xD2:
						case 0xE2:
						case 0xF2:  
						FArchive(); 
						break; 
					}
				}
			}
			EnableReceive;
		}
	}
	
	ClearPortError();   	// после начала отправки сообщения очистим регистр приема
} //end DataModBus


