#ifndef _DEBUG
#define _DEBUG

	/********** АВТОМАТИЧЕСКАЯ/РУЧНАЯ УСТАНОВКА УТСРОЙСТВА *********/
	#define AUT true 		//автоматическое определение устройтва(true)/в ручную(flase)*/
  	
	#if !AUT
    	#define TYP 1 			// 1 - ВЧ, 2 - оптика, 3 - Е1 
    	#define LIN 2 			// скольки концевая
    	#define PRD 1  			// кол-во команд на передеачу
    	#define PRM1 1 			// кол-во команд на прием1
    	#define PRM2 1 			// кол-во команд на прием2
    	#define DEF 0 			// защиты нет(0) / есть(1)
  	#endif 

  	/********** ПЕРЕСЫЛКА КОМАНД НА ПК *********/
	#define PK false		// Включена (true)/ отключена (false) 

  	#define ALT false 		// персесылка всех команд (true) / избранных (false)
  	#if !ALT 				// в CM1-CM4 заносим нужные команды
    	#define CT1 0xF1
    	#define CT2 0xF2
    	#define CT3 0x00
    	#define CT4 0x00
    	#define MST 0xFF    	// маска  (команда & 0xF0) == MST , если надо убрать пишем 0xFF 
  	#endif

  	#define ALR false 		// пересылка всех ответов БСП (true) / избранных (false)
  	#if !ALR 				// в CM1-CM4 заносим нужные команды 
    	#define CR1 0xF1
    	#define CR2 0xF2
    	#define CR3 0x00
    	#define CR4 0x00
    	#define MSR 0xFF    	// маска (команда & 0xF0) == MSR , если надо убрать пишем 0xFF
  	#endif
#endif