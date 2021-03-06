object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 590
  ClientWidth = 870
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
    Left = 201
    Top = 0
    Height = 590
    ExplicitLeft = 240
    ExplicitTop = 296
    ExplicitHeight = 100
  end
  object Image1: TImage
    Left = 204
    Top = 0
    Width = 666
    Height = 590
    Align = alClient
    ExplicitLeft = 512
    ExplicitTop = 248
    ExplicitWidth = 105
    ExplicitHeight = 105
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 201
    Height = 590
    Align = alLeft
    TabOrder = 0
    object Label1: TLabel
      Left = 23
      Top = 367
      Width = 105
      Height = 13
      Caption = 'the number of integer'
    end
    object Label2: TLabel
      Left = 24
      Top = 413
      Width = 47
      Height = 13
      Caption = 'range min'
    end
    object Label3: TLabel
      Left = 24
      Top = 16
      Width = 90
      Height = 13
      Caption = 'recursive traversal'
    end
    object Label4: TLabel
      Left = 24
      Top = 81
      Width = 112
      Height = 13
      Caption = 'non-recursive traversal'
    end
    object Label5: TLabel
      Left = 24
      Top = 453
      Width = 51
      Height = 13
      Caption = 'range max'
    end
    object Label6: TLabel
      Left = 24
      Top = 190
      Width = 33
      Height = 13
      Caption = 'Insert:'
    end
    object Label7: TLabel
      Left = 26
      Top = 276
      Width = 35
      Height = 13
      Caption = 'Delete:'
    end
    object Edit1: TEdit
      Left = 63
      Top = 187
      Width = 116
      Height = 21
      TabOrder = 0
      Text = '100'
    end
    object Button2: TButton
      Left = 23
      Top = 214
      Width = 157
      Height = 25
      Caption = 'Insert into BST (recursive)'
      TabOrder = 1
      OnClick = Button2Click
    end
    object Edit2: TEdit
      Left = 67
      Top = 276
      Width = 112
      Height = 21
      TabOrder = 2
      Text = '100'
    end
    object Button4: TButton
      Left = 24
      Top = 303
      Width = 156
      Height = 25
      Caption = 'Delete from BST (recursive)'
      TabOrder = 3
      OnClick = Button4Click
    end
    object Edit3: TEdit
      Left = 23
      Top = 386
      Width = 156
      Height = 21
      TabOrder = 4
      Text = '10'
    end
    object Edit4: TEdit
      Left = 24
      Top = 432
      Width = 155
      Height = 21
      TabOrder = 5
      Text = '0'
    end
    object Button6: TButton
      Left = 24
      Top = 499
      Width = 155
      Height = 25
      Caption = 'Insert Random Integers'
      TabOrder = 6
      OnClick = Button6Click
    end
    object Button1: TButton
      Left = 24
      Top = 154
      Width = 156
      Height = 25
      Caption = 'Print BST'
      TabOrder = 7
      OnClick = Button1Click
    end
    object CheckBox1: TCheckBox
      Left = 24
      Top = 35
      Width = 56
      Height = 17
      Caption = 'In-order'
      Checked = True
      State = cbChecked
      TabOrder = 8
    end
    object CheckBox2: TCheckBox
      Left = 23
      Top = 58
      Width = 73
      Height = 17
      Caption = 'Pre-order'
      TabOrder = 9
    end
    object CheckBox3: TCheckBox
      Left = 102
      Top = 58
      Width = 80
      Height = 17
      Caption = 'Post-order'
      TabOrder = 10
    end
    object CheckBox7: TCheckBox
      Left = 102
      Top = 123
      Width = 80
      Height = 17
      Caption = 'Level-order'
      TabOrder = 11
    end
    object CheckBox4: TCheckBox
      Left = 24
      Top = 100
      Width = 97
      Height = 17
      Caption = 'In-order'
      TabOrder = 12
    end
    object CheckBox5: TCheckBox
      Left = 102
      Top = 100
      Width = 77
      Height = 17
      Caption = 'Pre-order'
      TabOrder = 13
    end
    object CheckBox6: TCheckBox
      Left = 23
      Top = 123
      Width = 73
      Height = 17
      Caption = 'Post-order'
      TabOrder = 14
    end
    object Button7: TButton
      Left = 23
      Top = 530
      Width = 156
      Height = 25
      Caption = 'Clear BST'
      TabOrder = 15
      OnClick = Button7Click
    end
    object Edit5: TEdit
      Left = 23
      Top = 472
      Width = 156
      Height = 21
      TabOrder = 16
      Text = '100'
    end
    object Button3: TButton
      Left = 24
      Top = 245
      Width = 156
      Height = 25
      Caption = 'Insert into BST(nonrecursive)'
      TabOrder = 17
      OnClick = Button3Click
    end
    object Button5: TButton
      Left = 24
      Top = 336
      Width = 157
      Height = 25
      Caption = 'Delete from BST (nonrecursive)'
      TabOrder = 18
      OnClick = Button5Click
    end
  end
  object PageControl1: TPageControl
    Left = 204
    Top = 0
    Width = 666
    Height = 590
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'BST'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 658
        Height = 562
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
end
