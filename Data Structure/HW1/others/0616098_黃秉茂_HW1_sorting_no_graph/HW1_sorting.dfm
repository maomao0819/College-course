object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Selection vs. Bubble sorts by 0616098 '#40643#31177#33538' 2020/9/23'
  ClientHeight = 504
  ClientWidth = 784
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
    Left = 112
    Top = 48
    Width = 17
    Height = 13
    Caption = 'n ='
  end
  object Label2: TLabel
    Left = 90
    Top = 75
    Width = 39
    Height = 13
    Caption = 'range ='
  end
  object Label3: TLabel
    Left = 638
    Top = 75
    Width = 44
    Height = 13
    Caption = 'target = '
  end
  object Button1: TButton
    Left = 56
    Top = 112
    Width = 145
    Height = 25
    Caption = 'Generate Random Numbers'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 144
    Top = 45
    Width = 57
    Height = 21
    TabOrder = 1
    Text = '10'
  end
  object Memo1: TMemo
    Left = 56
    Top = 152
    Width = 145
    Height = 241
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object Edit2: TEdit
    Left = 144
    Top = 72
    Width = 57
    Height = 21
    TabOrder = 3
    Text = '1000'
  end
  object Button2: TButton
    Left = 240
    Top = 112
    Width = 145
    Height = 25
    Caption = 'Selection Sort'
    TabOrder = 4
    OnClick = Button2Click
  end
  object Memo2: TMemo
    Left = 240
    Top = 152
    Width = 145
    Height = 241
    Lines.Strings = (
      'Memo2')
    ScrollBars = ssVertical
    TabOrder = 5
  end
  object CheckBox1: TCheckBox
    Left = 240
    Top = 47
    Width = 97
    Height = 17
    Caption = 'Echo print'
    Checked = True
    State = cbChecked
    TabOrder = 6
  end
  object CheckBox2: TCheckBox
    Left = 240
    Top = 74
    Width = 97
    Height = 17
    Caption = 'Self-check'
    Checked = True
    State = cbChecked
    TabOrder = 7
  end
  object Button3: TButton
    Left = 424
    Top = 112
    Width = 145
    Height = 25
    Caption = 'Bubble Sort'
    TabOrder = 8
    OnClick = Button3Click
  end
  object Memo3: TMemo
    Left = 424
    Top = 152
    Width = 145
    Height = 241
    Lines.Strings = (
      'Memo3')
    ScrollBars = ssVertical
    TabOrder = 9
  end
  object Button4: TButton
    Left = 600
    Top = 112
    Width = 145
    Height = 25
    Caption = 'Binary Search'
    TabOrder = 10
    OnClick = Button4Click
  end
  object Memo4: TMemo
    Left = 600
    Top = 152
    Width = 145
    Height = 241
    Lines.Strings = (
      'Memo4')
    ScrollBars = ssVertical
    TabOrder = 11
  end
  object Edit3: TEdit
    Left = 688
    Top = 72
    Width = 57
    Height = 21
    TabOrder = 12
    Text = '200'
  end
  object CheckBox3: TCheckBox
    Left = 343
    Top = 47
    Width = 97
    Height = 17
    Caption = 'Clear memo'
    Checked = True
    ParentShowHint = False
    ShowHint = False
    State = cbChecked
    TabOrder = 13
  end
end
