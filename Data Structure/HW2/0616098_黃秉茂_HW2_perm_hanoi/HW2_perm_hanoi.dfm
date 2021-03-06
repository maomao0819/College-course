object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 572
  ClientWidth = 846
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
    Width = 846
    Height = 572
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Permutations'
      object Memo1: TMemo
        Left = 185
        Top = 0
        Width = 653
        Height = 544
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 185
        Height = 544
        Align = alLeft
        TabOrder = 1
        ExplicitLeft = 32
        ExplicitTop = 40
        object Label1_3: TLabel
          Left = 34
          Top = 133
          Width = 42
          Height = 13
          Caption = 'String = '
        end
        object Label1_2: TLabel
          Left = 34
          Top = 96
          Width = 17
          Height = 13
          Caption = 'n ='
        end
        object Label1_4: TLabel
          Left = 64
          Top = 168
          Width = 97
          Height = 13
          Caption = '(0 <= k <= n <= 9)'
        end
        object Label1_1: TLabel
          Left = 34
          Top = 59
          Width = 19
          Height = 13
          Caption = 'k = '
        end
        object Button1: TButton
          Left = 21
          Top = 228
          Width = 124
          Height = 41
          Caption = 'Permutations'
          TabOrder = 0
          OnClick = Button1Click
        end
        object Edit1_2: TEdit
          Left = 82
          Top = 93
          Width = 50
          Height = 21
          TabOrder = 1
          Text = '5'
        end
        object Edit1_3: TEdit
          Left = 82
          Top = 130
          Width = 50
          Height = 21
          TabOrder = 2
        end
        object CheckBox1: TCheckBox
          Left = 64
          Top = 187
          Width = 97
          Height = 17
          Caption = 'Tracing'
          Checked = True
          State = cbChecked
          TabOrder = 3
        end
        object Edit1_1: TEdit
          Left = 82
          Top = 56
          Width = 50
          Height = 21
          TabOrder = 4
          Text = '0'
        end
        object Button_Clear_1: TButton
          Left = 21
          Top = 288
          Width = 124
          Height = 41
          Caption = 'Clear Memo'
          TabOrder = 5
          OnClick = Button_Clear_1Click
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Permutation-Tracing'
      ImageIndex = 1
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 185
        Height = 544
        Align = alLeft
        TabOrder = 0
        object Label2_1: TLabel
          Left = 34
          Top = 59
          Width = 16
          Height = 13
          Caption = 'k ='
        end
        object Label2_2: TLabel
          Left = 34
          Top = 96
          Width = 17
          Height = 13
          Caption = 'n ='
        end
        object Label2_4: TLabel
          Left = 64
          Top = 168
          Width = 97
          Height = 13
          Caption = '(0 <= k <= n <= 9)'
        end
        object Label2_3: TLabel
          Left = 34
          Top = 133
          Width = 42
          Height = 13
          Caption = 'String = '
        end
        object Button2: TButton
          Left = 21
          Top = 228
          Width = 124
          Height = 41
          Caption = 'Permutations'
          TabOrder = 0
          OnClick = Button2Click
        end
        object Edit2_1: TEdit
          Left = 82
          Top = 56
          Width = 50
          Height = 21
          TabOrder = 1
          Text = '0'
        end
        object Edit2_2: TEdit
          Left = 82
          Top = 93
          Width = 50
          Height = 21
          TabOrder = 2
          Text = '5'
        end
        object CheckBox2: TCheckBox
          Left = 64
          Top = 187
          Width = 97
          Height = 17
          Caption = 'Tracing'
          Checked = True
          State = cbChecked
          TabOrder = 3
        end
        object Edit2_3: TEdit
          Left = 82
          Top = 130
          Width = 50
          Height = 21
          TabOrder = 4
        end
        object Button_Clear_2: TButton
          Left = 21
          Top = 288
          Width = 124
          Height = 41
          Caption = 'Clear Memo'
          TabOrder = 5
          OnClick = Button_Clear_2Click
        end
      end
      object Memo2: TMemo
        Left = 185
        Top = 0
        Width = 653
        Height = 544
        Align = alClient
        Lines.Strings = (
          'Memo2')
        ScrollBars = ssVertical
        TabOrder = 1
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Towers of Hanoi'
      ImageIndex = 2
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 185
        Height = 544
        Align = alLeft
        TabOrder = 0
        object Label3_1: TLabel
          Left = 24
          Top = 91
          Width = 81
          Height = 13
          Caption = 'Number of Disks:'
        end
        object Label3_2: TLabel
          Left = 24
          Top = 280
          Width = 224
          Height = 13
          Caption = 'Please move all the disks from Tower A to T TC'
        end
        object Button3: TButton
          Left = 24
          Top = 184
          Width = 139
          Height = 33
          Caption = 'Tower of Hanoi'
          TabOrder = 0
          OnClick = Button3Click
        end
        object Edit3: TEdit
          Left = 80
          Top = 120
          Width = 83
          Height = 21
          TabOrder = 1
          Text = '3'
        end
        object Button_Clear_3: TButton
          Left = 24
          Top = 232
          Width = 139
          Height = 33
          Caption = 'Clear Memo'
          TabOrder = 2
          OnClick = Button_Clear_3Click
        end
        object CheckBox3: TCheckBox
          Left = 82
          Top = 147
          Width = 81
          Height = 17
          Caption = 'Tracing'
          Checked = True
          State = cbChecked
          TabOrder = 3
        end
      end
      object Memo3: TMemo
        Left = 185
        Top = 0
        Width = 653
        Height = 544
        Align = alClient
        Lines.Strings = (
          'Memo3')
        ScrollBars = ssVertical
        TabOrder = 1
      end
    end
  end
end
