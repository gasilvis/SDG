//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("SidDataGrabber.res");
USEFORM("Unit1.cpp", Form1);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->Title = "SidDataGrabber";
       Application->CreateForm(__classid(TForm1), &Form1);
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------
