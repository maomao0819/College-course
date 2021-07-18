//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "HW1_sorting.h"
//#include <SimpleChart.h>
#include <time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// DEFINE MACRO INSTEAD OF FUNCTION
#define SWAP(x, y, t) (t = x, x = y, y = t)
// x > y, return 1
// x < y, return -1
// x == y, return 0
#define COMPARE(x,y) (((x)>(y)) ? 1 : ((x) == (y)) ? 0 : -1)

// using global variable to pass value easily
int original_data [100000];
int data [100000];
// number of data
int n = 0;
// enable we to reassign n
bool is_n_assigned = false;
// make sure creating chart and 3 series only one time
bool is_ChartANDSeries_exist = false;

TForm1 *Form1;

// PROTOTYPE DECLARATION
// generate random data and assign to array data
void RandData(int data[], int n, int range);
// get data from original data and assing to array 'data'
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
float CalculateDuration(clock_t t_begin, clock_t t_end);
// print cpu time at which memo according argument
void PrintCPUtime(int memo, float duration);
int BinarySearch(int data[], int n, int target);
// for generating different random number by different time
void delay_sec(int time);
void CreateChartANDThreeSeries();
// Add elements to series in chart1
void AddChartSeriesElement(int memo, float value, int n);

// MAIN
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

// generate random number
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if (!is_n_assigned)
		// the number of numbers in array
		n = StrToInt(Edit1->Text);
	// the range of random numbers
	int range = StrToInt(Edit2->Text);
	clock_t t_begin, t_end;
	t_begin = clock();
	RandData(original_data, n, range);
	t_end = clock();
	int memo = 1;
	// clear memo
	if (CheckBox3->Checked)
		ClearMemo(memo);
	// print text
	if (CheckBox1->Checked)
		PrintData(original_data, n, memo);
	float duration = CalculateDuration(t_begin, t_end);
	PrintCPUtime(memo, duration);
	// chart
	CreateChartANDThreeSeries();
	AddChartSeriesElement(memo, duration * 1000, n);
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
	// print text
	if (CheckBox1->Checked)
		PrintData(data, n, memo);
	if (CheckBox2->Checked)
		PrintCheckData(data, n, memo);
	// Form1->Memo2->Lines->Add("n = " + IntToStr(n));
	float duration = CalculateDuration(t_begin, t_end);
	PrintCPUtime(memo, duration);
	// chart
	CreateChartANDThreeSeries();
	AddChartSeriesElement(memo, duration * 1000, n);
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
	// print text
	if (CheckBox1->Checked)
		PrintData(data, n, memo);
	if (CheckBox2->Checked)
		PrintCheckData(data, n, memo);
//	Form1->Memo3->Lines->Add("n = " + IntToStr(n));
	float duration = CalculateDuration(t_begin, t_end);
	PrintCPUtime(memo, duration);
	// chart
	CreateChartANDThreeSeries();
	AddChartSeriesElement(memo, duration * 1000, n);
}
//---------------------------------------------------------------------------

// binary search
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	int target = StrToInt(Edit3->Text);
	// assume not found at begin
	int success = -1;
	success = BinarySearch(data, n, target);
	// found
	if (success >= 0 && success < n)
		Form1->Memo4->Lines->Add(IntToStr(target) + " has been found in data[" + IntToStr(success) + "]!");
	// not found
	else
		Form1->Memo4->Lines->Add(IntToStr(target) + " has NOT been found!");
}
//---------------------------------------------------------------------------

// run all
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	for (int memo = 1; memo <= 3; memo++)
		if (CheckBox3->Checked)
			ClearMemo(memo);

	CreateChartANDThreeSeries();

	n = StrToInt(Edit1->Text); // the number of numbers in array
	is_n_assigned = true;
	int times = StrToInt(Edit4->Text);
	int step = StrToInt(Edit5->Text);
	// generate different ranom number by different time
	int deley = 2;
	while (times--)
	{
		Button1Click(Sender);
		Button2Click(Sender);
		Button3Click(Sender);
		delay_sec(deley);
		n += step;
	}
	is_n_assigned = false;
}
//---------------------------------------------------------------------------

