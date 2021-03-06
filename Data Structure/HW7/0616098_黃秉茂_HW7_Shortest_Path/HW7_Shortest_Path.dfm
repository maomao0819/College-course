object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 570
  ClientWidth = 834
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
    Left = 233
    Top = 0
    Height = 570
    ExplicitLeft = 328
    ExplicitTop = 208
    ExplicitHeight = 100
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 233
    Height = 570
    Align = alLeft
    TabOrder = 0
    object Label1: TLabel
      Left = 9
      Top = 19
      Width = 48
      Height = 13
      Caption = 'G = (V, E)'
    end
    object Label2: TLabel
      Left = 25
      Top = 64
      Width = 103
      Height = 13
      Caption = 'Ramdomly Generated'
    end
    object Label3: TLabel
      Left = 40
      Top = 85
      Width = 17
      Height = 13
      Caption = 'n ='
    end
    object Label4: TLabel
      Left = 40
      Top = 110
      Width = 69
      Height = 13
      Caption = 'range(w(e)) ='
    end
    object Label5: TLabel
      Left = 40
      Top = 136
      Width = 42
      Height = 13
      Caption = 'if w(e) >'
    end
    object Label6: TLabel
      Left = 40
      Top = 160
      Width = 33
      Height = 13
      Caption = 'w(e) ='
    end
    object Label7: TLabel
      Left = 40
      Top = 216
      Width = 63
      Height = 13
      Caption = 'Source no. ='
    end
    object Label8: TLabel
      Left = 25
      Top = 298
      Width = 99
      Height = 13
      Caption = 'Shortest Path Solver'
    end
    object Label9: TLabel
      Left = 42
      Top = 187
      Width = 78
      Height = 13
      Caption = 'min # weights ='
    end
    object Button2: TButton
      Left = 40
      Top = 267
      Width = 161
      Height = 25
      Caption = 'Generate G'
      TabOrder = 0
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 40
      Top = 329
      Width = 161
      Height = 25
      Caption = 'Single Source All Destinations'
      TabOrder = 1
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 40
      Top = 360
      Width = 161
      Height = 25
      Caption = 'All Pairs'
      TabOrder = 2
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 40
      Top = 391
      Width = 161
      Height = 25
      Caption = 'Transitive Closure'
      TabOrder = 3
      OnClick = Button5Click
    end
    object Edit1: TEdit
      Left = 130
      Top = 83
      Width = 71
      Height = 21
      TabOrder = 4
      Text = '10'
    end
    object Edit2: TEdit
      Left = 130
      Top = 107
      Width = 71
      Height = 21
      TabOrder = 5
      Text = '1000'
    end
    object Edit3: TEdit
      Left = 130
      Top = 134
      Width = 71
      Height = 21
      TabOrder = 6
      Text = '250'
    end
    object Edit4: TEdit
      Left = 130
      Top = 157
      Width = 71
      Height = 21
      TabOrder = 7
      Text = '99999'
    end
    object Edit6: TEdit
      Left = 130
      Top = 213
      Width = 71
      Height = 21
      TabOrder = 8
      Text = '3'
    end
    object Button1: TButton
      Left = 112
      Top = 33
      Width = 89
      Height = 25
      Caption = 'Read G'
      TabOrder = 9
      OnClick = Button1Click
    end
    object CheckBox1: TCheckBox
      Left = 40
      Top = 244
      Width = 97
      Height = 17
      Caption = 'Undirected'
      TabOrder = 10
    end
    object CheckBox2: TCheckBox
      Left = 130
      Top = 244
      Width = 97
      Height = 17
      Caption = 'Print detail'
      TabOrder = 11
    end
    object Edit5: TEdit
      Left = 130
      Top = 184
      Width = 71
      Height = 21
      TabOrder = 12
      Text = '25'
    end
  end
  object PageControl1: TPageControl
    Left = 236
    Top = 0
    Width = 598
    Height = 570
    ActivePage = TabSheet3
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Text'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 590
        Height = 542
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Graph in adjacent matrix'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 590
        Height = 542
        Align = alClient
        TabOrder = 0
        RowHeights = (
          24
          24
          24
          24
          24)
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'SSAD table'
      ImageIndex = 2
      object StringGrid2: TStringGrid
        Left = 0
        Top = 0
        Width = 590
        Height = 542
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'All pairs'
      ImageIndex = 3
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object StringGrid3: TStringGrid
        Left = 0
        Top = 0
        Width = 590
        Height = 542
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'All pairs table'
      ImageIndex = 4
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object StringGrid4: TStringGrid
        Left = 0
        Top = 0
        Width = 590
        Height = 542
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'Transitive Closure'
      ImageIndex = 5
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object StringGrid5: TStringGrid
        Left = 0
        Top = 0
        Width = 590
        Height = 542
        Align = alClient
        TabOrder = 0
        ExplicitLeft = -1
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 80
    Top = 32
  end
end
