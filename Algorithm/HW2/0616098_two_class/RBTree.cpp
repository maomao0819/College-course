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

TreeNode::TreeNode() : left_child(NULL), right_child(NULL), parent(NULL), key(0), color(Red){}
TreeNode::TreeNode(int key) : left_child(NULL), right_child(NULL), parent(NULL), key(key), color(Red){};

RBTree::RBTree()
{
	NIL = new TreeNode;     // NIL need memory reallocation
	NIL -> color = Black;
	root = NIL;             // for insert, root initialize to NIL
	root -> parent = NIL;
}

const TreeNode* RBTree::getRoot() const
{
		return root;
}

const TreeNode* RBTree::getNil() const
{
		return NIL;
}

void RBTree::print(ofstream& stream)
{
	if(getRoot() != NIL)
        print_node(getRoot(), stream);
}

void RBTree::print_node(const TreeNode* node_ptr, ofstream& out_stream)
{
	if(node_ptr -> left_child != NIL)
		print_node(node_ptr -> left_child, out_stream);
	cout << "key: " << node_ptr -> key << " parent: ";
	out_stream << "key: " << node_ptr -> key << " parent: ";
	if(node_ptr -> parent == NIL)
    {
        cout << " ";
        out_stream << " ";
    }
	else
    {
        cout << node_ptr -> parent -> key;
        out_stream << node_ptr -> parent -> key;
    }
    cout << " color: ";
    out_stream << " color: ";
    if(node_ptr -> color)
    {
        cout << "black\n";
        out_stream << "black\n";
    }
    else
    {
        cout << "red\n";
        out_stream << "red\n";
    }
	if(node_ptr -> right_child != NIL)
		print_node(node_ptr -> right_child, out_stream);
}

void RBTree::LeftRotate(TreeNode* x)
{
	TreeNode* y = x -> right_child;
	x -> right_child = y -> left_child;
	if (y -> left_child != NIL)
		y -> left_child -> parent = x;
	y -> parent = x -> parent;
	if (x -> parent == NIL)
		root = y;
	else if (x -> parent -> left_child == x)
		x -> parent -> left_child = y;
	else
		x -> parent -> right_child = y;
	y -> left_child = x;
	x -> parent = y;
}

void RBTree::RightRotate(TreeNode* x)
{
	TreeNode* y = x -> left_child;
	x -> left_child = y -> right_child;
	if (y -> right_child != NIL)
		y -> right_child -> parent = x;
	y -> parent = x -> parent;
	if (x -> parent == NIL)
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
	TreeNode* x = root;
	TreeNode* y = NIL;
	TreeNode* z = new TreeNode(key);
	while (x != NIL)
    {
		y = x;
		if (z -> key < x -> key)
			x = x -> left_child;
		else
			x = x -> right_child;
    }
	z -> parent = y;
	if (y == NIL)
	{
		root = z;
		root -> color = Black;
	}
	else if (z -> key < y -> key)
		y -> left_child = z;
	else
		y -> right_child = z;
    // initialize z
	z -> left_child = z -> right_child = NIL;
	z -> color = Red;
	InsertFixUp(z);     // fix the red-red node
}

void RBTree::InsertFixUp(TreeNode* node_ptr)
{
    // case0:
	while(node_ptr -> parent -> color == Red)   //if parent is red, enter loop
    {
        // upper part : parent is grandparent's left child
		if(node_ptr -> parent == node_ptr -> parent -> parent -> left_child)
		{
			TreeNode* uncle = node_ptr -> parent -> parent -> right_child;
			// case1: uncle is red
			if (uncle -> color == Red)
			{
				node_ptr -> parent -> color = uncle -> color = Black;
				node_ptr -> parent -> parent -> color = Red;            //change grandparent to red
				node_ptr = node_ptr -> parent -> parent;
			}
			// case2 & 3: uncle is black
			else
			{
                // case 2
				if(node_ptr == node_ptr -> parent -> right_child)
				{
					node_ptr = node_ptr -> parent;
					LeftRotate(node_ptr);
				}
				// case 3
				node_ptr -> parent -> color = Black;
				node_ptr -> parent -> parent -> color = Red;
				RightRotate(node_ptr -> parent -> parent);
			}
		}
		// lower part : parent is grandparent's right child
		else
		{
			TreeNode* uncle = node_ptr -> parent -> parent -> left_child;
			// case1: uncle is red
			if(uncle -> color == Red)
			{
				node_ptr -> parent -> color = uncle -> color = Black;
				node_ptr -> parent -> parent -> color = Red;            //change grandparent to red
				node_ptr = node_ptr -> parent -> parent;
			}
			// case2 & 3: uncle is black
			else
			{
			    // case 2
				if (node_ptr == node_ptr -> parent -> left_child)
				{
					node_ptr = node_ptr -> parent;
					RightRotate(node_ptr);
				}
				// case 3
				node_ptr -> parent -> color = Black;
				node_ptr -> parent -> parent -> color = Red;
				LeftRotate(node_ptr -> parent -> parent);
			}
		}
	}
	root -> color = Black;  // make sure root is black
}

TreeNode* RBTree::Successor(TreeNode* node_ptr) const
{
	if(node_ptr -> right_child != NIL)
    {
		node_ptr = node_ptr -> right_child;
		while(node_ptr -> left_child != NIL)
			node_ptr = node_ptr -> left_child;
		return node_ptr;
	}
	TreeNode* successsor = node_ptr -> parent;
	while(successsor != NIL && node_ptr == successsor -> right_child)
	{
		node_ptr = successsor;
		successsor = successsor -> parent;
	}
	return successsor;
}

void RBTree::Delete(const int& key)
{
	TreeNode* delete_node = root;
	while(delete_node -> key != key)
    {
		if(key < delete_node -> key)
			delete_node = delete_node -> left_child;
		else
			delete_node = delete_node -> right_child;
	}
	TreeNode *y = NULL;
	TreeNode *x = NULL;
	if (delete_node -> left_child != NIL && delete_node -> right_child != NIL)
		y = Successor(delete_node);
	else
		y = delete_node;

	if (y -> left_child != NIL)
		x = y -> left_child;
	else
		x = y -> right_child;
	x -> parent = y -> parent;
	if (y -> parent == NIL)
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
		NIL -> parent = NULL;
}

void RBTree::DeleteFixUp(TreeNode* node_ptr)
{
	while(node_ptr != root && node_ptr -> color == Black)
    {
		if(node_ptr == node_ptr -> parent -> left_child)
		{
			TreeNode* sibling = node_ptr -> parent -> right_child;
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
			TreeNode* sibling = node_ptr -> parent -> left_child;
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
