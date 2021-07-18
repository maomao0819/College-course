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
    neel=new TreeNode;    // neel 需要配置記憶體
    neel->color=1;        // neel 是黑色
    root=neel;            // 為了insert, 要把root 初始化成neel
    root->parent=neel;
};
void RBTree::LeftRotation(TreeNode *x)
{
    TreeNode *y=x->rightchild;          // 把y指向x的rightchild, 最後y會變成x的parent
    x->rightchild=y->leftchild;         // 圖二(c)左, 把y的leftchild托在x的rightchild
    if(y->leftchild!=neel)              // 圖二(c)右, 若node(j)為NIL則忽略
        y->leftchild->parent=x;         // 將原先y的leftchild的parent改成x
    y->parent=x->parent;                // 圖二(d)左, 更新y的parent
    if(x->parent==neel)                 // 圖二(d)右, 若原先x是root, 旋轉後y變成新的root
        root=y;
    else if(x==x->parent->leftchild)    // 若原先x是其parent的leftchild
        x->parent->leftchild=y;         // 更新後y也是其parent的leftchild
    else                                // 若原先x是其parent的rightchild
        x->parent->rightchild=y;        // 更新後y也是其parent的rightchild
    y->leftchild=x;                     // 圖二(e)左, 最後才修改y與x
    x->parent=y;                        // 圖二(e)右
}
void RBTree::RightRotation(TreeNode *y)
{
    TreeNode *x=y->leftchild;           // 把x設成y的leftchild
    y->leftchild=x->rightchild;         // 把x的rightchild放到y的leftchild
    if (x->rightchild!=neel)            // 若x的rightchild不為NIL, 將其parent指向y
        x->rightchild->parent=y;
    x->parent=y->parent;                // 將x的parent指向原先y的parent
                                        // 以下一組if-else將修改原先y的parent之child
    if(y->parent==neel)                 // 若y原先是root, x將成為新的root
        root=x;
    else if (y==y->parent->leftchild)   // 若原先y是其parent之leftchild,
        y->parent->leftchild=x;         // x就成為其新的parent之leftchild
    else                                // 若原先y是其parent之rightchild,
        y->parent->rightchild=x;        // x就成為其新的parent之rightchild
    x->rightchild=y;                    // 將y設為x之rightchild
    y->parent=x;                        // 將x設為y之parent
}
bool RBTree::insert(int key,string sex,int Height,int Weight)// 前半部與 InsertBST()之邏輯完全相同, 僅僅需要修改 NULL <-> NIL
{
    TreeNode *y=neel;
    TreeNode *x=root;
    TreeNode *insert_node=new TreeNode(key,sex,Height,Weight);
    while (x != neel)       // 把root初始化成neel, 這裡就可以用neel來做判斷
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
    // 以下是對RBT之node的設定, 將child pointer指向NIL, 顏色設為紅色
    insert_node->leftchild=neel;
    insert_node->rightchild=neel;
    insert_node->color=0;               // 顏色可以在constructor中預設
    InsertFixedUpRBT(insert_node);      // 對可能出現紅色與紅色node相連之情形做修正
    return true;
}
void RBTree::InsertFixedUpRBT(TreeNode *current)
{
    // case0: parent是黑色, 就不用進回圈
    while(current->parent->color==0)    // 若parent是紅色即進入迴圈
    {
        // 上半部：parent是grandparent的left child
        if(current->parent==current->parent->parent->leftchild)
        {
            TreeNode *uncle=current->parent->parent->rightchild;
            // case1: 若uncle是紅色
            if(uncle->color==0)
            {
                current->parent->color=1;
                uncle->color=1;
                current->parent->parent->color=0;              //grandparent改成紅色
                current=current->parent->parent;
            }
            // case2 & 3: uncle是黑色
            else
            {
                if(current==current->parent->rightchild)
                {     // case2
                    current=current->parent;
                    LeftRotation(current);
                }
                // case3
                current->parent->color=1;                      //把parent塗黑
                current->parent->parent->color=0;              // grandparent塗紅
                RightRotation(current->parent->parent);
            }
        }
        // 下半部：parent是grandparent的right child, 與上半部對稱
        else
        {
            TreeNode *uncle=current->parent->parent->leftchild;
            // case1: 若uncle是紅色
            if(uncle->color==0)
            {
                current->parent->color=1;
                uncle->color=1;
                current->parent->parent->color=0;              //grandparent改成紅色
                current=current->parent->parent;
            }
            // case2 & 3: uncle是黑色
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
    root->color=1;    // 確保root是黑色
}
TreeNode& RBTree::operator[](int key)
{
    TreeNode *current=root;               // 將curent指向root作為traversal起點
    while(current!=NULL && key!=current->key)     // 兩種情況跳出迴圈：
    {	                                              // 1.沒找到 2.有找到
        if(key < current->key)
            current=current->leftchild;   // 向左走
        else
            current=current->rightchild;  // 向右走
    }
    return *current;
}





