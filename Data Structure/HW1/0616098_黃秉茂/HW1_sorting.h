//---------------------------------------------------------------------------

#ifndef HW1_sortingH
#define HW1_sortingH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TEdit *Edit1;
	TMemo *Memo1;
	TLabel *Label1;
	TEdit *Edit2;
	TLabel *Label2;
	TButton *Button2;
	TMemo *Memo2;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TButton *Button3;
	TMemo *Memo3;
	TButton *Button4;
	TMemo *Memo4;
	TEdit *Edit3;
	TLabel *Label3;
	TCheckBox *CheckBox3;
	TChart *Chart1;
	TBarSeries *Series1;
	TLineSeries *Series3;
	TButton *Button5;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *Edit4;
	TLabel *Label6;
	TEdit *Edit5;
	TBarSeries *Series2;
	TButton *Button6;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
