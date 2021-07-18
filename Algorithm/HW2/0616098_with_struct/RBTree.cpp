#include "RBTree.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

int main()
{
	int num_case = 0;
	RBTree tree;
    ifstream in_s;
    in_s.open("input.txt");
    ofstream out_s;
    out_s.open("output.txt");
    string str_case_num;
    getline(in_s, str_case_num);
    num_case = atoi(str_case_num.c_str());
	stringstream ss;
	while(num_case--)
    {
        cout <<"8";
        int op = 0;
        int key = 0;
		string str_op;
        getline(in_s, str_op);
        op = atoi(str_op.c_str());
        bool first = true;
        // Insert
        if(op == 1)
        {
            string Insert_str;
            getline(in_s, Insert_str);
            ss.clear();
            ss << Insert_str;
            cout << "Insert: ";
            out_s << "Insert: ";
            while(ss >> key)
            {
                tree.Insert(key);
                if(first)
					first = false;
				else
				{
					cout << ", ";
					out_s << ", ";
                }
                cout << key;
                out_s << key;
            }
        }
        // Delete
        else if(op == 2)
        {
            string Delete_str;
            getline(in_s, Delete_str);
            ss.clear();
            ss << Delete_str;
            cout << "Delete: ";
            out_s << "Delete: ";
            while(ss >> key)
            {
                tree.Delete(key);
				if(first)
					first = false;
				else
				{
					cout << ", ";
					out_s << ", ";
                }
                cout << key;
                out_s << key;
            }
        }
        cout << "\n";
        out_s << "\n";
        tree.print(out_s);
    }
    return 0;
}
RBTree::RBTree()
{
	nil = new Int_Node(0);
	nil -> color = Black;
	root = nil;
	root -> parent = nil;
}

const Int_Node* RBTree::getRoot() const
{
		return root;
}

const Int_Node* RBTree::getNil() const
{
		return nil;
}

void RBTree::print(ofstream& stream)
{
	if(getRoot() != nil)
        printnode(getRoot(), stream);
}

void RBTree::printnode(const Int_Node* node_ptr, ofstream& stream)
{
	if(node_ptr -> left_child != nil)
		printnode(node_ptr -> left_child, stream);
	cout << "key: " << node_ptr -> key << " parent: ";
	stream << "key: " << node_ptr -> key << " parent: ";
	if(node_ptr -> parent == nil)
    {
        cout << " ";
        stream << " ";
    }
	else
    {
        cout << node_ptr -> parent -> key;
        stream << node_ptr -> parent -> key;
    }
    cout << " color: ";
    stream << " color: ";
    if(node_ptr -> color)
    {
        cout << "black\n";
        stream << "black\n";
    }
    else
    {
        cout << "red\n";
        stream << "red\n";
    }
	if(node_ptr -> right_child != nil)
		printnode(node_ptr -> right_child, stream);
}

void RBTree::LeftRotate(Int_Node* x)
{
	Int_Node* y = x -> right_child;
	x -> right_child = y -> left_child;
	if (y -> left_child != nil)
		y -> left_child -> parent = x;
	y -> parent = x -> parent;
	if (x -> parent == nil)
		root = y;
	else if (x -> parent -> left_child == x)
		x -> parent -> left_child = y;
	else
		x -> parent -> right_child = y;
	y -> left_child = x;
	x -> parent = y;
}

void RBTree::RightRotate(Int_Node* x)
{
	Int_Node* y = x -> left_child;
	x -> left_child = y -> right_child;
	if (y -> right_child != nil)
		y -> right_child -> parent = x;
	y -> parent = x -> parent;
	if (x -> parent == nil)
		root = y;
	else if (x -> parent -> right_child == x)
		x -> parent -> right_child = y;
	else
		x -> parent -> left_child = y;
	y -> right_child = x;
	x -> parent = y;
}

void RBTree::Insert(const int& key)
{
	Int_Node* y = nil;
	Int_Node* x = root;
	Int_Node* z = new Int_Node(key);
	while (x != nil)
    {
		y = x;
		if (z -> key < x -> key)
			x = x -> left_child;
		else
			x = x -> right_child;
    }
	z -> parent = y;
	if (y == nil)
	{
		root = z;
		root -> color = Black;
	}
	else if (z -> key < y -> key)
		y -> left_child = z;
	else
		y -> right_child = z;
	z -> left_child = z -> right_child = nil;
	InsertFixUp(z);
}

