#ifndef MY_DEF_H_
#define MY_DEF_H_

#include <stdint.h>

// ������ ��������, ���� ������ ���� - �� �������
#define Insertion 0x0766
// ������� �������� 'f' - ������, ' ' - ���������
#define VARIANT 'f'	

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

//����� ������� ���� int
#define Hi(a) (unsigned char) (a>>8)
//����� ������� ���� Int
#define Lo(a) (unsigned char) (a)

#define SetBit(Port,Bit) Port|=(1<<Bit)
#define ClrBit(Port,Bit) Port&=~(1<<Bit)
#define TestBit(Port,Bit) Port&(1<<Bit)

//������ ������ � ������� ���� ���� �����
#define LoadHiByte(ints,chars) (((ints)&0x00ff)|((chars)<<8))
#define LoadLoByte(ints,chars) (((ints)&0xff00)|((chars)))
//���� ���������� ���������� ������ UART
#define EnRead 0x02
// ���� ���������� ���������� �������� UART
#define EnWrite 0x04
//���� ���������� ��� ���� ����� ��� �������� ���������
#define CurSost 0x10
//���� ����������, ��� ��������� �������
#define DataRead  0x08

//������ ������ ������������ �� UART ������
#define MaxLenghtRecBuf 128
#define MaxLenghtTrBuf 128

//������� ���������� ������ ������
#define HardError 0x01
  //��������� ���������� ������
  #define DisableReceive ClrBit(UCSR0B,RXEN0); ClrBit(UCSR0B,RXCIE0)
  //��������� ���������� ������
  #define EnableReceive SetBit(UCSR0B,RXEN0); SetBit(UCSR0B,RXCIE0)
  //��������� ���������� �� ������������ ������ ��������, ��������� ��������
  #define StopTrans ClrBit(UCSR0B,TXEN0); ClrBit(UCSR0B,UDRIE0)
//��������� ������� 0
#define StopT0 TCCR0=0

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