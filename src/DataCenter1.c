#include <ioavr.h>
#include <ina90.h>

#include "DataCenter1.h"
#include "UartBsp.h"
#include "UartLs.h"

/// ������������ ���������� ��������� ��������� ��� ������ � ����� ������.
#define MAX_NUM_HOLDING_REG 32

/// ������������ ���������� ������ ��������� ��� ������ � ����� �������.
#define MAX_NUM_COILS 64

extern unsigned char PCready;
extern unsigned char PCbyte;
extern unsigned char PCtime;

//���������� ����������� ��� �������� ������ �� ModBus
extern bool     bDefAvar;
extern bool     bDefWarn;
extern bool     bGlobalAvar;
extern bool     bGlobalWarn;
extern uint8_t  CurrentState[];
extern uint8_t  DataLCD[];
extern uint16_t eAddressWrite;
extern uint8_t *eMassiveWrite;
extern uint8_t  ePassword[];
extern uint8_t  eWrite;
extern uint8_t  GlobalCurrentState[];
extern int16_t  IlineValue;
extern uint16_t MyInsertion[];
extern uint8_t  TimeLCD[];
extern int8_t   ucf1;
extern int8_t   ucf2;
extern int8_t   udef1;
extern int8_t   udef2;
extern int16_t  UlineValue;

/// ������� ��������� � Modbus.
typedef enum {
    COM_01H_READ_COILS 				= 0x01,	///< ������ ������.
    COM_03H_READ_HOLDING_REGISTERS 	= 0x03,	///< ������ ���������� ���������.
//    COM_06H_WRITE_SINGLE_REGISTER 	= 0x06	///< ������ ������ ����������� ��������.
} comModbus_t;

/// ���� ����������
typedef enum {
    EXCEPTION_01H_ILLEGAL_FUNCTION 	= 0x01,	///< ��� ������� �� ��������������
    EXCEPTION_02H_ILLEGAL_DATA_ADR 	= 0x02,	///< �������� ����� ��������
    EXCEPTION_03H_ILLEGAL_DATA_VAL 	= 0x03,	///< �������� �������� ���� ������
    EXCEPTION_04H_DEVICE_FAILURE 	= 0x04	///< � ���������� ��������� ������
} exceptionModbus_t;

/// ������ ���������.
typedef enum {
    ADR_HOLDING_REG_MIN         = 0,
    // ���� � �����
    ADR_HOLDING_REG_YEAR        = 1,    ///< ���.
    ADR_HOLDING_REG_MONTH,			    ///< �����.
    ADR_HOLDING_REG_DAY,			    ///< ����.
    ADR_HOLDING_REG_HOUR,			    ///< ����.
    ADR_HOLDING_REG_MINUTE,			    ///< ������.
    ADR_HOLDING_REG_SECOND,		        ///< �������.
    // ������� ��������� 
    ADR_HOLDING_REG_GLB_FAULT   = 10,   ///< ��� ������������� �����.
    ADR_HOLDING_REG_GLB_WARNING,		///< ��� �������������� �����.
    ADR_HOLDING_REG_DEF_FAULT   = 22,	///< ��� ������������� ������.
    ADR_HOLDING_REG_DEF_WARNING,		///< ��� �������������� ������.
    ADR_HOLDING_REG_DEF_REGIME,			///< ����� ������.
    ADR_HOLDING_REG_DEF_STATE,			///< ��������� ������.
    // ��������
    ADR_HOLDING_REG_MEAS_U_OUT 	= 123,	///< �������� ����������.
    ADR_HOLDING_REG_MEAS_I_OUT,			///< �������� ���.
    ADR_HOLDING_REG_MEAS_UC1,			///< ����� �� U� (U�1).
    ADR_HOLDING_REG_MEAS_UC2,			///< ����� �� U�2.
    ADR_HOLDING_REG_MEAS_UD1    = 129,	///< ����� �� U� (U�1).
    ADR_HOLDING_REG_MEAS_UD2,			///< ����� �� U�2.
    // ������ ��������
    ADR_HOLDING_REGIC_BSP_MCU 	= 156,	///< ������ �������� �� ����� ���.
    ADR_HOLDING_REGIC_BSP_DSP,			///< ������ �������� DSP ����� ���.
    ADR_HOLDING_REGIC_PI_MCU,			///< ������ �������� �� ����� ��.
    ADR_HOLDING_REGIC_BSZ       = 163,	///< ������ �������� ���� ����� ���.
    // ������������ ���-�� ������������ ������� ���������
    ADR_HOLDING_REG_MAX
} adrHoldingReg_t;

