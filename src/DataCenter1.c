

#include "ioavr.h"
#include "MyDef.h"
#include "InterfaceS.h"
#include "modbus.h"

extern BazaModBus ModBusBaza;

unsigned int CRCSum1, CRCread;
unsigned char i_dc1;
extern unsigned char ePassword[];
unsigned int PassToPC;
extern unsigned char eWrite, eRead;
extern unsigned char *eMassiveWrite, *eMassiveRead;
extern unsigned int eAddressWrite,eAddressRead;
extern unsigned char Protocol;

//переменные необходимые для передачи данных по ModBus
unsigned char NumberRegister; //количество считываемых регистров
extern unsigned char ReadArch;
unsigned int AddressStartRegister; //адрес первого регистра
unsigned int NumRecStart; //номер первой считываемой записи
extern unsigned char NumberRec; //ко-во считываемых записей
extern unsigned char ComArch;  //команда считывания архива
unsigned char StRegister;

extern unsigned char CurrentState[];
extern unsigned char LCD2new, gr1, gr2;

extern void FTest1(unsigned char com);

//буфер данных для ModBus
//nsigned int BufModBus[150];
unsigned char AddressModBus=0x20; //адрес устройства в протоколе ModBus

//массивы для быстрого расчета кода CRC-16
__flash const unsigned char srCRCHi[256]={
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
__flash const unsigned char srCRCLo[256]={
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


//функция вычисляет код CRC-16
//на входе указатель на начало буфера
//и количество байт сообщения (без принятого кода CRC-16)
int GetCRC16(unsigned char *buf, char bufsize)
{
  char CRC_Low = 0xFF;
  char CRC_High = 0xFF;
  char k;
  char carry;
  for (k=0; k<bufsize; k++)
   {
    carry = CRC_Low ^ buf[k];
    CRC_Low = CRC_High ^ srCRCHi[carry];
    CRC_High = srCRCLo[carry];
   };
  //return (CRC_High);
  return((CRC_High<<8)|CRC_Low);
}



//функция вычисляет код CRC-16
//на входе указатель на начало буфера
//и количество байт сообщения (без принятого кода CRC-16)
//но при этом синхробайты не считаются
unsigned char GetCRCSum1(unsigned char *buf, char bufsize)
{
  unsigned char CRCbuf;
  unsigned char k;

  CRCbuf=0;
  switch(Protocol)
  {
    case 0:
    {
      for (k=2; k<bufsize; k++)
      {
        CRCbuf+=buf[k];
      };
    }
    break;
    case 1:
    {
      for (k=0;k<bufsize; k++) CRCbuf+=buf[k];
    }
    break;
  }

  return(CRCbuf);
}

//подпрограмма подготовки отпраки одного байта информации по UART
void TransDataByte1(unsigned char ByteCommand, unsigned char ByteData)
{
      Sost1|=CurSost;
    //байты синхронизации уже лежат в массиве
      Tr_buf_data_uart1[2]=ByteCommand;
      Tr_buf_data_uart1[3]=0x01;
      Tr_buf_data_uart1[4]=ByteData;
      CRCSum1=GetCRCSum1(Tr_buf_data_uart1,5);
      Tr_buf_data_uart1[5]=CRCSum1;
      StartTrans1(6);
}

void TransDataInf1(unsigned char ByteCommand, unsigned char NumberTransByte)
{
      Sost1|=CurSost;
      switch(Protocol)
      {
        case 0:
        {
          //байты синхронизации уже лежат в массиве
          Tr_buf_data_uart1[2]=ByteCommand;
          Tr_buf_data_uart1[3]=NumberTransByte;
          CRCSum1=GetCRCSum1(Tr_buf_data_uart1,4+NumberTransByte);
          Tr_buf_data_uart1[4+NumberTransByte]=CRCSum1;
          StartTrans1(5+NumberTransByte);
        }
        break;
        case 1:
        {
          //при считывании, в [2] ложится кол-во байт
          Tr_buf_data_uart1[0]=AddressModBus;
          Tr_buf_data_uart1[1]=ByteCommand; //команда
          CRCSum1=GetCRC16(Tr_buf_data_uart1,3+NumberTransByte);
          Tr_buf_data_uart1[3+NumberTransByte]=CRCSum1;
          Tr_buf_data_uart1[4+NumberTransByte]=(CRCSum1>>8);
          StartTrans1(5+NumberTransByte);
        }
        break;
     }
}



//возвращаем сообщение с ошибкой
void ErrorMessage1(char code)
{
      Sost1|=CurSost;
    //байты синхронизации уже лежат в массиве
      Tr_buf_data_uart1[2]=code;
      Tr_buf_data_uart1[3]=0x02; //т.е. посылается два байта данных
      CRCSum1=GetCRCSum1(Tr_buf_data_uart1,6);
      Tr_buf_data_uart1[6]=CRCSum1;
      StartTrans1(7);
}

void ErrorMessageModBus(char code)
{
  Sost1|=CurSost;
  Tr_buf_data_uart1[0]=AddressModBus; //адрес устройства
  Tr_buf_data_uart1[1]=Rec_buf_data_uart1[1]|0x80;
  Tr_buf_data_uart1[2]=code;
  CRCSum1=GetCRCSum1(Tr_buf_data_uart1,3);
  Tr_buf_data_uart1[3]=CRCSum1;
  Tr_buf_data_uart1[4]=(CRCSum1>>8);
  StartTrans1(5);
}

//обработка принятого сообщения
void DataModBus1(unsigned char NumberByte)
{

      if (GetSostPort1()&HardError)  //если произошла ошибка приема
        {
          Tr_buf_data_uart1[4]=0;
          Tr_buf_data_uart1[5]=0;
          ErrorMessage1(0xE1);
        }
      else
        {
          switch (Protocol)
          {
            case 0:
            {
              if ((Rec_buf_data_uart1[0]==0x55)&&(Rec_buf_data_uart1[1]==0xAA))  //проверка байт синхронизации
              {
                if (Rec_buf_data_uart1[3]!=NumberByte-5) //сравним принятое количество байт данных с заявленным
                {
                    Tr_buf_data_uart1[4]=Rec_buf_data_uart1[3]; //заявленное кол-во байт данных
                    Tr_buf_data_uart1[5]=NumberByte-5; //принятое кол-во байт данных
                    ErrorMessage1(0xE3);
                }
                else
                {
                  CRCSum1=GetCRCSum1(Rec_buf_data_uart1,NumberByte-1);
                  if (CRCSum1!=Rec_buf_data_uart1[NumberByte-1]) //прверка принятого CRC
                  {
                    Tr_buf_data_uart1[4]=Rec_buf_data_uart1[NumberByte-1];  //принятая контрольная сумма
                    Tr_buf_data_uart1[5]=CRCSum1; //вычисленная контрольная сумма
                    ErrorMessage1(0xE2);
                  }
                  else
                  {
                    if ((Rec_buf_data_uart1[2]==0x74)||(Rec_buf_data_uart1[2]==0x73))
                    {

                      if (Rec_buf_data_uart1[2]==0x74){
                        PassToPC=(ePassword[0]-0x30)*1000+(ePassword[1]-0x30)*100+(ePassword[2]-0x30)*10+(ePassword[3]-0x30);
                        Tr_buf_data_uart1[4]=Hi(PassToPC);
                        Tr_buf_data_uart1[5]=Lo(PassToPC);
                        TransDataInf1(0x72, 2);
                      }
                      if (Rec_buf_data_uart1[2]==0x73)
                      {
                        PassToPC=(Rec_buf_data_uart1[4]<<8)+Rec_buf_data_uart1[5];
                        ePassword[0]=PassToPC/1000+0x30;
                        PassToPC-=(ePassword[0]-0x30)*1000;
                        ePassword[1]=PassToPC/100+0x30;
                        PassToPC-=(ePassword[1]-0x30)*100;
                        ePassword[2]=PassToPC/10+0x30;
                        PassToPC-=(ePassword[2]-0x30)*10;
                        ePassword[3]=PassToPC+0x30;

                        TransDataInf1(0x73, 0);

                        //а теперь запишем пароль в EEPROM
                        eWrite=1;
                        eAddressWrite=0;
                        eMassiveWrite=ePassword;
                      }
                      PCtime=PC_wait;
                      EnableReceive1;
                    }
                    else
                    {
                      for (i_dc1=0; i_dc1<NumberByte; i_dc1++)
                      {
                        Tr_buf_data_uart[i_dc1]=Rec_buf_data_uart1[i_dc1];
                        Rec_buf_data_uart1[i_dc1]=0x00;
                      }
                      PCbyte=NumberByte;
                      PCready=1;
                      PCtime=PC_wait;
                    }
                  }
                }

              } //end if (col.11)
              else //если адрес не тот, то опять следим за линией
              {
                EnableReceive1;
              }
            }
            break;
            case 1:
            {
              if (Rec_buf_data_uart1[0]==AddressModBus)
              {
                //if ((Rec_buf_data_uart1[1]!=0x03)&&(Rec_buf_data_uart1[1]!=0x06)) ErrorMessageModBus(0x01); //проверка кода команды
                //else
                //{
                  CRCSum1=GetCRC16(Rec_buf_data_uart1,NumberByte-2);
                  CRCread=(Rec_buf_data_uart1[NumberByte-2])+(Rec_buf_data_uart1[NumberByte-1]<<8);
                  //************************************************************************************************************8
                  //**************************************************************** На вреия отладки, затем надо убрать ответ.
                  //************************************************************************************************************8
                  if (CRCSum1!=CRCread) {Tr_buf_data_uart1[2]=Lo(CRCSum1); Tr_buf_data_uart1[3]=Hi(CRCSum1); TransDataInf1(0xFF,2-1);}//{EnableReceive1;}//прверка принятого CRC
                  else{
                    AddressStartRegister=(Rec_buf_data_uart1[2]<<8)+Rec_buf_data_uart1[3];
                    NumberRegister=Rec_buf_data_uart1[5];
                    switch(Rec_buf_data_uart1[1]){
                      case 0x03:{
                          if ((NumberRegister>64)||(NumberRegister==0)) ErrorMessageModBus(0x03); //кол-во запрашиваемых данных выходит из допустимого диапазона
                          else
                          {
                            //проверка на достоверность указанных регистров ModBus
                            if (((AddressStartRegister>=250)&&(AddressStartRegister<1024))||((AddressStartRegister+NumberRegister>250)&&(AddressStartRegister<1024))){
                              ErrorMessageModBus(0x02);
                            }else{
                              Tr_buf_data_uart1[2]=NumberRegister*2;
                              if (AddressStartRegister<250){ //все кроме архивов
                                for (i_dc1=0; i_dc1<NumberRegister; i_dc1++){
                                    ModBusBaza.readregister(Tr_buf_data_uart1, 3+i_dc1*2, AddressStartRegister+i_dc1);
                                }
                                TransDataInf1(0x03, NumberRegister*2);
                              }else
                                if ((AddressStartRegister>=0x400)&&(AddressStartRegister<0x2200)){  //архив событий
                                  ReadArch = 1;
                                  ModBusBaza.NumberRecordingArchive(0); //
                                  NumberRec = NumberRegister/15;
                                  if (NumberRec==0) NumberRec++;
                                  if ((15-(AddressStartRegister-1024)%15)<NumberRegister) NumberRec++;
                                  NumRecStart=(AddressStartRegister-1024)/15;
                                  ComArch=0xF2;
                                  //ErrorMessageModBus(0x03);
                                }else
                                  if ((AddressStartRegister>=0x2400)&&(AddressStartRegister<0x4200)){  //архив Поста
                                    ReadArch = 1;
                                    ModBusBaza.NumberRecordingArchive(0); //
                                    NumberRec = NumberRegister/15;
                                    if (NumberRec==0) NumberRec++;
                                    StRegister=(AddressStartRegister - 0x2400)%15;
                                    if ((15-StRegister)<NumberRegister) NumberRec++;
                                    NumRecStart=(AddressStartRegister-0x2400)/15;
                                    ComArch=0xC2;
                                  }else
                                    if ((AddressStartRegister>=0x4400)&&(AddressStartRegister<0x6200)){  //архив ПРМ
                                       ReadArch = 1;
                                      ModBusBaza.NumberRecordingArchive(0); //
                                      NumberRec = NumberRegister/15;
                                      if (NumberRec==0) NumberRec++;
                                      StRegister=(AddressStartRegister - 0x4400)%15;
                                      if ((15-StRegister)<NumberRegister) NumberRec++;
                                      NumRecStart=(AddressStartRegister-0x4400)/15;
                                      ComArch=0xD2;
                                    }else
                                      if ((AddressStartRegister>=0x6400)&&(AddressStartRegister<0x8200)){  //архив ПРД
                                        ReadArch = 1;
                                        ModBusBaza.NumberRecordingArchive(0); //
                                        NumberRec = NumberRegister/15;
                                        if (NumberRec==0) NumberRec++;
                                        StRegister=(AddressStartRegister - 0x6400)%15;
                                        if ((15-StRegister)<NumberRegister) NumberRec++;
                                        NumRecStart=(AddressStartRegister-0x6400)/15;
                                        ComArch=0xE2;
                                      }
                                }
                          }
                      }break;
                      case 0x06:{
                        ModBusBaza.writetoAT(AddressStartRegister,(Rec_buf_data_uart1[4]<<8) + Rec_buf_data_uart1[5]);
                        for (i_dc1=0; i_dc1<6; i_dc1++) Tr_buf_data_uart1[i_dc1]=Rec_buf_data_uart1[i_dc1];
                        TransDataInf1(0x06, 4-1);
                      }break;
                      default:  {ErrorMessageModBus(0x01);} //команда не поддерживается данным устройством
                    }
                  }
                //}
              }
              else EnableReceive1;
            }
            break;
            default:
            {
              EnableReceive1;
            }
          }
        }//end else (col.9)
      ClearPortError1();   //после начала отправки сообщения очистим регистр приема
} //end DataModBus


