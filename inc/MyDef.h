#ifndef MY_DEF_H_
#define MY_DEF_H_
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

#define uchar unsigned char
#define schar signed char
#define uint  unsigned int
#define sint signed int

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
	uchar dev;			// ��� ���������� ��������
	uchar num;			// ���-�� �������
	uchar punkt[20];	// ������ �������, �� ������� ��������� � �������� ������� �� flash
	uchar name[20];		// ����� �������� , �� ������ �� ����
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
//	uchar type;					//���
//	uchar val;					//��������
//	uchar __flash* __flash* sp;	//��������
//	uchar __flash* name;		//��� ������
//	uchar num;					//���-�� ������� � ������
//	uchar punkt[3];				//������ �������
//};
//
//struct strMenuTest
//{
//	strTest sT[2];		//��������� �����
//	uchar num;			//���-�� ����� �� �����
//	uchar numTr;		//���-�� ����� �� ��������
//};

struct strNameToVal
{
	uchar __flash *name;
	uchar val;
};

struct strMenuTest
{
	uchar gr_items[2];			// ��������� ������ ��������
	uchar gr_items_max;			// ���-�� ����� ��������
			
	
	uchar def_items[2];			// ������ ��� ������� ������ <-> �������� 
	uchar def_items_max;		// ������������ ���-�� ��-�� ������
	uchar def_val;				// ������� �������� ������� ������		
	
	uchar cf_items[40];			// ������ ��� ������� �� <-> �������� 
	uchar cf_items_max;			// ������������ ���-�� ��-�� ��
	uchar cf_val;				// ������� �������� ������� ��
};

struct strParamPVZUE
{
	uchar protocol;		// �������� ������
	uchar parity;		// ������� ��������
	uchar proval[10];	// ���������� �������
	uchar porog[10];	// ����� �� ������
	uchar noise[10];	// ���������� ������
	uchar autocontrol;	// ��� ������������
	uchar periodAC[10];	// ������ ������� ������ ��
	uchar periodACre[10];// ������ ������� ������� ������ ��
	uchar timeCorrAC[10];// ����� ��������� ��
};

struct strParamOpt
{
	uchar reserv;		// �������������� (��� = 1/���� = 0)
};
#endif