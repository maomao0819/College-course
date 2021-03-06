//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW5_Linked_List.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// DECLAIR NEW DATA STRUCTURE

// Singly linked list node
typedef struct node
{
	int data;
	struct node * next;
} NODE;

// Doubly inked list node
typedef struct dnode
{
	int data;
	struct dnode * prev;
	struct dnode * next;
} DNODE;

// GLOBAL VARIABLE

// Singly linked list
// first blank node and last node
NODE * first, * last;
// for node index
int count = 0;

// Doubly inked list
// first blank dnode and last dnode
DNODE * head, * tail;
// for dnode index
int Dcount = 0;

// Linked Stack
NODE * top;

// Linked Queue
NODE * front, * rear;


// PROTOTYPE DECLARATION

// create node
NODE * NewNode(int element);
// create head biank node
void NewHeadBlankNode();
// create dnode
DNODE * NewDnode(int element);
// create head biank dnode
void NewHeadBlankDnode(String str);
// create 4 list
void Constructure();

// Singly linked list
// insert after head biank node
void InsertFirst(int element);
// insert element after node
void InsertAfter(NODE * x, int element);
// append list
void InsertLast(int element);
// search the node with target
NODE * Search(int target);
// search the node before target
NODE * SearchBefore(int target);
// delete the node after node x
int DeleteAfter(NODE * x);
// append random number
void RandomNumberInsertLast(int n, int range);
// reverse the list
void ReverseList();
// clear the list
void ClearList();
// print the list
void PrintList();

// Doubly linked list
// insert after head biank dnode
void InsertHead(int element);
// insert element after dnode
void InsertAfterD(DNODE * x, int element);
// append dlist
void InsertTail(int element);
// search the dnode with target
DNODE * SearchD(int target);
// delete the dnode
int DeleteD(DNODE * x);
// append random number
void RandomNumberInsertTail(int n, int range);
// reverse the dlist
void ReverseDList();
// clear the dlist
void ClearDList();
// print the dlist
void PrintDList();

// Linked Stack
// push into linked stack
void push(int element);
// pop from linked stack
int pop();
// push random number into linked stack
void RandomNumberPush(int n, int range);
// print the linked stack
void PrintStack();

// Linked Queue
// add into linked queue
void AddQueue(int element);
// delete from linked queue
int DeleteQueue();
// Add random number into linked queue
void RandomNumberAddQueue(int n, int range);
// print the linked queue
void PrintQueue();

//---------------------------------------------------------------------------
// initialization
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Constructure();
}
//---------------------------------------------------------------------------

// Singly Linked list
// Print List
 void __fastcall TForm1::Button1_1Click(TObject *Sender)
{
	PrintList();
}
//---------------------------------------------------------------------------

// Insert First
void __fastcall TForm1::Button1_2Click(TObject *Sender)
{
	int data = Edit1_1->Text.ToInt();
	InsertFirst(data);
	PrintList();
}
//---------------------------------------------------------------------------

// Insert After First
void __fastcall TForm1::Button1_3Click(TObject *Sender)
{
	int data = Edit1_1->Text.ToInt();
	// read Edit1_1 and insert after first
	InsertAfter(first->next, data);
	PrintList();
}
//---------------------------------------------------------------------------

// Insert Last
void __fastcall TForm1::Button1_4Click(TObject *Sender)
{
	int data = Edit1_1->Text.ToInt();
	InsertLast(data);
	PrintList();
}
//---------------------------------------------------------------------------

// Search Target
void __fastcall TForm1::Button1_5Click(TObject *Sender)
{
	int target = Edit1_2->Text.ToInt();
	NODE * p;
	// search the node with target
	p = Search(target);
	// found
	if (p)
		Form1->Memo1->Lines->Add("The target " + IntToStr(target) + " has been found at Node " + IntToStr(count) + ".");
	// not found
	else
		Form1->Memo1->Lines->Add("The target " + IntToStr(target) + " has NOT been found in the list.");
}
//---------------------------------------------------------------------------

