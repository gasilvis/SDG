object Form1: TForm1
  Left = 337
  Top = 127
  Width = 979
  Height = 741
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Caption = 'SID Data Grabber'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -20
  Font.Name = 'Arial'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Scaled = False
  ShowHint = True
  OnCreate = FormCreate
  PixelsPerInch = 120
  TextHeight = 23
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 971
    Height = 683
    ActivePage = graphTab
    Align = alClient
    TabOrder = 0
    object graphTab: TTabSheet
      Caption = 'Graph'
      ParentShowHint = False
      ShowHint = True
      object stationLabel: TLabel
        Left = 32
        Top = 192
        Width = 67
        Height = 23
        Caption = 'Station:'
      end
      object freqLabel: TLabel
        Left = 240
        Top = 192
        Width = 47
        Height = 23
        Caption = 'Freq:'
      end
      object Label3: TLabel
        Left = 32
        Top = 16
        Width = 82
        Height = 23
        Caption = 'Observer'
      end
      object Label4: TLabel
        Left = 240
        Top = 64
        Width = 59
        Height = 23
        Caption = 'Label4'
      end
      object Label6: TLabel
        Left = 240
        Top = 32
        Width = 107
        Height = 23
        Caption = 'Last log file:'
      end
      object lastFileLabel: TLabel
        Left = 350
        Top = 32
        Width = 6
        Height = 23
      end
      object versionLabel: TLabel
        Left = 320
        Top = 0
        Width = 48
        Height = 23
        Caption = '        '
        OnClick = versionLabelClick
      end
      object testLabel: TLabel
        Left = 520
        Top = 616
        Width = 81
        Height = 23
        Caption = 'testLabel'
        Visible = False
      end
      object Chart1: TChart
        Left = 8
        Top = 225
        Width = 945
        Height = 370
        AnimatedZoom = True
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -17
        Title.Font.Name = 'Arial'
        Title.Font.Style = [fsBold]
        Title.Text.Strings = (
          'TChart')
        OnClickSeries = Chart1ClickSeries
        BottomAxis.AxisValuesFormat = '0000'
        BottomAxis.DateTimeFormat = 'hhmm'
        BottomAxis.LabelStyle = talValue
        ClipPoints = False
        Legend.Visible = False
        RightAxis.Visible = False
        TopAxis.AxisValuesFormat = '0000'
        TopAxis.DateTimeFormat = 'hhmm'
        TopAxis.LabelStyle = talValue
        View3D = False
        View3DWalls = False
        TabOrder = 0
        object Series1: TLineSeries
          HorizAxis = aBothHorizAxis
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = 10485760
          ShowInLegend = False
          ValueFormat = '0'
          Dark3D = False
          Pointer.HorizSize = 3
          Pointer.InflateMargins = True
          Pointer.Style = psCircle
          Pointer.VertSize = 3
          Pointer.Visible = True
          XValues.DateTime = True
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series2: TArrowSeries
          Marks.ArrowLength = 0
          Marks.Frame.Visible = False
          Marks.Transparent = True
          Marks.Visible = True
          SeriesColor = clRed
          ShowInLegend = False
          Pointer.HorizSize = 12
          Pointer.InflateMargins = False
          Pointer.Pen.Width = 3
          Pointer.Style = psRectangle
          Pointer.VertSize = 13
          Pointer.Visible = True
          XValues.DateTime = True
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
          EndXValues.DateTime = True
          EndXValues.Name = 'EndX'
          EndXValues.Multiplier = 1
          EndXValues.Order = loNone
          EndYValues.DateTime = False
          EndYValues.Name = 'EndY'
          EndYValues.Multiplier = 1
          EndYValues.Order = loNone
          StartXValues.DateTime = True
          StartXValues.Name = 'X'
          StartXValues.Multiplier = 1
          StartXValues.Order = loAscending
          StartYValues.DateTime = False
          StartYValues.Name = 'Y'
          StartYValues.Multiplier = 1
          StartYValues.Order = loNone
        end
        object Series3: TArrowSeries
          Marks.ArrowLength = 0
          Marks.Frame.Visible = False
          Marks.Transparent = True
          Marks.Visible = True
          SeriesColor = clTeal
          ShowInLegend = False
          Title = 'flareInfo'
          Pointer.Brush.Color = 13160660
          Pointer.HorizSize = 1
          Pointer.InflateMargins = False
          Pointer.Pen.Width = 5
          Pointer.Style = psRectangle
          Pointer.VertSize = 1
          Pointer.Visible = True
          XValues.DateTime = True
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
          EndXValues.DateTime = True
          EndXValues.Name = 'EndX'
          EndXValues.Multiplier = 1
          EndXValues.Order = loNone
          EndYValues.DateTime = False
          EndYValues.Name = 'EndY'
          EndYValues.Multiplier = 1
          EndYValues.Order = loNone
          StartXValues.DateTime = True
          StartXValues.Name = 'X'
          StartXValues.Multiplier = 1
          StartXValues.Order = loAscending
          StartYValues.DateTime = False
          StartYValues.Name = 'Y'
          StartYValues.Multiplier = 1
          StartYValues.Order = loNone
        end
      end
      object GroupBox1: TGroupBox
        Left = 16
        Top = 96
        Width = 713
        Height = 89
        Caption = 'Event'
        TabOrder = 1
        object Label1: TLabel
          Left = 312
          Top = 20
          Width = 99
          Height = 23
          Caption = 'Importance'
        end
        object Label2: TLabel
          Left = 424
          Top = 20
          Width = 80
          Height = 23
          Hint = 
            '0 Questionable, 1 Possible, 2 Fair, 3 Reasonable, 4 Reasonably d' +
            'efinte, 5 Definte'
          Caption = 'Definition'
        end
        object startEdit: TEdit
          Left = 16
          Top = 50
          Width = 81
          Height = 31
          Hint = 'add D=after, E=before, U=uncertain when appropriate'
          TabOrder = 0
        end
        object startRB: TRadioButton
          Left = 16
          Top = 24
          Width = 113
          Height = 17
          Hint = 
            'The next click on the graph sends the time here  this is the one' +
            ' selected'
          Caption = 'Start'
          TabOrder = 1
        end
        object maxRB: TRadioButton
          Left = 120
          Top = 24
          Width = 113
          Height = 17
          Hint = 
            'The next click on the graph sends the time here  this is the one' +
            ' selected'
          Caption = 'Max'
          TabOrder = 2
        end
        object maxEdit: TEdit
          Left = 120
          Top = 50
          Width = 81
          Height = 31
          Hint = 'add D=after, E=before, U=uncertain when appropriate'
          TabOrder = 3
        end
        object endRB: TRadioButton
          Left = 224
          Top = 24
          Width = 81
          Height = 17
          Hint = 
            'The next click on the graph sends the time here  this is the one' +
            ' selected'
          Caption = 'End'
          TabOrder = 4
        end
        object endEdit: TEdit
          Left = 224
          Top = 50
          Width = 81
          Height = 31
          Hint = 'add D=after, E=before, U=uncertain when appropriate'
          TabOrder = 5
        end
        object definitionCB: TComboBox
          Left = 424
          Top = 48
          Width = 89
          Height = 31
          Hint = 
            '0 Questionable, 1 Possible, 2 Fair, 3 Reasonable, 4 Reasonably d' +
            'efinte, 5 Definte'
          ItemHeight = 23
          TabOrder = 6
          Text = '5'
          Items.Strings = (
            '0'
            '1'
            '2'
            '3'
            '4'
            '5')
        end
        object addButton: TButton
          Left = 552
          Top = 48
          Width = 145
          Height = 28
          Caption = 'add to report'
          TabOrder = 7
          OnClick = addButtonClick
        end
        object importanceEdit: TEdit
          Left = 328
          Top = 48
          Width = 73
          Height = 31
          TabOrder = 8
        end
      end
      object observerEdit: TEdit
        Left = 136
        Top = 11
        Width = 73
        Height = 31
        TabOrder = 2
        OnExit = observerEditExit
      end
      object Button1: TButton
        Left = 720
        Top = 192
        Width = 105
        Height = 28
        Caption = 'Next File'
        TabOrder = 3
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 456
        Top = 192
        Width = 97
        Height = 28
        Hint = 'Zoom by drawing a box. Unzoom my clicking here'
        Caption = 'un Zoom'
        TabOrder = 4
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 616
        Top = 192
        Width = 89
        Height = 28
        Caption = 'Prev File'
        TabOrder = 5
        OnClick = Button3Click
      end
      object reportDirSelect: TButton
        Left = 32
        Top = 64
        Width = 185
        Height = 28
        Caption = 'Set report file dir'
        TabOrder = 6
        OnClick = reportDirSelectClick
      end
      object Button5: TButton
        Left = 864
        Top = 192
        Width = 75
        Height = 28
        Caption = 'Open'
        TabOrder = 7
        OnClick = Open1Click
      end
      object Button4: TButton
        Left = 56
        Top = 608
        Width = 377
        Height = 28
        Hint = 'will include flare information'
        Caption = 'view data at Stanford website'
        TabOrder = 8
        OnClick = Button4Click
      end
      object stationEdit: TEdit
        Left = 112
        Top = 190
        Width = 81
        Height = 31
        Hint = '3 letter station code'
        TabOrder = 9
        OnExit = stationEditExit
      end
      object freqEdit: TEdit
        Left = 296
        Top = 190
        Width = 81
        Height = 31
        Hint = 'Hz'
        TabOrder = 10
        Text = '0'
        OnExit = freqEditExit
      end
    end
    object reportTab: TTabSheet
      Caption = 'Report'
      ImageIndex = 1
      object reportLabel: TLabel
        Left = 160
        Top = 8
        Width = 117
        Height = 23
        Caption = 'no report file '
      end
      object Label5: TLabel
        Left = 32
        Top = 600
        Width = 59
        Height = 23
        Caption = 'Label5'
        Visible = False
      end
      object Memo1: TMemo
        Left = 16
        Top = 40
        Width = 937
        Height = 497
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'Fixedsys'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
        OnDblClick = Memo1DblClick
      end
      object Button6: TButton
        Left = 24
        Top = 552
        Width = 89
        Height = 25
        Hint = 'If you edit the report, Save it'
        Caption = 'Save'
        TabOrder = 1
        OnClick = Button6Click
      end
      object GroupBox2: TGroupBox
        Left = 456
        Top = 560
        Width = 409
        Height = 73
        Caption = 'Report file naming'
        TabOrder = 2
        object reportByMonth: TRadioButton
          Left = 24
          Top = 32
          Width = 113
          Height = 20
          Hint = 'report file will by month, all stations combined'
          Caption = 'by month'
          TabOrder = 0
          OnClick = reportByMonthClick
        end
        object reportBymonthandstation: TRadioButton
          Left = 184
          Top = 32
          Width = 217
          Height = 20
          Caption = 'by month and station'
          Checked = True
          TabOrder = 1
          TabStop = True
          OnClick = reportByMonthClick
        end
      end
      object Button8: TButton
        Left = 192
        Top = 568
        Width = 75
        Height = 25
        Caption = 'Button8'
        TabOrder = 3
        Visible = False
        OnClick = Button8Click
      end
    end
    object bufferTab: TTabSheet
      Caption = 'Buffer'
      ImageIndex = 3
      object Label7: TLabel
        Left = 40
        Top = 32
        Width = 669
        Height = 23
        Caption = 
          'This tool will create log files from a current_buffer file saved' +
          ' from SidMonitor'
      end
      object ProcessBufferFileButton: TButton
        Left = 48
        Top = 88
        Width = 281
        Height = 25
        Caption = 'select current buffer file'
        TabOrder = 0
        OnClick = ProcessBufferFileButtonClick
      end
      object Memo3: TMemo
        Left = 48
        Top = 160
        Width = 793
        Height = 313
        ScrollBars = ssVertical
        TabOrder = 1
      end
      object Memo4: TMemo
        Left = 456
        Top = 64
        Width = 473
        Height = 81
        ScrollBars = ssVertical
        TabOrder = 2
        Visible = False
      end
      object Button7: TButton
        Left = 600
        Top = 536
        Width = 75
        Height = 25
        Caption = 'Button7'
        TabOrder = 3
        Visible = False
        OnClick = Button7Click
      end
    end
    object helpTab: TTabSheet
      Caption = 'Help'
      ImageIndex = 2
      object Memo2: TMemo
        Left = 24
        Top = 16
        Width = 921
        Height = 609
        Lines.Strings = (
          #10
          
            'The SID Data Grabber is an application to help prepare an AAVSO ' +
            'SID report file from your '
          
            'SIDmonitor log files. It offers a zoomable graphical view of the' +
            ' log data where you can click the '
          
            'graph to grab the times and then it puts it into the AAVSO forma' +
            't report file, ready for submission at '
          'the end of the month.'#10#13#10#10
          ''
          
            'First step is to set your observer id and the directory of the r' +
            'eport files.'#10#13#10#10
          ''
          
            'From there you select a batch of observation files. These files ' +
            'need to be in the SuperSID format (txt '
          
            'or csv) with header information and the timeseries data spanning' +
            ' one day. For example:'#10
          '# StationID = HWU'#10
          '# Frequency = 18300'#10
          '2015-03-01 00:00:00, 50885.6558753'#10
          '2015-03-01 00:00:05, 50885.6558753'#10
          '2015-03-01 00:00:10, 50885.6558753'#10#13#10#10
          ''
          
            'If your log files are in a different format but have the same da' +
            'ta, contact me and I'#39'll see about '
          
            'making modifications to the application for you. A141@GASilvis.n' +
            'et.'#10#13#10#10
          ''
          
            'If you see a flare event in the graph, zoom in on it by drawing ' +
            'a box around it. You can also scroll the '
          
            'graph if you hold down the Ctrl key while holding the Right Mous' +
            'e Button. Note that the graph also '
          
            'shows the sunrise/sunset times of the monitoring site as well as' +
            ' that of the transmitting station. '
          
            'Flares are going to happen in the daylight period of the station' +
            ' and site. Also displayed on the graph '
          
            'are known GEOS detected XRay events. A spike in the graph right ' +
            'after an XRay event is a good '
          
            'bet. This is similar to the data displayed at the Standford webs' +
            'ite. With the zoom you will then have '
          
            'the resolution to accurately pick the time to the minute by clic' +
            'king on the graph. After clicking on '
          
            'start, max and end review the importance computed and set the de' +
            'finiteness field. You can add D, E '
          
            'and U modifiers to the edit boxes as appropriate. Now you can cl' +
            'ick the "add to report" button. '#10#13#10#10
          ''
          
            'When you click on the graph the time will be put in the edit box' +
            ' with the radio check box lit. These will '
          
            'light up in turn. If you need to go back and change an entry, ju' +
            'st reclick the radio icon so that your '
          'graph click will go to the right place.'#10#13#10#10
          ''
          
            'Report files are named <observer ID><year><mo>.txt. The appropri' +
            'ate report file is opened based '
          
            'on the log file graph you are using. You can edit the file direc' +
            'tly from the Report tab (eg, to remove a '
          
            'record) and then you need to save the updated report with your e' +
            'dits.'#10#13#10#10
          ''
          
            'The Next/Prev File buttons take you through the list of files yo' +
            'u selected with the File/Open process.'#10#13#10#10
          ''
          
            'The main screen, the Graph tab, will show you the last log file ' +
            'that you processed. Helpful if you are '
          
            'scanning the files once a week as it shows you where you left of' +
            'f.'#10#13#10#10
          ''
          
            'If you have a graph open and your data is also on the Stanford S' +
            'ID Data Access website, you can '
          
            'click on the button below the graph and view that data in a brow' +
            'ser. This is handy as that display will '
          'include the known flares on the graph.'#10#13#10#10
          #13#10#10
          ''
          
            'Instructions for extracting the event times and report format is' +
            ' taken from:'#10
          
            'http://www.aavso.org/reducing-data-gathered-vlf-monitoring-syste' +
            'ms'#10
          'with minor modifications.'#10#13#10#10
          ''
          'Reducing Data Gathered by VLF Monitoring Systems'#10
          
            '(Extracted from SID Technical Bulletin Vol. 3, Number 4, Oct. 19' +
            '92)'#10#13#10#10
          ''
          
            'The reduction process is quite simple, and consists of the steps' +
            ' which follow. First, the universal time '
          
            'for each of three event-phases must be measured for each SID. '#10#13 +
            #10#10
          ''
          
            'Event Start: The moment when an event begins. Be aware that the ' +
            'amplitude of different events '
          
            'varies considerably, and some may appear in inverted form. If it' +
            ' is obvious that an event began '
          
            'before the first definable start time, an '#39'E'#39' (before) is append' +
            'ed to the recorded time. Look for the '
          
            'beginning of the sharp rise, same as for the event max (see belo' +
            'w).'#10#13#10#10
          ''
          
            'Event End: Of the three times, the end time is the most difficul' +
            't to determine. It is defined as the '
          
            'moment when the trace returns to the diurnal trend line, or is i' +
            'nterrupted by the onset of a new event. '
          
            'In the latter situation, the letter '#39'D'#39' (after) is appended to t' +
            'hat time, which in turn becomes the start '
          'time for the following event.'#10#13#10#10
          ''
          
            'Event Maximum: The moment when the ascending (descending in the ' +
            'case of inverted events) branch '
          
            'slows its sharp rise. Note that this generally does not coincide' +
            ' with the event'#39's peak amplitude.'#10#13#10#10
          ''
          
            'If the trace goes off-scale as maximum is approached, or is inte' +
            'rfered with in some other manner '
          
            'such as the onset of sunset, device failure, etc., we append a '#39 +
            'U'#39' (uncertain) to the last identifiable '
          
            'time. For example, if the SID maximum occurs somewhere off-scale' +
            ' and the last determinable time is '
          
            'fourteen hours, ten minutes (1410), the time is recorded as 141O' +
            'U.'#10#13#10#10
          ''
          'Duration'#9#9'Importance'#10
          '< 19 minutes'#9'1-'#10
          '19-25'#9#9'1'#10
          '26-32'#9#9'1+'#10
          '33-45'#9#9'2'#10
          '46-85'#9#9'2+'#10
          '86-125'#9#9'3'#10
          '>125'#9#9'3+'#10
          
            'After each of these times have been recorded, the event'#39's '#39'Impor' +
            'tance'#39' and '#39'Definiteness'#39' ratings can '
          
            'be determined. Importance generally refers to the length of an e' +
            'vent, found by subtracting the start '
          
            'time from the end time. This is computed automatically for you. ' +
            'The table above associates the '
          'Importance rating with event duration.'#10#13#10#10
          ''
          
            'With respect to the observer'#39's typical daily trace, a class 1 SI' +
            'D is an event with small intensity '
          
            'change and a relatively short duration. Class 2 is a moderate in' +
            'tensity event with a fairly long '
          
            'duration, and a class 3 describes a SID with a '#39'great'#39' change in' +
            ' intensity and long duration.'#10#13#10#10
          ''
          'Confidence'#9#9'Definition'#10
          'Questionable'#9#9'0'#10
          'Possible'#9#9#9'1'#10
          'Fair'#9#9#9'2'#10
          'Reasonable'#9#9'3'#10
          'Reasonably Definite'#9#9'4'#10
          'Definite'#9#9#9'5'#10
          
            'Definition is a subjective estimate of an observer'#39's confidence ' +
            'in the event. Normally, the events '
          
            'which are included in our reports have Definitions equal to 3 or' +
            ' greater. Use the right-hand scale as a '
          
            'guide to Definition. Careful study and experience teaches observ' +
            'ers how to recognize false SID '
          
            'events caused by man-made interference. Beginners should not hes' +
            'itate to assign high Definition '
          
            'values to those events which are not correlated with known noise' +
            ' sources. Other observers'#39' results '
          
            'will be compared to eliminate suspect events before a final repo' +
            'rt is submitted to the NGDC.'#10#13#10#10
          #13#10#10
          ''
          
            'Sometimes you need to shut down the sidmonitor. Before you do yo' +
            'u should save the buffered data '
          
            'of the last day. What can you do with that data? This applicatio' +
            'n has a tool for recovering this data '
          
            'into log files (with just part of a days data) that can then be ' +
            'surveyed with the grabber tool. See the '
          'Buffer tab. '#10#13#10#10
          ''
          
            'There is a review feature where from the Report screen you can d' +
            'ouble click on a report line and the '
          
            'program will show you the log file that derived that report line' +
            ' from. That'#39's assuming the log files are '
          'in the currently specified log directory.'#10#13#10#10
          ''
          
            'Any problems with this program or suggestions for improvement, p' +
            'lease email me at '
          'A141@GASilvis.net .'#10#13#10#10
          ''
          'George'#10)
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'text |*.txt|csv|*.csv|all|*.*'
    Left = 88
    Top = 312
  end
  object MainMenu1: TMainMenu
    Left = 16
    Top = 40
    object File1: TMenuItem
      Caption = 'File'
      object Open1: TMenuItem
        Caption = 'Open'
        Hint = 'Select a SID daily output file'
        OnClick = Open1Click
      end
      object SetLogtype1: TMenuItem
        Caption = 'Set Log type  '
        object LogTypeSuperSID: TMenuItem
          AutoLineReduction = maAutomatic
          Caption = 'Super SID   '
          Checked = True
          GroupIndex = 12
          Hint = 'eg. 2015-03-01 00:00:10, 50885.6558753'
          RadioItem = True
          OnClick = LogTypeSuperSIDClick
        end
        object LogTypeLASPextract: TMenuItem
          AutoLineReduction = maAutomatic
          Caption = 'LASP extract'
          GroupIndex = 12
          Hint = 'eg. 2015-04-03:0000,7.67e-07'
          RadioItem = True
          OnClick = LogTypeSuperSIDClick
        end
      end
      object Quit1: TMenuItem
        Caption = 'Quit'
        OnClick = Quit1Click
      end
    end
  end
  object ElasticForm1: TElasticForm
    DesignScreenWidth = 1448
    DesignScreenHeight = 876
    DesignPixelsPerInch = 120
    DesignFormWidth = 979
    DesignFormHeight = 741
    DesignFormClientWidth = 971
    DesignFormClientHeight = 683
    DesignFormLeft = 337
    DesignFormTop = 127
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Arial'
    Font.Style = []
    Version = 700
    Left = 96
    Top = 384
  end
  object HttpCli1: THttpCli
    LocalAddr = '0.0.0.0'
    ProxyPort = '80'
    Agent = 'Mozilla/4.0'
    Accept = 'image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, */*'
    NoCache = False
    ContentTypePost = 'application/x-www-form-urlencoded'
    MultiThreaded = False
    RequestVer = '1.0'
    FollowRelocation = True
    LocationChangeMaxCount = 5
    BandwidthLimit = 10000
    BandwidthSampling = 1000
    Options = []
    OnDocBegin = HttpCli1DocBegin
    OnDocEnd = HttpCli1DocEnd
    SocksAuthentication = socksNoAuthentication
    Left = 196
    Top = 531
  end
  object FtpClient1: TFtpClient
    Timeout = 15
    MultiThreaded = False
    Port = 'ftp'
    DataPortRangeStart = 0
    DataPortRangeEnd = 0
    LocalAddr = '0.0.0.0'
    UserName = 'anonymous'
    PassWord = 'George@GASilvis.net'
    DisplayFileFlag = False
    Binary = False
    ShareMode = ftpShareExclusive
    Options = [ftpAcceptLF, ftpWaitUsingSleep]
    ConnectionType = ftpDirect
    Left = 268
    Top = 547
  end
end
