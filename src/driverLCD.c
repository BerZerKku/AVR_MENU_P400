//подпрограмма работы с ЖК-индикатором
#include <stdint.h>
#include "ioavr.h"
#include "ina90.h"
#include "MyDef.h"


#define PortLCD PORTA

#define SetE PORTB|=1<<5
#define ClrE PORTB&=~(1<<5)
#define SetRS PORTB|=0x40
#define ClrRS PORTB&=0xBF

#define WriteLCDdata(data); SetRS; SetE; PortLCD=data; ClrE;
#define WriteLCDcommand(data); ClrRS; SetE; PortLCD=data; ClrE;

unsigned char LCDbuf[80];
unsigned char i1,i3;
unsigned char CommandLCD;
unsigned char LCDstat;

__flash unsigned char InitLCD[6]={0x38, 0x0C, 0x01,0x80, 0x02, 0x00};  //инициализация LCD для HD44780
//__flash unsigned char InitLCD[5]={0x3A, 0x0F, 0x01,0x06, 0x00};  //инициализация LCD для S6A0069

//                                             A    Б   В     Г   Д     Е   Ж     З   И     й   К     Л   М     Н   О     П
__flash const unsigned char CodeLetterLCD[]={0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,
//                                             Р     С   Т     У    Ф    Х   Ц     Ч   Ш     Щ   Ъ     Ы    Ь    Э   Ю     Я
                                             0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,0xB1,
//                                             а     б    в    г   д     е   ж     з    и    й   к     л   м     н   о     п
                                             0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,
//                                             р    с   т     у   ф     х   ц     ч   ш     щ   ъ     ы    ь    э    ю    я
                                             0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7};

#pragma vector=TIMER2_OVF_vect
__interrupt void Timer2_ovf(void){
  switch(LCDstat){
    case 2:{
      TCNT2=243;
      WriteLCDdata(LCDbuf[i1]);
      if (i1<79) i1++; else i1=0;
      switch(i1){
        case 0: {CommandLCD=0x80; LCDstat=1;} break;
        case 20: {CommandLCD=0xC0; LCDstat=1;} break;
        case 40: {CommandLCD=0x94; LCDstat=1;} break;
        case 60: {CommandLCD=0xD4; LCDstat=1;} break;
      }
    }break;
    case 1:{
      if (CommandLCD==0x01) TCNT2=48;
      else TCNT2=243;
      WriteLCDcommand(CommandLCD);
      LCDstat=2;
    }break;
    case 3:{ //инициализация ЖК
      if (InitLCD[i3]==0x01) TCNT2=48;
      else TCNT2=243;
      if (InitLCD[i3]!=0x00)  {WriteLCDcommand(InitLCD[i3]); i3++;}
      else{LCDstat=2;i3=0;i1=0;}
    }break;
  }
}

void LCDprint(unsigned char Line, unsigned char AddressInLine, unsigned char* bufer, unsigned char convers)
{
  unsigned char StartChar, i2=0;
  
  StartChar=(Line-1)*20+AddressInLine-1;
  while(bufer[i2]!=0x00){
    if (convers==1){
      if ((bufer[i2]>='А')&&(bufer[i2]<='я')) LCDbuf[StartChar+i2]=CodeLetterLCD[bufer[i2]-192];
      else LCDbuf[StartChar+i2]=bufer[i2];
    }else LCDbuf[StartChar+i2]=bufer[i2];
    i2++;
  }
}

void LCDbufClear(void){
  for (unsigned char i4=0;i4<80;i4++) LCDbuf[i4]=0x20;  //записывем пробел
  i1=0;
}

void LCDbufClMenu(void){  //очистка 3 нижних строк
  for (unsigned char i4=20;i4<80;i4++) LCDbuf[i4]=0x20;
}

void FuncInitLCD(void){
  i3=0;
  LCDstat=3;
}

void FuncCommandLCD(unsigned char com){
  CommandLCD=com;
  LCDstat=1;
}

void FuncClearCharLCD(unsigned char Line, unsigned char AddressInLine, unsigned char NumberChar){
  unsigned char StartChar, i2;
  StartChar=(Line-1)*20+AddressInLine-1;
  for (i2=0; i2<NumberChar;i2++) LCDbuf[StartChar++]=0x20;
}