void RBTree::InsertFixUp(Int_Node* node_ptr)
{
	while(node_ptr -> parent -> color == Red)
    {
		if(node_ptr -> parent == node_ptr -> parent -> parent -> left_child)
		{
			Int_Node* uncle = node_ptr -> parent -> parent -> right_child;
			if (uncle -> color == Red)
			{
				node_ptr -> parent -> color = uncle -> color = Black;
				node_ptr -> parent -> parent -> color = Red;
				node_ptr = node_ptr -> parent -> parent;
			}
			else
			{
				if(node_ptr == node_ptr -> parent -> right_child)
				{
					node_ptr = node_ptr -> parent;
					LeftRotate(node_ptr);
				}
				node_ptr -> parent -> color = Black;
				node_ptr -> parent -> parent -> color = Red;
				RightRotate(node_ptr -> parent -> parent);
			}
		}
		else
		{
			Int_Node* uncle = node_ptr -> parent -> parent -> left_child;
			if(uncle -> color == Red)
			{
				node_ptr -> parent -> color = uncle -> color = Black;
				node_ptr -> parent -> parent -> color = Red;
				node_ptr = node_ptr -> parent -> parent;
			}
			else
			{
				if (node_ptr == node_ptr -> parent -> left_child)
				{
					node_ptr = node_ptr -> parent;
					RightRotate(node_ptr);
				}
				node_ptr -> parent -> color = Black;
				node_ptr -> parent -> parent -> color = Red;
				LeftRotate(node_ptr -> parent -> parent);
			}
		}
	}
	root -> color = Black;
}

Int_Node* RBTree::Successor(Int_Node* node_ptr) const
{
	if(node_ptr -> right_child != nil)
    {
		node_ptr = node_ptr -> right_child;
		while(node_ptr -> left_child != nil)
			node_ptr = node_ptr -> left_child;
		return node_ptr;
	}
	Int_Node* successsor = node_ptr -> parent;
	while(successsor != nil && node_ptr == successsor -> right_child)
	{
		node_ptr = successsor;
		successsor = successsor -> parent;
	}
	return successsor;
}

void RBTree::Delete(const int& key)
{
	Int_Node* delete_node = root;
	while(delete_node -> key != key)
    {
		if(key < delete_node -> key)
			delete_node = delete_node -> left_child;
		else
			delete_node = delete_node -> right_child;
	}
	Int_Node *y = NULL, *x = NULL;
	if (delete_node -> left_child != nil && delete_node -> right_child != nil)
		y = Successor(delete_node);
	else
		y = delete_node;

	if (y -> left_child != nil)
		x = y -> left_child;
	else
		x = y -> right_child;
	x -> parent = y -> parent;
	if (y -> parent == nil)
		root = x;
	else if (y == y -> parent -> left_child)
		y -> parent -> left_child = x;
	else
		y -> parent -> right_child = x;

	if (y != delete_node)
		delete_node -> key = y -> key;

	if (y -> color == Black)
		DeleteFixUp(x);
	else
		nil -> parent = NULL;
}

void RBTree::DeleteFixUp(Int_Node* node_ptr)
{
	while(node_ptr != root && node_ptr -> color == Black)
    {
		if(node_ptr == node_ptr -> parent -> left_child)
		{
			Int_Node* sibling = node_ptr -> parent -> right_child;
			if (sibling -> color == Red)
			{
				node_ptr -> parent -> color = Red;
				sibling -> color = Black;
				LeftRotate(node_ptr -> parent);
				sibling = node_ptr -> parent -> right_child;
			}
			if((sibling -> left_child -> color == Black) && (sibling -> right_child -> color == Black))
			{
				sibling -> color = Red;
				node_ptr = node_ptr -> parent;
			}
			else
			{
				if(sibling -> right_child -> color == Black)
				{
					sibling -> color = Red;
					sibling -> left_child -> color = Black;
					RightRotate(sibling);
					sibling = node_ptr -> parent -> right_child;
				}
				sibling -> color = node_ptr -> parent -> color;
				node_ptr -> parent -> color = Black;
				sibling -> right_child -> color = Black;
				LeftRotate(node_ptr -> parent);
				node_ptr = root;
			}
		}
		else
		{
			Int_Node* sibling = node_ptr -> parent -> left_child;
			if (sibling -> color == Red)
            {
				node_ptr -> parent -> color = Red;
				sibling -> color = Black;
				RightRotate(node_ptr -> parent);
				sibling = node_ptr -> parent -> left_child;
			}
			if((sibling -> left_child -> color == Black) && (sibling -> right_child -> color == Black))
			{
				sibling -> color = Red;
				node_ptr = node_ptr -> parent;
			}
			else
			{
				if (sibling -> left_child -> color == Black)
				{
					sibling -> color = Red;
					sibling -> right_child -> color = Black;
					LeftRotate(sibling);
					sibling = node_ptr -> parent -> left_child;
				}
				sibling -> color = node_ptr -> parent -> color;
				node_ptr -> parent -> color = Black;
				sibling -> left_child -> color = Black;
				RightRotate(node_ptr -> parent);
				node_ptr = root;
			}
		}
	}
	node_ptr -> color = Black;
}
