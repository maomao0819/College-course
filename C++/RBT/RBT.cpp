#include "RBT.h"
TreeNode::TreeNode():leftchild(0),rightchild(0),parent(0),key(0),element(""),color(0){}
TreeNode::TreeNode(int key,string str=""):leftchild(0),rightchild(0),parent(0),key(key),element(str),color(0){}
int TreeNode::GetKey() const
{
    return key;
};
string TreeNode::GetElement() const
{
    return element;
};
RBT::RBT()
{
    neel=new TreeNode;    // neel �ݭn�t�m�O����
    neel->color=1;        // neel �O�¦�
    root=neel;            // ���Finsert, �n��root ��l�Ʀ�neel
    root->parent=neel;
};
void RBT::LeftRotation(TreeNode *x)
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
void RBT::RightRotation(TreeNode *y)
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
void RBT::InsertRBT(int key,string str)// �e�b���P InsertBST()���޿觹���ۦP, �ȶȻݭn�ק� NULL <-> NIL
{
    TreeNode *y=neel;
    TreeNode *x=root;
    TreeNode *insert_node=new TreeNode(key,str);
    while (x != neel)       // ��root��l�Ʀ�neel, �o�̴N�i�H��neel�Ӱ��P�_
    {
        y=x;
        if(insert_node->key < x->key)
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
}
void RBT::InsertFixedUpRBT(TreeNode *current)
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
TreeNode* RBT::Search(int KEY)
{
    TreeNode *current = root;               // �Ncurent���Vroot�@��traversal�_�I
    while(current != NULL && KEY != current->key)     // ��ر��p���X�j��G
    {	                                              // 1.�S��� 2.�����
        if(KEY < current->key)
            current=current->leftchild;   // �V����
        else
            current=current->rightchild;  // �V�k��
    }
    return current;
}
TreeNode* RBT::Leftmost(TreeNode *current)
{

    while(current->leftchild!=NULL)
        current=current->leftchild;
    return current;
}
TreeNode* RBT::Successor(TreeNode *current)
{
    if(current->rightchild!=NULL)
        return Leftmost(current->rightchild);
    TreeNode *new_node=current->parent;
    while(new_node!=NULL && current==new_node->rightchild)
    {
        current=new_node;
        new_node=new_node->parent;
    }
    return new_node;
}
void RBT::DeleteRBT(int KEY)              // �n�R���㦳KEY��node
{
    TreeNode *delete_node=Search(KEY);    // ���T�{RBT���O�_�s�b�㦳KEY��node
    if(delete_node==NULL)
    {
        std::cout<<"data not found.\n";
        return;
    }
    TreeNode *y=0;     // �u���n�Q�R��������O���骺node
    TreeNode *x=0;     // �n�Q�R����node��"child"
    if (delete_node->leftchild==neel || delete_node->rightchild==neel)
        y=delete_node;
    else
        y=Successor(delete_node);         // �Ny�]��delete_node��Successor
                                          // �g�L�o��if-else, y�վ㦨�ܦh�u���@��child
    if (y->leftchild!=neel)               // �Nx�]��y��child, �i�঳��ڸ��, �]���i��ONIL
        x=y->leftchild;
    else
        x=y->rightchild;
    x->parent=y->parent;                   // �Y��x�ONIL�]�n��x��parent���V���Ī��O�����m
                                           // �]���bFixUp�ɻݭn�ǥ�x->parent�P�_x��leftchild�άOrightchild
    if(y->parent==neel)                    // ���ۦA��n�Q����O���骺node��"parent"���V�s��child
        this->root=x;                      // �Y�R�����O�����root, �N��x���s��root
    else if(y==y->parent->leftchild)       // �Yy�쥻�O��parent��left child
        y->parent->leftchild=x;            // �K��x�Ҧby��parent��left child, ���Ny
    else                                   // �Yy�쥻�O��parent��right child
        y->parent->rightchild=x;           // �K��x�Ҧby��parent��right child, ���Ny
    if(y!=delete_node)                     // �w��case3
    {
        delete_node->key=y->key;           // �Yy�Odelete_node������, �̫�n�A�Ny�����
        delete_node->element=y->element;   // ��^delete_node���O�����m, �ñNy���O�����m����
    }
    if (y->color==1)                       // �Y�R����node�O�¦�, �n�qx�i��ץ�, �H�ŦXRBT���C��W�h
        DeleteFixedUpRBT(x);
}
void RBT::DeleteFixedUpRBT(TreeNode *current)   // Case0:(i)  current�O���⪺, �����⥦���
{                                               //       (ii) current�Oroot, �����⥦���
    while(current!=root && current->color==1)
    {                                           // current�Oleftchild
        if(current==current->parent->leftchild)
        {
            TreeNode *sibling=current->parent->rightchild;
            // Case1: �p�Gsibling�O����
            if(sibling->color==0)
            {
                sibling->color=1;
                current->parent->color=0;
                LeftRotation(current->parent);
                sibling=current->parent->rightchild;
            }
            // �i�J Case2�B3�B4: sibling�O�¦�
            // Case2: sibling�����child���O�¦�
            if(sibling->leftchild->color==1 && sibling->rightchild->color==1)
            {
                sibling->color=0;
                current=current->parent;           // �Ycurrent��s��root, �Y���X�j��
            }
            // Case3 & 4: current�u���䤤�@��child�O�¦�
            else
            {
            	// case3: sibling��right child�O�ª�, left child�O����
                if(sibling->rightchild->color==1)
                {
                    sibling->leftchild->color=1;
                    sibling->color=0;
                    RightRotation(sibling);
                    sibling=current->parent->rightchild;
                }
                // �g�LCase3��, �@�w�|�ܦ�Case4
                // Case 4: sibling��right child �O���⪺, left child�O�¦�
                sibling->color=current->parent->color;
                current->parent->color=1;
                sibling->rightchild->color=1;
                LeftRotation(current->parent);
                current=root;     // �Ncurrent���ʨ�root, �@�w���X�j��
            }
        }
        // current�Orightchild
        else
        {
            TreeNode *sibling=current->parent->leftchild;
            // Case1: �p�Gsibling�O����
            if(sibling->color==0)
            {
                sibling->color=1;
                current->parent->color=0;
                RightRotation(current->parent);
                sibling=current->parent->leftchild;
            }
            // �i�J Case2�B3�B4: sibling�O�¦�
            // Case2: sibling�����child���O�¦�
            if(sibling->leftchild->color==1 && sibling->rightchild->color==1)
            {
                sibling->color=0;
                current=current->parent;             // �Ycurrent��s��root, �Y���X�j��
            }
            // Case3 & 4: current�u���䤤�@��child�O�¦�
            else
            {
            	// case3: sibling��left child�O�ª�, right child�O����
                if(sibling->leftchild->color==1)
                {
                    sibling->rightchild->color=1;
                    sibling->color=0;
                    LeftRotation(sibling);
                    sibling=current->parent->leftchild;
                }
                // �g�LCase3��, �@�w�|�ܦ�Case4
                // Case 4: sibling��left child �O���⪺, rightt child�O�¦�
                sibling->color=current->parent->color;
                current->parent->color=1;
                sibling->leftchild->color=1;
                RightRotation(current->parent);
                current=root;     // �Ncurrent���ʨ�root, �@�w���X�j��
            }
        }
    }
    current->color=1;
}





