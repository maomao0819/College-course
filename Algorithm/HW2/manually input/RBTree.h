#pragma once

using namespace std;

enum Color {
	Red = 0,
	Black = 1
};

struct Int_Node {
	int key;
	Int_Node *left;
	Int_Node *right;
	Int_Node *parent;
	Color color;

	Int_Node() = delete;
	explicit Int_Node(int key);

};

class RBTree {
public:
	RBTree();
	~RBTree() = default;

	inline const Int_Node* getRoot() const{
		return root;
	}

	inline const Int_Node* getNil() const{
		return nil;
	}

	void Insert(const int& key);
	void Delete(const int& key);
	void print();

private:
	void InsertFixUp(Int_Node*);
	void DeleteFixUp(Int_Node*);
	void LeftRotate(Int_Node*);
	void RightRotate(Int_Node*);
	void print1(const Int_Node*);
	Int_Node* Successor(Int_Node*) const;

	Int_Node *root;
	Int_Node *nil;
};
