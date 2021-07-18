#ifndef RBTree_h
#define RBTree_h
#include <fstream>
using namespace std;
enum Color
{
	Red = 0,
	Black = 1
};
class TreeNode
{
    public:
        TreeNode();
        TreeNode(int);
    private:
        TreeNode *left_child;
        TreeNode *right_child;
        TreeNode *parent;
        int key;
        Color color;
        friend class RBTree;
};

class RBTree
{
public:
	RBTree();
	const TreeNode* getRoot() const;
	const TreeNode* getNil() const;
	void Insert(const int&);
	void Delete(const int&);
	void print(ofstream&);

private:
    void LeftRotate(TreeNode*);
	void RightRotate(TreeNode*);
	void InsertFixUp(TreeNode*);
	void DeleteFixUp(TreeNode*);
    TreeNode* Successor(TreeNode*) const;
	void print_node(const TreeNode*, ofstream&);
	TreeNode* root;
	TreeNode* NIL;
};
#endif
