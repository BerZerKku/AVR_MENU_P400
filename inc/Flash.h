#ifndef __MY_FLASH
#define __MY_FLASH

#include "MyDef.h"
#include "Menu.h"

__flash unsigned char fNoIzmI[] = "I1= --- ";
__flash unsigned char fAC_0[] = "����.�� ";
__flash unsigned char fAC_1[] = "����.�� ";
__flash unsigned char fAC_2[] = "����.�� ";
__flash unsigned char fAC_3[] = "���.��  ";
__flash unsigned char fAC_4[] = "����.�� ";
__flash unsigned char fAC_5[] = "����.�� ";
__flash unsigned char fAC_6[] = "�����.��";
__flash unsigned char fAC_7[] = "���� �� ";
__flash unsigned char fAC_8[] = "����.�� ";
__flash unsigned char fAC_9[] = "����.�� ";
__flash unsigned char fAC_10[]= "�����.��";
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
__flash unsigned char fAC1_0[] = "����.";
__flash unsigned char fAC1_1[] = "���� ";
__flash unsigned char fAC1_2[] = "���� ";
__flash unsigned char fAC1_3[] = "���. ";
__flash unsigned char fAC1_4[] = "����.";
__flash unsigned char fAC1_5[] = "����.";
__flash unsigned char fAC1_6[] = "�����";
__flash unsigned char fAC1_7[] = "���� ";
__flash unsigned char fAC1_8[] = "����.";
__flash unsigned char fAC1_9[] = "����.";
__flash unsigned char fAC1_10[]= "�����";
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

__flash unsigned char fSinh_0[] = "����.�� ";
__flash unsigned char fSinh_1[] = "����.�� ";
__flash unsigned char fSinh_2[] = "���.��  ";
__flash unsigned __flash char *flAutoSinch[]={fSinh_0, fSinh_1, fSinh_2};
__flash unsigned char fAk[] = "��-";

__flash unsigned char LCDavarNoUSP[] =	"��� ����� � ���     ";
__flash unsigned char fNoReadVers[] =	"  �������������     ";

__flash unsigned char Menu21[] = "1.������.";
__flash unsigned char Menu22[] = "2.����/�����.";
__flash unsigned char Menu23[] = "3.����������.";
__flash unsigned char Menu24[] = "4.����������.";
__flash unsigned char Menu25[] = "5.�������� �����.";
__flash unsigned char Menu26[] = "6.������������.";
__flash unsigned char Menu27[] = "7.��������.";
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

__flash unsigned char Menu31[] = "1. ����.            ";
__flash unsigned char Menu32[] = "2. �����.           ";

//������
__flash unsigned char Archive[] 	=	"������ ";
__flash unsigned char ArchiveEvent[]=	"�������";
__flash unsigned char ArchiveDef[] 	= 	"������";
__flash unsigned char ArchivePrm[] 	= 	"���������";
__flash unsigned char ArchivePrd[] 	= 	"�����������";
__flash unsigned __flash char *Menu4point[] = 
{
	ArchiveEvent,
	ArchivePrd,
	ArchivePrm,
	ArchiveDef
};
__flash unsigned char Menu21event[] =	"�������.";
__flash unsigned char Menu2xRdArch[] = 	"������ ������.";

__flash unsigned char ArchPrm[] = "��";
__flash unsigned char ArchPrd[] = "��";
__flash unsigned char ArchEvt[] = "��";
__flash unsigned char ArchDef[] = "��";
__flash unsigned __flash char *Menu21e[]={ArchEvt, ArchPrd, ArchPrm, ArchDef};

__flash unsigned char Menu21g[] = "���";

__flash unsigned char ArchEv11[] = "����������";
__flash unsigned char ArchEv12[] = "���.������";
__flash unsigned char ArchEv13[] = "������ �� ";
__flash unsigned char ArchEv14[] = "�����. �� ";
__flash unsigned char ArchEv15[] = "��� �� 5� ";
__flash unsigned char ArchEv16[] = "����.�.  �";
__flash unsigned char ArchEv17[] = "����.�.  �";
__flash unsigned char ArchEv20[] = "����������";
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
__flash unsigned char ArchEvV[]		=	"�����.";
__flash unsigned char ArchEvV1[] 	=	"������� ";
__flash unsigned char ArchEvStart[] =	"������ ";
__flash unsigned char ArchEvEnd[] 	= 	"����� ";
__flash unsigned char ArchEvCom[] 	=	"�������";


