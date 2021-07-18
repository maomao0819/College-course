object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 557
  ClientWidth = 955
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
    Top = 225
    Width = 955
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitTop = 193
    ExplicitWidth = 364
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 955
    Height = 225
    ActivePage = TabSheet7
    Align = alTop
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Singly Linked List'
      object Label1: TLabel
        Left = 40
        Top = 8
        Width = 29
        Height = 13
        Caption = 'Insert'
      end
      object Label2: TLabel
        Left = 239
        Top = 8
        Width = 33
        Height = 13
        Caption = 'Search'
      end
      object Label3: TLabel
        Left = 519
        Top = 8
        Width = 39
        Height = 13
        Caption = 'Random'
      end
      object Panel1: TPanel
        Left = 40
        Top = 25
        Width = 193
        Height = 170
        TabOrder = 0
        object Label4: TLabel
          Left = 16
          Top = 16
          Width = 49
          Height = 13
          Caption = 'element ='
        end
        object Button1_1: TButton
          Left = 16
          Top = 45
          Width = 169
          Height = 25
          Caption = 'Print List'
          TabOrder = 0
          OnClick = Button1_1Click
        end
        object Button1_2: TButton
          Left = 16
          Top = 75
          Width = 169
          Height = 25
          Caption = 'Insert First'
          TabOrder = 1
          OnClick = Button1_2Click
        end
        object Button1_3: TButton
          Left = 16
          Top = 106
          Width = 169
          Height = 25
          Caption = 'Insert After First'
          TabOrder = 4
          OnClick = Button1_3Click
        end
        object Button1_4: TButton
          Left = 16
          Top = 137
          Width = 169
          Height = 25
          Caption = 'Insert Last'
          TabOrder = 2
          OnClick = Button1_4Click
        end
        object Edit1_1: TEdit
          Left = 71
          Top = 13
          Width = 114
          Height = 21
          TabOrder = 3
          Text = '30'
        end
      end
      object Panel2: TPanel
        Left = 272
        Top = 25
        Width = 241
        Height = 170
        TabOrder = 1
        object Label5: TLabel
          Left = 24
          Top = 12
          Width = 41
          Height = 13
          Caption = 'target ='
        end
        object Button1_5: TButton
          Left = 32
          Top = 37
          Width = 169
          Height = 25
          Caption = 'Search Target'
          TabOrder = 0
          OnClick = Button1_5Click
        end
        object Edit1_2: TEdit
          Left = 79
          Top = 9
          Width = 130
          Height = 21
          TabOrder = 1
          Text = '30'
        end
        object Button1_6: TButton
          Left = 8
          Top = 68
          Width = 105
          Height = 25
          Caption = 'Insert After Target'
          TabOrder = 2
          OnClick = Button1_6Click
        end
        object Button1_7: TButton
          Left = 119
          Top = 68
          Width = 114
          Height = 25
          Caption = 'Insert Before Target'
          TabOrder = 3
          OnClick = Button1_7Click
        end
        object Button1_8: TButton
          Left = 8
          Top = 99
          Width = 105
          Height = 25
          Caption = 'Find First'
          TabOrder = 5
          OnClick = Button1_8Click
        end
        object Button1_9: TButton
          Left = 119
          Top = 99
          Width = 114
          Height = 25
          Caption = 'Find Last'
          TabOrder = 4
          OnClick = Button1_9Click
        end
        object Button1_10: TButton
          Left = 32
          Top = 130
          Width = 169
          Height = 25
          Caption = 'Delete Target'
          TabOrder = 6
          OnClick = Button1_10Click
        end
      end
      object Panel3: TPanel
        Left = 544
        Top = 25
        Width = 185
        Height = 170
        TabOrder = 2
        object Label6: TLabel
          Left = 8
          Top = 12
          Width = 17
          Height = 13
          Caption = 'n ='
        end
        object Label7: TLabel
          Left = 8
          Top = 41
          Width = 39
          Height = 13
          Caption = 'range ='
        end
        object Edit1_3: TEdit
          Left = 40
          Top = 11
          Width = 121
          Height = 21
          TabOrder = 0
          Text = '10'
        end
        object Edit1_4: TEdit
          Left = 64
          Top = 38
          Width = 97
          Height = 21
          TabOrder = 1
          Text = '100'
        end
        object Button1_11: TButton
          Left = 8
          Top = 65
          Width = 153
          Height = 25
          Caption = 'Insert a Random Number'
          TabOrder = 2
          OnClick = Button1_11Click
        end
        object Button1_12: TButton
          Left = 8
          Top = 96
          Width = 153
          Height = 25
          Caption = 'Reverse List'
          TabOrder = 3
          OnClick = Button1_12Click
        end
        object Button1_13: TButton
          Left = 8
          Top = 127
          Width = 153
          Height = 25
          Caption = 'Clear List'
          TabOrder = 4
          OnClick = Button1_13Click
        end
      end
      object Panel10: TPanel
        Left = 760
        Top = 25
        Width = 162
        Height = 170
        TabOrder = 3
        object Label23: TLabel
          Left = 24
          Top = 21
          Width = 26
          Height = 13
          Caption = 'data:'
        end
        object Edit1_5: TEdit
          Left = 72
          Top = 18
          Width = 57
          Height = 21
          TabOrder = 0
          Text = '30'
        end
        object Button1_14: TButton
          Left = 16
          Top = 94
          Width = 121
          Height = 25
          Caption = 'Next'
          TabOrder = 1
          OnClick = Button1_14Click
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Doubly Linked List'
      ImageIndex = 1
      object Label16: TLabel
        Left = 40
        Top = 8
        Width = 29
        Height = 13
        Caption = 'Insert'
      end
      object Label17: TLabel
        Left = 239
        Top = 8
        Width = 33
        Height = 13
        Caption = 'Search'
      end
      object Label18: TLabel
        Left = 519
        Top = 8
        Width = 39
        Height = 13
        Caption = 'Random'
      end
      object Panel6: TPanel
        Left = 40
        Top = 25
        Width = 193
        Height = 170
        TabOrder = 0
        object Label19: TLabel
          Left = 16
          Top = 16
          Width = 49
          Height = 13
          Caption = 'element ='
        end
        object Button2_1: TButton
          Left = 16
          Top = 45
          Width = 169
          Height = 25
          Caption = 'Print List'
          TabOrder = 0
          OnClick = Button2_1Click
        end
        object Button2_2: TButton
          Left = 16
          Top = 75
          Width = 169
          Height = 25
          Caption = 'Insert First'
          TabOrder = 1
          OnClick = Button2_2Click
        end
        object Button2_3: TButton
          Left = 16
          Top = 106
          Width = 169
          Height = 25
          Caption = 'Insert After First'
          TabOrder = 4
          OnClick = Button2_3Click
        end
        object Button2_4: TButton
          Left = 16
          Top = 137
          Width = 169
          Height = 25
          Caption = 'Insert Last'
          TabOrder = 2
          OnClick = Button2_4Click
        end
        object Edit2_1: TEdit
          Left = 71
          Top = 13
          Width = 114
          Height = 21
          TabOrder = 3
          Text = '30'
        end
      end
      object Panel7: TPanel
        Left = 272
        Top = 25
        Width = 241
        Height = 170
        TabOrder = 1
        object Label20: TLabel
          Left = 24
          Top = 12
          Width = 41
          Height = 13
          Caption = 'target ='
        end
        object Button2_5: TButton
          Left = 32
          Top = 37
          Width = 169
          Height = 25
          Caption = 'Search Target'
          TabOrder = 0
          OnClick = Button2_5Click
        end
        object Edit2_2: TEdit
          Left = 79
          Top = 9
          Width = 130
          Height = 21
          TabOrder = 1
          Text = '30'
        end
        object Button2_6: TButton
          Left = 8
          Top = 68
          Width = 105
          Height = 25
          Caption = 'Insert After Target'
          TabOrder = 2
          OnClick = Button2_6Click
        end
        object Button2_7: TButton
          Left = 119
          Top = 68
          Width = 114
          Height = 25
          Caption = 'Insert Before Target'
          TabOrder = 3
          OnClick = Button2_7Click
        end
        object Button2_8: TButton
          Left = 8
          Top = 99
          Width = 105
          Height = 25
          Caption = 'Find First'
          TabOrder = 5
          OnClick = Button2_8Click
        end
        object Button2_9: TButton
          Left = 119
          Top = 99
          Width = 114
          Height = 25
          Caption = 'Find Last'
          TabOrder = 4
          OnClick = Button2_9Click
        end
        object Button2_10: TButton
          Left = 32
          Top = 130
          Width = 169
          Height = 25
          Caption = 'Delete Target'
          TabOrder = 6
          OnClick = Button2_10Click
        end
      end
      object Panel8: TPanel
        Left = 544
        Top = 25
        Width = 185
        Height = 170
        TabOrder = 2
        object Label21: TLabel
          Left = 8
          Top = 12
          Width = 17
          Height = 13
          Caption = 'n ='
        end
        object Label22: TLabel
          Left = 8
          Top = 41
          Width = 39
          Height = 13
          Caption = 'range ='
        end
        object Edit2_3: TEdit
          Left = 40
          Top = 11
          Width = 121
          Height = 21
          TabOrder = 0
          Text = '10'
        end
        object Edit2_4: TEdit
          Left = 64
          Top = 38
          Width = 97
          Height = 21
          TabOrder = 1
          Text = '100'
        end
        object Button2_11: TButton
          Left = 8
          Top = 65
          Width = 153
          Height = 25
          Caption = 'Insert a Random Number'
          TabOrder = 2
          OnClick = Button2_11Click
        end
        object Button2_12: TButton
          Left = 8
          Top = 96
          Width = 153
          Height = 25
          Caption = 'Reverse List'
          TabOrder = 3
          OnClick = Button2_12Click
        end
        object Button2_13: TButton
          Left = 8
          Top = 127
          Width = 153
          Height = 25
          Caption = 'Clear List'
          TabOrder = 4
          OnClick = Button2_13Click
        end
      end
      object Panel9: TPanel
        Left = 760
        Top = 25
        Width = 162
        Height = 170
        TabOrder = 3
        object data: TLabel
          Left = 24
          Top = 21
          Width = 26
          Height = 13
          Caption = 'data:'
        end
        object Edit2_5: TEdit
          Left = 72
          Top = 18
          Width = 57
          Height = 21
          TabOrder = 0
          Text = '30'
        end
        object Button2_14: TButton
          Left = 16
          Top = 73
          Width = 121
          Height = 25
          Caption = 'Prev'
          TabOrder = 1
          OnClick = Button2_14Click
        end
        object Button2_15: TButton
          Left = 16
          Top = 115
          Width = 121
          Height = 25
          Caption = 'Next'
          TabOrder = 2
          OnClick = Button2_15Click
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Linked Stack'
      ImageIndex = 2
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 947
        Height = 197
        Align = alClient
        TabOrder = 0
        object Label8: TLabel
          Left = 120
          Top = 45
          Width = 17
          Height = 13
          Caption = 'n ='
        end
        object Label9: TLabel
          Left = 208
          Top = 45
          Width = 39
          Height = 13
          Caption = 'range ='
        end
        object Label10: TLabel
          Left = 120
          Top = 92
          Width = 75
          Height = 13
          Caption = 'push element ='
        end
        object Label11: TLabel
          Left = 120
          Top = 141
          Width = 55
          Height = 13
          Caption = 'pop result :'
        end
        object Label_pop_result: TLabel
          Left = 210
          Top = 141
          Width = 3
          Height = 13
        end
        object Button3_1: TButton
          Left = 392
          Top = 40
          Width = 153
          Height = 25
          Caption = 'Push n random elements'
          TabOrder = 0
          OnClick = Button3_1Click
        end
        object Button3_2: TButton
          Left = 392
          Top = 87
          Width = 153
          Height = 25
          Caption = 'Push'
          TabOrder = 1
          OnClick = Button3_2Click
        end
        object Button3_3: TButton
          Left = 392
          Top = 136
          Width = 153
          Height = 25
          Caption = 'Pop'
          TabOrder = 2
          OnClick = Button3_3Click
        end
        object Edit3_1: TEdit
          Left = 143
          Top = 42
          Width = 50
          Height = 21
          TabOrder = 3
          Text = '5'
        end
        object Edit3_2: TEdit
          Left = 253
          Top = 42
          Width = 84
          Height = 21
          TabOrder = 4
          Text = '50'
        end
        object Edit3_3: TEdit
          Left = 209
          Top = 89
          Width = 128
          Height = 21
          TabOrder = 5
          Text = '20'
        end
      end
    end
    object TabSheet7: TTabSheet
      Caption = 'Linked Queue'
      ImageIndex = 3
      object Panel5: TPanel
        Left = 0
        Top = 0
        Width = 947
        Height = 197
        Align = alClient
        TabOrder = 0
        object Label12: TLabel
          Left = 120
          Top = 45
          Width = 17
          Height = 13
          Caption = 'n ='
        end
        object Label13: TLabel
          Left = 208
          Top = 45
          Width = 39
          Height = 13
          Caption = 'range ='
        end
        object Label14: TLabel
          Left = 120
          Top = 92
          Width = 104
          Height = 13
          Caption = 'Add queue element ='
        end
        object Label15: TLabel
          Left = 120
          Top = 141
          Width = 100
          Height = 13
          Caption = 'delete queue result :'
        end
        object Label_delete_queue_result: TLabel
          Left = 238
          Top = 141
          Width = 3
          Height = 13
        end
        object Edit4_1: TEdit
          Left = 143
          Top = 42
          Width = 50
          Height = 21
          TabOrder = 0
          Text = '3'
        end
        object Edit4_2: TEdit
          Left = 253
          Top = 42
          Width = 84
          Height = 21
          TabOrder = 1
          Text = '100'
        end
        object Button4_1: TButton
          Left = 384
          Top = 40
          Width = 169
          Height = 25
          Caption = 'Add queue random  n numbers'
          TabOrder = 2
          OnClick = Button4_1Click
        end
        object Button4_2: TButton
          Left = 384
          Top = 87
          Width = 169
          Height = 25
          Caption = 'Add Queue'
          TabOrder = 3
          OnClick = Button4_2Click
        end
        object Button4_3: TButton
          Left = 384
          Top = 136
          Width = 169
          Height = 25
          Caption = 'Delete Queue'
          TabOrder = 4
          OnClick = Button4_3Click
        end
        object Edit4_3: TEdit
          Left = 238
          Top = 89
          Width = 99
          Height = 21
          TabOrder = 5
          Text = '20'
        end
      end
    end
  end
  object PageControl2: TPageControl
    Left = 0
    Top = 228
    Width = 955
    Height = 329
    ActivePage = TabSheet8
    Align = alClient
    TabOrder = 1
    object TabSheet4: TTabSheet
      Caption = 'The result of Singly Linked List'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 947
        Height = 301
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'The result of Doubly Linked List'
      ImageIndex = 1
      object Memo2: TMemo
        Left = 0
        Top = 0
        Width = 947
        Height = 301
        Align = alClient
        Lines.Strings = (
          'Memo2')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'The result of Linked Stack'
      ImageIndex = 2
      object Memo3: TMemo
        Left = 0
        Top = 0
        Width = 947
        Height = 301
        Align = alClient
        Lines.Strings = (
          'Memo3')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet8: TTabSheet
      Caption = 'The result of Linked Queue'
      ImageIndex = 3
      object Memo4: TMemo
        Left = 0
        Top = 0
        Width = 947
        Height = 301
        Align = alClient
        Lines.Strings = (
          'Memo4')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
end
