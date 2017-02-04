object FPassTest: TFPassTest
  Left = 0
  Top = 0
  Align = alTop
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1058#1077#1089#1090#1080
  ClientHeight = 473
  ClientWidth = 618
  Color = clSilver
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clGreen
  Font.Height = -16
  Font.Name = 'Arial Narrow'
  Font.Style = [fsBold]
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 20
  object LAsk: TLabel
    Left = 10
    Top = 8
    Width = 596
    Height = 17
    AutoSize = False
    Caption = 'LAsk'
    WordWrap = True
  end
  object Image1: TImage
    Left = 8
    Top = 88
    Width = 360
    Height = 305
  end
  object LQuest: TLabel
    Left = 166
    Top = 409
    Width = 44
    Height = 20
    Caption = 'LQuest'
    Visible = False
  end
  object LQuestMax: TLabel
    Left = 423
    Top = 409
    Width = 68
    Height = 20
    Caption = 'LQuestMax'
    Visible = False
  end
  object BOk: TButton
    Tag = -1
    Left = 8
    Top = 409
    Width = 97
    Height = 20
    Caption = 'Ok'
    TabOrder = 0
    OnClick = BOkClick
  end
  object BEnd: TButton
    Left = 516
    Top = 409
    Width = 90
    Height = 20
    Caption = #1047#1072#1074#1077#1088#1096#1080#1090#1080
    TabOrder = 1
    Visible = False
    OnClick = BEndClick
  end
  object ProgressBar1: TProgressBar
    Left = 200
    Top = 409
    Width = 217
    Height = 20
    Enabled = False
    Max = 0
    ParentShowHint = False
    BarColor = clMaroon
    BackgroundColor = clMaroon
    ShowHint = False
    TabOrder = 2
    Visible = False
  end
  object Panel1: TPanel
    Left = 8
    Top = 435
    Width = 305
    Height = 30
    Alignment = taLeftJustify
    BevelOuter = bvLowered
    Caption = 'Panel1'
    TabOrder = 3
  end
  object Panel2: TPanel
    Left = 319
    Top = 435
    Width = 122
    Height = 30
    Caption = ' '
    TabOrder = 4
    object LDoubDot: TLabel
      Left = 83
      Top = 8
      Width = 4
      Height = 20
      Caption = ':'
      Visible = False
    end
    object LDoubDot2: TLabel
      Left = 55
      Top = 8
      Width = 4
      Height = 20
      Caption = ':'
      Visible = False
    end
    object LHour: TLabel
      Left = 35
      Top = 8
      Width = 14
      Height = 20
      Caption = '00'
      Visible = False
    end
    object LMinute: TLabel
      Left = 63
      Top = 8
      Width = 14
      Height = 20
      Caption = '00'
      Visible = False
    end
    object LSecond: TLabel
      Left = 93
      Top = 8
      Width = 14
      Height = 20
      Caption = '00'
      Visible = False
    end
    object LTime: TLabel
      Left = 6
      Top = 8
      Width = 23
      Height = 20
      Caption = #1063#1072#1089
    end
  end
  object Panel3: TPanel
    Left = 447
    Top = 435
    Width = 159
    Height = 30
    Caption = 'Panel3'
    TabOrder = 5
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 552
    Top = 288
  end
end
