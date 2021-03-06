//---------------------------------------------------------------------------

#ifndef HW5_exp_polyH
#define HW5_exp_polyH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TPanel *Panel1;
	TSplitter *Splitter1;
	TPanel *Panel2;
	TSplitter *Splitter2;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit1;
	TEdit *Edit2;
	TButton *Button1;
	TEdit *Edit3;
	TLabel *Label3;
	TPanel *Panel3;
	TLabel *Label4;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TMemo *Memo1;
	TLabel *Label5;
	TLabel *Label6;
	TButton *Button2;
	TEdit *Edit4;
	TEdit *Edit5;
	TButton *Button3;
	TPanel *Panel4;
	TLabel *Label7;
	TOpenDialog *OpenDialog1;
	TButton *Button4;
	TMemo *Memo2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
