//---------------------------------------------------------------------------

#ifndef HW2_perm_hanoiH
#define HW2_perm_hanoiH
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
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TMemo *Memo1;
	TMemo *Memo2;
	TButton *Button1;
	TPanel *Panel2;
	TButton *Button2;
	TMemo *Memo3;
	TButton *Button3;
	TLabel *Label1_3;
	TEdit *Edit1_2;
	TLabel *Label1_2;
	TEdit *Edit1_3;
	TLabel *Label1_4;
	TLabel *Label2_1;
	TEdit *Edit2_1;
	TLabel *Label2_2;
	TEdit *Edit2_2;
	TLabel *Label2_4;
	TCheckBox *CheckBox1;
	TLabel *Label3_1;
	TEdit *Edit3;
	TCheckBox *CheckBox2;
	TPanel *Panel1;
	TPanel *Panel3;
	TLabel *Label3_2;
	TLabel *Label1_1;
	TEdit *Edit1_1;
	TLabel *Label2_3;
	TEdit *Edit2_3;
	TButton *Button_Clear_1;
	TButton *Button_Clear_2;
	TButton *Button_Clear_3;
	TCheckBox *CheckBox3;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button_Clear_1Click(TObject *Sender);
	void __fastcall Button_Clear_2Click(TObject *Sender);
	void __fastcall Button_Clear_3Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