__flash unsigned char Menu51[] =	"1.�����.";
__flash unsigned char Menu52[] =	"2.���������.";
__flash unsigned char Menu53[] = 	"3.������.";
__flash unsigned char Menu54[] =	"4.����.";
__flash unsigned __flash char* Menu5point[] = {Menu51, Menu52, Menu53, Menu54};

__flash unsigned char Menu61[] =	"������.";
__flash unsigned char Menu62[] =	"��������.";
__flash unsigned char Menu63[] =	"����������.";
__flash unsigned char Menu64[] =	"�����.";
__flash unsigned char Menu62_1[] =	"�������� 1.";
__flash unsigned char Menu62_2[] =	"�������� 2.";

__flash unsigned __flash char *Menu6point1[] = {Menu61, Menu64}; 				//������ ����
__flash unsigned __flash char *Menu6point2[] = {Menu62, Menu63, Menu64};  		//������ �������
__flash unsigned __flash char *Menu6point3[] = {Menu61, Menu62, Menu63, Menu64};//��� ����

//��������� �����
__flash unsigned char Menu70[] =	"��� ������";
__flash unsigned char Menu71[] =	"��� �����";
__flash unsigned char Menu72[] =	"���. ����� ��� ���.";
__flash unsigned char Menu73[] =	"�������� �� �����   ";
__flash unsigned char Menu74[] =	"���������� ���������";
__flash unsigned char Menu75[] =	"���� �������� ��  ��";
__flash unsigned char Menu76[] =	"�������� ������ ��  ";
__flash unsigned char Menu77[] =	"������� ���";
__flash unsigned char Menu78[] =	"������� ���";
__flash unsigned char Menu79[] = 	"����� ���.������ ���";
__flash unsigned char Menu710[] = 	"����� ���.������ ���";
__flash unsigned char Menu711[] = 	"����� ���";
__flash unsigned char Menu712[] = 	"����� �� ��� �� ����";
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
// ���-�� ���������� �����
#define NumParamDef (sizeof(Menu7paramPOST) / sizeof(Menu7paramPOST[0]))


//��������� ���������
__flash unsigned char Menu81[]= "�������� �� ���.    ";
__flash unsigned char Menu82[]= "������������ �������";
__flash unsigned char Menu83[]= "�������� �� ����.  �";
__flash unsigned char Menu84[]= "����. �������  ?..? ";
__flash unsigned char Menu85[]= "����. �������  ?..? ";
__flash unsigned __flash char *Menu8paramPRM[] =
{
	Menu81, 
	Menu82, 
	Menu83, 
	Menu84, 
	Menu85
};
// ���-�� ���������� ���������
#define NumParamPrm (sizeof(Menu8paramPRM) / sizeof(Menu8paramPRM[0]))

//��������� �����������
__flash unsigned char Menu93[] = "����� �� ����. ���. ";
__flash unsigned char Menu94[] = "����. �������  ?..? ";
__flash unsigned char Menu95[] = "����. �������  ?..? ";
__flash unsigned __flash char *Menu9paramPRD[] =
{
	Menu81, 
	Menu82, 
	Menu93, 
	Menu94, 
	Menu95
};
// ���-�� ���������� �����������
#define NumParamPrd (sizeof(Menu9paramPRD) / sizeof(Menu9paramPRD[0]))

//����� ���������
__flash unsigned char Menu100[] =	"�������������";
__flash unsigned char Menu101[] =	"C������������ �����";
__flash unsigned char Menu102[] =	"U��� �����������";		
__flash unsigned char Menu103[] =	"��������� ���� ���";
__flash unsigned char Menu104[] =	"������� �����";
__flash unsigned char Menu105[] =	"����� �����������";
__flash unsigned char Menu106[] =	"�������";
__flash unsigned char Menu107[]	=	"����� ��������";
__flash unsigned char Menu108[] =	"�������� ���.�������";
__flash unsigned char Menu109[]	=	"����� ������� �� �� ";
__flash unsigned char Menu1010[] =	"���� �������� ��  ��";
__flash unsigned char Menu1011[] =	"��������� ����������";
__flash unsigned char Menu1012[] =	"��������� ����";
__flash unsigned char Menu109_1[]=	"����� ������� �� �� ";	// ����� NumParamGlb
__flash unsigned char Menu1013[] =	"�������� ������";		// ����-�
__flash unsigned char Menu1014[] =	"������� ��������"; 	// ����-�
__flash unsigned char Menu1015[] =	"���������� �������"; 	// ����-� 
__flash unsigned char Menu1016[] =	"����� �� ������";		// ����-�
__flash unsigned char Menu1017[] =	"���������� ������";	// ����-�
__flash unsigned char Menu1018[] =	"��� ������������";		// ����-�
__flash unsigned char Menu1019[] =	"��������������";		// ������
__flash unsigned char Menu1020[] = 	"�������� ������ ��  ";	// ����				
__flash unsigned char Menu1021[] =	"������ ������� ��";	// ����-�
__flash unsigned char Menu1022[] =	"������ ����.����. ��";	// ����-�
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
// ���-�� ����� ����������
// - 1 , �.�. 109_1 - ������ ������� ������
#define NumParamGlb ( (sizeof(Menu10paramAll) / sizeof(Menu10paramAll[0])) - 1)

