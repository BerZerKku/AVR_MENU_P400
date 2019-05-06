#include <ioavr.h>
#include <ina90.h>

#include "DataCenter1.h"
#include "UartBsp.h"
#include "UartLs.h"
#include "modbus.h"

extern BazaModBus* ModBusBaza;

extern unsigned char ePassword[];
extern unsigned char eWrite, eRead;
extern unsigned char *eMassiveWrite, *eMassiveRead;
extern unsigned int eAddressWrite,eAddressRead;

//переменные необходимые для передачи данных по ModBus
extern unsigned char ReadArch;
extern unsigned char NumberRec; //ко-во считываемых записей
extern unsigned char ComArch;  //команда считывания архива

extern unsigned char CurrentState[];
extern unsigned char LCD2new, gr1, gr2;

extern void FTest1(unsigned char com);

void errorMsg(protocol_t prot, uint8_t code, uint8_t byte1, uint8_t byte2);

//массивы для быстрого расчета кода CRC-16
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


/** Рассчет контрольной суммы CRC-16.
 *
 *  Если функция используется для проверки КС принятого сообщения, то 
 *  из количества байт данных num необходимо исключить байты КС.
 *
 *  @param[in] buf
 *  @param[in] num Количество байт данных.
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


/** Рассчет контрольной суммы.
 * 
 *  Синхробайты не учитываются. 
 *  Если функция используется для проверки КС принятого сообщения, то 
 *  из количества байт данных num необходимо исключить байт КС.
 *
 *  @param[in] buf
 *  @param[in] num Количество байт данных.
 */
uint8_t STD_calcCrc(uint8_t *buf, uint8_t num) {
    uint8_t crc = 0;
    
    for(uint8_t i = 2; i < num; i++) {
        crc += buf[i];
    }
    
    return crc;
}

/** Отправка сообщения.
 *
 *  @param[in] adr Адрес в локальной сети.
 *  @param[in] com Команда.
 *  @param[in] numBytes Количество передаваемых полезных данных.
 *  @return Нет.
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

/** Отправка сообщения.
 *
 *  @param[in] adr Адрес в локальной сети.
 *  @param[in] com Команда.
 *  @param[in] numBytes Количество передаваемых полезных данных.
 *  @return Нет.
 */
void MODBUS_txData(uint8_t adr, uint8_t com, uint8_t numBytes) {
    uint16_t crc = 0;
    
    UARTLS_txBuf[0] = adr;
    UARTLS_txBuf[1] = com; 
    UARTLS_txBuf[2] = numBytes;
    crc = MODBUS_calcCRC(UARTLS_txBuf, 3 + numBytes);
    UARTLS_txBuf[3 + numBytes] = crc;
    UARTLS_txBuf[4 + numBytes] = (crc >> 8);
    UARTLS_txStart(5 + numBytes);
}

/** Отправка сообщения об ошибке.
 *
 *  Всегда передается два байта данных.
 *
 *  @param[in] adr Адрес в локальной сети.
 *  @param[in] code Код ошибки.
 *  @param[in] byte1 Байт данных 1.
 *  @param[in] byte2 Байт данных 2.
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


/** Отправка сообщения об ошибке.
 *
 *  Всегда передается два байта данных.
 *
 *  @param[in] adr Адрес в локальной сети.
 *  @param[in] code Код ошибки.
 *  @param[in] byte1 Байт данных 1.
 *  @param[in] byte2 Байт данных 2.
 */
void MODBUS_txError(uint8_t adr, uint8_t code, uint8_t byte1, uint8_t byte2) {
    uint16_t crc = 0;
    
    UARTLS_txBuf[0] = adr; 
    UARTLS_txBuf[1] = UARTLS_rxBuf[1] | 0x80;
    UARTLS_txBuf[2] = code;
    crc = MODBUS_calcCRC(UARTLS_txBuf, 3);
    UARTLS_txBuf[3] = crc;
    UARTLS_txBuf[4] = (crc >> 8);
    UARTLS_txStart(5);
}

    
/** Обработка принятого сообщения протокола Стандарт.
 *    
 *  @param[in] num Количество принятых байт данных.
 *  @return Нет.
 */
void STD_rxProc(uint8_t adr, uint8_t num) {
    bool err = false;
    
    // Проверка первого синхробайта.
    err |= (UARTLS_rxBuf[0] != 0x55);
    
    // Проверка второго синхробайта.
    err |= (UARTLS_rxBuf[1] != 0xAA);
         
    // Проверка заявленного в сообщении количества байт данных.
    err |= (UARTLS_rxBuf[3] != (num - 5));
    
    // Проверка контрольной суммы.
    err |= (UARTLS_rxBuf[num - 1] != STD_calcCrc(UARTLS_rxBuf, num - 1));
    
    if (err) {
        UARTLS_rxStart();
    } else {
        if (UARTLS_rxBuf[2] == 0x73) {
            // Изменение пароля.
            uint16_t pwd = (UARTLS_rxBuf[4] << 8) + UARTLS_rxBuf[5];       
            for(uint8_t i = 4; i > 0; i--) {
                ePassword[i - 1] = (pwd % 10) + '0';
                pwd /= 10;
            }
            
            STD_txData(adr, 0x73, 0);
            
            // запись пароля в EEPROM
            eWrite = 1;
            eAddressWrite = 0;
            eMassiveWrite = ePassword;
        } else if (UARTLS_rxBuf[2] == 0x74) {
            // Считывание пароля.
            uint16_t pwd = 0;
            for(uint8_t i = 0; i < 4; i++) {
                pwd *= 10;
                pwd += ePassword[i] - '0';
            }
            
            UARTLS_txBuf[4] = (pwd >> 8);
            UARTLS_txBuf[5] = pwd; 
            
            STD_txData(adr, 0x72, 2);
        } else {
            // Пересылка сообщения в МК БСП.
            for (uint8_t i = 0; i < num; i++) {
                Tr_buf_data_uart[i] = UARTLS_rxBuf[i];
                UARTLS_rxBuf[i] = 0x00;
            }
            
            PCbyte = num;
            PCready = 1;
        }
    }    
}
 
