#include "0616098_RBTree.h"
TreeNode::TreeNode():leftchild(0),rightchild(0),parent(0),key(0),sex(""),height(0),weight(0),color(0){}
TreeNode::TreeNode(int Key,string Sex="",int Height=0,int Weight=0):leftchild(0),rightchild(0),parent(0),key(Key),sex(Sex),height(Height),weight(Weight),color(0){}
int TreeNode::getHeight()
{
    return height;
};
int TreeNode::getWeight()
{
    return weight;
};
string TreeNode::getGender()
{
    return sex;
};
RBTree::RBTree()
{
    nil=new TreeNode;
    nil->color=1;
    root=nil;
    root->parent=nil;
};
void RBTree::LeftRotation(TreeNode *x)
{
    TreeNode *y=x->rightchild;
    x->rightchild=y->leftchild;
    if(y->leftchild!=nil)
        y->leftchild->parent=x;
    y->parent=x->parent;
    if(x->parent==nil)
        root=y;
    else if(x==x->parent->leftchild)
        x->parent->leftchild=y;
    else
        x->parent->rightchild=y;
    y->leftchild=x;
    x->parent=y;
}
void RBTree::RightRotation(TreeNode *y)
{
    TreeNode *x=y->leftchild;
    y->leftchild=x->rightchild;
    if (x->rightchild!=nil)
        x->rightchild->parent=y;
    x->parent=y->parent;

    if(y->parent==nil)
        root=x;
    else if (y==y->parent->leftchild)
        y->parent->leftchild=x;
    else
        y->parent->rightchild=x;
    x->rightchild=y;
    y->parent=x;
}
bool RBTree::insert(int Key,string Sex,int Height,int Weight)
{
    TreeNode *y=nil;
    TreeNode *x=root;
    TreeNode *insert_node=new TreeNode(Key,Sex,Height,Weight);
    while (x!=nil)
    {
        y=x;
        if(insert_node->key == x->key)
            return false;
        else if(insert_node->key < x->key)
            x=x->leftchild;
        else
            x=x->rightchild;
    }
    insert_node->parent=y;
    if(y==nil)
        this->root=insert_node;
    else if(insert_node->key < y->key)
        y->leftchild=insert_node;
    else
        y->rightchild=insert_node;
    insert_node->leftchild=nil;
    insert_node->rightchild=nil;
    insert_node->color=0;
    InsertFixedUpRBT(insert_node);
    return true;
}
void RBTree::InsertFixedUpRBT(TreeNode *current)
{
    while(current->parent->color==0)
    {
        if(current->parent==current->parent->parent->leftchild)
        {
            TreeNode *uncle=current->parent->parent->rightchild;
            if(uncle->color==0)
            {
                current->parent->color=1;
                uncle->color=1;
                current->parent->parent->color=0;
                current=current->parent->parent;
            }
            else
            {
                if(current==current->parent->rightchild)
                {
                    current=current->parent;
                    LeftRotation(current);
                }
                current->parent->color=1;
                current->parent->parent->color=0;
                RightRotation(current->parent->parent);
            }
        }
        else
        {
            TreeNode *uncle=current->parent->parent->leftchild;
            if(uncle->color==0)
            {
                current->parent->color=1;
                uncle->color=1;
                current->parent->parent->color=0;
                current=current->parent->parent;
            }
            else
            {
                if(current==current->parent->leftchild)
                {
                    current=current->parent;
                    RightRotation(current);
                }
                current->parent->color=1;
                current->parent->parent->color=0;
                LeftRotation(current->parent->parent);
            }
        }
    }
    root->color=1;
}
TreeNode& RBTree::operator[](int key)
{
    TreeNode *current=root;
    while(current!=NULL && key!=current->key)
    {
        if(key < current->key)
            current=current->leftchild;
        else
            current=current->rightchild;
    }
    return *current;
}
