//---------------------------------------------------------------------------

#ifndef UQuestH
#define UQuestH
//
#include <System.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
const int MaxNAnswer1=4;
//
class TQuest{
public:
	TQuest(){};
	~TQuest(){};
//
	virtual bool LoadFromFile(AnsiString str){};
	virtual bool isRight(){};
	AnsiString Ask;//ask
	AnsiString Img;//bmp-name
	int	nAnswer;
protected:
	void LoadPict(AnsiString sImg,AnsiString Path);
};
//class TQ
class TQuest1:public TQuest{
public:
	TQuest1(){};
	~TQuest1(){};
//
  	bool LoadFromFile(AnsiString str);
	bool isRight(int);
	int rAnswer;
	AnsiString Answer[MaxNAnswer1];
};
//
class TQuest2:public TQuest{
public:
	TQuest2(){};
	~TQuest2(){};
//
	bool LoadFromFile(AnsiString str);
	bool isRight(bool * arr);
	AnsiString Answer[MaxNAnswer1];
private:
	bool rAnswer[MaxNAnswer1];
};

class TQuest3:public TQuest{
public:
	TQuest3(){};
	~TQuest3(){};
//
	bool LoadFromFile(AnsiString str);
	bool isRight(bool * arr);
	int  NumPos[2][MaxNAnswer1];
	AnsiString Sentence[2][MaxNAnswer1];
};

#endif
