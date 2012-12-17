#include <ioavr.h>
#include <stdint.h>
#include "MyDef.h"
#include "InterfaceS.h"
#include "driverLCD.h"
#include "modbus.h"
#include "DataCenter1.h"
#include "Menu.h"

extern BazaModBus ModBusBaza;
extern strMenuGlbParam sMenuGlbParam, sMenuDefParam, sMenuUpr;
int CRCSum;

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
extern uchar MenuFreqPRD, MenuFreqPRM;

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

//параметры ПРД-ка
extern unsigned char MenuPrdTimeOn[];
extern unsigned char MenuPrdTimeCom[];
extern unsigned char MenuPrdTimeRep[];
extern unsigned char MenuPrdBlockCom[];
extern unsigned char MenuPrdLongCom[];
extern unsigned char ValuePrdBlockCom[];
extern unsigned char ValuePrdLongCom[];

//Параметры Общие
extern unsigned char MenuAllSynchrTimer;
extern unsigned char MenuAllLanAddress[];
extern unsigned char MenuAllUoutNominal[];
extern unsigned char MenuAllKeepComPRD;
extern unsigned char MenuAllKeepComPRM;
extern unsigned char MenuAllTimeRerun[];
extern unsigned char MenuAllFreq[];
extern unsigned char MenuAllNumDevice[];
extern unsigned char MenuAllControlUout;
extern unsigned char MenuAllCF[];
extern unsigned char MenuAllLowCF[];
extern unsigned int MyInsertion[];
extern uchar TypeUdDev;
///// ПВЗУ-Е
extern strParamPVZUE sParamPVZE;	
/////

//extern unsigned char Iline1[], Iline2[], Uline[], Usigndef[], Uinkch[], Kd[], Kov[], Pk[];
extern unsigned char Iline1[], Iline2[], Uline[], Usigndef1[], Usigndef2[], Uinkch1[], Uinkch2[], Kd[], Kov[], Pk[];
extern unsigned char Iline1H[], PkH[], KovH[];
extern signed int UlineValue, IlineValue;
extern unsigned char LCDparam;
extern unsigned char FreqNum[];

extern unsigned char Mass1[];

extern unsigned char Dop_byte[];

//Архив
extern unsigned int NumberRecording;
extern unsigned int NumRecStart;
extern unsigned char NumberRec;
extern unsigned char ReadArch;
extern unsigned int AddressStartRegister;
extern unsigned char NumberRegister;
extern unsigned char StRegister;

extern strArchives sArchives;

//Тесты
extern unsigned char gr1, gr2, gr21, gr22;


//переменные проверки достоверности даты и времени
unsigned char TrDataTimeMass[]={0x30,0x30,0x30,0x30,0x30,0x30};;
unsigned char DataError=9;
unsigned char TimeError=9;
unsigned int Pk_temp=0;

unsigned char j;
unsigned char l;
unsigned char i_dc;

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
extern  uchar   cNumKF;

extern void MenuParamGlbCreate(void);
extern void MenuParamDefCreate(void);
extern void MenuUprCreate(uint8_t act);
extern void MenuAKCreate(void);
extern void MenuTestCreate(void);
extern void Menu_Archive_Create(void);
extern unsigned char MaxShiftMenu, ShiftMenu;

extern __flash strParam paramDef[];
extern __flash strParam paramPrm[];
extern __flash strParam paramPrd[];
extern __flash strParam paramGlb[];

