#ifndef _DEBUG
#define _DEBUG
/********** ��������������/������ ��������� ���������� *********/
  #define AUT true /*�������������� ����������� ���������(true)/� ������(flase)*/
  #if !AUT
    #define TYP 2 /* 1 - ��, 2 - ������, 3 - �1 */
    #define LIN 3 /*������� ��������*/
    #define PRD 0  /*���-�� ������ �� ���������*/
    #define PRM1 0 /*���-�� ������ �� �����1*/
    #define PRM2 0 /*���-�� ������ �� �����2*/
    #define DEF 1 /*������ ���(0)/����(1)*/
  #endif 

  /********** ��������� ������ �� �� *********/
  #define PK false /* �� ����(true)/�� ���������(false) */
  #define ALT false /*���������� ���� ������ (true) / ��������� (false)*/
  #if !ALT /*� CM1-CM4 ������� ������ �������*/
    #define CT1 0xA3
    #define CT2 0xA2
    #define CT3 0xA1
    #define CT4 0xA4
    #define MST 0xA0    /*�����  �������&0xF0 == MST , ���� ���� ������ ����� 0xFF */
  #endif
  #define ALR false /*��������� ���� ������� ��� (true) / ��������� (false)*/
  #if !ALR /*� CM1-CM4 ������� ������ �������*/
    #define CR1 0x00
    #define CR2 0x00
    #define CR3 0x00
    #define CR4 0x00
    #define MSR 0xFF    /*����� �������&0xF0 == MSR , ���� ���� ������ ����� 0xFF*/
  #endif
#endif