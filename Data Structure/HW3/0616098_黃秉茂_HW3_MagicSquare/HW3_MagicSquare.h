//---------------------------------------------------------------------------

#ifndef HW3_MagicSquareH
#define HW3_MagicSquareH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSplitter *Splitter1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TButton *Button1;
	TLabel *Label1;
	TEdit *Edit1;
	TMemo *Memo1;
	TMemo *Memo2;
	TTabSheet *TabSheet3;
	TStringGrid *StringGrid1;
	TCheckBox *CheckBox1;
	TRadioButton *RadioButton_top;
	TRadioButton *RadioButton_left;
	TRadioButton *RadioButton_bottom;
	TRadioButton *RadioButton_right;
	TLabel *Label2;
	TLabel *Label3;
	TCheckBox *CheckBox_LT;
	TCheckBox *CheckBox_LB;
	TCheckBox *CheckBox_RT;
	TCheckBox *CheckBox_RB;
	TLabel *Label4;
	TLabel *Label5;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