/// ������ ������.
typedef enum {
    ADR_COIL_MIN        = 200,
    // ������� ���������
    ADR_COIL_FAULT 		= 201,	///< ������� �������������.
	ADR_COIL_WARNING,			///< ������� ��������������.
    //
    ADR_COIL_MAX 
} adrCoil_t;

//������� ��� �������� ������� ���� CRC-16
__flash const uint8_t srCRCHi[256] = {
         0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
         0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
         0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
         0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
         0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
         0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
         0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
         0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
         0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
         0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
         0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
         0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
         0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
         0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
         0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
         0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
         0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
         0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
         0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
         0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
         0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
         0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
         0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
         0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
         0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
         0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};

__flash const uint8_t srCRCLo[256] = {
         0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
         0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
         0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
         0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
         0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
         0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
         0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
         0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
         0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
         0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
         0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
         0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
         0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
         0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
         0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
         0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
         0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
         0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
         0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
         0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
         0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
         0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
         0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
         0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
         0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
         0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};


/** ������� ����������� ����� CRC-16.
 *
 *  ���� ������� ������������ ��� �������� �� ��������� ���������, �� 
 *  �� ���������� ���� ������ num ���������� ��������� ����� ��.
 *
 *  @param[in] buf
 *  @param[in] num ���������� ���� ������.
 */
uint16_t MODBUS_calcCRC(uint8_t *buf, uint8_t num) {
    uint8_t low = 0xFF;
    uint8_t high = 0xFF;
    
    for (uint8_t i = 0; i < num; i++) {
        uint8_t carry = low ^ buf[i];
        
        low = high ^ srCRCHi[carry];
        high = srCRCLo[carry];
    }
    
    return ((high << 8) | low);
}


/** ������� ����������� �����.
 * 
 *  ����������� �� �����������. 
 *  ���� ������� ������������ ��� �������� �� ��������� ���������, �� 
 *  �� ���������� ���� ������ num ���������� ��������� ���� ��.
 *
 *  @param[in] buf
 *  @param[in] num ���������� ���� ������.
 */
uint8_t STD_calcCrc(uint8_t *buf, uint8_t num) {
    uint8_t crc = 0;
    
    for(uint8_t i = 2; i < num; i++) {
        crc += buf[i];
    }
    
    return crc;
}

/** �������� ���������.
 *
 *  @param[in] adr ����� � ��������� ����.
 *  @param[in] com �������.
 *  @param[in] numBytes ���������� ������������ �������� ������.
 */
void STD_txData(uint8_t adr, uint8_t com, uint8_t numBytes) {
    uint8_t crc = 0;
    
    UARTLS_txBuf[0] = 0x55;
    UARTLS_txBuf[1] = 0xAA;
    UARTLS_txBuf[2] = com;
    UARTLS_txBuf[3] = numBytes;
    crc = STD_calcCrc(UARTLS_txBuf, 4 + numBytes);
    UARTLS_txBuf[4 + numBytes] = crc;
    UARTLS_txStart(5 + numBytes); 
}

/** �������� ���������.
 *    
 *  ��������� ������������ ������:
 *  - ����� (adr);
 *  - ������� (com);
 *  - ���������� ������������ ���� ������ (numBytes);
 *  - crc (2 �����).  
 *
 *  @param[in] numBytes ���������� ������������ �������� ������.
 */
