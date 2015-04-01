//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <IniFiles.hpp>
#include <FileCtrl.hpp>
#include <stdio.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ElastFrm"
#pragma link "HttpProt"
#pragma link "IcsLogger"
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

#define Version 1.04
AnsiString dataDir, reportDir, reportFile, reportPath, lastFile; // Path is the combination of Dir and File

AnsiString INIfilename= "";
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   //TScreen->MenuFont=       ??  trying to set menufont. can't do
   // set window header
   Form1->Caption= "SID Data Grabber Application, "+ FormatFloat("version 0.00", Version);
   // collect INI file entries
   TIniFile *ini;
   if(0==INIfilename.Length()) { // first time
      INIfilename= ChangeFileExt( Application->ExeName, ".INI");
      ini= new TIniFile(INIfilename);
      INIfilename= ini->ReadString("Setup", "INI", INIfilename); // allows changing the INIfilename some day
      delete ini;
   }
   ini = new TIniFile(INIfilename);

   OpenDialog1->FilterIndex= ini->ReadInteger("Setup", "FilterIndex", 2); // default to all
   dataDir= ini->ReadString("Setup", "dataDir", "");
   observerEdit->Text= ini->ReadString("Setup", "Observer", "");
   Label4->Caption= reportDir= ini->ReadString("Setup", "reportDir", "");
   reportFile= ini->ReadString("Setup", "reportFile", "None");
   lastFile= ini->ReadString("Setup", "lastFile", "");
   lastFileLabel->Caption= lastFile;
   openReportFile(Sender, false);
   delete ini;

}
//---------------------------------------------------------------------------
AnsiString dataFile;   
TStrings *dataFiles= new TStringList;
int filesIndex= -1;

