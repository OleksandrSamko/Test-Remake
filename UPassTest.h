//---------------------------------------------------------------------------


#ifndef UPassTestH
#define UPassTestH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//
#include "UQuest.h"
#include "UTimeSMH.h"
//
const int MaxNAnswer=4;

//
//---------------------------------------------------------------------------
class TFPassTest : public TForm
{

__published:	// IDE-managed Components
	TLabel *LAsk;
	TImage *Image1;
	TButton *BOk;
	TButton *BEnd;
	TProgressBar *ProgressBar1;
	TLabel *LQuest;
	TLabel *LQuestMax;
	TTimer *Timer1;
	TLabel *LHour;
	TLabel *LDoubDot;
	TLabel *LMinute;
	TLabel *LSecond;
	TLabel *LDoubDot2;
	TLabel *LTime;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BOkClick(TObject *Sender);
	void __fastcall BEndClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	TRadioButton *RadBut[MaxNAnswer];//вибора
	TCheckBox *CheckBox[MaxNAnswer];//вибора
//
	TSpeedButton *ButtonLeft[MaxNAnswer];
	TSpeedButton *ButtonRight[MaxNAnswer];
//
	TListBox *ListTests;
	TMemo	*MemoDesgr;
	TLabel  *LDesgr;
	//
	TQuest* Quest;
	TQuest1* Quest1;
	TQuest2* Quest2;
    TQuest3* Quest3;
	//
	TimeSMH* QTime;
	TStringList* TestNames;
	int *arrRandInt;
// кнопке выбора ответа
	void __fastcall RadioButtonClick(TObject *Sender);// щелчок на
	void __fastcall GetSelectedCheckBox();
	void __fastcall ShowQuest();
	int __fastcall PosQuest();
	void __fastcall ReadInfFromFile();
	void __fastcall EraseQuest(void);
	//
	void __fastcall ClearCheckArr();
	void __fastcall BLeftOnClick(TObject *Sender);
	void __fastcall BRightOnClick(TObject *Sender);
	//
	void __fastcall EndTest(void);
	void __fastcall ShowImg(const AnsiString & Path, const int n);
	void __fastcall updateTime(const TimeSMH * Time);
	bool __fastcall NextQuest(int numQuest);
	void __fastcall ListTestsClick(TObject *Sender);
	inline void CheckBoxClear();
	void __fastcall LoadProfile(AnsiString str);
	//
	int __fastcall SearchButLeft();
	int __fastcall SearchButRight();
	void __fastcall RemoveLeftFlat();
	void __fastcall RemoveRightFlat();
public:		// User declarations
	__fastcall TFPassTest(TComponent* Owner);
	AnsiString TestName;
};
//---------------------------------------------------------------------------
extern PACKAGE TFPassTest *FPassTest;
//---------------------------------------------------------------------------
#endif
