//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW2_perm_hanoi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// DEFINE MACRO INSTEAD OF FUNCTION
#define SWAP(x, y, t) (t = x, x = y, y = t)

TForm1 *Form1;

int perm_counter = 0;
int hanoi_counter = 0;

// PROTOTYPE DECLARATION
String CharListToString(char *char_list, int n);
String GenerateBlank(int tab_time);
void Permutation(char *char_list, int k, int n);
void PermutationTracing(char *char_list, int k, int n, int tab_time);
void Hanoi(int disk, String source, String spare, String destination);
void HanoiTracing(int disk_num, String source, String spare, String destination, int tab_time);
void ClearMemo(int memo);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	int k = StrToInt(Edit1_1->Text);
	int n = StrToInt(Edit1_2->Text);
	String str = Edit1_3->Text;
	perm_counter = 0;
	char * char_list;
    if (n > 0 && str == "\0")
	{
		char_list = new char (n);
		for (int i = 0; i < n; i++)
			*(char_list + i) = 'A' + i;
    }
    else if (str != "\0")
	{
		if (n == 0 || n > str.Length())
			n = str.Length();
		char_list = new char (n);
		int i = 0;
		 // Hint: String a starting from position 1 ending at a.Length()
		for (i = 0; i < n; i++)
			*(char_list + i) = str[i + 1];
		char_list[n] = '\0';    // ?r???}?C?B?r?ꪺ????
	}
	Permutation(char_list, k, n);
	delete char_list;
	Form1->Memo1->Lines->Add("-----------------------------");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int k = StrToInt(Edit2_1->Text);
	int n = StrToInt(Edit2_2->Text);
	String str = Edit2_3->Text;
	perm_counter = 0;
	char * char_list;
	if (n > 0 && str == "\0")
	{
		char_list = (char *)malloc(n * sizeof(char));
		for (int i = 0; i < n; i++)
			*(char_list + i) = 'A' + i;
	}
	else if (str != "\0")
	{
		if (n == 0 || n > str.Length())
			n = str.Length();
		char_list = (char *)malloc((n) * sizeof(char));
		int i = 0;
		 // Hint: String a starting from position 1 ending at a.Length()
		for (i = 0; i < n; i++)
			*(char_list + i) = str[i + 1];
		char_list[n] = '\0';    // ?r???}?C?B?r?ꪺ????
	}
	Form1->Memo2->Lines->Add("\tGo ==> (k, n) = (" + IntToStr(k) + ", " + IntToStr(n) + ")");
	int tab_time = 1;
	PermutationTracing(char_list, k, n, tab_time);
	free(char_list);
	Form1->Memo2->Lines->Add("----------------------------------------------------------------------------------------------------------------------");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	int disk_num = StrToInt(Edit3->Text);
	hanoi_counter = 0;
	//?I?sHonoi function
	if (CheckBox3->Checked)
	{
        Form1->Memo3->Lines->Add("< " + IntToStr(disk_num) + " > Try Moving the top " + IntToStr(disk_num) + " disk from tower A to tower C");
		int tab_time = 0;
		HanoiTracing(disk_num, "A", "B", "C", tab_time);
    }
	else
        Hanoi(disk_num, "A", "B", "C");
	Form1->Memo3->Lines->Add("----- " + IntToStr(hanoi_counter) + " steps in total for " + IntToStr(disk_num) + " disks -----");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_Clear_1Click(TObject *Sender)
{
	int memo = 1;
	ClearMemo(memo);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_Clear_2Click(TObject *Sender)
{
	int memo = 2;
	ClearMemo(memo);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_Clear_3Click(TObject *Sender)
{
    int memo = 3;
	ClearMemo(memo);
}
//---------------------------------------------------------------------------
String CharListToString(char *char_list, int n)
{
    // Convert char * list to String a
	String str = char_list;
	// The first n characters of a
	// a.SubString(1, n) ==> the n-char starting from a[1]
	str = str.SubString(1, n);
	return str;
}

String GenerateBlank(int tab_time)
{
	String blank = "\t";
	tab_time--;
	while (tab_time--)
		blank += "\t";
	return blank;
}
void Permutation(char *char_list, int k, int n)
{
	char temp = ' ';
	// ???? char_list[k], ... , char_list[n - 1] ???Ҧ??ƦC
	if (k == n - 1)	// ?׵????󦨥߮ɿ??X?????ƦC
	{
		String str = CharListToString(char_list, n);
		Form1->Memo1->Lines->Add(str + "  [" + IntToStr(perm_counter++)+ "]");
	}
	else            // ??c[k]?T?w???ʡA?DPermutation(c[], k - 1, n)
	{
		// ??c[k] ~ c[n - 1]???y??c[k]
		for (int i = k; i < n; i++)
		{
			// char temp = char_list[k]; char_list[k] = char_list[i], char_list[i] = temp
			SWAP(*(char_list + k), *(char_list + i), temp);
			// ????char_list[k + 1], ... , char_list[n - 1]???Ҧ??ƦC
			Permutation(char_list, k + 1, n);
			// char temp = char_list[k]; char_list[k] = char_list[i], char_list[i] = temp
			// ?٭????r??????
			SWAP(*(char_list + k), *(char_list + i), temp);
		}
	}
}

void PermutationTracing(char *char_list, int k, int n, int tab_time)
{
	char temp = ' ';
	tab_time++;
	String blank = GenerateBlank(tab_time);
	// ???? char_list[k], ... , char_list[n - 1] ???Ҧ??ƦC
	if (k == n - 1)	// ?׵????󦨥߮ɿ??X?????ƦC
	{
		String str = CharListToString(char_list, n);
		Form1->Memo2->Lines->Add(blank + "==> (k, n) = (" + IntToStr(k) + ", " + IntToStr(n) + ")! k == n - 1 print!");
		Form1->Memo2->Lines->Add(str + "  [" + IntToStr(perm_counter++)+ "]");
		tab_time--;
	}
	else            // ??c[k]?T?w???ʡA?DPermutation(c[], k - 1, n)
	{
		// ??c[k] ~ c[n - 1]???y??c[k]
		for (int i = k; i < n; i++)
		{
			// char temp = char_list[k]; char_list[k] = char_list[i], char_list[i] = temp
			SWAP(*(char_list + k), *(char_list + i), temp);
			String str = CharListToString(char_list, n);
			Form1->Memo2->Lines->Add(blank + "> i = " + IntToStr(i) + " (k, n) = (" + IntToStr(k) + ", " + IntToStr(n) + "), swap[k, x] = [" + IntToStr(k) + ", " + IntToStr(i) + "], list[] = " + str);
			// ????char_list[k + 1], ... , char_list[n - 1]???Ҧ??ƦC
			PermutationTracing(char_list, k + 1, n, tab_time);
			// char temp = char_list[k]; char_list[k] = char_list[i], char_list[i] = temp
			// ?٭????r??????
			SWAP(*(char_list + k), *(char_list + i), temp);
            str = CharListToString(char_list, n);
			Form1->Memo2->Lines->Add(blank + "< i = " + IntToStr(i) + " (k, n) = (" + IntToStr(k) + ", " + IntToStr(n) + "), swap[k, x] = [" + IntToStr(k) + ", " + IntToStr(i) + "], list[] = " + str);
		}
	}
}
void Hanoi(int disk_num, String source, String spare, String destination)
{
	if (disk_num == 1)  // move the top disk, ???ʳ̳????L?l???ؼ?
		Form1->Memo3->Lines->Add("Step" + IntToStr(++hanoi_counter) + ": Move the top disk from tower " + source + " to tower " + destination);
	else            	// recursive calls to Hanoi functions
	{
		Hanoi(disk_num - 1, source, destination, spare);
		Hanoi(1, source, spare, destination);
		Hanoi(disk_num - 1, spare, source, destination);
	}
}
void HanoiTracing(int disk_num, String source, String spare, String destination, int tab_time)
{
	tab_time++;
	String blank = GenerateBlank(tab_time);
	if (disk_num == 1)  // move the top disk, ???ʳ̳????L?l???ؼ?
		Form1->Memo3->Lines->Add("Step" + IntToStr(++hanoi_counter) + ": Move the top disk from tower " + source + " to tower " + destination);
	else            	// recursive calls to Hanoi functions
	{
		Form1->Memo3->Lines->Add(blank + "< " + IntToStr(disk_num - 1) + " > Try Moving the top " + IntToStr(disk_num - 1) + " disk from tower " + source + " to tower " + spare);
		HanoiTracing(disk_num - 1, source, destination, spare, tab_time);
		Form1->Memo3->Lines->Add(blank + "< 1 > Try Moving the top 1 disk from tower " + source + " to tower " + destination);
		HanoiTracing(1, source, spare, destination, tab_time);
		Form1->Memo3->Lines->Add(blank + "< " + IntToStr(disk_num - 1) + "> Try Moving the top " + IntToStr(disk_num - 1) + " disk from tower " + spare + " to tower " + spare);
		HanoiTracing(disk_num - 1, spare, source, destination, tab_time);
	}
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

