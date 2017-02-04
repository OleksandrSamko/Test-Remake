//---------------------------------------------------------------------------

#pragma hdrstop

#include "UQuest.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
bool TQuest1::LoadFromFile(AnsiString str)
{
TStringList* Quest = new TStringList();
Quest->LoadFromFile(str);

if(Quest->Count>0)
{
// прочитать кол-во вариантов ответа, номер правильного ответа
// и наличия иллюстрации
	this->Ask=Quest->Strings[0].SubString(Quest->Strings[0].Pos("=")+1,Quest->Strings[0].Length());
	this->nAnswer=StrToInt(Quest->Strings[1].SubString(Quest->Strings[1].Pos("=")+1,Quest->Strings[1].Length()));
	this->rAnswer=StrToInt(Quest->Strings[2].SubString(Quest->Strings[2].Pos("=")+1,Quest->Strings[2].Length()));
AnsiString s=Quest->Strings[3].SubString(Quest->Strings[3].Pos("=")+1,Quest->Strings[3].Length());
//is picture
	this->LoadPict(s,str);
	// читаем варианты ответа
   for(int i=0, fAnsr=3;i<this->nAnswer;i++)
	{
		this->Answer[i]=Quest->Strings[++fAnsr];
	}
	Quest->Free();
	return true;
}
//else
	Quest->Free();
	return false;
}

bool TQuest1::isRight(int ans)
{
	if(ans==rAnswer)
	{
		return true;
	}
	else
		return false;
}

void TQuest::LoadPict(AnsiString s, AnsiString str)
{
	if(s!="")
	{
		AnsiString Dir="";
		while(str.Pos("\\")!=0)
		{
			Dir+=str.SubString(0,str.Pos("\\"));
			str=str.SubString(str.Pos("\\")+1,str.Length());
		}//Dir
		this->Img=Dir+s;
	}
	else
		this->Img="";
}

bool TQuest2::LoadFromFile(AnsiString str)
{
TStringList* Quest = new TStringList();
Quest->LoadFromFile(str);

if(Quest->Count>0)
{
// прочитать кол-во вариантов ответа, номер правильних ответов
// и наличия иллюстрации
	this->Ask=Quest->Strings[0].SubString(Quest->Strings[0].Pos("=")+1,Quest->Strings[0].Length());
	this->nAnswer=StrToInt(Quest->Strings[1].SubString(Quest->Strings[1].Pos("=")+1,Quest->Strings[1].Length()));
	//this->rAnswer=StrToInt(Quest->Strings[2].SubString(Quest->Strings[2].Pos("=")+1,Quest->Strings[2].Length()));
wchar_t* rAnsw=new wchar_t[MaxNAnswer1];
	rAnsw=Quest->Strings[2].SubString(Quest->Strings[2].Pos("=")+1,Quest->Strings[2].Length()).c_str();
//
for(int i=0;i<MaxNAnswer1;i++)
{
	if(rAnsw[i]=='1')
	{
		rAnswer[i]=true;
	}
	else
		rAnswer[i]=false;
}
delete [] rAnsw;
//
//picture
AnsiString s=Quest->Strings[3].SubString(Quest->Strings[3].Pos("=")+1,Quest->Strings[3].Length());
//is picture
	this->LoadPict(s,str);
// читаем варианты ответа
   for(int i=0, fAnsr=3;i<this->nAnswer;i++)
	{
		this->Answer[i]=Quest->Strings[++fAnsr];
	}
	Quest->Free();
	return true;
}
//else
	Quest->Free();
	return false;
}

bool TQuest2::isRight(bool * arr)
{
	for(int i=0;i<nAnswer;++i)
	{
		if(rAnswer[i]!=arr[i])
		return false;
	}
	return true;
}

bool TQuest3::LoadFromFile(AnsiString str)
{
TStringList* Quest = new TStringList();
Quest->LoadFromFile(str);

if(Quest->Count>0)
{
int fCount=0;
// прочитать кол-во вариантов ответа, номер правильних ответов
// и наличия иллюстрации
	this->Ask=Quest->Strings[fCount].SubString(Quest->Strings[fCount].Pos("=")+1,Quest->Strings[fCount].Length());
	fCount++;
	this->nAnswer=StrToInt(Quest->Strings[fCount].SubString(Quest->Strings[fCount].Pos("=")+1,Quest->Strings[fCount].Length()));
	fCount++;
//read relation
for(int j=0;j<2;j++)
	for(int i=0;i<nAnswer;++i,fCount++)
	{
		NumPos[j][i]=StrToInt(Quest->Strings[fCount].SubString(0,Quest->Strings[fCount].Pos(":")-1));
		Sentence[j][i]=Quest->Strings[fCount].SubString(Quest->Strings[fCount].Pos(":")+1,Quest->Strings[fCount].Length());
	//next step
	}
	Quest->Free();
	return true;
}
//else
	Quest->Free();
	return false;
}
