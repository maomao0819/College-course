object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 556
  ClientWidth = 776
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 113
    Width = 776
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitTop = 41
    ExplicitWidth = 515
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 776
    Height = 113
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 40
      Top = 35
      Width = 20
      Height = 13
      Caption = 'n = '
    end
    object Label2: TLabel
      Left = 369
      Top = 15
      Width = 126
      Height = 13
      Caption = 'initial position(for n is odd)'
    end
    object Label3: TLabel
      Left = 544
      Top = 13
      Width = 112
      Height = 13
      Caption = 'movement(for n is odd)'
    end
    object Label4: TLabel
      Left = 40
      Top = 13
      Width = 64
      Height = 13
      Caption = '(n can'#39't be 2)'
    end
    object Label5: TLabel
      Left = 544
      Top = 26
      Width = 123
      Height = 13
      Caption = '(You should select ONE!!)'
    end
    object Button1: TButton
      Left = 200
      Top = 37
      Width = 145
      Height = 42
      Caption = 'Magic Square'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Edit1: TEdit
      Left = 74
      Top = 32
      Width = 99
      Height = 21
      TabOrder = 1
      Text = '3'
    end
    object CheckBox1: TCheckBox
      Left = 40
      Top = 59
      Width = 97
      Height = 17
      Caption = 'Check'
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
    object RadioButton_top: TRadioButton
      Left = 399
      Top = 34
      Width = 49
      Height = 17
      Caption = 'Top'
      Checked = True
      TabOrder = 3
      TabStop = True
    end
    object RadioButton_left: TRadioButton
      Left = 369
      Top = 57
      Width = 49
      Height = 17
      Caption = 'Left'
      TabOrder = 4
    end
    object RadioButton_bottom: TRadioButton
      Left = 399
      Top = 80
      Width = 49
      Height = 17
      Caption = 'Bottom'
      TabOrder = 5
    end
    object RadioButton_right: TRadioButton
      Left = 426
      Top = 57
      Width = 49
      Height = 17
      Caption = 'Right'
      TabOrder = 6
    end
    object CheckBox_LT: TCheckBox
      Left = 544
      Top = 47
      Width = 73
      Height = 17
      Caption = 'left-top'
      Checked = True
      State = cbChecked
      TabOrder = 7
    end
    object CheckBox_LB: TCheckBox
      Left = 544
      Top = 70
      Width = 73
      Height = 17
      Caption = 'left-bottom'
      TabOrder = 8
    end
    object CheckBox_RT: TCheckBox
      Left = 632
      Top = 47
      Width = 73
      Height = 17
      Caption = 'right-top'
      TabOrder = 9
    end
    object CheckBox_RB: TCheckBox
      Left = 632
      Top = 70
      Width = 81
      Height = 17
      Caption = 'right-bottom'
      TabOrder = 10
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 116
    Width = 776
    Height = 440
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Font + Space'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 768
        Height = 412
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Multiple Magic Square (for n is odd)'
      ImageIndex = 1
      object Memo2: TMemo
        Left = 0
        Top = 0
        Width = 768
        Height = 412
        Align = alClient
        Lines.Strings = (
          'Memo2')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Data Grid View'
      ImageIndex = 2
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 768
        Height = 412
        Align = alClient
        TabOrder = 0
      end
    end
  end
end