// Insert After Target
void __fastcall TForm1::Button1_6Click(TObject *Sender)
{
	int data = Edit1_1->Text.ToInt();
	int target = Edit1_2->Text.ToInt();
	NODE * p;
	// search the node with target
	p = Search(target);
	// found
	if (p)
		InsertAfter(p, data);
	// not found
	else
		Form1->Memo1->Lines->Add("The target " + IntToStr(target) + " has NOT been found in the list.");
	PrintList();
}
//---------------------------------------------------------------------------

// Insert Before Target
void __fastcall TForm1::Button1_7Click(TObject *Sender)
{
	int data = Edit1_1->Text.ToInt();
	int target = Edit1_2->Text.ToInt();
	NODE * p;
	// search the node before target
	p = SearchBefore(target);
	// found
	if (p)
		InsertAfter(p, data);
	// not found
	else
		Form1->Memo1->Lines->Add("The target " + IntToStr(target) + " has NOT been found in the list.");
	PrintList();
}
//---------------------------------------------------------------------------

// Find First
void __fastcall TForm1::Button1_8Click(TObject *Sender)
{
	Form1->Memo1->Lines->Add(IntToStr(first->next->data));
}
//---------------------------------------------------------------------------

// Find Last
void __fastcall TForm1::Button1_9Click(TObject *Sender)
{
	Form1->Memo1->Lines->Add(IntToStr(last->data));
}
//---------------------------------------------------------------------------

// Delete Target
void __fastcall TForm1::Button1_10Click(TObject *Sender)
{
	int target = Edit1_2->Text.ToInt();
	NODE * p;
	// search the node before target
	p = SearchBefore(target);
	// found
	if (p)
		int data = DeleteAfter(p);
	// not found
	else
		Form1->Memo1->Lines->Add("The target " + IntToStr(target) + " has NOT been found in the list.");
	PrintList();
}
//---------------------------------------------------------------------------

// Insert Random Number
void __fastcall TForm1::Button1_11Click(TObject *Sender)
{
	int n = Edit1_3->Text.ToInt();
	int range = Edit1_4->Text.ToInt();
	RandomNumberInsertLast(n, range);
	PrintList();
}
//---------------------------------------------------------------------------

// Reverse List
void __fastcall TForm1::Button1_12Click(TObject *Sender)
{
	ReverseList();
	PrintList();
}
//---------------------------------------------------------------------------

// Clear List
void __fastcall TForm1::Button1_13Click(TObject *Sender)
{
	ClearList();
	PrintList();
}
//---------------------------------------------------------------------------

// Next Element
void __fastcall TForm1::Button1_14Click(TObject *Sender)
{
	int target = Edit1_5->Text.ToInt();
	NODE * p;
	// search the node with target
	p = Search(target);
	// found
	if (p)
	{
		int next_data = p->next->data;
		if (p->next == first)
			next_data = p->next->next->data;
		Form1->Memo1->Lines->Add("The next data of the data " + IntToStr(target) + " is " + IntToStr(next_data) + ".");
		Edit1_5->Text = next_data;
	}
	// not found
	else
		Form1->Memo1->Lines->Add("The data " + IntToStr(target) + " has NOT been found in the list.");
}
//---------------------------------------------------------------------------

// Doubly Linked list
// Print List
void __fastcall TForm1::Button2_1Click(TObject *Sender)
{
	PrintDList();
}
//---------------------------------------------------------------------------

// Insert Head
void __fastcall TForm1::Button2_2Click(TObject *Sender)
{
	int data = Edit2_1->Text.ToInt();
	InsertHead(data);
	PrintDList();
}
//---------------------------------------------------------------------------

// Insert After Head
void __fastcall TForm1::Button2_3Click(TObject *Sender)
{
	int data = Edit2_1->Text.ToInt();
	// read Edit2_1 and insert after first
	InsertAfterD(head->next, data);
	PrintDList();
}
//---------------------------------------------------------------------------

