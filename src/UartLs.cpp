#include "ioavr.h"
#include "ina90.h" 
#include "UartLs.h"

/// Размер буфера принимаемых по UART данных.
#define UARTLS_BUF_RX_LENGTH 128

/// Размер буфера передаваемых по UART данных.
#define UARTLS_BUF_TX_LENGTH 255  

/// Пауза между принятыми байтами, при которой идет сброс на начало приема (мс).
#define DELAY_RESET 3

/// Пауза между принятыми байтами, при которой определяется окончание приема (мс).
#define DELAY_READ 5

/// Состояние приема.
typedef enum {
    STATE_RX_WAIT = 0,  ///< Ожидание начала приема данных. 
    STATE_RX_READ,      ///< Идет прием данных.
    STATE_RX_READY      ///< Данные приняты.
} stateRx_t;

/// Буфер принимаемых по UART данных.
unsigned char UARTLS_rxBuf[UARTLS_BUF_RX_LENGTH]; 

/// Буфер передаваемых по UART данных.
unsigned char UARTLS_txBuf[UARTLS_BUF_TX_LENGTH]; 

/// Состояние приема.
static stateRx_t stateRx;

// Время прошедшее с момента последнего приема байта данных.
static uint8_t delay = DELAY_READ; 

// счетчик принятых байт
static uint8_t rxCounter = 0;

// счетчик передаваемых данных
static uint8_t txCounter = 0; 

// кол-во передаваемых байт.
static uint8_t txLen = 0; 

static void push(uint8_t byte);
static void rxIntrOff(void);
static void rxIntrOn(void);
static void txIntrOff(void);
static void txIntrOn(void);

/// Прием байта данных.
void push(uint8_t byte) {
    if (rxCounter >= UARTLS_BUF_RX_LENGTH) {
        // переполнение буфера
        rxCounter = 0;
        stateRx = STATE_RX_WAIT;         
    } else {
        UARTLS_rxBuf[rxCounter++] = byte;
        stateRx = STATE_RX_READ;
    }   
}

/// Отключить прерывания приемника.
void rxIntrOff(void) {
    UCSR1B &= ~(1 << RXCIE1);
}

/// Включить прервания приемника.
void rxIntrOn(void) {
    UCSR1B |= (1 << RXCIE1);
}

/// Отключить прерывания передатчика.
void txIntrOff(void) {
    UCSR1B &= ~((1 << UDRIE1) | (1 << TXCIE1));
}

/// Включить прерывания передатчика.
void txIntrOn(void) {
    UCSR1B |= ((1 << UDRIE1) | (1 << TXCIE1));
}

/** Запуск работы приемника UART.
 *
 */
void UARTLS_rxStart(void) {
    stateRx = STATE_RX_WAIT;
    rxCounter = 0;    
    
    txIntrOff(); 
    rxIntrOn();
}

/** Старт передачи данных.
 *  
 *  Данные для передачи заранее помещаются в буфер передачи.
 *  Разрешаются прерывания по опустошению буфера и окончанию передачи.
 *
 *  @param[in] len Количество передаваемых данных.
 *  @return Нет.
 */
void UARTLS_txStart(uint8_t len) {
   txCounter = 0;
   txLen = len;
   
   // При запуске передачи приемник отключается и сбрасывается его состояние 
   rxIntrOff();
   stateRx = STATE_RX_WAIT;
   
   UDR1 = UARTLS_txBuf[txCounter++]; 
   txIntrOn();
}

/** Счетчик времени.
 *
 *  Должно вызываться с периодом 1 мс, напрмер из прерывания.
 * 
 *  Сделано для возможности работы по протоколу Modbus. Но по этому же принципу
 *  работает и стандартный протокол.
 *  
 *  TODO Так же сделана проверка перехода в режим чтения данных, при "зависании"
 *  в режиме передачи.
 *
 *  @return Нет.
 */
void UARTLS_tick(void) {   
    if (delay <= DELAY_READ)
        delay++;
    
    if (delay >= DELAY_READ) { 
        if (stateRx == STATE_RX_READ) {  
            //если прием сообщения уже шел, считаем что прием завершен
            //если обнаружена ошибка, то останавливаем прием
            rxIntrOff();
            stateRx = STATE_RX_READY;
        }
    } 
}

/** Проверка наличия принятого сообщения.
 *  
 *  @return True если есть принятое сообщение, иначе false.
 */
bool UARTLS_isRxData(void) {
    return (stateRx == STATE_RX_READY);
}

/** Возвращает количество принятых байт данных.
 *
 *  @return Количество принятых байт данных.
 */
uint8_t UARTLS_getDataLen(void) {
    return rxCounter;
}

/// Инициализация и запуск работы приемопередатчика UART1.
void UARTLS_setup(void) {
    UBRR1L = 51;
    
    // AT_RXD
    DDRD  &= ~(1 << PORTD2);
    PORTD &= ~(1 << PORTD2);
    
    // AT_TXD
    DDRD  |= (1 << PORTD3);
    PORTD |= (1 << PORTD3);
    
    // два стоп-бита и формат посылки 8 разрядов
    UCSR1C = (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10);
    
    // старт работы приемника и передатчика
    UCSR1B = (1 << TXEN1) | (1 << RXEN1); 
}

#pragma vector=USART1_RXC_vect
__interrupt void UART1_RX_interrupt(void) {
    volatile uint8_t byte = UDR1;
     
    if  (UCSR1A & ((1 << FE1) | (1 << DOR1) | (1 << UPE1))) {   
        // аппаратные ошибки
        UARTLS_rxStart();    
    } else {      
        if (delay >= DELAY_READ) {
            // начало приема данных
            rxCounter = 0; 
            push(byte);
        } else if (delay < DELAY_RESET) {
            // прием данных
            push(byte);
        }
    }
    
    // сброс счетчика паузы между байтами
    delay = 0;
}

#pragma vector=USART1_TXC_vect
__interrupt void UART1_TXC_interrupt(void) {   
    UARTLS_rxStart();
}

#pragma vector=USART1_UDRE_vect
__interrupt void UART1_UDRE_interrupt(void) {
    
    if (txCounter < txLen) {
        //если мы еще передали не все байты, то продолжаем передовать
        UDR1 = UARTLS_txBuf[txCounter++];
    } else {  
        // если все данные переданы, отключим прерывание по опустошению буфера
        UCSR1B &= ~(1 << UDRIE1);
    }
}