__flash uchar TypeUdDev0[] = "����� �400";
__flash uchar TypeUdDev1[] = "���-90";
__flash uchar TypeUdDev2[] = "����-80";
__flash uchar TypeUdDev3[] = "����-�";
__flash uchar TypeUdDev4[] = "����";
__flash uchar TypeUdDevX[] = "������";
__flash unsigned __flash char *fmTypeUdDev[] = 
{
	TypeUdDev0, 
	TypeUdDev1, 
	TypeUdDev2, 
	TypeUdDev3,
	TypeUdDev4,
	TypeUdDevX
};
// ���-�� ����� �������������,
// -1, �.�. ��������� � ������ - ������
#define NumTypeUdDev ( (sizeof(fmTypeUdDev) / sizeof(fmTypeUdDev[0])) - 1)

__flash unsigned char Menu11d[]	=	"���";
__flash unsigned char Menu11r[]	=	"���";
__flash unsigned char Menu11r1[]=	"��1";
__flash unsigned char Menu11r2[]=	"��2";
__flash unsigned char Menu11t[]	=	"���";

__flash unsigned char Menu11var1[] = "����� ";
__flash unsigned char Menu11var2[] = "����� ";
__flash unsigned char Menu11var3[] = "������";
__flash unsigned char Menu11var4[] = "����  ";
__flash unsigned char Menu11var5[] = "���� 1";
__flash unsigned char Menu11var6[] = "���� 2";
__flash unsigned char Menu11var7[] = "���� 3";
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

__flash unsigned char TestDelayMline2[] = "   ������ �����     ";
__flash unsigned char TestDelayMline3[] = "  ��������� ? ���   ";

//����/4.��������.
__flash unsigned char Menu18[]			= "��������";
__flash unsigned char Menu18protocol1[]	= "��������";
__flash unsigned char Menu18protocol2[]	= "ModBus";
__flash unsigned __flash char *Menu18Param[] = {Menu18protocol1, Menu18protocol2};

//���� ����������
__flash unsigned char Menu1Def[]	= "���:";
__flash unsigned char Menu1Rec[]	= "���:";
__flash unsigned char Menu1Rec1[]	= "��1:";
__flash unsigned char Menu1Rec2[]	= "��2:";
__flash unsigned char Menu1Tran[]	= "���:";
__flash unsigned char Menu1Err[]	= "????    ";
__flash unsigned char Menu1disrepair[] 	= "������  ";
__flash unsigned char Menu1warning[]	= "������� ";

__flash unsigned char Menu1Disc[]	= "������� ";
__flash unsigned char Menu1Ready[]	= "�����   ";
__flash unsigned char Menu1Work[]	= "������  ";
__flash unsigned char Menu1Talk[]	= "����    ";
__flash unsigned char Menu1Test1[]	= "����1   ";
__flash unsigned char Menu1Test2[]	= "����2   ";
__flash unsigned char Menu1Test3[]	= "����3   ";
__flash unsigned __flash char *Menu1regime[] 	= {Menu1Disc, Menu1Ready, Menu1Work, Menu1Talk, Menu1Test1, Menu1Test2};
__flash unsigned __flash char *Menu1regimeInp[]	= {Menu1Disc, Menu1Work};
__flash unsigned __flash char *Menu1regimeInp1[]= {Menu1Disc, Menu1Test1, Menu1Test2, Menu1Test3};
__flash unsigned __flash char *Menu1regimeInp2[]= {Menu1Disc, Menu1Work, Menu1Test1, Menu1Test2, Menu1Test3};

//��������� �����
__flash unsigned char Menu1post00[]	= "������. ";
__flash unsigned char Menu1post01[]	= "��������";
__flash unsigned char Menu1post02[]	= "����    ";
__flash unsigned char Menu1post03[]	= "������  ";
__flash unsigned char Menu1post04[]	= "������. ";
__flash unsigned char Menu1post05[]	= "�.������";
__flash unsigned char Menu1post06[]	= "��������";
__flash unsigned char Menu1post07[]	= "���.����";
__flash unsigned char Menu1post08[]	= "��.���� ";
__flash unsigned char Menu1post09[]	= "��� ��  ";
__flash unsigned char Menu1post0A[]	= "����    ";
__flash unsigned char Menu1post0B[]	= "����    ";
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