void LCDprintHEX(unsigned char Line, unsigned char AddressInLine, unsigned char CodePrint){
  unsigned char StartChar;
  StartChar=(Line-1)*20+AddressInLine-1;
  LCDbuf[StartChar]=CodePrint/16;
  LCDbuf[StartChar+1]=CodePrint-LCDbuf[StartChar]*16;
  if (LCDbuf[StartChar]>9) LCDbuf[StartChar]+=0x37;
  else  LCDbuf[StartChar]+=0x30;
  if (LCDbuf[StartChar+1]>9) LCDbuf[StartChar+1]+=0x37;
  else  LCDbuf[StartChar+1]+=0x30;
}

//вывод на экран числа в десятичном виде, со сдвигом влево
uint8_t LCDprintDEC(uint8_t Line, uint8_t AddressInLine, uint8_t CodePrint)
{
  uint8_t pos;
  uint8_t numChar = 1;
  
  pos = (Line - 1)*20 + AddressInLine - 1;
  if (CodePrint > 9) 
  {
	  LCDbuf[pos++] = (CodePrint / 10) + '0';
	  numChar++;
  }
  LCDbuf[pos] = (CodePrint % 10) + '0';
  
  return numChar;
}

//вывод на экран числа в десятичном виде, со сдвигом вправо
void LCDprintDEC1(unsigned char Line, unsigned char AddressInLine, unsigned char CodePrint){
  unsigned char StartChar;
  StartChar=(Line-1)*20+AddressInLine-1;
  if(CodePrint>9)
    LCDbuf[StartChar]=CodePrint/10+0x30;
  else
    LCDbuf[StartChar]=' ';
  StartChar++;
  LCDbuf[StartChar]=(CodePrint%10)+0x30;
}

//вывод на экран числа в десятичном виде 4 знаков, со сдвигом вправо
void LCDprintDEC2(unsigned char Line, unsigned char AddressInLine, unsigned char CodePrint)
{
	unsigned char StartChar;
	StartChar = (Line-1)*20 + AddressInLine - 1;
	
	StartChar += 3;
	
	LCDbuf[StartChar--] = '0';
	while(CodePrint > 0)
	{
		LCDbuf[StartChar--] = CodePrint%10 + '0';
		CodePrint /= 10;
	}
	
//	CodePrint /= 10;
//	LCDbuf[StartChar--] = CodePrint%10 + '0';
//	LCDbuf[StartChar--] = CodePrint/10 + '0';
	
//	LCDbuf[StartChar]=CodePrint/100 + '0';
//	CodePrint = CodePrint-(LCDbuf[StartChar] - '0') * 100;
//	StartChar++;
//	LCDbuf[StartChar]=CodePrint/10+0x30;
//	StartChar++;
//	LCDbuf[StartChar]=CodePrint%10+0x30;
//	
//	if (LCDbuf[StartChar - 2] == 0x30) 
//		LCDbuf[StartChar - 2]=' ';
//	
//	if (LCDbuf[StartChar - 1] == 0x30) 
//		LCDbuf[StartChar - 1]=' ';
//	
//	StartChar++;
//	LCDbuf[StartChar]='0';
}

void LCDprintBits(unsigned char Line, unsigned char AddressInLine, unsigned char CodePrint){
  unsigned char StartChar;
  unsigned char temp=0x80;

  StartChar=(Line-1)*20+AddressInLine-1;
  do{
    LCDbuf[StartChar]=(CodePrint&temp)+0x30;
    if (LCDbuf[StartChar]!=0x30) LCDbuf[StartChar]=0x31;
    StartChar++;
    temp=temp>>1;
  }while(temp!=0);
}

void LCDprintTetr(unsigned char Line, unsigned char AddressInLine, unsigned char CodePrint){
  unsigned char StartChar;
  unsigned char temp=0x08;

  StartChar=(Line-1)*20+AddressInLine-1;
  do{
    LCDbuf[StartChar]=(CodePrint&temp)+0x30;
    if (LCDbuf[StartChar]!=0x30) LCDbuf[StartChar]=0x31;
    StartChar++;
    temp=temp>>1;
  }while(temp!=0);
}

void LCDprintf(unsigned char Line, unsigned char AddressInLine, unsigned __flash char* buferf, unsigned char convers)
{
  unsigned char StartChar, i2=0;
  StartChar=(Line-1)*20+AddressInLine-1;
  while(buferf[i2]!=0x00)
    {
      if (convers==1)
        {
          if ((buferf[i2]>='А')&&(buferf[i2]<='я')) LCDbuf[StartChar+i2]=CodeLetterLCD[buferf[i2]-192];
          else LCDbuf[StartChar+i2]=buferf[i2];
        }
      else
        if (convers==2)
          {
            LCDbuf[StartChar+i2]=0x20;
          }
        else
          {
            LCDbuf[StartChar+i2]=buferf[i2];
          }
      i2++;
    }
}

