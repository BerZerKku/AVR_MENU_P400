/*****************************************
�������� ����� ����
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


/** ������������ ������ ���������� ����� � ����������� �� �������������
*	@param ���
*	@return ���
*/
void MenuParamGlbCreate(void)
{
	char num = 0;
	
	switch(TypeUdDev)
	{
		
		case 1:		// ���-90
		case 2:		// ����-80	
		case 8: 	// ���
		{
			sMenuGlbParam.punkt[num] = 0; 	sMenuGlbParam.name[num++] = 0;		// �������������
			sMenuGlbParam.punkt[num] = 2; 	sMenuGlbParam.name[num++] = 2;		// U��� �����������
			sMenuGlbParam.punkt[num] = 4;	sMenuGlbParam.name[num++] = 4;		// ������� �����
			sMenuGlbParam.punkt[num] = 6;	sMenuGlbParam.name[num++] = 6;		// �������
			sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;		// ����� ��������
			sMenuGlbParam.punkt[num] = 8; 	sMenuGlbParam.name[num++] = 8;		// �������� ���.�������
			sMenuGlbParam.punkt[num] = 9; 	sMenuGlbParam.name[num++] = NumParamGlb; // ����� ������� �� ��
			sMenuGlbParam.punkt[num] = 11; 	sMenuGlbParam.name[num++] = 11;		// ��������� ����������
			sMenuGlbParam.punkt[num] = 12; 	sMenuGlbParam.name[num++] = 12;		// ��������� ����
		}
		break;
		
		case 3:		// ����-�
		{
			sMenuGlbParam.punkt[num] = 0; 	sMenuGlbParam.name[num++] = 0;		// �������������
			sMenuGlbParam.punkt[num] = 2; 	sMenuGlbParam.name[num++] = 2;		// U��� �����������
			sMenuGlbParam.punkt[num] = 4; 	sMenuGlbParam.name[num++] = 4;		// ������� �����
			sMenuGlbParam.punkt[num] = 6;	sMenuGlbParam.name[num++] = 6;		// �������
			sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;		// ����� ��������
			sMenuGlbParam.punkt[num] = 8; 	sMenuGlbParam.name[num++] = 8;		// �������� ���.�������
			sMenuGlbParam.punkt[num] = 9; 	sMenuGlbParam.name[num++] = NumParamGlb; // ����� ������� �� ��
			sMenuGlbParam.punkt[num] = 11; 	sMenuGlbParam.name[num++] = 11;		// ��������� ����������
			sMenuGlbParam.punkt[num] = 12; 	sMenuGlbParam.name[num++] = 12;		// ��������� ����
			sMenuGlbParam.punkt[num] = 13; 	sMenuGlbParam.name[num++] = 13;		// �������� ������
			sMenuGlbParam.punkt[num] = 14; 	sMenuGlbParam.name[num++] = 14;		// ������� ��������
			sMenuGlbParam.punkt[num] = 15; 	sMenuGlbParam.name[num++] = 15;		// ���������� �������
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.proval[i] = MenuAllProval[i];
				if (MenuAllProval[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[num] = 16;	sMenuGlbParam.name[num++] = 16;		// ����� �� ������
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.porog[i] = MenuAllPorog[i];
				if (MenuAllPorog[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[num] = 17;	sMenuGlbParam.name[num++] = 17;		// ���������� ������
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.noise[i] = MenuAllNoise[i];
				if (MenuAllNoise[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[num] = 18; 	sMenuGlbParam.name[num++] = 18;		// ��� ������������
			sMenuGlbParam.punkt[num] = 21; 	sMenuGlbParam.name[num++] = 21;		// ������ ������� ������ ��
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.periodAC[i] = MenuAllPorog[i];
				if (MenuAllPorog[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[num] = 22; 	sMenuGlbParam.name[num++] = 22;		/// ������ ������� ������� ������ ��
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.periodACre[i] = MenuAllPorog[i];
				if (MenuAllPorog[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[num] = 23; 	sMenuGlbParam.name[num++] = 23;		// ��������� ������� ��
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.timeCorrAC[i] = MenuAllTimeCorrAC[i];
				if (MenuAllTimeCorrAC[i] == 0)
					break;
			}
		}
		break;
		
		case 4:		// ����
		{
			sMenuGlbParam.punkt[num] = 0; 	sMenuGlbParam.name[num++] = 0;		// �������������
			sMenuGlbParam.punkt[num] = 2; 	sMenuGlbParam.name[num++] = 2;		// U��� �����������
			sMenuGlbParam.punkt[num] = 4;	sMenuGlbParam.name[num++] = 4;		// ������� �����
			sMenuGlbParam.punkt[num] = 6;	sMenuGlbParam.name[num++] = 6;		// �������
			sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;		// ����� ��������
			sMenuGlbParam.punkt[num] = 8; 	sMenuGlbParam.name[num++] = 8;		// �������� ���.�������
			sMenuGlbParam.punkt[num] = 9; 	sMenuGlbParam.name[num++] = NumParamGlb; // ����� ������� �� ��
			sMenuGlbParam.punkt[num] = 20;	sMenuGlbParam.name[num++] = 20;		// �������� ������ ��
			sMenuGlbParam.punkt[num] = 11; 	sMenuGlbParam.name[num++] = 11;		// ��������� ����������
			sMenuGlbParam.punkt[num] = 12; 	sMenuGlbParam.name[num++] = 12;		// ��������� ����
		}
		break;
		
		case 7 : 	// ����
		{
			sMenuGlbParam.punkt[num] = 0; 	sMenuGlbParam.name[num++] = 0;		// �������������
			sMenuGlbParam.punkt[num] = 2; 	sMenuGlbParam.name[num++] = 2;		// U��� �����������
			sMenuGlbParam.punkt[num] = 4;	sMenuGlbParam.name[num++] = 4;		// ������� �����
			sMenuGlbParam.punkt[num] = 6;	sMenuGlbParam.name[num++] = 6;		// �������
			sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;		// ����� ��������
			sMenuGlbParam.punkt[num] = 8; 	sMenuGlbParam.name[num++] = 8;		// �������� ���.�������
			sMenuGlbParam.punkt[num] = 9; 	sMenuGlbParam.name[num++] = NumParamGlb; // ����� ������� �� ��
			sMenuGlbParam.punkt[num] = 15; 	sMenuGlbParam.name[num++] = 15;		// ���������� �������
			sMenuGlbParam.punkt[num] = 23; 	sMenuGlbParam.name[num++] = 23;		// ��������� ������� ��
			sMenuGlbParam.punkt[num] = 11; 	sMenuGlbParam.name[num++] = 11;		// ��������� ����������
			sMenuGlbParam.punkt[num] = 12; 	sMenuGlbParam.name[num++] = 12;		// ��������� ����
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.timeCorrAC[i] = MenuAllTimeCorrAC[i];
				if (MenuAllTimeCorrAC[i] == 0)
					break;
			}
		}
		break;
		
		default: 	// �����
		{
			if (cTypeLine == 1)													
			{
				sMenuGlbParam.punkt[num] = 0;	sMenuGlbParam.name[num++] = 0;	// �������������
				sMenuGlbParam.punkt[num] = 1;	sMenuGlbParam.name[num++] = 1;	// C������������ �����
				sMenuGlbParam.punkt[num] = 2;	sMenuGlbParam.name[num++] = 2;	// U��� �����������
				sMenuGlbParam.punkt[num] = 4;	sMenuGlbParam.name[num++] = 4;	// ������� �����
				//				sMenuGlbParam.punkt[num] = 5; 	sMenuGlbParam.name[num++] = 5;	// ����� �����������
				sMenuGlbParam.punkt[num] = 6;	sMenuGlbParam.name[num++] = 6;	// �������
				sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;	// ����� ��������
				sMenuGlbParam.punkt[num] = 8; 	sMenuGlbParam.name[num++] = 8;	// �������� ���.�������
				sMenuGlbParam.punkt[num] = 9; 	sMenuGlbParam.name[num++] = 9;	// ����� ������� �� ��
				sMenuGlbParam.punkt[num] = 11; 	sMenuGlbParam.name[num++] = 11;	// ��������� ����������
				sMenuGlbParam.punkt[num] = 12; 	sMenuGlbParam.name[num++] = 12;	// ��������� ����
			}
			else
			{
				sMenuGlbParam.punkt[num] = 1; 	sMenuGlbParam.name[num++] = 1;	// C������������ �����
				sMenuGlbParam.punkt[num] = 4; 	sMenuGlbParam.name[num++] = 4;	// ������� �����
				sMenuGlbParam.punkt[num] = 7; 	sMenuGlbParam.name[num++] = 7;	// ����� ��������
				if (cNumComR > 0)
					sMenuGlbParam.punkt[num] = 5;	sMenuGlbParam.name[num++] = 5;	// ����� �����������
				sMenuGlbParam.punkt[num] = 19;	sMenuGlbParam.name[num++] = 19;	// ��������������
			}			
		}
	}
	
	sMenuGlbParam.num = num;
}

/** ������������ ������ ���������� ������ � ����������� �� �������������
 *	� ������ �������������� ���, ������� ��������������� ���-�� ������
 *	@param ���
 *	@return ���
 */
void MenuParamDefCreate(void)
{
	char num = 0;
	char type = TypeUdDev;
	
	// � ������ ��� ��������������
	if (cTypeLine == 2)
		type = 0;
	
	switch(type)
	{
		case 1:		// ���-90 
		case 2:		// ����-80
		case 3:		// ����-�
		case 8:
		{
			sMenuDefParam.punkt[num++] = 0;		// ��� ������
			sMenuDefParam.punkt[num++] = 1;		// ��� �����
			sMenuDefParam.punkt[num++] = 2;		// ���. ����� ��� ���.
//			sMenuDefParam.punkt[num++] = 3;		// �������� �� �����
//			sMenuDefParam.punkt[num++] = 4;		// ���������� ���������
			sMenuDefParam.punkt[num++] = 5;		// ���� �������� ��  ��
			sMenuDefParam.punkt[num++] = 7;		// ������� ���
			sMenuDefParam.punkt[num++] = 8;		// ������� ���
		}
		break;
		
		case 4:		// ����
		{
			sMenuDefParam.punkt[num++] = 0;		// ��� ������
			sMenuDefParam.punkt[num++] = 2;		// ���. ����� ��� ���.
//			sMenuDefParam.punkt[num++] = 3;		// �������� �� �����
//			sMenuDefParam.punkt[num++] = 4;		// ���������� ���������
			sMenuDefParam.punkt[num++] = 5;		// ���� �������� ��  ��
			sMenuDefParam.punkt[num++] = 7;		// ������� ���
			sMenuDefParam.punkt[num++] = 8;		// ������� ���
		}
		break;
		
		case 7: 	// ����
		{
			sMenuDefParam.punkt[num++] = 0;		// ��� ������
			sMenuDefParam.punkt[num++] = 1;		// ��� �����
			sMenuDefParam.punkt[num++] = 2;		// ���. ����� ��� ���.
			sMenuDefParam.punkt[num++] = 5;		// ���� �������� ��  ��
			sMenuDefParam.punkt[num++] = 7;		// ������� ���
			sMenuDefParam.punkt[num++] = 8;		// ������� ���
		}
		break;
		
		default:	// �����
		{
			sMenuDefParam.punkt[num++] = 0;		// ��� ������
			sMenuDefParam.punkt[num++] = 1;		// ��� �����
			sMenuDefParam.punkt[num++] = 2;		// ���. ����� ��� ���.
//			sMenuDefParam.punkt[num++] = 3;		// �������� �� �����
//			sMenuDefParam.punkt[num++] = 4;		// ���������� ���������
			if (cTypeLine == 1)						// � �� ���� �������������� ���������
			{
				sMenuDefParam.punkt[num++] = 5;	// ���� �������� ��  ��						 	
				sMenuDefParam.punkt[num++] = 6;	// �������� ������ ��
			}
		}
	}	
	sMenuDefParam.punkt[num++] = 9;	// ����� ���.������ ���
	sMenuDefParam.punkt[num++] = 10;// ����� ���.������ ���
	sMenuDefParam.punkt[num++] = 11;// ����� ���
	sMenuDefParam.punkt[num++] = 12;// ����� �� ��� �� ����
	
	sMenuDefParam.num = num;
}

/** ������������ ������ ������ ���������� � ����������� �� �������������
 *	@param act ��������
 *	@arg 0 �������� ������ ���� ����������
 *	@arg 1 �������� ���������
 *	@return ���
 */
void MenuUprCreate(uint8_t act)
{
	if (act == 0 )
	{
		// ������ ���� ���� ������
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
		
		// ������ ���� ���� ������
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
			case 1:		// ���-90	
			{
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				dSetUprItem(CTRL_COM_RESET_REMOTE, 		CTRL_NAME_RESET_REMOTE);	
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 2:		// ����-80		
			{		
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 3:		// ����-�
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
			
			case 4: 	// ����
			{
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				dSetUprItem(CTRL_COM_START_REMOTE_2,	CTRL_NAME_AC_START_REMOTE);
				dSetUprItem(CTRL_COM_START_REMOTE_12, 	CTRL_NAME_START_PRD);
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 7: 	// ����
			{	
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
				dSetUprItem(CTRL_COM_CALL,				CTRL_NAME_CALL);
			}
			break;
			
			case 8:		// ���
			{
				dSetUprItem(CTRL_COM_RESET_SELF, 		CTRL_NAME_RESET_SELF);
			}
			break;
			
			default:	// �����
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
							// � �� ���� � �����
							dSetUprItem(CTRL_COM_CALL, CTRL_NAME_CALL);
						}
					}
				}
			}
		}
		
		sMenuUpr.num = num;	
	}
}

/** ������������ ������ ������ ���������� �� � ����������� �� �������������.
 *	
 *	@return ���
 */
void MenuACCreate(void)
{
	char num = 0;
	
	switch(TypeUdDev)
	{
		case 1:		// ���-90	
		{	
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_ACCELERATED,			CTRL_NAME_AC_ACCELERATED);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_TEST);
			dSetACItem(CTRL_COM_AC_START,				CTRL_NAME_AC_START);
		}
		break;
		
		case 2:		// ����-80		
		{		
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_ACCELERATED,			CTRL_NAME_AC_ACCELERATED);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_TEST);
			dSetACItem(CTRL_COM_AC_START,				CTRL_NAME_AC_START);
		}
		break;
		
		case 3:		// ����-�
		{
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_ACCELERATED,			CTRL_NAME_AC_ACCELERATED);
			dSetACItem(CTRL_COM_AC_CHECK, 				CTRL_NAME_AC_QUICK);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_CHECK);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
		}
		break;
		
		case 4: 	// ����
		{
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_CHECK,				CTRL_NAME_AC_ONE_SIDE);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
			dSetACItem(CTRL_COM_RESET_REMOTE,			CTRL_NAME_AC_RESET);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_START_SELF);
		}
		break;

		case 7: 	// ����
		{
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_ACCELERATED,			CTRL_NAME_AC_ACCELERATED);
			dSetACItem(CTRL_COM_AC_CHECK, 				CTRL_NAME_AC_QUICK);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_CHECK);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
		}
		break;
		
		case 8:		// ���
		{
			dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,	CTRL_NAME_AC_NORMAL);
			dSetACItem(CTRL_COM_AC_ACCELERATED,			CTRL_NAME_AC_ACCELERATED);
			dSetACItem(CTRL_COM_AC_OFF,					CTRL_NAME_AC_OFF);
			dSetACItem(CTRL_COM_AC_TEST,				CTRL_NAME_AC_START);
		}
		break;
		
		default:	// �����
		{
			if (cTypeLine == 1)													
			{
				// � �� ���� ����� �� � �����
				dSetACItem(CTRL_COM_AC_AUTO_ACCELERATED,CTRL_NAME_AC_AUTO);
				dSetACItem(CTRL_COM_AC_ACCELERATED,		CTRL_NAME_AC_ACCELERATED);
				dSetACItem(CTRL_COM_AC_OFF,				CTRL_NAME_AC_OFF);
			}
		}
	}
	
	sMenuAC.num = num;	
}



