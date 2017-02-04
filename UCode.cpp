//---------------------------------------------------------------------------

#pragma hdrstop

#include "UCode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

AnsiString Code(AnsiString s, char Key)
{
for (int i=1; i<=s.Length();i++)
s[i]=s[i]^Key;
return s;
}

