#ifndef MY_DEF_H_
#define MY_DEF_H_

#include <stdint.h>

// ������ ��������, ���� ������ ���� - �� �������
#define Insertion 0x0766
// ������� �������� 'f' - ������, ' ' - ���������
#define VARIANT ' '	

// ����������� �������
// ���������� ��������������, ���������� �������� ������
// ����������� ���������� ���������
//#define EXHIBITION

#define DEB false/*������(false)/�������(true)*/
#if DEB // ����������� ����� "debug.h" 
	#warning "DEBUG MODE ON!!!"
	#include "debug.h"
#endif

#define SIZE_OF(mas) (sizeof(mas) / sizeof(mas[0]))

#define SetBit(Port,Bit) Port|=(1<<Bit)
#define ClrBit(Port,Bit) Port&=~(1<<Bit)
#define TestBit(Port,Bit) Port&(1<<Bit)

//���� ���������� ��� ���� ����� ��� �������� ���������
#define CurSost 0x10

//������ ������ ������������ �� UART ������
#define MaxLenghtRecBuf 128
#define MaxLenghtTrBuf 128

//��������� ���������� ������
#define DisableReceive ClrBit(UCSR0B,RXEN0); ClrBit(UCSR0B,RXCIE0)
//��������� ���������� ������
#define EnableReceive SetBit(UCSR0B,RXEN0); SetBit(UCSR0B,RXCIE0)
//��������� ���������� �� ������������ ������ ��������, ��������� ��������
#define StopTrans ClrBit(UCSR0B,TXEN0); ClrBit(UCSR0B,UDRIE0)

//*100�� , ����� �������� ������� � ��
#define PC_wait 15

struct strArchive{
  unsigned char NumDev; 	//���-�� ���������
  unsigned char CurrDev;  	//��������� ����������
  unsigned char Dev[5]; 	//������ ������� ���������: 0 ���� ����� ��� ����� ���� �� ������� =0�00 ������!
                       		//�������: 0 - ������� , 1 - ���, 2- ���, 3- ���
  int RecCount; 			//���-�� ������� � ������� ������
  char CurCount;  			//����� ����� ������ ������ ������
  unsigned char Data[16];
};

struct strCorrParam {
    unsigned char Print[7]; //������ ��� ����� ��������� �� �����
    signed int Corr;  //������� ���������
};

struct strMenuGlbParam {
	uint8_t dev;			// ��� ���������� ��������
	uint8_t num;			// ���-�� �������
	uint8_t punkt[20];	    // ������ �������, �� ������� ��������� � �������� ������� �� flash
	uint8_t name[20];		// ����� �������� , �� ������ �� ����
};

/** ������ �������������� ���������� ������ �� ��������� ����.
 *
 *  ������ ������ �������������� Menu18Param.
 */
typedef enum {
    PROTOCOL_S = 0,     // ����������� ��������
    PROTOCOL_MODBUS,    // ModBus
    PROTOCOL_MAX        // ���������� ��������� ������������. 
} protocol_t;

/** ������ ��������� ���������.
 *
 *  ������ ������ ��������������� fmTypeUdDev.
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

/// ������ ������������ ������.
typedef enum {
    COM_GET_MEAS 			= 0x34,
    COM_PRM_ENTER 			= 0x51,	
    COM_SET_CONTROL 		= 0x72,
    COM_SET_PASSWORD 		= 0x73,	// ������ � ��
	COM_GET_PASSWORD 		= 0x74,	// ������ � ��
    COM_DEF_SET_TYPE_AC 	= 0x8A,	
    COM_PRM_RES_IND			= 0x9A,
    COM_PRD_RES_IND 		= 0xAA
} com_t;

/// �������� ������� ���������� (COM_SET_CONTROL).
typedef enum {
	CONTROL_RESET_SELF 	= 1,	///< ����� ������
    CONTROL_RESET_UD_1	= 2,	///< ����� ���������� 1
	CONTROL_RESET_UD_2	= 3,	///< ����� ���������� 2
    CONTROL_PUSK_UD_1 	= 4,	///< ���� ���������� (1)
	CONTROL_PUSK_UD_2 	= 5,	///< ���� ���������� 2
    CONTROL_PUSK_UD_ALL = 6,	///< ���� ���������
    CONTROL_CALL 		= 7,	///< �����
    CONTROL_PUSK_ON 	= 8,	///< ���� ���������� ���.
	CONTROL_PUSK_OFF 	= 9,	///< ���� ���������� ����.
    CONTROL_MAN_1 		= 10,	///< ���� ��� ���������� (1)
	CONTROL_MAN_2 		= 11,	///< ���� ��� ���������� 2
    CONTROL_MAN_ALL 	= 12,	///< ���� ��� ���������
    CONTROL_PUSK_UD_3 	= 13,	///< ���� ���������� 3
    CONTROL_MAN_3 		= 14,	///< ���� ��� ���������� 3
    CONTROL_RESET_AC	= 15,	///< ����� ��
    //
	CONTROL_MAX					///<
} control_t;

/// �������� ������� ������������ (COM_DEF_SET_TYPE_AC)
typedef enum {
    AC_NORM_FAST    = 1,    ///< ����-����������.    
    AC_NORM         = 2,    ///< ����-����������.
    AC_FAST         = 3,    ///< ����������.
    AC_OFF          = 4,    ///< ��������.
    AC_CHECK        = 5,    ///< ����������� �������� (� ����-� ������� ��������).
    AC_TEST         = 6,    ///< ��������� (����������� �������� � ����-�).
    AC_PUSK         = 7,    ///< ����.
    //
    AC_MAX                  ///<
} ac_t;

//struct strTest
//{
//	uint8_t type;					//���
//	uint8_t val;					//��������
//	uint8_t __flash* __flash* sp;	//��������
//	uint8_t __flash* name;		//��� ������
//	uint8_t num;					//���-�� ������� � ������
//	uint8_t punkt[3];				//������ �������
//};
//
//struct strMenuTest
//{
//	strTest sT[2];		//��������� �����
//	uint8_t num;			//���-�� ����� �� �����
//	uint8_t numTr;		//���-�� ����� �� ��������
//};

struct strNameToVal
{
	uint8_t __flash *name;
	uint8_t val;
};

struct strMenuTest
{
	uint8_t gr_items[2];			// ��������� ������ ��������
	uint8_t gr_items_max;			// ���-�� ����� ��������
			
	
	uint8_t def_items[2];			// ������ ��� ������� ������ <-> �������� 
	uint8_t def_items_max;		// ������������ ���-�� ��-�� ������
	uint8_t def_val;				// ������� �������� ������� ������		
	
	uint8_t cf_items[40];			// ������ ��� ������� �� <-> �������� 
	uint8_t cf_items_max;			// ������������ ���-�� ��-�� ��
	uint8_t cf_val;				// ������� �������� ������� ��
};

struct strParamPVZUE
{
	uint8_t protocol;		// �������� ������
	uint8_t parity;		// ������� ��������
	uint8_t proval[10];	// ���������� �������
	uint8_t porog[10];	// ����� �� ������
	uint8_t noise[10];	// ���������� ������
	uint8_t autocontrol;	// ��� ������������
	uint8_t periodAC[10];	// ������ ������� ������ ��
	uint8_t periodACre[10];// ������ ������� ������� ������ ��
	uint8_t timeCorrAC[10];// ����� ��������� ��
};

struct strParamOpt
{
	uint8_t reserv;		// �������������� (��� = 1/���� = 0)
};
#endif