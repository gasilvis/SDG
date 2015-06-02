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
//#pragma link "IcsLogger"
//#pragma link "SHDocVw_OCX"
#pragma link "FtpCli"
#pragma link "WSocket"
#pragma resource "*.dfm"
TForm1 *Form1;

#define Version 1.08
// when you change this, update gasilvis.com/SID/SIDlog.php which should return this value
/*
  1.08
  - add feature: double click on report and open related log file
  - add FLA flare events
  - increase FLAREMAX; sometimes there are more!
  - show events in the middle of the graph
  - fix fault on bailing out of file open; Canceling the log file open clears the file list, so test for it
    late addition:
      - don't unzoom after add event
      - scroll in all directions
  1.07
  - tidy up httpget
  - include quality in Stanford web call
  - capture siteLat/Long
  - show sunrise/sunset times of site and station
  - show known XRay events on the graph
*/

void computeSunRiseandSet(double latitude, double longitude, short yday, short* sunrise, short* sunset);
int DayOfYear(int yr, int mo, int day);
typedef struct {
   char*  ID;
   double Lat;
   double Long;
   char*  Desc;
} stationDetail;
//from http://sidstation.loudet.org/stations-list-en.xhtml   5/5/2015
stationDetail Stations[]= {
    {"VTX",  +8.387015,  +77.752762, "16300, 17000, 18200, 19200	South Vijayanarayanam, India"}
   ,{"JXN", +66.974353,  +13.873617, "16400	Novik, Norway"}
   ,{"SAQ", +57.113171,  +12.397277, "17200	Grimeton, Sweden"}
   ,{"GBZ", +54.911643,   -3.278456, "19580	Anthorn, UK"}
   ,{"NWC",	-21.816328, +114.165586, "19800	Harold E. Holt, North West Cape, Exmouth, Australia"}
   ,{"ICV", +40.923127,   +9.731011, "20270	Isola di Tavolara, Italy"}
   ,{"FTA", +48.544632,   +2.579429, "16800 20900	Sainte-Assise, France"}
   ,{"NPM", +21.420166, -158.151140, "21400	Pearl Harbour, Lualuahei, HI"}
   ,{"HWU", +46.713129,   +1.245248, "15100 18300 21750 22600	Rosnay, France"}
   ,{"GQD", +54.731799,   -2.883033, "22100	Skelton, UK"}
   ,{"NDT", +32.082084, +130.827960, "22200	Ebino, Japan"}
   ,{"JJI",  32.04, 130.81, "22100, Ebino, Japan"} // defunct?
   ,{"DHO", +53.078900,   +7.61500038, "23400	Rhauderfehn, Germany  DHO38"}
   ,{"NAA", +44.644936,  -67.281639, "24000	Cutler, ME"}
   ,{"NLK", +48.203487, -121.916827, "24800	Oso Wash, Jim Creek, WA"}
//   ,{"unid25", +34.679068, +126.445383, "25000	Mokpo, South Korea"}
   ,{"NML", +46.365990,  -98.335638, "25200	La Moure, ND"}
   ,{"TBB", +37.412725,  +27.323342, "26700	Bafa, Turkey"}
   ,{"NRK", +63.850365,  -22.466773, "37500	Grindavik, Iceland"}
   ,{"TFK", +63.850365,  -22.466773, "37500	Grindavik, Iceland"}
   ,{"JJY", +37.372598, +140.848906, "40000	Mount Ootakadoya, Fukushima prefecture, Japan, JJY-40"}
   ,{"SRC", +57.113171,  +12.397277, "40400	Varberg, Sweden"}
   ,{"NAU", +18.398762,  -67.177599, "40800	Aguada, Puerto Rico"}
   ,{"NSY",	+37.125660,  +14.436416, "45900	Niscemi, Italy"}
   ,{"SXA", +38.145170,  +24.019709, "49000	Marathon, Greece"}
   ,{"GYW", +57.617464,   -1.887595, "51950	Crimond, UK,  GYW1"}
   ,{"MSF", +54.911195,   -3.279302, "60000	Anthorn, UK"}
   ,{"WWV", +40.677722, -105.047153, "60000	Fort Collins, Colorado,  WWVB"}
//   ,{"JJY-60", +33.465433, +130.175415, "60000	Mount Hagane, Fukuoka prefecture, Japan"}
   ,{"FUG", +43.386798,   +2.097388, "62600	La Régine, France"}
   ,{"FUE", +48.637672,   -4.350725, "65800	Kerlouan, France"}
   ,{"BPC", +34.456519, +115.836937, "68500	Shangqiu, Henan Province, China"}
   ,{"CFH", +44.967276,  -63.982160, "73600	Halifax, Canada"}
   ,{"DCF", +50.015411,   +9.008307, "77500	Mainflingen, Germany,  DCF77"}
   ,{"GYN", +53.830071,   -2.834266, "81000	Inskip, UK,  GYN2"}
};

