//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW6_BSTree.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// DECLAIR NEW DATA STRUCTURE
// BSTree node with int data
typedef struct BSTreeNode
{
  struct BSTreeNode * leftchild;
  int data;
  struct BSTreeNode * rightchild;
} BST_NODE;
// BSTree node with char data
typedef struct BSTreeCNode
{
  struct BSTreeCNode * leftchild;
  char * data;
  struct BSTreeCNode * rightchild;
} BST_CNODE;
// Stack node for non-recursive traversal
typedef struct StackNode
{
  BST_NODE *treenode;
  struct StackNode * next;
} STACK_NODE;
// Queue node for LevelOrder
typedef struct QueueNode
{
  BST_NODE * treenode;
  struct QueueNode * next;
} QUEUE_NODE;
// Tree node for drawing
typedef struct DrawTreeNode
{
  struct DrawTreeNode * leftchild;
  int data;
  int index;
  struct DrawTreeNode * rightchild;
} DRAW_TREE_NODE;

// GLOBAL VARIABLE
// BSTree node with int data
BST_NODE *root;
// BSTree node with char data
BST_CNODE *Croot;
// Stack node
STACK_NODE *top;
// Queue node
QUEUE_NODE *front, *rear;
// Output string
String tree_nums = "";
// the number of nodes
int n_node = 0;

DRAW_TREE_NODE* DrawRoot;
int* X;
int* Y;
//int** treenode;
int tempcount;

// PROTOTYPE DECLARATION
// create and initialize a BSTree node
BST_NODE * NewBSTNode(int x);
// search recursicely
BST_NODE * SearchBST(BST_NODE * tree, int x);
// search with loop
BST_NODE * Search_BST_iterative(BST_NODE * node, int x);
// insert into BSTree recursicely
BST_NODE * InsertBSTree_recursive(BST_NODE * node, int x);
// insert into with loop
int InsertBST(int x);
// insert n random number into BSTree
String InsertRandomNumber(int n, int range_min, int range_max);
// find inorder successor for DeleteBSTree_recursive
BST_NODE * InorderSucc(BST_NODE * node);
// delete from BSTree recursicely
BST_NODE * DeleteBSTree_recursive(BST_NODE * node, int x);
// delete from BSTree with loop and if-else
int DeleteBSTree(int x);
int DeleteBSTree_another(int x);
// print BSTree recursicely
void print_BSTree_inorder(BST_NODE * node);
void print_BSTree_preorder(BST_NODE * node);
void print_BSTree_postorder(BST_NODE * node);
void PrintBST_recursive();
// stack
void push_node(BST_NODE *node);
BST_NODE * pop_node();
// queue
void AddQueue(BST_NODE *Tnode);
BST_NODE * DeleteQueue();
// print BSTree with stack and loop
void Inorder_Stack(BST_NODE * node);
void Postorder_Stack(BST_NODE * node);
void Preorder_Stack(BST_NODE * node);
// print BSTree with queue and loop
void LevelOrder(BST_NODE *node);
// print BSTree non-recursicely
void PrintBST_nonrecursive();
// clear BSTree recursively
void Clear_BST(BST_NODE* BSTnode);

void Clear_DBST(DRAW_TREE_NODE* DBSTnode);
int Depth_BTree(BST_NODE* node, int level);
void determine_X(DRAW_TREE_NODE* node, int left, int right);
void determine_Y(DRAW_TREE_NODE* node, int top, int bottom, int depth);
DRAW_TREE_NODE* CopyBSTtoDT(BST_NODE* TreeRoot, int index, int depth);
void Draw_BST(DRAW_TREE_NODE* DrawRoot, int node_radius);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

// print BSTree
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if (root != NULL)
	{
		// print BSTree
		PrintBST_recursive();
		PrintBST_nonrecursive();
		Form1->Memo1->Lines->Add("There are " + IntToStr(n_node)+ " nodes in the BSTree.");
	}
	else
		Form1->Memo1->Lines->Add("The BSTree doesn't exist yet.");
	Form1->Memo1->Lines->Add("");
}
//---------------------------------------------------------------------------