/** Обработка принятого сообщения протокола Modbus.
 *
 *  @param[in] adr Адрес устройства в локальной сети.
 *  @param[in] num Количество принятых байт данных.
 *  @return Нет.
 */
void MODBUS_rxProc(uint8_t adr, uint8_t num) {
    uint8_t NumberRegister; //количество считываемых регистров
    uint8_t StRegister;
    uint16_t AddressStartRegister; //адрес первого регистра
    uint16_t NumRecStart; //номер первой считываемой записи
    
    
    // Проверка адреса устройства.
    if (UARTLS_rxBuf[0] != adr) {
        UARTLS_rxStart();
        return;
    }
    
    // Проверка контрольной суммы.
    uint16_t crcCalc = MODBUS_calcCRC(UARTLS_rxBuf, num - 2);
    uint16_t crcRead = (UARTLS_rxBuf[num - 1] << 8) + (UARTLS_rxBuf[num - 2]);    
    if (crcCalc != crcRead) {       
        UARTLS_rxStart();
        return;
    }
    
    // FIXME Сделать обработку принятого сообщения Modbus!
    UARTLS_rxStart();

//    AddressStartRegister=(UARTLS_rxBuf[2]<<8)+UARTLS_rxBuf[3];
//    NumberRegister=UARTLS_rxBuf[5];
//    switch(UARTLS_rxBuf[1]){
//        case 0x03:{
//            if ((NumberRegister>64)||(NumberRegister==0)) ErrorMessageModBus(0x03); //кол-во запрашиваемых данных выходит из допустимого диапазона
//            else
//            {
//                //проверка на достоверность указанных регистров ModBus
//                if (((AddressStartRegister>=250)&&(AddressStartRegister<1024))||((AddressStartRegister+NumberRegister>250)&&(AddressStartRegister<1024))){
//                    ErrorMessageModBus(0x02);
//                }else{
//                    UARTLS_txBuf[2]=NumberRegister*2;
//                    if (AddressStartRegister<250){ //все кроме архивов
//                        for (uint8_t i = 0; i < NumberRegister; i++) {
//                            ModBusBaza->readregister(UARTLS_txBuf, 3 + i*2, AddressStartRegister + i);
//                        }
//                        TransDataInf1(0x03, NumberRegister*2);
//                    }else
//                        if ((AddressStartRegister>=0x400)&&(AddressStartRegister<0x2200)){  //архив событий
//                            ReadArch = 1;
//                            ModBusBaza->NumberRecordingArchive(0); //
//                            NumberRec = NumberRegister/15;
//                            if (NumberRec==0) NumberRec++;
//                            if ((15-(AddressStartRegister-1024)%15)<NumberRegister) NumberRec++;
//                            NumRecStart=(AddressStartRegister-1024)/15;
//                            ComArch=0xF2;
//                            //ErrorMessageModBus(0x03);
//                        }else
//                            if ((AddressStartRegister>=0x2400)&&(AddressStartRegister<0x4200)){  //архив Поста
//                                ReadArch = 1;
//                                ModBusBaza->NumberRecordingArchive(0); //
//                                NumberRec = NumberRegister/15;
//                                if (NumberRec==0) NumberRec++;
//                                StRegister=(AddressStartRegister - 0x2400)%15;
//                                if ((15-StRegister)<NumberRegister) NumberRec++;
//                                NumRecStart=(AddressStartRegister-0x2400)/15;
//                                ComArch=0xC2;
//                            }else
//                                if ((AddressStartRegister>=0x4400)&&(AddressStartRegister<0x6200)){  //архив ПРМ
//                                    ReadArch = 1;
//                                    ModBusBaza->NumberRecordingArchive(0); //
//                                    NumberRec = NumberRegister/15;
//                                    if (NumberRec==0) NumberRec++;
//                                    StRegister=(AddressStartRegister - 0x4400)%15;
//                                    if ((15-StRegister)<NumberRegister) NumberRec++;
//                                    NumRecStart=(AddressStartRegister-0x4400)/15;
//                                    ComArch=0xD2;
//                                }else
//                                    if ((AddressStartRegister>=0x6400)&&(AddressStartRegister<0x8200)){  //архив ПРД
//                                        ReadArch = 1;
//                                        ModBusBaza->NumberRecordingArchive(0); //
//                                        NumberRec = NumberRegister/15;
//                                        if (NumberRec==0) NumberRec++;
//                                        StRegister=(AddressStartRegister - 0x6400)%15;
//                                        if ((15-StRegister)<NumberRegister) NumberRec++;
//                                        NumRecStart=(AddressStartRegister-0x6400)/15;
//                                        ComArch=0xE2;
//                                    }
//                }
//            }
//        }break;
//        case 0x06:{
//            ModBusBaza->writetoAT(AddressStartRegister,(UARTLS_rxBuf[4]<<8) + UARTLS_rxBuf[5]);
//            for (uint8_t i = 0; i < 6; i++) {
//                UARTLS_txBuf[i] = UARTLS_rxBuf[i];
//            }
//            TransDataInf1(0x06, 4-1);
//        }break;
//        default:  {ErrorMessageModBus(0x01);} //команда не поддерживается данным устройством
//    }  
}

/** Обработка принятых данных.
 *
 *  @param[in] protocol Протокол работы в локальной сети.
 *  @param[in] adr Адрес устройства в локальной сети.
 *  @param[in] num Количество принятых байт данных.
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


