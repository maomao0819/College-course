object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 543
  ClientWidth = 856
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
    Top = 193
    Width = 856
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitWidth = 127
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 856
    Height = 193
    ActivePage = TabSheet1
    Align = alTop
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Infix'
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 848
        Height = 165
        Align = alClient
        TabOrder = 0
        object Button1: TButton
          Left = 96
          Top = 56
          Width = 89
          Height = 25
          Caption = 'Infix => Prefix'
          TabOrder = 0
          OnClick = Button1Click
        end
        object Button2: TButton
          Left = 96
          Top = 95
          Width = 89
          Height = 25
          Caption = 'Infix => Postfix'
          TabOrder = 1
          OnClick = Button2Click
        end
        object Edit1: TEdit
          Left = 232
          Top = 20
          Width = 321
          Height = 21
          TabOrder = 2
          Text = '(A+B)*C^(D+E*F-G*(H+J))'
        end
        object Edit2: TEdit
          Left = 232
          Top = 58
          Width = 321
          Height = 21
          TabOrder = 3
        end
        object Edit3: TEdit
          Left = 232
          Top = 97
          Width = 321
          Height = 21
          TabOrder = 4
        end
      end
    end
  end
  object Memo1: TMemo
    Left = 0
    Top = 196
    Width = 856
    Height = 347
    Align = alClient
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssVertical
    TabOrder = 1
  end
end
