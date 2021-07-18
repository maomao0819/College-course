#include "RBTree.h"
#include <iostream>
#include <sstream>
#include <fstream>

Int_Node::Int_Node(int key) : key(key), left(NULL), right(NULL), parent(NULL), color(Red) {}

RBTree::RBTree() {
	nil = new Int_Node(0);
	nil -> color = Black;
	root = nil;
	root -> parent = nil;
}
int main()
{
	int n, p, key;
	RBTree tree;
	cin >> n;
	string str;
	stringstream ss("");
	while(n--)
    {
		cin >> p;
		cin.ignore();
		getline(cin, str);
        ss.clear();
        ss.str("");
        ss << str;
        bool f = 1;
        if(p == 1)
        {

            cout << "Insert: ";
            while(ss >> key)
            {
                tree.Insert(key);
                if(f == 1)
                {
					cout << key;
					f = 0;
                }
				else
				{
					cout << ", " << key;
                }
            }
        }
        else
        {
            cout << "Delete: ";
            while(ss >> key)
            {
                tree.Delete(key);
				if(f == 1)
				{
					cout << key;
					f = 0;
                }
				else
				{
					cout << ", " << key;
                }
            }
        }
        cout << '\n';
        tree.print();
    }
}
void RBTree::print()
{
	if(getRoot() != nil)
        print1(getRoot());
}
void RBTree::print1(const Int_Node *ptr)
{
	if(ptr -> left != nil)
    {
		print1(ptr->left);
	}
	cout << "key: " << ptr -> key << " parent: ";
	if(ptr -> parent == nil)
        cout << ' ';
	else
        cout << ptr -> parent -> key;
    cout <<" color: ";
    if(ptr -> color)
        cout << "black\n";
    else
        cout << "red\n";
	if(ptr -> right != nil)
	{
		print1(ptr -> right);
	}

}
//inline Int_Node* InOrder(Int_Node* node){
//		if (node ==nil){
//			return nil;
//		}
//		while(ptr !=nil){
//			Int_Node* ptr = node->left;
//		}
//		while (ptr !=nil){
//			if (ptr->right !=nil){
//				ptr = ptr->right;
//			}
//			else{
//				break;
//			}
//		}
//		if (ptr ==nil){
//			Int_Node* index = node->parent;
//			ptr = node;
//			while (index !=nil && ptr == index->left){
//				ptr = index;
//				index = index->parent;
//			}
//			ptr = index;
//		}
//		return ptr;
//	}
void RBTree::Insert(const int& key)
{
	Int_Node* y = nil;
	Int_Node* x = root;
	Int_Node* z = new Int_Node(key);
	while (x != nil)
    {
		y = x;
		if (z -> key < x -> key)
			x = x->left;
		else
			x = x->right;
    }
	z -> parent = y;
	if (y == nil)
	{
		root = z;
		root -> color = Black;
	}
	else if (z -> key < y -> key)
		y -> left = z;
	else
		y -> right = z;
	z -> left = z -> right = nil;
	InsertFixUp(z);
}

void RBTree::InsertFixUp(Int_Node* ptr)
{
	while(ptr -> parent -> color == Red)
    {
		if(ptr -> parent == ptr -> parent -> parent -> left)
		{
			Int_Node* uncle = ptr -> parent -> parent -> right;
			if (uncle -> color == Red)
			{
				ptr -> parent -> color = uncle -> color = Black;
				ptr -> parent -> parent -> color = Red;
				ptr = ptr -> parent -> parent;
			}
			else
			{
				if(ptr == ptr -> parent -> right)
				{
					ptr = ptr -> parent;
					LeftRotate(ptr);
				}
				ptr -> parent -> color = Black;
				ptr -> parent -> parent -> color = Red;
				RightRotate(ptr -> parent -> parent);
			}
		}
		else
		{
			Int_Node* uncle = ptr -> parent -> parent -> left;
			if(uncle -> color == Red)
			{
				ptr -> parent -> color = uncle -> color = Black;
				ptr -> parent -> parent -> color = Red;
				ptr = ptr -> parent -> parent;
			}
			else
			{
				if (ptr == ptr -> parent -> left)
				{
					ptr = ptr -> parent;
					RightRotate(ptr);
				}
				ptr -> parent -> color = Black;
				ptr -> parent -> parent -> color = Red;
				LeftRotate(ptr -> parent -> parent);
			}
		}
	}
	root -> color = Black;
}