// Insert into BST (recursive)
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int data = Edit1->Text.ToInt();
	n_node++;
	root = InsertBSTree_recursive(root, data);
	Form1->Memo1->Lines->Add("Insert " + IntToStr(data));
	// print BSTree
	PrintBST_recursive();
	PrintBST_nonrecursive();
	Form1->Memo1->Lines->Add("There are " + IntToStr(n_node)+ " nodes in the BSTree.");
	Form1->Memo1->Lines->Add("");
}
//---------------------------------------------------------------------------

// Insert into BST (non-recursive)
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	int data = Edit1->Text.ToInt();
	n_node++;
	int success_code = InsertBST(data);
	if (!success_code)
		Form1->Memo1->Lines->Add("Fail to insert:" + IntToStr(data));
	else
	{
		Form1->Memo1->Lines->Add("Insert " + IntToStr(data));
		// print BSTree
		PrintBST_recursive();
		PrintBST_nonrecursive();
		Form1->Memo1->Lines->Add("There are " + IntToStr(n_node)+ " nodes in the BSTree.");
		Form1->Memo1->Lines->Add("");
	}
}
//---------------------------------------------------------------------------

// Delete from BST (recursive)
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	int target = Edit2->Text.ToInt();
	root = DeleteBSTree_recursive(root, target);
	if (root != NULL)
	{
		// print BSTree
		PrintBST_recursive();
		PrintBST_nonrecursive();
		Form1->Memo1->Lines->Add("There are " + IntToStr(n_node)+ " nodes in the BSTree.");
	}
	else
		Form1->Memo1->Lines->Add("The BSTree doesn't exist yet.");
	Form1->Memo1->Lines->Add("");
}
//---------------------------------------------------------------------------

// Delete from BST (non-recursive)
void __fastcall TForm1::Button5Click(TObject *Sender)
{
    int target = Edit2->Text.ToInt();
	int success = DeleteBSTree(target);
	if (root != NULL)
	{
		if (success)
		{
			Memo1->Lines->Add(IntToStr(target) + " has been deleted.");
			n_node--;
		}
		else
			Memo1->Lines->Add(IntToStr(target) + " has not been found.");
		// print BSTree
		PrintBST_recursive();
		PrintBST_nonrecursive();
		Form1->Memo1->Lines->Add("There are " + IntToStr(n_node)+ " nodes in the BSTree.");
	}
	else
		Form1->Memo1->Lines->Add("The BSTree doesn't exist yet.");
	Form1->Memo1->Lines->Add("");
}
//---------------------------------------------------------------------------

// Insert Random Integers
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	int n = Edit3->Text.ToInt();
	int range_min = Edit4->Text.ToInt();
	int range_max = Edit5->Text.ToInt();
	String nums = InsertRandomNumber(n, range_min, range_max);
	n_node += n;
	// print BSTree
	PrintBST_recursive();
	PrintBST_nonrecursive();
	Form1->Memo1->Lines->Add("There are " + IntToStr(n_node)+ " nodes in the BSTree.");
	Form1->Memo1->Lines->Add("");
}
//---------------------------------------------------------------------------

// Clear BST
void __fastcall TForm1::Button7Click(TObject *Sender)
{
    if (root != NULL)
	{
		Clear_BST(root);
		n_node = 0;
        root = NULL;
	    Form1->Memo1->Lines->Add("The BSTree has been cleared.");
		Clear_DBST(DrawRoot);
	}
	else
		Form1->Memo1->Lines->Add("The BSTree doesn't exist yet.");
	Form1->Memo1->Lines->Add("");
}
//---------------------------------------------------------------------------

// FUNCTION DEFINITION
// create and initialize a BSTree node
BST_NODE * NewBSTNode(int x)
{
	BST_NODE * node = new BST_NODE;
	node->data = x;
	node->leftchild = NULL;
	node->rightchild = NULL;
	return node;
}

