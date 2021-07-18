#pragma once
#include <fstream>
using namespace std;
enum Color
{
	Red = 0,
	Black = 1
};

struct Int_Node
{
	int key;
	Int_Node *left_child;
	Int_Node *right_child;
	Int_Node *parent;
	Color color;
	Int_Node(int key) : key(key), left_child(NULL), right_child(NULL), parent(NULL), color(Red)
	{}
};

class RBTree
{
public:
	RBTree();
	~RBTree() = default;
	const Int_Node* getRoot() const;
	const Int_Node* getNil() const;
	void Insert(const int&);
	void Delete(const int&);
	void print(ofstream&);

private:
    void LeftRotate(Int_Node*);
	void RightRotate(Int_Node*);
	void InsertFixUp(Int_Node*);
	void DeleteFixUp(Int_Node*);
    Int_Node* Successor(Int_Node*) const;
	void printnode(const Int_Node*, ofstream&);
	Int_Node* root;
	Int_Node* nil;
};
