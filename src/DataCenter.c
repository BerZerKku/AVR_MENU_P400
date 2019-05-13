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
extern unsigned char maxLCDtimer; //������������ ���-�� ����� ��������� LCDtimer

//��������� �����
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
//��������� ���-��
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
//��������� ���-��
extern unsigned char MenuPrdTimeOn[];
extern unsigned char MenuPrdTimeCom[];
extern unsigned char MenuPrdTimeRep[];
extern unsigned char MenuPrdBlockCom[];
extern unsigned char MenuPrdLongCom[];
extern unsigned char ValuePrdBlockCom[];
extern unsigned char ValuePrdLongCom[];
extern __flash uint16_t RangPrd[] [3];
//��������� �����
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
///// ����-�
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

//�����
extern unsigned int NumberRecording;
extern unsigned char NumberRec;
extern unsigned char ReadArch;
extern unsigned char NumberRegister;
extern unsigned char StRegister;
extern strArchive sArchive;

//�����
extern unsigned char gr1, gr2, gr21, gr22;


//���������� �������� ������������� ���� � �������
unsigned char TrDataTimeMass[]={0x30,0x30,0x30,0x30,0x30,0x30};
unsigned char DataError=9;
unsigned char TimeError=9;
unsigned int Pk_temp=0;

unsigned char TempMass[10];

//��� ������ ������
extern unsigned char cNumComR, cNumComT;
extern unsigned char cNumComR1, cNumComR2;
extern unsigned char cTypeLine;
extern unsigned char cNumLine;
extern bool bDef;
extern bool bReadVers; //true - ������ ���� �������, false - ����� �� ������, ���������� �����
extern bool bViewParam[];
extern bool bAllDevice; //true - ����� 3-� �������� � ��� 4 ����������
//��� ������ ���������� � 0 ����
extern bool bDefAvar, bDefWarn;
extern bool bGlobalAvar, bGlobalWarn;
extern bool bRec1Avar, bRec1Warn;
extern bool bTrAvar, bTrWarn;
extern bool bRec2Avar, bRec2Warn;
extern __flash  unsigned char  Menu61[],Menu62[],Menu63[],Menu64[],Menu62_1[],Menu62_2[];
extern unsigned char LineInMenu6; //���-�� ����� � ���� �������� ����������/ ���������� ���������
extern unsigned __flash char  *mMenu6point[]; //������ ����� ��� ���� �������� ����������/ ���������� ���������
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

//������� ��������� ��� CRC-16
//�� ����� ��������� �� ������ ������
//� ���������� ���� ��������� (��� ��������� ���� CRC-16)
//�� ��� ���� ����������� �� ���������
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

//������������ ���������� ������� ������ ����� ���������� �� UART
void TransDataByte(unsigned char ByteCommand, unsigned char ByteData)
{
	Sost|=CurSost;
    //����� ������������� ��� ����� � �������
	Tr_buf_data_uart[2]=ByteCommand;//��������� ����
	Tr_buf_data_uart[3]=0x01;
	Tr_buf_data_uart[4]=ByteData;
	CRCSum=GetCRCSum(Tr_buf_data_uart,5);
	Tr_buf_data_uart[5]=CRCSum;
	StartTrans(6);
}

void TransDataInf(unsigned char ByteCommand, unsigned char NumberTransByte)
{
	Sost|=CurSost;
    //����� ������������� ��� ����� � �������
	Tr_buf_data_uart[2]=ByteCommand;
	Tr_buf_data_uart[3]=NumberTransByte;
	CRCSum=GetCRCSum(Tr_buf_data_uart,4+NumberTransByte);
	Tr_buf_data_uart[4+NumberTransByte]=CRCSum;
	StartTrans(5+NumberTransByte);
}

