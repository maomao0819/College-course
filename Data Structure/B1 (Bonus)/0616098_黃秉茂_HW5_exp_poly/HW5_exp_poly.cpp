//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW5_exp_poly.h"
#include <cmath>
#include <time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int * parameter;

// PROTOTYPE DECLARATION
// calculate with cmath built-in function
long long int pow_built_in(int base, int exponent);
// calculate with recursive
long long int pow_recursive(int base, int exponent);
// calculate with for-loop
long long int pow_for_loop(int base, int exponent);
// calculate with square
long long int pow_square(int base, int exponent);
// calculate with square binary
long long int pow_square_binary(int base, int exponent);
// calculate time duration
float CalculateDuration(clock_t t_begin, clock_t t_end);
// create and initialize array parameter
void Create_param(int k);
// load txt data to array parameter
void Load_param(int k);
// generate random data and assign to array parameter
void Rand_param(int k);
// calculate with general method
long long int general_poly(int n, int x);
// calculate with Horner method
long long int Horner(int n, int x);

// MAIN
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	int base = StrToInt(Edit1->Text);
	int exponent = StrToInt(Edit2->Text);
	int time = StrToInt(Edit3->Text);
	// calculate with cmath built-in function
	if (CheckBox1->Checked)
	{
		int counter = time;
		long long int result = 0;
		clock_t t_begin, t_end;
		t_begin = clock();
		while (counter--)
			result = pow_built_in(base, exponent);
		t_end = clock();
		// calculate time duration
		float duration = CalculateDuration(t_begin, t_end);
		Form1->Memo1->Lines->Add("pow(x, n) with built-in function = " + IntToStr(result) + " [" + FloatToStrF(duration, ffFixed, 5, 4) + "(sec.)] " + IntToStr(time) + " times");
	}
	// calculate with recursive
	if (CheckBox2->Checked)
	{
		int counter = time;
		long long int result = 0;
		clock_t t_begin, t_end;
		t_begin = clock();
		while (counter--)
			result = pow_recursive(base, exponent);
		t_end = clock();
		// calculate time duration
		float duration = CalculateDuration(t_begin, t_end);
		Form1->Memo1->Lines->Add("pow(x, n) with recursive = " + IntToStr(result) + " [" + FloatToStrF(duration, ffFixed, 5, 4) + "(sec.)] " + IntToStr(time) + " times");
	}
	// calculate with for-loop
	if (CheckBox3->Checked)
	{
		int counter = time;
		long long int result = 0;
		clock_t t_begin, t_end;
		t_begin = clock();
		while (counter--)
			result = pow_for_loop(base, exponent);
		t_end = clock();
		// calculate time duration
		float duration = CalculateDuration(t_begin, t_end);
		Form1->Memo1->Lines->Add("pow(x, n) with for-loop = " + IntToStr(result) + " [" + FloatToStrF(duration, ffFixed, 5, 4) + "(sec.)] " + IntToStr(time) + " times");
	}
	// calculate with square
	if (CheckBox4->Checked)
	{
		int counter = time;
		long long int result = 0;
		clock_t t_begin, t_end;
		t_begin = clock();
		while (counter--)
			result = pow_square(base, exponent);
		t_end = clock();
		// calculate time duration
		float duration = CalculateDuration(t_begin, t_end);
		Form1->Memo1->Lines->Add("pow(x, n) with square = " + IntToStr(result) + " [" + FloatToStrF(duration, ffFixed, 5, 4) + "(sec.)] " + IntToStr(time) + " times");
	}
	// calculate with square binary
	if (CheckBox5->Checked)
	{
		int counter = time;
		long long int result = 0;
		clock_t t_begin, t_end;
		t_begin = clock();
		while (counter--)
			result = pow_square_binary(base, exponent);
		t_end = clock();
		// calculate time duration
		float duration = CalculateDuration(t_begin, t_end);
		Form1->Memo1->Lines->Add("pow(x, n) with square binary = " + IntToStr(result) + " [" + FloatToStrF(duration, ffFixed, 5, 4) + "(sec.)] " + IntToStr(time) + " times");
	}
	Form1->Memo1->Lines->Add("---------------------------------------------------------------");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	// delete array parameter if it exists
	if (parameter)
		delete [] parameter;
	int k = StrToInt(Edit4->Text);
	// create and initialize array parameter
	Create_param(k);
	// generate random data and assign to array parameter
    Rand_param(k);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	// delete array parameter if it exists
	if (parameter)
		delete [] parameter;
	int k = StrToInt(Edit4->Text);
	// create and initialize array parameter
	Create_param(k);
	// load txt data to array parameter
	Load_param(k);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	int k = StrToInt(Edit4->Text);
	int n = StrToInt(Edit5->Text);
	// calculate with general method
	Form1->Memo2->Lines->Add("General method:");
    for (int i = 1; i <= n; i++)
		Form1->Memo2->Lines->Add("f(" + IntToStr(i) + ") = " + IntToStr(general_poly(k, i)));
	// calculate with Horner method
	Form1->Memo2->Lines->Add("Horner method:");
    for (int i = 1; i <= n; i++)
		Form1->Memo2->Lines->Add("f(" + IntToStr(i) + ") = " + IntToStr(Horner(k, i)));
	Form1->Memo2->Lines->Add("---------------------------------------------------------------");
}
//---------------------------------------------------------------------------