// Insert Tail
void __fastcall TForm1::Button2_4Click(TObject *Sender)
{
	int data = Edit2_1->Text.ToInt();
	InsertTail(data);
	PrintDList();
}
//---------------------------------------------------------------------------

// Search Target
void __fastcall TForm1::Button2_5Click(TObject *Sender)
{
	int target = Edit2_2->Text.ToInt();
	DNODE * p;
	p = SearchD(target);
	// found
	if (p)
		Form1->Memo2->Lines->Add("The target " + IntToStr(target) + " has been found at Node " + IntToStr(count) + ".");
	// not found
	else
		Form1->Memo2->Lines->Add("The target " + IntToStr(target) + " has NOT been found in the list.");
}
//---------------------------------------------------------------------------

// Insert After Target
void __fastcall TForm1::Button2_6Click(TObject *Sender)
{
	int data = Edit2_1->Text.ToInt();
	int target = Edit2_2->Text.ToInt();
	DNODE * p;
	// search the node with target
	p = SearchD(target);
	// found
	if (p)
		InsertAfterD(p, data);
	// not found
	else
		Form1->Memo2->Lines->Add("The target " + IntToStr(target) + " has NOT been found in the list.");
	PrintDList();
}
//---------------------------------------------------------------------------

// Insert Before Target
void __fastcall TForm1::Button2_7Click(TObject *Sender)
{
	int data = Edit2_1->Text.ToInt();
	int target = Edit2_2->Text.ToInt();
	DNODE * p;
	// search the node with target
	p = SearchD(target)->prev;
	// found
	if (p)
		InsertAfterD(p, data);
	// not found
	else
		Form1->Memo2->Lines->Add("The target " + IntToStr(target) + " has NOT been found in the list.");
	PrintDList();
}
//---------------------------------------------------------------------------

// Find Head
void __fastcall TForm1::Button2_8Click(TObject *Sender)
{
	Form1->Memo2->Lines->Add(IntToStr(head->next->data));
}
//---------------------------------------------------------------------------

// Find Tail
void __fastcall TForm1::Button2_9Click(TObject *Sender)
{
	Form1->Memo2->Lines->Add(IntToStr(tail->data));
}
//---------------------------------------------------------------------------

// Delete Target
void __fastcall TForm1::Button2_10Click(TObject *Sender)
{
	int target = Edit2_2->Text.ToInt();
	DNODE * p;
	// search the node with target
	p = SearchD(target);
	// found
	if (p)
		int data = DeleteD(p);
	// not found
	else
		Form1->Memo2->Lines->Add("The target " + IntToStr(target) + " has NOT been found in the list.");
	PrintDList();
}
//---------------------------------------------------------------------------

// Insert Random Number
void __fastcall TForm1::Button2_11Click(TObject *Sender)
{
	int n = Edit2_3->Text.ToInt();
	int range = Edit2_4->Text.ToInt();
	RandomNumberInsertTail(n, range);
	PrintDList();
}
//---------------------------------------------------------------------------

// Reverse List
void __fastcall TForm1::Button2_12Click(TObject *Sender)
{
	ReverseDList();
	PrintDList();
}
//---------------------------------------------------------------------------

// Clear List
void __fastcall TForm1::Button2_13Click(TObject *Sender)
{
	ClearDList();
	PrintDList();
}
//---------------------------------------------------------------------------

// Prev Element
void __fastcall TForm1::Button2_14Click(TObject *Sender)
{
	int target = Edit2_5->Text.ToInt();
	DNODE * p;
	// search the node with target
	p = SearchD(target);
	// found
	if (p)
	{
		int prev_data = p->prev->data;
		if (p->prev == head)
			prev_data = p->prev->prev->data;
		Form1->Memo2->Lines->Add("The prev data of the data " + IntToStr(target) + " is " + IntToStr(prev_data) + ".");
		Edit2_5->Text = prev_data;
	}
	// not found
	else
		Form1->Memo2->Lines->Add("The data " + IntToStr(target) + " has NOT been found in the list.");
}
//---------------------------------------------------------------------------

