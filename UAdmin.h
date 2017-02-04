//---------------------------------------------------------------------------

#ifndef UAdminH
#define UAdminH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TFAdmin : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	void __fastcall TFAdmin::LoadProfile(AnsiString str, int row);
public:		// User declarations
	__fastcall TFAdmin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFAdmin *FAdmin;
//---------------------------------------------------------------------------
#endif
