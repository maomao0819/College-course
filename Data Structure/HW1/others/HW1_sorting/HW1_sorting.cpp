//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW1_sorting.h"
#include <time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

int data [10000];
int n;

TForm1 *Form1;

void SelectionSort(int data[], int n);
void printData(int data[], int n);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	n = StrToInt(Edit1->Text);
	int range = StrToInt(Edit2->Text);
	int i;
	for (i = 0; i < n; i++) 
	{
		data[i] = rand() % range + 1;
		if (CheckBox1->Checked)
			Form1->Memo1->Lines->Add("data[" + IntToStr(i) + "] = " + IntToStr(data[i]));	
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	clock_t t_begin, t_end;
	t_begin = clock();
	SelectionSort(data, n);
	t_end = clock();
	// Form1->Memo2->Lines->Add("n = " + IntToStr(n));
	Form1->Memo2->Lines->Add("CPU time (sec.) = " + FloatToStr((float)(t_end - t_begin) / CLOCKS_PER_SEC));
	if (CheckBox1->Checked)
		printData(data, n);
}
//---------------------------------------------------------------------------

void SelectionSort(int data[], int n)
{
	int i, j, min, temp;
	for (i = 0; i < n; i++) 
	{
		min = i;
		for (j = i + 1; j < n; j++) 
		{
			if (data[j] < data[min]) 
				min = j;
			temp = data[i];
			data[i] = data[min];
			data[min] = temp;
		}	
	}
}

void printData(int data[], int n)
{
	int i;
	for (i = 0; i < n; i++) 
		Form1->Memo2->Lines->Add("data[" + IntToStr(i) + "] = " + IntToStr(data[i]));		
}