// Next Element
void __fastcall TForm1::Button2_15Click(TObject *Sender)
{
	int target = Edit2_5->Text.ToInt();
	DNODE * p;
	// search the node with target
	p = SearchD(target);
    // found
	if (p)
	{
		int next_data = p->next->data;
		if (p->next == head)
			next_data = p->next->next->data;
		Form1->Memo2->Lines->Add("The next data of the data " + IntToStr(target) + " is " + IntToStr(next_data) + ".");
		Edit2_5->Text = next_data;
	}
	// not found
	else
		Form1->Memo2->Lines->Add("The data " + IntToStr(target) + " has NOT been found in the list.");
}
//---------------------------------------------------------------------------

// Linked Stack
// Push n random numbers
void __fastcall TForm1::Button3_1Click(TObject *Sender)
{
	int n = Edit3_1->Text.ToInt();
	int range = Edit3_2->Text.ToInt();
	RandomNumberPush(n, range);
	PrintStack();
}
//---------------------------------------------------------------------------

// Push
void __fastcall TForm1::Button3_2Click(TObject *Sender)
{
	int data = Edit3_3->Text.ToInt();
	push(data);
	PrintStack();
}
//---------------------------------------------------------------------------

// Pop
void __fastcall TForm1::Button3_3Click(TObject *Sender)
{
	int result = pop();
	if (result != -1)
	{
		PrintStack();
		Form1->Label_pop_result->Caption = result;
	}
	else
		Form1->Memo3->Lines->Add("Stack is EMPTY!");
}
//---------------------------------------------------------------------------

// Linked Queue
// Add queue random n number
void __fastcall TForm1::Button4_1Click(TObject *Sender)
{
	int n = Edit4_1->Text.ToInt();
	int range = Edit4_2->Text.ToInt();
	RandomNumberAddQueue(n, range);
	PrintQueue();
}
//---------------------------------------------------------------------------

// Add Queue
void __fastcall TForm1::Button4_2Click(TObject *Sender)
{
    int data = Edit4_3->Text.ToInt();
	AddQueue(data);
	PrintQueue();
}
//---------------------------------------------------------------------------

// Delete Queue
void __fastcall TForm1::Button4_3Click(TObject *Sender)
{
	int result = DeleteQueue();
	if (result != -1)
	{
		PrintQueue();
		Form1->Label_delete_queue_result->Caption = result;
	}
	else
		Form1->Memo4->Lines->Add("Queue is EMPTY!");
}
//---------------------------------------------------------------------------

// FUNCTION DEFINITION
// create node
NODE * NewNode(int element)
{
	NODE * p;
	p = new NODE;
	p->data = element;
	p->next = NULL;
	return p;
}

// create head biank node
void NewHeadBlankNode(String str)
{
	// Singly linked list
	if (str == "list")
	{
		first = NewNode(0);
		first->next = first;
		last = first;
	}
	// Linked Stack
	else if (str == "stack")
	{
		top = NewNode(0);
		top->next = top;
	}
	// Linked Queue
	else if (str == "queue")
	{
		front = NewNode(0);
		front->next = front;
		rear = front;
	}
}

// create dnode
DNODE * NewDnode(int element)
{
	DNODE * p;
	p = new DNODE;
	p->data = element;
	p->prev = NULL;
	p->next = NULL;
	return p;
}

// create head biank dnode
void NewHeadBlankDnode()
{
	head = NewDnode(0);
	head->prev = head;
	head->next = head;
	tail = head;
}

// create 4 list
void Constructure()
{
	// Singly linked list
	NewHeadBlankNode("list");
	Form1->Memo1->Lines->Add("first -> last");
	// Doubly linked list
	NewHeadBlankDnode();
	Form1->Memo2->Lines->Add("head -> tail");
	// Linked Stack
	NewHeadBlankNode("stack");
	Form1->Memo3->Lines->Add("top -> next");
	// Linked Queue
	NewHeadBlankNode("queue");
	Form1->Memo4->Lines->Add("front -> rear");
}