//��������� ���
__flash unsigned char Menu1prm00[]	= "������. ";
__flash unsigned char Menu1prm01[] 	= "��� ��  ";
__flash unsigned char Menu1prm02[]	= "��� ��  ";
__flash unsigned char Menu1prm03[]	= "��� ��  ";
__flash unsigned char Menu1prm04[]	= "������. ";
__flash unsigned char Menu1prm05[]	= "�.������";
__flash unsigned char Menu1prm06[]	= "��������";
__flash unsigned char Menu1prm07[]	= "��� ��  ";
__flash unsigned char Menu1prm08[]	= "?0x08?  ";
__flash unsigned char Menu1prm09[]	= "?0x09?  ";
__flash unsigned char Menu1prm0A[]	= "?0x0A?  ";
__flash unsigned char Menu1prm0B[]	= "����    ";
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

//��������� ���
__flash unsigned char Menu1prd00[]	= "������. ";
__flash unsigned char Menu1prd01[]	= "��� ��  ";
__flash unsigned char Menu1prd02[]	= "��� ��  ";
__flash unsigned char Menu1prd03[]	= "��� ��  ";
__flash unsigned char Menu1prd04[]	= "������. ";
__flash unsigned char Menu1prd05[]	= "�.������";
__flash unsigned char Menu1prd06[]	= "��������";
__flash unsigned char Menu1prd07[]	= "?0x07?  ";
__flash unsigned char Menu1prd08[]	= "?0x08?  ";
__flash unsigned char Menu1prd09[]	= "������. ";
__flash unsigned char Menu1prd0A[]	= "?0x0A?  ";
__flash unsigned char Menu1prd0B[]	= "����    ";
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

__flash unsigned char MenuInputData[]		= "����:";
__flash unsigned char MenuInputOldPassword[]= "������:";
__flash unsigned char MenuInputNewPassword[]= "����� ������:";


__flash unsigned char MenuValue[] = "��������: ";
__flash unsigned char MenuState[] = "��������: ";

__flash unsigned char MenuTypeDefend0[]	= "���-����  ";
__flash unsigned char MenuTypeDefend1[]	= "���-�����1";
__flash unsigned char MenuTypeDefend2[]	= "���-�����2";
__flash unsigned char MenuTypeDefend3[]	= "���-L60   ";
__flash unsigned char MenuTypeDefend4[]	= "��-����   ";
__flash unsigned char MenuTypeDefend5[]	= "��-���-�� ";
__flash unsigned char MenuTypeDefend6[]	= "���-����  ";
__flash unsigned char MenuTypeDefend7[]	= "���-���-��";
__flash unsigned char MenuTypeDefend8[]	= "������    ";
#define MaxNumTypeDefend 7 /*������������ ����� ������� � ������*/
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

__flash unsigned char MenuAllSynchrTimer0[]	= "����.";
__flash unsigned char MenuAllSynchrTimer1[]	= "���.";
__flash unsigned char MenuAllSynchrTimer2[]	= "????";
__flash unsigned __flash char *MenuAllSynchrTimerNum[] =
{
	MenuAllSynchrTimer0, 
	MenuAllSynchrTimer1, 
	MenuAllSynchrTimer2
};

/***********************/
/* ����-�	*/
__flash unsigned char MenuAllProtocol0[] = "????";
__flash unsigned char MenuAllProtocol1[] = "�������";
__flash unsigned char MenuAllProtocol2[] = "���������";
__flash unsigned __flash char *MenuAllProtocolNum[] = 
{
	MenuAllProtocol0, 
	MenuAllProtocol1, 
	MenuAllProtocol2, 
	MenuAllProtocol0
};

__flash unsigned char MenuAllParity0[] = "????";
__flash unsigned char MenuAllParity1[] = "���.";
__flash unsigned char MenuAllParity2[] = "����.";
__flash unsigned __flash char *MenuAllParityNum[] = 
{
	MenuAllParity0, 
	MenuAllParity1, 
	MenuAllParity2, 
	MenuAllParity0
};

__flash unsigned char MenuAllProval[] 	= "??? ����";
__flash unsigned char MenuAllPorog[]	= "??? ���";
__flash unsigned char MenuAllNoise[] 	= "?? ����";

