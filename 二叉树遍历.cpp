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

//先序遍历递归版
void preOrder(BiTree T)
{
	if (T == NULL)
		return;
	cout << T->data << endl;
	preOrder(T->left);
	preOrder(T->right);
}

//先序遍历非递归版
void preOrderNonRecursion(BiTree T)
{
    if(T != NULL)
    {
        stack<BinaryTreeNode*> s;
        s.push(T);
        BinaryTreeNode* cur;
        while(!s.empty())
        {
            cur = s.top();
            s.pop();
            cout<<cur->data<<endl;
            if(cur->right!=NULL)
                s.push(cur->right);
            if(cur->left!=NULL)
                s.push(cur->left);
        }
    }  
}

//中序遍历
void inOrder(BiTree T)
{
	if (T == NULL)
		return;
	inOrder(T->left);
	cout << T->data << endl;
	inOrder(T->right);
}

//中序遍历非递归版
void inOrderNonRecursion(BiTree T)
{
    if(T != NULL)
    {
        stack<BinaryTreeNode*> s;
        BinaryTreeNode* cur = T;
        while(!s.empty() || cur!=NULL)
        {
            if(cur!=NULL)
            {
                s.push(cur);  
                cur = cur->left;             
            }
            else
            {
                cur = s.top();
                cout<<cur->data<<endl;
                s.pop();
                cur = cur->right;
            }
            
        }
    }  
}

//后序遍历
void postOrder(BiTree T)
{
	if (T == NULL)
		return;
	postOrder(T->left);
	postOrder(T->right);
	cout << T->data << endl;
}

//后序遍历非递归版
void postOrderNonRecursion(BiTree T)
{
    if(T!=NULL)
    {
        stack<BinaryTreeNode* > s;
        stack<BinaryTreeNode* > aids;
        BinaryTreeNode* cur = T;
        s.push(cur);
        while(!s.empty())
        {
            cur = s.top();
            s.pop();
            aids.push(cur);
            if(cur->left!=NULL)
                s.push(cur->left);
            if(cur->right!=NULL)
                s.push(cur->right);
        }
        while(!aids.empty())
        {
            cur = aids.top();
            cout<<cur->data<<endl;
            aids.pop();
        }
    }
}

int main(void)
{
	BiTree T;
	Create(T);
    postOrderNonRecursion(T);
	return 0;
}