// search recursicely
BST_NODE * SearchBST(BST_NODE * tree, int x)
{
	if (tree == NULL)
		return NULL;
	if (x == tree->data)
		return tree;
	if (x < tree->data)
		return SearchBST(tree->leftchild, x);
	return SearchBST(tree->rightchild, x);
}

// search with loop
BST_NODE * Search_BST_iterative(BST_NODE * node, int x)
{
	while (node != NULL)
	{
		if (x == node->data)
			return node;
		if (x < node->data)
			node = node->leftchild;
		else
			node = node->rightchild;
	}
	return NULL;
}

// insert into BSTree recursicely
BST_NODE * InsertBSTree_recursive(BST_NODE * node, int x)
{
	if (node == NULL)
		return NewBSTNode(x);
 	if (x < node->data)
		node->leftchild = InsertBSTree_recursive(node->leftchild, x);
	else
		node->rightchild = InsertBSTree_recursive(node->rightchild, x);
	return node;
}

// insert into with loop
int InsertBST(int x)
{
	BST_NODE *p, *q;
    p = root;
    q = NULL;
    while (p != NULL)
    {
		q = p;
		// comment since repeat isn't a problem
		// if (x == p->data)
		//     // means fail
		//     return 0;
		if (x < p->data)
            p = p->leftchild;
        else
            p = p->rightchild;
    }
	// p = (BST_NODE *) malloc (sizeof(BSTreeNode));
	p = new BST_NODE;
    p->data = x;
    p->leftchild = p->rightchild = NULL;
	if (root == NULL)
		root = p;
	else if (x < q->data)
		q->leftchild = p;
    else
		q->rightchild = p;
	// means success
    return 1;
}

// insert n random number into BSTree
String InsertRandomNumber(int n, int range_min, int range_max)
{
	srand(time(NULL));
	int data = 0;
	int range = range_max - range_min + 1;
	String nums = "";
	for (int i = 0; i < n; i++)
	{
		data = rand() % range + range_min;
		int success_code = InsertBST(data);
		nums += IntToStr(data) + " ";
	}
	Form1->Memo1->Lines->Add("Insert random number: " + nums);
	return nums;
}

// find inorder successor for DeleteBSTree_recursive
BST_NODE * InorderSucc(BST_NODE * node)
{
	BST_NODE * p = node;
	// for (p = node; p->leftchild != NULL; p = p->leftchild)
	while (p->leftchild != NULL)
		p = p->leftchild;
	return p;
}

// delete from BSTree recursicely
BST_NODE * DeleteBSTree_recursive(BST_NODE * node, int x)
{
	BST_NODE * temp;
	if (node == NULL)
	{
		Form1->Memo1->Lines->Add(IntToStr(x) + " has not been found.");
		return node;
	}
	if (x < node->data)
		node->leftchild = DeleteBSTree_recursive(node->leftchild, x);
	else if (x > node->data)
		node->rightchild = DeleteBSTree_recursive(node->rightchild, x);
	// x found in node
	else
	{
		if ((node->leftchild == NULL) || (node->rightchild == NULL))
		{
			temp = node->leftchild ? node->leftchild : node->rightchild;
			// node itself is a leaf
			if (temp == NULL)
			{
				temp = node;
 				node = NULL;
			}
			// Copy the contents of the only/non-empty child
 			else
				* node = * temp;
			n_node--;
			Form1->Memo1->Lines->Add(IntToStr(x) + " has been deleted.");
 			free(temp);
		}
		// node has two children
		else
		{
 			temp = InorderSucc(node->rightchild);
 			node->data = temp->data;
 			node->rightchild = DeleteBSTree_recursive(node->rightchild, temp->data);
 		}
 	}
 	return node;
}