__flash unsigned char MenuAllControl0[] = "????";
__flash unsigned char MenuAllControl1[] = "���������";
__flash unsigned char MenuAllControl2[] = "����������";
__flash unsigned char MenuAllControl3[] = "���������";
__flash unsigned __flash char *MenuAllControlNum[] = 
{
	MenuAllControl0, 
	MenuAllControl1, 
	MenuAllControl2, 
	MenuAllControl3, 
	MenuAllControl0
};

/*************************/
__flash uchar MenuAllFreq0[] = "-1000 ��";
__flash uchar MenuAllFreq1[] = "-500 ��";
__flash uchar MenuAllFreq2[] = "+0 ��";
__flash uchar MenuAllFreq3[] = "+500 ��";
__flash uchar MenuAllFreq4[] = "+1000 ��";
__flash uchar MenuAllFreq5[] = "������";
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

__flash unsigned char ParamRange[] 	= "��������: ";
__flash unsigned char NoData[]		= "��� ������";
__flash unsigned char List[]		= "������";

//	�������� �������� ��� ����� //���� 13
__flash uint RangPost[NumParamDef + 1] [3] = 
{  /* +1  - ��� ������������, ������� ������ ����� ��������� � �����*/
	0,	MaxNumTypeDefend,	1,  /*��� ������*/ /*��� �� �������� ��������, � ��� � ��� ����� �������"*/
	2,	3,		1,  	// ��� �����
	0,	99,		1,  	// ��� ����� ��� �����������
	0,	18,		1,  	// �������� �� �����
	18,	54,		1,  	// ���������� ���������
	0,	22,		1,  	// ����. ������. �� ��
	0,	1,		1,  	// �������� ������ ��
	0,	4,		1,		// ������� ���
	0,	4,		1,		// ������� ���
	0,	72,		1,		// ����� ��������� ������ ���
	0,	72,		1,		// ����� ������� ������ ���
	0,	72,		1,		// ����� ���
	0,	72,		1,		// ����� �� ��� �� ����
	1,	9,		1   	// ������������, ������ � �����  !!! �� ������ ��������� � DataCener � StudyATmega162 (���������� ������� 'C')!!!*/
};

//�������� �������� ��� ���������
__flash uint RangPrm[NumParamPrm] [3] = 
{
	0 , 10,   	1,    	// �������� �� ���������
	1,  50,   	10,   	// ������������ �������
	0,  100,  	10,   	// �������� �� ����������
	0,  255,  	1,    	// ������������� �������
	0,  255,  	1 		// ���������� �������
};  	

//�������� �������� ��� �����������
__flash uint RangPrd[NumParamPrd] [3] = 
{
	0 , 10,   	1,  	// �������� �� ����
	1,  50,  	10,  	// ������������ �������
	1,  50,  	10,  	// ����� �� ����������
	0,  255,  	1,  	// ������������� �������
	0,  255,  	1		// ���������� �������
}; 	

//�������� �������� ��� ����� ����������
__flash uint RangGlb[NumParamGlb] [3] = 
{	
	0,	4,		1,		// 0  ��� ��.��������	
	0,	1,    	1,		// 1  ������������� �����  
	8, 	50,		1,  	// 2  U��� ����������� 
	0,  2,    	1,  	// 3  ��������� ���� ��� 
	0,  255,  	1,  	// 4  ������� ����� 
	0,  5,    	1,  	// 5  ����� �����������  
	16, 1000,  	1,  	// 6  �������  
	1,  3,    	1,  	// 7  ����� ��������  
	0,  1,   	1,  	// 8  �������� ��������� �������  
	0,  22,  	1,  	// 9  ����� �������������� �� ��  
	0,  22,   	1,  	// 10 ����������� ���������������� �� ��  
	0,  999,  	1,  	// 11 ��������� ����������  
	0,  999,	1,  	// 12 ��������� ���� 
	1,	2,		1,		// 13 �������� ������	
	1,	2,		1,		// 14 ������� ��������	
	0,	80,		1,		// 15 ���������� �������	
	0,	255,	1,		// 16 ����� �� ������	
	20,	80,		1,		// 17 ���������� ������	
	1,	3,		1,		// 18 ��� ������������	
	0,	1,		1,		// 19 �������������� (������)
	0,	20, 	1,		// 20 �������� ������ �� (����)
	1, 	255,	1,		// 21 ������ ������� ������ �� (����-�)
	1, 	255,	1		// 22 ������ ������� ������� ������ �� (����-�)	
};		

__flash unsigned char Menu16Shift10[] = "0.0..99.9";

