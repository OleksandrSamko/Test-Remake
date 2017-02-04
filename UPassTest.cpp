//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "URegistration.h"
#include "UPassTest.h"
#include "UCode.h"

#include "UGenRandomUniq.h"
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>

//#define DEBUG
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFPassTest *FPassTest;
const int MaxLevel=4;
const int MaxDifLev=3;
int DifLevCount;
const AnsiString fTestNames="TestNames.txt";
const AnsiString dirQuest="Quest";
//
//PetebQuest
AnsiString fNameFolder;
//Quest
AnsiString fNameQuest[MaxDifLev];
//max number of Quests
int QuestMaxN[MaxDifLev];
int QuestCount;
const AnsiString fConfig="config.txt";
int level[MaxLevel];// кол-во правильных ответов ,. необходимое
// для достижения уровня
AnsiString mes[MaxLevel];// сообщение о достижении уровня
//
int intAnswer;// номер выбранного ответа
bool arrCheckBox[MaxNAnswer];
int nRight;// кол-во правильных ответов
TColor ColorBut=clPurple;
//max
int MaxQuest;
int MaxTime;
//
void __fastcall TFPassTest::ClearCheckArr()
{
for(int i=0;i<MaxNAnswer;i++)
{
	arrCheckBox[i]=false;
}
}

void __fastcall TFPassTest::ShowImg(const AnsiString & Path, const int n)
{
	/* определим высоту области, которую можно
использовать для вывода иллюстрации */
//область питання
		int RegHeight=BOk->Top-(LAsk->Top+LAsk->Height+10)
		-(RadBut[1]->Height+10)*n;
		Image1->Top=LAsk->Top+LAsk->Height+10;
		//загрузимо картинку і визначимо розмір
		Image1->AutoSize=true;
		Image1->Picture->LoadFromFile(Path);
// картинка не помещается
		if(Image1->Height>RegHeight)
		{
			Image1->AutoSize=false;
			Image1->Height=RegHeight;
			Image1->Proportional=true;
		}
		Image1->Visible=true;
}

