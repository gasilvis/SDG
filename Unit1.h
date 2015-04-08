//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <chartfx3.hpp>
#include <OleCtrls.hpp>
#include <vcfi.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <Series.hpp>
#include "ElastFrm.hpp"
#include <ComCtrls.hpp>
#include <HttpProt.hpp>
#include <NMHttp.hpp>
#include <Psock.hpp>
#include <NMURL.hpp>
//#include "SHDocVw_OCX.h"
#include <ArrowCha.hpp>
//#include <IcsLogger.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TOpenDialog *OpenDialog1;
   TMainMenu *MainMenu1;
   TMenuItem *File1;
   TMenuItem *Open1;
   TMenuItem *Quit1;
   TElasticForm *ElasticForm1;
   TPageControl *PageControl1;
   TTabSheet *graphTab;
   TTabSheet *reportTab;
   TChart *Chart1;
   TLineSeries *Series1;
   TMemo *Memo1;
   TGroupBox *GroupBox1;
   TEdit *startEdit;
   TRadioButton *startRB;
   TRadioButton *maxRB;
   TEdit *maxEdit;
   TRadioButton *endRB;
   TEdit *endEdit;
   TLabel *Label1;
   TLabel *stationLabel;
   TLabel *freqLabel;
   TLabel *Label2;
   TComboBox *definitionCB;
   TLabel *Label3;
   TEdit *observerEdit;
   TButton *Button1;
   TButton *Button2;
   TButton *Button3;
   TButton *addButton;
   TTabSheet *helpTab;
   TMemo *Memo2;
   TLabel *reportLabel;
   TButton *reportDirSelect;
   TLabel *Label4;
   TButton *Button6;
   TEdit *importanceEdit;
   TLabel *Label6;
   TTabSheet *bufferTab;
   TLabel *Label7;
   TButton *ProcessBufferFileButton;
   TButton *Button5;
   TLabel *lastFileLabel;
   TMemo *Memo3;
   TMemo *Memo4;
   TNMHTTP *NMHTTP1;
   THttpCli *HttpCli1;
   TNMURL *NMURL1;
   TButton *Button4;
   TLabel *versionLabel;
   TButton *Button7;
   TGroupBox *GroupBox2;
   TRadioButton *reportByMonth;
   TRadioButton *reportBymonthandstation;
   TMenuItem *SetLogtype1;
   TMenuItem *LogTypeSuperSID;
   TMenuItem *LogTypeLASPextract;
   TEdit *stationEdit;
   TEdit *freqEdit;
   void __fastcall Open1Click(TObject *Sender);
   void __fastcall Quit1Click(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall Chart1ClickSeries(TCustomChart *Sender,
          TChartSeries *Series, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y);
   void __fastcall observerEditExit(TObject *Sender);
   void __fastcall Button2Click(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall Button3Click(TObject *Sender);
   void __fastcall reportDirSelectClick(TObject *Sender);
   void __fastcall addButtonClick(TObject *Sender);
   void __fastcall Button6Click(TObject *Sender);
   void __fastcall ProcessBufferFileButtonClick(TObject *Sender);
   void __fastcall Button4Click(TObject *Sender);
   void __fastcall HttpCli1DocBegin(TObject *Sender);
   void __fastcall HttpCli1DocEnd(TObject *Sender);
   void __fastcall Button7Click(TObject *Sender);
   void __fastcall versionLabelClick(TObject *Sender);
   void __fastcall reportByMonthClick(TObject *Sender);
   void __fastcall LogTypeSuperSIDClick(TObject *Sender);
   void __fastcall stationEditExit(TObject *Sender);
   void __fastcall freqEditExit(TObject *Sender);
private:	// User declarations

public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
   void __fastcall TForm1::displayNextFile(TObject *Sender);
   bool __fastcall TForm1::openReportFile(TObject *Sender, bool create);
   void __fastcall TForm1::logMsg(TObject *Sender, AnsiString msg);
   bool __fastcall TForm1::IsSafeChar(int ch);
   AnsiString __fastcall TForm1::EncodeURIComponent(AnsiString ASrc);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
