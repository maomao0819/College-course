#ifndef _0616098_RBTree_h
#define _0616098_RBTree_h
#include <iostream>

using namespace std;

class TreeNode
{
    public:
        TreeNode();
        TreeNode(int Key,string Sex,int Height,int Weight);
        string getGender();
        int getHeight();
        int getWeight();
    private:
        TreeNode *leftchild;
        TreeNode *rightchild;
        TreeNode *parent;
        int key;
        string sex;
        int height;
        int weight;
        int color;             //color: 0:Red 1:Black
        friend class RBTree;
};

class RBTree
{
    public:
        RBTree();
        bool insert(int Key,string Sex,int Height,int Weight);
        TreeNode &operator[](int key);
    private:
        TreeNode *root;
        TreeNode *nil;
        void LeftRotation(TreeNode *x);
        void RightRotation(TreeNode *y);
        void InsertFixedUpRBT(TreeNode *current);
};
#endif
