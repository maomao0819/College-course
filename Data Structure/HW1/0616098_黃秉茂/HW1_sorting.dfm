object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Selection vs. Bubble sorts by 0616098 '#40643#31177#33538' 2020/9/23'
  ClientHeight = 621
  ClientWidth = 806
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 80
    Top = 24
    Width = 17
    Height = 13
    Caption = 'n ='
  end
  object Label2: TLabel
    Left = 58
    Top = 51
    Width = 39
    Height = 13
    Caption = 'range ='
  end
  object Label3: TLabel
    Left = 638
    Top = 51
    Width = 44
    Height = 13
    Caption = 'target = '
  end
  object Label4: TLabel
    Left = 192
    Top = 24
    Width = 32
    Height = 13
    Caption = 'repeat'
  end
  object Label5: TLabel
    Left = 282
    Top = 24
    Width = 25
    Height = 13
    Caption = 'times'
  end
  object Label6: TLabel
    Left = 192
    Top = 51
    Width = 36
    Height = 13
    Caption = 'Step = '
  end
  object Button1: TButton
    Left = 56
    Top = 88
    Width = 145
    Height = 25
    Caption = 'Generate Random Numbers'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 112
    Top = 21
    Width = 57
    Height = 21
    TabOrder = 1
    Text = '10000'
  end
  object Memo1: TMemo
    Left = 56
    Top = 128
    Width = 145
    Height = 241
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object Edit2: TEdit
    Left = 112
    Top = 48
    Width = 57
    Height = 21
    TabOrder = 3
    Text = '1000'
  end
  object Button2: TButton
    Left = 240
    Top = 88
    Width = 145
    Height = 25
    Caption = 'Selection Sort'
    TabOrder = 4
    OnClick = Button2Click
  end
  object Memo2: TMemo
    Left = 240
    Top = 128
    Width = 145
    Height = 241
    Lines.Strings = (
      'Memo2')
    ScrollBars = ssVertical
    TabOrder = 5
  end
  object CheckBox1: TCheckBox
    Left = 424
    Top = 23
    Width = 97
    Height = 17
    Caption = 'Echo print'
    Checked = True
    State = cbChecked
    TabOrder = 6
  end
  object CheckBox2: TCheckBox
    Left = 424
    Top = 50
    Width = 97
    Height = 17
    Caption = 'Self-check'
    Checked = True
    State = cbChecked
    TabOrder = 7
  end
  object Button3: TButton
    Left = 424
    Top = 88
    Width = 145
    Height = 25
    Caption = 'Bubble Sort'
    TabOrder = 8
    OnClick = Button3Click
  end
  object Memo3: TMemo
    Left = 424
    Top = 128
    Width = 145
    Height = 241
    Lines.Strings = (
      'Memo3')
    ScrollBars = ssVertical
    TabOrder = 9
  end
  object Button4: TButton
    Left = 600
    Top = 88
    Width = 145
    Height = 25
    Caption = 'Binary Search'
    TabOrder = 10
    OnClick = Button4Click
  end
  object Memo4: TMemo
    Left = 600
    Top = 128
    Width = 145
    Height = 241
    Lines.Strings = (
      'Memo4')
    ScrollBars = ssVertical
    TabOrder = 11
  end
  object Edit3: TEdit
    Left = 688
    Top = 48
    Width = 57
    Height = 21
    TabOrder = 12
    Text = '200'
  end
  object CheckBox3: TCheckBox
    Left = 503
    Top = 23
    Width = 97
    Height = 17
    Caption = 'Clean memo'
    ParentShowHint = False
    ShowHint = False
    TabOrder = 13
  end
  object Chart1: TChart
    Left = 56
    Top = 384
    Width = 689
    Height = 229
    Title.Text.Strings = (
      'TChart')
    TabOrder = 14
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object Series1: TBarSeries
      SeriesColor = clRed
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
    end
    object Series2: TBarSeries
      SeriesColor = clGreen
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
    end
    object Series3: TLineSeries
      SeriesColor = clYellow
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  object Button5: TButton
    Left = 314
    Top = 46
    Width = 71
    Height = 25
    Caption = 'run-all'
    TabOrder = 15
    OnClick = Button5Click
  end
  object Edit4: TEdit
    Left = 234
    Top = 21
    Width = 42
    Height = 21
    TabOrder = 16
    Text = '5'
  end
  object Edit5: TEdit
    Left = 234
    Top = 48
    Width = 42
    Height = 21
    TabOrder = 17
    Text = '5000'
  end
  object Button6: TButton
    Left = 314
    Top = 17
    Width = 71
    Height = 25
    Caption = 'clean-all'
    TabOrder = 18
    OnClick = Button6Click
  end
end
