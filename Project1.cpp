//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

//---------------------------------------------------------------------------
USEFORM("UPassTest.cpp", FPassTest);
USEFORM("URegistration.cpp", FRegistration);
USEFORM("UAdmin.cpp", FAdmin);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = false;
		Application->CreateForm(__classid(TFRegistration), &FRegistration);
		Application->CreateForm(__classid(TFPassTest), &FPassTest);
		Application->CreateForm(__classid(TFAdmin), &FAdmin);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
