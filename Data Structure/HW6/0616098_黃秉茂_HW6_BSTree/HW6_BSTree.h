//---------------------------------------------------------------------------

#ifndef HW6_BSTreeH
#define HW6_BSTreeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSplitter *Splitter1;
	TPageControl *PageControl1;
	TMemo *Memo1;
	TTabSheet *TabSheet1;
	TEdit *Edit1;
	TButton *Button2;
	TEdit *Edit2;
	TButton *Button4;
	TLabel *Label1;
	TEdit *Edit3;
	TLabel *Label2;
	TEdit *Edit4;
	TButton *Button6;
	TButton *Button1;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox7;
	TLabel *Label3;
	TLabel *Label4;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TCheckBox *CheckBox6;
	TButton *Button7;
	TLabel *Label5;
	TEdit *Edit5;
	TLabel *Label6;
	TLabel *Label7;
	TButton *Button3;
	TButton *Button5;
	TImage *Image1;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
