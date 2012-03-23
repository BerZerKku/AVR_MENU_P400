/*****************************************
          переходы между меню
*****************************************/

void Menu_Start(void){
  MenuLevel=1;
  LCDbufClMenu();
  LCDtimerNew=1;
  ShiftMenu=0;
  MaxDisplayLine=0;
  ValueVsRange=0;
  NumberCom=1;
  if (bAllDevice) MaxShiftMenu=1;
  else MaxShiftMenu=0;
}

void Menu_Second(void){
  MenuLevel=2;
  LCDbufClMenu();
  LCDtimerNew=1;
  ShiftMenu=0;
  MaxShiftMenu=3;
  MaxDisplayLine=3;
  LCD2new=1;
}

void Menu_DataTime(void){
  MenuLevel=3;
  LCDbufClMenu();
  LCD2new=1;
}

void Menu_Journal(void){
  MenuLevel=4;
  LCDbufClMenu();
  ShiftMenu=0;
  MaxDisplayLine=3;
  if (sArchive.NumDev>2) MaxShiftMenu=1;
  else MaxShiftMenu=0;
  sArchive.Data[12]=0;
  FuncClearCharLCD(2,1,40);
  sArchive.RecCount=0;
  LCD2new=1;
}

void Menu_Setup(void){
  MenuLevel=5;
  LCDbufClMenu();
  ShiftMenu=0;
  MaxDisplayLine=3;
  MaxShiftMenu=1;
  if ((cNumComR>0)&&(CurrentState[2]<0x04)) MaxShiftMenu=0;   //если есть приемник, и он не в Тест
  if ((cNumComT>0)&&(CurrentState[4]<0x04)) MaxShiftMenu=0;  //если есть передатчик, и он не в Тест
  if ((bDef)&&(CurrentState[0]<0x04)) MaxShiftMenu=0; //если есть Пост, и он не в Тест
  LCD2new=1;
}

//меню/просмотр параметров
void Menu_ParamSetup(char Menu){
  MenuLevel=Menu; // 6 и 12
  LCDbufClMenu();
  ShiftMenu=0;
  ValueVsRange=0;
  NumberCom=1;
  if (LineInMenu6 <= 3){ //если 3 или менее строк
    MaxShiftMenu=0;
    MaxDisplayLine = LineInMenu6;
  }else{
    MaxShiftMenu = LineInMenu6-3;
    MaxDisplayLine=3;
  }
  LCD2new=1;
}

void Menu_ParamSetup_Def(void)
{
  	MenuLevel += 1; //7 и 13
  	LCDbufClMenu();
  	ShiftMenu = 0;
  	MaxDisplayLine = 1;
  	MaxShiftMenu = sMenuDefParam.num - 1;
  	LCD2new = 1;
  	cNumParam = 0x20;
}

void Menu_ParamSetup_Prm(void){
  MenuLevel+=2; // 8 и 14
  LCDbufClMenu();
  ShiftMenu=0;
  MaxDisplayLine=1;
  NumberCom=1;
  MaxShiftMenu=NumParamPrm-1;
  LCD2new=1;
  cNumParam=0x40;
}

void Menu_ParamSetup_Prd(void){
  MenuLevel+=3; // 9 и 15
  LCDbufClMenu();
  ShiftMenu=0;
  MaxShiftMenu=4;
  MaxDisplayLine=1;
  MaxShiftMenu=NumParamPrd-1;
  LCD2new=1;
  cNumParam=0x60;
}

void Menu_ParamSetup_Global(void)
{
  	MenuLevel += 4; //10 или 16
  	LCDbufClMenu();
  	ShiftMenu = 0;
  	MaxDisplayLine = 1;
  	NumberCom = 1;
  	MaxShiftMenu = sMenuGlbParam.num - 1;
  	LCD2new = 1;
  	cNumParam = 0x80;
}

void Menu_Setup_Regime(void){
  MenuLevel=11;
  LCDbufClMenu();
  ShiftMenu=0;
  MaxShiftMenu=0;
  MaxDisplayLine=1;
  LCD2new=1;
}