void RBTree::Delete(const int& key)
{
	Int_Node* delete_node = root;
	while(delete_node -> key != key) {
		if(key < delete_node -> key)
			delete_node = delete_node -> left;
		else
			delete_node = delete_node -> right;
	}
	Int_Node *y = NULL, *x = NULL;
	if (delete_node -> left != nil && delete_node -> right != nil)
		y = Successor(delete_node);
	else
		y = delete_node;

	if (y -> left != nil)
		x = y -> left;
	else
		x = y -> right;

	x -> parent = y -> parent;
	if (y -> parent == nil)
		root = x;
	else if (y == y -> parent -> left)
		y -> parent -> left = x;
	else
		y -> parent -> right = x;

	if (y != delete_node)
		delete_node -> key = y -> key;

	if (y -> color == Black)
		DeleteFixUp(x);
	else
		nil -> parent = NULL;
}

void RBTree::DeleteFixUp(Int_Node* ptr) {
	while(ptr != root && ptr->color == Black)
    {
		if(ptr == ptr->parent->left)
		{
			Int_Node* sibling = ptr -> parent -> right;
			if (sibling -> color == Red)
			{
				ptr -> parent -> color = Red;
				sibling -> color = Black;
				LeftRotate(ptr -> parent);
				sibling = ptr -> parent -> right;
			}
			if (sibling -> left -> color == Black && sibling -> right -> color == Black)
			{
				sibling -> color = Red;
				ptr = ptr -> parent;
			}
			else
			{
				if(sibling -> right -> color == Black)
				{
					sibling -> color = Red;
					sibling -> left -> color = Black;
					RightRotate(sibling);
					sibling = ptr -> parent -> right;
				}
				sibling -> color = ptr -> parent -> color;
				ptr -> parent -> color = Black;
				sibling -> right -> color = Black;
				LeftRotate(ptr -> parent);
				ptr = root;
			}
		}
		else
		{
			Int_Node* sibling = ptr -> parent -> left;
			if (sibling -> color == Red) {
				ptr -> parent -> color = Red;
				sibling -> color = Black;
				RightRotate(ptr -> parent);
				sibling = ptr -> parent -> left;
			}
			if (sibling -> left -> color == Black && sibling -> right -> color == Black)
			{
				sibling -> color = Red;
				ptr = ptr -> parent;
			}
			else
			{
				if (sibling -> left -> color == Black)
				{
					sibling -> color = Red;
					sibling -> right -> color = Black;
					LeftRotate(sibling);
					sibling = ptr -> parent -> left;
				}
				sibling -> color = ptr -> parent -> color;
				ptr -> parent -> color = Black;
				sibling -> left -> color = Black;
				RightRotate(ptr -> parent);
				ptr = root;
			}
		}
	}
	ptr -> color = Black;
}

void RBTree::LeftRotate(Int_Node* x)
{
	Int_Node* y = x -> right;
	x -> right = y -> left;
	if (y -> left != nil)
		y -> left -> parent = x;
	y -> parent = x -> parent;
	if (x -> parent == nil)
		root = y;
	else if (x -> parent -> left == x)
		x -> parent -> left = y;
	else
		x -> parent -> right = y;
	y -> left = x;
	x -> parent = y;
}

void RBTree::RightRotate(Int_Node* x)
{
	Int_Node* y = x -> left;
	x -> left = y -> right;
	if (y -> right != nil)
		y -> right -> parent = x;
	y -> parent = x -> parent;
	if (x -> parent == nil)
		root = y;
	else if (x -> parent -> right == x)
		x -> parent -> right = y;
	else
		x -> parent -> left = y;
	y -> right = x;
	x -> parent = y;
}

Int_Node* RBTree::Successor(Int_Node* ptr) const
{
	if(ptr->right != nil)
    {
		ptr = ptr -> right;
		while (ptr -> left != nil)
			ptr = ptr -> left;
		return ptr;
	}
	Int_Node* successsor = ptr -> parent;
	while(successsor != nil && ptr == successsor -> right)
	{
		ptr = successsor;
		successsor = successsor -> parent;
	}
	return successsor;
}