//���������� ��������� � �������
void ErrorMessage(char code)
{
	Sost|=CurSost;
    //����� ������������� ��� ����� � �������
	Tr_buf_data_uart[2]=code;
	Tr_buf_data_uart[3]=0x02; //�.�. ���������� ��� ����� ������
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
		{  //������� �������� ���� ������ (����)
			if ((tmp < RangPost[0] [0]) || (tmp > RangPost[0] [1])) 
				MenuTypeDefend = RangPost[0] [1] + 1;
			else 
				MenuTypeDefend = tmp;
		}break;
		case 0x02:
		{ 
			// ������� �������� ���� ����� (����) (���-�� ������)
			// �������� �� ���������� ��������
			// � ������, ���� ��� ����� �� ��������� � ���������
			// �������� ������ ���� � ������ ���������� ��������
			
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
					
					// ������� ������ Uk � �������� ������
					if ((TypeUdDev == TYPE_UD_DEV_PVZUE) && (cNumLine > 3)) {
						// � ����-� � ���-��� ������ ����� 3, ������������
						// ������� U� ������� ������.
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
		{//������� �������� ����������� ������� ��� ����������� (����)
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
		{//������� �������� ���������� �������� � ������� ������ (����)
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
		case 0x05:{//������� �������� ���������� ��������� (����)
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
		{//������� �������� ���������� ������ (����)
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
				
				// ���� ��� ���������� �������� ��� ��� ����
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
		case 0x18:{ //����� ��������� (��������)
			if (command==0x11) TmpMass=MenuPrmTimeOn;
			else TmpMass=MenuPrmTimeOn2;
			
			if ((Rec_buf_data_uart[4]<RangPrm[0] [0])||(Rec_buf_data_uart[4]>RangPrm[0] [1])) {TmpMass[0]='?';TmpMass[1]='?';}
			else{
				TmpMass[0]=Rec_buf_data_uart[4]/10+0x30;
				TmpMass[1]=Rec_buf_data_uart[4]%10+0x30;
			}
		}break;
		case 0x12:
		case 0x19:{ //������������ ������� (��������)
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
		case 0x1A:{ //�������� �� ���������� (��������)
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
		case 0x1B: { //���������� ������ �� ������
			if (command==0x14) TmpMass=ValuePrmBlockCom;
			else TmpMass=ValuePrmBlockCom2;
			
			for(uint8_t i = 0; i < Rec_buf_data_uart[3]; i++) { 
				TmpMass[i] = Rec_buf_data_uart[4 + i];
			}
		}break;
		case 0x15:
		case 0x1C:{ //���������� �������
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
		{ //����� ��������� (����������)
			if (Rec_buf_data_uart[4]>RangPrd[0] [1]){
				MenuPrdTimeOn[0]='?';MenuPrdTimeOn[1]='?';
			}else{
				MenuPrdTimeOn[0]=Rec_buf_data_uart[4]/10+0x30;
				MenuPrdTimeOn[1]=Rec_buf_data_uart[4]%10+0x30;
			}
		}break;
		case 0x22:{//������������ ������� (����������)
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
		case 0x23:{ //����� �� ��������� ������������ ������� (����������)
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
		case 0x24:{//���������� ������ (����������)
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


/**	������� �������� ���������
 *	@param ���
 *	@return ���
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
	{ //������� �������� ��������� ��������� � ��������� �������� � ������
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

/**	������� ����� ��������������/��������������
 *	@param ���
 *	@return ���
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
#if DEB // ��������� ��������������/�������������
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
	
	// � ������ �400 ����-� ������������ ���.���� � �������� �������� , ���������� ������
	// 0 ��� - 1 �������
	// 1 ��� - 2 �������
	// 2 ��� - 3 �������
	// ...
	// 8 ��� - 8 �������
	uint8_t mask = 0;
	for(uint8_t i = 0; i < cNumLine; i++) {
		mask |= (1 << i);
	}
	NumDevError = GlobalCurrentState[4] & mask;
	
	// �������������� �������� ������������ � ������������� ��� � ������������� ����
	getNumDfzError(GlobalCurrentState[5]);
	
	
	bRec1Avar = (GlobalCurrentState[4] != 0) || (GlobalCurrentState[5] != 0) ? true : false;
	bRec1Warn = (GlobalCurrentState[6] != 0) || (GlobalCurrentState[7] != 0) ? true : false;
	
	bTrAvar = (GlobalCurrentState[8] != 0) || (GlobalCurrentState[9] != 0) ? true : false;
	bTrWarn = (GlobalCurrentState[10] != 0) || (GlobalCurrentState[11] != 0) ? true :false;
	
	bRec2Avar = (GlobalCurrentState[16] != 0) || (GlobalCurrentState[17]!=0) ? true : false;
	bRec2Warn = (GlobalCurrentState[18] != 0) || (GlobalCurrentState[19]!=0) ? true : false;
	
	RecivVar=1;
}

// ���������� ���������� ��� ������ �������� ��� ������������� ��� � ������������� � ����
// �������� �������� 0.255, ��������� ������ ������ ���-�� ���� (�� ����� 1).
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
	DataLCD[7] = (Rec_buf_data_uart[4]&0x0F)+0x30; //1-�� ���
	DataLCD[6] = (Rec_buf_data_uart[4]>>4)+0x30;  //10-�� ���
	DataLCD[4] = (Rec_buf_data_uart[5]&0x0F)+0x30;  //1-�� ���
	DataLCD[3] = (Rec_buf_data_uart[5]>>4)+0x30;  //10-� ���
	DataLCD[1] = (Rec_buf_data_uart[6]&0x0F)+0x30;  //1-�� ����
	DataLCD[0] = (Rec_buf_data_uart[6]>>4)+0x30;  //10-� ����
	
	TimeLCD[1] = (Rec_buf_data_uart[7]&0x0F)+0x30; //1-�� ���
	TimeLCD[0] = (Rec_buf_data_uart[7]>>4)+0x30;  //10-�� ���
	TimeLCD[4] = (Rec_buf_data_uart[8]&0x0F)+0x30;  //1-�� ���
	TimeLCD[3] = (Rec_buf_data_uart[8]>>4)+0x30;  //10-� ���
	TimeLCD[7] = (Rec_buf_data_uart[9]&0x0F)+0x30;  //1-�� ���
	TimeLCD[6] = (Rec_buf_data_uart[9]>>4)+0x30;  //10-� ���
	
	//�������� �� ��������������
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
		DataLCD[7]='0'; //1-�� ���
		DataLCD[6]='0';  //10-�� ���
		DataLCD[4]='0';  //1-�� ���
		DataLCD[3]='0';  //10-� ���
		DataLCD[1]='0';  //1-�� ����
		DataLCD[0]='0';  //10-� ����
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
		TimeLCD[1]='0'; //1-�� ���
		TimeLCD[0]='0';  //10-�� ���
		TimeLCD[4]='0';  //1-�� ���
		TimeLCD[3]='0';  //10-� ���
		TimeLCD[7]='0';  //1-�� ���
		TimeLCD[6]='0';  //10-� ���
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
	LCDtimerNew=1; //�������, ��� ���� �������� ����� ����� � ����
};

void fDopCodeToChar(unsigned char *Mass, unsigned char StartAddr, unsigned char Factor, unsigned char Param, unsigned char Value){  //������, ��������� �����, ���������, ��������
	unsigned char i;
	//��������� 1 ��� 2, ������ �������� ���� �� ������
	Factor--;
	
	for(i=StartAddr; i<8; i++) Mass[i]=' ';
	
	if (Value>127){ //�������� �� ������������� �����
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
			Mass[StartAddr]='�';
		}break;
		case 2:{
			Mass[StartAddr]='�';
			Mass[StartAddr+1]='�';
		}break;
	}
}

/** �������������� ������ ����� � ������.
 *
 *	���� ����� ������ ���������, ����� �������� "??".
 *
 *	@param *Mass ��������� �� ������ ������.
 *	@param StartAddr ��������� ������ � ������ ��� ������ �����.
 *  @param Param ��� ���������, ��� ������ �����������.
 *	@arg 1 - "��"
 *	@arg 2 - "%"
 *  @arg 3 - "�"
 *	@arg 4 - " ���"
 *	@param Value ����� �� 0 �� 9999 ������������.
 *	@param Max ������������ �������� ����� (������������).
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
			Mass[StartAddr++]='�';
			Mass[StartAddr]  ='�';
		} break;
		
		case 2: {
			Mass[StartAddr]  ='%';
		} break;
		case 3: {
			Mass[StartAddr]  ='�';
		} break;
		case 4: {
			Mass[StartAddr++]=' ';
			Mass[StartAddr++]='�';
			Mass[StartAddr++]='�';
			Mass[StartAddr++]='�';
		} break;
		case 5: {
			Mass[StartAddr++]=' ';
			Mass[StartAddr++]='�';
			Mass[StartAddr++]='�';
			Mass[StartAddr++]='�';
		} break;
	}
}

/** �������������� HEX ���� � ������.
 *
 *	@param *Mass ��������� �� ������ ������.
 *	@param StartAddr ��������� ������ � ������ ��� ������ �����.
 *	@param Hex ����� �� 0x00 �� 0xFF ������������.
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
	//����������
	temp1=(signed char) Rec_buf_data_uart[4];
	temp2=(signed char) Rec_buf_data_uart[5];
	sCorrParam[0].Corr=0; //�� ��������� ������� ��������� �������
	if ((temp1>99)||(temp1<-99)||(temp2>90)||temp2<-90){  //��� ���������
		sCorrParam[0].Print[0]='?';
		sCorrParam[0].Print[1]='?';
		sCorrParam[0].Print[2]=0x00;
	}else{
		step=0;
		sCorrParam[0].Print[step++]= ((temp1|temp2)&0x80)? '-' : '+'; //���� �����;
		if (temp1<0) temp1=0x100 - temp1;
		if (temp2<0) temp2=0x100 - temp2;
		if (!(temp1|temp2)){  //���� ������� ���������
			sCorrParam[0].Print[0]='0';
			sCorrParam[0].Print[1]=0x00;
		}
		if (temp1>9){
			sCorrParam[0].Print[step++]=(temp1/10) + 0x30;
		}
		sCorrParam[0].Print[step++]=(temp1%10) + 0x30;
		sCorrParam[0].Print[step++]='.';
		sCorrParam[0].Print[step++]=(temp2/10) + 0x30;
		sCorrParam[0].Print[step++]='�';
		sCorrParam[0].Print[step++]=0x00;
		
		sCorrParam[0].Corr=(temp1*10) + (temp2/10);
		if ( sCorrParam[0].Print[0] == '-' )  sCorrParam[0].Corr = 0x10000 - sCorrParam[0].Corr;
	}
	//��� 1 � 2
	for(char i=1; i<3; i++){
		temp3=(signed int) (Rec_buf_data_uart[4+2*i]<<8) + Rec_buf_data_uart[5+2*i];
		sCorrParam[i].Corr=0; //�� ��������� ������� ��������� �������
		if ((temp3>999)||(temp3<-999)){//���� ��������� ��������
			sCorrParam[i].Print[0]='?';
			sCorrParam[i].Print[1]='?';
			sCorrParam[i].Print[2]=0x00;
		}else{
			if (temp3==0){  //���� ������� ���������
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
				sCorrParam[i].Print[step++]='�';
				sCorrParam[i].Print[step++]='�';
				sCorrParam[i].Print[step++]=0x00;
				
			}
		}//end if(temp3>999 <-999)
	}//end for (i<2)
}

extern strParamOpt	sParamOpt;

void vfOptParam(void)
{
	uint8_t tmp;
	// �������� ������
	
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
	{  //������ ��� ���������
		//����������� ����������
		fDopCodeToChar(Iline1,2,2,1,Rec_buf_data_uart[5]);
		HexToViewHex(Iline1H,3,Rec_buf_data_uart[5]);
		HexToViewHex(Iline1H,5,Rec_buf_data_uart[6]);
		//��� ������
		IlineValue = (Rec_buf_data_uart[7] << 8) + Rec_buf_data_uart[8];  //�������� ��� ���������� ���������
		fIntCodeToChar(Iline2,3,1,IlineValue,999);
		//���������� �� �����
		Uline[5]=Rec_buf_data_uart[10] / 10;
		UlineValue=((signed int) Rec_buf_data_uart[9])*10 + Uline[5];  //�������� ��� ���������� ���������
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
		//���������� ������
        udef1 = Rec_buf_data_uart[11];
		fDopCodeToChar(Usigndef1, 3, 1, 2, udef1);        
		if (cNumLine==3) {
            udef2 = Rec_buf_data_uart[12];
			fDopCodeToChar(Usigndef2, 3, 1, 2, udef2);
        }
		
		//���������� �������
		if ( (cAutoControl == 4) && (CurrentState[0] < 4) )
		{   //���� �� ���� � �� ���� �� Uk ������ 0
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
			// � ����-� ����� ���� �� 8 Uk
			fDopCodeToChar(Uinkch2,3,1,2,Rec_buf_data_uart[14]);
			fDopCodeToChar(Uinkch3,3,1,2,Rec_buf_data_uart[19]);
			fDopCodeToChar(Uinkch4,3,1,2,Rec_buf_data_uart[20]);
			fDopCodeToChar(Uinkch5,3,1,2,Rec_buf_data_uart[21]);
			fDopCodeToChar(Uinkch6,3,1,2,Rec_buf_data_uart[22]);
			fDopCodeToChar(Uinkch7,3,1,2,Rec_buf_data_uart[23]);
			fDopCodeToChar(Uinkch8,3,1,2,Rec_buf_data_uart[24]);
		}
		
		
		//������������� ������������� ��������� ���������
		fDopCodeToChar(Kd,3,1,2,Rec_buf_data_uart[15]);
		//����������� ������������ ���
		fIntCodeToChar(Kov,4,2,Rec_buf_data_uart[16],99);
		HexToViewHex(KovH,3,Rec_buf_data_uart[16]);
		// ������������ ��������� �� ����������
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
		case 0x35:{  //������������� ����� (�����)
			if (Rec_buf_data_uart[4]>RangGlb[1] [1]) MenuAllSynchrTimer=0x02;
			else MenuAllSynchrTimer=Rec_buf_data_uart[4];
		}break;
		case 0x36:{ //��������� ���� ������ ��������� (�����)
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
		{ //��� ���������� ��������
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
            //����� �������� � ��������� ���� (�����)
            adrLan = Rec_buf_data_uart[4];
		}break;
		case 0x39:
		{ 	// ������ - "����� �����������"
			// �� - ��������� ����-�
			uint8_t tmp;
			
			if (cTypeLine == 2)
			{
				tmp = Rec_buf_data_uart[4];
				MenuAllTimeRerun[0] = (tmp > RangGlb[5] [1]) ? '0' : tmp + '0';
					
				return;
			}
			
			// � ���� ������������ ������ ��������
			// ��������� � ����-�
			if (TypeUdDev == TYPE_UD_DEV_PVZL)
			{
				//�������� ������ ��
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
				// �������� ������
				tmp = Rec_buf_data_uart[4];
				if ( (tmp < RangGlb[13] [0]) || (tmp > RangGlb[13] [1]) )
					tmp = RangGlb[13] [1] + 1;
				sParamPVZE.protocol = tmp;
				
				// ������� ��������
				tmp = Rec_buf_data_uart[5];
				if ( (tmp < RangGlb[14] [0]) || (tmp > RangGlb[14] [1]) )
					tmp = RangGlb[14] [1] + 1;
				sParamPVZE.parity = tmp;
				
				// ���������� �������
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
				
				// ����� �� ������
				tmp = Rec_buf_data_uart[7];
				sParamPVZE.porog[2] = (tmp % 10) + '0';
				tmp = tmp / 10;
				sParamPVZE.porog[1] = (tmp % 10) + '0';
				sParamPVZE.porog[0] = (tmp / 10) + '0';
				
				// ���������� ������
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
				
				// ��� ������������
				tmp = Rec_buf_data_uart[9];
				if ( (tmp < RangGlb[18] [0]) || (tmp > RangGlb[18] [1]) )
					tmp = RangGlb[18] [1] + 1;
				sParamPVZE.autocontrol = tmp;
				
				// ������ ������� ������ ��
				tmp = Rec_buf_data_uart[10];
				if ( (tmp < RangGlb[21] [0]) || (tmp > RangGlb[21] [1]) ) {
					sParamPVZE.periodAC[0] = '?';
					sParamPVZE.periodAC[1] = '?';
					sParamPVZE.periodAC[1] = '?';
				} else {
					fIntCodeToChar(sParamPVZE.periodAC, 0, 4, tmp, RangGlb[21] [1]);
				}
				
				// ������ ������� ������� ������ ��
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
		case 0x3A:{ //������� (�����)
			Pk_temp = (Rec_buf_data_uart[4]<<8) + Rec_buf_data_uart[5];
			Rec_buf_data_uart[4]=0;
			
			if (Pk_temp<RangGlb[6] [0]) Rec_buf_data_uart[4]=1;
			else
				if (Pk_temp>RangGlb[6] [1]) Rec_buf_data_uart[4]=1;
			
			if (Rec_buf_data_uart[4]){
				MenuAllFreq[0] = '?';MenuAllFreq[1] = '?';MenuAllFreq[2] = '?';MenuAllFreq[3] = ' ';
				MenuAllFreq[4] = '�';MenuAllFreq[5] = '�';MenuAllFreq[6] = '�';
				
				FreqNum[0]='?';FreqNum[1]='?';FreqNum[2]='?';
			}else{
				if (Pk_temp<100){
					MenuAllFreq[0] = Pk_temp/10 + '0';
					MenuAllFreq[1] = Pk_temp%10 + '0';
					MenuAllFreq[2] = ' ';
					MenuAllFreq[3] = '�';
					MenuAllFreq[4] = '�';
					MenuAllFreq[5] = '�';
					MenuAllFreq[6] = ' ';
				} else if (Pk_temp < 1000) {
					MenuAllFreq[0] = Pk_temp/100 + '0'; Pk_temp %= 100;
					MenuAllFreq[1] = Pk_temp/10 + '0';
					MenuAllFreq[2] = Pk_temp%10 + '0';
					MenuAllFreq[3] = ' ';
					MenuAllFreq[4] = '�';
					MenuAllFreq[5] = '�';
					MenuAllFreq[6] = '�';
				} else if (Pk_temp < 10000) {
					MenuAllFreq[0] = Pk_temp/1000 + '0'; Pk_temp %= 1000;
					MenuAllFreq[1] = Pk_temp/100 + '0'; Pk_temp %= 100;
					MenuAllFreq[2] = Pk_temp/10 + '0';
					MenuAllFreq[3] = Pk_temp%10 + '0';
					MenuAllFreq[4] = '�';
					MenuAllFreq[5] = '�';
					MenuAllFreq[6] = '�';
				}
				
				
				
				FreqNum[0]=MenuAllFreq[0];
				FreqNum[1]=MenuAllFreq[1];
				FreqNum[2]=MenuAllFreq[2];
			}//end else if (Rec_buf_data_uart[4])
			LCDtimerNew=1;
		}break;
		case 0x3B:{ //����� �������� (�����)
			
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
		case 0x3C:{ //������ ��
			uint8_t tmp = 0;
			
			//������ �������������� �� ��
			tmp = Rec_buf_data_uart[4];
			if (tmp > RangGlb[9] [1]) {
				MenuAllCF[0] = 0x3F;
				MenuAllCF[1] = 0x3F;
			}
			else {
				MenuAllCF[0] = tmp/10 + '0';
				MenuAllCF[1] = tmp%10 + '0';
			}
			
			//�������� ���������������� �� �� (��1)
			tmp = Rec_buf_data_uart[5];
			if (tmp > RangGlb[10] [1]) {
				MenuVoltageLimitPRM1[0] = 0x3F;
				MenuVoltageLimitPRM1[1] = 0x3F;
			}
			else {
				MenuVoltageLimitPRM1[0] = tmp/10 + '0';
				MenuVoltageLimitPRM1[1] = tmp%10 + '0';
			}
			
			//�������� ���������������� �� ��2
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
			
			//����� ������ �� ��
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
		case 0x3D:{ //�������� ��������� �������
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
	
	//�������� �� ������������ �������� �������, �������� ������ ����
	if ((0x0F - (Rec_buf_data_uart[2]>>4)) == sArchive.Dev[sArchive.CurrDev])  er=true;
	
	if ((Rec_buf_data_uart[2]&0x0F)==0x01){ //���-�� ������� ������
		if (er){  //���� �������� ������� ����� ������
			if (Rec_buf_data_uart[5]) {
				sArchive.RecCount=256;
				sArchive.CurCount=Rec_buf_data_uart[4];
			}else{
				sArchive.RecCount = Rec_buf_data_uart[4];
				sArchive.CurCount = 0;
			}
		}
	}
	
	if ((Rec_buf_data_uart[2]&0x0F)==0x02){ //������ ������
		unsigned char i;
		if(er){ //���� �������� ������� ����� ������
			for(i=0; i<16; i++) sArchive.Data[i]=Rec_buf_data_uart[4+i];
		}else{
			for(i=0; i<16; i++) sArchive.Data[i]=0x00;
		}
	}
}

extern strMenuTest sMenuTest;

/** ����������� �������� � �������� �������
 *	���������� ������ ������������ ������ � ������ �� �����
* 	��������: ��� ������� ���1, ���2, ���10 - ���������� ����� ������ ���1
 * 	@param com ����� ������� (�� ������ ������ �� ������������)
 *	@return ���
 */
void FTest1(unsigned char com)
{
	// 4-�� ����: 0x76543210 ;
	// 	��� 0 - ��1 
	//	��� 1 -	��2
	//	��� 2 - ��3
	//	��� 3 - ��4
	//	��� 4 - ��1
	//	��� 5 - ��2
	// 5-�� ����: 0xhgfedcba ; a- 1���, h- 8���
	// 6-�� ����: 0xhgfedcba ; a- 9���, h- 16���
	// 7-�� ����: 0xhgfedcba ; a- 17���, h- 24���
	// 8-�� ����: 0xhgfedcba ; a- 25���, h- 32���
	uint8_t sign = 0;
	uint8_t tmp = 0;
	
	// ���������� �������� ������� �������� ��
	// ���� �� ��� � ���� ���/���,  �������� ������� �������� ������
	sign = SIGN_OFF;
	tmp = Rec_buf_data_uart[4];
	if (tmp & 0x0F)
	{
		
		if (tmp & 0x01)
			sign = SIGN_CF1;	
		else if (tmp & 0x02)
			sign = SIGN_CF2;
		
		// � ������ ������������ �����
		// �������� ������� ��3 � ��4 
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
		// ������������ ���-�� ������
		signed char num_com = (cNumComR > cNumComT) ? cNumComR : cNumComT;
		// ��������� �� ���� ������ � ���������
		uint8_t *ptr = &Rec_buf_data_uart[5];
		// ����� ������ ������� � ������� ����� ������
		uint8_t cur_sign = SIGN_COM1;
		
		// ��������� ������� ���� ������ �� ������� ������
		// ��� ������ �����������, ��������� �����
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
	
	// ������� ������ ������ 2, ���� ���� ������
	if (bDef)
	{
		tmp = Rec_buf_data_uart[4];
		sign = (tmp & 0x10) ? SIGN_DEF : SIGN_OFF;
		
		sMenuTest.def_val = sign;
	}
	
	RecivVar=1;
	LCD2new=1;
}

/**	����������� ���� ����������
 * 	� ������ ������������� ���������� ��������, ����� ��������� ��������� �� ���������:
 *	���� : ����
 *  ������� : ���
 *	��� ����� ����� : ��
 * 	������������� : ����� - ��� ������ �� �����������
 *  ���-�� ��������� � ����� : 2
 * 	������ ��� ���� �� ������ ������ �� �������������� !!!
 *
 *	@param ���
 *	@return True ���� � �������� ������ ��� ������, ����� false.
 */
bool VersDevice(void)
{
	bool CorrectVers = true;
	//���������� ������������ ������ ����: ������
	sArchive.NumDev=0;  //���������� ���-�� ���������=0:
	sArchive.Dev[0]=0;  //��� ������ � ������ "�������", ������ ������ ���� 0
	
#if ( (DEB) && (!AUT) ) // �������������� ��������� ���� ��������
	#warning �������� �������������� ��������� ���� ��������!!!
	Rec_buf_data_uart[4] = DEF;
	Rec_buf_data_uart[5] = PRM1;
	Rec_buf_data_uart[6] = PRM2;
	Rec_buf_data_uart[7] = PRD;
	Rec_buf_data_uart[8] = LIN;
	Rec_buf_data_uart[9] = TYP;
#endif
	
	// ������� �����	
	if (Rec_buf_data_uart[4]==1)
	{
		bDef = true;
		bViewParam[5] = true; 
		sArchive.Dev[++sArchive.NumDev] = 3; // ����
	}
	else 
	{
		bDef = false; 
		bViewParam[3] = false;
		
		if (Rec_buf_data_uart[4] != 0)
			CorrectVers = false;
	}
	
	 //���-�� ������ �� ���1
	// ������ 4-��
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
	
	// ���-�� ������ �� ���2
	// ������ 4-��
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
	
	// ���-�� ������ �� ���
	// ������ 4-�� 
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
	
	
	// �������� ������������� � ���� �� ���������� ������� �����
	if (Rec_buf_data_uart[14] < TYPE_UD_DEV_MAX)	{ 
		TypeUdDev = (typeUdDev_t) Rec_buf_data_uart[14];
	}
	else
	{
		CorrectVers = false;
		TypeUdDev = TYPE_UD_DEV_AVANT;
	}
	
	// �������� ������� ��� Uk ����� Uk1
	for(uint8_t i = 1; i < 8; i++) {
		bViewParam[5 + i] = false; 
	}
	
	// ���-�� ��������� � �����
	// 2 ��� 3
	// � ���������� �� �����, �������������� ��������� ���������
	if (Rec_buf_data_uart[8] == 2) {
		cNumLine = 2; 
		cNumComR2 = 0;
		cNumComR = cNumComR1;
	} else if (Rec_buf_data_uart[8] == 3) {
		cNumLine = 3; 
		if ( (cNumComR2) || (bDef) )
			bViewParam[6] = true;  //���� ���� �������� �� ������ ����� ��� ������
		if ((bDef)		&&
			(cNumComR1)	&&
			(cNumComR2)	&&
			(cNumComT)	)
		{
			bAllDevice=true;
		}
		
		cNumComR = cNumComR1 + cNumComR2;
		
		// ����� ��� ������� ���������. ��� �������������
		if (cNumComR2 != 0)
			sArchive.Dev[++sArchive.NumDev] = 4;  // ������ ��������
	} else if ((TypeUdDev == TYPE_UD_DEV_PVZUE) && (Rec_buf_data_uart[8] <= 8)) {
			cNumLine = Rec_buf_data_uart[8];
			
			// � ����-� ����� ���� �� 8 Uk
			for(uint8_t i = 1; i < cNumLine; i++) {
				bViewParam[5 + i] = true;
			}
	} else {
			cNumLine = 2; 
			cNumComR2 = 0;
			cNumComR = cNumComR1;
			
			CorrectVers = false;
	}
	
	// ����� ���������
	if (cNumComR != 0) 
		sArchive.Dev[++sArchive.NumDev] = 2; //��������
	
	// ����� �����������
	if (cNumComT != 0) 
		sArchive.Dev[++sArchive.NumDev] = 1; //����������
	
	// ��� �����
	// 1 - ��
	// 2 - ������
	if (Rec_buf_data_uart[9] == 2)
		cTypeLine = 2;
	else
	{
		cTypeLine = 1;
		
		if (Rec_buf_data_uart[9] != 1)
			CorrectVers = false;
	}
	
	// ���-�� ������������ ����������, � ���������� �� ���� �����	
	// ���� = 4, �� ��� �����/����/�������/��
	if (cTypeLine == 1)
    	maxLCDtimer = 4;  		
	else
		maxLCDtimer = 3;
	
	MyInsertion[1] = (Rec_buf_data_uart[10] << 8) + Rec_buf_data_uart[11];  //������ ������ ���
	MyInsertion[2] = (Rec_buf_data_uart[12] << 8) + Rec_buf_data_uart[13];  //������ DSP
	MyInsertion[3] = (Rec_buf_data_uart[19] << 4) & 0x0F00;  
	MyInsertion[3] += Rec_buf_data_uart[19] & 0x0F;	//������ ��� ����
	
	//���������� ���-�� ���������� � ���� ����, ������ 1
	if (cTypeLine == 2)   // ���� ����
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
	
	//���������� ���� �������� ����������/����������� ���������
	LineInMenu6 = 0;
	if (bDef)
		mMenu6point[LineInMenu6++] = Menu61; //����
	if (cNumLine==2)
	{
		if (cNumComR>0)
			mMenu6point[LineInMenu6++] = Menu62;  //���, � 2-� ��������
	}
	else
	{
		if (cNumComR1 > 0)
			mMenu6point[LineInMenu6++] = Menu62_1; //��� 1, � 3-� ��������
		if (cNumComR2 > 0)
			mMenu6point[LineInMenu6++] = Menu62_2; //��� 2, � 3-� ��������
	}
	
	if (cNumComT > 0)
		mMenu6point[LineInMenu6++] = Menu63;  //���
	mMenu6point[LineInMenu6++] = Menu64;  //���
	
	//���������� ���� ����� ����������, �� ���� ��� ��� ������ ��������� ��� ���������� ��������
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

//��������� ��������� ���������
void DataModBus(unsigned char NumberByte) {
	//������� ��������� CRC
	CRCSum = GetCRCSum(Rec_buf_data_uart,NumberByte - 1);
	if (CRCSum != Rec_buf_data_uart[NumberByte - 1]) 
	{
		EnableReceive; 
	}
	else
	{
		//for (i_dc=0; i_dc<NumberByte; i_dc++) UARTLS_txBuf[i_dc]=Rec_buf_data_uart[i_dc];
		//TransDataInf1(UARTLS_txBuf[2], UARTLS_txBuf[3]);
		
#if ( (DEB) && (PK) )	// ��������� ��������� �� ��� �� ��
	#warning �������� ��������� ��������� �� ��� �� ��!!!
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
			// ���� ������ � ��
			for (uint8_t i = 0; i < NumberByte; i++) {
				UARTLS_txBuf[i] = Rec_buf_data_uart[i];
			}
			
            // ��� �������� �� �� ������� ������ ���������, ������� ������ ��
			if (UARTLS_txBuf[2] == 0x3F) {
				uint8_t crc = UARTLS_txBuf[NumberByte - 1];
				uint8_t num = UARTLS_txBuf[3];
				if (num < 19) {
					// ���� � ������� �� ��������������� ����� ��� ������ ��
					// �.�. ���������� ������ ���� ������, ������� ������ ���-��
					for(uint8_t i = num + 4; num < 19; i++, num++) {
						UARTLS_txBuf[i] = 0x00;
					}
					crc += 19 - UARTLS_txBuf[3];
					UARTLS_txBuf[3] = num;
					NumberByte = num + 5;
				} else {
					// ���� ����� ��� ������ �� ���������������, �� ������ ������
					// ����� ��������� ����������� �����.
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
				case 0x00:	// ��������� ������
				FParamDef(Rec_buf_data_uart[2]);
				break;
				
				case 0x10:	// ��������� ���������
				FParamPrm(Rec_buf_data_uart[2]);
				break;
				
				case 0x20:	// ��������� �����������
				FParamPrd(Rec_buf_data_uart[2]);
				break;
				
				case 0x30:	// ���
				{ 
					switch(Rec_buf_data_uart[2])
					{
						case 0x30:  // ������� ������� ���������
						FCurrentState();
						break; 
						
						case 0x31:	//������� ����� ������� ���������
						FGlobalCurrentState(); 
						break;  
						
						case 0x32:	// ������ ������ ����/�����
						FDataTime(); 
						break;  
						
						case 0x33:	// ��������� ����/����������  
						{
							if (cTypeLine == 1)
								FCorrParam();
							else
								vfOptParam();
						} 
						break; 
						
						case 0x34:  // ������ ���������� ���������
						{
							
							if (cTypeLine == 1) 
								FMeasureParam();
						}
						break; 
						
						case 0x3E:  // ������� �������� �����1
						FTest1(Rec_buf_data_uart[4]);
						break; 
						
						case 0x3F:  // ���������� �� ��������
						VersDevice(); 
						break; 
						
						default:	// ����� ���������
						FParamGlobal(Rec_buf_data_uart[2]);
					}
				}
				break;
				default:
				{
					switch(Rec_buf_data_uart[2])
					{
						case 0xC1:	// ���-�� ������� � ������
						case 0xD1:
						case 0xE1:
						case 0xF1: 
						FArchive();
						break;
						
						case 0xC2:	// ������ ������
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
	
	ClearPortError();   	// ����� ������ �������� ��������� ������� ������� ������
} //end DataModBus


