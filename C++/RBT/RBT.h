#include <iostream>
#include <string>

using namespace std;

class RBT;
class TreeNode
{
    public:
        TreeNode();
        TreeNode(int key,string str);
        int GetKey() const;
        string GetElement() const;
    private:
        TreeNode *leftchild;
        TreeNode *rightchild;
        TreeNode *parent;
        int key;
        string element;
        int color;             // for color: 0: Red, 1: Black
    friend class RBT;
};

class RBT
{
    public:
        RBT();
        void InsertRBT(int key,string str);
        void DeleteRBT(int KEY);
        TreeNode* Search(int KEY);   // called by DeleteRBT()
    private:
        TreeNode *root;
        TreeNode *neel;
        void LeftRotation(TreeNode *current);
        void RightRotation(TreeNode *current);
        void InsertFixedUpRBT(TreeNode *current);
        void DeleteFixedUpRBT(TreeNode *current);
        TreeNode* Successor(TreeNode *current);       // called by DeleteRBT()
        TreeNode* Leftmost(TreeNode *current);        // called by Successor()
};
