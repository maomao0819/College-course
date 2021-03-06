//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW1_sorting.h"
#include <time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// define swap with macro instead of function
#define SWAP(x, y, t) (t = x, x = y, y = t)
// define compare with macro instead of function
// x > y, return 1
// x < y, return -1
// x == y, return 0
#define COMPARE(x,y) (((x)>(y)) ? 1 : ((x) == (y)) ? 0 : -1)

// using global variable to pass value easily
int original_data [10000];
int data [10000];
// number of data
int n;

TForm1 *Form1;

// prototype declaration
// generate random data and assign to array data
void RandData(int data[], int n, int range);
// get data from original data and assing to array data
void GetData(int data[], int original_data[], int n);
void SelectionSort(int data[], int n);
void BubbleSort(int data[], int n);
// clear memo at which memo according argument
void ClearMemo(int memo);
// print data at which memo according argument
void PrintData(int data[], int n, int memo);
// check data if it is sorted
bool CheckData(int data[], int n);
// print result of CheckData
void PrintCheckData(int data[], int n, int memo);
// print cpu time at which memo according argument
void PrintCPUtime(int memo, clock_t t_begin, clock_t t_end);
int BinarySearch(int data[], int n, int target);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
// generate random number
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	n = StrToInt(Edit1->Text); // the number of numbers in array
	int range = StrToInt(Edit2->Text); // the range of random numbers
	srand(time(NULL));
	clock_t t_begin, t_end;
	t_begin = clock();
	RandData(original_data, n, range);
	t_end = clock();
	int memo = 1;
	// clear memo
	if (CheckBox3->Checked)
		ClearMemo(memo);
	// print
	if (CheckBox1->Checked)
		PrintData(original_data, n, memo);
	PrintCPUtime(memo, t_begin, t_end);
}
//---------------------------------------------------------------------------
// selection sort
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	clock_t t_begin, t_end;
	GetData(data, original_data, n);
	t_begin = clock();
	SelectionSort(data, n);
	t_end = clock();
	int memo = 2;
	// clear memo
	if (CheckBox3->Checked)
		ClearMemo(memo);
	// print
	if (CheckBox1->Checked)
		PrintData(data, n, memo);
	if (CheckBox2->Checked)
		PrintCheckData(data, n, memo);
	// Form1->Memo2->Lines->Add("n = " + IntToStr(n));
	PrintCPUtime(memo, t_begin, t_end);
}
//---------------------------------------------------------------------------
// bubble sort
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	clock_t t_begin, t_end;
	GetData(data, original_data, n);
	t_begin = clock();
	BubbleSort(data, n);
	t_end = clock();
	int memo = 3;
    // clear memo
	if (CheckBox3->Checked)
		ClearMemo(memo);
	// print
	if (CheckBox1->Checked)
		PrintData(data, n, memo);
	if (CheckBox2->Checked)
		PrintCheckData(data, n, memo);
	// Form1->Memo2->Lines->Add("n = " + IntToStr(n));
	PrintCPUtime(memo, t_begin, t_end);
}
//---------------------------------------------------------------------------
// binary search
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	int target = StrToInt(Edit3->Text);
	int success = -1; // assume not found at begin
	success = BinarySearch(data, n, target);
	if (success >= 0 && success < n)	// found
		Form1->Memo4->Lines->Add(IntToStr(target) + " has been found in data[" + IntToStr(success) + "]!");
	else    // not found
		Form1->Memo4->Lines->Add(IntToStr(target) + " has NOT been found!");
}
//---------------------------------------------------------------------------

// define function
// generate random data and assign to array data
void RandData(int data[], int n, int range)
{
	int i;
	for (i = 0; i < n; i++)
		data[i] = rand() % range + 1;
}

// get data from original data and assing to array data
void GetData(int data[], int original_data[], int n)
{
	for (int i = 0; i < n; i++)
		data[i] = original_data[i];
}

void SelectionSort(int data[], int n)
{
	int min, temp;
	for (int i = 0; i < n; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
			if (data[j] < data[min])
				min = j;
		/*
		temp = data[i];
		data[i] = data[min];
		data[min] = temp;
		*/
		// put the smallest number to the left
		SWAP(data[i], data[min], temp);
	}
}

void BubbleSort(int data[], int n)
{
	int temp;
	for (int i = n - 1; i >= 0; i--)
		for (int j = 1; j < i + 1; j++)
			// put the largest number to the right
			if (data[j - 1] > data[j])
				SWAP(data[j - 1], data[j], temp);
}

// clear memo at which memo according argument
void ClearMemo(int memo)
{
    switch(memo)
	{
		case 1:
			Form1->Memo1->Lines->Clear();
			break;
		case 2:
			Form1->Memo2->Lines->Clear();
			break;
		case 3:
			Form1->Memo3->Lines->Clear();
	}
}

// print data at which memo according argument
void PrintData(int data[], int n, int memo)
{
	switch(memo)
	{
		case 1:
			for (int i = 0; i < n; i++)
				Form1->Memo1->Lines->Add("data[" + IntToStr(i) + "] = " + IntToStr(data[i]));
			break;
		case 2:
			for (int i = 0; i < n; i++)
				Form1->Memo2->Lines->Add("data[" + IntToStr(i) + "] = " + IntToStr(data[i]));
			break;
		case 3:
			for (int i = 0; i < n; i++)
				Form1->Memo3->Lines->Add("data[" + IntToStr(i) + "] = " + IntToStr(data[i]));
	}

}

// check data if it is sorted
bool CheckData(int data[], int n)
{
	for (int i = 0; i < n - 1; i++)
		if (data[i] > data[i + 1])
			return false;
    return true;
}

// print result of CheckData
void PrintCheckData(int data[], int n, int memo)
{
	switch(memo)
	{
		case 2:
			if (CheckData(data, n))
				Form1->Memo2->Lines->Add("Correctly Sorted.");
			else
				Form1->Memo2->Lines->Add("NOT Sorted.");
			break;
		case 3:
			if (CheckData(data, n))
				Form1->Memo3->Lines->Add("Correctly Sorted.");
			else
				Form1->Memo3->Lines->Add("NOT Sorted.");
	}
}

// print cpu time at which memo according argument
void PrintCPUtime(int memo, clock_t t_begin, clock_t t_end)
{
	String duration = FloatToStrF((float)(t_end - t_begin) / CLOCKS_PER_SEC, ffFixed, 5, 4);
	switch(memo)
	{
		case 1:
			Form1->Memo1->Lines->Add("CPU time (sec.) = " + duration);
			break;
		case 2:
			Form1->Memo2->Lines->Add("CPU time (sec.) = " + duration);
			break;
		case 3:
			Form1->Memo3->Lines->Add("CPU time (sec.) = " + duration);
	}
}

int BinarySearch(int data[], int n, int target)
{
	int left = 0, right = n, middle;
	while (left <= right)
	{
		middle = (left + right) / 2;
		/*
		if (data[middle] == target)
			return middle;
		else if (data[middle] < target)
			left = middle + 1;
		else
			right = middle - 1;
		*/
		switch (COMPARE(data[middle], target))
		{
			case -1:
				left = middle + 1;
				break;
			case 0:
				return middle;
			case 1:
                right = middle - 1;
		}
	}
	return -1;
}
