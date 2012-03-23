#ifndef _DEBUG
#define _DEBUG
/********** АВТОМАТИЧЕСКАЯ/РУЧНАЯ УСТАНОВКА УТСРОЙСТВА *********/
  #define AUT true /*автоматическое определение устройтва(true)/в ручную(flase)*/
  #if !AUT
    #define TYP 2 /* 1 - ВЧ, 2 - оптика, 3 - Е1 */
    #define LIN 3 /*скольки концевая*/
    #define PRD 0  /*кол-во команд на передеачу*/
    #define PRM1 0 /*кол-во команд на прием1*/
    #define PRM2 0 /*кол-во команд на прием2*/
    #define DEF 1 /*защиты нет(0)/есть(1)*/
  #endif 

  /********** ПЕРЕСЫЛКА КОМАНД НА ПК *********/
  #define PK false /* на комп(true)/по умолчанию(false) */
  #define ALT false /*персесылка всех команд (true) / избранных (false)*/
  #if !ALT /*в CM1-CM4 заносим нужные команды*/
    #define CT1 0xA3
    #define CT2 0xA2
    #define CT3 0xA1
    #define CT4 0xA4
    #define MST 0xA0    /*маска  команда&0xF0 == MST , если надо убрать пишем 0xFF */
  #endif
  #define ALR false /*пересылка всех ответов БСП (true) / избранных (false)*/
  #if !ALR /*в CM1-CM4 заносим нужные команды*/
    #define CR1 0x00
    #define CR2 0x00
    #define CR3 0x00
    #define CR4 0x00
    #define MSR 0xFF    /*маска команда&0xF0 == MSR , если надо убрать пишем 0xFF*/
  #endif
#endif