void MODBUS_txData(uint8_t numBytes) {
    uint16_t crc = 0;
    
    UARTLS_txBuf[0] = UARTLS_rxBuf[0];
    UARTLS_txBuf[1] = UARTLS_rxBuf[1];
    UARTLS_txBuf[2] = numBytes;
    crc = MODBUS_calcCRC(UARTLS_txBuf, 3 + numBytes);
    UARTLS_txBuf[3 + numBytes] = crc;
    UARTLS_txBuf[4 + numBytes] = (crc >> 8);
    UARTLS_txStart(5 + numBytes);
}

/** �������� ��������� �� ������.
 *
 *  ������ ���������� ��� ����� ������.
 *
 *  @param[in] adr ����� � ��������� ����.
 *  @param[in] code ��� ������.
 *  @param[in] byte1 ���� ������ 1.
 *  @param[in] byte2 ���� ������ 2.
 */
void STD_txError(uint8_t adr, uint8_t code, uint8_t byte1, uint8_t byte2) {
    uint16_t crc = 0;
    
    UARTLS_txBuf[0] = 0x55;
    UARTLS_txBuf[1] = 0xAA;
    UARTLS_txBuf[2] = code;
    UARTLS_txBuf[3] = 0x02; 
    crc = STD_calcCrc(UARTLS_txBuf, 6);
    UARTLS_txBuf[6] = crc;
    UARTLS_txStart(7);
}

/**	���������� ��������� ����� ��������/����� � �������.
*
* 	@return ��������� ����� �������� ��� ����� � �������� �������.
*/
uint16_t MODBUS_getStartAddress() {
		return ((uint16_t) UARTLS_rxBuf[2] << 8) + UARTLS_rxBuf[3] + 1;
}

/**	���������� ���������� ���������/������ � �������.
*
* 	@return ���������� ���������/������ � �������.
*/
uint16_t MODBUS_getNumOfAddress() {
    return ((uint16_t) UARTLS_rxBuf[4] << 8) + UARTLS_rxBuf[5];
}

/** �������� ��������� �� ������.
 *
 *  ������ ���������� ��� ����� ������.
 *
 *  @param[in] code ��� ������.
 */
void MODBUS_txError(exceptionModbus_t exception) {
    uint16_t crc = 0;
    
    UARTLS_txBuf[0] = UARTLS_rxBuf[0];
    UARTLS_txBuf[1] = UARTLS_rxBuf[1] | 0x80;
    UARTLS_txBuf[2] = exception;
    crc = MODBUS_calcCRC(UARTLS_txBuf, 3);
    UARTLS_txBuf[3] = crc;
    UARTLS_txBuf[4] = (crc >> 8);
    UARTLS_txStart(5);
}
   
/** ��������� ��������� ��������� ��������� ��������.
 *    
 *  @param[in] num ���������� �������� ���� ������.
 */
void STD_rxProc(uint8_t adr, uint8_t num) {
    bool err = false;
    
    // �������� ������� �����������.
    err |= (UARTLS_rxBuf[0] != 0x55);
    
    // �������� ������� �����������.
    err |= (UARTLS_rxBuf[1] != 0xAA);
         
    // �������� ����������� � ��������� ���������� ���� ������.
    err |= (UARTLS_rxBuf[3] != (num - 5));
    
    // �������� ����������� �����.
    err |= (UARTLS_rxBuf[num - 1] != STD_calcCrc(UARTLS_rxBuf, num - 1));
    
    if (err) {
        UARTLS_rxStart();
    } else {
        if (UARTLS_rxBuf[2] == 0x73) {
            // ��������� ������.
            uint16_t pwd = (UARTLS_rxBuf[4] << 8) + UARTLS_rxBuf[5];       
            for(uint8_t i = 4; i > 0; i--) {
                ePassword[i - 1] = (pwd % 10) + '0';
                pwd /= 10;
            }
            
            STD_txData(adr, 0x73, 0);
            
            // ������ ������ � EEPROM
            eWrite = 1;
            eAddressWrite = 0;
            eMassiveWrite = ePassword;
        } else if (UARTLS_rxBuf[2] == 0x74) {
            // ���������� ������.
            uint16_t pwd = 0;
            for(uint8_t i = 0; i < 4; i++) {
                pwd *= 10;
                pwd += ePassword[i] - '0';
            }
            
            UARTLS_txBuf[4] = (pwd >> 8);
            UARTLS_txBuf[5] = pwd; 
            
            STD_txData(adr, 0x72, 2);
        } else {
            // ��������� ��������� � �� ���.
            for (uint8_t i = 0; i < num; i++) {
                Tr_buf_data_uart[i] = UARTLS_rxBuf[i];
                UARTLS_rxBuf[i] = 0x00;
            }
            
            PCbyte = num;
            PCready = 1;
        }
    }    
}