// Singly Linked list
// insert after head biank node
void InsertFirst(int element)
{
	NODE * p;
	p = NewNode(element);
	p->next = first->next;
	first->next = p;
	if (last == first)
		last = p;
}

// insert element after node
void InsertAfter(NODE * x, int element)
{
	// create new node p
	// set p's data to element
	NODE * p;
	p = NewNode(element);
	// the next of p is the original next of x
	p->next = x->next;
	// change the next of x to p
	x->next = p;
	if (x == last)
		last = p;
}

// append list
void InsertLast(int element)
{
	// create new node p
	NODE * p;
	// set p's data to element
	p = NewNode(element);
	p->next = last->next;
	last->next = p;
	last = p;
}

// search the node with target
NODE * Search(int target)
{
	NODE * p;
	p = first->next;
	count = 1;
	while ((p != first) && (p->data != target))
	{
		p = p->next;
		count++;
	}
	// not found
	if (p == first)
		return NULL;
	// found
	return p;
}

// search the node before target
NODE * SearchBefore(int target)
{
	NODE * p, * q;
	for (q = first, p = first->next; (p != first && p->data != target); q = p, p = p->next);
	// not found
	if (p == first)
		return NULL;
	// found
	return q;
}

// delete the node after node x
int DeleteAfter(NODE * x)
{
	NODE * p;
	p = x->next;
	x->next = p->next;
	int item = p->data;
	if (p == last)
		last = x;
	delete [] p;
	return item;
}

// append random number
void RandomNumberInsertLast(int n, int range)
{
    srand(time(NULL));
	int data = 0;
	String line = "";
	for (int i = 0; i < n; i++)
	{
		data = rand() % range + 1;
		line += IntToStr(data) + "  ";
		InsertLast(data);
	}
	Form1->Memo1->Lines->Add("Random numbers: " + line);
}

// reverse the list
void ReverseList()
{
	NODE * Current, * Prev, * Next;
	Next = first->next;
	Current = last;
	last = Next;
	while (Next != first)
	{
		Prev = Current;
		Current = Next;
		Next = Next->next;
		Current->next = Prev;
	}
	first->next = Current;
	last->next = first;
}

// clear the list
void ClearList()
{
	NODE * p;
	for (p = first->next; p != first; p = first->next)
	{
		first->next = p->next;
		delete [] p;
	}
	last = first;
}

// print the list
void PrintList()
{
	String line = "";
	NODE * p;
	for (p = first->next; p != first; p = p->next)
		line += IntToStr(p->data) + " -> ";
	line += "<";
	// print on which tab
	Form1->PageControl2->TabIndex = 0;
	Form1->Memo1->Lines->Add(line);
}

// Doubly Linked list
// insert after head biank dnode
void InsertHead(int element)
{
	DNODE * p;
	p = NewDnode(element);
	p->next = head->next;
	head->next->prev = p;
	head->next = p;
	p->prev =head;
	if (tail == head)
		tail = p;
}

// insert element after dnode
void InsertAfterD(DNODE * x, int element)
{
	// create new node p
	// set p's data to element
	DNODE * p;
	p = NewDnode(element);
	// the next of p is the original next of x
	p->next = x->next;
	x->next->prev = p;
	// change the next of x to p
	x->next = p;
	p->prev = x;
	if (x == tail)
		tail = p;
}

// append dlist
void InsertTail(int element)
{
	// create new node p
	DNODE * p;
	// set p's data to element
	p = NewDnode(element);
	p->next = tail->next;
	tail->next->prev = p;
	tail->next = p;
	p->prev = tail;
	tail = p;
}

// search the dnode with target
DNODE * SearchD(int target)
{
	DNODE * p;
	p = head->next;
	Dcount = 1;
	while ((p != head) && (p->data != target))
	{
		p = p->next;
		Dcount++;
	}
	// not found
	if (p == head)
		return NULL;
	// found
	return p;
}