typedef struct {
   double begin;
   double end;
   char  desc[15];
} flareDetail;
#define FLAREMAX 200
flareDetail flares[FLAREMAX];
short flareCount= 0;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

AnsiString dataDir, reportDir, reportFile, reportPath, lastFile; // Path is the combination of Dir and File
#define LogTypesNum  10
TMenuItem *LogTypes[LogTypesNum]; //= { LogTypeSuperSID, LogTypeLASPextract etc   set at create time};

AnsiString Site, StationID= "   ", Frequency= "0";

AnsiString INIfilename= "";
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   TStream *DataIn;
   char cp[10000];
   float cver;
   AnsiString s;
   int lt, i;
   //TScreen->MenuFont=       ??  trying to set menufont. can't do
   // set window header
   Form1->Caption= "SID Data Grabber Application, "+ FormatFloat("version 0.00", Version);

   // get current version information
   if(httpGet("http://www.gasilvis.com/SID/SIDlog.php", cp, sizeof(cp))) {
      sscanf(cp, "%f", &cver);
      if(cver > Version+ 0.001) {
         versionLabel->Tag= 1;
         versionLabel->Font->Color= clBlue;
         versionLabel->Caption= s.sprintf("Click here to download version %.2f", cver);
      } else {
         versionLabel->Caption= s.sprintf("%.2f is the latest version of SDG", cver);
      }
   }

   // build LogType array
   LogTypes[0]= LogTypeSuperSID;
   LogTypes[1]= LogTypeLASPextract;

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
   reportByMonth->Checked= ini->ReadBool("Setup", "reportByMonth", false);
   lastFile= ini->ReadString("Setup", "lastFile", "");
   lastFileLabel->Caption= lastFile;
   openReportFile(Sender, false);
   lt= ini->ReadInteger("Setup", "LogType", 0); // default to SuperSid
   LogTypes[lt]->Checked= true;
   freqEdit->Text= Frequency= ini->ReadString("Setup", "lastFrequency", 0);
   stationEdit->Text= StationID= ini->ReadString("Setup", "lastStation", "   ");
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
         filesIndex= (dataFiles->Count)? 0: -1;
         displayNextFile(Sender);
         // Save selection info
         TIniFile *ini= new TIniFile(INIfilename);
         ini->WriteString("Setup", "dataDir", dataDir); // set in displayNextFile
         ini->WriteInteger("Setup", "FilterIndex", OpenDialog1->FilterIndex);
         delete ini;
        // get observer? No.  ??
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Quit1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
int SampleRate= 0, sidMonitor= 0;
int startMin, endMin, maxMin, yr, mo, day;
double siteLat, siteLong;

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
    short siteSR, siteSS, stationSR, stationSS, stationIndex;

    Chart1->Series[0]->Clear();
    Chart1->Series[1]->Clear();
    Chart1->Series[2]->Clear();
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
/* eg
# Site = MASH
# Longitude = -70.63324
# Latitude = 41.71686
#
# UTC_Offset = -4
# TimeZone = Eastern Standard time (EST)
#
# UTC_StartTime = 2015-03-08 00:00:00
# StationID = NLK
# Frequency = 24800
# MonitorID = 9130
# SampleRate =  5
*/
           sb= AnsiString(buf).TrimRight(); // cut the \n
            if(sb.SubString(2, 13)== " StationID = ") {
              StationID= sb.SubString(15, 20).TrimRight().TrimLeft();
              stationEdit->Text= StationID;
              stationEditExit(Sender);
           } else if(sb.SubString(2, 13)== " Frequency = ") {
              Frequency= sb.SubString(15, 20).TrimRight().TrimLeft();
              //Frequency= sb.sprintf("%g", y); // g fmt loses the trailing 0's
              freqEdit->Text= Frequency;
              freqEditExit(Sender);
           } else if(sb.SubString(2, 14)== " SampleRate = ") {
              SampleRate= sb.SubString(16, 20).ToInt();
           } else if(sb.SubString(2, 13)== " MonitorID = ") {
              sidMonitor= sb.SubString(15, 20).ToInt();
           } else if(sb.SubString(2, 8)== " Site = ") {
              Site= sb.SubString(10, 20).TrimRight().TrimLeft();
           } else if(sb.SubString(2, 13)== " Longitude = ") {
              siteLong= sb.SubString(15, 20).ToDouble();
           } else if(sb.SubString(2, 12)== " Latitude = ") {
              siteLat= sb.SubString(14, 20).ToDouble();
           }
        } else {
           if(LogTypeSuperSID->Checked) {
              //2015-03-01 00:00:10, 50885.6558753    eg
              x=sscanf(buf, "%04d-%02d-%02d %02d:%02d:%02d, %f\n", &yr, &mo, &day, &hr, &min, &sec, &dp); // %d avoids %i confusion over octal eg 08
              if(7==x) {
                 time= (hr + (min+ sec/60.0)/60.0)/24.0; // put in days
                 x=Chart1->Series[0]->AddXY(time, dp, "", clTeeColor);
              } else {
                 ShowMessage("bad data line: "+ AnsiString(buf));
                 break;
              }
          } else if(LogTypeLASPextract->Checked) {
              //2015-04-03:0000,7.67e-07   eg
              x=sscanf(buf, "%04d-%02d-%02d:%04d,%f\n", &yr, &mo, &day, &min, &dp); // %d avoids %i confusion over octal eg 08
              if(5==x) {
                 time= min/1440.0; // put in days
                 x=Chart1->Series[0]->AddXY(time, dp, "", clTeeColor);
              } else {
                 ShowMessage("bad data line: "+ AnsiString(buf));
                 break;
              }
          }
       }
    } // end while
    // get flare data
    flareCount= getFlareData(yr, mo, day);

    // show station and monitor sunrise/sunset
    computeSunRiseandSet(siteLat, siteLong, DayOfYear(yr, mo, day), &siteSR, &siteSS);
    //testLabel->Caption= sb.sprintf("sunrise/set %04d  %04d", siteSunrise, siteSunset);
    int maxY= Chart1->Series[0]->MaxYValue();
    dynamic_cast<TArrowSeries*>(Chart1->Series[1])->AddArrow(siteSR/1440.0, 0, siteSR/1440.0, maxY, "site", clTeeColor);
    dynamic_cast<TArrowSeries*>(Chart1->Series[1])->AddArrow(siteSS/1440.0, maxY, siteSS/1440.0, 0, "site", clTeeColor);
    for(int i= 0; i<sizeof(Stations)/sizeof(stationDetail); i++)
       if(0==strcmp(Stations[i].ID, StationID.c_str())) {stationIndex= i; break;}
    computeSunRiseandSet(Stations[stationIndex].Lat, Stations[stationIndex].Long, DayOfYear(yr, mo, day), &stationSR, &stationSS);
    dynamic_cast<TArrowSeries*>(Chart1->Series[1])->AddArrow(stationSR/1440.0, 0, stationSR/1440.0, maxY, Stations[stationIndex].ID, clTeeColor);
    dynamic_cast<TArrowSeries*>(Chart1->Series[1])->AddArrow(stationSS/1440.0, maxY, stationSS/1440.0, 0, Stations[stationIndex].ID, clTeeColor);

    // get flare data