// FUNCTION DEFINITION
// calculate with cmath built-in function
long long int pow_built_in(int base, int exponent)
{
	return pow(base, exponent);
}

// calculate with recursive
long long int pow_recursive(int base, int exponent)
{
	if (exponent == 1)
		return base;
	else
		return base * pow_recursive(base, exponent - 1);
}

// calculate with for-loop
long long int pow_for_loop(int base, int exponent)
{
	long long int pow = 1;
	for (int i = 0; i < exponent; i++)
		pow *= base;
	return pow;
}

// calculate with square
long long int pow_square(int base, int exponent)
{
	long long int pow = 1;
	long long int multi = base;
	while (exponent > 0)
	{
		// if exponent is odd or even now
		if (exponent % 2 == 1)
			// if exponent is odd now
			pow *= multi;
		// square the base
		multi *= multi;
		// half the exponent
		exponent /= 2;
	}
	return pow;
}

// calculate with square binary
long long int pow_square_binary(int base, int exponent)
{
	long long int pow = 1;
	long long int multi = base;
	while (exponent)
	{
		// if exponent is odd or even now
		if(exponent & 1)
			// if exponent is odd now
			pow *= multi;
		// square the base
		multi *= multi;
		// half the exponent
		exponent >>= 1;
	}
	return pow;
}

// calculate time duration
float CalculateDuration(clock_t t_begin, clock_t t_end)
{
	return (float)(t_end - t_begin) / CLOCKS_PER_SEC;
}

// create and initialize array parameter
void Create_param(int k)
{
	parameter = new int (k);
	for (int i = 0; i < k; i++)
		parameter[i] = 0;
}

// load txt data to array parameter
void Load_param(int k)
{
	// Define fp as a pointer pointing to some file (with data type FILE) in hard desk
	FILE *fp;
	if (Form1->OpenDialog1->Execute())
	{
        // Use builder's string (AnsiString) to ease the conversion (into const char *)
		AnsiString infile;
		infile = Form1->OpenDialog1->FileName;
		// The return value of function c_str is const char *, casting AnsiString to const char * for the use of fopen
		fp = fopen(infile.c_str(), "r+");
		for (int i = 0; i < k; i++)
			fscanf(fp, "%d", &parameter[i]);
		fclose(fp);
	}
	// Print array parameter
	String hint = "";
	for (int i = 0; i < k; i++)
		hint += "a[" + IntToStr(i) + "]\t";
	Form1->Memo2->Lines->Add(hint);
	String para = "";
	for (int i = 0; i < k; i++)
		para += IntToStr(parameter[i]) + "\t";
	Form1->Memo2->Lines->Add(para);
}

// generate random data and assign to array data
void Rand_param(int k)
{
    // generate random number by time
	srand(time(NULL));
	for (int i = 0; i < k; i++)
		// assign random number to array parameter
		parameter[i] = rand() % 200 - 100;
	// Print array parameter
	String hint = "";
	for (int i = 0; i < k; i++)
		hint += "a[" + IntToStr(i) + "]\t";
	Form1->Memo2->Lines->Add(hint);
	String para = "";
	for (int i = 0; i < k; i++)
		para += IntToStr(parameter[i]) + "\t";
	Form1->Memo2->Lines->Add(para);
}

// calculate with general method
long long int general_poly(int n, int x)
{
	// Initialize result
	long long int result = parameter[0];

	// Evaluate value of polynomial using general method
	for (int i = 1; i < n; i++)
		result += parameter[i] * pow_square_binary(x, i);

    return result;
}

// calculate with Horner method
long long int Horner(int n, int x)
{
	// Initialize result
	long long int result = parameter[n - 1];

    // Evaluate value of polynomial using Horner's method
    for (int i = 1; i < n; i++)
		result = result * x + parameter[n - i - 1];

    return result;
}