// clean all and initialization
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	for (int memo = 1; memo <= 4; memo++)
		ClearMemo(memo);
	is_ChartANDSeries_exist = false;
	CreateChartANDThreeSeries();
}
//---------------------------------------------------------------------------

// FUNCTION DEFINITION
// generate random data and assign to array data
void RandData(int data[], int n, int range)
{
	// generate random number by time
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		data[i] = rand() % range + 1;
}

// get data from original data and assing to array 'data'
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
		// put the smallest number to the left
		SWAP(data[i], data[min], temp);
        /*
		temp = data[i];
		data[i] = data[min];
		data[min] = temp;
		*/
	}
}

void BubbleSort(int data[], int n)
{
	int temp;
	for (int i = n - 1; i >= 0; i--)
		// put the largest number to the right
		for (int j = 1; j < i + 1; j++)
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
	bool check_data = CheckData(data, n);
	switch(memo)
	{
		case 2:
			if (check_data)
				Form1->Memo2->Lines->Add("Correctly Sorted.");
			else
				Form1->Memo2->Lines->Add("NOT Sorted.");
			break;
		case 3:
			if (check_data)
				Form1->Memo3->Lines->Add("Correctly Sorted.");
			else
				Form1->Memo3->Lines->Add("NOT Sorted.");
	}
}

float CalculateDuration(clock_t t_begin, clock_t t_end)
{
	return (float)(t_end - t_begin) / CLOCKS_PER_SEC;
}

// print cpu time at which memo according argument
void PrintCPUtime(int memo, float duration)
{
	// round to only 4 places after the decimal point
	String duration_str = FloatToStrF(duration, ffFixed, 5, 4);
	switch(memo)
	{
		case 1:
			Form1->Memo1->Lines->Add("CPU time (sec.) = " + duration_str);
			break;
		case 2:
			Form1->Memo2->Lines->Add("CPU time (sec.) = " + duration_str);
			break;
		case 3:
			Form1->Memo3->Lines->Add("CPU time (sec.) = " + duration_str);
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

// for generating different random number by different time
void delay_sec(int time)
{
    clock_t now = clock();
	while (clock() - now < time * 1000);
}

void CreateChartANDThreeSeries()
{
	if (!is_ChartANDSeries_exist)
	{
		Form1->Chart1->RemoveAllSeries();			// Remove all previous series
		Form1->Chart1->Title->Text->Clear();        // Clear chart chart title
		Form1->Chart1->Title->Text->Add("A sample chart");
		Form1->Chart1->BottomAxis->Title->Caption = "data size";    	// x-axis' title
		Form1->Chart1->LeftAxis->Title->Caption = "CPU time (msec.)";   // y-axis' title

		// create 2 new BAR series
		for (int i = 1; i <= 2; i++)
		{
			TBarSeries *Series = new TBarSeries(Form1->Chart1);
			Series->ParentChart = Form1->Chart1;
			Form1->Chart1->AddSeries(Series);
		}
		// create a new LINE series
		Form1->Chart1->AddSeries(new TLineSeries(Form1->Chart1));

		Form1->Chart1->Series[0]->Title = "Selection Sort";
		Form1->Chart1->Series[0]->SeriesColor = clRed;
		Form1->Chart1->Series[1]->Title = "Bubble Sort";
		Form1->Chart1->Series[1]->SeriesColor = clGreen;
		Form1->Chart1->Series[2]->Title = "Data generation";
		Form1->Chart1->Series[2]->SeriesColor = clYellow;

		for (int i = 0; i < 3; i++)     // Set marks visible
		{
			Form1->Chart1->Series[i]->Marks->Visible = true;
			Form1->Chart1->Series[i]->Marks->Style = smsValue;
		}
	}
	is_ChartANDSeries_exist = true;
}

void AddChartSeriesElement(int memo, float value, int n)
{
	switch(memo)
	{
		case 1:
			Form1->Chart1->Series[2]->Add(value, n, clYellow);
			break;
		case 2:
			Form1->Chart1->Series[0]->Add(value, n, clRed);
			break;
		case 3:
			Form1->Chart1->Series[1]->Add(value, n, clGreen);
	}
}