//��������
__flash unsigned char Menu19Shift0[] = "�������� �� MCU  ";
__flash unsigned char Menu19Shift1[] = "�������� ��� MCU ";
__flash unsigned char Menu19Shift2[] = "�������� ��� DSP ";
__flash unsigned char Menu19Shift3[] = "�������� ��� ����";
__flash unsigned char Menu19Shift4[] = "������. ���������"; 
__flash unsigned char Menu19Shift5[] = "��� ���������";		
__flash unsigned __flash char *Menu19Param[] = 
{
	Menu19Shift0, 
	Menu19Shift1, 
	Menu19Shift2, 
	Menu19Shift3,
	Menu19Shift4,
	Menu19Shift5
};

__flash unsigned char fDopParamViewTrue[] 	="����";
__flash unsigned char fDopParamViewFalse[] 	= "���";
__flash unsigned __flash char *fDopParamView[] = {fDopParamViewFalse, fDopParamViewTrue};
__flash unsigned char fDopParamValueTrue[]	= "��������";
__flash unsigned char fDopParamValueFalse[]	= "HEX";
__flash unsigned __flash char *fDopParamValue[] = {fDopParamValueFalse, fDopParamValueTrue};

// ������ ���� ����������
__flash unsigned char Menu22Shift0[]	= ".����� ������.     ";
__flash unsigned char Menu22Shift1[]	= ".����� ����������. ";
__flash unsigned char Menu22Shift2[]	= ".����� ���������� 1";
__flash unsigned char Menu22Shift3[]	= ".����� ���������� 2";
__flash unsigned char Menu22Shift3x[]	= ".����� ���������� 3";
__flash unsigned char Menu22Shift4[]	= ".���� ����������.  ";
__flash unsigned char Menu22Shift5[]	= ".���� ���������� 1 ";
__flash unsigned char Menu22Shift6[]	= ".���� ���������� 2 ";
__flash unsigned char Menu22Shift6x[]	= ".���� ���������� 3 ";
__flash unsigned char Menu22Shift7[]	= ".���� ���������    ";
__flash unsigned char Menu22Shift8[]	= ".�� �������������� ";
__flash unsigned char Menu22Shift9[]	= ".�� ����������     ";
__flash unsigned char Menu22Shift10[]	= ".�� ��������       ";
__flash unsigned char Menu22Shift11[]	= ".�� �����.�������� ";
__flash unsigned char Menu22Shift12[]	= ".�� ���������      ";
__flash unsigned char Menu22Shift13[]	= ".�� ����           ";
__flash unsigned char Menu22Shift14[]	= ".�����             ";
__flash unsigned char Menu22Shift15[]	= ".�� ����������     ";	
__flash unsigned char Menu22Shift16[]	= ".�� ������         ";	
__flash unsigned char Menu22Shift17[]	= ".���� ������. ���  ";	
__flash unsigned char Menu22Shift18[]	= ".�� �������������  ";
__flash unsigned char Menu22Shift19[]	= ".����� ��          ";
__flash unsigned char Menu22Shift20[]	= ".���� �� ����      ";
__flash unsigned char Menu22Shift21[]	= ".���� �� ��������� ";
__flash unsigned char Menu22Shift22[]	= ".���� ���          ";
__flash unsigned char Menu22Shift23[]	= ".���� �����. ���.  ";
__flash unsigned char Menu22Shift24[]	= ".���� �����. ����. ";
__flash unsigned char Menu22Shift25[] 	= ".���� ����. ��� 1  ";
__flash unsigned char Menu22Shift26[] 	= ".���� ����. ��� 2  ";
__flash unsigned char Menu22Shift27[] 	= ".���� ����. ��� 3  ";
__flash unsigned char Menu22Shift28[] 	= ".���� ����-�� ���  ";
// ������ ���� ����������
// ������ ��������� � eMENUctrlName
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

//__flash unsigned char fRes[]	= "�����";
//__flash unsigned char fPusk[]	= "����";
//__flash unsigned char fEnter[]	= "����";
//__flash unsigned char fCall[]	= "�����";
//__flash unsigned char fOn[] 	= "���.";
//__flash unsigned char fOff[]	= "����.";
//__flash unsigned __flash char *fReset[] = {fRes, fPusk, fEnter, fCall, fOn, fOff};
__flash unsigned char fEnter[] = "���������";
__flash unsigned __flash char *fReset[] = {fEnter};


//����������� ������
__flash unsigned char UnknownErrorT[]		= "     Error      ";