void __fastcall TForm1::Open1Click(TObject *Sender)
{
   if(observerEdit->Text == "" || reportDir == "") {
      ShowMessage("Must set Observer and report directory before selecting files");
   } else {
      OpenDialog1->Title= "Select a logging file";
      OpenDialog1->Options << ofAllowMultiSelect << ofFileMustExist;
      OpenDialog1->InitialDir= dataDir;
      // in ini file OpenDialog1->FilterIndex = 0; // start the dialog showing all files
      if(OpenDialog1->Execute()){
         dataFiles= OpenDialog1->Files;
         filesIndex= 0;
         displayNextFile(Sender);
      };
      // get observer? No.
      // Save selection info
      TIniFile *ini= new TIniFile(INIfilename);
      ini->WriteString("Setup", "dataDir", dataDir); // set in displayNextFile
      ini->WriteInteger("Setup", "FilterIndex", OpenDialog1->FilterIndex);
      delete ini;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Quit1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
AnsiString Site, StationID, Frequency;
int SampleRate= 0, sidMonitor= 0;
int startMin, endMin, maxMin, yr, mo, day;

void __fastcall TForm1::displayNextFile(TObject *Sender)
{
    dataFile= dataFiles->Strings[filesIndex];
    dataDir= dataFile.SubString(1, dataFile.LastDelimiter("\\"));//- 2);
    FILE* fp= fopen(dataFile.c_str(), "r");
    char buf[65];
    int /* global: yr, mo, day,*/ hr, min, sec, x;
    float dp, time= 0;
    AnsiString sb;
    float y;

    Chart1->Series[0]->Clear();
    Chart1->Title->Text->Clear();
    Chart1->Title->Text->Add(dataFile);
    lastFile= dataFile;
    TIniFile *ini = new TIniFile(INIfilename);
    ini->WriteString("Setup", "lastFile", lastFile);
    delete ini;
    lastFileLabel->Caption= lastFile;

    startRB->Checked= true; // start at the start
    startMin= maxMin= endMin= 0;
    yr= mo= 0;
    while(fgets(buf, 64, fp)) {
        if(buf[0]=='#') {
           sb= AnsiString(buf).TrimRight(); // cut the \n
           if(sb.SubString(2, 13)== " StationID = ") {
              StationID= sb.SubString(15, 20).TrimRight().TrimLeft();
              stationLabel->Caption= "Station:  "+StationID;
           } else if(sb.SubString(2, 13)== " Frequency = ") {
              Frequency= sb.SubString(15, 20).TrimRight().TrimLeft();
              //Frequency= sb.sprintf("%g", y); // g fmt loses the trailing 0's
              freqLabel->Caption= "Freq:  "+ Frequency;
           } else if(sb.SubString(2, 14)== " SampleRate = ") {
              SampleRate= sb.SubString(16, 20).ToInt();
           } else if(sb.SubString(2, 13)== " MonitorID = ") {
              sidMonitor= sb.SubString(15, 20).ToInt();
           } else if(sb.SubString(2, 8)== " Site = ") {
              Site= sb.SubString(10, 20).TrimRight().TrimLeft();
           }
        } else {
          //2015-03-01 00:00:10, 50885.6558753    eg
          x=sscanf(buf, "%04d-%02d-%02d %02d:%02d:%02d, %f\n", &yr, &mo, &day, &hr, &min, &sec, &dp); // %d avoids %i confusion over octal eg 08
          if(7==x) {
             time= (hr + (min+ sec/60.0)/60.0)/24.0; // put in days
             x=Chart1->Series[0]->AddXY(time, dp, "", clTeeColor);
          } else {
             ShowMessage("bad data line: "+ AnsiString(buf));
          }
       }
    }
    Chart1->UndoZoom();
    fclose(fp);
    //TBD is the file complete? clear dataFile if not
    if(StationID=="" || Frequency=="") {
       dataFile= "";
       ShowMessage("Data file does not include station or frequency");
    } else {
       reportFile= observerEdit->Text+ sb.sprintf("_%04d%02d", yr, mo)+ ".txt";
       openReportFile(Sender, true);
    }
/*   problem with arrow chart..
    // add flare information
    Chart1->Series[1]->Clear();
    Chart1->Series[1]->AddXY(.3, 100000, "", clTeeColor);
    Chart1->Series[1]->AddXY(.6, 100000, "", clTeeColor);
    Chart1->Series[1]->AddXY(.8, 100000, "", clTeeColor);
    Chart1->Series[1]->AddXY(.9, 100000, "", clTeeColor);
*/    
}
//---------------------------------------------------------------------------

bool __fastcall TForm1::openReportFile(TObject *Sender, bool create)
{
   FILE *rf;
   bool ret= true;
   if(reportFile=="None") {
      Memo1->Lines->Clear();
      reportLabel->Caption= reportFile;
      ret= false;
   } else {
      reportPath= reportDir+ "\\"+ reportFile;
      if(reportPath!= reportLabel->Caption) { // must have changed
         rf= fopen(reportPath.c_str(), "rt"); // does file exist?
         if(rf) { // yes
            fclose(rf);
            Memo1->Lines->LoadFromFile(reportPath);
         } else { // no file
            Memo1->Lines->Clear();
            //reportFile= "None";
            // create file?
            if(create) {
               rf= fopen(reportPath.c_str(), "a+t");
               if(rf==NULL) {
                  ShowMessage("Problem creating report file: "+ reportPath);
                  logMsg(Sender, "report file create problem: "+ reportPath);
                  ret= false;
                  reportFile= "None";
               } else {
                  fclose(rf);
                  logMsg(Sender, "report file: "+ reportFile);
              }
           }
         }

         reportLabel->Caption= (reportFile=="None")? AnsiString("None"): reportPath;
         // Save report file info
         TIniFile *ini = new TIniFile(INIfilename);
         ini->WriteString("Setup", "reportDir", reportDir);
         ini->WriteString("Setup", "reportFile", reportFile);
         delete ini;
      }
   }
   return ret;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Chart1ClickSeries(TCustomChart *Sender,
      TChartSeries *Series, int ValueIndex, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
      unsigned short  hr, min, sec, msec, len;
      AnsiString s;
      DecodeTime(Chart1->Series[0]->XValue[ValueIndex], hr, min, sec, msec);

      if(startRB->Checked) {
         startEdit->Text= s.sprintf("%02d%02d", hr, min);
         startMin= hr*60 + min;
         maxRB->Checked= true;
      } else if (maxRB->Checked) {
         maxEdit->Text= s.sprintf("%02d%02d", hr, min);
         maxMin= hr*60 + min;
         if(maxMin<startMin) ShowMessage("max cannot be before start");
         else  endRB->Checked= true;
      } else if (endRB->Checked) {
         endEdit->Text= s.sprintf("%02d%02d", hr, min);
         endMin= hr*60 + min;
         if(endMin < maxMin) ShowMessage("end cannot be before start");
         else startRB->Checked= true;
      }
      len= endMin- startMin;
      if     (len<19)  importanceEdit->Text= "1-";
      else if(len<26)  importanceEdit->Text= "1 ";
      else if(len<33)  importanceEdit->Text= "1+";
      else if(len<46)  importanceEdit->Text= "2 ";
      else if(len<86)  importanceEdit->Text= "2+";
      else if(len<126) importanceEdit->Text= "3 ";
      else             importanceEdit->Text= "3+";
}
//---------------------------------------------------------------------------





void __fastcall TForm1::observerEditExit(TObject *Sender)
{
    // save to ini
   TIniFile *ini;
   ini = new TIniFile(INIfilename);
   ini->WriteString("Setup", "Observer", observerEdit->Text);
   delete ini;
   // test code     logMsg(Sender, observerEdit->Text);  // test
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    Chart1->UndoZoom();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
   if(filesIndex==-1) {
      ShowMessage("No files opened");
   }else if(filesIndex== dataFiles->Count - 1) {
      ShowMessage("you're looking at the last file in the list");
   } else {
      filesIndex++;
      displayNextFile(Sender);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
   if(filesIndex==-1) {
      ShowMessage("No files opened");
   }else if(filesIndex== 0) {
      ShowMessage("you're looking at the first file in the list");
   } else {
      filesIndex--;
      displayNextFile(Sender);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::reportDirSelectClick(TObject *Sender)
{
	AnsiString Directory = "C:\\";
   if(SelectDirectory(Directory, TSelectDirOpts() << sdAllowCreate << sdPerformCreate << sdPrompt, 1000)) {
      TIniFile *ini;
      ini = new TIniFile(INIfilename);
      ini->WriteString("Setup", "reportDir", Directory);
      delete ini;
      reportDir= Directory;
      Label4->Caption= reportDir;
   }
}
//---------------------------------------------------------------------------

// add an event to the report file
void __fastcall TForm1::addButtonClick(TObject *Sender)
{
   AnsiString s, st, mt, et, imp, def; int freq;
   // obs and report dir set?
   if(observerEdit->Text == "" || reportDir == "") {
      ShowMessage("Must set Observer and report directory before adding events");
   } else {
      // report file ready
      if(openReportFile(Sender, true)) {
         // is the data complete?
         st= (startEdit->Text+ "     ").SubString(1,5);
         mt= (maxEdit->Text+ "     ").SubString(1,5);
         et= (endEdit->Text+ "     ").SubString(1,5);
         imp= (importanceEdit->Text+ "  ").SubString(1,2);
         def= (definitionCB->Text+ " ").SubString(1,1);
         freq= (500+ Frequency.ToInt())/1000;
         // compose record
         s.sprintf("40   %02i%02i%02i  %5s%5s%5s                %2s    %1s%2s%02i              %s"
            , yr-2000, mo, day, st, et, mt, imp, def, StationID.SubString(2,2), freq, observerEdit->Text);
         // clear
         startEdit->Text= "";
         maxEdit->Text= "";
         endEdit->Text= "";
         // special handling of endtime D :
         if(et[5]=='D') {
            startEdit->Text= et.SubString(1, 4);
            startMin= endMin;
            maxMin= endMin= 0;
            maxRB->Checked= true;
         } else {
            startMin= maxMin= endMin= 0;
         }
         // append record
         Memo1->Lines->Add(s);
         Memo1->Lines->SaveToFile(reportLabel->Caption);
         Chart1->UndoZoom();
      }



   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
   Memo1->Lines->SaveToFile(reportDir+ "\\"+ reportFile);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::logMsg(TObject *Sender, AnsiString msg)
{
      AnsiString s;
   //   TStream *DataIn; int I;
   //   char cp[10000];


      // log the process
      s= "http://www.gasilvis.com/SID/SIDlog.php?logentry=";
      s+= observerEdit->Text;
      s+= ", "+ FormatFloat("0.00", Version);
      s+= ", "+ msg;
      s= EncodeURIComponent(s);
      // doesn't work. Encodes too many things. Just need space to %20
      //NMURL1->InputString= s;
      //s= NMURL1->Encode;
      NMHTTP1->Get(s);
   /*
      HttpCli1->URL        = s;
      HttpCli1->RcvdStream = NULL;
      try {
         Form1->HttpCli1->Get();
      } __except (TRUE) {
             Form1->Memo4->Lines->Add(s);
             Form1->Memo4->Lines->Add("GET Failed !");
             Form1->Memo4->Lines->Add("StatusCode   = " + IntToStr(Form1->HttpCli1->StatusCode));
             Form1->Memo4->Lines->Add("ReasonPhrase = " + Form1->HttpCli1->ReasonPhrase);
             //return 0;
      }
   */
}
/*
void __fastcall TForm1::HttpCli1DocBegin(TObject *Sender)
{
    //Memo4->Lines->Add(HttpCli1->ContentType + " => " + HttpCli1->DocName);
    //Memo4->Lines->Add("Document = " + HttpCli1->DocName);
    HttpCli1->RcvdStream = new TFileStream(HttpCli1->DocName, fmCreate);
}

void __fastcall TForm1::HttpCli1DocEnd(TObject *Sender)
{
    if (HttpCli1->RcvdStream) {
        delete HttpCli1->RcvdStream;
        HttpCli1->RcvdStream = NULL;
    }
}
//---------------------------------------------------------------------------
*/

void __fastcall TForm1::ProcessBufferFileButtonClick(TObject *Sender)
{
   #define numStations  10
   FILE* cbf, *df[numStations];
   char buf[256], *T;
   int stationCnt= 0, i, hr, min, sec, secs, secinc;
   AnsiString Site, Long, Lat, startTime, interval, Stations[numStations], freqs[numStations], s;

   OpenDialog1->Title= "Select a current_buffers file";
   OpenDialog1->Options << ofFileMustExist;
   // in ini file OpenDialog1->FilterIndex = 0; // start the dialog showing all files
   if(OpenDialog1->Execute()){
       cbf= fopen(OpenDialog1->Files->Strings[0].c_str(), "rt");
       df[0]= NULL;
       if(cbf!= NULL) {
          Memo3->Lines->Clear();
          while(fgets(buf, 255, cbf)) {
             if(buf[0]=='#') { // collect header
                if     (0==strncmp(buf, "# Site = ", 9)) Site= AnsiString(&buf[9]).TrimRight();
                else if(0==strncmp(buf, "# UTC_StartTime = ", 18)) startTime= AnsiString(&buf[18]).TrimRight();
                else if(0==strncmp(buf, "# LogInterval =  ", 17)) interval= AnsiString(&buf[17]).TrimRight();
                else if(0==strncmp(buf, "# Stations = ", 13)) {
                   T= strtok(&buf[13], " ,\r\n");
                   while(T) {
                      Stations[stationCnt++]= AnsiString(T);
                      T= strtok(NULL, " ,\r\n");
                   }
                }
                else if(0==strncmp(buf, "# Frequencies = ", 16)) {
                   T= strtok(&buf[16], " ,\r\n");
                   i= 0;
                   while(T) {
                      freqs[i++]= AnsiString(T);
                      T= strtok(NULL, " ,\r\n");
                   }
                }
             } else { // data records
                // create files?
                if(df[0]==NULL) {
                   for(i= 0; i< stationCnt; i++) {
                      s= dataDir/* + "\\"  */+ Site+ "_"+ Stations[i]+ "_"+ startTime.SubString(1, 10)+ "_CB.csv"  ;
                      df[i]= fopen(s.c_str(), "wt");
                      //if(df[i]==NULL) perror("Error");
                      //else {
                      Memo3->Lines->Add("create file: "+ s);
                      fputs(("# Site = "+ Site+ "\r\n").c_str(), df[i]);
                      fputs(("# UTC_StartTime = "+ startTime+ "\r\n").c_str(), df[i]);
                      fputs(("# StationID = "+ Stations[i]+ "\r\n").c_str(), df[i]);
                      fputs(("# Frequency = "+ freqs[i]+ "\r\n").c_str(), df[i]);
                      fputs(("# SampleRate = "+ interval+ "\r\n").c_str(), df[i]);
                      //}
                   }
                   // set time base
                   secs= 0;
                   secinc= interval.ToInt();
                }
                // start adding records
                hr= secs/3600;
                min= (secs- hr*3600)/60;
                sec= secs- (hr*3600+ min*60);
                T= strtok(buf, " ,\r\n");
                for(i= 0; i< stationCnt; i++) {
                    s.sprintf("%s %02i:%02i:%02i, %s\r\n", startTime.SubString(1, 10), hr, min, sec, T);
                    fputs(s.c_str(), df[i]);
                    T= strtok(NULL, " ,\r\n");
                }
                secs+= secinc;
             }
          } // reading records
          for(i= 0; i< stationCnt; i++) fclose(df[i]);
          fclose(cbf);
       } // no cbf
   };
}
//---------------------------------------------------------------------------


bool __fastcall TForm1::IsSafeChar(int ch)
{
   bool Result;
   if     (ch >= 48 && ch <= 57) Result= true;    // 0-9
   else if(ch >= 61 && ch <= 90) Result= true;  // =?>@A-Z
   else if(ch >= 97 && ch <= 122) Result= true;  // a-z
   else if(ch == 33) Result= true; // !
   else if(ch >= 39 && ch <= 42) Result= true; // '()*
   else if(ch >= 44 && ch <= 46) Result= true; // ,-.
   else if(ch == 95) Result= true; // _
   else if(ch == 126) Result= true; // ~
   else if(ch == 58) Result= true; // :
   else if(ch == 47) Result= true; // /
   else Result= false;
   return Result;
}

// the only thing needed to be encoded are spaces
// this code is pretty hacked up
AnsiString __fastcall TForm1::EncodeURIComponent(AnsiString ASrc)
{
   AnsiString UTF8String, HexMap= "0123456789ABCDEF", Result= "", ASrcUTF8;
   int I= 1, J= 1;

   ASrcUTF8= ASrc; //ASrcUTF8 := UTF8Encode(ASrc);
   // UTF8Encode call not strictly necessary but
   // prevents implicit conversion warning

   Result.SetLength(ASrcUTF8.Length() * 3); // space to %xx encode every byte
   while(I <= ASrcUTF8.Length()) {
      if(IsSafeChar(ASrcUTF8[I])) {
         Result[J]= ASrcUTF8[I];
         J++;
      }
/*      else if(ASrcUTF8[I] == ' ') {
         Result[J]= '+';
         J++;
      } */
      else {
         Result[J]= '%';
         Result[J+1]= HexMap[(ASrcUTF8[I] >> 4) + 1];
         Result[J+2]= HexMap[(ASrcUTF8[I] & 0x0F) + 1];
         J+= 3;
      }
      I++;
   }

   Result.SetLength(J-1);
   return Result;
}



void __fastcall TForm1::Button4Click(TObject *Sender)
{
   AnsiString a, s;
   s= "http://sid.stanford.edu/database-browser/browse.jsp?display=vertical";
   s+= "&goesFlareStrength=C1.0";
   s+= "&timeRange=1440&size=1000x200";

   s+= a.sprintf("&monitor=%i$%s$%s", sidMonitor, Site, StationID);


//   s+= "&monitor=9130$MASH$HWU&monitor=9130$MASH$NAA&monitor=9130$MASH$NLK&monitor=9130$MASH$NML&monitor=9130$MASH$NPM";
   s+= a.sprintf("&date=%i-%02i-%02iT00.00.00", yr, mo, day);
   ShellExecute(Handle,"open",s.c_str(),0,0,SW_SHOW);
}
//---------------------------------------------------------------------------

