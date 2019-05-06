#include "ioavr.h"
#include "ina90.h"
#include "MyDef.h"
#include "comp_a90.h"
#include "delay.h"
#include "board.h"
#include "driverLCD.h"
 
/** Проверка строки на нажатые кнопки.
 *
 *  @param[in] row Номер строки.
 *  @param[out] Считанное с клавиатуры значение.
 *  @return Если обнаружена нажатая кнопка(и) true, иначе false.
 */
static bool checkRow(unsigned char row, unsigned char *key) {
    DDRC = (1 << row);
    delay_us(1);
    *key = PINC;
    
    return !(*key == ((unsigned char) ~(1 << row)));
}

/** Опрос клавиатуры.
 *
 *  @return Возвращает код нажатой кнопки.
 *  @retval 0xF0 Нажатых кнопок нет. 
 */
unsigned char InquiryKeyboard(void){
    bool state;
    unsigned char key;
    
    state = checkRow(PIN_ROW1, &key);
    
    if (!state) {
        state = checkRow(PIN_ROW2, &key);
    }
    
    if (!state) {
        state = checkRow(PIN_ROW3, &key);
    }
        
    if (!state) {
        state = checkRow(PIN_ROW4, &key);   
    }
    
    if (state) {
        switch(key){
            case 0x7E: key='C'; break;
            case 0xDE: key='#'; break;
            case 0xBE: key='0'; break;
            case 0xEE: key='M'; break;
            case 0x7D: key='D'; break;
            case 0xDD: key='9'; break;
            case 0xBD: key='8'; break;
            case 0xED: key='7'; break;
            case 0x7B: key='U'; break;
            case 0xDB: key='6'; break;
            case 0xBB: key='5'; break;
            case 0xEB: key='4'; break;
            case 0x77: key='E'; break;
            case 0xD7: key='3'; break;
            case 0xB7: key='2'; break;
            case 0xE7: key='1'; break;
            default: key=0xF0;
        }
    } else {
        key = 0xF0;
    }
    
    return key;
};