void LCDprintInsertion(unsigned char Line, unsigned char AddressInLine, unsigned int CodePrint){
  unsigned char StartChar;
  StartChar=(Line-1)*20+AddressInLine-1;

  LCDbuf[StartChar]=CodePrint/1000+0x30;
  CodePrint=CodePrint-(LCDbuf[StartChar]-0x30)*1000;
  StartChar++;
  LCDbuf[StartChar]=CodePrint/100+0x30;
  CodePrint=CodePrint-(LCDbuf[StartChar]-0x30)*100;
  StartChar++;
  LCDbuf[StartChar]=CodePrint/10+0x30;
  StartChar++;
  LCDbuf[StartChar]=CodePrint%10+0x30;
}

void LCDprintChar (unsigned char Line, unsigned char AddressInLine, unsigned int CodePrint){
  unsigned char StartChar;
  StartChar=(Line-1)*20+AddressInLine-1;

  LCDbuf[StartChar] = CodePrint;
}

void LCDptinrArchCount(uint16_t max, uint16_t now)
{
	uint8_t poz = 60;		// текущий адрес в массиве
	
	uint8_t charInMax = 1;	// кол-во знаков в макс. значении
	uint8_t charInNow = 1;	// кол-во знаков в текущем значении
	
	if (max > 999)
		charInMax = 4;
	else if (max > 99)
		charInMax = 3;
	else if (max > 9)
		charInMax = 2;
	else 
		charInMax = 1;
	
	if (now > 999)
		charInNow = 4;
	else if (now > 99)
		charInNow = 3;
	else if (now > 9)
		charInNow = 2;
	else
		charInNow = 1;
	
	poz += charInNow + charInMax + 2;	// +2 - учет символов '(', '/', ')'
	
	LCDbuf[poz--] = ')';
	while (charInMax > 0)
	{
		LCDbuf[poz--] = max % 10 + '0';
		max /= 10;
		charInMax--;
	}
	LCDbuf[poz--] = '/';
	while (charInNow > 0)
	{
		LCDbuf[poz--] = now % 10 + '0';
		now /= 10;
		charInNow--;
	}
	LCDbuf[poz] = '(';
}

void LCDprintData(uint8_t adr, uint8_t day, uint8_t month, uint8_t year)
{
	uint8_t *ptr = (uint8_t *) &LCDbuf[adr];
	
	// day
	*ptr++ = (day >> 4)  + '0';
	*ptr++ = (day & 0x0F) + '0';
	
	*ptr++ = '.';
	
	// month
	*ptr++ = (month >> 4) + '0';
	*ptr++ = (month & 0x0F) + '0';
	
	*ptr++ = '.';
	
	// year
	*ptr++ = (year >> 4) + '0';
	*ptr++ = (year & 0x0F) + '0';
}

void LCDprintTime(uint8_t adr, uint8_t h, uint8_t m, uint8_t s, uint16_t ms)
{
	uint8_t *ptr = (uint8_t *) &LCDbuf[adr];
	
	// hours	
	*ptr++ = (h >> 4) + '0';
	*ptr++ = (h & 0x0F) + '0';
	
	*ptr++ = ':';
	
	// minutes
	*ptr++ = (m >> 4) + '0';
	*ptr++ = (m & 0x0F) + '0';
	
	*ptr++ = ':';
	
	// seconds
	*ptr++ = (s >> 4) + '0';
	*ptr++ = (s & 0x0F) + '0';
	
	*ptr++ = '.';
	
	// milliseconds
	ptr += 2;
	*ptr-- = ms%10 + '0';
	ms /= 10;
	*ptr-- = ms%10 + '0';
	*ptr = ms/10 + '0';
}

void LCDprintBitMask(unsigned char Adr, unsigned char Val, unsigned char Mask){
  unsigned char temp=0x80;
  do{
    if (Mask&temp){ //если надо вывести этот бит
      if (Val&temp) LCDbuf[Adr]='1';
      else LCDbuf[Adr]='0';
      Adr++;
    }
    temp>>=1;
  }while(temp>0);
}

