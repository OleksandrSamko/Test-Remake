//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//
#include <stdio.h>
#include <Vcl.Imaging.pngimage.hpp>
#include <cstdlib>
#include <fstream>
//

//---------------------------------------------------------------------------
class TFRegistration : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TButton *Button1;
	TLabeledEdit *LabeledEdit1;
	TLabeledEdit *LabeledEdit2;
	TLabel *Label1;
	TComboBox *ComboBox1;
	TLabel *Label2;
	TLabel *LWarning;
	TLabeledEdit *LabeledEdit3;
	TSpeedButton *SpeedButton1;
	TPanel *Panel1;
	TLabeledEdit *LabeledEdit4;
	TLabeledEdit *LabeledEdit5;
	TSpeedButton *SpeedButton2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TFRegistration(TComponent* Owner);
		AnsiString profilePath;
	AnsiString dirProfile;
	AnsiString fprofile;
	AnsiString fIdConf;
};
//---------------------------------------------------------------------------
extern PACKAGE TFRegistration *FRegistration;

//---------------------------------------------------------------------------
#endif
