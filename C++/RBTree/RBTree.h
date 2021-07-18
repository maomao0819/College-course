#ifndef RBTree_h
#define RBTree_h
#include <iostream>
#include <string>

using namespace std;

class RBTree;
class TreeNode
{
    public:
        TreeNode();
        TreeNode(int key,string sex,int Height,int Weight);
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
        int color;             // for color: 0: Red, 1: Black
        friend class RBTree;
};

class RBTree
{
    public:
        RBTree();
        bool insert(int key,string sex,int Height,int Weight);
        TreeNode &operator[](int key) ;
    private:
        TreeNode *root;
        TreeNode *neel;
        void LeftRotation(TreeNode *current);
        void RightRotation(TreeNode *current);
        void InsertFixedUpRBT(TreeNode *current);
};
#endif