//    flareCount= getFlareData(yr, mo, day);
    for(int ii= 0; ii< flareCount; ii++) {
       dynamic_cast<TArrowSeries*>(Chart1->Series[2])->AddArrow(flares[ii].begin, 0.5*maxY, flares[ii].end, 0.5*maxY, flares[ii].desc, clTeeColor);
    }



    Chart1->UndoZoom();
    fclose(fp);
    //TBD is the file complete? clear dataFile if not
    if(StationID=="" || Frequency=="") {
       dataFile= "";
       ShowMessage("Data file does not include station or frequency");
    } else {
       if(reportByMonth->Checked) {
          reportFile= observerEdit->Text+ sb.sprintf("_%04d%02d", yr, mo)+ ".DAT";
       } else {
          reportFile= observerEdit->Text+ sb.sprintf("_%s_%04d%02d", StationID, yr, mo)+ ".DAT";
       }
       openReportFile(Sender, true);
    }
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
         //Chart1->Series[0]->ValueColor[ValueIndex]= clRed; not visible enough
         //Chart1->Series[0]->Marks[ValueIndex].  = "start";  needs investigation
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
   if(dataFiles->Count==0)
      filesIndex= -1;
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
   if(dataFiles->Count==0)
      filesIndex= -1;
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
//         Chart1->UndoZoom();
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
      // log the process
      s= "http://www.gasilvis.com/SID/SIDlog.php?logentry=";
      s+= observerEdit->Text;
      s+= ", "+ FormatFloat("0.00", Version);
      s+= ", "+ msg;
      httpGet(s, NULL, 0);
}


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
                else if(0==strncmp(buf, "# Longitude = ", 14)) Long= AnsiString(&buf[14]).TrimRight();
                else if(0==strncmp(buf, "# Latitude = ", 13)) Lat= AnsiString(&buf[13]).TrimRight();
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
                      fputs(("# Longitude = "+ Long+ "\r\n").c_str(), df[i]);
                      fputs(("# Latitude = "+ Lat+ "\r\n").c_str(), df[i]);
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