extern uchar cNumLine;
extern unsigned int iTimeToAKnow, iTimeToAK;
void LCDprintTimeAK(unsigned char AK, uchar dev, unsigned char Num, unsigned char* Time)
{
  	//			АВАНТ			ПВЗ-90 / АВЗК		ПВЗЛ
	//AK = 1 - авто ускор 		нормальный			нормальный
  	//АК = 2 - авто норм 	
  	//АК = 3 - ускор			ускор.				
  	//АК = 4 - АК выключен		выкл.				выкл.
	//AK = 5 - 					проверка			односторон.
	//AK = 6 - 					испыт.				
	
	// dev = 0 - АВАНТ
	// dev = 1 - ПВЗ-90
	// dev = 2 - АВЗК
	// dev = 3 - ПВЗУ-Е
	// dev = 4 - ПВЗЛ
	
    uchar 	time1 = 59,	// минуты
	time2 = 0, 	// секунды
	time3 = 0;	// часы
    uchar 	start1 = 48;
	
	
	if  ( (AK > 6) || (AK == 4) || (AK == 0) || (dev > 4) || (iTimeToAKnow > iTimeToAK) )
	{
		// если ошибочный тип АК или тип удаленного устройства
		// либо текущий счетчик времени больше времени до АК
		// очистим строку и выйдем из функции
		for( ; start1 < 60; start1++)
			LCDbuf[start1]=' ';
		return;
	}
	
	//если предыдущий символ не пробел, пропустим 1 знак
	if (LCDbuf[start1 - 1] != ' ')
		LCDbuf[start1++] = ' ';
	
	// в АВАНТе время высчитывается
	// при совместимости выводится полученное значение
	switch(dev)
	{
		case 0:		// АВАНТ
		{
			time2 = 60 - (Time[6]-0x30)*10 - (Time[7]-0x30);
			
			if (cNumLine == 2)
			{
				if (Num == '2') time2 += 30; //если 2 аппарат, добавим 30 секунд
			}
			else
				if (cNumLine == 3)
				{
					if (Num == '2') time2+=20;
					else
						if (Num == '3') time2+=40;
				}
			
			if (time2 > 59) {time2 -= 60; time1++;} //если 60 сек, то добавим 1 мин и обнулим секунды
			
			if ( (AK == 1)||(AK == 3) )
				time1 = 0; //если АК ускоренныЙ, то нужны только секунды
			else
			{
			  	time1 -= (Time[3] - 0x30) * 10 + (Time[4] - 0x30);
			  	if (time1 == 60)
					time1 = 0;
			}
		}
		break;
		
		case 1:
		case 2:
		case 3:
		case 4:
		{
			unsigned int a;
			
			a = iTimeToAK - iTimeToAKnow;
			time2 = a % 60;
			a /= 60;
			time1 = a % 60;
			a /= 60;
			time3 = a % 60;
		}
		break;
	}
	
	
	
	// выведем время до АК
	// если есть часы, не выводим "через"
	
	if (time3 == 0)
	{
		LCDbuf[start1++] = 0xC0; // 'ч';
		LCDbuf[start1++] = 0x65; // 'е';
		LCDbuf[start1++] = 0x70; // 'р';
		LCDbuf[start1++] = 0x65; // 'е';
		LCDbuf[start1++] = 0xB7; // 'з';
		LCDbuf[start1++] = ' ';	
	}
	else
	{
		
		LCDbuf[start1++] = (time3 / 10) + '0';
		LCDbuf[start1++] = (time3 % 10) + '0';
		LCDbuf[start1++] = ':';
	}
	LCDbuf[start1++] = (time1 / 10) + '0';
	LCDbuf[start1++] = (time1 % 10) + '0';
	
	LCDbuf[start1++] = ':';
	LCDbuf[start1++] = (time2 / 10) + '0';
	LCDbuf[start1++] = (time2 % 10) + '0';
	
  	for(; start1 < 60; start1++)
		LCDbuf[start1] = ' ';  //очистим строку до конца
}

extern unsigned char *Measuring[];
extern __flash unsigned __flash char* fAKdecr[];
//функция вывода Uk в главном меню, в чистой Защите
void LCDprintUkDef(unsigned char AKdecrease)
{
  unsigned char i=0, j = 60, t;

  if (AKdecrease>2) AKdecrease=2;

  while(fAKdecr[AKdecrease] [i] != 0x00){
    t=fAKdecr[AKdecrease] [i++];
    if ((t>='А')&&(t<='я')) t =  CodeLetterLCD[t - 192];
    LCDbuf[j++] = t;
  }

  i=3;

  while(Measuring[5] [i] != 'д'){
    LCDbuf[j++] = Measuring[5] [i++] ;
  }

  LCDbuf[j++]=CodeLetterLCD['д'-192];; //'д'
  LCDbuf[j++]=CodeLetterLCD['Б'-192];;  //'Б'

  for(; j<80; j++) LCDbuf[j]=' ';
}