//---------------------------------------------------------------------------
__fastcall TFPassTest::TFPassTest(TComponent* Owner): TForm(Owner)
{}
//
// щелчок на радиокнопке выбора ответа
void __fastcall TFPassTest::RadioButtonClick (TObject *Sender)
{
	int i=0;
	while (!RadBut[i]->Checked)
		i++;
	//
	intAnswer=++i;
	// ответ выбран, сделаем доступной кнопку Дальше
	BOk->Enabled=true;
}
//
//---------------------------------------------------------------------------
void __fastcall TFPassTest::FormActivate(TObject *Sender)
{
MaxQuest=0;
#ifdef DEBUG
LoadProfile("profiles\\id1\\profile1.txt");
#else
LoadProfile(FRegistration->profilePath);
#endif
Quest=Quest1;
//
Panel3->Visible=false;
Panel2->Visible=false;
//
Timer1->Enabled=false;
LHour->Visible=false;
LMinute->Visible=false;
LSecond->Visible=false;
LDoubDot->Visible=false;
LDoubDot2->Visible=false;
LTime->Visible=false;
// BEnd
BEnd->Visible=false;
//ProgBar
ProgressBar1->Visible=false;
LQuest->Visible=false;
LQuestMax->Visible=false;
//
 FPassTest->Caption="Тести";
 QuestMaxN[0]=0;
 QuestCount=0;
 intAnswer=-1;// номер выбранного ответа
 nRight=0;// кол-во правильных ответов
	// имя файла теста в файлі test name
//testList
TestNames = new TStringList();
TestNames->LoadFromFile(fTestNames);
if(TestNames->Count<1)
{
LAsk->Caption="Немає доступних тестів";
	TestNames->Free();
	return;
}
//якщо є імена тести
//ListTests
ListTests->Clear();
for(int i=0;i<TestNames->Count;++i){
	ListTests->Items->Add(TestNames->Strings[i].SubString(TestNames->Strings[i].Pos(":")+1,TestNames->Strings[i].Length()));
}

LAsk->Width=FPassTest->ClientWidth;
LAsk->Caption="Виберіть доступні тести";
LAsk->AutoSize=true;
ListTests->ItemIndex=0;
ListTests->Visible=true;
//description
MemoDesgr->Clear();
MemoDesgr->Visible=true;
LDesgr->Visible=true;
//
ListTestsClick(Sender);
//Bok
BOk->Tag=0;
BOk->Enabled=true;
BOk->Caption="Ok";
}
//---------------------------------------------------------------------------
int __fastcall TFPassTest::PosQuest()
{
	LAsk->Width=FPassTest->ClientWidth;
	LAsk->Caption=Quest->Ask;
	LAsk->AutoSize=true;
	if(Quest->Img!="")//є малюнок
	{
		ShowImg(Quest->Img,Quest->nAnswer);
	// положение полей отсчитываем от иллюстрации
	   return(Image1->Top+Image1->Height+10);
	}
	else// положение полей отсчитываем от вопроса
	{
		Image1->Visible=false;
		return(LAsk->Top+LAsk->Height+10);
	}
}
//
inline void TFPassTest::CheckBoxClear()
{
	for(int i=0;i<MaxNAnswer;++i)
	{
		CheckBox[i]->Checked=false;
	}
}
//
int __fastcall TFPassTest::SearchButLeft()
{
for(int i=0;i<Quest->nAnswer;i++)
{
	if(ButtonLeft[i]->Flat==true)
	{
		return i;
	}
}
//else
return -1;
}
//
int __fastcall  TFPassTest::SearchButRight()
{
for(int i=0;i<Quest->nAnswer;i++)
{
	if(ButtonRight[i]->Flat==true)
	{
		return i;
	}
}
//else
return -1;
}
//
void __fastcall  TFPassTest::BLeftOnClick(TObject *Sender)
{
	RemoveLeftFlat();
	//norm
	((TSpeedButton*)Sender)->Font->Color=ColorBut;
	((TSpeedButton*)Sender)->Flat=true;
	int i=SearchButRight();
	//add if right selected
	if(i>=0)
	{
		int temp;
		if(i==Quest3->NumPos[1][i] && ((temp=SearchButLeft())==Quest3->NumPos[0][temp]))
		{
		//add right answer
			arrCheckBox[i]=true;
		}
//
		ButtonRight[i]->Enabled=false;
		((TSpeedButton*)Sender)->Enabled=false;
		RemoveLeftFlat();
		RemoveRightFlat();
		return;
	}
}
//
void __fastcall  TFPassTest::BRightOnClick(TObject *Sender)
{
	RemoveRightFlat();
	//norm
	((TSpeedButton*)Sender)->Font->Color=ColorBut;
	((TSpeedButton*)Sender)->Flat=true;
	int i=SearchButLeft();
	//add if right selected
	if(i>=0)
	{
		int temp;              //0-2 2-2
		if(Quest3->NumPos[0][i]==Quest3->NumPos[1][SearchButRight()])
		{
		//add right answer
				arrCheckBox[i]=true;
		}
		ButtonLeft[i]->Enabled=false;
		((TSpeedButton*)Sender)->Enabled=false;
		RemoveLeftFlat();
		RemoveRightFlat();
		return;
	}
}
//
void __fastcall  TFPassTest::RemoveLeftFlat()
{
for(int i=0;i<Quest->nAnswer;i++)
{
	ButtonLeft[i]->Flat=false;
	ButtonLeft[i]->Font->Color=FPassTest->Font->Color;
}
}
//
void __fastcall  TFPassTest::RemoveRightFlat()
{
for(int i=0;i<Quest->nAnswer;i++)
{
	ButtonRight[i]->Flat=false;
	ButtonRight[i]->Font->Color=FPassTest->Font->Color;
}
}
//
void __fastcall TFPassTest::ShowQuest()
{
	int top;
	int i;
//ask
	 top=PosQuest();
switch (DifLevCount)
{
case 0:
	// варианты ответа
	for(i=0;i<Quest->nAnswer;i++)
	{
		RadBut[i]->Top=top;
		RadBut[i]->Caption=Quest1->Answer[i];
		RadBut[i]->Visible=true;
		RadBut[i]->Checked=false;
		top+=20;
	}
	break;
case 1:
	for(int i=0;i<Quest->nAnswer;i++)
	{
		CheckBox[i]->Top=top;
		CheckBox[i]->Caption=Quest2->Answer[i];
		CheckBox[i]->Visible=true;
		CheckBox[i]->Checked=false;
		top+=20;
	}
	break;
case 2:
	{	// варианты ответа
		for(int i=0;i<Quest->nAnswer;i++)
		{
		ButtonLeft[i]->Visible=true;
		ButtonRight[i]->Visible=true;
		ButtonLeft[i]->Caption=Quest3->Sentence[0][i];
		ButtonRight[i]->Caption=Quest3->Sentence[1][i];
	//position
		ButtonLeft[i]->Top=top;
		ButtonRight[i]->Top=top;
		top+=40;
		}
	//
	break;
	}
}
}
//
bool __fastcall TFPassTest::NextQuest(int numQuest)
{
	QuestCount++;
if(DifLevCount==MaxDifLev-1 && QuestCount>QuestMaxN[MaxDifLev-1])
{
	return false;
}
//else
if(QuestCount<=QuestMaxN[DifLevCount])
  {
	ProgressBar1->Position++;
	LQuest->Caption=IntToStr(ProgressBar1->Position);
	LQuestMax->Caption=IntToStr(ProgressBar1->Position)+"/"+IntToStr(ProgressBar1->Max);
//3level
	switch(DifLevCount)
	{
	case 0:
		Quest1->LoadFromFile(dirQuest+"\\"+fNameFolder+"\\"+fNameQuest[numQuest]+"_"+arrRandInt[QuestCount-1]+"\\"+"Quest.txt");
		break;
	case 1:
		Quest2->LoadFromFile(dirQuest+"\\"+fNameFolder+"\\"+fNameQuest[numQuest]+"_"+arrRandInt[QuestCount-1]+"\\"+"Quest.txt");
		break;
	case 2:
		Quest3->LoadFromFile(dirQuest+"\\"+fNameFolder+"\\"+fNameQuest[numQuest]+"_"+arrRandInt[QuestCount-1]+"\\"+"Quest.txt");
		break;
	}
	ShowQuest();
  }//
  else
  {
	QuestCount=0;
	DifLevCount++;
	switch(DifLevCount)
	{
	case 0:
		Quest=Quest1;
		break;
	case 1:
		Quest=Quest2;
		break;
	case 2:
		Quest=Quest3;
		break;
	}
	Panel3->Caption="Рівень: "+IntToStr(DifLevCount+1);
	gen_random_uniq(QuestMaxN[DifLevCount],arrRandInt,1,QuestMaxN[DifLevCount]);
	NextQuest(DifLevCount);
  }
//
QTime->SetTime(MaxTime+1);
	return true;
}
//
void __fastcall TFPassTest::ReadInfFromFile()
{
	fNameFolder=TestNames->Strings[ListTests->ItemIndex].SubString(0,TestNames->Strings[ListTests->ItemIndex].Pos(":")-1);
	ListTests->Visible=false;
	//open config file
	TStringList* TestConfig = new TStringList();
	TestConfig->LoadFromFile(dirQuest+"\\"+fNameFolder+"\\"+fConfig);
		//Show info about test
	int fCount=0;
	FPassTest->Caption=TestConfig->Strings[fCount].SubString(TestConfig->Strings[fCount].Pos("=")+1,TestConfig->Strings[fCount].Length());
	TestName=FPassTest->Caption;
	   // прочитать вводную информацию
	LAsk->Width=FPassTest->ClientWidth;//-LAsk->Left-20;
	fCount++;
	LAsk->Caption=TestConfig->Strings[fCount].SubString(TestConfig->Strings[fCount].Pos("=")+fCount,TestConfig->Strings[fCount].Length());
	LAsk->AutoSize=true;
	//img?
	fCount++;
	AnsiString img=TestConfig->Strings[fCount].SubString(TestConfig->Strings[fCount].Pos("=")+1,TestConfig->Strings[fCount].Length());
//
	if(img!="")
	{
		ShowImg(dirQuest+"\\"+fNameFolder+"\\"+img,0);
	}
	   // прочитать информацию об уровнях оценки
	for(int i=0;i<MaxLevel;i++)
	{
		level[i]=StrToInt(TestConfig->Strings[++fCount]);
		mes[i]=TestConfig->Strings[++fCount];
	}
	fCount++;
		//read folderQuestName
	for(int i=0;i<MaxDifLev;i++,fCount++)
	{
		fNameQuest[i]=TestConfig->Strings[fCount].SubString(TestConfig->Strings[fCount].Pos("=")+1,TestConfig->Strings[fCount].Length());
	}
		//read Quest max number
	for(int i=0;i<MaxDifLev;i++,fCount++)
	{
		QuestMaxN[i]=StrToInt(TestConfig->Strings[fCount].SubString(TestConfig->Strings[fCount].Pos("=")+1,TestConfig->Strings[fCount].Length()));
	}
	MaxQuest=QuestMaxN[0]+QuestMaxN[1]+QuestMaxN[2];
	//time
	QTime->SetTime(StrToInt((TestConfig->Strings[TestConfig->Count-1].SubString(TestConfig->Strings[TestConfig->Count-1].Pos("=")+1,TestConfig->Strings[TestConfig->Count-1].Length()))));
	MaxTime=QTime->GetTimeSMHSec();
	TestConfig->Free();
}
//
void __fastcall TFPassTest::GetSelectedCheckBox()
{
	for(int i=0;i<Quest->nAnswer;i++)
	{
		arrCheckBox[i]=CheckBox[i]->Checked;
	}
}
//
void __fastcall TFPassTest::LoadProfile(AnsiString str)
{
AnsiString data;
TStringList* SProfile =new TStringList();
SProfile->LoadFromFile(str);
for(int i=0;i<SProfile->Count;i++)
//шифр
{
	SProfile->Strings[i]=Code(SProfile->Strings[i],Key);
}
int count=1;
//імя
data="ІП:"+SProfile->Strings[count].SubString(SProfile->Strings[count].Pos("=")+1,SProfile->Strings[count].Length());
count++;
//фаміл
data+=" "+SProfile->Strings[count].SubString(SProfile->Strings[count].Pos("=")+1,SProfile->Strings[count].Length());
count++;
//група
data+=" Група:"+SProfile->Strings[count].SubString(SProfile->Strings[count].Pos("=")+1,SProfile->Strings[count].Length());
Panel1->Caption=data;
SProfile->Free();
}