extern strMenuTest sMenuTest;

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
	u8 min, max;
	uint8_t tmp = Rec_buf_data_uart[4];
	
	switch(command)
	{
		case 0x01:
		{  //принято значение типа защиты (пост)
			if ((tmp < paramDef[0].min) || (tmp > paramDef[0].max)) 
				MenuTypeDefend = paramDef[0].max + 1;
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
			if ((tmp < paramDef[1].min) || (tmp > paramDef[1].max)) 
				MenuTypeLine[0] = '?'; 
			else 
			{
				MenuTypeLine[0] = tmp + '0';
				if (cNumLine != tmp)
				{
					cNumLine = tmp;
					MenuTestCreate();
					MenuParamGlbCreate();
					MenuParamDefCreate();
					MenuUprCreate(1);
					MenuAKCreate();
					MenuTestCreate();
				}
			}
			
			
		}break;
		case 0x03:
		{//принято значение допустимого времени без манипуляции (пост)
			if ((tmp < paramDef[2].min) || (tmp > paramDef[2].max)) 
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
			min = paramDef[3].min;
			max = paramDef[3].max;
			
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
			min = paramDef[4].min;
			max = paramDef[4].max;
			
			if ((tmp < min) || (tmp > max)) 
			{
				MenuCoveringImpulse1[0] = '?';
				MenuCoveringImpulse1[1] = '?';
			}
			else
			{	
				MenuCoveringImpulse1[0] = tmp/10 + '0';
				MenuCoveringImpulse1[1] = tmp%10 + '0';
				
				if ( (cTypeLine == 2) && (cNumLine == 3) )						// в 3-х концевой оптике параметр дублируется
				{
					tmp = Rec_buf_data_uart[5];
					if ((tmp < min) || (tmp > max)) 
					{
						MenuCoveringImpulse2[0] = '?';
						MenuCoveringImpulse2[1] = '?';
					}
					else
					{
						MenuCoveringImpulse2[0] = (tmp / 10) + '0';
						MenuCoveringImpulse2[1] = (tmp % 10) + '0';
					}
				}
 			}
		}break;
		case 0x06:
		{//принято значение напряжения порога (пост)
			min = paramDef[5].min;
			max = paramDef[5].max;
			
			if ( (tmp < min) || (tmp > max) ) 
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
				if ( (tmp < min) || (tmp > max) ) 
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
			if ( (tmp < paramDef[6].min) || (tmp > paramDef[6].min) ) 
				MenuAKdecrease = 2;
			else 
				MenuAKdecrease = tmp;
		}break;
		case 0x08:
		{
			if (tmp > paramDef[7].min)
				MenuFreqPRD = paramDef[7].max + 1;
			else
				MenuFreqPRD = tmp;
		}
		break;
		case 0x09:
		{
			if (tmp > paramDef[8].max)
				MenuFreqPRM = paramDef[8].max + 1;
			else
				MenuFreqPRM = tmp;
		}
		break;
		case 0x0A:
		{
			if ( (tmp < paramDef[9].min) || (tmp > paramDef[9].max) )
			{
				cAutoControl = 0;
			}
			else
			{
				cAutoControl = tmp;
				
				// если тип удаленного аппарата ПВЗ или АВЗК
				if ( (sMenuGlbParam.dev >= 1) || (sMenuGlbParam.dev <= 4) )
				{
					long a;
					
					switch(sMenuGlbParam.dev)
					{
						case 1:	// ПВЗ
						{
							switch(cAutoControl)
							{
								case 1:	// норм
								case 2:
								iTimeToAK = 16800;
								break;
								case 3:	// ускор
								iTimeToAK = 2100;
								break;
								case 5:	// проверка
								iTimeToAK = 131;
								break;
								case 6:	// испыт
								iTimeToAK = 2;
								break;
							}
							a = Rec_buf_data_uart[5];
							a <<= 8;
							a += Rec_buf_data_uart[6];
							a <<= 8;
							a += Rec_buf_data_uart[7];
							a <<= 8;
							a += Rec_buf_data_uart[8];
							a = a / 1000;
							iTimeToAKnow = a;
						}
						break;
						case 2:	// АВЗК
						{
							switch(cAutoControl)
							{
								case 1:	// норм
								case 2:
								iTimeToAK = 20000;
								break;
								case 3:	// ускор
								iTimeToAK = 2000;
								break;
								case 5:	// проверка
								iTimeToAK = 200;
								break;
								case 6:	// испыт
								iTimeToAK = 2;
								break;
							}
							a = Rec_buf_data_uart[5];
							a <<= 8;
							a += Rec_buf_data_uart[6];
							a <<= 8;
							a += Rec_buf_data_uart[7];
							a <<= 8;
							a += Rec_buf_data_uart[8];
							a = a / 1000;
							iTimeToAKnow = a;
						}
						break;
						case 3: // ПВЗЕ-У
						case 4: // ПВЗЛ
				  		// Женька посылает время до АК
						{
							a = Rec_buf_data_uart[5];
							a <<= 8;
							a += Rec_buf_data_uart[6];
							a <<= 8;
							a += Rec_buf_data_uart[7];
							a <<= 8;
							a += Rec_buf_data_uart[8];
							a = a / 1000;
							iTimeToAK = a;
							iTimeToAKnow = 0;
						}
						break;
					} 
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
	uint8_t min, max;
	
	switch(command){
		case 0x11:
		case 0x18:{ //Время включения (приемник)
			if (command==0x11) 
				TmpMass=MenuPrmTimeOn;
			else 
				TmpMass=MenuPrmTimeOn2;
			
			min = paramPrm[0].min;
			max = paramPrm[0].max;
			
			if ( (Rec_buf_data_uart[4] < min) || (Rec_buf_data_uart[4] > max) ) 
			{
				TmpMass[0]='?';
				TmpMass[1]='?';
			}
			else
			{
				TmpMass[0]=Rec_buf_data_uart[4]/10+0x30;
				TmpMass[1]=Rec_buf_data_uart[4]%10+0x30;
			}
		}
		break;
		
		case 0x12:
		case 0x19:{ //длительность команды (приемник)
			if (command==0x12) 
				TmpMass=MenuPrmTimeCom;
			else 
				TmpMass=MenuPrmTimeCom2;
			
			
			min = paramPrm[1].min;
			max = paramPrm[1].max;
			
			if ((Rec_buf_data_uart[4] < min) || (Rec_buf_data_uart[4] > max)) 
			{
				TmpMass[0]='?';
				TmpMass[1]='?';
				TmpMass[2]='?';
			}
			else
			{
				if (Rec_buf_data_uart[4]<10)
				{
					TmpMass[0]=Rec_buf_data_uart[4]+0x30;
					TmpMass[1]='0';
					TmpMass[2]=' ';
				}
				else
				{
					TmpMass[0]=Rec_buf_data_uart[4]/10+0x30;
					TmpMass[1]=Rec_buf_data_uart[4]%10+0x30;
					TmpMass[2]='0';
				}
			}
		}
		break;
				 
		case 0x13:
		case 0x1A:{ //задержка на выключение (приемник)
			if (command==0x13) 
				TmpMass=ValuePrmTimeOff;
			else 
				TmpMass=ValuePrmTimeOff2;
			
			min = paramPrm[2].min;
			max = paramPrm[2].max;
			
			for (l=0; l<Rec_buf_data_uart[3]; l++)
			{
				if ( (Rec_buf_data_uart[4+l] < min) || (Rec_buf_data_uart[4+l] > max) ) 
					TmpMass[l]=0xFF;
				else 
					TmpMass[l]=Rec_buf_data_uart[4+l];
			}
		}
		break;
		
		case 0x14:
		case 0x1B: { //блокировка команд на приеме
			if (command==0x14) 
				TmpMass=ValuePrmBlockCom;
			else 
				TmpMass=ValuePrmBlockCom2;
			
			for(l=0; l<Rec_buf_data_uart[3]; l++) 
				TmpMass[l]=Rec_buf_data_uart[4+l];
		}break;
		case 0x15:
		case 0x1C:{ //длительные команды
			if (command==0x15) 
				TmpMass=ValuePrmLongCom;
			else 
				TmpMass=ValuePrmLongCom2;
			
			for(l=0; l<Rec_buf_data_uart[3]; l++) 
				TmpMass[l]=Rec_buf_data_uart[4+l];
		}
		break;
	}
				 
	RecivVar=1;
  	LCD2new=1;
};


void FParamPrd(unsigned char command)
{
	uint8_t min, max;
	uint8_t tmp = Rec_buf_data_uart[4];
	
	switch(command)
	{
		case 0x21:
		{ //время включения (передатчик)			
			min = paramPrd[0].min;
			max = paramPrd[0].max;
			
			if ( (tmp < min) || (tmp > max) )
			{
				MenuPrdTimeOn[0]='?';
				MenuPrdTimeOn[1]='?';
			}
			else
			{
				MenuPrdTimeOn[0] = tmp/10 + '0';
				MenuPrdTimeOn[1] = tmp%10 + '0';
			}
		}
		break;
		
		case 0x22:
		{//длительность команды (передатчик)
			min = paramPrd[1].min;
			max = paramPrd[1].max;
			
			if ( (tmp < min) || (tmp > max) )
			{
				MenuPrdTimeCom[0]='?';
				MenuPrdTimeCom[1]='?';
				MenuPrdTimeCom[2]='?';
			}
			else
			{
				if (tmp < 10)
				{
					MenuPrdTimeCom[0]=tmp + '0';
					MenuPrdTimeCom[1]='0';
					MenuPrdTimeCom[2]=' ';
				}
				else
				{
					MenuPrdTimeCom[0] = tmp/10 + '0';
					MenuPrdTimeCom[1] = tmp%10 + '0';
					MenuPrdTimeCom[2] = '0';
				}
			}
		}
		break;
		
		case 0x23:{ //время на повторное формирование команды (передатчик)
			min = paramPrd[2].min;
			max = paramPrd[2].max;
			
			if ( (tmp < min) || (tmp > max) )
			{
				MenuPrdTimeRep[0]='?';
				MenuPrdTimeRep[1]='?';
				MenuPrdTimeRep[2]='?';
			}
			else
			{
				if (tmp < 10)
				{
					MenuPrdTimeRep[0] = tmp + '0';
					MenuPrdTimeRep[1] = '0';
					MenuPrdTimeRep[2] = ' ';
				}
				else
				{
					MenuPrdTimeRep[0] = tmp/10 + '0';
					MenuPrdTimeRep[1] = tmp%10 + '0';
					MenuPrdTimeRep[2] = '0';
				}
			}
		}
		break;
		
		case 0x24:
		{	//блокировка команд (передатчик)
			for(l=0; l<Rec_buf_data_uart[3]; l++) 
				ValuePrdBlockCom[l] = Rec_buf_data_uart[4+l];
		}
		break;
		
		case 0x25:
		{
			for(l=0; l<Rec_buf_data_uart[3]; l++) 
				ValuePrdLongCom[l] = Rec_buf_data_uart[4+l];
		}
		break;
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
	
	bRec1Avar = (GlobalCurrentState[4] != 0) || (GlobalCurrentState[5] != 0) ? true : false;
	bRec1Warn = (GlobalCurrentState[6] != 0) || (GlobalCurrentState[7] != 0) ? true : false;
	
	bTrAvar = (GlobalCurrentState[8] != 0) || (GlobalCurrentState[9] != 0) ? true : false;
	bTrWarn = (GlobalCurrentState[10] != 0) || (GlobalCurrentState[11] != 0) ? true :false;
	
	bRec2Avar = (GlobalCurrentState[16] != 0) || (GlobalCurrentState[17]!=0) ? true : false;
	bRec2Warn = (GlobalCurrentState[18] != 0) || (GlobalCurrentState[19]!=0) ? true : false;
	
	RecivVar=1;
}

void FDataTime(void){
	DataLCD[7]=(Rec_buf_data_uart[4]&0x0F)+0x30; //1-цы лет
	DataLCD[6]=(Rec_buf_data_uart[4]>>4)+0x30;  //10-ки лет
	DataLCD[4]=(Rec_buf_data_uart[5]&0x0F)+0x30;  //1-цы мес
	DataLCD[3]=(Rec_buf_data_uart[5]>>4)+0x30;  //10-и мес
	DataLCD[1]=(Rec_buf_data_uart[6]&0x0F)+0x30;  //1-цы дней
	DataLCD[0]=(Rec_buf_data_uart[6]>>4)+0x30;  //10-и дней
	
	TimeLCD[1]=(Rec_buf_data_uart[7]&0x0F)+0x30; //1-цы час
	TimeLCD[0]=(Rec_buf_data_uart[7]>>4)+0x30;  //10-ки час
	TimeLCD[4]=(Rec_buf_data_uart[8]&0x0F)+0x30;  //1-цы мин
	TimeLCD[3]=(Rec_buf_data_uart[8]>>4)+0x30;  //10-и мин
	TimeLCD[7]=(Rec_buf_data_uart[9]&0x0F)+0x30;  //1-цы сек
	TimeLCD[6]=(Rec_buf_data_uart[9]>>4)+0x30;  //10-и сек
	
	//Проверка на достовереность
	for (j=0;j<8;j++){
		if  (((DataLCD[j]>0x39)||(DataLCD[j]<0x30))&&(DataLCD[j]!='.')) DataError++; else DataError=0;
		if  (((TimeLCD[j]>0x39)||(TimeLCD[j]<0x30))&&(TimeLCD[j]!=':')) TimeError++; else TimeError=0;
	}
	
	if (((DataLCD[7]-0x30)+((DataLCD[6]-0x30)*10))>99)  DataError++;
	if (((DataLCD[4]-0x30)+((DataLCD[3]-0x30)*10))>12)  DataError++;
	if (((DataLCD[1]-0x30)+((DataLCD[0]-0x30)*10))>31)  DataError++;
	if (((TimeLCD[1]-0x30)+((TimeLCD[0]-0x30)*10))>24)  TimeError++;
	if (((TimeLCD[4]-0x30)+((TimeLCD[3]-0x30)*10))>60)  TimeError++;
	if (((TimeLCD[7]-0x30)+((TimeLCD[6]-0x30)*10))>60)  TimeError++;
	
	if (DataError!=0){
		DataLCD[7]='0'; //1-цы лет
		DataLCD[6]='0';  //10-ки лет
		DataLCD[4]='0';  //1-цы мес
		DataLCD[3]='0';  //10-и мес
		DataLCD[1]='0';  //1-цы дней
		DataLCD[0]='0';  //10-и дней
		DataError=0;
		for (j=0; j<3; j++) TrDataTimeMass[j]=0x00;
	}
	else for (j=0; j<3; j++) TrDataTimeMass[j]=Rec_buf_data_uart[4+j];
	
	if (TimeError!=0){
		TimeLCD[1]='0'; //1-цы час
		TimeLCD[0]='0';  //10-ки час
		TimeLCD[4]='0';  //1-цы мин
		TimeLCD[3]='0';  //10-и мин
		TimeLCD[7]='0';  //1-цы сек
		TimeLCD[6]='0';  //10-и сек
		TimeError=0;
		for (j=0; j<3; j++) TrDataTimeMass[j+3]=0x00;
	}else
		for (j=0; j<3; j++) TrDataTimeMass[j+3]=Rec_buf_data_uart[4+j+3];
	
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

void fIntCodeToChar(unsigned char *Mass, unsigned char StartAddr, unsigned char Factor, unsigned char Param, unsigned int Value, unsigned int Max){
	unsigned char i;
	// Value - должно быть меньше 1000
	Factor--;
	
	for(i=StartAddr; i<8; i++) Mass[i]=' ';
	
	Value=Value<<Factor;
	if (Value<Max){
		if (Value>999){
			Mass[StartAddr]=Value/1000;
			Value=Value-Mass[StartAddr]*1000;
			Mass[StartAddr]+=0x30; StartAddr++;
		}
		if (Value>99){
			Mass[StartAddr]=Value/100;
			Value=Value-Mass[StartAddr]*100;
			Mass[StartAddr]+=0x30; StartAddr++;
		}
		Mass[StartAddr]=Value/10+0x30; StartAddr++;
		Mass[StartAddr]=Value%10+0x30; StartAddr++;
	}else{
		Mass[StartAddr]='?'; StartAddr++;
		Mass[StartAddr]='?'; StartAddr++;
	}
	
	switch(Param){
		case 1:{
			Mass[StartAddr]='м';
			Mass[StartAddr+1]='А';
		}break;
		case 2:{
			Mass[StartAddr]='%';
		}break;
	}
	
}

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
	u8 tmp;
	// протокол обмена
	
	tmp = Rec_buf_data_uart[4];
	if ( (tmp < paramGlb[19].min) || (tmp > paramGlb[19].max) )
		tmp = paramGlb[19].max + 1;
	
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
		IlineValue=(Rec_buf_data_uart[7]<<8)+Rec_buf_data_uart[8];  //значение для вычисления коррекции
		fIntCodeToChar(Iline2,3,1,1,IlineValue,1000);
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
		fDopCodeToChar(Usigndef1,3,1,2,Rec_buf_data_uart[11]);
		if (cNumLine==3)
			fDopCodeToChar(Usigndef2,3,1,2,Rec_buf_data_uart[12]);
		
		//контрльная частота
		if ( (cAutoControl == 4) && (CurrentState[0] < 4) )
		{   //если АК выкл и не тест то Uk всегда 0
			Rec_buf_data_uart[13]=0;
			Rec_buf_data_uart[14]=0;
		}
		fDopCodeToChar(Uinkch1,3,1,2,Rec_buf_data_uart[13]);
		if (cNumLine==3)
			fDopCodeToChar(Uinkch2,3,1,2,Rec_buf_data_uart[14]);
		
		//использование динамического диапазона приемника
		fDopCodeToChar(Kd,3,1,2,Rec_buf_data_uart[15]);
		//коэффициент переполнения АЦП
		fIntCodeToChar(Kov,4,1,2,Rec_buf_data_uart[16],100);
		HexToViewHex(KovH,3,Rec_buf_data_uart[16]);
		//вероятность пропуска команд
		itmp=(Rec_buf_data_uart[17]<<8)+Rec_buf_data_uart[18];
		if ((itmp>999)&&(itmp<10000)){
			Pk[3]=itmp/1000;
			itmp=itmp-Pk[3]*1000;
			Pk[3]+=0x30;
		}else Pk[3]='0';
		fIntCodeToChar(Pk,5,1,3,itmp,1000);
		HexToViewHex(PkH,3,Rec_buf_data_uart[17]);
		HexToViewHex(PkH,5,Rec_buf_data_uart[18]);
	}
	LCDparam=1;
	RecivVar=1;
}

void FParamGlobal(unsigned char command)
{
	uint8_t min, max;
	uint8_t tmp = Rec_buf_data_uart[4];
	
	
	switch(command)
	{
		case 0x35:		// синхронизация часов (общие)
		{  
			min = paramGlb[1].min;
			max = paramGlb[1].max;
			
			if ( (tmp < min) || (tmp > max) ) 
				MenuAllSynchrTimer = max + 1;
			else 
				MenuAllSynchrTimer = tmp;
		}
		break;
		
		case 0x36:		
		{ 
			// удержание реле ПРМ ---  ОПТИКА С КОМАНДАМИ
			min = paramGlb[21].min;
			max = paramGlb[21].max;
			
			if ( (tmp < min) || (tmp > max) ) 
				MenuAllKeepComPRM = max + 1;
			else
				MenuAllKeepComPRM = tmp;
		}
		break;
	
		case 0x37:		
		{ 
			min = paramGlb[3].min;
			max = paramGlb[3].max;
			
			// удержание реле ПРД ---  ОПТИКА С КОМАНДАМИ
			if ( (tmp < min) || (tmp > max) )
				MenuAllKeepComPRD = max + 1;
			else
				MenuAllKeepComPRD = tmp;
		}
		break;
		
		case 0x38:		// адрес аппарата в локальной сети (общие)
		{ 	
			min = paramGlb[4].min;
			max = paramGlb[4].max;
			
			if ( (tmp < min) || (tmp > max) )
				tmp = 0;
			
			MenuAllLanAddress[2] = tmp%10 + '0';
			tmp /= 10;
			MenuAllLanAddress[1] = tmp%10 + '0';
			MenuAllLanAddress[0] = tmp/10 + '0';
		}break;
		
		case 0x39:
		{ 	// Оптика - "Время перезапуска"
			// ВЧ - параметры ПВЗУ-Е
			min = paramGlb[5].min;
			max = paramGlb[5].max;
			
			if ( (tmp < min) || (tmp > max) )
				tmp = 0;

			MenuAllTimeRerun[0] = tmp + '0';	
		}
		break;
		
		case 0x3B:
		{ //номер аппарата (общие)
			min = paramGlb[7].min;
			max = paramGlb[7].max;
			
			if ( (tmp < min) || (tmp > max) )
			{
				MenuAllNumDevice[0] = '?';
				FreqNum[7]='?';
			}
			else
			{
				MenuAllNumDevice[0] = tmp + '0';
				FreqNum[7] = MenuAllNumDevice[0];
			}
			LCDtimerNew=1;
		}
		break;
	}

	RecivVar=1;
	LCD2new=1;
};


/** Обработка посылки с информацией по журналам
 * 	@param Нет
 *	@return Нет
 */
void FArchive(void)
{
	uint8_t com = Rec_buf_data_uart[2];
	
	// is command of the current log?
	if ( (com & 0xF0) != sArchives.curArchive->typeDev)
		return;
	
	if ( (com & 0x0F) == 0x01)			// read number of log entries
	{ 
		
		if (Rec_buf_data_uart[5] & 0x80) 
			sArchives.ovf = true;	
		else
			sArchives.ovf = false;
		
		sArchives.oldestEntry = (Rec_buf_data_uart[5] << 8) + Rec_buf_data_uart[4];
	}
	else if ( (com & 0x0F) == 0x02)		// read log entries
	{ 	

		uint8_t *ptr = (uint8_t *) &Rec_buf_data_uart[4];
		
		com &= 0xF0;
		
		// read data entry
		if (com == 0xF0)
		{
			// event journal
			sArchives.regime = *ptr++;
			sArchives.bytes[3] = *ptr++;
			sArchives.bytes[2] = *ptr++;
			sArchives.bytes[1] = *ptr++;
			sArchives.bytes[0] = *ptr++;
		}
		else if ( (com == 0xD0) || (com == 0xE0) )
		{
			// prm and prd journals
			sArchives.bytes[3] = *ptr++;
			sArchives.bytes[2] = *ptr++;
			sArchives.bytes[1] = *ptr++;
			sArchives.bytes[0] = *ptr++;
		}
		else
		{
			// def journal 
			sArchives.bytes[0] = *ptr++;
			sArchives.bytes[1] = *ptr++;
		}
		
		// read date entry
		sArchives.year = *ptr++;
		sArchives.month = *ptr++;
		sArchives.day = *ptr++;
		
		// read time entry
		sArchives.hours = *ptr++;
		sArchives.minutes = *ptr++;
		sArchives.seconds = *ptr++;
		sArchives.milliseconds = (*ptr << 8) + *(ptr + 1);
		
		sArchives.refresh = true;
	}
	
	RecivVar = 1;
	LCD2new = 1;
}


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
 *	пость : есть
 *  команды : нет
 *	тип линии связи : ВЧ
 * 	совместимость : АВАНТ - тут вообще не проверяется
 *  кол-во аппаратов в линии : 2
 * 	Ошибка при этом на данный момент не обрабатывается !!!
 *	@param Нет
 *	@return Нет
 */
void VersDevice(void)
{
	bool CorrectVers = true;
	//происходит формирование пунтка меню: журнал
	//sArchive.NumDev=0;  //изначально кол-во устройств=0:
	//sArchive.Dev[0]=0;  //для вывода в архиве "события", всегда должно быть 0
	
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
//		sArchive.Dev[++sArchive.NumDev] = 3;
//		sArchive.typeDev = 1;	
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
	
	// Кол-во аппаратов в линии
	// 2 или 3
	// в звисимости от этого, корректируются некоторые параметры
	if (Rec_buf_data_uart[8] == 3)
	{
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
		
//		// архив для второго приемника. при необходимости
//		if (cNumComR2 != 0)
//			sArchive.Dev[++sArchive.NumDev] = 4;  
	}
	else
	{
		cNumLine = 2; 
		cNumComR2 = 0;
		cNumComR = cNumComR1;
		
		if (Rec_buf_data_uart[8] != 2)
			CorrectVers = false;
	}
	
//	// Архив приемника
//	if (cNumComR != 0) 
//	{
//		sArchive.Dev[++sArchive.NumDev] = 2; //приемник
//		sArchive.typeDev = 2;
//	}
//	
//	// Архив передатчика
//	if (cNumComT != 0) 
//	{
//		sArchive.Dev[++sArchive.NumDev] = 1; //передатчик
//		sArchive.typeDev = 2;
//	}
	
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
	
	
	MyInsertion[1] = (Rec_buf_data_uart[10]<<8)+Rec_buf_data_uart[11];  //версия АТмега БСП
	MyInsertion[2] = (Rec_buf_data_uart[12]<<8)+Rec_buf_data_uart[13];  //версия DSP
	
	
	// проверим совместимость и если не корректная включим АВАНТ
	if (Rec_buf_data_uart[14] < 5)	// 5 == NumTypeUdDev
	{
		TypeUdDev = Rec_buf_data_uart[14];
	}
	else
	{
		CorrectVers = false;
		TypeUdDev = 0;
	}
	
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
	MenuAKCreate();
	MenuTestCreate();
	Menu_Archive_Create();
	
	bReadVers = true;
}

//обработка принятого сообщения
void DataModBus(unsigned char NumberByte)
{
	//прверка принятого CRC
	CRCSum = GetCRCSum(Rec_buf_data_uart,NumberByte - 1);
	if (CRCSum != Rec_buf_data_uart[NumberByte - 1]) 
	{
		EnableReceive; 
	}
	else
	{
		//for (i_dc=0; i_dc<NumberByte; i_dc++) Tr_buf_data_uart1[i_dc]=Rec_buf_data_uart[i_dc];
		//TransDataInf1(Tr_buf_data_uart1[2], Tr_buf_data_uart1[3]);
		
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
			Tr_buf_data_uart1[i_dc] = Rec_buf_data_uart[i_dc];
		TransDataInf1(Tr_buf_data_uart1[2], Tr_buf_data_uart1[3]);
	}
#endif
		
		if (PCready==2)
		{ 
			// идет работа с ПК
			for (i_dc=0; i_dc<NumberByte; i_dc++) Tr_buf_data_uart1[i_dc]=Rec_buf_data_uart[i_dc];
			PCready=3;
			PCbyte=NumberByte;
		}
		else if (PCready==0)
		{
			// идет работа с БСП
			ModBusBaza.writeinf(Rec_buf_data_uart[2], Rec_buf_data_uart);
			
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
	bUartRcReady1 = false;  // обработка сообщения закончена
} //end DataModBus


