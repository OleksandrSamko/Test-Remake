//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "URegistration.h"
#include "UPassTest.h"
#include "UCode.h"
#include "UAdmin.h"

#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRegistration *FRegistration;
//

//admin
const AnsiString superLogin="1";
const AnsiString superPass="1";
//
//---------------------------------------------------------------------------
__fastcall TFRegistration::TFRegistration(TComponent* Owner)
	: TForm(Owner)
{
 dirProfile="profiles";
 fprofile="profile";
 fIdConf="idconf.txt";
}
//---------------------------------------------------------------------------

void __fastcall TFRegistration::Button1Click(TObject *Sender)
{
//check for input
if(LabeledEdit1->Text=="" || LabeledEdit2->Text=="" || LabeledEdit3->Text=="")
{
	LWarning->Caption="Заповніть всі поля";
	return;
}
LWarning->Caption="";
//else ok?
TStringList* SProfileId =new TStringList();
//зчитали id
SProfileId->LoadFromFile(dirProfile+"\\"+fIdConf);
int idLast=StrToInt(SProfileId->Strings[SProfileId->Count-1]);
idLast++;
//створюємо папку
if(DirectoryExists(dirProfile))
	MkDir(dirProfile+"\\id"+idLast);
else
{
	ShowMessage("Не знайдена папка "+dirProfile);
	return;
}
//створимо профайл
TStringList* SProfile =new TStringList();
SProfile->Add("id="+IntToStr(idLast));
SProfile->Add("firstName="+LabeledEdit1->Text);
SProfile->Add("lastName="+LabeledEdit2->Text);
SProfile->Add("group="+LabeledEdit3->Text);
SProfile->Add("sex="+ComboBox1->Text);
SProfile->Add("regDate="+Time()+";"+Date());
//
profilePath=dirProfile+"\\id"+idLast+"\\"+fprofile+idLast+".txt";
//шифр
for(int i=0;i<SProfile->Count;i++)
{
	SProfile->Strings[i]=Code(SProfile->Strings[i],Key);
}
//save
SProfile->SaveToFile(profilePath);
//запишемо новий id
// ios::app - открывает файл для записи в конец файла
AnsiString tempString=dirProfile+"\\"+fIdConf;
ofstream fileOut;
fileOut.open(tempString.c_str(), ios::app);
fileOut<<"\n"<<idLast;
fileOut.close();
SProfileId->Free();
SProfile->Free();
//
FPassTest->Show();
FRegistration->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TFRegistration::FormActivate(TObject *Sender)
{
LabeledEdit1->Text="";
LabeledEdit2->Text="";
LabeledEdit3->Text="";
LabeledEdit4->Text="";
LabeledEdit5->Text="";
Panel1->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TFRegistration::SpeedButton1Click(TObject *Sender)
{
	Panel1->Visible=!Panel1->Visible;
	if(!Panel1->Visible)
	{
	LabeledEdit3->Text="";
	LabeledEdit4->Text="";
	}
}
//---------------------------------------------------------------------------


void __fastcall TFRegistration::SpeedButton2Click(TObject *Sender)
{
if(LabeledEdit4->Text==superLogin && LabeledEdit5->Text==superPass)
{
//show admin
	FAdmin->Show();
	FRegistration->Hide();
}
else
	Application->MessageBox(L"В доступі відмовлено", L"", MB_OK);
}
//---------------------------------------------------------------------------

