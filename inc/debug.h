#ifndef _DEBUG
#define _DEBUG

	/********** ��������������/������ ��������� ���������� *********/
	#define AUT true 		//�������������� ����������� ���������(true)/� ������(flase)*/
  	
	#if !AUT
    	#define TYP 1 			// 1 - ��, 2 - ������, 3 - �1 
    	#define LIN 2 			// ������� ��������
    	#define PRD 1  			// ���-�� ������ �� ���������
    	#define PRM1 1 			// ���-�� ������ �� �����1
    	#define PRM2 1 			// ���-�� ������ �� �����2
    	#define DEF 0 			// ������ ���(0) / ����(1)
  	#endif 

  	/********** ��������� ������ �� �� *********/
	#define PK false		// �������� (true)/ ��������� (false) 

  	#define ALT false 		// ���������� ���� ������ (true) / ��������� (false)
  	#if !ALT 				// � CM1-CM4 ������� ������ �������
    	#define CT1 0xF1
    	#define CT2 0xF2
    	#define CT3 0x00
    	#define CT4 0x00
    	#define MST 0xFF    	// �����  (������� & 0xF0) == MST , ���� ���� ������ ����� 0xFF 
  	#endif

  	#define ALR false 		// ��������� ���� ������� ��� (true) / ��������� (false)
  	#if !ALR 				// � CM1-CM4 ������� ������ ������� 
    	#define CR1 0xF1
    	#define CR2 0xF2
    	#define CR3 0x00
    	#define CR4 0x00
    	#define MSR 0xFF    	// ����� (������� & 0xF0) == MSR , ���� ���� ������ ����� 0xFF
  	#endif
#endif