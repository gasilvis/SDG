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