/** ���������� ��������� ���� � �������.
 *
 *  ��-��������� ���������� 0xFFFF.
 *
 *  @param[in] reg ����� ��������.
 *  @return �������� ��������.
 */
uint16_t MODBUS_readHoldingRegDateTime(adrHoldingReg_t reg) {
    uint16_t val = 0xFFFF;
    
    switch(reg) {
        case ADR_HOLDING_REG_YEAR: {     
            if ((DataLCD[6] != '?') && (DataLCD[7] != '?')) {                
                val = (DataLCD[6] - '0')*10 + (DataLCD[7] - '0');
            }
        } break;
        
        case ADR_HOLDING_REG_MONTH: {
            if ((DataLCD[3] != '?') && (DataLCD[4] != '?')) {                
                val = (DataLCD[3] - '0')*10 + (DataLCD[4] - '0');
            }
        } break;
        
        case ADR_HOLDING_REG_DAY: {
            if ((DataLCD[0] != '?') && (DataLCD[1] != '?')) {                
                val = (DataLCD[0] - '0')*10 + (DataLCD[1] - '0');
            }
        } break;
        
        case ADR_HOLDING_REG_HOUR: {
            if ((TimeLCD[0] != '?') && (TimeLCD[1] != '?')) {                
                val = (TimeLCD[0] - '0')*10 + (TimeLCD[1] - '0');
            }
        } break;
        
        case ADR_HOLDING_REG_MINUTE: {
            if ((TimeLCD[3] != '?') && (TimeLCD[4] != '?')) {                
                val = (TimeLCD[3] - '0')*10 + (TimeLCD[4] - '0');
            }
        } break;
        
        case ADR_HOLDING_REG_SECOND: {
            if ((TimeLCD[6] != '?') && (TimeLCD[7] != '?')) {                
                val = (TimeLCD[6] - '0')*10 + (TimeLCD[7] - '0');
            }
        } break;
    }
    
    return val;
}

/** ���������� ��������� ���������.
 *
 *  ��-��������� ���������� 0xFFFF.
 *
 *  @param[in] reg ����� ��������.
 *  @return �������� ��������.
 */
uint16_t MODBUS_readHoldingRegState(adrHoldingReg_t reg) {
    uint16_t val = 0xFFFF;
    
    switch(reg) {
        case ADR_HOLDING_REG_GLB_FAULT: {
            val = (GlobalCurrentState[12] << 8) + GlobalCurrentState[13];
        } break;
        
        case ADR_HOLDING_REG_GLB_WARNING: {
            val = (GlobalCurrentState[14] << 8) + GlobalCurrentState[15];
        } break;
        
        case ADR_HOLDING_REG_DEF_FAULT: {
            val = (GlobalCurrentState[0] << 8) + GlobalCurrentState[1];
        } break;
        
        case ADR_HOLDING_REG_DEF_WARNING: {
            val = (GlobalCurrentState[2] << 8) + GlobalCurrentState[3];
        } break;
        
        case ADR_HOLDING_REG_DEF_REGIME: {
            val = CurrentState[0];
        } break;
        
        case ADR_HOLDING_REG_DEF_STATE: {
            val = CurrentState[1];
        } break;
    }
    
    return val;
}