//������ ����������
__flash unsigned char Menu1GlobalError1[]	= "������.��. FLASH";
__flash unsigned char Menu1GlobalError2[]   = "������.���.FLASH";
__flash unsigned char Menu1GlobalError4[]   = "������.��. PLIS ";
__flash unsigned char Menu1GlobalError8[]   = "������.���.PLIS ";
__flash unsigned char Menu1GlobalError10[]  = "������.���.2RAM ";
__flash unsigned char Menu1GlobalError20[]  = "��� ������� ��� ";
__flash unsigned char Menu1GlobalError40[]  = "��-������.������";
__flash unsigned char Menu1GlobalError80[] 	= "������ � �����  ";
__flash unsigned char Menu1GlobalError100[] = "������.DSP 2RAM ";
__flash unsigned char Menu1GlobalError200[] = "������.��. 2RAM ";
__flash unsigned char Menu1GlobalError400[] = "��� �����       ";
__flash unsigned char Menu1GlobalError800[] = "������ ����.���.";
__flash unsigned char Menu1GlobalError1000[]= "������� ����.���";
__flash unsigned char Menu1GlobalError2000[]= "������. �� ��   ";
__flash unsigned char Menu1GlobalError4000[]= "�� ����� �����. ";
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
//� ������ ������ ������ "��� ������� ���", ������� ������ ���������
__flash unsigned char Menu1GLobalError20_1[] 	= "��-��� ������   ";

//����� ��������������
__flash unsigned char Menu1GlobalWarning1[] 	= "���������� ���� ";
__flash unsigned char Menu1GlobalWarning2[]		= "����� ������.���";
__flash unsigned char Menu1GlobalWarning10[]	= "����.���� ������";
__flash unsigned char Menu1GlobalWarning20[] 	= "����.��� ������.";
__flash unsigned char Menu1GlobalWarning40[] 	= "����.��� ������.";
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

//������ ������
__flash unsigned char Menu1PostError1[]		= "��� ����� ���   ";
__flash unsigned char Menu1PostError2[]		= "������.����.��� ";
__flash unsigned char Menu1PostError4[]		= "������.������.  ";
__flash unsigned char Menu1PostError8[]		= "������.���. ��� ";
__flash unsigned char Menu1PostError10[]	= "��� ������� ��� ";
__flash unsigned char Menu1PostError20[]	= "������ ��. ��   ";
__flash unsigned char Menu1PostError40[]	= "������.��.���";	// ����-� (+ �����)
__flash unsigned char Menu1PostError80[]	= "������.��.���";	// ����-� (+ �����)
__flash unsigned char Menu1PostError100[]	= "������.����.����";
__flash unsigned char Menu1PostError200[]	= "������.����.����";
__flash unsigned char Menu1PostError400[]	= "����.��� ���.";	// ����-� (+ �����)
__flash unsigned char Menu1PostError800[]	= "������.����.��� ";
__flash unsigned char Menu1PostError1000[]	= "����.���.���.";	// ����-� (+ �����)
__flash unsigned char Menu1PostError2000[]	= "������.���. ��� ";
__flash unsigned char Menu1PostError4000[]	= "����. ������ ";	// ����-�
__flash unsigned char Menu1PostError8000[]	= "������. ���  ";	// ����-�
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
//� ������ ������ ������ "��� ������� ���", ������� ������ ���������// ����-� (+ �����)
__flash unsigned char Menu1PostError10_1[] 	= "��-��� ������";

//�������������� ������
__flash unsigned char Menu1PostWarning1[]	= "��-��.������ ";	// ����-� (+ �����)
__flash unsigned char Menu1PostWarning2[] 	= "��� ������� ��� ";
__flash unsigned char Menu1PostWarning4[] 	= "����� �� ������ ";
__flash unsigned char Menu1PostWarning8[]	= "������������    ";

//������ ���������
__flash unsigned char Menu1PrmError1[]		= "��� ����� ���   ";
__flash unsigned char Menu1PrmError2[]		= "������.����.��� ";
__flash unsigned char Menu1PrmError4[] 		= "��� ��          ";
__flash unsigned char Menu1PrmError8[]		= "����.��-���.���.";
__flash unsigned char Menu1PrmError100[]	= "������.���. ��� ";
__flash unsigned char Menu1PrmError200[]	= "������.����.��� ";
__flash unsigned char Menu1PrmError400[]	= "������.���. ��� ";
__flash unsigned char Menu1PrmError800[]	= "������.�����.���";
__flash unsigned char Menu1PrmError1000[] 	= "�������.��� ��1 ";
__flash unsigned char Menu1PrmError8000[] 	= "����� ����. ���.";
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

//�������������� ���������
__flash unsigned char Menu1PrmWarning1[] = "����. ������ ���";