// delete from BSTree with loop and if-else
int DeleteBSTree(int x)
{
	BST_NODE *p , *parent, *k, *f;
	p = root;
	parent = NULL;
	while (p != NULL)
	{
		// found x at node p
		if (x == p->data)
		{
			// p is leaf
			if ((p->leftchild == NULL) && (p->rightchild == NULL))
				k = NULL;
			// p has left sub-tree
			else if (p->leftchild != NULL )
            {
				// find the rightest leaf of p's left sub-tree
				f = p;
                k = p->leftchild;
                while (k->rightchild !=NULL)
				{
					f = k;
					k = k->rightchild;
				}
				// k is the rightest leaf of p's left sub-tree
				if (p == f)
					// k is p's left child
                    f->leftchild = k->leftchild;
				else
                    f->rightchild = k->leftchild;
			}
			// p doesn't have left sub-tree, check right sub-tree
			else
            {
				// find the leftest leaf of p's right sub-tree
				f = p;
                k = p->rightchild;
                while (k->leftchild != NULL)
                {
					f = k;
                    k = k ->leftchild;
				}
				// k is the leftest leaf of p's right sub-tree
				if (p == f)
					// k is p's right child
                    f->rightchild = k->rightchild;
                else
                    f->leftchild = k->rightchild;
			}
			// move k to the oroginal position of p, and inherit p's left and right pointer
			if (k != NULL)
            {
                k->leftchild = p->leftchild;
                k->rightchild = p->rightchild;
            }
            if (parent == NULL)
                root = k;
			else
            {
				// decide k is parent's left child or right child
				if (x < parent->data)
                    parent->leftchild = k;
                else
                    parent->rightchild = k;
			}
			free(p);
			// delete x successfully
			return 1;
		}
		// x hasn't been found yet, keep finding at next level
		else
        {
            parent = p;
            if (x < p->data)
                p = p->leftchild;
			else
                p = p->rightchild;
        }
    }
	// x hasn't been found
    return 0;
}

int DeleteBSTree_another(int x)
{
	BST_NODE *p, *parent, *k, *f;
	p = root;
 	parent = NULL;
	while (p != NULL)
	{
		// found x at node p
		if (x == p->data)
		{
			// p is leaf
			if ((p->leftchild == NULL) && (p->rightchild == NULL))
 			{
				if (p == root)
 					root = NULL;
				else if (parent->leftchild == p)
					parent->leftchild = NULL;
				else
					parent->rightchild = NULL;
	 			free(p);
	 		}
	 		else
	 		{
				// p has left sub-tree
				if (p->leftchild != NULL )
	 			{
					// find the rightest leaf of p's left sub-tree
					f = p;
	 				k = p->leftchild;
	 				while (k->rightchild !=NULL)
	 				{
	 					f = k;
						k = k->rightchild;
					}
					// k is the rightest leaf of p's left sub-tree
					if (p == f)
						// k is p's left child
	 					f->leftchild = k->leftchild;
	 				else
	 					f->rightchild = k->leftchild;
				}
				// p doesn't have left sub-tree, check right sub-tree
				else
	 			{
					// find the leftest leaf of p's right sub-tree
					f = p;
	 				k = p->rightchild;
	 				while (k->leftchild != NULL)
	 				{
	 					f = k;
	 					k = k ->leftchild;
					}
					// k is the leftest leaf of p's right sub-tree
					if (p == f)
						// k is p's right child
	 					f->rightchild = k->rightchild;
	 				else
	 					f->leftchild = k->rightchild;
	 			}
	 			p->data = k->data;
	 			free(k);
			}
			// delete x successfully
			return 1;
		}
		// x hasn't been found yet, keep finding at next level
		else
	 	{
	 		parent = p;
	 		if (x < p->data)
	 			p = p->leftchild;
	 		else
	 			p = p->rightchild;
		}
	}
	//x hasn't been found
	return 0;
}

// print BSTree recursicely
void print_BSTree_inorder(BST_NODE * node)
{
	if (node != NULL)
	{
		print_BSTree_inorder(node->leftchild);
		tree_nums += IntToStr(node->data) + "_";
		print_BSTree_inorder(node->rightchild);
	}
}

void print_BSTree_preorder(BST_NODE * node)
{
	if (node != NULL)
	{
		tree_nums += IntToStr(node->data) + "_";
		print_BSTree_preorder(node->leftchild);
		print_BSTree_preorder(node->rightchild);
	}
}