/** ���������� ��������� ���������� ����������.
 *
 *  ��-��������� ���������� 0xFFFF.
 *
 *  @param[in] reg ����� ��������.
 *  @return �������� ��������.
 */
uint16_t MODBUS_readHoldingRegMeasure(adrHoldingReg_t reg) {
    uint16_t val = 0xFFFF;
    
    switch(reg) {
        case ADR_HOLDING_REG_MEAS_U_OUT: {
            val = UlineValue;
        } break;            
        
        case ADR_HOLDING_REG_MEAS_I_OUT: {
            val = IlineValue;
        } break;
        
        case ADR_HOLDING_REG_MEAS_UC1: {
            val = ucf1;
        } break;
        case ADR_HOLDING_REG_MEAS_UC2: {
            val = ucf2;
        } break;
        case ADR_HOLDING_REG_MEAS_UD1: {
            val = udef1;
        } break;
        case ADR_HOLDING_REG_MEAS_UD2: {
            val = udef2;
        } break;
    }
    
    return val;
}

/** ���������� ��������� ������ ��������.
 *
 *  ��-��������� ���������� 0xFFFF.
 *
 *  @param[in] reg ����� ��������.
 *  @return �������� ��������.
 */
uint16_t MODBUS_readHoldingRegVersionIC(adrHoldingReg_t reg) {
    uint16_t val = 0xFFFF;
    
    switch(reg) {
        case ADR_HOLDING_REGIC_BSP_MCU: {
            val = MyInsertion[1];
        } break;
        case ADR_HOLDING_REGIC_BSP_DSP: {
            val = MyInsertion[2];
        } break;
        case ADR_HOLDING_REGIC_PI_MCU: {
            val = MyInsertion[0];
        } break;
        case ADR_HOLDING_REGIC_BSZ: {
            val = MyInsertion[3];
        } break;
    }
    
    return val;
}

/** ���������� ������ ���������.
 *
 *  ��-��������� ����� ���������� false.
 *
 *  @param[in] coil ����� �����.
 *  @return �������� �����.
 */
bool MODBUS_readCoilState(adrCoil_t coil) {
    bool val = false;
    
    switch(coil) {
        case ADR_COIL_FAULT: {
            val = bGlobalAvar | bDefAvar;
        } break;
        
        case ADR_COIL_WARNING: {
            val = bGlobalWarn | bDefWarn;
        } break;
    }
    
    return val;
}

/// ������ ������.
void MODBUS_readCoils() {
    uint16_t adr = MODBUS_getStartAddress();	// ��������� �����
	uint16_t num = MODBUS_getNumOfAddress();	// ���-�� �������
    
    // �������� ���������� ������
	if ((num == 0) || (num > MAX_NUM_COILS)) {
        MODBUS_txError(EXCEPTION_03H_ILLEGAL_DATA_VAL);
		return;
	} 
    
    // �������� ������ ������� �����
    if ((adr <= ADR_COIL_MIN) || ((adr + num - 1) >= ADR_COIL_MAX)) {
        MODBUS_txError(EXCEPTION_02H_ILLEGAL_DATA_ADR);
		return;
    }
    
    for(uint8_t i = 0; i < num; i++) {
        bool val = false;
        
        adrCoil_t coil = (adrCoil_t) (adr + i);
        
        if (coil >= ADR_COIL_FAULT) {
            val = MODBUS_readCoilState(coil);
        }
        
        // ��������� ��� ����������� ������ ������������� ������
        if ((i % 8) == 0) {
            UARTLS_txBuf[3 + i/8] = 0x00;
        }
        
        if (val) {
            UARTLS_txBuf[3 + i/8] |= (1 << (i % 8));
        }
    }
    
    MODBUS_txData((num + 7) / 8);
}