// delete the dnode
int DeleteD(DNODE * x)
{
	if (x == head)
	{
		Form1->Memo2->Lines->Add("Can't delete empty list!");
        return -1;
	}
	else
	{
		x->prev->next = x->next;
		x->next->prev = x->prev;
		int item = x->data;
		if (x == tail)
			tail = x->prev;
		delete [] x;
		return item;
	}

}

// append random number
void RandomNumberInsertTail(int n, int range)
{
	srand(time(NULL));
	int data = 0;
	String line = "";
	for (int i = 0; i < n; i++)
	{
		data = rand() % range + 1;
		line += IntToStr(data) + "  ";
		InsertTail(data);
	}
	Form1->Memo2->Lines->Add("Random numbers: " + line);
}

// reverse the dlist
void ReverseDList()
{
	DNODE * Current, * Prev, * Next;
	Next = head->next;
	Current = tail;
	tail = Next;
	while (Next != head)
	{
		Prev = Current;
		Current = Next;
		Next = Next->next;
		Current->next = Prev;
		Prev->prev = Current;
	}
	head->next = Current;
	Current->prev = head;
	tail->next = head;
    head->prev = tail;
}

// clear the dlist
void ClearDList()
{
	DNODE * p;
	for (p = head->next; p != head; p = head->next)
	{
		head->next = p->next;
		delete [] p;
	}
	tail = head;
}

// print the dlist
void PrintDList()
{
	String line = "";
	DNODE * p;
	for (p = head->next; p != head; p = p->next)
		line += IntToStr(p->data) + " -> ";
	line += "<";
	// print on which tab
	Form1->PageControl2->TabIndex = 1;
	Form1->Memo2->Lines->Add(line);
}

// Linked Stack
// push into linked stack
void push(int element)
{
	NODE * p = NewNode(element);
	p->next = top->next;
	top->next = p;
}

// pop from linked stack
int pop()
{
	NODE * p = top->next;
	if (p == top)
		return -1;
	int result = p->data;
	top->next = p->next;
	delete [] p;
	return result;
}

// push random number into linked stack
void RandomNumberPush(int n, int range)
{
	srand(time(NULL));
	int data = 0;
	String line = "";
	for (int i = 0; i < n; i++)
	{
		data = rand() % range + 1;
		line += IntToStr(data) + "  ";
		push(data);
	}
	Form1->Memo3->Lines->Add("Random numbers: " + line);
}

// print the linked stack
void PrintStack()
{
	String line = "";
	NODE * p;
	for (p = top->next; p != top; p = p->next)
		line += IntToStr(p->data) + " -> ";
	line += "<";
	// print on which tab
	Form1->PageControl2->TabIndex = 2;
	Form1->Memo3->Lines->Add(line);
}

// Linked Queue
// add into linked queue
void AddQueue(int element)
{
	NODE * p = NewNode(element);
	p->next = rear->next;
	rear->next = p;
	rear = p;
}

// delete from linked queue
int DeleteQueue()
{
	NODE * p = front->next;
	if (p == front)
		return -1;
	int result = p->data;
	front->next = p->next;
	delete [] p;
	return result;
}

// Add random number into linked queue
void RandomNumberAddQueue(int n, int range)
{
	srand(time(NULL));
	int data = 0;
	String line = "";
	for (int i = 0; i < n; i++)
	{
		data = rand() % range + 1;
		line += IntToStr(data) + "  ";
		AddQueue(data);
	}
	Form1->Memo4->Lines->Add("Random numbers: " + line);
}

// print the linked queue
void PrintQueue()
{
	String line = "";
	NODE * p;
	for (p = front->next; p != front; p = p->next)
		line += IntToStr(p->data) + " -> ";
	line += "<";
	// print on which tab
	Form1->PageControl2->TabIndex = 3;
	Form1->Memo4->Lines->Add(line);
}
