//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UAdmin.h"
#include "URegistration.h"
#include "UCode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFAdmin *FAdmin;
//
//---------------------------------------------------------------------------
__fastcall TFAdmin::TFAdmin(TComponent* Owner)
	: TForm(Owner)
{
}
//
void __fastcall TFAdmin::LoadProfile(AnsiString str, int row)
{
AnsiString data;
TStringList* SProfile = new TStringList();
SProfile->LoadFromFile(str);
//�������
for(int i=0;i<SProfile->Count;i++)
{
	SProfile->Strings[i]=Code(SProfile->Strings[i],Key);
}
//
int count;
for(count=0;count<6;count++)
{
	StringGrid1->Cells[count][row]=
		SProfile->Strings[count].SubString(SProfile->Strings[count].Pos("=")+1,SProfile->Strings[count].Length());
}
//
//++count;
if(SProfile->Count>6)
{
	StringGrid1->Cells[count][row]=
		SProfile->Strings[count].SubString(0,SProfile->Strings[count].Pos(":")-1);
	StringGrid1->Cells[count+1][row]=
		SProfile->Strings[count].SubString(SProfile->Strings[count].Pos(":")+1,SProfile->Strings[count].Length());
}//
SProfile->Free();
}
//---------------------------------------------------------------------------
void __fastcall TFAdmin::FormActivate(TObject *Sender)
{
TStringList* SProfileId =new TStringList();
//������� id
SProfileId->LoadFromFile(FRegistration->dirProfile+"\\"+FRegistration->fIdConf);
int idLast=StrToInt(SProfileId->Strings[SProfileId->Count-1]);
//set grid
StringGrid1->ColCount=8;
StringGrid1->RowCount=idLast+1;
int count=0;
StringGrid1->Cells[count][0]="id";
StringGrid1->Cells[++count][0]="���";
StringGrid1->Cells[++count][0]="�������";
StringGrid1->Cells[++count][0]="�����";
StringGrid1->Cells[++count][0]="�����";
StringGrid1->Cells[++count][0]="���� ���.";
StringGrid1->Cells[++count][0]="����";
StringGrid1->Cells[++count][0]="������";
//
for(int profileI=1, rowI=1;profileI<=idLast;profileI++,rowI++)
{
	LoadProfile(FRegistration->dirProfile+"\\id"+profileI+"\\"+FRegistration->fprofile+profileI+".txt",rowI);
}
SProfileId->Free();
}
//---------------------------------------------------------------------------
void __fastcall TFAdmin::FormClose(TObject *Sender, TCloseAction &Action)
{
	FAdmin->Hide();
	FRegistration->Show();
}
//---------------------------------------------------------------------------


