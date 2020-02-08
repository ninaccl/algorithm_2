// morris遍历 时间复杂度O(N),额外空间复杂度O(1)
// 1)来到的当前节点记为Cur。如果cur无左孩子，cur向右移动(cur = cur.right)
// 2)如果cur有左孩子，找到cur左子树上最右的节点，记为mostright
//     1.如果mostright的右指针指向空，让其指向cur，cur向左移动(cur = cur.left)
//     2.如果mostright的右指针指向cur，让其指向空，cur向右移动

#include <stack>
#include <iostream>

//树 1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 7 -1 -1
//     1
//   2   3
//  4 5 6 7

typedef struct BinaryTreeNode
{
	int data;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
}BinaryTreeNode, *BiTree;

using namespace std;

void Create(BiTree &T)
{
	int ch;
	cin >> ch;
	if (ch == -1)
		T = NULL;
	else
	{
		T = new BinaryTreeNode;
		T->data = ch;
		Create(T->left);
		Create(T->right);
	}
}

void printEdge(BiTree T)
{
    BinaryTreeNode *pre = T;
    BinaryTreeNode *cur = T->right;
    while(cur !=NULL)
    {
        BinaryTreeNode* next = cur->right;
        cur->right = pre;
        pre = cur;
        cur = next;
    }
    cur = pre;
    pre = NULL;
    while(cur !=T)
    {
        cout<<cur->data<<" ";
        BinaryTreeNode* next = cur->right;
        cur->right = pre;
        pre = cur;
        cur = next;
    }
    cout<<cur->data<<" ";
}

//第二次遇到的时候打印
void morrisIn(BiTree head)
{
    if(head == NULL)
        return;
    BinaryTreeNode* cur = head;
    BinaryTreeNode* mostRight = NULL;
    while(cur!=NULL)
    {
        mostRight = cur->left;
        if(mostRight!=NULL)
        {
            //找左子树最右节点
            while(mostRight->right != NULL && mostRight->right !=cur)
                mostRight = mostRight->right;
            if(mostRight->right == NULL)
            {
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else
            {
                mostRight->right = NULL;
            }
        }
        cout<<cur->data<<" ";
        cur = cur->right;
    }
    cout<<endl;
}

//第一次遇到的时候打印
void morrisPre(BiTree head)
{
    if(head == NULL)
        return;
    BinaryTreeNode* cur = head;
    BinaryTreeNode* mostRight = NULL;
    while(cur!=NULL)
    {
        mostRight = cur->left;
        if(mostRight!=NULL)
        {
            //找左子树最右节点
            while(mostRight->right != NULL && mostRight->right !=cur)
                mostRight = mostRight->right;
            if(mostRight->right == NULL)
            {
                mostRight->right = cur;
                //第一次遇到的时候打印
                cout<<cur->data<<" ";
                cur = cur->left;
                continue;
            }
            else
            {
                mostRight->right = NULL;
            }
        }
        //没有左子树的话只能经历一次，直接打印
        else
        {
            cout<<cur->data<<" ";
        }      
        cur = cur->right;
    }
    cout<<endl;
}

//morris实现后序
//只关注能到两次的节点，第二次到的时候逆序打印左子树右边界，函数退出前单独打印整棵树的右边界
void morrisPos(BiTree head)
{
    if(head == NULL)
        return;
    BinaryTreeNode* cur = head;
    BinaryTreeNode* mostRight = NULL;
    while(cur!=NULL)
    {
        mostRight = cur->left;
        if(mostRight!=NULL)
        {
            //找左子树最右节点
            while(mostRight->right != NULL && mostRight->right !=cur)
                mostRight = mostRight->right;
            if(mostRight->right == NULL)
            {
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else
            {
                mostRight->right = NULL;
                printEdge(cur->left);
            }
        }    
        cur = cur->right;
    }
    printEdge(head);
    cout<<endl;
}

int main(void)
{
	BiTree T;
	Create(T);
    morrisPre(T);
    morrisIn(T);
    morrisPos(T);
	return 0;
}