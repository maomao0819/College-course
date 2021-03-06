//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "B2_infix_prefix_postfix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

String *stack;
String *stack_opn;
int len;
int top = -1;
int top_opn = -1;
// print message when the stack is full and illegal push
void StackFull();
// print message when the stack is empty and illegal pop
void StackEmpty();
// push to the stack
void push(String data);
// pop from the stack
String pop();
bool isOperand(String data);
int p(String data);
int q(String data);
String get_prefix(String x);
// push to the stack
void push_opn(String data);
// pop from the stack
String pop_opn();
void print();
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	String str = Edit1->Text;
	len = str.Length();

	stack_opn = new String (len);
//	String stack_opn [len];
	stack = new String (len);
//    String stack [len];
	String x;
	push("#");
	String postfix = "";
	int c = 0;
	for (int i = 1; i <= len; i++)
	{
		String s = str[i];
		if (isOperand(s))
		{
//			Form1->Memo1->Lines->Add(s);
			push_opn(s);
		}
		else if (s == ")")
			//將堆疊中第一個 ( 之前的運算子皆pop出並印出之
			while ((x = pop()) != "(")
			{
				push_opn(get_prefix(x));

//				Form1->Memo1->Lines->Add("12");
//				c++;
//				if (c > 5) {
//					break;
//				}
			}
		else
		{
			c = 0;
			while (p(s) <= q(stack[top]))
			{
				x = pop();
				// output(x);
				push_opn(get_prefix(x));
//				Form1->Memo1->Lines->Add("77");
//				c++;

//				if (c > 5) {
//					break;
//				}
			}
			push(s);
		}
//		Form1->Memo1->Lines->Add(IntToStr(i));
//		print();
	}
//	int d = 0;
	while ((x = pop()) != "#")
	{
		// output(x);
		push_opn(get_prefix(x));
//		d++;
//		print();
//		Form1->Memo1->Lines->Add("88");
//		if (d>5) {
//			break;
//		}
	}
	Form1->Memo1->Lines->Add(postfix);
	Form1->Edit2->Text = postfix;
	delete stack;
	delete stack_opn;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	String str = Edit1->Text;
	len = str.Length();
	stack = new String (len);
	String x;
	push("#");
	String postfix = "";
	for (int i = 1; i <= len; i++)
	{
		String s = str[i];
		if (isOperand(s))
			// output(s);
			postfix += s;
		else if (s == ")")
			//將堆疊中第一個 ( 之前的運算子皆pop出並印出之
			while ((x = pop()) != "(")
				postfix += x;
		else
		{
			while (p(s) <= q(stack[top]))
			{
				x = pop();
				// output(x);
				postfix += x;
			}
			push(s);
		}
	}
	while ((x = pop()) != "#")
	{
		// output(x);
		postfix += x;
	}
	x = pop();
	Form1->Memo1->Lines->Add(postfix);
	Form1->Edit3->Text = postfix;
	delete stack;
}
//---------------------------------------------------------------------------

// print message when the stack is full and illegal push
void StackFull()
{
	Form1->Memo1->Lines->Add("PUSH is ILLEGAL! Stack is full!");
}

// print message when the stack is empty and illegal pop
void StackEmpty()
{
	Form1->Memo1->Lines->Add("POP is ILLEGAL! Stack is empty!");
}

// push to the stack
void push (String data)
{
	if (top == len)
		StackFull();
	else
		stack[++top] = data;
	return;
}

// pop from the stack
String pop()
{
	if (top == -1)
		StackEmpty();
	else
		return stack[top--];
}

bool isOperand(String data)
{
	if (((data >= 'a') && (data <= 'z')) || ((data >= 'A') && (data <= 'Z')))
		return True;
	return False;
}
int p(String data)
{
	if (data == "(")
		return 10;
	else if (data == "^")
		return 9;
	else if (data == "*" || data == "/" || data == "%")
		return 8;
	else if (data == "+" || data == "-")
		return 7;
	else if (data == "&&")
		return 3;
	else if (data == "||")
		return 2;
	else if (data == "#")
		return -1;
}
int q(String data)
{
	if (data == "(")
		return 0;
	else if (data == "^")
		return 9;
	else if (data == "*" || data == "/" || data == "%")
		return 8;
	else if (data == "+" || data == "-")
		return 7;
	else if (data == "&&")
		return 3;
	else if (data == "||")
		return 2;
	else if (data == "#")
		return -1;
}

// push to the stack
void push_opn(String data)
{
	if (top_opn == len)
		StackFull();
	else
	{
		stack_opn[++top_opn] = data;
		Form1->Memo1->Lines->Add(IntToStr(top_opn));
		Form1->Memo1->Lines->Add("asas" + stack_opn[top_opn]);
	}
	Form1->Memo1->Lines->Add("lala"+ data);
}
// pop from the stack
String pop_opn()
{
	if (top_opn == -1)
		StackEmpty();
	else
		return stack_opn[top_opn--];
}

String get_prefix(String x)
{
	String a = pop_opn();
	String pre = x + pop_opn() + a;
	return pre;
}
void print()
{
	String s = "operator: ";
	for (int i = 0; i < top; i++) {
		s+= stack[i] + " ";
	}
	Form1->Memo1->Lines->Add(s);
	s = "opn: ";
	for (int i = 0; i < top_opn; i++) {
		s+= stack_opn[i] + " ";
	}
	Form1->Memo1->Lines->Add(s);
}