void Menu_Protocol(void){
  MenuLevel=18;
  LCDbufClMenu();
  ShiftMenu=0;
  MaxShiftMenu=0;
  MaxDisplayLine=1;
  LCD2new=1;
}

void Menu_Info(void){
  MenuLevel=19;
  LCDbufClMenu();
  ShiftMenu=0;
  MaxShiftMenu=3;
  MaxDisplayLine=1;
  LCD2new=1;
}

void Menu_Setup_Test(void)
{
	if ( (cNumComR) && (CurrentState[2] < 0x04) )
		return;   //если есть приемник, и он не в Тест
  	if ( (cNumComT) && (CurrentState[4]  <0x04) )
		return;  //если есть передатчик, и он не в Тест
  	if ( (bDef) && (CurrentState[0] < 0x04) )
	 	return;  //если есть Защита, и она не в Тест

   	MenuLevel = 20;
   	LCDbufClMenu();
   	ShiftMenu = 0;
	MaxDisplayLine = 3;
	MaxShiftMenu = sMenuTest.numTr - 1;

   	if ((cNumComR>0)&&(CurrentState[2]==5)) MaxShiftMenu=0;   //если есть приемник, и он в Тест2
   	if ((cNumComT>0)&&(CurrentState[4]==5)) MaxShiftMenu=0;  //если есть передатчик, и он в Тест2
   	if ((bDef)&&(CurrentState[0]==5)) MaxShiftMenu=0;  //если есть Защита, и она в Тест2
   	LCD2new=1;
}

void PressInMenuJournal(char Key){  //нажатие в меню Журна -> переход в подпункты журнала
  Key-=0x31;
  if (sArchive.NumDev>=Key){ //если есть устройство
    MenuLevel=21;
    LCDbufClMenu();
    ShiftMenu=0;
    MaxDisplayLine=2;
    sArchive.CurrDev=Key;
    sArchive.RecCount=0;  //для начала сбросим кол-во данных

    LCD2new=1;
  }
}

void Menu_Upr(void)
{
	MenuLevel = 22;
  	LCDbufClMenu();
  	ShiftMenu = 0;
  	MaxDisplayLine = 3;
  	MaxShiftMenu = sMenuUpr.num - 3;
  	LCD2new=1;
}

void PressInMenuDataTime(char Key){ //нажатеи в меню Дата/Время
  WorkRate=0x03;
  InputParameter=Key;
  if (Key==1) ChangeMass=DataLCD;
  else ChangeMass=TimeLCD;
  Discret=1;  //дискрет 1
  for (char i=0; i<=8; i++) InputDataTime[i]=ChangeMass[i];
}

void PressInMenuReset(char Key)
{  //выбор устройства сброса
	if (Key > sMenuUpr.num)
		return;
	Key--;
	SelectValue = sMenuUpr.punkt[Key];
	
  	switch(sMenuUpr.punkt[Key])
	{    	
	  case 2:
		SelectValue--;
	  case 0:
	  case 1:
	  case 3:
		{ //сбросы
			MaxValue = MinValue = InputSelectValue = 0;
      		SelectValue = SelectValue + 1;
      		TrValue=0x72;
    	}
		break;    	
	  case 5:
	  case 6:
	  case 7:
		SelectValue--;
	  case 4:
		{  //пуски
      		MaxValue = MinValue = InputSelectValue = 1;
      		SelectValue = SelectValue;
      		TrValue = 0x72;
		}
		break;
	  case 9:
	  case 10:
	  case 11:
	  case 12:
	  case 13:
		SelectValue++;
	  case 8:
		{  //АК
      		MaxValue = MinValue = InputSelectValue = 2;
      		SelectValue = SelectValue - 7;
      		TrValue = 0x8A;
		}
	  break;
	  case 14:
		{	//вызов
			MaxValue = MinValue = InputSelectValue = 3;
			SelectValue = 7;
			TrValue = 0x72;
		}
		break;
	  default:
	  	return;  //ошибка
	}
	ShiftMenu = Key;
  	WorkRate = 2; //тип ввода с клавиатуры
  	MassSelectValue = fReset; //массив списка значений
}

