object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 566
  ClientWidth = 813
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
    Left = 185
    Top = 0
    Height = 566
    ExplicitLeft = 232
    ExplicitTop = 264
    ExplicitHeight = 100
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 566
    Align = alLeft
    TabOrder = 0
    ExplicitLeft = 1
    ExplicitHeight = 551
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 19
      Height = 13
      Caption = 'Size'
    end
    object Label2: TLabel
      Left = 28
      Top = 51
      Width = 38
      Height = 13
      Caption = 'Height: '
    end
    object Label3: TLabel
      Left = 31
      Top = 78
      Width = 35
      Height = 13
      Caption = 'Width: '
    end
    object Label4: TLabel
      Left = 16
      Top = 392
      Width = 23
      Height = 13
      Caption = 'Auto'
    end
    object Label5: TLabel
      Left = 16
      Top = 136
      Width = 37
      Height = 13
      Caption = 'Entrace'
    end
    object Label6: TLabel
      Left = 16
      Top = 213
      Width = 18
      Height = 13
      Caption = 'Exit'
    end
    object Label7: TLabel
      Left = 56
      Top = 161
      Width = 10
      Height = 13
      Caption = 'x:'
    end
    object Label8: TLabel
      Left = 56
      Top = 186
      Width = 10
      Height = 13
      Caption = 'y:'
    end
    object Label9: TLabel
      Left = 56
      Top = 238
      Width = 10
      Height = 13
      Caption = 'x:'
    end
    object Label10: TLabel
      Left = 56
      Top = 265
      Width = 10
      Height = 13
      Caption = 'y:'
    end
    object Label11: TLabel
      Left = 18
      Top = 105
      Width = 48
      Height = 13
      Caption = 'Grid Size: '
    end
    object Button1: TButton
      Left = 29
      Top = 296
      Width = 115
      Height = 25
      Caption = 'Generate Maze'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Edit1: TEdit
      Left = 87
      Top = 48
      Width = 58
      Height = 21
      TabOrder = 1
      Text = '10'
    end
    object Edit2: TEdit
      Left = 87
      Top = 75
      Width = 57
      Height = 21
      TabOrder = 2
      Text = '10'
    end
    object Button2: TButton
      Left = 29
      Top = 327
      Width = 115
      Height = 25
      Caption = 'Load Maze'
      TabOrder = 3
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 28
      Top = 358
      Width = 115
      Height = 25
      Caption = 'Save Maze'
      TabOrder = 4
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 29
      Top = 411
      Width = 115
      Height = 25
      Caption = 'Find a tour'
      TabOrder = 5
      OnClick = Button4Click
    end
    object Edit3: TEdit
      Left = 88
      Top = 158
      Width = 58
      Height = 21
      TabOrder = 6
      Text = '0'
    end
    object Edit4: TEdit
      Left = 88
      Top = 185
      Width = 58
      Height = 21
      TabOrder = 7
      Text = '0'
    end
    object Edit5: TEdit
      Left = 88
      Top = 235
      Width = 58
      Height = 21
      TabOrder = 8
      Text = '9'
    end
    object Edit6: TEdit
      Left = 87
      Top = 262
      Width = 58
      Height = 21
      TabOrder = 9
      Text = '9'
    end
    object CheckBox1: TCheckBox
      Left = 86
      Top = 135
      Width = 84
      Height = 17
      Caption = 'Set Entrance'
      TabOrder = 10
    end
    object CheckBox2: TCheckBox
      Left = 87
      Top = 212
      Width = 60
      Height = 17
      Caption = 'Set Exit'
      TabOrder = 11
    end
    object Edit7: TEdit
      Left = 87
      Top = 102
      Width = 57
      Height = 21
      TabOrder = 12
      Text = '40'
    end
    object CheckBox3: TCheckBox
      Left = 24
      Top = 448
      Width = 113
      Height = 17
      Caption = 'Finding animation'
      TabOrder = 13
    end
    object TrackBar1: TTrackBar
      Left = 29
      Top = 471
      Width = 114
      Height = 45
      Hint = '111'
      Max = 100
      ParentShowHint = False
      ShowHint = True
      TabOrder = 14
    end
    object CheckBox4: TCheckBox
      Left = 24
      Top = 502
      Width = 97
      Height = 17
      Caption = 'Double Buffer'
      TabOrder = 15
    end
    object Button5: TButton
      Left = 31
      Top = 522
      Width = 112
      Height = 25
      Caption = 'Scanning Animation'
      TabOrder = 16
      OnClick = Button5Click
    end
  end
  object PageControl1: TPageControl
    Left = 188
    Top = 0
    Width = 625
    Height = 566
    ActivePage = TabSheet3
    Align = alClient
    TabOrder = 1
    ExplicitWidth = 623
    ExplicitHeight = 551
    object TabSheet1: TTabSheet
      Caption = 'memo'
      ExplicitWidth = 615
      ExplicitHeight = 523
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 617
        Height = 538
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
        ExplicitWidth = 615
        ExplicitHeight = 523
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Show 0/1'
      ImageIndex = 1
      ExplicitWidth = 615
      ExplicitHeight = 523
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 617
        Height = 538
        Align = alClient
        TabOrder = 0
        ExplicitWidth = 615
        ExplicitHeight = 523
      end
    end
    object TabSheet3: TTabSheet
      Caption = '0/1-fixed size'
      ImageIndex = 2
      ExplicitWidth = 615
      ExplicitHeight = 523
      object StringGrid2: TStringGrid
        Left = 0
        Top = 0
        Width = 617
        Height = 538
        Align = alClient
        TabOrder = 0
        OnDrawCell = StringGrid2DrawCell
        ExplicitLeft = 2
        ExplicitWidth = 615
        ExplicitHeight = 523
      end
    end
    object TabSheet4: TTabSheet
      Caption = '0/1-colored'
      ImageIndex = 3
      ExplicitWidth = 615
      ExplicitHeight = 523
      object StringGrid3: TStringGrid
        Left = 0
        Top = 0
        Width = 617
        Height = 538
        Align = alClient
        TabOrder = 0
        OnDrawCell = StringGrid3DrawCell
        ExplicitWidth = 615
        ExplicitHeight = 523
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'symbol-colored'
      ImageIndex = 4
      ExplicitWidth = 615
      ExplicitHeight = 523
      object StringGrid4: TStringGrid
        Left = 0
        Top = 0
        Width = 617
        Height = 538
        Align = alClient
        TabOrder = 0
        OnDrawCell = StringGrid4DrawCell
        ExplicitWidth = 615
        ExplicitHeight = 523
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'colored'
      ImageIndex = 5
      ExplicitWidth = 615
      ExplicitHeight = 523
      object StringGrid5: TStringGrid
        Left = 0
        Top = 0
        Width = 617
        Height = 538
        Align = alClient
        TabOrder = 0
        OnDrawCell = StringGrid5DrawCell
        ExplicitWidth = 615
        ExplicitHeight = 523
      end
    end
    object TabSheet7: TTabSheet
      Caption = 'colored without line'
      ImageIndex = 6
      ExplicitWidth = 615
      ExplicitHeight = 523
      object StringGrid6: TStringGrid
        Left = 0
        Top = 0
        Width = 617
        Height = 538
        Align = alClient
        TabOrder = 0
        OnDrawCell = StringGrid6DrawCell
        ExplicitWidth = 615
        ExplicitHeight = 523
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 152
    Top = 328
  end
  object SaveDialog1: TSaveDialog
    Left = 152
    Top = 360
  end
end
