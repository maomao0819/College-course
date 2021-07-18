#include "RBTree.h"
TreeNode::TreeNode():leftchild(0),rightchild(0),parent(0),key(0),sex(""),height(0),weight(0),color(0){}
TreeNode::TreeNode(int key,string sex="",int Height=0,int Weight=0):leftchild(0),rightchild(0),parent(0),key(key),sex(sex),height(Height),weight(Weight),color(0){}
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
    neel=new TreeNode;    // neel �ݭn�t�m�O����
    neel->color=1;        // neel �O�¦�
    root=neel;            // ���Finsert, �n��root ��l�Ʀ�neel
    root->parent=neel;
};
void RBTree::LeftRotation(TreeNode *x)
{
    TreeNode *y=x->rightchild;          // ��y���Vx��rightchild, �̫�y�|�ܦ�x��parent
    x->rightchild=y->leftchild;         // �ϤG(c)��, ��y��leftchild���bx��rightchild
    if(y->leftchild!=neel)              // �ϤG(c)�k, �Ynode(j)��NIL�h����
        y->leftchild->parent=x;         // �N���y��leftchild��parent�令x
    y->parent=x->parent;                // �ϤG(d)��, ��sy��parent
    if(x->parent==neel)                 // �ϤG(d)�k, �Y���x�Oroot, �����y�ܦ��s��root
        root=y;
    else if(x==x->parent->leftchild)    // �Y���x�O��parent��leftchild
        x->parent->leftchild=y;         // ��s��y�]�O��parent��leftchild
    else                                // �Y���x�O��parent��rightchild
        x->parent->rightchild=y;        // ��s��y�]�O��parent��rightchild
    y->leftchild=x;                     // �ϤG(e)��, �̫�~�ק�y�Px
    x->parent=y;                        // �ϤG(e)�k
}
void RBTree::RightRotation(TreeNode *y)
{
    TreeNode *x=y->leftchild;           // ��x�]��y��leftchild
    y->leftchild=x->rightchild;         // ��x��rightchild���y��leftchild
    if (x->rightchild!=neel)            // �Yx��rightchild����NIL, �N��parent���Vy
        x->rightchild->parent=y;
    x->parent=y->parent;                // �Nx��parent���V���y��parent
                                        // �H�U�@��if-else�N�ק���y��parent��child
    if(y->parent==neel)                 // �Yy����Oroot, x�N�����s��root
        root=x;
    else if (y==y->parent->leftchild)   // �Y���y�O��parent��leftchild,
        y->parent->leftchild=x;         // x�N������s��parent��leftchild
    else                                // �Y���y�O��parent��rightchild,
        y->parent->rightchild=x;        // x�N������s��parent��rightchild
    x->rightchild=y;                    // �Ny�]��x��rightchild
    y->parent=x;                        // �Nx�]��y��parent
}
bool RBTree::insert(int key,string sex,int Height,int Weight)// �e�b���P InsertBST()���޿觹���ۦP, �ȶȻݭn�ק� NULL <-> NIL
{
    TreeNode *y=neel;
    TreeNode *x=root;
    TreeNode *insert_node=new TreeNode(key,sex,Height,Weight);
    while (x != neel)       // ��root��l�Ʀ�neel, �o�̴N�i�H��neel�Ӱ��P�_
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
    if(y==neel)
        this->root=insert_node;
    else if(insert_node->key < y->key)
        y->leftchild=insert_node;
    else
        y->rightchild=insert_node;
    // �H�U�O��RBT��node���]�w, �Nchild pointer���VNIL, �C��]������
    insert_node->leftchild=neel;
    insert_node->rightchild=neel;
    insert_node->color=0;               // �C��i�H�bconstructor���w�]
    InsertFixedUpRBT(insert_node);      // ��i��X�{����P����node�۳s�����ΰ��ץ�
    return true;
}
void RBTree::InsertFixedUpRBT(TreeNode *current)
{
    // case0: parent�O�¦�, �N���ζi�^��
    while(current->parent->color==0)    // �Yparent�O����Y�i�J�j��
    {
        // �W�b���Gparent�Ograndparent��left child
        if(current->parent==current->parent->parent->leftchild)
        {
            TreeNode *uncle=current->parent->parent->rightchild;
            // case1: �Yuncle�O����
            if(uncle->color==0)
            {
                current->parent->color=1;
                uncle->color=1;
                current->parent->parent->color=0;              //grandparent�令����
                current=current->parent->parent;
            }
            // case2 & 3: uncle�O�¦�
            else
            {
                if(current==current->parent->rightchild)
                {     // case2
                    current=current->parent;
                    LeftRotation(current);
                }
                // case3
                current->parent->color=1;                      //��parent���
                current->parent->parent->color=0;              // grandparent���
                RightRotation(current->parent->parent);
            }
        }
        // �U�b���Gparent�Ograndparent��right child, �P�W�b�����
        else
        {
            TreeNode *uncle=current->parent->parent->leftchild;
            // case1: �Yuncle�O����
            if(uncle->color==0)
            {
                current->parent->color=1;
                uncle->color=1;
                current->parent->parent->color=0;              //grandparent�令����
                current=current->parent->parent;
            }
            // case2 & 3: uncle�O�¦�
            else
            {
                if(current==current->parent->leftchild)       // case2
                {
                    current=current->parent;
                    RightRotation(current);
                }
                // case3
                current->parent->color=1;
                current->parent->parent->color=0;
                LeftRotation(current->parent->parent);
            }
        }
    }
    root->color=1;    // �T�Oroot�O�¦�
}
TreeNode& RBTree::operator[](int key)
{
    TreeNode *current=root;               // �Ncurent���Vroot�@��traversal�_�I
    while(current!=NULL && key!=current->key)     // ��ر��p���X�j��G
    {	                                              // 1.�S��� 2.�����
        if(key < current->key)
            current=current->leftchild;   // �V����
        else
            current=current->rightchild;  // �V�k��
    }
    return *current;
}





