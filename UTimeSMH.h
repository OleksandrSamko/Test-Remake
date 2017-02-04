//---------------------------------------------------------------------------

#ifndef UTimeSMHH
#define UTimeSMHH
//---------------------------------------------------------------------------
class TimeSMH
{
public:
	TimeSMH(int s = 0, int m = 0, int h = 0);
	int GetTimeSMHSec()const;
	void ChangeBy(const int s=1);
	void SetTime(int s = 0, int m = 0, int h = 0);
	~TimeSMH(){};
private:
	void GetNormalView();
	void CheckVal();
	int hr;
	int min;
	int sec;
public:
	__property int hour = {read=hr};
	__property int minute = {read=min};
	__property int second = {read=sec};
};
#endif