void __fastcall TForm1::Button4Click(TObject *Sender)
{
   AnsiString a, s;
   s= "http://sid.stanford.edu/database-browser/browse.jsp?display=vertical";
   s+= "&goesFlareStrength=C1.0&quality=true";
   s+= "&timeRange=1440&size=1000x200";
   s+= a.sprintf("&monitor=%i$%s$%s", sidMonitor, Site, StationID);
//   s+= "&monitor=9130$MASH$HWU&monitor=9130$MASH$NAA&monitor=9130$MASH$NLK&monitor=9130$MASH$NML&monitor=9130$MASH$NPM";
   s+= a.sprintf("&date=%i-%02i-%02iT00.00.00", yr, mo, day);
   ShellExecute(Handle,"open",s.c_str(),0,0,SW_SHOW);
}
//---------------------------------------------------------------------------

// test function
void __fastcall TForm1::Button7Click(TObject *Sender)
{
    // adfa
}
//---------------------------------------------------------------------------

void __fastcall TForm1::versionLabelClick(TObject *Sender)
{
    if(versionLabel->Tag) {
       ShellExecute(Handle,"open", "https://github.com/gasilvis/SDG/raw/master/SidDataGrabber.exe",0,0,SW_SHOW);
//       ShellExecute(Handle,"open", "http://www.gasilvis.com/SID/SidDataGrabber.exe",0,0,SW_SHOW);
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::reportByMonthClick(TObject *Sender)
{
      TIniFile *ini= new TIniFile(INIfilename);
      ini->WriteBool("Setup", "reportByMonth", reportByMonth->Checked);
      delete ini;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::LogTypeSuperSIDClick(TObject *Sender)
{
   // click a log file option
   TMenuItem *p;
   if((p=dynamic_cast<TMenuItem*>(Sender))==NULL)
      return;
   p->Checked= true;
   // update ini
   for(int i= 0; i< LogTypesNum; i++) {
      if(p==LogTypes[i]) {
         TIniFile *ini= new TIniFile(INIfilename);
         ini->WriteInteger("Setup", "LogType", i);
         delete ini;
         break;
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::stationEditExit(TObject *Sender)
{
   // set StationID and INI
   StationID= (stationEdit->Text.TrimLeft().TrimRight()+ "   ").SubString(1, 3);
   stationEdit->Text= StationID;
   TIniFile *ini= new TIniFile(INIfilename);
   ini->WriteString("Setup", "lastStation", StationID);
   delete ini;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::freqEditExit(TObject *Sender)
{
   int freq= 0;
   // set Frequency and INI
   Frequency= freqEdit->Text.TrimLeft().TrimRight();
   try { freq= Frequency.ToInt();}
   catch (...) { Frequency= "0"; }
   freqEdit->Text= freq;
   TIniFile *ini= new TIniFile(INIfilename);
   ini->WriteString("Setup", "lastFrequency", Frequency);
   delete ini;
}
//---------------------------------------------------------------------------

// http get
bool __fastcall TForm1::httpGet(AnsiString URL, char* buffer, int bufsize)
{
   TStream *DataIn;
   // simple encoding: replace ' ' with '+'
   while(URL.Pos(" ")) URL[URL.Pos(" ")]= '+';
   HttpCli1->URL        = URL;
   HttpCli1->RcvdStream = NULL;
   char altbuffer[100];
   char* buf;
   if(buffer==NULL) { // return not expected
      buf= altbuffer;
      bufsize= sizeof(buffer);
   } else { buf= buffer; }
   try {
      HttpCli1->Get();
      DataIn = new TFileStream(Form1->HttpCli1->DocName, fmOpenRead);
      DataIn->ReadBuffer(buf, min(bufsize, DataIn->Size));
      delete DataIn;
      remove(HttpCli1->DocName.c_str());
      return true;
   } __except (TRUE) {
      Form1->Memo4->Lines->Add("GET Failed !");
      Form1->Memo4->Lines->Add("StatusCode   = " + IntToStr(Form1->HttpCli1->StatusCode));
      Form1->Memo4->Lines->Add("ReasonPhrase = " + Form1->HttpCli1->ReasonPhrase);
      return false;
   }
}
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

// Sunrise/Sunset comps
//   derived from solar.py from Rodney which comes from solareqns.pdf
//	Based upon "Low Accuracy Equations" at
//	http://www.esrl.noaa.gov/gmd/grad/solcalc/sollinks.html


#define pi2 6.283185307

void computeSunRiseandSet(double latitude, double longitude, short yday, short* sunrise, short* sunset)
{
   // lat and long in degrees, return sunrise and sunset in minutes
   //	Based upon "Low Accuracy Equations" at
	//http://www.esrl.noaa.gov/gmd/grad/solcalc/sollinks.html
   double fy, fy2, fy3;
	// Fractional year in radians
	fy = pi2 *(yday - 1) / 365.0;
	fy2 = 2 * fy;
	fy3 = 3 * fy;
   // Equation of time in minutes
	double eqtime = 229.18*(0.000075+0.001868*cos(fy)-0.032077*sin(fy)-0.014615*cos(fy2)-0.040849*sin(fy2));
	// Solar declination angle in radians
	double decl = 0.006918-0.399912*cos(fy)+0.070257*sin(fy)-0.006758*cos(fy2)+0.000907*sin(fy2)-0.002697*cos(fy3)+0.00148*sin(fy3);

	longitude = -longitude; // switch to West positive
	double rlat = latitude* pi2/ 360.0;
	//double rlong = longitude* pi2/ 360.0;
	//double sin_lat = sin(rlat);
	double cos_lat = cos(rlat);
	//double sin_decl = sin(decl);
	double cos_decl = cos(decl);

	// Hour angle with zenith 90.833 deg
	double ha1 = cos(90.833* pi2/ 360.0) / (cos_lat*cos_decl);
	double ha2 = tan(rlat)*tan(decl);
	double ha = acos(ha1 - ha2)* 360.0/pi2; // ha in degrees

	// Sunrise,, sunset in minutes
	*sunrise = 720 + 4*(longitude - ha) - eqtime;
	if(*sunrise > 1440) *sunrise -= 1440;
	else if(*sunrise < 0) *sunrise += 1440;
	*sunset = 720 + 4*(longitude + ha) - eqtime;
	if(*sunset > 1440) *sunset -= 1440;
	else if(*sunset < 0) *sunset += 1440;
}

int DayOfYear(int yr, int mo, int day)
{
   int leap= 0, moday[]= {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
   if((mo > 2) && ((yr%400 == 0) || ((yr%4==0) && (yr%100)) )) leap= 1;
   return leap+ moday[mo]+ day;
}

// get flare data
AnsiString lastFlare;
short __fastcall TForm1::getFlareData(int yr, int mo, int day)
{
      AnsiString s;
      FILE* fp;
      char buf[256];
      int x;
//eg    ftp://ftp.swpc.noaa.gov/pub/warehouse/2015/2015_events/20150301events.txt
      FtpClient1->HostName= "ftp.swpc.noaa.gov";
      FtpClient1->HostDirName= s.sprintf("pub/warehouse/%04d/%04d_events", yr, yr);
      FtpClient1->HostFileName= s.sprintf("%04d%02d%02devents.txt", yr, mo, day);
      if(s==lastFlare) return flareCount; // did it already
      FtpClient1->LocalFileName= "flare.txt";
      if(FtpClient1->Receive()) {
         fp= fopen("flare.txt", "r");
         flareCount= 0;
         while(fgets(buf, sizeof(buf), fp) && flareCount< FLAREMAX) {
            if(buf[43]=='X' || buf[43]=='F') { // XRA  xray or FLA flare event
               flares[flareCount].begin= ((buf[11]-48)* 600 + (buf[12]-48)*60 + (buf[13]-48)*10 + (buf[14]-48))/ 1440.0;
               flares[flareCount].end= ((buf[18]-48)* 600 + (buf[19]-48)*60 + (buf[20]-48)*10 + (buf[21]-48))/ 1440.0;
               x= 57;
               while(buf[++x]!= ' ');
               buf[x]= 0;
               strcpy(flares[flareCount].desc, &buf[58]);
               flareCount++;
            }
         }
         lastFlare= s;
         fclose(fp);
//         remove("flare.txt");
      }
      return flareCount;
}
/*
:Product: 20150301events.txt
:Created: 2015 Mar 04 0357 UT
:Date: 2015 03 01
# Prepared by the U.S. Dept. of Commerce, NOAA, Space Weather Prediction Center
# Please send comments and suggestions to SWPC.Webmaster@noaa.gov
#
# Missing data: ////
# Updated every 5 minutes.
#                            Edited Events for 2015 Mar 01
#
#Event    Begin    Max       End  Obs  Q  Type  Loc/Frq   Particulars       Reg#
#-------------------------------------------------------------------------------

4080       0158   0210      0232  G15  5   XRA  1-8A      C1.0    1.9E-03   2290
4080       0158   0159      0211  LEA  3   FLA  N19W66    SF                2290

4090       0449   0449      0451  LEA  3   FLA  N19W68    SF                2290

4100       0453   0453      0503  LEA  3   FLA  N19W68    SF                2290

4110       0504   0513      0521  G15  5   XRA  1-8A      C3.7    2.6E-03   2290
4110       0505   0508      0526  LEA  3   FLA  N20W66    SF      ERU       2290
4110       0508   ////      0509  LEA  C   RSP  027-047   III/1             2290

4120      B0605   ////     B0655  LEA  3   EPL  ////      0.24              2289

4130       0724   0725      0730  LEA  3   FLA  N19W71    SF                2290

4140       0855   0956      1021  G15  5   XRA  1-8A      B7.4    1.7E-03   2290

4150      B0957  U0959     A1001  SVI  3   FLA  N18W72    SF                2290

4160       1255   1257      1302  SVI  3   FLA  N18W74    SF                2290

4170       1314   1314      1321  SVI  3   FLA  N05E09    SF      ERU       2293

4180       1533   1613      1631  G15  5   XRA  1-8A      C6.8    1.3E-02   2290
4180 +     1552   1554      1609  HOL  3   FLA  N20W74    SF      ERU       2290

4190       1711   1713      1716  HOL  2   FLA  N20W74    SF      DSD       2290
*/


void __fastcall TForm1::Memo1DblClick(TObject *Sender)
{
   // dbl click on memo and display the relevant log file

   AnsiString s, fn, line, yr, mo, day, station;
   int x, i;

   if(Memo1->CaretPos.x > 70 || Memo1->CaretPos.x < 0) return;
   x= Memo1->CaretPos.y;
   line= Memo1->Lines->Strings[x];
   //Label5->Caption= line;

   // get a valid line?
   //eg "40   150301  1559 1633 1604                 2     5WU18              A141"
   // get yr, mo , day, station
   if(line.Length() > 60) {
     x= line.SubString(6 ,2).ToInt();
     x+= (x<58)? 2000: 1900;
     yr= s.sprintf("%i", x);
     mo= "-"+ line.SubString(8, 2);
     day= "-"+ line.SubString(10,2);
     station= line.SubString(52, 2);
     //Label5->Caption= yr + mo + day + station;
   } else {
      ShowMessage("no report line captured");
      return;
   }

   // get files in current log directory
   //get dir from dataDir
   struct ffblk ffblk;
   dataFiles->Clear();
   i= findfirst((dataDir+ "\\*.*").c_str(), &ffblk, 0);
   while (!i) {
      //Memo1->Lines->Add(s.sprintf("  %s\n", ffblk.ff_name));
      fn= AnsiString(ffblk.ff_name);
      if(fn.Pos(yr) && fn.Pos(mo) && fn.Pos(day) && fn.Pos(station) && (fn.Pos(mo)<fn.Pos(day)) ) {
         dataFiles->Add(dataDir+ fn);
         //Memo1->Lines->Add(fn);
      }
      i= findnext(&ffblk);
   }
   if(dataFiles->Count) {
      filesIndex= 0;
      if(dataFiles->Count > 1)
         ShowMessage("more than one possible source log file");
      displayNextFile(Sender);
      startEdit->Text= line.SubString(14, 5);
      maxEdit->Text= line.SubString(19, 5);
      endEdit->Text= line.SubString(24, 5);
      PageControl1->ActivePage= graphTab;
   } else
      ShowMessage("Could not find log file");

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button8Click(TObject *Sender)
{
   Memo1DblClick(Sender);
}
//---------------------------------------------------------------------------

