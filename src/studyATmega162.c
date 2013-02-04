#include <ioavr.h>
#include <ina90.h>
#include <stdint.h>
#include "StartSetup.h"
#include "InterfaceS.h"
#include "MyDef.h"
#include "DataCenter.h"
#include "DataCenter1.h"
#include "driverLCD.h"
#include "WatchDog.h"
#include "ModBus.h"
#include "Flash.h"
#include "Menu.h"

static char itoa					(uint8_t start, uint16_t val, uint8_t buf[]);
static void FuncViewValue			(uint8_t numparam);
static void PressSharp				(void);
static void FuncInpCorrParam		(void);
static void FuncSelectValue			(void);
static void FuncInputDataTime		(void);
static void FuncInputData			(void);
static void FuncPressKey			(void);
static void ModBusOpros				(void);
static void FuncTr					(void);
static void LCDMenu1				(uint8_t NumString, uint8_t Device);
static void LCDwork					(void);


//���������� ���� ������ ���������
#define LoopUARTtime 10

//������ "����/�����" ������������ � USP
extern unsigned char TrDataTimeMass[];

//������� ���������� ��� ������ � EEPROM
extern unsigned char eWrite, eRead;
extern unsigned char *eMassiveWrite, *eMassiveRead;
extern unsigned int eAddressWrite,eAddressRead;

unsigned char PressKey;
unsigned char eNumberAskMeasuring[]={0x00,0x00};
unsigned char eProtocol[]={0x00,0x00};

unsigned int MyInsertion[]={Insertion, 0x0000, 0x0000};

unsigned int DataM[250];
unsigned int JournalM[129]; //������ ������� - ���������� ������� � ������

unsigned char LoopUART;
unsigned char LCDnew, LCD2new;
unsigned char LCDtimerNew = 1, LCDparam = 1;
unsigned char LCDtimer = 2;
unsigned char maxLCDtimer;  //������������ ���-�� ����� ��������� LCDtimer
unsigned char TransVar;
unsigned char RecivVar;
unsigned char NumberLostLetter = 0;
unsigned char AvarNoUsp = 0;
unsigned char NewTime = 0;
eMENUlvl MenuLevel = LVL_START;
unsigned char PreduprMenu1[4]={0x01,0x01,0x01,0x00};
unsigned char AvarMenu1[4]={0x01,0x01,0x01,0x00};

bool TimeWink;

unsigned char NumberCom=1;

unsigned char CodePrint1, PassCen;

unsigned char InputDataTime[]="??.??.??";
unsigned char DataLCD[]="??.??.??";
unsigned char TimeLCD[]="??:??:??";
unsigned char FreqNum[]="???���-?";
unsigned char FreqNumCom;

unsigned char Iline1H[]=  "1- ????h";
unsigned char KovH[]=     "2- ??h  ";
unsigned char PkH[]=      "3- ????h";
unsigned char Iline1[]={'a', '=', '?', '?', ' ', '�', ' ', ' ', 0x00};
unsigned char Iline2[]= "I1=??mA ";
unsigned char Kov[]=    "Kov=??% ";
unsigned char Pk[]=     "Pk=0,???";
unsigned char Uline[]=  "U=??,?B ";
unsigned char Kd[]=     "U�=??�� ";
unsigned char Usigndef1[]="U�=??�� ";
unsigned char Usigndef2[]="U�=??�� ";
unsigned char Uinkch1[]= "U�=??�� ";
unsigned char Uinkch2[]= "U�=??�� ";
unsigned char *Measuring[]={Iline1, Iline2, Uline, Usigndef1, Usigndef2, Uinkch1, Uinkch2, Kd,    Kov,  Pk};
unsigned char bViewParam[]={false,   true,   true,  true,     false,     false,   false,   true,  false,false}; //true - ������� ��������, false -���������.
signed int UlineValue, IlineValue;

unsigned char GlobalCurrentState[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x00};
unsigned char CurrentState[]={0x4E,0x4E,0x4E,0x4E,0x4E,0x4E,0x4E,0x4E,0x00};
unsigned char Dop_byte[]={0x3F, 0x3F, 0x3F, 0x3F};

unsigned char Protocol;
//�������� x*100��
#define Delay1 60
//�������� ����� �1
unsigned char gr1='?', gr2='?', gr21='?', gr22='?';

unsigned char TempCurrState; //���������� ����� ��� ����������� ������ � ���� ����������\�����

//���������� ����������� ��� FuncInputData
unsigned char NumberInputSymbol;
unsigned char NewPass=0, EntPass=0;


strMenuGlbParam sMenuParam;
//��������� �����
unsigned char mErr[]="???";
unsigned char MenuTypeLine[]="? ��������";
unsigned char MenuPossibleTimeNoMan[]="?? ���  ";
unsigned char MenuPossibleTimeSignal1[]="?? ����";
unsigned char MenuPossibleTimeSignal2[]="?? ����";
unsigned char *MenuPossibleTimeSignal[]={MenuPossibleTimeSignal1, MenuPossibleTimeSignal2};
unsigned char MenuCoveringImpulse1[]="?? ����";
unsigned char MenuCoveringImpulse2[]="?? ����";
unsigned char *MenuCoveringImpulse[]={MenuCoveringImpulse1, MenuCoveringImpulse2};
unsigned char MenuVoltageLimit1[]="?? ��";
unsigned char MenuVoltageLimit2[]="?? ��";
unsigned char* MenuVoltageLimit[]={MenuVoltageLimit1,MenuVoltageLimit2};
unsigned char cAutoControl=0;
unsigned int iTimeToAK = 0, iTimeToAKnow = 0;
unsigned char MenuAKdecrease=2;  //�������� ��, ���������� �� ��
uchar MenuFreqPRD = dMaxMenuAllFreq;
uchar MenuFreqPRM = dMaxMenuAllFreq;
strMenuGlbParam sMenuDefParam, sMenuUpr;

