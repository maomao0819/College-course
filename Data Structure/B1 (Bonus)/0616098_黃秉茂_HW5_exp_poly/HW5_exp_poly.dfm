object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 464
  ClientWidth = 752
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 752
    Height = 464
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Power'
      object Splitter1: TSplitter
        Left = 185
        Top = 0
        Height = 436
        ExplicitLeft = 320
        ExplicitTop = 224
        ExplicitHeight = 100
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 185
        Height = 436
        Align = alLeft
        TabOrder = 0
        object Label1: TLabel
          Left = 21
          Top = 40
          Width = 17
          Height = 13
          Caption = 'x ='
        end
        object Label3: TLabel
          Left = 21
          Top = 171
          Width = 31
          Height = 13
          Caption = 'time ='
        end
        object Label4: TLabel
          Left = 16
          Top = 237
          Width = 45
          Height = 13
          Caption = 'Algorithm'
        end
        object Label2: TLabel
          Left = 21
          Top = 75
          Width = 17
          Height = 13
          Caption = 'n ='
        end
        object Edit1: TEdit
          Left = 58
          Top = 37
          Width = 57
          Height = 21
          TabOrder = 0
          Text = '2'
        end
        object Edit2: TEdit
          Left = 58
          Top = 72
          Width = 57
          Height = 21
          TabOrder = 1
          Text = '30'
        end
        object Button1: TButton
          Left = 23
          Top = 112
          Width = 132
          Height = 33
          Caption = 'x ^ n'
          TabOrder = 2
          OnClick = Button1Click
        end
        object Edit3: TEdit
          Left = 58
          Top = 168
          Width = 91
          Height = 21
          TabOrder = 3
          Text = '10000000'
        end
        object Panel3: TPanel
          Left = 16
          Top = 256
          Width = 145
          Height = 145
          TabOrder = 4
          object CheckBox1: TCheckBox
            Left = 16
            Top = 16
            Width = 97
            Height = 17
            Caption = 'built-in function'
            Checked = True
            State = cbChecked
            TabOrder = 0
          end
          object CheckBox2: TCheckBox
            Left = 16
            Top = 39
            Width = 97
            Height = 17
            Caption = 'recursive'
            Checked = True
            State = cbChecked
            TabOrder = 1
          end
          object CheckBox3: TCheckBox
            Left = 16
            Top = 62
            Width = 97
            Height = 17
            Caption = 'for-loop'
            Checked = True
            State = cbChecked
            TabOrder = 2
          end
          object CheckBox4: TCheckBox
            Left = 16
            Top = 82
            Width = 97
            Height = 17
            Caption = 'squaring'
            Checked = True
            State = cbChecked
            TabOrder = 3
          end
          object CheckBox5: TCheckBox
            Left = 16
            Top = 105
            Width = 97
            Height = 17
            Caption = 'squaring binary'
            Checked = True
            State = cbChecked
            TabOrder = 4
          end
        end
      end
      object Memo1: TMemo
        Left = 188
        Top = 0
        Width = 556
        Height = 436
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 1
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Polynomials'
      ImageIndex = 1
      object Splitter2: TSplitter
        Left = 185
        Top = 0
        Height = 436
        ExplicitLeft = 194
        ExplicitTop = -24
        ExplicitHeight = 557
      end
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 185
        Height = 436
        Align = alLeft
        TabOrder = 0
        object Label5: TLabel
          Left = 32
          Top = 72
          Width = 16
          Height = 13
          Caption = 'k ='
        end
        object Label6: TLabel
          Left = 32
          Top = 112
          Width = 17
          Height = 13
          Caption = 'n ='
        end
        object Label7: TLabel
          Left = 18
          Top = 157
          Width = 64
          Height = 13
          Caption = 'Generate a[i]'
        end
        object Edit4: TEdit
          Left = 66
          Top = 69
          Width = 71
          Height = 21
          TabOrder = 0
          Text = '5'
        end
        object Edit5: TEdit
          Left = 66
          Top = 109
          Width = 71
          Height = 21
          TabOrder = 1
          Text = '5'
        end
        object Panel4: TPanel
          Left = 16
          Top = 176
          Width = 137
          Height = 97
          TabOrder = 2
          object Button2: TButton
            Left = 16
            Top = 25
            Width = 105
            Height = 25
            Caption = 'Randomly Generate'
            TabOrder = 0
            OnClick = Button2Click
          end
          object Button3: TButton
            Left = 16
            Top = 56
            Width = 105
            Height = 25
            Caption = 'Load'
            TabOrder = 1
            OnClick = Button3Click
          end
        end
        object Button4: TButton
          Left = 18
          Top = 296
          Width = 135
          Height = 25
          Caption = 'Polynomials'
          TabOrder = 3
          OnClick = Button4Click
        end
      end
      object Memo2: TMemo
        Left = 188
        Top = 0
        Width = 556
        Height = 436
        Align = alClient
        Lines.Strings = (
          'Memo2')
        ScrollBars = ssVertical
        TabOrder = 1
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 124
    Top = 256
  end
end