//������ �����������
__flash unsigned char Menu1PrdError1[]	= "��� ����� ���   ";
__flash unsigned char Menu1PrdError2[]	= "������.����.��� ";
__flash unsigned char Menu1PrdError100[]= "������.��.������";
__flash unsigned char Menu1PrdError200[]= "������.����.����";
__flash unsigned char Menu1PrdError400[]= "������.���. ����";
__flash unsigned char Menu1PrdError800[]= "������.����.��� ";
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

//�������� ����� 1
__flash unsigned char Menu20gr1n[] = "��1:";
__flash unsigned char Menu20gr2n[] = "��2:";
__flash unsigned char Menu20grName1[] = "������ 1";
__flash unsigned char Menu20grName2[] = "������ 2";
__flash strNameToVal Menu20grName[] = 
{
	{Menu20grName1, 1},
	{Menu20grName2, 2}
};

__flash unsigned char Menu20gr_off[] = "����";
__flash unsigned char Menu20gr_err[] = "����";
__flash unsigned char Menu20gr_def[] = "��";
__flash unsigned char Menu20gr_cf1[] = "��1";
__flash unsigned char Menu20gr_cf2[] = "��2";
__flash unsigned char Menu20gr_cf3[] = "��3";
__flash unsigned char Menu20gr_cf4[] = "��4";
__flash unsigned char Menu20gr_com1[] = "���1";
__flash unsigned char Menu20gr_com2[] = "���2";
__flash unsigned char Menu20gr_com3[] = "���3";
__flash unsigned char Menu20gr_com4[] = "���4";
__flash unsigned char Menu20gr_com5[] = "���5";
__flash unsigned char Menu20gr_com6[] = "���6";
__flash unsigned char Menu20gr_com7[] = "���7";
__flash unsigned char Menu20gr_com8[] = "���8";
__flash unsigned char Menu20gr_com9[] = "���9";
__flash unsigned char Menu20gr_com10[] = "��10";
__flash unsigned char Menu20gr_com11[] = "��11";
__flash unsigned char Menu20gr_com12[] = "��12";
__flash unsigned char Menu20gr_com13[] = "��13";
__flash unsigned char Menu20gr_com14[] = "��14";
__flash unsigned char Menu20gr_com15[] = "��15";
__flash unsigned char Menu20gr_com16[] = "��16";
__flash unsigned char Menu20gr_com17[] = "��17";
__flash unsigned char Menu20gr_com18[] = "��18";
__flash unsigned char Menu20gr_com19[] = "��19";
__flash unsigned char Menu20gr_com20[] = "��20";
__flash unsigned char Menu20gr_com21[] = "��21";
__flash unsigned char Menu20gr_com22[] = "��22";
__flash unsigned char Menu20gr_com23[] = "��23";
__flash unsigned char Menu20gr_com24[] = "��24";
__flash unsigned char Menu20gr_com25[] = "��25";
__flash unsigned char Menu20gr_com26[] = "��26";
__flash unsigned char Menu20gr_com27[] = "��27";
__flash unsigned char Menu20gr_com28[] = "��28";
__flash unsigned char Menu20gr_com29[] = "��29";
__flash unsigned char Menu20gr_com30[] = "��30";
__flash unsigned char Menu20gr_com31[] = "��31";
__flash unsigned char Menu20gr_com32[] = "��32";

// ��������� ������ ��� ��������
// ������
#define NDEF 0
// ����������� ������
#define NCF (1 - 1)
// ������
#define NCOM (3 - 1)

// ������ �������� � ������ 1, 2
// strNameToVal.name - ��� �������
// strNameToVal.val - ����� ������������ � ��� ��� ����� ������� � ���� 1
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

__flash unsigned char Menu201line4[] = "���� 1";
__flash unsigned char Menu202line4[] = "���� 2";
__flash unsigned __flash char *Menu20line4[] = {Menu201line4, Menu202line4};

__flash unsigned char Menu20no[] = "���� �� �������";

#define dNumSob 25
__flash unsigned char ArchSob[dNumSob] [11] =
{	
	"�.��.FLASH",
	"�.��.FLASH",
	"�.��.PLIS ",
	"�.��.PLIS ",
	"�.��.2RAM ",
	"�.��.2RAM ",
	"�.���.DSP ",
	"����.�.DSP",
	"����. U���",
	"���. U��� ",
	"�.��. � ��",
	"�. �����  ",
	"��� ��.���",
	"�.����.���",
	"�.���. ���",
	"��� �. ���",
	"����������",
	"���.������",
	"��.������ ",
	"��.�����. ",
	"����.�.���",
	"��� �. ���",
	"��� �.����",
	"��� �.����",
	"����������"
};											
#endif