void print_BSTree_postorder(BST_NODE * node)
{
	if (node != NULL)
	{
		print_BSTree_postorder(node->leftchild);
		print_BSTree_postorder(node->rightchild);
		tree_nums += IntToStr(node->data) + "_";
	}
}

void PrintBST_recursive()
{
	tree_nums = "";
	if (Form1->CheckBox1->Checked)
	{
        tree_nums = "";
		print_BSTree_inorder(root);
		Form1->Memo1->Lines->Add("In-order (recursively):\t" + tree_nums);
	}
	if (Form1->CheckBox2->Checked)
	{
		tree_nums = "";
		print_BSTree_preorder(root);
		Form1->Memo1->Lines->Add("Pre-order (recursively):\t" + tree_nums);
	}
	if (Form1->CheckBox3->Checked)
	{
		tree_nums = "";
		print_BSTree_postorder(root);
		Form1->Memo1->Lines->Add("Post-order (recursively):\t" + tree_nums);
	}
}

// stack
void push_node(BST_NODE *node)
{
	STACK_NODE *old_top;
	old_top = top;
	// top = (STACK_NODE *) malloc (sizeof(STACK_NODE));
	top = new STACK_NODE;
	top->treenode = node;
	top->next = old_top;
}

BST_NODE *pop_node()
{
	BST_NODE *TreeNode;
	STACK_NODE *old_top;
	if (top == NULL)
		Form1->Memo1->Lines->Add("Stack is EMPTY!");
	else
	{
		TreeNode = top->treenode;
        old_top = top;
		top = top->next;
        free(old_top);
		return TreeNode;
    }
}

// queue
void AddQueue(BST_NODE *TreeNode)
{
	QUEUE_NODE *Qnode;
	// node = (QUEUE_NODE *) malloc (sizeof(QUEUE_NODE));
	Qnode = new QUEUE_NODE;
	Qnode->treenode = TreeNode;
	Qnode->next = NULL;
    if (front == NULL)
		front = Qnode;
    else
		rear->next = Qnode;
	rear = Qnode;
}

BST_NODE *DeleteQueue()
{
	BST_NODE *TreeNode;
	QUEUE_NODE *old_front;
	if (front == NULL)
		Form1->Memo1->Lines->Add("Queue is EMPTY!");
	else
	{
		TreeNode = front->treenode;
		old_front = front;
		front = front->next;
        free(old_front);
		return TreeNode;
	}
}

// print BSTree with stack and loop
void Inorder_Stack(BST_NODE * node)
{
    do
	{
		// push all left children
        while (node != NULL)
        {
            push_node(node);
            node = node->leftchild;
		}
		// inorder printing and check right child
        if (top != NULL)
        {
            node = pop_node();
			tree_nums += IntToStr(node->data) + "_";
            node = node->rightchild;
		}
	} while ((top != NULL) || (node != NULL));
	// top == NULL: stack is empty
	// node == NULL: no right child
}

void Preorder_Stack(BST_NODE * node)
{
	do
	{
		// push all left children and preorder printing
		while (node != NULL)
		{
			tree_nums += IntToStr(node->data) + "_";
			push_node(node);
            node = node->leftchild;
		}
		// check right child
		if (top != NULL)
        {
			node = pop_node();
			node = node->rightchild;
		}
	} while ((top != NULL) || (node != NULL));
    // top == NULL: stack is empty
	// node == NULL: no right child
}

void Postorder_Stack(BST_NODE * node)
{
    do
    {
		// push all right children and postorder printing
		while (node != NULL)
        {
			tree_nums = IntToStr(node->data) + "_" + tree_nums;
			push_node(node);
            node = node->rightchild;
		}
		// check left child
        if (top != NULL)
        {
            node = pop_node();
            node = node->leftchild;
        }
	} while ((top != NULL) || (node != NULL));
    // top == NULL: stack is empty
	// node == NULL: no right child
}