void __fastcall TFPassTest::BOkClick(TObject *Sender)
{
// результат чтения из файла очередного вопроса
bool ok;
switch(BOk->Tag)
{
//вибір тесту загрузить тест
	case 0:
	{
		DifLevCount=0;
		Panel3->Visible=true;
		Panel2->Visible=true;
		Panel3->Caption="Рівень: "+IntToStr(DifLevCount+1);
		ReadInfFromFile();
	   //rand counter
		arrRandInt= new int[QuestMaxN[DifLevCount]];
		gen_random_uniq(QuestMaxN[DifLevCount],arrRandInt,1,QuestMaxN[DifLevCount]);
		//
	//description
	MemoDesgr->Visible=false;
	LDesgr->Visible=false;
//
	LHour->Visible=true;
	LMinute->Visible=true;
	LSecond->Visible=true;
	LDoubDot->Visible=true;
	LDoubDot2->Visible=true;
	LTime->Visible=true;
	updateTime(QTime);
//
	BOk->Tag=1;
	break;
	 }
	case 1:// щелчок на кнопке ОК в начале работы программы
		// прочитать и вывести первый вопрос
	{
		BOk->Caption="Далі";
	//visible
		BEnd->Visible=true;
	//LQuest
		LQuest->Caption=IntToStr(QuestCount);
		LQuestMax->Caption=IntToStr(QuestCount)+"/"+IntToStr(QuestMaxN[DifLevCount]);
		LQuest->Visible=true;
		LQuestMax->Visible=true;
	//ProgressBar
		ProgressBar1->Min=0;
		ProgressBar1->Max=MaxQuest;
		ProgressBar1->Position=0;
		ProgressBar1->Step=1;
		ProgressBar1->Visible=true;
    //Show Quest
		NextQuest(DifLevCount);
	//time start
		Timer1->Enabled=true;
		//next step
		BOk->Tag=2;
	break;
	}
	case 2://клік далі
	 {
	 //якщо правильний
	 switch(DifLevCount)
	 {
	 case 0:
		if(((TQuest1*)Quest)->isRight(intAnswer))
		{
			nRight++;
		}
		break;
	 case 1:
		GetSelectedCheckBox();
		if(((TQuest2*)Quest)->isRight(arrCheckBox))
		{
			nRight++;
		}
		break;
	 case 2:
	 {
		bool ok1=true;
		for(int i=0;i<Quest3->nAnswer;++i)
		{
			if(arrCheckBox[i]==false)
			{
				ok1=false;
			}
		}
		if(ok1)
		{
			nRight++;
		}
		//
		break;
	 }
	}
	 EraseQuest();
	 //? кінець тесту немає питань
		if(!NextQuest(DifLevCount))
		{
			BOk->Tag=3;
			EndTest();
		}
		break;
	 }
	 //restart
	 case 3:
	 {
		FormActivate(Sender);
		break;
	 }

}
}
//---------------------------------------------------------------------------
// удаляет вопрос с экрана
void __fastcall TFPassTest::EraseQuest(void){// скрыть поле вывода иллюстрации	Image1->Visible=false;// скрыть поля выбора ответаswitch (DifLevCount){
case 0:	for(int i=0;i<MaxNAnswer;i++)	{		RadBut[i]->Visible=false;		RadBut[i]->Checked=false;	}	intAnswer=-1;	break;case 1:	for(int i=0;i<MaxNAnswer;i++)	{		CheckBox[i]->Visible=false;		CheckBox[i]->Checked=false;		ClearCheckArr();	}	break;case 2:	for(int i=0;i<MaxNAnswer;i++)	{		ButtonLeft[i]->Enabled=true;		ButtonRight[i]->Enabled=true;		ButtonLeft[i]->Visible=false;		ButtonRight[i]->Visible=false;		RemoveRightFlat();		RemoveLeftFlat();		ClearCheckArr();	}	break;}}//
void __fastcall TFPassTest::EndTest(void)
{
//вивести результат
	Timer1->Enabled=false;
	BOk->Enabled=true;
	AnsiString st;//повідомлення
	int iLevel;
	FPassTest->Caption="Результат тесту";
	st.printf("Правильних відповідів: %i\n",nRight);
	st+="Не правильних відповідів:"+IntToStr(MaxQuest-nRight)+"\n";
	iLevel=0;
	while (( nRight < level[iLevel])&&(iLevel<MaxLevel-1))
		iLevel++;
	st=st+"Оцінка:"+mes[iLevel];
//write in file
	ofstream fileOut;
	fileOut.open(FRegistration->profilePath.c_str(), ios::app);
AnsiString temp=Code(TestName+":"+mes[iLevel],Key);
	fileOut<<temp.c_str();
	fileOut<<"\n";
	fileOut.close();
//show	result
	LAsk->Width=FPassTest->ClientWidth;
	LAsk->Caption=st;
	LAsk->AutoSize=true;
//
	BOk->Tag=3;
	BOk->Caption="Ok";
	BEnd->Visible=false;
	//
	delete [] arrRandInt;
}
//
//---------------------------------------------------------------------------
void __fastcall TFPassTest::BEndClick(TObject *Sender)
{
if(Application->MessageBox(L"Завершити тест?", L"", MB_YESNOCANCEL)==IDYES)
{
	EraseQuest();
	EndTest();
}
}
//---------------------------------------------------------------------------
void __fastcall TFPassTest::updateTime(const TimeSMH * TimeSMH0)
{
//многабукавкмбтребащосьзробити
	if(TimeSMH0->second<10)
		LSecond->Caption="0"+IntToStr(TimeSMH0->second);
	else
		LSecond->Caption=IntToStr(TimeSMH0->second);
	if(TimeSMH0->minute<10)
		LMinute->Caption="0"+IntToStr(TimeSMH0->minute);
	else
		LMinute->Caption=IntToStr(TimeSMH0->minute);
	if(TimeSMH0->hour<10)
		LHour->Caption="0"+IntToStr(TimeSMH0->hour);
	else
		LHour->Caption=IntToStr(TimeSMH0->hour);
}
//
void __fastcall TFPassTest::Timer1Timer(TObject *Sender)
{
	QTime->ChangeBy(-1);
	updateTime(QTime);
	if(QTime->GetTimeSMHSec()<=0)
	{
		EraseQuest();
	 //? кінець тесту немає питань
		if(!NextQuest(DifLevCount))
		{
			BOk->Tag=3;
			EndTest();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFPassTest::FormDestroy(TObject *Sender)
{
	ListTests->Free();
	MemoDesgr->Free();
	LDesgr->Free();
	delete Quest;
	delete QTime;
	TestNames->Free();
//
	for(int i=0;i<MaxNAnswer;i++)
		RadBut[i]->Free();
	for(int i=0;i<MaxNAnswer;i++)
		CheckBox[i]->Free();

}
//---------------------------------------------------------------------------
void __fastcall TFPassTest::FormCreate(TObject *Sender)
{
Quest1=new TQuest1();//питання 1
Quest2=new TQuest2();//питання 2
Quest3=new TQuest3();//питання 3

//
QTime=new TimeSMH();
int left=10;
// создадим радиокнопки для выбора
// правильного ответа, но сделаем их невидимыми
for(int i=0;i<MaxNAnswer;i++){
	RadBut[i]= new TRadioButton(FPassTest);
	//set properties
	RadBut[i]->Parent=FPassTest;
	RadBut[i]->Left=left;
	RadBut[i]->Width=FPassTest->ClientWidth-left-20;
	RadBut[i]->Visible=false;
	RadBut[i]->Checked=false;
	RadBut[i]->OnClick=RadioButtonClick;
}
//
 ListTests= new TListBox(FPassTest);
//set properties
	ListTests->Parent=FPassTest;
	ListTests->Left=10;
	ListTests->Width=FPassTest->ClientWidth-30;
	ListTests->Visible=false;
	ListTests->Enabled=true;
	ListTests->ExtendedSelect=true;
	ListTests->Top=30;
	ListTests->OnClick=ListTestsClick;
	ListTests->Color=clSkyBlue;
//
 LDesgr= new TLabel(FPassTest);
//set properties
	 LDesgr->Parent=FPassTest;
	 LDesgr->Left=10;
	 LDesgr->Width=FPassTest->ClientWidth-30;
	 LDesgr->Visible=false;
	 LDesgr->Enabled=true;
	 LDesgr->Top=ListTests->Top+ ListTests->Height+10;
	 LDesgr->Caption="Короткий опис";
//
 MemoDesgr= new TMemo(FPassTest);
 //set properties
	MemoDesgr->Parent=FPassTest;
	MemoDesgr->Left=10;
	MemoDesgr->Width=FPassTest->ClientWidth-30;
	MemoDesgr->Visible=false;
	MemoDesgr->Enabled=true;
	MemoDesgr->Top=LDesgr->Top+LDesgr->Height+10;
	MemoDesgr->Height=BOk->Top-MemoDesgr->Top-10;
	MemoDesgr->ReadOnly=true;
	MemoDesgr->BorderStyle=bsNone;
	MemoDesgr->WordWrap=true;
	MemoDesgr->ScrollBars=ssVertical;
	MemoDesgr->Color=clSkyBlue;
//
// создадим радиокнопки для выбора
// правильного ответа, но сделаем их невидимыми
for(int i=0;i<MaxNAnswer;i++)
{
	CheckBox[i]= new TCheckBox(FPassTest);
	//set properties
	CheckBox[i]->Parent=FPassTest;
	CheckBox[i]->Left=10;
	CheckBox[i]->Width=FPassTest->ClientWidth-20;
	CheckBox[i]->Visible=false;
	CheckBox[i]->Checked=false;
}
//
int leftpos=10;
int width=400;
int height=40;
int dist=50;
//
for(int i=0;i<MaxNAnswer;i++)
{
	ButtonLeft[i]= new TSpeedButton(FPassTest);
	ButtonRight[i]= new TSpeedButton(FPassTest);
}
for(int i=0;i<MaxNAnswer;i++)
{
	//set properties left
	ButtonLeft[i]->Parent=FPassTest;
	ButtonLeft[i]->Left=leftpos;
	ButtonLeft[i]->Width=width;
	ButtonLeft[i]->Height=height;
	ButtonLeft[i]->Visible=false;
	ButtonLeft[i]->OnClick=BLeftOnClick;
	//set properties  right
	ButtonRight[i]->Parent=FPassTest;
	ButtonRight[i]->Left=leftpos+width+dist;
	ButtonRight[i]->Width=width;
	ButtonRight[i]->Height=height;
	ButtonRight[i]->Visible=false;
	ButtonRight[i]->OnClick=BRightOnClick;
}

//
}
//---------------------------------------------------------------------------
void __fastcall TFPassTest::ListTestsClick(TObject *Sender)
{
//open config file
	TStringList* TestConfig = new TStringList();
	MemoDesgr->Clear();
	TestConfig->LoadFromFile(dirQuest+"\\"+
		TestNames->Strings[ListTests->ItemIndex].SubString(0,TestNames->Strings[ListTests->ItemIndex].Pos(":")-1)+"\\"+fConfig);
	//Show info about test
	MemoDesgr->Lines->Add("Опис:");
	MemoDesgr->Lines->Add(TestConfig->Strings[1].SubString(TestConfig->Strings[1].Pos("=")+1,TestConfig->Strings[1].Length()));
	 //read Quest max number
//shit
int count;
int temp=0;
for(count=4;count>1;count--)
{
	temp+=StrToInt(TestConfig->Strings[TestConfig->Count-count].SubString(TestConfig->Strings[TestConfig->Count-count].Pos("=")+1
	,TestConfig->Strings[TestConfig->Count-count].Length()));
}
//
	 MemoDesgr->Lines->Add("Кількість питань:"+IntToStr(temp));
//time
	 QTime->SetTime(StrToInt((TestConfig->Strings[TestConfig->Count-1].SubString(TestConfig->Strings[TestConfig->Count-1].Pos("=")+1,TestConfig->Strings[TestConfig->Count-1].Length()))));
//? 0 hr => no show
	 if(QTime->hour==0)
		MemoDesgr->Lines->Add("Час:"+IntToStr(QTime->minute)+"хв "+IntToStr(QTime->second)+"сек");
	 else
		MemoDesgr->Lines->Add("Час:"+IntToStr(QTime->hour)+"год "+IntToStr(QTime->minute)+"хв "+IntToStr(QTime->second)+"сек");
//
	TestConfig->Free();
}
//
void __fastcall TFPassTest::FormClose(TObject *Sender, TCloseAction &Action)
{
	FRegistration->Show();
}
//---------------------------------------------------------------------------