/// ������ ���������.
void MODBUS_readHoldingRegs(void) {
    uint16_t adr = MODBUS_getStartAddress();	// ��������� �����
	uint16_t num = MODBUS_getNumOfAddress();	// ���-�� �������
    
    // �������� ���������� ���������
	if ((num == 0) || (num > MAX_NUM_HOLDING_REG)) {
        MODBUS_txError(EXCEPTION_03H_ILLEGAL_DATA_VAL);
		return;
	}    
    
    // �������� ������� ���������
    if ((adr <= ADR_HOLDING_REG_MIN) || ((adr + num - 1) >= ADR_HOLDING_REG_MAX)) {
        MODBUS_txError(EXCEPTION_02H_ILLEGAL_DATA_ADR);
		return;
    }

    for(uint8_t i = 0; i < num; i++) {
        uint16_t val = 0xFFFF;
        
        adrHoldingReg_t reg = (adrHoldingReg_t) (adr + i);
        
        if (reg >= ADR_HOLDING_REGIC_BSP_MCU) {
            val = MODBUS_readHoldingRegVersionIC(reg);
        } else if (reg >= ADR_HOLDING_REG_MEAS_U_OUT) {
            val = MODBUS_readHoldingRegMeasure(reg);
        } else if (reg >= ADR_HOLDING_REG_GLB_FAULT) {
            val = MODBUS_readHoldingRegState(reg);
        } else if (reg >= ADR_HOLDING_REG_YEAR) {
            val = MODBUS_readHoldingRegDateTime(reg);            
        }
        
        UARTLS_txBuf[3 + i*2] = val >> 8;
        UARTLS_txBuf[4 + i*2] = val;
    }
    
    MODBUS_txData(num * 2);
}

/// ������ ��������.
void MODBUS_writeSingleReg(void) {
        
    UARTLS_rxStart();
}

/** ��������� ��������� ��������� ��������� Modbus.
 *
 *  @param[in] adr ����� ���������� � ��������� ����.
 *  @param[in] num ���������� �������� ���� ������.
 *  @return ���.
 */
void MODBUS_rxProc(uint8_t adr, uint8_t num) {
    bool err = false;
      
    // �������� ������ ����������.
    err |= (UARTLS_rxBuf[0] != adr);
    
    // �������� ����������� �����.
    uint16_t crcCalc = MODBUS_calcCRC(UARTLS_rxBuf, num - 2);
    uint16_t crcRead = (UARTLS_rxBuf[num - 1] << 8) + (UARTLS_rxBuf[num - 2]);
    err |= (crcCalc != crcRead);
    
    if (err) {      
        // � ������ ������ ���� ��������� ���������.
        UARTLS_rxStart();         
    } else {
        switch((comModbus_t) UARTLS_rxBuf[1]){
            case COM_01H_READ_COILS: {
                MODBUS_readCoils();
            } break;
            
            case COM_03H_READ_HOLDING_REGISTERS: {
                MODBUS_readHoldingRegs();
            } break;
            
//            case COM_06H_WRITE_SINGLE_REGISTER:{
//                MODBUS_writeSingleReg();
//            } break;
//            
            default:  {
                MODBUS_txError(EXCEPTION_01H_ILLEGAL_FUNCTION);
            } 
        }  
    }
}

/** ��������� �������� ������.
 *
 *  @param[in] protocol �������� ������ � ��������� ����.
 *  @param[in] adr ����� ���������� � ��������� ����.
 *  @param[in] num ���������� �������� ���� ������.
 */
void DC1_dataProc(protocol_t protocol, uint8_t adr, uint8_t num) {
    switch (protocol) {
        case PROTOCOL_S: {
            STD_rxProc(adr, num);
        } break;
        
        case PROTOCOL_MODBUS: {
            MODBUS_rxProc(adr, num);
        } break;
        
        default: {
            UARTLS_rxStart();
        }
    }
}