void MenuParamGlbCreate(void)
{
	sMenuGlbParam.num = 0;
	switch(TypeUdDev)
	{
	  case 1:	//пвз-90
	  case 2:	//авзк-80	
		{
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 0; sMenuGlbParam.name[sMenuGlbParam.num++] = 0;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 2; sMenuGlbParam.name[sMenuGlbParam.num++] = 2;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 4; sMenuGlbParam.name[sMenuGlbParam.num++] = 4;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 7; sMenuGlbParam.name[sMenuGlbParam.num++] = 7;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 8; sMenuGlbParam.name[sMenuGlbParam.num++] = 8;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 9; sMenuGlbParam.name[sMenuGlbParam.num++] = NumParamGlb;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 11; sMenuGlbParam.name[sMenuGlbParam.num++] = 11;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 12; sMenuGlbParam.name[sMenuGlbParam.num++] = 12;
		}
		break;
	  case 3:	// ПВЗУ-Е
		{
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 0; sMenuGlbParam.name[sMenuGlbParam.num++] = 0;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 2; sMenuGlbParam.name[sMenuGlbParam.num++] = 2;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 4; sMenuGlbParam.name[sMenuGlbParam.num++] = 4;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 7; sMenuGlbParam.name[sMenuGlbParam.num++] = 7;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 8; sMenuGlbParam.name[sMenuGlbParam.num++] = 8;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 9; sMenuGlbParam.name[sMenuGlbParam.num++] = NumParamGlb;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 11; sMenuGlbParam.name[sMenuGlbParam.num++] = 11;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 12; sMenuGlbParam.name[sMenuGlbParam.num++] = 12;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 13; sMenuGlbParam.name[sMenuGlbParam.num++] = 13;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 14; sMenuGlbParam.name[sMenuGlbParam.num++] = 14;
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 15; sMenuGlbParam.name[sMenuGlbParam.num++] = 15;
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.proval[i] = MenuAllProval[i];
				if (MenuAllProval[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 16; sMenuGlbParam.name[sMenuGlbParam.num++] = 16;
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.porog[i] = MenuAllPorog[i];
				if (MenuAllPorog[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 17; sMenuGlbParam.name[sMenuGlbParam.num++] = 17;
			for(char i = 0; i < 10; i++)
			{
				sParamPVZE.noise[i] = MenuAllNoise[i];
				if (MenuAllNoise[i] == 0)
					break;
			}
			sMenuGlbParam.punkt[sMenuGlbParam.num] = 18; sMenuGlbParam.name[sMenuGlbParam.num++] = 18;
			
		}
		break;
		default:	//в остальных случаях будет Авант
		{
			if (cTypeLine == 1)													
			{
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 0; sMenuGlbParam.name[sMenuGlbParam.num++] = 0;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 1; sMenuGlbParam.name[sMenuGlbParam.num++] = 1;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 2; sMenuGlbParam.name[sMenuGlbParam.num++] = 2;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 4; sMenuGlbParam.name[sMenuGlbParam.num++] = 4;
				// sMenuGlbParam.punkt[sMenuGlbParam.num] = 5; sMenuGlbParam.name[sMenuGlbParam.num++] = 5;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 6; sMenuGlbParam.name[sMenuGlbParam.num++] = 6;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 7; sMenuGlbParam.name[sMenuGlbParam.num++] = 7;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 8; sMenuGlbParam.name[sMenuGlbParam.num++] = 8;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 9; sMenuGlbParam.name[sMenuGlbParam.num++] = 9;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 11; sMenuGlbParam.name[sMenuGlbParam.num++] = 11;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 12; sMenuGlbParam.name[sMenuGlbParam.num++] = 12;
			}
			else
			{
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 1; sMenuGlbParam.name[sMenuGlbParam.num++] = 1;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 4; sMenuGlbParam.name[sMenuGlbParam.num++] = 4;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 7; sMenuGlbParam.name[sMenuGlbParam.num++] = 7;
				// sMenuGlbParam.punkt[sMenuGlbParam.num] = 5; sMenuGlbParam.name[sMenuGlbParam.num++] = 5;
				sMenuGlbParam.punkt[sMenuGlbParam.num] = 19; sMenuGlbParam.name[sMenuGlbParam.num++] = 19;
			}
			
		}
	}
}

void MenuParamDefCreate(void)
{
	sMenuDefParam.num = 0;
	switch(TypeUdDev)
	{
	  case 1:	// пвз-90 
	  case 2:	// авзк-80
	  case 3:	// ПВЗУ-Е
		{
			sMenuDefParam.punkt[sMenuDefParam.num++] = 0;
			sMenuDefParam.punkt[sMenuDefParam.num++] = 1;
			sMenuDefParam.punkt[sMenuDefParam.num++] = 2;
			sMenuDefParam.punkt[sMenuDefParam.num++] = 3;
			sMenuDefParam.punkt[sMenuDefParam.num++] = 4;
			sMenuDefParam.punkt[sMenuDefParam.num++] = 5;
			sMenuDefParam.punkt[sMenuDefParam.num++] = 7;
			sMenuDefParam.punkt[sMenuDefParam.num++] = 8;	
		}
		break;
	  default:	//в остальных случаях будет Авант
		sMenuDefParam.punkt[sMenuDefParam.num++] = 0;
		sMenuDefParam.punkt[sMenuDefParam.num++] = 1;
		sMenuDefParam.punkt[sMenuDefParam.num++] = 2;
		sMenuDefParam.punkt[sMenuDefParam.num++] = 3;
		sMenuDefParam.punkt[sMenuDefParam.num++] = 4;
		if (cTypeLine == 1)														// в ВЛ есть дополнительные параметры
		{
			sMenuDefParam.punkt[sMenuDefParam.num++] = 5;						 	
			sMenuDefParam.punkt[sMenuDefParam.num++] = 6;
		}
	}	
}

void MenuUprCreate(void)
{
	sMenuUpr.num = 0;
	switch(TypeUdDev)
	{
	  case 1:	//пвз-90
	
		{
			sMenuUpr.punkt[sMenuUpr.num] = 0; sMenuUpr.name[sMenuUpr.num++] = 0;
			sMenuUpr.punkt[sMenuUpr.num] = 1; sMenuUpr.name[sMenuUpr.num++] = 1;
			sMenuUpr.punkt[sMenuUpr.num] = 8; sMenuUpr.name[sMenuUpr.num++] = dNumUprLine;
			sMenuUpr.punkt[sMenuUpr.num] = 9; sMenuUpr.name[sMenuUpr.num++] = 9;
			sMenuUpr.punkt[sMenuUpr.num] = 10; sMenuUpr.name[sMenuUpr.num++] = 10;
			sMenuUpr.punkt[sMenuUpr.num] = 12; sMenuUpr.name[sMenuUpr.num++] = 12;
			sMenuUpr.punkt[sMenuUpr.num] = 13; sMenuUpr.name[sMenuUpr.num++] = 13;
			sMenuUpr.punkt[sMenuUpr.num] = 14; sMenuUpr.name[sMenuUpr.num++] = 14;
		}
		break;
		
	  case 2:	//авзк-80		
		{		
			sMenuUpr.punkt[sMenuUpr.num] = 0; sMenuUpr.name[sMenuUpr.num++] = 0;
			sMenuUpr.punkt[sMenuUpr.num] = 8; sMenuUpr.name[sMenuUpr.num++] = dNumUprLine;
			sMenuUpr.punkt[sMenuUpr.num] = 9; sMenuUpr.name[sMenuUpr.num++] = 9;
			sMenuUpr.punkt[sMenuUpr.num] = 10; sMenuUpr.name[sMenuUpr.num++] = 10;
			sMenuUpr.punkt[sMenuUpr.num] = 12; sMenuUpr.name[sMenuUpr.num++] = 12;
			sMenuUpr.punkt[sMenuUpr.num] = 13; sMenuUpr.name[sMenuUpr.num++] = 13;
			sMenuUpr.punkt[sMenuUpr.num] = 14; sMenuUpr.name[sMenuUpr.num++] = 14;
		}
		break;
	  case 3:	// ПВЗУ-Е
		{
			sMenuUpr.punkt[sMenuUpr.num] = 0; sMenuUpr.name[sMenuUpr.num++] = 0;
			sMenuUpr.punkt[sMenuUpr.num] = 4; sMenuUpr.name[sMenuUpr.num++] = 4;
			sMenuUpr.punkt[sMenuUpr.num] = 7; sMenuUpr.name[sMenuUpr.num++] = dNumUprLine + 2;
			sMenuUpr.punkt[sMenuUpr.num] = 8; sMenuUpr.name[sMenuUpr.num++] = dNumUprLine;
			sMenuUpr.punkt[sMenuUpr.num] = 9; sMenuUpr.name[sMenuUpr.num++] = 9;
			sMenuUpr.punkt[sMenuUpr.num] = 11; sMenuUpr.name[sMenuUpr.num++] = dNumUprLine + 1;
			sMenuUpr.punkt[sMenuUpr.num] = 12; sMenuUpr.name[sMenuUpr.num++] = 11;
			sMenuUpr.punkt[sMenuUpr.num] = 10; sMenuUpr.name[sMenuUpr.num++] = 10;
			sMenuUpr.punkt[sMenuUpr.num] = 14; sMenuUpr.name[sMenuUpr.num++] = 14;
		}
		break;
	  default:	//в остальных случаях будет Авант
		sMenuUpr.punkt[sMenuUpr.num] = 0; sMenuUpr.name[sMenuUpr.num++] = 0;
		if (cNumLine == 3)
		{
			sMenuUpr.punkt[sMenuUpr.num] = 2; sMenuUpr.name[sMenuUpr.num++] = 2;
			sMenuUpr.punkt[sMenuUpr.num] = 3; sMenuUpr.name[sMenuUpr.num++] = 3;
			sMenuUpr.punkt[sMenuUpr.num] = 5; sMenuUpr.name[sMenuUpr.num++] = 5;
			sMenuUpr.punkt[sMenuUpr.num] = 6; sMenuUpr.name[sMenuUpr.num++] = 6;
			sMenuUpr.punkt[sMenuUpr.num] = 7; sMenuUpr.name[sMenuUpr.num++] = 7;
			if (cTypeLine == 1)													// в ВЛ есть смена АК
			{
				sMenuUpr.punkt[sMenuUpr.num] = 8; sMenuUpr.name[sMenuUpr.num++] = 8;
				sMenuUpr.punkt[sMenuUpr.num] = 9; sMenuUpr.name[sMenuUpr.num++] = 9;
				sMenuUpr.punkt[sMenuUpr.num] = 10; sMenuUpr.name[sMenuUpr.num++] = 10;
			}
		}
		else
		{
			sMenuUpr.punkt[sMenuUpr.num] = 1; sMenuUpr.name[sMenuUpr.num++] = 1;
			sMenuUpr.punkt[sMenuUpr.num] = 4; sMenuUpr.name[sMenuUpr.num++] = 4;
			if (cTypeLine == 1)													// в ВЛ есть смена АК и вызов
			{
				sMenuUpr.punkt[sMenuUpr.num] = 8; sMenuUpr.name[sMenuUpr.num++] = 8;			
				sMenuUpr.punkt[sMenuUpr.num] = 9; sMenuUpr.name[sMenuUpr.num++] = 9;
				sMenuUpr.punkt[sMenuUpr.num] = 10; sMenuUpr.name[sMenuUpr.num++] = 10;
				sMenuUpr.punkt[sMenuUpr.num] = 14; sMenuUpr.name[sMenuUpr.num++] = 14;
			}
		}
	}	
}

void MenuAKCreate(void)
{
	char i = 0;
	
	param4[i++] = 0;
	
	if (TypeUdDev > 0)	//пвз-90, авзк-80, ПВЗЕ-У
	{
		param4[i++] = 8;
		param4[i++] = 8;
	}
	else
	{
		param4[i++] = 1;
		param4[i++] = 2;
	}
	param4[i++] = 3;
	param4[i++] = 4;
	if (TypeUdDev == 3) // ПВЗУ-Е
	{
		param4[i++] = 9;
		param4[i++] = 5;
	}
	else
	{
		param4[i++] = 5;
		param4[i++] = 6;
	}
}

void MenuTestCreate(void)
{
	//формирование меню Тест
	//на данный момент только для Защиты
	
	switch(TypeUdDev)
	{
	  case 1:	//пвз-90
	  case 2:	//авзк-80
	  case 3:	//пвзу-е
		{
			sMenuTest.num = 1;
			sMenuTest.numTr = 1; // передача КЧ и РЗ
			sMenuTest.sT[0].type = 2;	// РЗ
			sMenuTest.sT[0].name = Menu20line2test12;
			sMenuTest.sT[0].sp = Menu20gr2;
			sMenuTest.sT[0].val = sNumGrRZ;
			sMenuTest.sT[0].num = 0;
			sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 0;
			sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 1;
		}
		break;
	  default:
		{	//авант
			//или в случае ошибочного значения, параметры будут для Аванта	
			
			if (cNumLine == 3)
			{	//трехконцевая версия пост
				sMenuTest.num = 4;
				sMenuTest.numTr = 2;	//передача КЧ и РЗ
				sMenuTest.sT[0].type = 1;	// 1 КЧ
				sMenuTest.sT[0].sp = Menu20gr1;
				sMenuTest.sT[0].name = Menu20line2test13;
				sMenuTest.sT[0].val = dNumGrCH;
				sMenuTest.sT[0].num = 0;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 0;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 1;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 2;
				
				sMenuTest.sT[1].type = 2;	// 1 РЗ
				sMenuTest.sT[1].name = Menu20line2test15;
				sMenuTest.sT[1].sp = Menu20gr2;
				sMenuTest.sT[1].val = sNumGrRZ;
				sMenuTest.sT[1].num = 0;
				sMenuTest.sT[1].punkt[sMenuTest.sT[1].num++] = 0;
				sMenuTest.sT[1].punkt[sMenuTest.sT[1].num++] = 1;
				
				sMenuTest.sT[2].type = 3;	// 2 КЧ
				sMenuTest.sT[2].sp = Menu20gr1;
				sMenuTest.sT[2].name = Menu20line2test14;
				sMenuTest.sT[2].val = dNumGrCH;
				sMenuTest.sT[2].num = 0;
				sMenuTest.sT[2].punkt[sMenuTest.sT[2].num++] = 0;
				sMenuTest.sT[2].punkt[sMenuTest.sT[2].num++] = 1;
				sMenuTest.sT[2].punkt[sMenuTest.sT[2].num++] = 2;
				
				sMenuTest.sT[3].type = 4;	// 1 РЗ
				sMenuTest.sT[3].name = Menu20line2test16;
				sMenuTest.sT[3].sp = Menu20gr2;
				sMenuTest.sT[3].val = sNumGrRZ;
				sMenuTest.sT[3].num = 0;
				sMenuTest.sT[3].punkt[sMenuTest.sT[3].num++] = 0;
				sMenuTest.sT[3].punkt[sMenuTest.sT[3].num++] = 1;
				
			}
			else
			{	//двухконцевая версия
				sMenuTest.num = 2;
				sMenuTest.numTr = 2;	//передача КЧ и РЗ
				sMenuTest.sT[0].type = 1;	// КЧ
				sMenuTest.sT[0].num = 0;
				sMenuTest.sT[0].sp = Menu20gr1;
				sMenuTest.sT[0].name = Menu20line2test11;
				sMenuTest.sT[0].val = dNumGrCH;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 0;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 1;
				sMenuTest.sT[0].punkt[sMenuTest.sT[0].num++] = 2;
				
				sMenuTest.sT[1].type = 2;	// РЗ
				sMenuTest.sT[1].name = Menu20line2test12;
				sMenuTest.sT[1].sp = Menu20gr2;
				sMenuTest.sT[1].val = sNumGrRZ;
				sMenuTest.sT[1].num = 0;
				sMenuTest.sT[1].punkt[sMenuTest.sT[1].num++] = 0;
				sMenuTest.sT[1].punkt[sMenuTest.sT[1].num++] = 1;
			}
		}
	}
}