//��������� ���������
unsigned char MenuPrmTimeOn[]="?? ��";
unsigned char MenuPrmTimeCom[]="??? ��";
unsigned char MenuPrmTimeOff[]="     ��";
unsigned char MenuPrmBlockCom[]="        ";
unsigned char MenuPrmLongCom[]= "        ";
unsigned char* MenuParamPRM[]={MenuPrmTimeOn, MenuPrmTimeCom, MenuPrmTimeOff, MenuPrmBlockCom, MenuPrmLongCom};
unsigned char NumberTransCom; //���� � ������� �������� ����� ������������ "������� �� ������"
unsigned char ValuePrmTimeOff[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char ValuePrmBlockCom[4]={'?','?','?','?'};
unsigned char ValuePrmLongCom[4]={'?','?','?','?'};
unsigned char MenuVoltageLimitPRM1[]="?? ��";
unsigned char MenuVoltageLimitPRM2[]="?? ��";
unsigned char* MenuVoltageLimitPRM[]={MenuVoltageLimitPRM1,MenuVoltageLimitPRM2};
//��� ������� ���������
unsigned char MenuPrmTimeOn2[]="?? ��";
unsigned char MenuPrmTimeCom2[]="??? ��";
unsigned char MenuPrmTimeOff2[]="     ��";
unsigned char MenuPrmBlockCom2[]="        ";
unsigned char MenuPrmLongCom2[]= "        ";
unsigned char* MenuParamPRM2[]={MenuPrmTimeOn2, MenuPrmTimeCom2, MenuPrmTimeOff2, MenuPrmBlockCom2, MenuPrmLongCom2};
unsigned char ValuePrmTimeOff2[]={0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0};
unsigned char ValuePrmBlockCom2[4]={'?','?','?','?'};
unsigned char ValuePrmLongCom2[4]={'?','?','?','?'};
unsigned char MenuVoltageLimitPRM12[]="?? ��";
unsigned char MenuVoltageLimitPRM22[]="?? ��";
unsigned char* MenuVoltageLimitPRM_2[]={MenuVoltageLimitPRM12,MenuVoltageLimitPRM22};
//��������� �����������
unsigned char MenuPrdTimeOn[]="?? ��";
unsigned char MenuPrdTimeCom[]="??? ��";
unsigned char MenuPrdBlockCom[]="????";
unsigned char MenuPrdLongCom[]="????";
unsigned char* MenuParamPRD[]={MenuPrdTimeOn, MenuPrdTimeCom, MenuPrdBlockCom, MenuPrdLongCom};
unsigned char ValuePrdBlockCom[4]={'?','?','?','?'};
unsigned char ValuePrdLongCom[4]={'?','?','?','?'};

//��������� �����
unsigned char MenuAllSynchrTimer=0x02;  //��� ���� ������������ ������ MenuAllSynchrTimerNum
unsigned char MenuAllUoutNominal[]="?? �";
uchar MenuAllKeepComPRD = 0x02;
uchar MenuAllKeepComPRM = 0x02;
unsigned char MenuAllLanAddress[]="???";
unsigned char MenuAllTimeRerun[]= "? ���";
unsigned char MenuAllFreq[]		= "??? ���";
unsigned char MenuAllNumDevice[]= "?";
unsigned char MenuAllCF[]		= "?? ��";
unsigned char MenuAllLowCF[] 	= "?? ��";
unsigned char MenuAllControlUout= 0x02; //��� ���� ������������ ������ MenuAllSynchrTimerNum

uchar TypeUdDev = 0;	//��� ���������� ��������, �� ��������� �����
strMenuGlbParam sMenuGlbParam;
strParamPVZUE sParamPVZE;
strParamOpt	sParamOpt;

strCorrParam sCorrParam[3]; //�������� ��������� �� ����� ���������

//
unsigned char DopComTrans;

//��������� �����
unsigned char MenuTypeDefend = MaxNumTypeDefend + 1;

//���������� ���������� �� ����� �� ����� �������� ��������� ��� ��� ���������� ��������
unsigned char ValueVsRange = 0;

//���������� ����������� ��� ��������� ����
unsigned char ShiftMenu=0;
unsigned char MaxShiftMenu=0;
unsigned char MaxDisplayLine=0;


unsigned char TimeInitLCD=0; //���������� ���������� �� ����� ����������������� ��
//���������� ������ ������������� �� � ���.
#define ConstTimeInitLCD 5

unsigned char Menu1Temp[]={0x30,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00};
//���������� ��� ����� ���-� � ����������
unsigned char InputValue[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char NumberInputChar=0x00;
unsigned char MaxNumberInputChar=0x00;
unsigned char*  ChangeMass;
unsigned char WorkRate=0x00;
unsigned char ByteShift=0x00;
unsigned char Discret=0x00; //���������� ������������ ��������� �����
unsigned int MaxValue, MinValue;
unsigned int TempValueD; //��������� ����� �� �������������
unsigned int TempValue; //��������� �����, ����� �������������
unsigned char TempValueBCD;
unsigned char InputParameter; //����������� ����� �������� ������ � ����������, �� ��������� = 0
unsigned char ControlParameter; //���������� ����� �� ��� ������ ��������
unsigned char Winking=0x00; //������� �������

//������ �������� ������
unsigned char PressPassword = 2;
__flash unsigned char Password[]={0x30,0x30,0x30,0x30,0x00};
unsigned char ePassword[]={0x00,0x00,0x00,0x00,0x00};

// ���������� ��� ������ ���������� ����������
unsigned char NumberAskMeasuring = 0x01;

//���������� ������ �������� ��������� �� ������
unsigned char InputSelectValue;
unsigned char SelectValue;
//unsigned char MaxSelectValue, MinSelectValue;
unsigned char __flash* __flash *MassSelectValue;
strNameToVal __flash *MassSelectValueRam; 
uint8_t *MassItems;

unsigned char TrParam, TrValue;
unsigned int TrValueD;

unsigned char PosModBusInfill = 0, ModBusInfill = 0;

//�����
unsigned char NumberRec;
unsigned char ReadArch = 0; // 1 - �������� ���� ������ ������, 2 - ������ ���������, 0 - ����� �� �����
extern unsigned int NumRecStart;
unsigned char ComArch; //����� ������� ��� ���������� ������������ ������

strArchiveDevice 	sArchiveDef(ARCH_DEF, ArchiveDef, 	ArchDef, 2048), 
					sArchivePrm(ARCH_PRM, ArchivePrm, 	ArchPrm), 
					sArchivePrd(ARCH_PRD, ArchivePrd, 	ArchPrd), 
					sArchiveEvt(ARCH_EVT, ArchiveEvent,	ArchEvt);
strArchives sArchives;  //��������� ������

//��� ������ ������
bool bDef; //false - ���, true-���� ������.
unsigned char cNumComR, cNumComT,cNumComR1,cNumComR2; //���-�� ������ �� ����� � ��������
bool bInpVal=false;  //���������� �� ���� ������ �������� ���������
unsigned char cTypeLine;  //��� ����� 1/2/3 = ��/����/�1
unsigned char cNumLine; //2-3 �������� �����
bool bReadVers = false; //true - ������ ���� �������, false - ����� �� ������, ���������� �����
bool bParamView = false; //����/��� ����� �� ����� �������������� ����������
bool bParamValue = false; //true - ���� �����������, false - hex ���
bool bLCDwork = true;  //���������� ���������� ������
bool bAllDevice = false; //���� ������������ ��� 4 ��������� (����, 2 ���������, ����������) , ������ ��� 3-� ��������
//��� ������ �� ���� ������� ���������, � ���� 0
bool bGlobalAvar = false, bGlobalWarn = false;
bool bDefAvar = false, bDefWarn = false;
bool bRec1Avar = false, bRec1Warn = false;
bool bTrAvar = false, bTrWarn = false;
bool bRec2Avar = false, bRec2Warn = false;
unsigned char cNumPrm;  //����� 1/2 ��������� � 3-� �������� ������
//unsigned char LineInMenu6=0; //���-�� ����� � ���� �������� ����������/ ���������� ���������
//unsigned __flash char  *mMenu6point[5]; //������ ����� ��� ���� �������� ����������/ ���������� ���������
unsigned char param4[10];
uchar   cNumKF;         /*���-�� ����������� ������ */

bool bUartTrReady1=false;

strMenuTest sMenuTest;

//�������� ������� ������ � ������� BazaModBus
BazaModBus ModBusBaza(DataM, JournalM, ePassword);

uint8_t cViewParam[11]="          ";
/*����� ���������� ���������
������� ������� - ������ ���������� :
1(2*) ������
3(4*) ��������
5(6*) ����������
7(8*) �����
* - ��������������� �� ������, ���� ���������� ����� ������ 15
������� ������� - ����� ��������� � ������
*/
uchar cNumParam;


/** ����� ������������ ��������� � ������� ������ �������
 *	@param *bytes ��������� �� ������ ������
 *	@param numBytes ���-�� ������������ ���� ������ � ������� ������
 *	@param searchDir ����������� ������
 *		@arg 0 ������ ������� � 0
 *		@arg 1 ������
 *		@arg 2 �����
 *	@param curNum ����� �������� ��������� 
 *	@return ����� ������ ���������
 */
static uint8_t findNextSubEntry(uint8_t *bytes, uint8_t numBytes, uint8_t searchDir, uint8_t curNum)
{
	bool find = false;
	uint8_t cnt = numBytes;
	int8_t pos = 0;
	int8_t byte = 0;
	
	if (searchDir < 2)
	{	
		if (searchDir == 1)
			curNum += 1;

		do
		{
			curNum %= (numBytes * 8);
			byte = curNum / 8;
			pos = curNum % 8;
			
			if ( *(bytes + byte) > 0)
			{
				for(uint8_t i = 1 << pos; i > 0; i <<= 1, curNum++)
				{
					if ( *(bytes + byte) & i )
					{
						find = true;
						break;
					}
				}
			}
			
			if (!find)
				curNum = (byte + 1) * 8;

			cnt--;
		}
		while( (!find) and (cnt > 0) );
	}
	else if (searchDir == 2)
	{
		curNum -= 1;

		do
		{
			curNum %= (numBytes * 8);
			byte = curNum / 8;
			pos = curNum % 8;

			for(uint8_t i = 1 << pos; i > 0; i >>= 1, curNum--)
			{
				if ( *(bytes + byte) & i )
				{
					find = true;
					break;
				}
			}

			if (!find)
				curNum = byte*8 - 1;

			cnt--;
		}
		while( (!find) and (cnt > 0) );
	}

	return curNum;
}


/**	�������������� ������ ����� � ������
 *	@param start ��������� ����� ������ � �������
 *	@param val ������������� ��������
 *	@param buf[] �����
 *	@return ���-�� �������� ���������� � �����
 */
static char itoa(uint8_t start, uint16_t val, uint8_t buf[])
{	
	uint8_t adr = start;
	uint8_t cnt = 0;
	
	// �������� ������, � ������� �������
	do
	{
		buf[adr++] = (val % 10) + '0';
		val = val / 10;
		cnt++;
	}
	while(val > 0);
	buf[adr] = '\0';
	
	// ���������� ���������� ������
	adr--;
	for (uint8_t tmp; start < adr; start++, adr--) 
	{
		tmp = buf[adr];
		buf[adr] = buf[start];
		buf[start] = tmp;
	}
	
	return cnt;
}

//��������� ������ ��������� ��������� ����������� ��������
static void FuncViewValue(uint8_t numparam)
{
	uchar i=0;
	uchar var=0;  //0- ��������� ��������, 1 - ������, 2 - �����
	uchar num;
	uint min, max;
	
	num = numparam & 0x1F;
	numparam = numparam & 0xE0;
	
	switch(numparam)
	{
		case 0x20:	//��������� ������
		{ 
			min = paramDef[num].min * paramDef[num].div;
			max = paramDef[num].max * paramDef[num].div;
			var = paramDef[num].var;
		}break;
		case 0x40:
		{
			min = paramPrm[num].min * paramPrm[num].div;
			max = paramPrm[num].max * paramPrm[num].div;
			var = paramPrm[num].var;
		}break;
		case 0x60:
		{
			min = paramPrd[num].min * paramPrd[num].div;
			max = paramPrd[num].max * paramPrd[num].div;
			var = paramPrd[num].var;
		}break;
		case 0x80:
		{
			min = paramGlb[num].min * paramGlb[num].div;
			max = paramGlb[num].max * paramGlb[num].div;
			var = paramGlb[num].var;
		}break;
	}
	
	switch(var)
	{
		case 1:
		{  //"������"
			i=0;
			do 
				cViewParam[i] = List[i];
			while (List[i++] != 0x00);
		}break;
		case 2:
		{  //����� ��������� ����� �����
			i += itoa(i, min, cViewParam); //�������
			cViewParam[i++]='.';
			cViewParam[i++]='.';
			itoa(i, max, cViewParam); //��������
		}break;
		case 3:
		{  //����� �������� ����� (1 ���� ����� �������)
			do cViewParam[i]=Menu16Shift10[i];
			while (Menu16Shift10[i++]!=0x00);
		}break;
		
		default:
		{ //"��� ������"
			i=0;
			do 
				cViewParam[i] = NoData[i];
			while (NoData[i++]!=0x00);
		}
	}//end switch(var)
}//end void FuncViewValue(char numparam)

//������� �� ������� '#'
static void PressSharp(void)
{
  	if (MenuLevel == LVL_START)
	{
		DopComTrans = 2;
	}
	else if (MenuLevel == LVL_DEF_SETUP)
	{
		ValueVsRange = (ValueVsRange > 0) ? 0 : 1;
		FuncViewValue(cNumParam + sMenuDefParam.punkt[ShiftMenu]);
		LCD2new = 1;
	}
	else if (MenuLevel < LVL_GLB_SETUP) 
	{
    	ValueVsRange = (ValueVsRange > 0) ? 0 : 1;
    	FuncViewValue(cNumParam + ShiftMenu);
    	LCD2new = 1;
  	}
 	else if (MenuLevel == LVL_GLB_SETUP)
	{
		ValueVsRange = (ValueVsRange > 0) ? 0 : 1;
		FuncViewValue(cNumParam + sMenuGlbParam.punkt[ShiftMenu]);
		LCD2new = 1;
	}
}

#include "Menu.c"

//������� ����� �������� ��������� ����/����������, � ������ �����
static void FuncInpCorrParam(void)
{
	signed int ii;
	LCDprintf(4, 1, MenuInputData, 1); //������� �� ����� "����:"
	
	FuncClearCharLCD(4,6,15); //������� 4-�� ������
	
	//�������� ����������� �������
	if ((PressKey=='D')&&(NumberInputChar>0)){
		if (InputParameter==1){
			if (NumberInputChar!=0){
				NumberInputChar--;
				if (NumberInputChar==2) NumberInputChar=1;
			}
			InputValue[NumberInputChar]=0x30;
		}else InputValue[--NumberInputChar]=0x00;
	}
	//���� �����, ���� ���-�� �������� �������� ��� ������ ���������������������
	if (NumberInputChar<MaxNumberInputChar){
		if ((PressKey>='0')&&(PressKey<='9')) {InputValue[NumberInputChar]=PressKey;NumberInputChar++;} //������� �� ������� �����
		if (InputParameter==1)
			if (NumberInputChar==2) NumberInputChar=3;
	}
	
	//����� �� ��������� ���������� ��������
	LCDprint(4, 7, InputValue,1);
	//����� ��������� �������, ���� �� ������� ����. ���-�� ��������
	if (NumberInputChar<MaxNumberInputChar){
		if (Winking==1){
			LCDprintf(4, 7 + NumberInputChar, WinkingMass, 0);
			Winking=0;
		}else Winking=1;
	}
	
	//����� ���������� �����
	if (PressKey=='C'){
		WorkRate=0x00; LCDbufClMenu(); LCD2new=1;
		for(NumberInputChar=0; NumberInputChar<4;NumberInputChar++) InputValue[NumberInputChar]=0x00;
		ValueVsRange=0; NumberInputChar=0x00; MaxNumberInputChar=0x00; ByteShift=0;MaxValue=0; MinValue=0;
	}
	
	if (PressKey=='E'){
		if (InputParameter==1){ //���� ������ ����������
			//���������� *10, ��� ����� ������� ����� ��������� � �����
			ii=(InputValue[0]&0x0f)*10;ii+=InputValue[1]&0x0F;
			ii*=10;
			ii+=(InputValue[3]&0x0F);
			//if ((UlineValue>999)||(UlineValue<-999)) UlineValue=0; - ��� �������� ������� � DataCenter.h
			if (ii==0){//���� ����� 0, �� ������� ��� �������� ������ ���������
				InputParameter+=3;
			}else{
				ii= ii - UlineValue + sCorrParam[0].Corr ;
				TrValueD=(unsigned char) ((signed char) (ii/10));
				TrValueD<<=8;
				TrValueD+=(unsigned char) ((signed char) (ii%10)*10);
			}
		}else{
			if (NumberInputChar==3){
				ii=((signed int) (InputValue[0]&0x0F)*100 + (InputValue[1]&0x0F)*10+ (InputValue[2]&0x0F));
			}else
				if (NumberInputChar==2){
					ii=((signed int) (InputValue[0]&0x0F)*10+ (InputValue[1]&0x0F));
				}else
					if (NumberInputChar==1){
						ii=(signed int) (InputValue[0]&0x0F);
					}else
						ii=IlineValue;
			if ((IlineValue>999)||(IlineValue<-999)) IlineValue=0;
			if (ii==0){//���� ����� 0, �� ������� ��� �������� ������ ���������
				InputParameter+=3;
			}else{
				ii=ii-IlineValue+sCorrParam[InputParameter-1].Corr;
				TrValueD=(unsigned int) *(&ii);
			}
		}
		
		if ((ii<1000)||(ii>-1000)){ //���� ���������� ���������� ��������
			TrParam=10; //��� ������ �������
			NumberTransCom=InputParameter; //��� ������ ����/����������
			
			for(NumberInputChar=0; NumberInputChar<5;NumberInputChar++) InputValue[NumberInputChar]=0x00;
			WorkRate=0x00;LCDbufClMenu();LCD2new=1;
			ValueVsRange=0;NumberInputChar=0x00;MaxNumberInputChar=0x00;ByteShift=0;MaxValue=0; MinValue=0;
		}
	}
	
	PressKey=0xF0;
}


//������� ����� ������ ���������
//������� ������ �������� ��������� �� ������
static void FuncSelectValue(void)
{
	LCDprintf(4, 1,  MenuInputData, 1); 	//������� �� ����� "����:"
	FuncClearCharLCD(4, 6, 15); 			//������� 4-�� ������
	LCDprintf(4, 7, MassSelectValue[InputSelectValue], 1);
	
	switch(PressKey)
    {
        case 'U': 
		{
            if (InputSelectValue > MinValue) InputSelectValue--;

            if (MenuLevel == LVL_REGIME)
            {//� ���� ��������� �������
                if ((cNumComT == 0) && (!bDef))
                {  //���� ��� ����� � ���, ���� ������ ���� 1
                    if (((SelectValue == 1) && (InputSelectValue == 2))||
                        ((SelectValue == 2) && (InputSelectValue == 1)))
                        InputSelectValue--;
                }
            }
        }
		break;
		
        case 'D': 
		{
            if (InputSelectValue < MaxValue)  InputSelectValue++;
		
            if (MenuLevel == LVL_REGIME)  //� ���� ��������� �������
			{
                if ((cNumComT==0)&&(!bDef)){  //���� ��� ����� � ���, ���� ������ ���� 1
                    if (((SelectValue==1)&&(InputSelectValue==2))||((SelectValue==2)&&(InputSelectValue==1))) InputSelectValue++;
                }
			}
        }
		break;
		
		case 'C': 
		{
			WorkRate=0x00; LCDbufClMenu(); LCD2new=1; InputSelectValue=0x00;
			MaxValue=0; MinValue=0;TrParam=0;
		}
		break;
		
		case '#': 
		PressSharp(); 
		break;
		
		case 'E': 
		{
			switch(MenuLevel)
			{
				case LVL_PROTOCOL:
				{
					Protocol=InputSelectValue; TrParam=0;
					eProtocol[0]=Protocol;eWrite=1;eAddressWrite=7;eMassiveWrite=eProtocol;
					if (Protocol==0) {Tr_buf_data_uart[0]=0x55; Tr_buf_data_uart[1]=0xAA;}
				}
				break;
				
				case LVL_INFO:
				{
					if (SelectValue==1) 
					{
						bParamView=InputSelectValue;
						if (bParamView) {bViewParam[0]=true;bViewParam[8]=true;bViewParam[9]=true;}
						else {bViewParam[0]=false;bViewParam[8]=false;bViewParam[9]=false;}
					}
					if (SelectValue==2) bParamValue=InputSelectValue;
				}
				break;
				
				case LVL_UPR:
				{
					TrParam = SelectValue;
				}
				break;
				
				default:
				{
					TrParam = SelectValue; TrValue = InputSelectValue;
				}
			}
			LCDbufClMenu();
			LCD2new=1;
			WorkRate=0x00;
		}
		break;
    }
	PressKey=0xF0;
}

/** ������� ��������� ������� ������ ��� ������ �������� �� ������
 *	���� ���������� �� ������� ��������
 *	MassSelectValueRam - ������ �������� �������� <-> ������
 *	MassItems - ������ ��������� ������� �� ������� ��������
 *	MaxValue - ���-�� ��������� � ������� MassItems (����. ��� [2] ����� 2)
 *	@param ���
 *	@return ���
 */
static void FuncSelectValueList(void)
{
	FuncClearCharLCD(4, 6, 15); 			// ������� 4-�� ������
	LCDprintf(4, 1, MenuInputData, 1); 	// ������� �� ����� "����:"
	LCDprintf(4, 7, MassSelectValueRam[MassItems[InputSelectValue]].name, 1);
	
	switch(PressKey)
	{
		 case 'U': 
		{
            if (InputSelectValue > MinValue) 
				InputSelectValue--;
        }
		break;
		
		case 'D': 
		{
            if (InputSelectValue < (MaxValue - 1))
				InputSelectValue++;
        }
		break;
		
		case 'C': 
		{
			WorkRate=0x00; LCDbufClMenu(); LCD2new=1; InputSelectValue=0x00;
			MaxValue=0; MinValue=0; TrParam=0;
		}
		break;
		
		case 'E':
		{
			TrParam = SelectValue; 
			TrValue = MassSelectValueRam[MassItems[InputSelectValue]].val;
			LCDbufClMenu();
			LCD2new=1;
			WorkRate=0x00;
		}
		break;
	}
	PressKey = 0xF0;
}

static void FuncInputDataTime(void)
{
	FuncClearCharLCD(4, 6, 15); //������� 4-�� ������
	LCDprintf(4, 1, MenuInputData, 1); //������� �� ����� "����:"
	LCDprint(4, 7, InputDataTime, 1);
	
	if (NumberInputChar < 8)
	{ //����� ��������� �������
		if (Winking==1)
		{
			if (MenuLevel == LVL_SETUP)
			{
				if (PressPassword==2) LCDprintf(4, 9 + NumberInputChar, WinkingMass,0);
				if (PressPassword==1) LCDprintf(4, 15 + NumberInputChar, WinkingMass,0);
			}
			else if ((MenuLevel == LVL_REGIME) && (PressPassword==2)) 
			{
				LCDprintf(4, 9 + NumberInputChar, WinkingMass, 0);
			}
			else 
				LCDprintf(4, 7 + NumberInputChar, WinkingMass, 0);
			Winking=0;
		}
		else 
			Winking=1;
	}
	
	if (NumberInputChar<8){ //���� ���-�� �������� �������� ��� ������ ���������������������
		if ((PressKey>='0')&&(PressKey<='9')){ //������� �� ������� �����
			//������ ����
			if (InputParameter==1){
				switch (NumberInputChar){
					case 0: {
						if (PressKey<='3'){
							InputDataTime[NumberInputChar]=PressKey;
							NumberInputChar++;
							if (PressKey=='3') InputDataTime[NumberInputChar]='0';
						}
					}break;
					case 1: {
						if (InputDataTime[0]=='3') {if (PressKey<='1'){InputDataTime[NumberInputChar]=PressKey; NumberInputChar++;}}
						else  {InputDataTime[NumberInputChar]=PressKey;NumberInputChar++;}
					}break;
					case 3:{
						if (PressKey<='1'){
							InputDataTime[NumberInputChar]=PressKey;
							NumberInputChar++;
							if (PressKey=='1') InputDataTime[NumberInputChar]='0';
						}
					}break;
					case 4: {
						if (InputDataTime[3]=='1') {if (PressKey<='2') {InputDataTime[NumberInputChar]=PressKey; NumberInputChar++;}}
						else {InputDataTime[NumberInputChar]=PressKey;NumberInputChar++;}
					}break;
					case 6:
					case 7: {InputDataTime[NumberInputChar]=PressKey;NumberInputChar++;} break;
				}
			}
			
			if (InputParameter==2){
				switch(NumberInputChar){
					case 0: {
						if (PressKey<='2'){
							InputDataTime[NumberInputChar]=PressKey;
							NumberInputChar++;
							if (PressKey=='2'){
								if (InputDataTime[1]>'3') InputDataTime[NumberInputChar]='0';
							}
						}
					}break;
					case 1:{
						if (InputDataTime[0]=='2') {if (PressKey<'4') {InputDataTime[NumberInputChar]=PressKey; NumberInputChar++;}}
						else {InputDataTime[NumberInputChar]=PressKey;NumberInputChar++;}
					}break;
					case 6:
					case 3: {if (PressKey<='5') {InputDataTime[NumberInputChar]=PressKey;NumberInputChar++;}} break;
					case 7:
					case 4: {InputDataTime[NumberInputChar]=PressKey;NumberInputChar++;} break;
				}
			}
			
			if (NumberInputChar==2) NumberInputChar=3;if (NumberInputChar==5) NumberInputChar=6;
		}
	}
	
	//������� � ���������� �����
	if ((PressKey=='D')&&(NumberInputChar>0)) {NumberInputChar--;if (NumberInputChar==2) NumberInputChar=1;if (NumberInputChar==5) NumberInputChar=4;}
	//������� � ��������� �����
	if ((PressKey=='U')&&(NumberInputChar<7)) {NumberInputChar++;if (NumberInputChar==2) NumberInputChar=3;if (NumberInputChar==5) NumberInputChar=6;}
	//������
	if (PressKey=='C') {WorkRate=0x00;NumberInputChar=0;FuncClearCharLCD(4,1,20); LCD2new=1;}
	//����
	if (PressKey=='E'){
		if (InputParameter==1){
			TempValue=(InputDataTime[0]-0x30)*10+(InputDataTime[1]-0x30);
			if (TempValue<32) TrDataTimeMass[2]=((InputDataTime[0]-0x30)<<4)+(InputDataTime[1]-0x30);
			TempValue=(InputDataTime[3]-0x30)*10+(InputDataTime[4]-0x30);
			if (TempValue<13) TrDataTimeMass[1]=((InputDataTime[3]-0x30)<<4)+(InputDataTime[4]-0x30);
			TrDataTimeMass[0]=((InputDataTime[6]-0x30)<<4)+(InputDataTime[7]-0x30);
		}
		if (InputParameter==2){
			TempValue=(InputDataTime[0]-0x30)*10+(InputDataTime[1]-0x30);
			if (TempValue<24) TrDataTimeMass[3]=((InputDataTime[0]-0x30)<<4)+(InputDataTime[1]-0x30);
			TempValue=(InputDataTime[3]-0x30)*10+(InputDataTime[4]-0x30);
			if (TempValue<60) TrDataTimeMass[4]=((InputDataTime[3]-0x30)<<4)+(InputDataTime[4]-0x30);
			TempValue=(InputDataTime[6]-0x30)*10+(InputDataTime[7]-0x30);
			if (TempValue<60) TrDataTimeMass[5]=((InputDataTime[6]-0x30)<<4)+(InputDataTime[7]-0x30);
		}
		NewTime=1;WorkRate=0x00;NumberInputChar=0;FuncClearCharLCD(4,1,20); LCD2new=1;
	}
	PressKey=0xF0;
}

//������� ����� �������� � ����������
static void FuncInputData(void)
{
  	FuncClearCharLCD(4, 6, 15); //������� 4-�� ������
	//������� �� ��������� "����:", "������:" ��� "����� ������:"
  	if (MenuLevel == LVL_SETUP)
	{
    	if (PressPassword == 2)
			LCDprintf(4, 1, MenuInputOldPassword, 1);
    	if (PressPassword == 1)
			LCDprintf(4, 1, MenuInputNewPassword, 1);
  	}
	else if ( (MenuLevel == LVL_REGIME) && (PressPassword == 2) )
	{
		LCDprintf(4, 1, MenuInputOldPassword, 1);
	}
    else
		LCDprintf(4, 1, MenuInputData, 1); //������� �� ����� "����:"
		
	if (NumberInputChar<MaxNumberInputChar) //���� ���-�� �������� �������� ��� ������ ���������������������
		if ( (InputParameter == 14) || (InputParameter == 15) || (InputParameter == 20) || (InputParameter == 21) )
		{	//�.�. ������ ���-� �� 0 � 1
			if ( (PressKey == '0') || (PressKey == '1') )
			{
				InputValue[NumberInputChar] = PressKey;
				NumberInputChar++;
			}
		}else
			if ( (PressKey >= '0') && (PressKey <= '9') )
			{	//������� �� ������� �����
				InputValue[NumberInputChar] = PressKey;
				NumberInputChar++;
			}
	
	if (PressKey == '#')
		PressSharp();
		
		
	//����� ��������� �������, ���� �� ������� ����. ���-�� ��������
	if (NumberInputChar < MaxNumberInputChar)
	{
		if (Winking == 1)
		{
			if (MenuLevel == LVL_SETUP)
			{
				if (PressPassword == 2)
					LCDprintf(4, 9 + NumberInputChar, WinkingMass, 0);
				if (PressPassword == 1)
					LCDprintf(4, 15 + NumberInputChar, WinkingMass, 0);
			}
			else if ( (MenuLevel == LVL_REGIME) && (PressPassword == 2) )
			{
				LCDprintf(4, 9 + NumberInputChar, WinkingMass, 0);
			}
			else
				LCDprintf(4, 7 + NumberInputChar, WinkingMass, 0);
			Winking=0;
		}
		else
			Winking=1;
	}
		
	//�������� ����������� �������
	if ( (PressKey == 'D') && (NumberInputChar > 0) )
	{
		NumberInputChar--;
		InputValue[NumberInputChar] = 0x00;
	}
	
	//����� �� ��������� ���������� ��������
	if (MenuLevel == LVL_SETUP)
	{
		if (PressPassword == 2)
			LCDprint(4, 9, InputValue, 1);
		if (PressPassword == 1)
			LCDprint(4, 15, InputValue, 1);
	}
	else if ( (MenuLevel == LVL_REGIME) && (PressPassword == 2) )
	{
		LCDprint(4, 9, InputValue, 1);
	}
	else
		LCDprint(4, 7, InputValue, 1);
			
	//����� ���������� �����
	if (PressKey=='C')
	{
		//������ � �������
		if (PressPassword==1) PressPassword=2;
		//���� ����� �� �������, ����1-3 , �� ������� EntPass
		if ((bDef)&&(CurrentState[0]==2)) EntPass=0;
		if ((cNumComR>0)&&((CurrentState[2]==1)||(CurrentState[2]==2))) EntPass=0;
		if ((cNumComT>0)&&(CurrentState[4]==2)) EntPass=0;
		
		if (EntPass==1) PassCen=1;
		WorkRate=0x00; LCDbufClMenu(); LCD2new=1;
		for(NumberInputChar=0; NumberInputChar<4;NumberInputChar++) InputValue[NumberInputChar]=0x00;
		ValueVsRange=0; NumberInputChar=0x00; MaxNumberInputChar=0x00; ByteShift=0;
		MaxValue=0; MinValue=0;
	}
	//��������� �������� ����������, ��������� 0 � 1
	if (((InputParameter==14)||(InputParameter==15)||(InputParameter==20)||(InputParameter==21))&&(NumberInputChar==MaxNumberInputChar)&&(PressKey=='E'))
	{
		WorkRate=0x00;LCDbufClMenu();LCD2new=1;TempValue=0;
		if (MaxNumberInputChar==8) TempValue=((InputValue[0]-0x30)*128)+((InputValue[1]-0x30)*64)+((InputValue[2]-0x30)*32)+((InputValue[3]-0x30)*16)+((InputValue[4]-0x30)*8)+((InputValue[5]-0x30)*4)+((InputValue[6]-0x30)*2)+((InputValue[7]-0x30));
		if (MaxNumberInputChar==4) TempValue=((InputValue[0]-0x30)*8)+((InputValue[1]-0x30)*4)+((InputValue[2]-0x30)*2)+((InputValue[3]-0x30));
		ControlParameter=1; TrValue=TempValue;
		if ((InputParameter==14)||(InputParameter==15)) TrParam=InputParameter-10;
		if ((InputParameter==20)||(InputParameter==21)) TrParam=InputParameter-16;
		// ������� �������� ������
		for(NumberInputChar=0; NumberInputChar<8;NumberInputChar++) InputValue[NumberInputChar]=0x00;
		NumberInputChar=0x00;MaxNumberInputChar=0x00;ByteShift=0;InputParameter = 0;
		MaxValue=0; MinValue=0;
	}
			
	//�������� ���������� ����a
	if (	(PressKey=='E') && (MenuLevel != LVL_MENU) && (MenuLevel != LVL_SETUP) && (MenuLevel != LVL_REGIME) &&
		(InputParameter != 14) && (InputParameter != 15) && (InputParameter != 20) && (InputParameter != 21) )
	{
		WorkRate=0x00;LCDbufClMenu();LCD2new=1;
		
		switch(NumberInputChar)
		{
			case 1:{
				TempValueD=(InputValue[0]-0x30)/Discret;
				TempValue=TempValueD*Discret;
				TempValueBCD=InputValue[0]-0x30;
				if ((TempValue>=MinValue)&&(TempValue<=MaxValue)) ControlParameter=1;
			}break;
			case 2:{
				TempValueD=((InputValue[0]-0x30)*10+(InputValue[1]-0x30))/Discret;TempValue=TempValueD*Discret;
				TempValueBCD=((InputValue[0]-0x30)<<4)+(InputValue[1]-0x30);
				if ((TempValue>=MinValue)&&(TempValue<=MaxValue)) ControlParameter=1;
			}break;
			case 3:{
				TempValueD=((InputValue[0]-0x30)*100+(InputValue[1]-0x30)*10+(InputValue[2]-0x30))/Discret;
				TempValue=TempValueD*Discret;
				if ((TempValue>=MinValue)&&(TempValue<=MaxValue)) ControlParameter=1;
			}break;
			case 4:{
				TempValueD=((InputValue[0]-0x30)*1000+(InputValue[1]-0x30)*100+(InputValue[2]-0x30)*10+(InputValue[3]-0x30))/Discret;
				TempValue=TempValueD*Discret;
				if ((TempValue>=MinValue)&&(TempValue<=MaxValue)) ControlParameter=1;
			}break;
		}
		
		//� ������ ���������� � �������� � USP �������� ��������, ���� ����������
		if (ControlParameter==1)
		{
			switch(InputParameter)
			{
				case 7: {TrParam=2+InputParameter-7;TrValue=TempValue-1;} break;
				case 8: {TrParam=2+InputParameter-7;TrValue=TempValue;} break;
				case 9:
				case 10: {TrParam=2+InputParameter-7;TrValue=TempValue;} break;
				case 11: {TrParam=InputParameter-10;TrValue=TempValue;} break;
				case 12:
				case 13: {TrParam=InputParameter-10;TrValue=TempValue/10;} break;
				case 17: {TrParam=InputParameter-16;TrValue=TempValue;} break;
				case 18:
				case 19: {TrParam=InputParameter-16;TrValue=TempValue/10;} break;
				case 25:
				case 26: {TrParam=InputParameter-21;TrValue=TempValue;} break;
				case 27: {TrParam=6; TrValue=TempValue;} break;//�������� �����/���������� ������
				case 28: {TrParam=InputParameter-22;TrValueD=TempValueD;} break;
				case 29: {TrParam=InputParameter-22;TrValue=TempValue;} break;
				case 30: {TrParam=8; TrValue=TempValue;} break; //�������� ���/���������� ������
				case 0x39: {TrParam = 0x39; TrValue = TempValue;} break;
				case 0xB6: {TrParam=2; TrValue=TempValue;} break; //�������� ����� , U��� �����������
			}
			InputParameter=0;
			ControlParameter=0;
		}
		
		// ������� �������� ������
		for(NumberInputChar=0; NumberInputChar<8;NumberInputChar++) InputValue[NumberInputChar]=0x00;
		
		ValueVsRange=0;NumberInputChar=0x00;MaxNumberInputChar=0x00;ByteShift=0;MaxValue=0; MinValue=0;
	}
	
	//���� �� ������� ������
	if (	(PressKey == 'E') && (NumberInputChar == 4) && ( (PressPassword == 1) || (PressPassword == 2) ) && 
			((MenuLevel == LVL_SETUP) || (MenuLevel == LVL_REGIME)) )
	{
		WorkRate=0x00;LCDbufClMenu();LCD2new=1;
		//�������� ��������� ������ ���� 2, ���� 1 ���� ������ ������
		if (PressPassword==2){
			//�������� ���������� � ���������������� �������
			NumberInputChar=0;
			for (PressPassword=0; PressPassword<4; PressPassword++) if (InputValue[PressPassword]!=ePassword[PressPassword]) NumberInputChar++;
			//���� ������ �� ������ � ����������������, ������� ��� � ����������
			if (NumberInputChar!=0){
				NumberInputChar=0;
				for (PressPassword=0; PressPassword<4; PressPassword++) if (InputValue[PressPassword]!=Password[PressPassword]) NumberInputChar++;
			}
			//���� ������ �����
			//**************/ NumberInputChar =0;
			
			if (NumberInputChar==0) {PressPassword=1;NewPass=1;}
			else{
				PressPassword=2;
				if ((bDef)&&(CurrentState[0]==2)) EntPass=0;
				if ((cNumComR>0)&&((CurrentState[2]==1)||(CurrentState[2]==2))) EntPass=0;
				if ((cNumComT>0)&&(CurrentState[4]==2)) EntPass=0;
				
				if (EntPass==1) PassCen=1;
			}
		}else{
			//����� ����� ������
			if (PressPassword==1){
				ePassword[0]=InputValue[0];ePassword[1]=InputValue[1];ePassword[2]=InputValue[2];ePassword[3]=InputValue[3];
				ModBusBaza.NewPass(ePassword);
				//� ������ ������� ������ � EEPROM
				eWrite=1;eAddressWrite=0;eMassiveWrite=ePassword;
				PressPassword=2;
			}
		}
		// ������� �������� ������
		for(NumberInputChar=0; NumberInputChar<4;NumberInputChar++) InputValue[NumberInputChar]=0x00;
		NumberInputChar=0x00;MaxNumberInputChar=0x00;ByteShift=0;MaxValue=0; MinValue=0;
	}
			
	PressKey=0xF0;
	if (PassCen==1) {PressKey='E'; PassCen=0;}
	if ( (PressPassword == 1) && (MenuLevel == LVL_REGIME) ) 
		PressKey='E';
	if ( (PressPassword == 1) && (MenuLevel == LVL_SETUP) && (NewPass == 1) ) 
	{
		PressKey = '3'; 
		NewPass = 0;
	}
}

//��������� ������� ������
static void FuncPressKey(void)
{
	eMENUlvl lvl = MenuLevel;
	uint8_t key = PressKey;
	switch(key)
	{
        case '1':
		{
			switch(lvl)
			{
				case LVL_MENU: 			//������	
				Menu_Journal(); 					
				break;	
				
				case LVL_DATA_TIME: 	//���� ����/�������	
				PressInMenuDataTime(1); 			
				break;  
				
				case LVL_JOURNAL: 		// ������\������ �������	
				PressInMenuJournal('1'); 			
				break;  
				
				case LVL_SETUP: 		//������� � ���� ����������\�����	
				Menu_Setup_Regime(); 				
				break;  
				
				case LVL_PARAM_VIEW:
				case LVL_PARAM_SETUP:
					pressInMenuParam(lvl, key);
				break;
				
				case LVL_UPR: 			
				PressInMenuReset(1); 				
				break;
			}
		}break;
		
        case '2':
		{
			switch(lvl)
			{
				case LVL_START:			
				{  //��������� ���������� ����������
					if (cTypeLine==1)
					{
						do
						{
							if (NumberAskMeasuring>1) 
								NumberAskMeasuring--; 
							else NumberAskMeasuring=10;
						}
						while( !bViewParam[NumberAskMeasuring-1] ); 			// �������� �� ������ ����������� ���-��
						eNumberAskMeasuring[0] = NumberAskMeasuring;
						eWrite = 1; 
						eAddressWrite = 5;
						eMassiveWrite = eNumberAskMeasuring;
					}
				}break;
				
				case LVL_MENU: 			// ������� � ����� "���� ����/�����"		
				Menu_DataTime(); 					
				break;	
				
				case LVL_DATA_TIME: 	 // ���� �������
				PressInMenuDataTime(2); 			
				break; 
				
				case LVL_JOURNAL: 		// ������/ ������ ����������
				PressInMenuJournal('2'); 			
				break;  
				
				case LVL_SETUP: 		// ����������\���������
				Menu_ParamSetup(LVL_PARAM_SETUP); 	
				break; 	
				
				case LVL_PARAM_VIEW:
				case LVL_PARAM_SETUP:
					pressInMenuParam(lvl, key);
				break;
				
				case LVL_UPR: 			
				PressInMenuReset(2); 				
				break;
			}
        }break;
		
        case '3':
		{
			switch(lvl)
			{
				case LVL_MENU: 		//������� � ����/����������	
				Menu_Upr(); 						
				break;	
				
				case LVL_JOURNAL: 	//������/ ������ ����������	
				PressInMenuJournal('3'); 			
				break; 				
				
				case LVL_SETUP:	
				{ 
					//���� ������ ������
					if (PressPassword==2)		
					{
						WorkRate=0x01;
						MaxNumberInputChar=4;
						ChangeMass=ePassword;
						ByteShift=0;
						MaxValue=0;
						MinValue=0;
						Discret=1;
					}
					else if (PressPassword == 1)
					{
						WorkRate=0x01;
						MaxNumberInputChar=4;
						ChangeMass=ePassword;
						ByteShift=0;
						MaxValue=0;
						MinValue=0; 
						Discret=1; //������� 1
					}
				}break;
				
				case LVL_PARAM_VIEW:
				case LVL_PARAM_SETUP:
					pressInMenuParam(lvl, key);
				break;
				
				case LVL_UPR: 			
				PressInMenuReset(3); 				
				break;
			}
        }break;
        case '4':
		{
			switch(lvl)
			{
				case LVL_START: 												//������������ ����������� � ��������� ���� ����/�������
				{
					if (cTypeLine == 1) 
					{
						if (LCDtimer > 1) 
							LCDtimer--; 
						else 
							LCDtimer = maxLCDtimer;
					}
				}
				break; 
				
				case LVL_MENU: 			//���� � ���� "����������"	
				Menu_Setup(); 						
				break; 	
				
				case LVL_JOURNAL:		//������/ ������ ���������� 		
				PressInMenuJournal('4'); 			
				break;  
				
				case LVL_SETUP: 		//������� � �������� ����������\����� (����������\�����)//������� � ���� ������	
				Menu_Setup_Test(); 					
				break; 
				
				case LVL_PARAM_VIEW:
				case LVL_PARAM_SETUP:
					pressInMenuParam(lvl, key);
				break;
				
				case LVL_DEF_VIEW:
				case LVL_DEF_SETUP: { 
					//����� ������, � ���������� ����� ��� 3-� �������� �����
					if (sMenuDefParam.punkt[ShiftMenu] == 3) {
						if ( (cTypeLine == 2) && ((cNumLine == 3) || (sParamOpt.reserv == 1)) )
						{
							
							NumberCom = (NumberCom == 1) ? 2 : 1;
							LCDbufClMenu();
							LCD2new=1;
						}
					}
				}
				break;
				
				case LVL_PRM_VIEW:
				case LVL_PRM_SETUP:
				{ 	//���������� ������ �������,��� ���������											
					unsigned char tNumComR;
					
					if (cNumLine==2) 
						tNumComR = cNumComR;
					else
					{
						if (cNumPrm==1) 
							tNumComR = cNumComR1;
						else 
							tNumComR = cNumComR2;
					}

					if (ShiftMenu==2)
					{  //�������� �� ����
						if (NumberCom>1) 
							NumberCom--; 
						else 
							NumberCom = tNumComR;
							LCDbufClMenu();LCD2new=1;
					}
					else
					{  //���� � ���� ������
						if ((ShiftMenu==3)||(ShiftMenu==4))
						{
							if (tNumComR>8)
								if (NumberCom>1) NumberCom--; else NumberCom=tNumComR/8;
								LCDbufClMenu();LCD2new=1;
						}
					}
				}
				break; 
				
				case LVL_PRD_VIEW:
				case LVL_PRD_SETUP:
				{  //���������� ������ �������, ��� �����������
					if ( (ShiftMenu == 2) || (ShiftMenu == 3) )
					{
						if (cNumComT > 8)
						{
							
							if (NumberCom > 1) 
								NumberCom--; 
							else 
								NumberCom=cNumComT/8;
							LCDbufClMenu(); LCD2new=1;
						}
					}
				}
				break;
				
				case LVL_GLB_VIEW:
				case LVL_GLB_SETUP:												//���������/����
				{ 
					if (ShiftMenu==9)
						if (cNumLine==3)
							if (NumberCom==1) NumberCom=2; else NumberCom=1;
				}
				break;
				
				case LVL_UPR: 
				PressInMenuReset(4); 
				break;
				
				case LVL_JRN_VIEW:
				sArchives.subNum = findNextSubEntry(sArchives.bytes, 4, 2, sArchives.subNum);
				break;
			}
        }break;
        case '5':
		{
			if (lvl == LVL_MENU)
			{
				// ������� � �������� ����������
				Menu_ParamSetup(LVL_PARAM_VIEW); 								
			}
			else if (lvl == LVL_UPR) 
			{
				PressInMenuReset(5);
			}
        }break;
		
        case '6':
		{
			switch(lvl)
			{
				case LVL_START:
				{	//������������ ����������� � ��������� ���� ����/�������
					if (cTypeLine==1) 
					{
						LCDtimer++;
						if (LCDtimer>maxLCDtimer) 
							LCDtimer=1;
					}
				}
				break; 		
				
				case LVL_MENU: 	
				Menu_Protocol(); 
				break;

				case LVL_DEF_VIEW:
				case LVL_DEF_SETUP:
				{ //����� ������ � ���������� �����, ��� 3-� �������� �����
//					if (cNumLine==3)
//					{
//						if ((ShiftMenu==3)||(ShiftMenu==5)) if (NumberCom==1) NumberCom=2; else NumberCom=1;
//					}
					if (sMenuDefParam.punkt[ShiftMenu] == 3) {
						if ( (cTypeLine == 2) && ((cNumLine == 3) || (sParamOpt.reserv == 1)) )
						{
							
							NumberCom = (NumberCom == 1) ? 2 : 1;
							LCDbufClMenu();
							LCD2new=1;
						}
					}
				}
				break;
				
				case LVL_PRM_VIEW:
				case LVL_PRM_SETUP:
				{ //���� ���������� ���������
					unsigned char tNumComR;
					
					if (cNumLine==2) 
						tNumComR = cNumComR;
					else
						if (cNumPrm==1) 
							tNumComR=cNumComR1;
						else 
							tNumComR=cNumComR2;
						
					if (ShiftMenu == 2)
					{
						if (NumberCom<tNumComR) 
							NumberCom++; 
						else 
							NumberCom=1;
						LCDbufClMenu();
						LCD2new=1;
					}
					else
					{
						if ((ShiftMenu==3)||(ShiftMenu==4))
						{
							if (tNumComR>8)
								if (NumberCom < (tNumComR / 8)) 
									NumberCom++; 
								else 
									NumberCom=1;
								LCDbufClMenu();
								LCD2new=1;
						}
					}
				}
				break; //������ ������
				
				case LVL_PRD_VIEW:
				case LVL_PRD_SETUP:
				{ //���� ���������� �����������
					if ((ShiftMenu == 2)||(ShiftMenu == 3)){
						if (cNumComT>8){
							if (NumberCom<(cNumComT/8)) NumberCom++; else NumberCom=1;
							LCDbufClMenu();LCD2new=1;
						}
					}
				}
				break;
				
				case LVL_GLB_VIEW:
				case LVL_GLB_SETUP:
				{ //���������/����
					if (ShiftMenu==9)
						if (cNumLine==3)
							if (NumberCom==1) NumberCom=2; else NumberCom=1;
				}
				break;
				
				case LVL_UPR: 
				PressInMenuReset(6); 
				break;
				
				case LVL_JRN_VIEW:
				sArchives.subNum = findNextSubEntry(sArchives.bytes, 4, 1, sArchives.subNum);
				break;
			}
        }break;
		
        case '7':{
			if (lvl == LVL_MENU) 
				Menu_Info();
			else if (lvl == LVL_UPR) 
				PressInMenuReset(7);
        }
		break;
		
        case '8':{
			if (lvl == LVL_START)
			{  																	//��������� ���������� ����������
				if (cTypeLine == 1)
				{
					do
					{
						NumberAskMeasuring++; 
						if (NumberAskMeasuring>10) 
							NumberAskMeasuring=1;
					}
					while( !bViewParam[NumberAskMeasuring-1] ); 				//�������� �� ������ ����������� ���-��
					eNumberAskMeasuring[0] = NumberAskMeasuring;
					eWrite = 1;
					eAddressWrite = 5;
					eMassiveWrite = eNumberAskMeasuring;
				}
			}
			if (MenuLevel == LVL_UPR) 
				PressInMenuReset(8);
        }
		break;
		
        case '9':
        {
            if (lvl == LVL_UPR) 
				PressInMenuReset(9);
        }
		break;
		
		case '0':
        {
            if (lvl == LVL_UPR) 
				PressInMenuReset(0);
        }
		break;
		
        case 'M':
		{
			if (lvl == LVL_START) 
				Menu_Second(); //������� �� ������ �������
			else 
				Menu_Start();//����� � ������ ������ ������� �� ��������� ����
        }
		break;
		
        case 'C':
		{
			switch (lvl)
			{
				case LVL_MENU: 			Menu_Start(); 	break;					//������� � ��������� ����
				
				case LVL_DATA_TIME:
				case LVL_JOURNAL:
				case LVL_SETUP:
				case LVL_PARAM_VIEW:
				case LVL_PROTOCOL:
				case LVL_INFO:
				case LVL_UPR: 			Menu_Second(); 	break;  				//������� � ���� 2-��� ������
				
				case LVL_DEF_VIEW:
				case LVL_PRM_VIEW:
				case LVL_PRD_VIEW:
				case LVL_GLB_VIEW: 		Menu_ParamSetup(LVL_PARAM_VIEW); 	break; 	//������� � �������� ����������
				
				case LVL_TEST:
				case LVL_REGIME:
				case LVL_PARAM_SETUP: 	Menu_Setup(); 	break; 					//������� � �����/����������
				
				case LVL_DEF_SETUP:
				case LVL_PRM_SETUP:
				case LVL_PRD_SETUP:
				case LVL_GLB_SETUP: 	Menu_ParamSetup(LVL_PARAM_SETUP); 	break; 	//������� � �����������\���������

				case LVL_JRN_VIEW: 		Menu_Journal(); break;		 			//������� � ���� ������
			}
        }
		break;
		
        case 'U':
		{
			switch(lvl)
			{
				case LVL_START:
				{
					if (bAllDevice)
					{
						if (ShiftMenu == 1) 
							ShiftMenu=0;
					}
				}
				break;
				
				case LVL_DEF_SETUP:
				case LVL_PRM_SETUP:
				case LVL_PRD_SETUP:
				case LVL_GLB_SETUP:	
				case LVL_DEF_VIEW:
				case LVL_PRM_VIEW:
				case LVL_PRD_VIEW:
				case LVL_GLB_VIEW: ValueVsRange = 0;
				case LVL_MENU:
				case LVL_JOURNAL:
				case LVL_SETUP:
				case LVL_PARAM_VIEW:
				case LVL_PARAM_SETUP:
				case LVL_INFO:
				case LVL_TEST:
				case LVL_UPR:
				{
					if (ShiftMenu > 0) 
					{
						ShiftMenu--; LCD2new=1; LCDbufClMenu(); NumberCom=1;
					}
					
//					if ((MenuLevel == LVL_PRM_VIEW) || (MenuLevel == LVL_PRM_SETUP))
//					{  //���� �������� ���������� ���������
//						if (ShiftMenu == 1)
//							ShiftMenu--;
//						
//					}
//					else if ( (MenuLevel == LVL_PRD_VIEW) || (MenuLevel == LVL_PRD_SETUP) )
//					{
//						if (ShiftMenu == 2)
//							ShiftMenu--;
//					}
					
					
					
				}
				break; //��������� ����
				
				case LVL_JRN_VIEW:
				{
					strArchives *ptr = &sArchives;
					
					if (ptr->curEntry > 0)
						ptr->curEntry--;
					else
					{
						if (ptr->ovf)
							ptr->curEntry = ptr->curArchive->maxNumEntries - 1;
						else
							ptr->curEntry = ptr->oldestEntry - 1;
					}
					ptr->subNum = 0;
					ptr->refresh = false;
				}
				break;
			}
        
		}break;
		
        case 'D':
		{
			switch(lvl)
			{
				case LVL_START:
				{  //��������� ����, ���� 3-� �������� � ��� 4 ����������
					if (bAllDevice)
					{
						if (ShiftMenu == 0) 
							ShiftMenu = 1;
					}
				}break;
				
				case LVL_DEF_SETUP:
				case LVL_PRM_SETUP:
				case LVL_PRD_SETUP:
				case LVL_GLB_SETUP:	
				case LVL_DEF_VIEW:
				case LVL_PRM_VIEW:
				case LVL_PRD_VIEW:
				case LVL_GLB_VIEW: ValueVsRange=0;				
				case LVL_MENU:
				case LVL_JOURNAL:
				case LVL_SETUP:
				case LVL_PARAM_VIEW:
				case LVL_PARAM_SETUP:
				case LVL_INFO:
				case LVL_TEST:
				case LVL_UPR:
				{
					if (ShiftMenu < MaxShiftMenu) 
					{
						ShiftMenu++; LCD2new=1; LCDbufClMenu(); NumberCom=1;
					}
//					if ( (MenuLevel == LVL_PRM_VIEW) || (MenuLevel == LVL_PRM_SETUP) )
//					{  //���� �������� ���������� ���������
//						if (ShiftMenu == 1)
//							ShiftMenu++;
//						
//					}
//					else if ( (MenuLevel == LVL_PRD_VIEW) || (MenuLevel == LVL_PRD_SETUP) )
//					{
//						if (ShiftMenu == 2)
//							ShiftMenu++;
//					}
				}break; //��������� ����
				
				case LVL_JRN_VIEW:
				{
					strArchives *ptr = &sArchives;
					
					if (ptr->ovf)
					{
						if (ptr->curEntry < ptr->curArchive->maxNumEntries - 1)
							ptr->curEntry++;
						else
							ptr->curEntry = 0;
						
					}
					else
					{
						if (ptr->curEntry < ptr->oldestEntry - 1)
							ptr->curEntry++;
						else
							ptr->curEntry = 0;
					}
					ptr->subNum = 0;
					ptr->refresh = false;
				}
				break;
			}
        }
		break;
		
        case '#':
		PressSharp();
		break;
		
        case 'E':
		{
			switch(lvl)
			{
				case LVL_START: DopComTrans=1; break; 							//"����" ���������
				
				case LVL_REGIME:
				{  //���� ������� ������
					if ((PressPassword==2)&&(EntPass==0))
					{
						WorkRate=0x01;MaxNumberInputChar=4;ChangeMass=ePassword;
						ByteShift=0;MaxValue=0;MinValue=0;Discret=1;EntPass=1;
					}
					else
					{
						if (PressPassword==1)
						{
							bInpVal=false;
							if ((bDef)&&((CurrentState[0]==2)||(CurrentState[0]==0x4E))) bInpVal=true;
							if ((cNumComR>0)&&((CurrentState[2]==2)||(CurrentState[2]==1)||(CurrentState[2]==0x4E))) bInpVal=true;
							if ((cNumComT>0)&&((CurrentState[4]==2)||(CurrentState[4]==0x4E))) bInpVal=true;
							if (bInpVal){
								WorkRate=2;SelectValue=1;InputSelectValue=0;MaxValue=1;MinValue=0;/*MaxSelectValue=1;MinSelectValue=0;*/MassSelectValue=Menu1regimeInp;PressPassword=2;
							}else{
								WorkRate=2;SelectValue=1;InputSelectValue=0;MinValue=0;/*MinSelectValue=0;*/MassSelectValue=Menu1regimeInp2; PressPassword=2;
								if ((cNumComT>0)||(bDef)) MaxValue=3;//MaxSelectValue=3;
								else MaxValue=2;//MaxSelectValue=2;  //� ��� ��� ���� �������������, ��� � ���������� ��� � ����, ����� ����� � ����2 � ������ � ����1.
							}
							EntPass=0;
						}
						else
						{
							bInpVal=false;
							if ((bDef)&&((CurrentState[0]!=2)&&(CurrentState[0]!=0x4E))) bInpVal=true;
							if ((cNumComR>0)&&((CurrentState[2]!=2)&&(CurrentState[2]!=1)&&(CurrentState[2]!=0x4E))) bInpVal=true;
							if ((cNumComT>0)&&((CurrentState[4]!=2)&&(CurrentState[4]!=0x4E))) bInpVal=true;
							
							if (bInpVal){
								WorkRate=2;SelectValue=2;InputSelectValue=0;MinValue=0;/*MinSelectValue=0;*/MassSelectValue=Menu1regimeInp1;PressPassword=2;
								if ((cNumComT>0)||(bDef)) MaxValue=2;//MaxSelectValue=2;
								else MaxValue=1; //MaxSelectValue=1; //� ��� ��� ���� �������������, ��� � ���������� ��� � ����, ����� ����� � ����2 � ������ � ����1.
							}
							EntPass=0;
						}
					}
				}break;
				
				case LVL_DEF_SETUP:
				{  //���� ���������� � ���� ����������\���������\����
					uint8_t param = sMenuDefParam.punkt[ShiftMenu];
					
					if (CurrentState[0]==0x00)
					{
						switch(param)
						{
							case 0: {WorkRate=2;SelectValue=1;InputSelectValue=0;MassSelectValue=MenuTypeDefendNum;} break;
							case 1: {WorkRate=0x01;MaxNumberInputChar=1;ByteShift=0;InputParameter=7;Discret=1;} break;
							case 2: {WorkRate=0x01;MaxNumberInputChar=2;ByteShift=0;InputParameter=8;Discret=1;} break;
							case 3: {WorkRate=0x01;MaxNumberInputChar=2;ByteShift=0;InputParameter=9;Discret=2;NumberTransCom=NumberCom;} break;
							case 4: {WorkRate=0x01;MaxNumberInputChar=2;ByteShift=0;InputParameter=10;Discret=2;NumberTransCom=NumberCom;} break;
							case 5: {WorkRate=0x01;MaxNumberInputChar=2;ByteShift=0;InputParameter=27;Discret=1;NumberTransCom=NumberCom;} break;  //�����
							case 6: {WorkRate=2;SelectValue=7;InputSelectValue=0;MassSelectValue=MenuAllSynchrTimerNum;} break;
							case 7: {WorkRate=2;SelectValue=8;InputSelectValue=0;MassSelectValue=fmMenuAllFreq;}break;
							case 8: {WorkRate=2;SelectValue=9;InputSelectValue=0;MassSelectValue=fmMenuAllFreq;}break;
						}
						
						MinValue = paramDef[param].min * paramDef[param].div;
						MaxValue = paramDef[param].max * paramDef[param].div;
						Discret = paramDef[param].dis;
					}
				}
				break;
				
				case LVL_PRM_SETUP:
				{  //���� ���������� � ���� ����������\���������\��������
					if (CurrentState[2]==0x00)
					{
						switch(ShiftMenu)
						{
							case 0: {WorkRate=0x01; MaxNumberInputChar=2; ByteShift=0; /*MaxValue=10;MinValue=0;*/ InputParameter=11; Discret=1;} break;
							case 1: {WorkRate=0x01; MaxNumberInputChar=3; ByteShift=0; /*MaxValue=500;MinValue=10;*/ InputParameter=12; Discret=10;} break;
							case 2: {WorkRate=0x01; MaxNumberInputChar=4; ByteShift=0; /*MaxValue=1000;MinValue=0;*/ InputParameter=13; Discret=10; NumberTransCom=NumberCom;} break;
							case 3: {
								WorkRate=0x01;  ByteShift=0; /*MaxValue=9999;MinValue=0;*/ InputParameter=14; Discret=1; NumberTransCom=NumberCom;
								if (cNumLine==2)
									if (cNumComR>4) MaxNumberInputChar=8; else MaxNumberInputChar=4;
								else
									if (cNumPrm==1)
										if (cNumComR1>4) MaxNumberInputChar=8; else MaxNumberInputChar=4;
									else
										if (cNumComR2>4) MaxNumberInputChar=8; else MaxNumberInputChar=4;
							} break;
							case 4: {
								WorkRate=0x01; ByteShift=0; /*MaxValue=9999;MinValue=0;*/ InputParameter=15; Discret=1; NumberTransCom=NumberCom;
								if (cNumLine==2)
									if (cNumComR>4) MaxNumberInputChar=8; else MaxNumberInputChar=4;
								else
									if (cNumPrm==1)
										if (cNumComR1>4) MaxNumberInputChar=8; else MaxNumberInputChar=4;
									else
										if (cNumComR2>4) MaxNumberInputChar=8; else MaxNumberInputChar=4;
							} break;
						}
						
						MinValue = paramPrm[ShiftMenu].min * paramPrm[ShiftMenu].div;
						MaxValue = paramPrm[ShiftMenu].max * paramPrm[ShiftMenu].div;
						Discret = paramPrm[ShiftMenu].dis;
					}
					
				}break;
				case LVL_PRD_SETUP:
				{  //���� ���������� ����������\���������\����������
					if (CurrentState[4]==0x00)
					{
						switch(ShiftMenu)
						{
							case 0: {WorkRate=0x01;MaxNumberInputChar=2;ByteShift=0;/*MaxValue=10;MinValue=0;*/InputParameter=17;Discret=1;} break;
							case 1: {WorkRate=0x01;MaxNumberInputChar=3;ByteShift=0;/*MaxValue=500;MinValue=10;*/InputParameter=18;Discret=10;} break;
							case 2: {WorkRate=0x01; if (cNumComT!=4) MaxNumberInputChar=8; else MaxNumberInputChar=4;ByteShift=0;/*MaxValue=9999;MinValue=0;*/InputParameter=20;Discret=1; NumberTransCom=NumberCom;} break;
							case 3: {WorkRate=0x01; if (cNumComT!=4) MaxNumberInputChar=8; else MaxNumberInputChar=4;ByteShift=0;/*MaxValue=9999;MinValue=0;*/InputParameter=21;Discret=1; NumberTransCom=NumberCom;} break;
						}
						
						MinValue = paramPrd[ShiftMenu].min * paramPrd[ShiftMenu].div;
						MaxValue = paramPrd[ShiftMenu].max * paramPrd[ShiftMenu].div;
						Discret = paramPrd[ShiftMenu].dis;
					}
				}break;
				
				case LVL_GLB_SETUP:
				{ //����/����������/���������/�����
					bInpVal=true; //�������� ��������� ���������
					if ( (bDef) && (CurrentState[0]!=0x00) ) 
						bInpVal=false;
					if ( (cNumComR>0)&&(CurrentState[2]!=0x00) ) 
						bInpVal=false;
					if ( (cNumComT>0)&&(CurrentState[4]!=0x00) ) 
						bInpVal=false;
					
					// ���� ��� ��������� ���������, �� �������� ���� ���������
					if ( (sMenuGlbParam.punkt[ShiftMenu] == 11) || (sMenuGlbParam.punkt[ShiftMenu] == 12) )
						bInpVal = true;
					
					uint8_t param = sMenuGlbParam.punkt[ShiftMenu];
					
					if (bInpVal)
					{
						switch(param)
						{
							case 0:
							{
								WorkRate = 2;
								SelectValue = 3;
								InputSelectValue = 0;
								MassSelectValue = fmTypeUdDev;
							}
							break;		
							case 1: {WorkRate=2;SelectValue=1;InputSelectValue=0;/*MaxSelectValue=1;MinSelectValue=0;*/MassSelectValue=MenuAllSynchrTimerNum;} break;
							case 2: {WorkRate=0x01;MaxNumberInputChar=2;ByteShift=0;InputParameter=0xB6;Discret=1;} break;
							case 3: {WorkRate=2;SelectValue=3;InputSelectValue=0;/*MaxSelectValue=1;MinSelectValue=0;*/MassSelectValue=MenuAllSynchrTimerNum;} break;
							case 4: {WorkRate=0x01;MaxNumberInputChar=3;ByteShift=0;/*MaxValue=255;MinValue=0;*/InputParameter=25;Discret=1;} break;
							case 5: {WorkRate=0x01;MaxNumberInputChar=1;ByteShift=0;/*MaxValue=5;MinValue=0;*/InputParameter=26;Discret=1;} break;
							case 6: {WorkRate=0x01;MaxNumberInputChar=3;ByteShift=0;/*MaxValue=998;MinValue=26;*/InputParameter=28;Discret=1;} break;
							case 7: {WorkRate=0x01;MaxNumberInputChar=1;ByteShift=0;/*MaxValue=3;MinValue=1;*/InputParameter=29;Discret=1;} break;
							case 8: {WorkRate=2;SelectValue=9;InputSelectValue=0;/*MaxSelectValue=1;MinSelectValue=0;*/MassSelectValue=MenuAllSynchrTimerNum;} break;
							case 9: {WorkRate=0x01;MaxNumberInputChar=2;ByteShift=0;/*MaxValue=22;MinValue=0;*/InputParameter=30;Discret=1;NumberTransCom=1;} break; //����� �������������� �� ��
							case 10: {WorkRate=0x01; MaxNumberInputChar=2;ByteShift=0;/*MaxValue=22;MinValue=0;*/InputParameter=30;Discret=1;NumberTransCom=NumberCom+1;} break;
							case 11:	//��������� ����������
							WorkRate = 0x04;
							InputParameter = 1;
							MaxNumberInputChar = 4;
							InputValue[0]='0';InputValue[1]='0';InputValue[2]='.';InputValue[3]='0';
							break;
							case 12:
							WorkRate = 0x04;
							InputParameter = 1 + NumberCom;
							MaxNumberInputChar = 3;
							break;
							case 13:
							{
								WorkRate = 2; 
								SelectValue = 0x39;
								NumberTransCom = 1;
								InputSelectValue = 1;
								MassSelectValue = MenuAllProtocolNum;	
							}
							break;
							case  14:
							{
								WorkRate = 2;
								SelectValue = 0x39;
								NumberTransCom = 2;
								InputSelectValue = 1;
								MassSelectValue = MenuAllParityNum;
							}
							break;
							case 15:
							{
								WorkRate = 1;
								MaxNumberInputChar = 3;
								ByteShift = 0;
								InputParameter = 0x39;
								NumberTransCom = 3;
								Discret = 18;
							}
							break;
							case 16:
							{
								WorkRate = 1;
								MaxNumberInputChar = 3;
								ByteShift = 0;
								InputParameter = 0x39;
								NumberTransCom = 4;
								Discret = 1;
							}
							break;
							case 17:
							{
								WorkRate = 1;
								MaxNumberInputChar = 2;
								ByteShift = 0;
								InputParameter = 0x39;
								NumberTransCom = 5;
								Discret = 18;
							}
							break;
							case 18:
							{
								WorkRate = 2;
								SelectValue = 0x39;
								NumberTransCom = 6;
								InputSelectValue = 1;
								MassSelectValue = MenuAllControlNum;
							}
							break;
							case 19:
							{
								WorkRate = 2;
								SelectValue = 0x33;								
								NumberTransCom = 1;								
								InputSelectValue = 0;							
								MassSelectValue = MenuAllSynchrTimerNum; 
							}
							break;
							case 20:
							{
								WorkRate = 1;
								MaxNumberInputChar = 2;
								ByteShift = 0;
								InputParameter = 0x39;
								NumberTransCom = 1;
								Discret = 1;
							}
							break;
							case 21:
							{
								WorkRate = 2;
								SelectValue = 2;	
								InputSelectValue = 0;
								MassSelectValue = MenuAllSynchrTimerNum;
							}
							break;
						}
						bInpVal=false;
					}
					
					MinValue = paramGlb[param].min * paramGlb[param].div;
					MaxValue = paramGlb[param].max * paramGlb[param].div;
					Discret = paramGlb[param].dis;
					
				}
				break;
				
				case LVL_PROTOCOL: 
				{
					WorkRate=2;SelectValue=2;InputSelectValue=0;MaxValue=1;MinValue=0;/*MaxSelectValue=1;MinSelectValue=0;*/MassSelectValue=Menu18Param;
				}
				break;
				
				case LVL_INFO: 
				{
					if (ShiftMenu == 3)
					{
						WorkRate=2; SelectValue=1; InputSelectValue=0; /*MaxSelectValue=1;MinSelectValue=0;*/ MinValue=0; MaxValue=1; MassSelectValue=fDopParamView;
					}
					else if (ShiftMenu == 4)
					{
						WorkRate=2; SelectValue=2; InputSelectValue=0; /*MaxSelectValue=1;MinSelectValue=0;*/ MinValue=0; MaxValue=1; MassSelectValue=fDopParamValue;
					}
				}
				break;
				
				case LVL_TEST: 
				{
					//� ����� ����� �������� ������� ������ ���� ���� � ���������� (��� ���� ������������ ������ 1 �� ���) � ������ ����
					if (((cNumComT>0)&&(CurrentState[4]<0x04))) break;
					if (((bDef)&&(CurrentState[0]<0x04))) break;
					//� ����2 ������ ������ ��������
					if (((cNumComT>0)&&(CurrentState[4]==0x05))) break;
					if (((bDef)&&(CurrentState[0]==0x05))) break;
					
					WorkRate = 5;
					InputSelectValue = 0;
					MinValue = 0;
					
					uint8_t group = sMenuTest.gr_items[ShiftMenu];
					
					SelectValue = Menu20grName[group - 1].val;
					MassSelectValueRam = Menu20gr;
					if (group == 1)
					{
						MaxValue = sMenuTest.cf_items_max;
						MassItems = sMenuTest.cf_items;
						
					}
					else if (group == 2)
					{
						MaxValue = sMenuTest.def_items_max;
						MassItems = sMenuTest.def_items;
					}
				}
				break;
			}
        }
		break;
        default: { _NOP();};
	}
	PressKey=0xF0;
}

//����� ���������� ��� ���������� ������� ModBus
static void ModBusOpros(void)
{
	if (ModBusBaza.status(0)!=2)
	{
		if (ReadArch==0){ //��������� ���� �� ���������� ������
			PosModBusInfill++;
			if(PosModBusInfill<0x10)
			{ //����� ���������
				switch(PosModBusInfill)
				{
					case 1:
					case 2: {TransDataInf(0x30-1+PosModBusInfill, 0x00);} break;
					case 3:
					case 4:
					case 5:
					case 6:
					case 7: {TransDataInf(0x30 + 2 + PosModBusInfill, 0x00);} break;
					case 8: {TransDataInf(0x3D,0x00);} break;
					case 9: {TransDataInf(0xF1,0x00);} break;
					case 10: {TransDataInf(0x33, 0x00);} break;					// ����� ��������� ����/��������� ��� ���������� ����
					default: PosModBusInfill=0x10;
				}
			}
			if ((PosModBusInfill>=0x10)&&(PosModBusInfill<0x20))				//��������� ��
			{  				
				if (cTypeLine == 1)
				{  																//���� ����� �� ���
					switch(PosModBusInfill){
						case 0x10: {TransDataByte(0x34, 0x00);} break;
						case 0x11:
						case 0x12: {TransDataInf(0x30+PosModBusInfill-7, 0x00);} break;
						default: PosModBusInfill=0x20;
					}
				}
				else 
					PosModBusInfill=0x20;
			}
			
			if ((PosModBusInfill>=0x20)&&(PosModBusInfill<0x30))				//��������� ������
			{  
				if (bDef)
				{
					switch(PosModBusInfill)
					{
						case 0x20:
						case 0x21:
						case 0x22:
						case 0x23:
						case 0x24:
						case 0x25:
						case 0x26:{TransDataInf(0x01+PosModBusInfill-0x20, 0x00);} break;
						case 0x27: {TransDataInf(0xC1,0x00);} break;
						case 0x28: {TransDataInf(0x0A, 0x00);} break; //����� �������� ������������
						default: PosModBusInfill=0x30;
					}
				}
				else PosModBusInfill=0x30;
			}
			
			if (PosModBusInfill>=0x30){  //��������� ��� � ���
				if ( (cNumComR1 == 0) && (PosModBusInfill < 0x36) ) PosModBusInfill=0x40;  //���� ��� ���1
				if ( (cNumComR2 == 0) && (PosModBusInfill == 0x36) ) PosModBusInfill=0x40;  //���� ��� ���2
				if ( (cNumComT == 0) && (PosModBusInfill > 0x3F) ) PosModBusInfill=0x00;  //���� ��� ���
				
				switch(PosModBusInfill){
					case 0x30:
					case 0x31:
					case 0x32:
					case 0x33:
					case 0x34: {TransDataInf(0x11+PosModBusInfill-0x30, 0x00);} break; //��������� ���
					case 0x35: {TransDataInf(0xD1,0x00);} break; //���-�� ������� � ������ ���
					case 0x36:
					case 0x37:
					case 0x38:
					case 0x39:
					case 0x3A: {TransDataInf(0x18+PosModBusInfill-0x36, 0x00);} break;  //��������� ������� ���
					case 0x3B: PosModBusInfill=0x40;
					case 0x40:
					case 0x41:
					case 0x42:
					case 0x43:
					case 0x44: {TransDataInf(0x21+PosModBusInfill-0x40, 0x00);} break;
					case 0x45: {TransDataInf(0xE1,0x00);} break; //��������� ���
					default: PosModBusInfill=0x00;
				}
			}
		}else{
			Tr_buf_data_uart[4]=Lo(NumRecStart);
			Tr_buf_data_uart[5]=Hi(NumRecStart);
			TransDataInf(ComArch,0x02); //��������� �����
		}
	}else{
		ModBusBaza.writeregister(Tr_buf_data_uart);
		TransDataInf(ModBusBaza.trans(1), ModBusBaza.trans(2));
		ModBusBaza.status(1);
	}
}

void FuncTr(void)
{
	if (PCready==0){  //����� � ���
        if(RecivVar==0){
			if (NumberLostLetter<5) NumberLostLetter++; //���� � ��� ������ 5 ���������� �������, �� �������� �������
        }else {NumberLostLetter=0;RecivVar=0;} //����� ����� � ���������� ������� 0 � �������� ���������� ���������� ������
		
        if (bReadVers)
		{ //���� ������ �������� �������
			if (LoopUART == 1)  //���������� �������� ��� � 1���
            {
				//���� ���� ������� ����� �������� ����/����� � ����������, �������� ��� � USP, ����� ������� USP
				if (NewTime==1){
					for (NewTime=0; NewTime<6; NewTime++) Tr_buf_data_uart[4+NewTime]=TrDataTimeMass[NewTime];
					TransDataInf(0xB2,6); //�������� �������� �����/����
					NewTime=0;
				}
				else															//�������� ������ ����/����� ���� �������/����� ��������
				{
					
					if ( (bDef) && (cNumComR == 0) && (cNumComT == 0) )  					//���� ������ ����, ����� ��������� ���������� �����. ��������� ��������� � ��� ������������ ���������� �����
						TransDataInf(0x32,0x00);
					else
					{
						if (LCDtimer < 3) 
							TransDataInf(0x32, 0x00); 							// �������� ������� ������� ����/�����
						else
							if (LCDtimer==3)
							{ 													// ����� ������� � ������ ��������
								if (cTypeLine != 1)								// ��� ������ ������� �� �����	
									FreqNumCom = 1;
								else
								{
									FreqNumCom = (FreqNumCom > 0) ? 0 : 1;
								}
								TransDataInf(0x3A+FreqNumCom,0x00);
							}
							else
								if (LCDtimer==4)  								//����� ������ ������������
									TransDataInf(0x0A, 0x00);
					}
				}
            }
			else if (LoopUART == 2)
			{  //���������� �������� ��� � 0.5 ���
				if (MenuLevel == LVL_JRN_VIEW)
				{  	
					//���� ��������� � �������, ������ ������� ������ ���-�� �������
					TransDataInf(sArchives.curArchive->typeDev + 1, 0);
				}
				else
				{	
					//�������� ������� ������� �������� ���������
					TransDataInf(0x30, 0x00); 
				}
			}
			else if ( (LoopUART == 3) || (LoopUART == 7) )  //���������� �������� ��� � 0.5 ���
            {
				//������� ������ ���������, ���������� �� �����
				if (cNumComR==0){ //��������� �������� ��� �������, � ���� ���������� ���������
					if (DopComTrans==1) DopComTrans=0;
					if (DopComTrans==2) DopComTrans=3;
				}
				if (cNumComT==0){ //��������� �������� ��� �������, � ���� ���������� �����������
					if (DopComTrans==3) DopComTrans=0;
				}
				switch (DopComTrans){
					case 1: {TransDataInf(0x51,0x00);DopComTrans=0;} break; //���� ������ �� ������ ���� ���������
					case 2: {TransDataInf(0x9A,0x00);DopComTrans=3;} break; //����� ��������� ���
					case 3: {TransDataInf(0xAA,0x00);DopComTrans=0;} break; //����� ��������� ���
					default:  TransDataByte(0x34, 0x00); //������ ���������� ��� ���������� ���������
				}
            }
			else if (LoopUART==4)  //���������� �������� ��� � 0.5 ���
            {
				if (TrParam==0)
				{
					switch(MenuLevel)
					{
						case LVL_DEF_VIEW:
						case LVL_DEF_SETUP:	
						{	
							//���������� ���������� �����
							TransDataInf(0x01 + sMenuDefParam.punkt[ShiftMenu],0x00);
						}break;
						
						case LVL_GLB_VIEW:
						case LVL_GLB_SETUP:	 					
						{	
							//���������� ����� ����������
							switch(sMenuGlbParam.punkt[ShiftMenu])
							{                	
								case 0:	//��� ��.��������
								{
									TransDataInf(0x37, 0x00);	
								}
								break;
								case 8:	//�������� ���.�������
								{
									TransDataInf(0x3D,0x00);
								}
								break;
								case 9:
								case 10:	//����� �������������� �� ��
								{
									TransDataInf(0x3C,0x00);
								}
								break;
								case 11:
								case 12:	// ��������� ����/����������
								case 19:	// ���� ���������� ����
								{
									TransDataInf(0x33,0x00);
								}
								break;
								case 13:
								case 14:
								case 15:
								case 16:
								case 17:
								case 18:	// ��������� ����-�
								case 20:	// �������� ����
								{
									TransDataInf(0x39, 0x00);
								}
								break;
								case 21:
									TransDataInf(0x36, 0x00);
								break;
								default:
								{
									TransDataInf(0x34 + sMenuGlbParam.punkt[ShiftMenu], 0x00);
								}
							}
						}break;
						
						case LVL_PRM_VIEW:
						case LVL_PRM_SETUP:
						{
							if ((cNumLine==3)&&(cNumPrm==2))
							{
								if (ShiftMenu < 2) 
									TransDataInf(0x18+ShiftMenu,0x00);
								else if (ShiftMenu == 2) 
									TransDataInf(0x1A,0x00);
								else 
									TransDataInf(0x1B+ShiftMenu-3,0x00);
							}
							else
							{
								if (ShiftMenu<2) 
									TransDataInf(0x11+ShiftMenu,0x00);
								else if (ShiftMenu==2) 
									TransDataInf(0x13,0x00);
								else
									TransDataInf(0x14+ShiftMenu-3,0x00);
							}
						}break;
						
						case LVL_PRD_VIEW:
						case LVL_PRD_SETUP:
						{
							if (ShiftMenu < 2)
								TransDataInf(0x21 + ShiftMenu,0x00);
							else
								TransDataByte(0x24 + ShiftMenu-3,NumberCom);
						}break;
						
						case LVL_INFO: 		
						TransDataInf(0x34,0x00); 	
						break;
						
						case LVL_TEST: 			//������ ���������� � ���� ����	
						TransDataByte(0x3E,0x00);	
						break; 

						case LVL_JRN_VIEW:		// ��������� �������
						{  
							strArchives *ptr = &sArchives;
							
							// ���� ������ �� ������, ������� ������
							if ( (ptr->ovf) || (ptr->oldestEntry != 0) )
							{
								uint16_t adr = 0;
								
								// calculate the address of the desired entry
								if (ptr->ovf)
									adr = ptr->oldestEntry;
								adr += ptr->curEntry;
								
								adr = adr % ptr->curArchive->maxNumEntries;							
								
								Tr_buf_data_uart[5] = adr;
								Tr_buf_data_uart[4] = adr >> 8;
								TransDataInf(ptr->curArchive->typeDev + 2, 0x02);
							}
						}break;
						
						default: 
						TransDataInf(0x31, 0x00); 	//�������� ������ ������ �������� ���������
					}
				}
				else{
					switch(MenuLevel)
					{
						case LVL_REGIME:
						{
							if (TrParam==2)
								if (TrValue>0) {TrValue++;}
							switch(TrValue)
							{
								case 0: TransDataInf(0x70,0x00);break; //�������
								case 1: TransDataInf(0x71,0x00);break;  //������
								case 2: {Tr_buf_data_uart[4]=0x00; Tr_buf_data_uart[5]=0x00; TransDataInf(0x7E,0x02);} break; //���� 1
								case 3: TransDataInf(0x7D,0x00);break;  //���� 2
							}
						}break;
						
						case LVL_DEF_SETUP: {
							if (TrParam == 4) {
								Tr_buf_data_uart[4] = TrValue;
								Tr_buf_data_uart[5] = NumberTransCom;
								TransDataInf(0x84, 2);
							}
							else if (cNumLine != 3) {
								TransDataByte(0x80 + TrParam, TrValue); //���� 2-� �������� ������
							}
							else if ( (TrParam>4) && (TrParam<=6) ) {
  								//���� 3-� �������� �����
								Tr_buf_data_uart[4] = TrValue;
								Tr_buf_data_uart[5] = NumberTransCom;
								TransDataInf(0x80 + TrParam,2);
								NumberTransCom = 0x00;
							}
							else
								TransDataByte(0x80 + TrParam,TrValue);
						}break;
						
						case LVL_PRM_SETUP:
						{
							if ((cNumLine==3)&&(cNumPrm==2)){
								TrParam += 7;
							}
							switch(TrParam)
							{
								case 1:
								case 2:
								case 8:
								case 9: 
								{
									TransDataByte(0x90+TrParam, TrValue); 
								}break;
								case 3:
								case 10:{
									if ((NumberTransCom>0)&&(NumberTransCom<=(cNumComR))){
										Tr_buf_data_uart[4]=NumberTransCom;
										Tr_buf_data_uart[5]=TrValue;
										TransDataInf(0x90+TrParam,2);
										NumberTransCom=0x00;
									}
								}break;
								case 4:
								case 5:
								case 11:
								case 12:{
									if (cNumComR>4)
									{
										if ((NumberTransCom>0)&&(NumberTransCom<=(cNumComR/8))){
											Tr_buf_data_uart[4]=NumberTransCom;
											Tr_buf_data_uart[5]=TrValue;
											TransDataInf(0x90+TrParam,2);
											NumberTransCom=0x00;
										}
									}
									else
									{
										Tr_buf_data_uart[4]=NumberTransCom;
										Tr_buf_data_uart[5]=TrValue;
										TransDataInf(0x90+TrParam,2);
										NumberTransCom=0x00;
									}
								}break;
							}
						}
						break;
						
						case LVL_PRD_SETUP:
						{
							if (TrParam<4) 
							{
								TransDataByte(0xA0+TrParam,TrValue);
							}
							else
								if (cNumComT>4)
								{
									if ((NumberTransCom>0)&&(NumberTransCom<=(cNumComT/8)))
									{
										Tr_buf_data_uart[4]=NumberTransCom;
										Tr_buf_data_uart[5]=TrValue;
										TransDataInf(0xA0+TrParam,2);
										NumberTransCom=0x00;
									}
								}
								else
								{
									Tr_buf_data_uart[4]=NumberTransCom;
									Tr_buf_data_uart[5]=TrValue;
									TransDataInf(0xA0+TrParam,2);
									NumberTransCom=0x00;
								}
						}
						break;
						
						case LVL_GLB_SETUP:
						{
							switch(TrParam)
							{
								case 6:{										//�������
									Tr_buf_data_uart[4]=((char) (TrValueD>>8));
									Tr_buf_data_uart[5]=((char) TrValueD);
									TransDataInf(0xBA,2);
								}
								break;
								
								case 8:{										//������ ��
									Tr_buf_data_uart[4]=NumberTransCom;
									Tr_buf_data_uart[5]=TrValue;
									TransDataInf(0xBC,2);
								}
								break;
								
								case 10:{										//��������� ����/����������
									Tr_buf_data_uart[4]=NumberTransCom;
									Tr_buf_data_uart[5]=TrValueD>>8;
									Tr_buf_data_uart[6]=TrValueD;
									TransDataInf(0xB3,3);
								}
								break;
								
								case 0x33:										// ��������� ����							
								{
									Tr_buf_data_uart[4] = NumberTransCom;
									Tr_buf_data_uart[5] = TrValue;
									TransDataInf(0xB3, 2);
								}
								break;
								
								case 0x39:
								{
									Tr_buf_data_uart[4] = NumberTransCom;
									Tr_buf_data_uart[5] = TrValue;
									TransDataInf(0xB9, 2);
								}
								break;
								
								default:
								TransDataByte(0xB4 + TrParam, TrValue);
							}
						}
						break;
						
						case LVL_TEST:
						{
							Tr_buf_data_uart[4] = TrParam;
							Tr_buf_data_uart[5] = TrValue;
							TransDataInf(0x7E,2);
						}
						break;
						
						case LVL_UPR:
						{ 
							//����� ���������
							TransDataByte(TrValue, TrParam);
						}
						break;
					}
					TrValue=0;
					TrParam=0;
				}
            }
			else if (LoopUART == 5)
			{	
				//����� ���� ��, ���� ������ � ������� ����
				if ( (bDef) && (cNumComR == 0) && (MenuLevel == LVL_START) )
					TransDataInf(0x0A, 0x00);
				else  ModBusOpros();
			}
			else if (LoopUART == 6)
			{	
				//����� ���� ���������� �������� (�������������), ���� ��� �� ��������
				if (sMenuGlbParam.dev == 0xFF)
					TransDataInf(0x37, 0x00);
				else
					ModBusOpros();
			}
			else 
			{
				ModBusOpros();
			}
        }
		else
		{
			TransDataInf(0x3F,0); //���� ������ �������� ��� �� �������
        }
	}//����� ����� � ���
	bUartTrReady1=false;
}

//����� �� ����� ��������������, ��������������, ��������� � ������ ����
static void LCDMenu1(uint8_t NumString, uint8_t Device)
{
	//Device: 1-������, 2 - ���1, 3 - ���, 5 - ���2
	unsigned int tglobal, temp;
	unsigned char i, j;
	unsigned char __flash* Title;
	unsigned char __flash* __flash* MassError;
	unsigned char __flash* __flash* MassStat;
	bool DevAvar, DevWarn;
	
	if (Device==1){
		Title=Menu1Def;
		MassError=Menu1PostErrorT;
		MassStat=Menu1condPOST;
		DevAvar=bDefAvar;
		DevWarn=bDefWarn;
	}else
		if ((Device==2)||(Device==5))
		{  //���������
			if (Device==2){  //�������� 1 � 3-� ��������, ��� ������ �������� � 2-�
				if (cNumLine==2) Title=Menu1Rec;
				else Title=Menu1Rec1;
				MassError=Menu1PrmErrorT;
				MassStat=Menu1condPRM;
				DevAvar=bRec1Avar;
				DevWarn=bRec1Warn;
			}else{  //�������� 2 � 3-� ��������
				Title=Menu1Rec2;
				MassError=Menu1PrmErrorT;
				MassStat=Menu1condPRM;
				DevAvar=bRec2Avar;
				DevWarn=bRec2Warn;
			}
		}else
			if (Device==3){
				Title=Menu1Tran;
				MassError=Menu1PrdErrorT;
				MassStat=Menu1condPRD;
				DevAvar=bTrAvar;
				DevWarn=bTrWarn;
			}
	
	LCDprintf(NumString, 1, Title, 1);
	if (bGlobalAvar)
	{ //����� ������
		tglobal = (GlobalCurrentState[12]<<8) + (GlobalCurrentState[13]);
		for(i=0, temp=1, j = 0; i<16; i++, temp=temp<<1)
		{
			if (tglobal & temp)
				j++;
		}
		j = (j > 1) ? 1 : 0;
		
		if ( (!TimeWink) && (j) )
		{ //����� �������, ��� � �������
			LCDprintf(NumString, 5, Menu1disrepair, 1);
			FuncClearCharLCD(NumString,13,8);
			LCDprintf(NumString, 13, GlobalAvar, 0);
			LCDprintHEX(NumString,15,GlobalCurrentState[12]);
			LCDprintHEX(NumString,17,GlobalCurrentState[13]);
		}
		else
		{
			tglobal = (GlobalCurrentState[12]<<8) + (GlobalCurrentState[13]);
			for(i=0, temp=1; i<16; i++, temp=temp<<1)
			{
				if (tglobal&temp)
				{
					LCDprintf(NumString, 5, Menu1GlobalErrorT[i], 1);
					break;
				}
			}
		}
	}
	else if (DevAvar)
	{  //���� ������ ����������
		tglobal = (GlobalCurrentState[(Device-1)*4]<<8) + GlobalCurrentState[(Device-1)*4 + 1];
		for(i=0, temp=1, j = 0; i<16; i++, temp=temp<<1)
		{
			if (tglobal & temp)
				j++;
		}
		j = (j > 1) ? 1 : 0;
		
		if ( (!TimeWink) && (j) )
		{ //����� �������, ��� � �������
			LCDprintf(NumString, 5, Menu1disrepair, 1);
			FuncClearCharLCD(NumString,13,8);
			LCDprintf(NumString, 13, LocalAvar, 0);
			LCDprintHEX(NumString,15,GlobalCurrentState[(Device-1)*4]);
			LCDprintHEX(NumString,17,GlobalCurrentState[(Device-1)*4 + 1]);
		}
		else
		{
			tglobal = (GlobalCurrentState[(Device-1)*4]<<8) + GlobalCurrentState[(Device-1)*4 + 1];
			for(i=0, temp = 1; i < 16; i++, temp *= 2)
			{
				if (tglobal & temp)
					LCDprintf(NumString, 5, MassError[i], 1);
			}
		}
	}
	else
	{  //���� �������������� ���
		if ((TimeWink)&&((bGlobalWarn)||(DevWarn)))
		{ 
			// �������� ������� ������ ��������������
			// �� ������ ������ ����������� ������ ������� ���� GlobalCurrentState[15]			
			if (bGlobalWarn)
			{ 
				uint8_t num_warn = 0;
				uint8_t cur_warn = 0;
				uint8_t warn = GlobalCurrentState[15];
				
				// ��������� ���-�� ��������������
				// � ����� �������� �� ���
				for(uint8_t i = 1; i > 0; i <<= 1)
				{
					if (i & warn)
						num_warn += 1;
					
					if (num_warn == 0)
						cur_warn += 1;
				}
				
				// ���� ���� ��������������:
				// ���� ������ ���� - ��������� ��� �����������
				// ���� ������ ������ - ��������� ���������� ��� ��������������
				if (num_warn > 0)
				{
					if ( (num_warn == 1) && (Menu1GlobalWarningT[cur_warn] != UnknownErrorT) )
					{
						LCDprintf(NumString, 5, Menu1GlobalWarningT[cur_warn], 1);
					}
					else
					{
						LCDprintf(NumString, 5, Menu1warning,1);
						FuncClearCharLCD(NumString, 13, 8);
						LCDprintf(NumString, 13, GlobalAvar,0);
						LCDprintHEX(NumString, 15, GlobalCurrentState[14]);
						LCDprintHEX(NumString, 17, GlobalCurrentState[15]);
					}
				}
			}
			else
			{//�������������� ����������
				temp = (int) (GlobalCurrentState[2+(Device-1)*4]<<8) + GlobalCurrentState[3+(Device-1)*4];  //��������������
				switch(Device)
				{
					case 1:
					{
						// �������������� ������
						switch(temp)
						{
							case 1:
							LCDprintf(NumString, 5, Menu1PostWarning1, 1);
							break;
							case 2:
							LCDprintf(NumString, 5, Menu1PostWarning2, 1);			
							break;
							case 4:
							LCDprintf(NumString, 5, Menu1PostWarning4, 1);
							break;
							case 8:
							LCDprintf(NumString, 5, Menu1PostWarning8, 1);
							break;
							default:
							temp = 0;
						}
					}
					break;
					case 2:
					case 5:
					{
						//  � ���������� 1-� ��������������
						//	���� ��� �� 1, ������� ��� �� �����
						if (temp == 1)
						{
							if (cTypeLine == 2)
								LCDprintf(NumString, 5, Menu1PrmWarning1o, 1);
							else
								LCDprintf(NumString, 5, Menu1PrmWarning1, 1);
						}
						else 
							temp = 0;
					}
					break;
					default:
					temp = 0;
				}
				
				if (temp == 0)
				{
					// 	���� ��� ��������� ���
					// 	��� �������������� ���������
					// 	������� �� ����� ��� ��������������
					LCDprintf(NumString, 5, Menu1warning, 1);
					FuncClearCharLCD(NumString, 13, 8);
					LCDprintf(NumString, 13, LocalAvar, 0);
					LCDprintHEX(NumString, 15, GlobalCurrentState[(Device - 1) * 4 + 2]);
					LCDprintHEX(NumString, 17, GlobalCurrentState[(Device - 1) * 4 + 3]);
				}
			}
		}
		else
		{  
			//����� �����/������
			
			//� ������� ����������� ����� ������, ������ ��� ���������� �� ������� �������� �� 1
			if (Device == 5) 
				Device = 4;  
			
			// ���� ��� �������� ��� ������, ������� ��������� �� �����
			// ���� �� ��� �� ������� �������� ���, ������� "????"
			if (CurrentState[(Device - 1) * 2] != 0x4E) 
				LCDprintf(NumString, 5, Menu1regime[CurrentState[(Device - 1) * 2]], 1); 
			else 
				LCDprintf(NumString, 5, Menu1Err, 0);  
			
			// ������� ��������� ����������
			// ���� �� ��� �� ������� �������� ���, ������� "????"
			if (CurrentState[(Device - 1) * 2 + 1] != 0x4E) 
				LCDprintf(NumString, 13, MassStat[CurrentState[(Device - 1) * 2 + 1]], 1);
			else 
				LCDprintf(NumString, 13, Menu1Err, 0);  
			
			//����� �� ����� ��������������� �����
			if( (Device == 2) || (Device == 4) )
			{
				//����� ��, ������� ��� ����.�������
				if ( (CurrentState[(Device - 1) * 2 + 1] == 1)	||
					(CurrentState[(Device - 1) * 2 + 1] == 2)	||
						(CurrentState[(Device - 1) * 2 + 1] == 7)	)  
				{
					LCDprintDEC(NumString,19,Dop_byte[Device-1]);
				}
			}
			if(Device == 3)
			{
				//�������� �� ��� �������
				if ( (CurrentState[(Device - 1) * 2 + 1] == 1) 	||
					(CurrentState[(Device - 1) * 2 + 1] == 2)	) 
					LCDprintDEC(NumString,19,Dop_byte[Device-1]);
			}
		}
	}
}

static void LCDwork(void)
{
	static uint8_t PCconn = 0;
	
	if (PCready==0){
		//����� ������� "��� ����� � ���"
		if (NumberLostLetter>4){ //���� ���� �� ������� 5 ������� ������, �� ������� �� ����� ������
			AvarNoUsp=1;  //������� ��� � ��� ������ ��� ����� � USP
			if (LoopUART==1) LCDprintf(1, 1, LCDavarNoUSP, 1);  //������� �� ����� ��������� "��� ����� � USP"
		}
		else
			if ((NumberLostLetter<5)&&(AvarNoUsp==1)){ //���� �� � ��� �������-�� ���� �������� ������� �� USP
				AvarNoUsp=0;  //������ ��� ����� � USP ��������
				LCDtimerNew=1;
				LCDprintf(1, 1, LCDavarNoUSP, 2);  //������� � ������ ��������� "��� ����� � USP"
			}
		
		
		if (bReadVers)		 //���� ������� ������
		{ 
			switch (MenuLevel)
			{
				case LVL_START:
				{ 
					unsigned char i = 2;
					if (bAllDevice)	 	//����� 3-� �������� ������ � ���� ��� 4 ���������
					{ 
						if (ShiftMenu==0) 
							LCDMenu1(i++, 1); 
						LCDMenu1(i++, 2);
						LCDMenu1(i++, 5);
						if (ShiftMenu == 1) 
							LCDMenu1(i, 3);
					}
					else
					{
						if (bDef) 
							LCDMenu1(i++,1);
						
						// � 3-� �������� ��������� ��� ���������. � 2-� ������ 1
						if (cNumLine == 3)
						{ 
							if (cNumComR1 > 0) 
								LCDMenu1(i++, 2);
							if (cNumComR2 > 0) 
								LCDMenu1(i++, 5);
						}
						else if (cNumComR1 > 0) 
							LCDMenu1(i++, 2);
						
						if (cNumComT > 0) 
							LCDMenu1(i, 3);
						
						// ��
						if (cTypeLine == 1)
						{
							if ( (bDef) && (cNumComR == 0) && (cNumComT == 0) )	// ���� � ��� ������ ���� 
							{	
								LCDprintf(3, 1, fAk, 1);
								LCDprintf(3, 4, flAutoContorl1[param4[cAutoControl]], 1);
								if ((FreqNum[7] < '4')      &&
									(FreqNum[7] > '0')      &&
									(cAutoControl)        	&&	
									(CurrentState[0] == 2)	)
								{
									// ������ � ����-� ��� ������/������������� ��������� ����� �� ��
									if ( (TypeUdDev != 3) && (bDefAvar || bGlobalAvar ||  (CurrentState[1] != 1)) )
										FuncClearCharLCD(3, 9, 13);
									else
									{
										if (TimeError)
										{
											LCDprintf(3, 15, Menu11Err, 1);
											FuncClearCharLCD(3, 19, 2);
										}
										else
											LCDprintTimeAK(cAutoControl, TypeUdDev, FreqNum[7] , TimeLCD);
										
									}
								}
								else
									FuncClearCharLCD(3, 9, 13);
								
								if (cNumLine == 2)
									LCDprint(4, 1, Measuring[5], 1);
								else
									if (cNumLine == 3)
									{
										LCDprintChar(4, 1, '1');
										LCDprint(4, 2, Measuring[5], 1);
										LCDprintChar(4, 11, '2');
										LCDprint(4, 12, Measuring[6], 1);
									}
							}
						}
					}
				}break;
				case LVL_MENU:		//������ ������� ����
				{ 
					if (LCD2new==1)
					{ //��������� ���������� �� ������ ����
						for(uint8_t i = ShiftMenu, j = 0; j < MaxDisplayLine; i++, j++)
							LCDprintf(2 + j, 1, Menu2point[i], 1);
						LCD2new=0;
					}
				}break;
				case LVL_DATA_TIME:	//������ ������� ����, ����� ����/�����
				{ 
					if (LCD2new==1)
					{
						LCDprintf(2, 1, Menu31, 1);
						LCDprintf(3, 1, Menu32, 1);
						LCD2new=0;
					}
				}break;
				
				case LVL_JOURNAL:	//����/������
				{  
					if (LCD2new==1)
					{
						for(uint8_t i = 2, j = ShiftMenu; (j < sArchives.numArchives) && (i < 5); i++, j++)
						{
							LCDprintChar(i, 1, j + '1');
							LCDprintChar(i, 2, '.');
							LCDprintf(i, 3, Archive, 1);
							LCDprintf(i, 10, sArchives.listArchives[j]->name,1);
						}
						LCD2new=0;
					}
				}
				break;
				
				case LVL_SETUP: 	//����/����������
				{
					if (LCD2new==1)
					{
						if (WorkRate!=0)  /*�� �� ���*/
						{
							LCDprintf(2, 1, Menu5point[ShiftMenu], 1);
							LCDprintf(3, 1, Menu5point[ShiftMenu+1], 1);
						}
						else
						{
							for(uint8_t i = ShiftMenu, j = ShiftMenu; j < MaxDisplayLine; i++, j++)
							{
								LCDprintf(2 + j, 1, Menu5point[i], 1);
							}
						}
						LCD2new=0;
					}
				}
				break;
				
				case LVL_PARAM_VIEW: //����/�������� ����������
				case LVL_PARAM_SETUP:
				{
					for(uint8_t i = 0, j = ShiftMenu;  i < MaxDisplayLine; i++, j++)
					{
						uint8_t line = 2 + i;
						uint8_t name = sMenuParam.punkt[j];
						LCDprintChar(line, 1, '1' + j);
						LCDprintChar(line, 2, '.');
						LCDprintf(line, 3, Menu6point3[name],1);
					}
					LCD2new=0;
				}
				break;
				
				case LVL_DEF_VIEW:
				case LVL_DEF_SETUP:
				{  //����/��������(����������) ����������/������
					if (LCD2new==1)
					{
						LCDprintf(2, 1, Menu7paramPOST[sMenuDefParam.punkt[ShiftMenu]], 1);
						
						
						if (sMenuDefParam.punkt[ShiftMenu] == 3) {
							if (cTypeLine == 2) {
								if ( (cNumLine == 3) || (sParamOpt.reserv == 1) ) 
									LCDprintChar(2, 19, NumberCom + '0');
							}
						}
							
							// ���������� ��������� ���� ������ ����
//							if (sMenuDefParam.punkt[ShiftMenu] == 4) 
//							{
//								LCDprintChar(2, 19, '.');
//								LCDprintChar(2, 20, NumberCom + '0');
//							}
						
						FuncClearCharLCD(3,1,20);
						LCDprintf(3, 1, MenuValue, 1);
						
						if (ValueVsRange == 0)
						{
							switch(sMenuDefParam.punkt[ShiftMenu])
							{
								case 0:
								LCDprintf(3, 11, MenuTypeDefendNum[MenuTypeDefend], 1);
								break;
								case 1:
								LCDprint(3, 11, MenuTypeLine, 1);
								break;
								case 2:
								LCDprint(3, 11, MenuPossibleTimeNoMan, 1);
								break;
								case 3:
								LCDprint(3, 11, MenuPossibleTimeSignal[NumberCom-1], 1);
								break;
								case 4:
								LCDprint(3, 11, MenuCoveringImpulse[NumberCom - 1], 1);
								break;
								case 5:
								LCDprint(3, 11, MenuVoltageLimit[NumberCom - 1], 1);
								break;
								case 6:
								LCDprintf(3, 11, MenuAllSynchrTimerNum[MenuAKdecrease], 1);
								break;
								case 7:
								LCDprintf(3, 11, fmMenuAllFreq[MenuFreqPRD], 1);
								break;
								case 8:
								LCDprintf(3, 11,  fmMenuAllFreq[MenuFreqPRM], 1);
								break;
							}
						}
						else
						{
							LCDprintf(3, 1, ParamRange, 1);
							LCDprint(3, 11, cViewParam, 1);
						}
						LCD2new=0;
					}
				}
				break;

				case LVL_GLB_VIEW:
				case LVL_GLB_SETUP:
				{  //����/�������� ����������(����������/���������)/�����
					if (LCD2new==1)
					{
						LCDprintf(2, 1, Menu10paramAll[sMenuGlbParam.name[ShiftMenu]], 1);
						FuncClearCharLCD(3,1,20);						
						
						if (ValueVsRange==0)
						{
							LCDprintf(3, 1, MenuValue,1);
							switch(sMenuGlbParam.punkt[ShiftMenu])
							{
								case 0: LCDprintf(3, 11, fmTypeUdDev[TypeUdDev], 1); break;
								case 1: LCDprintf(3, 11, MenuAllSynchrTimerNum[MenuAllSynchrTimer], 1); break;					
								case 2: LCDprint(3, 11, MenuAllUoutNominal, 1); break;					
								case 3: LCDprintf(3, 11, MenuAllSynchrTimerNum[MenuAllKeepComPRD], 1); break;	
								case 4: LCDprint(3, 11, MenuAllLanAddress, 1); break;
								case 5: LCDprint(3, 11, MenuAllTimeRerun, 1); break;
								case 6: LCDprint(3, 11, MenuAllFreq, 1); break;
								case 7: LCDprint(3, 11, MenuAllNumDevice, 1); break;
								case 8: LCDprintf(3, 11, MenuAllSynchrTimerNum[MenuAllControlUout], 1); break;	
								case 9: LCDprint(3, 11, MenuAllCF, 1); break; //����� ��					
								case 10: {
									LCDprint(3, 11, MenuVoltageLimitPRM[NumberCom-1], 1); 
									if (cNumLine == 3)
										LCDprintChar(2, 18, NumberCom + '0');
								} break;					
								case 11:					
								case 12: LCDprint(3, 11, sCorrParam[sMenuGlbParam.punkt[ShiftMenu] + NumberCom - 12].Print, 1); break;  //��������� ���������� � ����
								// ����-�
								case 13: LCDprintf(3, 11, MenuAllProtocolNum[sParamPVZE.protocol], 1); break;
								case 14: LCDprintf(3, 11, MenuAllParityNum[sParamPVZE.parity], 1); break;
								case 15: LCDprint(3, 11, sParamPVZE.proval, 1); break;
								case 16: LCDprint(3, 11, sParamPVZE.porog, 1); break;
								case 17: LCDprint(3, 11, sParamPVZE.noise, 1); break;
								case 18: LCDprintf(3, 11, MenuAllControlNum[sParamPVZE.autocontrol], 1); break;
								case 19: LCDprintf(3, 11, MenuAllSynchrTimerNum[sParamOpt.reserv], 1); break;
								case 20: LCDprint(3, 11, MenuAllLowCF, 1); break;
								case 21: LCDprintf(3, 11, MenuAllSynchrTimerNum[MenuAllKeepComPRM], 1); break;	
							}				
						}
						else
						{
							LCDprintf(3, 1, ParamRange, 1);
							LCDprint(3, 11, cViewParam, 1);				
						}
					}
					LCD2new=0;
				}break;
				case LVL_REGIME:  //����/����������/�����
				{			
					if (LCD2new==1)
					{
						FuncClearCharLCD(2,1,20);
						FuncClearCharLCD(3,1,20);
						if (bAllDevice){
							//����
							LCDprintf(2, 1, Menu1Def, 1);
							if (CurrentState[0]==0x4E) LCDprintf(2, 5, Menu11Err, 1);
							else LCDprintf(2, 5, Menu11var[CurrentState[0]], 1);
							//���1
							LCDprintf(2,11, Menu1Rec1, 1);
							if (CurrentState[2]==0x4E) LCDprintf(2, 15, Menu11Err, 1);
							else LCDprintf(2, 15, Menu11var[CurrentState[2]], 1);
							//���
							LCDprintf(3,1, Menu1Tran, 1);
							if (CurrentState[4]==0x4E) LCDprintf(3, 5, Menu11Err, 1);
							else LCDprintf(3, 5, Menu11var[CurrentState[4]], 1);
							//���2
							LCDprintf(3, 11, Menu1Rec2, 1);
							if (CurrentState[6]==0x4E) LCDprintf(3, 15, Menu11Err, 1);
							else LCDprintf(3, 15, Menu11var[CurrentState[6]], 1);
						}else{
							uint8_t i = 1;  //������������ �����, ��� ���������� ������ ��� ���������� ���������
							if (bDef)
							{
								LCDprintf(2, 2, Menu11d, 1);
								if (CurrentState[0]==0x4E) LCDprintf(3, 2, Menu11Err, 1);
								else LCDprintf(3, 1, Menu11var[CurrentState[0]], 1);
								i+=7;
							}
							if (cNumComR1 > 0)
							{
								if (cNumLine==2) LCDprintf(2, i + 1, Menu11r, 1);
								else LCDprintf(2, i + 1, Menu11r1, 1);
								if (CurrentState[2]==0x4E) LCDprintf(3, i + 1, Menu11Err, 1);
								else LCDprintf(3, i, Menu11var[CurrentState[2]], 1);
								i+=7;
							}
							if (cNumComR2 > 0)
							{
								LCDprintf(2, i + 1, Menu11r2, 1);
								if (CurrentState[6]==0x4E) LCDprintf(3, i + 1, Menu11Err, 1);
								else LCDprintf(3, i, Menu11var[CurrentState[6]], 1);
								i += 7;
							}
							if (cNumComT > 0)
							{
								LCDprintf(2, i + 1, Menu11t, 1);
								if (CurrentState[4] == 0x4E) LCDprintf(3, i + 1, Menu11Err, 1);
								else LCDprintf(3, i, Menu11var[CurrentState[4]], 1);
							}
						}
						LCD2new = 0;
					}
				}
				break;
				case LVL_PRM_VIEW: 
				case LVL_PRM_SETUP:
				{  
					// �������� ����-�� ��������� ���-��
					if (LCD2new == 0)
						return;
					LCD2new = 0;
					
					LCDprintf(2, 1, Menu8paramPRM[ShiftMenu], 1);
					
					unsigned char **tmValuePRMparam, **tmMenuVoltageLimitPRM;
					unsigned char *tmValuePrmTimeOff, *tmValuePrmBlockCom, *tmValuePrmLongCom;
					unsigned char tNumComR;
					
					if ((cNumPrm==1)||(cNumLine==2))
					{ //���� 2-� ��������, ��� 1-�� �������� � 3-� ��������
						tmValuePRMparam=MenuParamPRM;
						tmValuePrmTimeOff=ValuePrmTimeOff;
						if (cNumLine==2) tNumComR=cNumComR;
						else tNumComR=cNumComR1;
						tmValuePrmBlockCom=ValuePrmBlockCom;
						tmValuePrmLongCom=ValuePrmLongCom;
						tmMenuVoltageLimitPRM=MenuVoltageLimitPRM;
					}
					else
					{//���� 2-�� �������� � 3-� ��������
						tmValuePRMparam=MenuParamPRM2;
						tmValuePrmTimeOff=ValuePrmTimeOff2;
						tNumComR=cNumComR2;
						tmValuePrmBlockCom=ValuePrmBlockCom2;
						tmValuePrmLongCom=ValuePrmLongCom2;
						tmMenuVoltageLimitPRM=MenuVoltageLimitPRM_2;
					}
					
					// ����� �������� ���������
					if (ShiftMenu == 2)
					{
						LCDprintDEC1(2, 18, NumberCom);
					}
					else if ( (ShiftMenu == 3) || (ShiftMenu == 4) )
					{
						if (tNumComR <= 8)
						{	
							LCDprintDEC1(2, 15, tNumComR);
							LCDprintDEC(2, 19, 1);
						}
						else
						{
							LCDprintDEC1(2, 15, (NumberCom - 1) * 8 + 8);
							LCDprintDEC(2, 19, (NumberCom - 1) * 8 + 1);
						}	
					}
					
					// ����� ��������/��������� ���������
					FuncClearCharLCD(3,1,20);
					if (ValueVsRange == 0)
					{
						LCDprintf(3, 1, MenuValue,1);
						LCDprint(3, 11, tmValuePRMparam[ShiftMenu], 1);
						
						if (ShiftMenu == 2)
						{
							if (tmValuePrmTimeOff[NumberCom-1] != 255) 
								LCDprintDEC2(3, 11, tmValuePrmTimeOff[NumberCom - 1]);
							else 
								LCDprintf(3, 11, Menu11Err, 1);
							
						}
						else if (ShiftMenu == 3)
						{
							if (tNumComR > 4)
								LCDprintBits(3, 11, tmValuePrmBlockCom[NumberCom - 1]);
							else
								LCDprintTetr(3, 11, (tmValuePrmBlockCom[0] & 0x0F));
							
						}		
						else if (ShiftMenu == 4)
						{
							if (tNumComR > 4)
								LCDprintBits(3, 11, tmValuePrmLongCom[NumberCom-1]);
							else
								LCDprintTetr(3, 11, (tmValuePrmLongCom[0]&0x0F));
						}
					}
					else
					{
						LCDprintf(3, 1,  ParamRange, 1);
						LCDprint(3, 11, cViewParam, 1);
					}
					
				}break;
				case LVL_PRD_VIEW:
				case LVL_PRD_SETUP:  
				{				
					// �������� ����-�� ��������� ���-��
					if (LCD2new == 0)
						return;
					LCD2new = 0;
					
					// ����� �������� ���������
					LCDprintf(2, 1, Menu9paramPRD[ShiftMenu], 1);
					// ������� ��������, ��� ������� ����������
					if ( (ShiftMenu == 2) || (ShiftMenu == 3) )
					{
						if (cNumComT <= 8)
						{	
							LCDprintDEC1(2, 15, cNumComT);
							LCDprintDEC(2, 19, 1);
						}
						else
						{
							LCDprintDEC1(2, 15, (NumberCom - 1) * 8 + 8);
							LCDprintDEC(2, 19, (NumberCom - 1) * 8 + 1);
						}	
					}
					
					FuncClearCharLCD(3,1,20);
					
					// ����� ��������/��������� ���������
					if (ValueVsRange == 0)
					{
						LCDprintf(3, 1, MenuValue, 1);
						LCDprint(3, 11, MenuParamPRD[ShiftMenu], 1);
				
						if (ShiftMenu == 2)
						{
							if (cNumComT < 8)
								LCDprintTetr(3, 11, (ValuePrdBlockCom[0]&0x0F) );
							else
								LCDprintBits(3, 11, ValuePrdBlockCom[NumberCom-1] );
						}
						else if (ShiftMenu == 3)
						{
							if (cNumComT < 8)
								LCDprintTetr(3, 11, (ValuePrdLongCom[0]&0x0F));
							else
								LCDprintBits(3, 11, ValuePrdLongCom[NumberCom-1] );
						}			
					}	
					else
					{
						LCDprintf(3, 1, ParamRange, 1);
						LCDprint(3, 11, cViewParam, 1);
					}
				}
				break;
				
				case LVL_PROTOCOL: 	//���� ���������
				{
					LCDprintf(2, 1, Menu18, 1);
					LCDprintf(3, 1, MenuValue, 1);
					LCDprintf(3, 11, Menu18Param[Protocol], 1);
				} 
				break;
				
				case LVL_INFO: 		//���� ��������
				{
					LCDprintf(2, 1, Menu19Param[ShiftMenu], 1);
					LCDprintf(3, 1, MenuValue, 1);
					if (ShiftMenu<3)
					{
						LCDprintHEX(3,11,(char) (MyInsertion[ShiftMenu]>>8));
						LCDprintHEX(3,14,(char) MyInsertion[ShiftMenu]);
						LCDprintChar(3,13,'.');
					}
					else
					{	
						if (ShiftMenu==3)
						{
							if (bParamView) LCDprintf(3, 11, fDopParamViewTrue, 1);
							else LCDprintf(3, 11, fDopParamViewFalse, 1);
						}
						else
						{
							if (ShiftMenu==4)
							{
								if (bParamValue) LCDprintf(3, 11, fDopParamValueTrue, 1);
								else LCDprintf(3, 11, fDopParamValueFalse, 1);
							}
						}
					}
				}break;
				case LVL_TEST:  	//���� ������
				{ 
					// �������� ��������� ���� ��������� ���������
					// ���� ���� �� ���� �� � �����. ������ �� ����
					bool isTest = true;
					if ( (cNumComR > 0) && (CurrentState[2] < 0x04) ) 
						isTest = false;
					if ( (cNumComT > 0) && (CurrentState[4] < 0x04) ) 
						isTest = true;  
					if ( (bDef) && (CurrentState[0] < 0x04) )       
						isTest = false;   
					
					if (!isTest)
					{
						Menu_Setup();
						break;
					}
					
					// �� ������ �� ��������� ��������� ��������� ����� �������� �����
					char Test=0xFF;
					if (cNumComR > 0) 
						Test = CurrentState[2] - 4;   
					else if (cNumComT > 0) 
						Test = CurrentState[4] - 4;  
					else if (bDef) 
						Test = CurrentState[0] - 4; 
					
					FuncClearCharLCD(2, 1, 20);
					FuncClearCharLCD(3, 1, 20);
					
					// ���� �� ������ ��������
					// � ������ ������ ������� ����� �����
					if (WorkRate == 0) 
					{
						LCDprintf(4, 1, Menu20line4[Test], 1);
						FuncClearCharLCD(4, 7, 13);
					}
					
					// ������� ��������� ������ � ��������������� �� �������
					for(char i = 0; i < sMenuTest.gr_items_max; i++)
					{
						char group = sMenuTest.gr_items[i];
						
						if (group == 1)
						{
							LCDprintf(2, 1, Menu20gr1n, 1);
							LCDprintf(2, 6, Menu20gr[sMenuTest.cf_val].name, 1);
						}
						else if (group == 2)
						{
							LCDprintf(2, 11, Menu20gr2n, 1);
							LCDprintf(2, 16,  Menu20gr[sMenuTest.def_val].name, 1);
						}
					}
					
					// � ����1 ������� �� ����� ������� ��������� ������
					if (Test == 0)
						LCDprintf(3, 1, Menu20grName[sMenuTest.gr_items[ShiftMenu] - 1].name, 1);		
				}
				break;
				
				case LVL_JRN_VIEW:		// logs
				{ 
					if (LCD2new == 0)
						break;
					
					LCD2new = 0;
					
					// clear 2-4 LCD lines
					FuncClearCharLCD(2, 1, 20); 
					FuncClearCharLCD(3, 1, 20); 
					FuncClearCharLCD(4, 1, 20); 
					
					// print log name
					LCDprintf(2, 1, sArchives.curArchive->nameJrn,1); 
					
					// print (current entry / max entries)
					uint16_t max = (sArchives.ovf) ? sArchives.curArchive->maxNumEntries : sArchives.oldestEntry; 
					LCDptinrArchCount(max, sArchives.curEntry + 1);
					
					if (sArchives.refresh)
					{
					
						if ( (sArchives.ovf) || (sArchives.oldestEntry != 0) )
						{
							strArchiveDevice *ptr = sArchives.curArchive;
							
							// print entry time
							LCDprintTime(28, sArchives.hours, sArchives.minutes,
											 sArchives.seconds, sArchives.milliseconds);
							
							// print entry data
							LCDprintData(72, sArchives.day, sArchives.month, sArchives.year);
												
							// print current signals sost: Pusk, Stop, Man, Prm, Prd, PZ
							if (ptr->typeDev == 0xC0)			// def log
							{
								LCDprintf(3, 1, fLogDefLine3, 1);
								
								uint8_t byte = sArchives.bytes[0];
								
								LCDprintChar(3, 2, (byte&0x01) + '0'); 
								
								byte >>= 1;
								LCDprintChar(3, 4, (byte&0x01) + '0');
								
								byte >>= 1;
								LCDprintChar(3, 6, (byte&0x01) + '0');
								
								byte = sArchives.bytes[1];
								LCDprintChar(3, 16, (byte&0x01) + '0');
								
								byte >>= 1;
								LCDprintChar(3, 11, (byte&0x01) + '0');
								
								(byte & 0x03) ?	LCDprintChar(3, 20, '1') : LCDprintChar(3, 20, '0');
							}
							else if (ptr->typeDev == 0xD0)		// prm log
							{
								// counting number entries in current log entry
								uint8_t num = 0;
								for(uint8_t j = 0; j < 4; j++)
								{
									if (sArchives.bytes[j] > 0)
									{
										for(uint8_t i = 1; i > 0; i <<= 1)
										{
											if (sArchives.bytes[j] & i)
												num++;
										}
									}
								}
								
								uint8_t pos = 4;
								// print number entries in current log entry
								LCDprintChar(2, pos++, '(');
								pos += LCDprintDEC(2, pos, num);
								LCDprintChar(2, pos, ')');
								
								if (num > 0)
								{
									// check current entry in current log entry
									sArchives.subNum = findNextSubEntry(sArchives.bytes, 4, 0, sArchives.subNum);
										
									// print current entry in current log entry
									if (sArchives.subNum < 32)
									{
										LCDprintf(3, 1, fPrmCom, 1);
										LCDprintDEC(3, 17, sArchives.subNum + 1);
									}
								}
								else
									LCDprintf(3, 1, fNoCom, 1);
							}
							else if (ptr->typeDev == 0xE0)		// prd log
							{
								// counting number entries in current log entry
								uint8_t num = 0;
								for(uint8_t j = 0; j < 4; j++)
								{
									if (sArchives.bytes[j] > 0)
									{
										for(uint8_t i = 1; i > 0; i <<= 1)
										{
											if (sArchives.bytes[j] & i)
												num++;
										}
									}
								}
								
								uint8_t pos = 4;
								// print number entries in current log entry
								LCDprintChar(2, pos++, '(');
								pos += LCDprintDEC(2, pos, num);
								LCDprintChar(2, pos, ')');
								
								if (num > 0)
								{	
									// check current entry in current log entry
									sArchives.subNum = findNextSubEntry(sArchives.bytes, 4, 0, sArchives.subNum);
														
									// print current entry in current log entry
									if (sArchives.subNum < 32)
									{
										LCDprintf(3, 1, fPrdCom, 1);
										LCDprintDEC(3, 16, sArchives.subNum + 1);
									}
								}
								else
									LCDprintf(3, 1, fNoCom, 1);
							}
							else if (ptr->typeDev == 0xF0)		// event log
							{
								// print regime
								if ( sArchives.regime < (sizeof(Menu1regime) / sizeof(Menu1regime[0])) )
									LCDprintf(3, 1, Menu1regime[sArchives.regime], 1);
								else
									LCDprintf(3, 1, Menu11Err, 1);
								
								// counting number entries in current log entry
								uint8_t num = 0;
								for(uint8_t j = 0; j < 4; j++)
								{
									for(uint8_t i = 1; i > 0; i <<= 1)
									{
										if (sArchives.bytes[j] & i)
											num++;
									}
								}
								
								if (num > 0)
								{
									uint8_t pos = 4;
									
									// check current entry in current log entry
									sArchives.subNum = findNextSubEntry(sArchives.bytes, 4, 0, sArchives.subNum);
									
									// print number entries in current log entry
									LCDprintChar(2, pos++, '(');
									pos += LCDprintDEC(2, pos, num);
									LCDprintChar(2, pos, ')');
									
									// print current entry in current log entry
									if (sArchives.subNum < 32)
										LCDprintf(3, 9, fEventLog[sArchives.subNum], 1);
								}
							}						
						}
					}
					
					LCD2new=0;
				}
				break;
				
				case LVL_UPR:		//����/����������
				{ 
					if (WorkRate==0)
					{ 
						
						//���� ����� ������
						if (ShiftMenu > MaxShiftMenu) 
							ShiftMenu = MaxShiftMenu;
						
						// ��������� ���-�� ������������ �����
						uint8_t num = sMenuUpr.num;
						if (num > 3)
							num = 3;
						
						MenuUprCreate(0);	// ��������� ������� �������� ��� ����� �����������
						
						for (uint8_t i = 0; i < num; i++)
						{
							LCDprintChar(2 + i, 1, i + ShiftMenu + '0');
							LCDprintf(2 + i, 2, Menu22upr[sMenuUpr.name[i + ShiftMenu]], 1);
						}
					}
					else
					{
						LCDprintChar(2, 1, ShiftMenu + '0');
						LCDprintf(2, 2, Menu22upr[sMenuUpr.name[ShiftMenu]], 1);
						FuncClearCharLCD(3,1,20);
					}
					LCD2new=0;
				}break;
			}
			
			//��������� ������ �������� ���������� ����/�����  � ���������� ����������
			//���� �� ������ ������ ���� ������, �� ������� ����� ������
			if ((AvarNoUsp==1)&&(LoopUART==5)) 
			{
				LCDtimerNew=1; 
				LCDparam=1; 
				LCDprintf(1, 1, LCDavarNoUSP, 2);
			}
			
			if (LCDtimerNew==1)
			{
				if (((AvarNoUsp==1)&&(LoopUART==5))||(AvarNoUsp==0))
				{
					FuncClearCharLCD(1, 9, 2);
					if (cTypeLine == 1)
					{
						if (MenuLevel != LVL_DATA_TIME)
						{
							if (LCDtimer == 1) 
								LCDprint(1, 1, DataLCD, 0);
							else if (LCDtimer == 2) 
								LCDprint(1, 1, TimeLCD, 0);
							else if (LCDtimer == 3) 
								LCDprint(1, 1, FreqNum, 1);
							else if (LCDtimer == 4)
								LCDprintf(1, 1, flAutoContorl[param4[cAutoControl]], 1);//������� ����� ������������	  
						} 
						else 
						{
							LCDprint(1, 1, DataLCD, 0);
							LCDprint(1, 13, TimeLCD, 0);
							FuncClearCharLCD(1,11,2);
						}
					}
					else 
					{
						LCDprint(1, 1, DataLCD, 0); 
						LCDprint(1, 13, TimeLCD, 0);
					}
					LCDtimerNew=0;
				}
			}
			
			if (cTypeLine == 1)
			{
				//������� �� ����� ���������� ��������
				if ( (LCDparam==1)&&(PCready==0) )
				{
					if ( (eNumberAskMeasuring[0] == 0) || (eNumberAskMeasuring[0] > 10) ) 
						eNumberAskMeasuring[0] = 1;
					NumberAskMeasuring=eNumberAskMeasuring[0];
					if (((AvarNoUsp==1)&&(LoopUART==5))||(AvarNoUsp==0))
						if (MenuLevel != LVL_DATA_TIME) 
						{
							FuncClearCharLCD(1,11,2);
							while(!bViewParam[NumberAskMeasuring-1])
							{ //�������� �� ������ ����������� ���-��
								NumberAskMeasuring++;
								if (NumberAskMeasuring > 10) 
									NumberAskMeasuring=1;
							}
							if ((!bParamValue)&&((NumberAskMeasuring==1)||(NumberAskMeasuring==9)||(NumberAskMeasuring==10)))
							{
								if (NumberAskMeasuring == 1) 
									LCDprint(1, 13, Iline1H, 1);
								else if (NumberAskMeasuring == 9) 
									LCDprint(1, 13, KovH, 1);
								else if (NumberAskMeasuring == 10) 
									LCDprint(1, 13, PkH, 1);
							}
							else 
								LCDprint(1, 13, Measuring[NumberAskMeasuring-1], 1);
							
							if (cNumLine==3)
							{ //���� ����-�������� �����, �� ������� 1 ��� 2 ����� U�/U�
								//   if ((NumberAskMeasuring==4)||(NumberAskMeasuring==5)){  //1 ����� U�
								//     LCDprintChar(1,12, NumberAskMeasuring-3 + 0x30);
								//  }else
								if ((NumberAskMeasuring==6)||(NumberAskMeasuring==7))
								{  //1 ����� U�
									LCDprintChar(1,12, NumberAskMeasuring-5 + 0x30);
								}
							}
							
						}
					LCDparam=0;
				}
			}
		}else
			if (((AvarNoUsp==1)&&(LoopUART==5))||(AvarNoUsp==0)) 
			{
				FuncClearCharLCD(1, 1, 20);
				LCDprintf(2, 1, fNoReadVers, 1);
				PCconn++;
				if (PCconn>3) 
					PCconn=1;
				for (uint8_t i = 0; i < PCconn; i++) 
					LCDprintf(2, 16 + i, Point, 1);
			}
	}else
	{  
		//����� �� ��������� "����� � ��..."
		if ((LoopUART==0)||(LoopUART==5))
		{
			LCDbufClear();
			LCDprintf(2, 4, PCconnect, 1);
			PCconn++;
			if (PCconn>3) PCconn=1;
			for (uint8_t i = 0; i < PCconn; i++) 
				LCDprintf(2, 15 + i, Point, 1);
		}
	}
	bLCDwork=false;
}


__C_task main(void)
{
	for(unsigned i=30000; i > 1; i--); //��������� ��������, ��� ���� ����� ��������� ����� ����������
	
	StartSetup(); 		//��������� ���������
	ClearPortError(); 	//������� ������ ����
	StartUART();  		//������ ����
	ClearPortError1(); 	//������� ������ ����
	StartUART1();
	LCDbufClear();  	//������� ������������ ������ LCD
	FuncInitLCD();  	//������������� ��-����������
	WatchDogInit();  	//������������� ����������� �������
	TCCR2 = 0x04;
	TCCR1B = 0x05;  
	_SEI(); //��������� ���� ���������� ����������
	
	// ��������� ������ �� EEPROM �� ����
	eRead = 1;
	eAddressRead = 0;
	eMassiveRead = ePassword;
	while(eRead);
	
	// ��������� ��������� �� ����� ���-�� �� EEPROM �� ����
	eRead = 1;
	eAddressRead = 5;
	eMassiveRead = eNumberAskMeasuring;
	while(eRead);
	
	// ��������� ������� �������� �� EEPROM �� ����
	eRead = 1;
	eAddressRead = 7;
	eMassiveRead = eProtocol;
	while(eRead);
	
	// � ������ ���� EEPROM, ����� ������������ �����������
	Protocol = (eProtocol[0] < 2) ? eProtocol[0] : 0; 
	
	while(1)
	{
		if (bUartRcReady1) 
			DataModBus(cNumRecByte);

#if DEB
		LCDprintHEX(1, 19, sParamOpt.reserv);
#endif		
		
		if (bLCDwork) 
			LCDwork();

#if DEB
		LCDprintHEX(1, 19, sParamOpt.reserv);
#endif		
		
		if (bUartTrReady1) 
			FuncTr();
	}
}

#pragma vector=TIMER1_OVF_vect
__interrupt void Timer1ovf(void)
{
	_SEI();
	TCNT1H=0xF9;  //
	TCNT1L=0xF0;  //���� E5 ��������� 0.1� ��� �������� 1024
	
	//������ � ��
	if (PCready == 1) 
	{
		StartTrans(PCbyte);
		PCready = 2;
	}
	else if (PCready==3) 
	{
		StartTrans1(PCbyte);
		PCready = 4;
	}
	
	//���� ������� ����� �� 0, ������ � �� ������ �� ���� �������
	PCtime--;
	if (PCtime==0) 
	{
		if (PCready!=0) 
		{
			PCready = 0; 
			EnableReceive1; 
			FuncClearCharLCD(2,4,14);
		}
		PCtime=PC_wait;
	}
	
	LoopUART++; //������� ��� ������ ��� 100��
	//������ 1�
	if (LoopUART >= LoopUARTtime)
	{
		// ��� � ������� �� �������� ������ ������ �������� ��������� � MenuLevel = LVL_START,  ������ ��������� ��� ���������� ��� ��������
		LoopUART = 0; //�������� ���� 1� �������
		if (TimeInitLCD >= ConstTimeInitLCD) 
		{
			//������������� ��-����������
			FuncInitLCD();
			TimeInitLCD=0;
		}  
		else 
			TimeInitLCD++;
	}
	
	// ��������� ���� ���������� �������� ������� � ���	
	bUartTrReady1 = true;
	
	//��� ������� ������ 0.1�
	//������ �������, ���� �� ��� �������� ���������� �� ������ LCD
	bLCDwork = true;
	
	// ��������� ���������� ������� �������, �������� ��� � 0.3�
	if (bReadVers)
	{
		if ( ((LoopUART == 0) || (LoopUART == 3) || (LoopUART == 6)) &&
			 (PCready == 0))
		{
			switch(WorkRate)
			{
				case 0: 				// ��������� ������� ������ � ����
				FuncPressKey();
				break;
				
				case 1: 				// ��������� ������� ������ ��� ����� 
				FuncInputData();		// ��������
				break;
				
				case 2: 				// ��������� ������� ������ ��� ������ 
				FuncSelectValue();		// �������� �� ������
				break;
				
				case 3: 				// ���� ����/�������
				FuncInputDataTime();
				break;
				
				case 4: 				// ���� ��������� ����/����������
				FuncInpCorrParam();
				break;
				
				case 5:					// ��������� ������� ������ ��� ������ 				
				FuncSelectValueList();	// �������� �� ������� ��� <-> ��������		
				break;
			}
		}
	}
	
	//��� ������� ��������, �������������/��������������
	if (LoopUART == 5) 
		TimeWink = !TimeWink;
}


