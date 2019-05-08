#include "ioavr.h"
#include "ina90.h" 
#include "UartLs.h"

/// ������ ������ ����������� �� UART ������.
#define UARTLS_BUF_RX_LENGTH 128

/// ������ ������ ������������ �� UART ������.
#define UARTLS_BUF_TX_LENGTH 255  

/// ����� ����� ��������� �������, ��� ������� ���� ����� �� ������ ������ (��).
#define DELAY_RESET 3

/// ����� ����� ��������� �������, ��� ������� ������������ ��������� ������ (��).
#define DELAY_READ 5

/// ��������� ������.
typedef enum {
    STATE_RX_WAIT = 0,  ///< �������� ������ ������ ������. 
    STATE_RX_READ,      ///< ���� ����� ������.
    STATE_RX_READY      ///< ������ �������.
} stateRx_t;

/// ����� ����������� �� UART ������.
unsigned char UARTLS_rxBuf[UARTLS_BUF_RX_LENGTH]; 

/// ����� ������������ �� UART ������.
unsigned char UARTLS_txBuf[UARTLS_BUF_TX_LENGTH]; 

/// ��������� ������.
static stateRx_t stateRx;

// ����� ��������� � ������� ���������� ������ ����� ������.
static uint8_t delay = DELAY_READ; 

// ������� �������� ����
static uint8_t rxCounter = 0;

// ������� ������������ ������
static uint8_t txCounter = 0; 

// ���-�� ������������ ����.
static uint8_t txLen = 0; 

static void push(uint8_t byte);
static void rxIntrOff(void);
static void rxIntrOn(void);
static void txIntrOff(void);
static void txIntrOn(void);

/// ����� ����� ������.
void push(uint8_t byte) {
    if (rxCounter >= UARTLS_BUF_RX_LENGTH) {
        // ������������ ������
        rxCounter = 0;
        stateRx = STATE_RX_WAIT;         
    } else {
        UARTLS_rxBuf[rxCounter++] = byte;
        stateRx = STATE_RX_READ;
    }   
}

/// ��������� ���������� ���������.
void rxIntrOff(void) {
    UCSR1B &= ~(1 << RXCIE1);
}

/// �������� ��������� ���������.
void rxIntrOn(void) {
    UCSR1B |= (1 << RXCIE1);
}

/// ��������� ���������� �����������.
void txIntrOff(void) {
    UCSR1B &= ~((1 << UDRIE1) | (1 << TXCIE1));
}

/// �������� ���������� �����������.
void txIntrOn(void) {
    UCSR1B |= ((1 << UDRIE1) | (1 << TXCIE1));
}

/** ������ ������ ��������� UART.
 *
 */
void UARTLS_rxStart(void) {
    stateRx = STATE_RX_WAIT;
    rxCounter = 0;    
    
    txIntrOff(); 
    rxIntrOn();
}

/** ����� �������� ������.
 *  
 *  ������ ��� �������� ������� ���������� � ����� ��������.
 *  ����������� ���������� �� ����������� ������ � ��������� ��������.
 *
 *  @param[in] len ���������� ������������ ������.
 *  @return ���.
 */
void UARTLS_txStart(uint8_t len) {
   txCounter = 0;
   txLen = len;
   
   // ��� ������� �������� �������� ����������� � ������������ ��� ��������� 
   rxIntrOff();
   stateRx = STATE_RX_WAIT;
   
   UDR1 = UARTLS_txBuf[txCounter++]; 
   txIntrOn();
}

/** ������� �������.
 *
 *  ������ ���������� � �������� 1 ��, ������� �� ����������.
 * 
 *  ������� ��� ����������� ������ �� ��������� Modbus. �� �� ����� �� ��������
 *  �������� � ����������� ��������.
 *  
 *  TODO ��� �� ������� �������� �������� � ����� ������ ������, ��� "���������"
 *  � ������ ��������.
 *
 *  @return ���.
 */
void UARTLS_tick(void) {   
    if (delay <= DELAY_READ)
        delay++;
    
    if (delay >= DELAY_READ) { 
        if (stateRx == STATE_RX_READ) {  
            //���� ����� ��������� ��� ���, ������� ��� ����� ��������
            //���� ���������� ������, �� ������������� �����
            rxIntrOff();
            stateRx = STATE_RX_READY;
        }
    } 
}

/** �������� ������� ��������� ���������.
 *  
 *  @return True ���� ���� �������� ���������, ����� false.
 */
bool UARTLS_isRxData(void) {
    return (stateRx == STATE_RX_READY);
}

/** ���������� ���������� �������� ���� ������.
 *
 *  @return ���������� �������� ���� ������.
 */
uint8_t UARTLS_getDataLen(void) {
    return rxCounter;
}

/// ������������� � ������ ������ ����������������� UART1.
void UARTLS_setup(void) {
    UBRR1L = 51;
    
    // AT_RXD
    DDRD  &= ~(1 << PORTD2);
    PORTD &= ~(1 << PORTD2);
    
    // AT_TXD
    DDRD  |= (1 << PORTD3);
    PORTD |= (1 << PORTD3);
    
    // ��� ����-���� � ������ ������� 8 ��������
    UCSR1C = (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10);
    
    // ����� ������ ��������� � �����������
    UCSR1B = (1 << TXEN1) | (1 << RXEN1); 
}

#pragma vector=USART1_RXC_vect
__interrupt void UART1_RX_interrupt(void) {
    volatile uint8_t byte = UDR1;
     
    if  (UCSR1A & ((1 << FE1) | (1 << DOR1) | (1 << UPE1))) {   
        // ���������� ������
        UARTLS_rxStart();    
    } else {      
        if (delay >= DELAY_READ) {
            // ������ ������ ������
            rxCounter = 0; 
            push(byte);
        } else if (delay < DELAY_RESET) {
            // ����� ������
            push(byte);
        }
    }
    
    // ����� �������� ����� ����� �������
    delay = 0;
}

#pragma vector=USART1_TXC_vect
__interrupt void UART1_TXC_interrupt(void) {   
    UARTLS_rxStart();
}

#pragma vector=USART1_UDRE_vect
__interrupt void UART1_UDRE_interrupt(void) {
    
    if (txCounter < txLen) {
        //���� �� ��� �������� �� ��� �����, �� ���������� ����������
        UDR1 = UARTLS_txBuf[txCounter++];
    } else {  
        // ���� ��� ������ ��������, �������� ���������� �� ����������� ������
        UCSR1B &= ~(1 << UDRIE1);
    }
}