/** ������������ ������ ����� �� � ����������� �� ���� �������������
*	@param ���
*	@return ���
*/
void MenuAKCreate(void)
{
	char i = 0;
	
	param4[i++] = 0;
	
	if (TypeUdDev > 0)			// ���-90, ����-80, ����-�, ���� 
	{	
		param4[i++] = 8;	// ����.��
		param4[i++] = 8;	// ����.��
	}
	else						// �����
	{
		param4[i++] = 1;	// ����.��
		param4[i++] = 2;	// ����.��
	}
	
	param4[i++] = 3;		// ���.��
	param4[i++] = 4;		// ����.��
	
	if ((TypeUdDev == 3) || (TypeUdDev == 7))	// ����-�
	{
		param4[i++] = 9;	// ����.��
		param4[i++] = 5;	// ����.��
	}
	else if (TypeUdDev == 4)	// ����
	{
		param4[i++] = 10;	// �����.��
		param4[i++] = 5;	// ����.��
	}
	else						// �����, ���-90, ����
	{
		param4[i++] = 5;	// ����.��
		param4[i++] = 6;	// �����.��
	}
}

/** ������������ ���� ����
*	@param ���
* 	@return ���
*/
void MenuTestCreate(void)
{	
	uint8_t num = 0;
	
	// ������� ���-�� ��������� ����� ��������
	sMenuTest.gr_items_max = 0;
	
	// ������� �������� ������ 1 ������������:
	// � ������ - ������ ��1
	// � �� ������ ����, ������������� �� ����� - ��� ��������
	// � �� 2-�������� ������������� ����� �400 - ��1, ��2
	// � �� 3-�������� ������������� ����� �400 - ��1, ��2, ��3, ��4
	//
	// ����� ����������� ���� ������, ��� �� �������
	// ��� ���� ����� ���� ������ ��1, ��2
	
	sMenuTest.cf_val = SIGN_ERROR;
	num = 0;
	if ( (cNumComR != 0) || (cNumComT != 0) || (TypeUdDev == 0) )
	{		
		uint8_t num_com = (cNumComR > cNumComR) ? cNumComR : cNumComT;
		
		// ������� ������ 1
		sMenuTest.gr_items[sMenuTest.gr_items_max++] = 1;
		
		sMenuTest.cf_items[num++] = SIGN_OFF;
		sMenuTest.cf_items[num++] = SIGN_CF1;
		
		// � ������ ���� ������ ��1
		// � 2-� �������� �� ��1, ��2
		// � 3-� �������� �� ��1, ��2, ��3, ��4
		if (cTypeLine != 2)
		{
			sMenuTest.cf_items[num++] = SIGN_CF2;
			
			if (cNumLine == 3)
			{
				sMenuTest.cf_items[num++] = SIGN_CF3;
				sMenuTest.cf_items[num++] = SIGN_CF4;
			}
		}
		
		// �������� ������, ��� �� �������
		for(char i = 0 ; i < num_com; i++)
		{
			sMenuTest.cf_items[num++] = SIGN_COM1 + i;
		}
	}
	sMenuTest.cf_items_max = num;
	
	// ������� ������� ������, ������������ ������ �������� �����
	sMenuTest.def_val = SIGN_ERROR;
	num = 0;
	if (bDef)
	{
		// ������� ������ 2
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
	if ((cNumComR>0)&&(CurrentState[2]<0x04)) MaxShiftMenu=0;   //���� ���� ��������, � �� �� � ����
	if ((cNumComT>0)&&(CurrentState[4]<0x04)) MaxShiftMenu=0;  //���� ���� ����������, � �� �� � ����
	if ((bDef)&&(CurrentState[0]<0x04)) MaxShiftMenu=0; //���� ���� ����, � �� �� � ����
	LCD2new=1;
}

//����/�������� ����������
static void Menu_ParamSetup(eMENUlvl Menu)
{
	MenuLevel = Menu; // 6 � 12
	LCDbufClMenu();
	ShiftMenu=0;
	ValueVsRange=0;
	NumberCom=1;
	if (LineInMenu6 <= 3){ //���� 3 ��� ����� �����
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
	MaxShiftMenu = NumParamPrm - 1 - 1;	// �� ������ ������ ��� ���������� ���-��
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
		return;   //���� ���� ��������, � �� �� � ����
  	if ( (cNumComT) && (CurrentState[4]  <0x04) )
		return;  //���� ���� ����������, � �� �� � ����
  	if ( (bDef) && (CurrentState[0] < 0x04) )
	 	return;  //���� ���� ������, � ��� �� � ����
	
   	MenuLevel = LVL_TEST;
   	LCDbufClMenu();
   	ShiftMenu = 0;
	MaxDisplayLine = 3;
	MaxShiftMenu = sMenuTest.gr_items_max - 1;
	
   	if ((cNumComR>0)&&(CurrentState[2]==5)) MaxShiftMenu=0;   //���� ���� ��������, � �� � ����2
   	if ((cNumComT>0)&&(CurrentState[4]==5)) MaxShiftMenu=0;  //���� ���� ����������, � �� � ����2
   	if ((bDef)&&(CurrentState[0]==5)) MaxShiftMenu=0;  //���� ���� ������, � ��� � ����2
   	LCD2new=1;
}

static void PressInMenuJournal(char Key)
{  //������� � ���� ����� -> ������� � ��������� �������
	Key-=0x31;
	if (sArchive.NumDev>=Key)
	{ //���� ���� ����������
		MenuLevel = LVL_JRN_VIEW;
		LCDbufClMenu();
		ShiftMenu=0;
		MaxDisplayLine=2;
		sArchive.CurrDev=Key;
		sArchive.RecCount=0;  //��� ������ ������� ���-�� ������
		
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
{ //������� � ���� ����/�����
	WorkRate=0x03;
	InputParameter=Key;
	if (Key==1) ChangeMass=DataLCD;
	else ChangeMass=TimeLCD;
	Discret=1;  //������� 1
	for (char i=0; i<=8; i++) InputDataTime[i]=ChangeMass[i];
}

/** ����� ������ � ���� ����������
*	@param key ��� ������� ������
*	@return ���
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

/** ����� ������ � ���� ������������
*	@param key ��� ������� ������
*	@return ���
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

