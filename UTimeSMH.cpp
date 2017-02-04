//---------------------------------------------------------------------------

#pragma hdrstop

#include "UTimeSMH.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
TimeSMH::TimeSMH(int s, int m, int h):
sec(s),min(m),hr(h)
{
	GetNormalView();
}

void TimeSMH::SetTime(int s, int m, int h)
{
	sec=s;
	min=m;
	hr=h;
	GetNormalView();
}
//
int TimeSMH::GetTimeSMHSec()const
{
	return ((hr*60+min)*60+sec);
}
//
void TimeSMH::ChangeBy(const int s)
{
	this->SetTime(GetTimeSMHSec()+s);
}
//
void TimeSMH::GetNormalView()
{
	CheckVal();
	if(sec>=60)
	{
		min=sec/60;
		sec=sec%60;
	}
	//
	if(min>=60)
	{
		hr=min/60;
		min=min%60;
	}
}

void TimeSMH::CheckVal()
{
	if(hr<0)
		hr=0;
	if(min<0)
		min=0;
	if(sec<0)
		sec=0;
}