// print BSTree with queue and loop
void LevelOrder(BST_NODE *node)
{
	AddQueue(node);
	while (front != NULL)
	{
		node = DeleteQueue();
		tree_nums += IntToStr(node->data) + "_";
		if (node->leftchild != NULL)
			AddQueue(node->leftchild);
		if (node->rightchild != NULL)
			AddQueue(node->rightchild);
	}
}

// print BSTree non-recursicely
void PrintBST_nonrecursive()
{
	if (Form1->CheckBox4->Checked)
	{
		tree_nums = "";
		Inorder_Stack(root);
		Form1->Memo1->Lines->Add("In-order (stack and loop):\t" + tree_nums);
	}
	if (Form1->CheckBox5->Checked)
	{
		tree_nums = "";
		Preorder_Stack(root);
		Form1->Memo1->Lines->Add("Pre-order (stack and loop):\t" + tree_nums);
	}
	if (Form1->CheckBox6->Checked)
	{
		tree_nums = "";
		Postorder_Stack(root);
		Form1->Memo1->Lines->Add("Post-order (stack and loop):\t" + tree_nums);
	}
	if (Form1->CheckBox7->Checked)
	{
		tree_nums = "";
		LevelOrder(root);
		Form1->Memo1->Lines->Add("Level-order (queue and loop):\t" + tree_nums);
	}
}

/*
int Depth_BTree(BST_NODE* node, int level, int site)
{
    int depth, l_depth, r_depth;
    if (node!=NULL)
    {
        treenode[tempcount][0] = node->data;
        treenode[tempcount][1] = level;
        treenode[tempcount][2] = site;
        tempcount++;
        l_depth = Depth_BTree(node->leftchild, (level + 1), site * 2);
        r_depth = Depth_BTree(node->rightchild, (level + 1), site * 2 + 1);
        depth = l_depth > r_depth ? l_depth : r_depth;
        return depth;
    }
    else
        return (level - 1);
}
*/

int Depth_BTree(BST_NODE* node, int level)
{
    int depth, l_depth, r_depth;
	if (node != NULL)
    {
        //treenode[tempcount][0] = node->data;
        //treenode[tempcount][3] = site;
        //tempcount++;
		l_depth = Depth_BTree(node->leftchild, (level + 1));
		r_depth = Depth_BTree(node->rightchild, (level + 1));
        depth = l_depth > r_depth ? l_depth : r_depth;
        return depth;
        }
    else
		return (level - 1);
}

/*
int** Find_Coordinate(int** data, int data_count, int total_node)
{
    BST_NODE *p;
    int m, L, R, x, level;
    for (int i = 0; i < data_count; i++)
    {
        p = root;
        L = 1;
        R = total_node;
        x = data[i][0];
        level = 1;
        do
        {
            m = (L + R) / 2;
            if (x == p->data)
                break;
            else if (x < p->data)
            {
                R = m - 1;
                p = p->leftchild;
            }
            else
            {
                L = m + 1;
                p = p->rightchild;
            }
            level += 1;
        } while(p->data != NULL);
        data[i][1] = m;
        data[i][2] = level;
    }
    return data;
}
*/

void determine_X(DRAW_TREE_NODE* node, int left, int right)
{
    if (node != NULL)
    {
        int m = (left+right)/2;
        X[node->index] = (m == 0) ? left : m;
        determine_X(node->leftchild, left, (m - 1 < left) ? left : m - 1);
        determine_X(node->rightchild, (m + 1 < right) ? m + 1 : right, right);
    }
}

void determine_Y(DRAW_TREE_NODE* node, int top, int bottom, int depth)
{
    int detH = (top + bottom) / (depth + 1);
    for (int i = 0; i < depth + 1; i++)
        Y[i] = (detH < 10) ? 10 * i : detH * i;
}

DRAW_TREE_NODE* CopyBSTtoDT(BST_NODE* TreeRoot, int index, int depth)
{
    if (TreeRoot==NULL)
        return NULL;
	// DRAW_TREE_NODE* copyRoot = (DRAW_TREE_NODE*)malloc(sizeof(DrawTreeNode));
	DRAW_TREE_NODE* copyRoot = new DRAW_TREE_NODE;
    copyRoot->data = TreeRoot->data;
    copyRoot->index = index;
    // copyRoot->y = ceil(log(index + 1) / log(2.0));
    // copyRoot->x = pow(2, (depth - copyRoot->y)) + pow(2, (depth - copyRoot->y) + 1)
    // *     (index - (pow(2, copyRoot->y - 1) - 1) - 1);
    copyRoot->leftchild = CopyBSTtoDT(TreeRoot->leftchild, 2 * index, depth);
    copyRoot->rightchild = CopyBSTtoDT(TreeRoot->rightchild, 2 * index + 1, depth);
    return copyRoot;
}

// void Draw_BST(DRAW_TREE_NODE* DrawRoot, int detW, int detH, int node_radius)
//void Draw_BST(DRAW_TREE_NODE* DrawRoot, int node_radius)
//{
//	if (DrawRoot!=NULL)
//	{
//        int level = ceil(log(DrawRoot->index+1)/log(2.0));
//        if (DrawRoot->leftchild!=NULL)
//        {
//			Form1->Image1->Canvas->MoveTo(X[DrawRoot->index], Y[level]);
//			Form1->Image1->Canvas->LineTo(X[DrawRoot->leftchild->index], Y[level + 1]);
//            //Form1->Image1->Canvas->MoveTo((DrawRoot->x) * detW, (DrawRoot->y) * detH);
//            //Form1->Image1->Canvas->LineTo((DrawRoot->leftchild->x) * detW, (DrawRoot->leftchild->y) * detH);
//
//        }
//        if (DrawRoot->rightchild)
//        {
//            Form1->Image1->Canvas->MoveTo(X[DrawRoot->index], Y[level]);\
//			Form1->Image1->Canvas->LineTo(X[DrawRoot->rightchild->index], Y[level + 1]);
//            //Form1->Image1->Canvas->MoveTo((DrawRoot->x) * detW, (DrawRoot->y) * detH);
//            //Form1->Image1->Canvas->LineTo((DrawRoot->rightchild->x) * detW, (DrawRoot->rightchild->y) * detH);
//        }
//        Form1->Image1->Canvas->Ellipse(X[DrawRoot->index] - node_radius,
//        Y[level] - node_radius,
//		X[DrawRoot->index] + node_radius,
//        Y[level] + node_radius);
//        Form1->Image1->Canvas->TextOutA(X[DrawRoot->index] - 5, Y[level] - 7, IntToStr(DrawRoot->data));
//        //Form1->Image1->Canvas->Ellipse((X[DrawRoot->index]- node_radius,
//        //                 ((DrawRoot->y) * detH) - node_radius,
//        //                 ((DrawRoot->x) * detW) + node_radius,
//        //                 ((DrawRoot->y) * detH) + node_radius);
//        //Form1->Image1->Canvas->TextOutA((DrawRoot->x) * detW - 5, (DrawRoot->y) * detH - 8, IntToStr(DrawRoot->data));
//        // Draw_BST(DrawRoot->leftchild, detW, detH, node_radius);
//        // Draw_BST(DrawRoot->rightchild, detW, detH, node_radius);
//        Draw_BST(DrawRoot->leftchild, node_radius);
//        Draw_BST(DrawRoot->rightchild, node_radius);
//	}
//}

// clear BSTree recursively
void Clear_BST(BST_NODE * BSTnode)
{
	if (BSTnode != NULL)
	{
		Clear_BST(BSTnode->leftchild);
		Clear_BST(BSTnode->rightchild);
		delete(BSTnode);
	}
}

void Clear_DBST(DRAW_TREE_NODE * DBSTnode)
{
    if (DBSTnode != NULL)
    {
        Clear_DBST(DBSTnode->leftchild);
        Clear_DBST(DBSTnode->rightchild);
        delete(DBSTnode);
    }
}
