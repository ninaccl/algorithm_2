//对任意结点为头结点的树，左子树都比它小，右子树都比它大
//判断条件：中序遍历升序

#include <iostream>
#include <stack>

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

bool isBST(BiTree T)
{
    bool res = true;
    if(T==NULL)
        return res;
    int pre = INT32_MIN;
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
            res = cur->data > pre? true: false;
            if(res == false)
                return false;
            s.pop();
            pre = cur->data;   
            cur = cur->right;
        }
    }
    return true;
}

int main(void)
{
	BiTree T;
	Create(T);
    bool res = isBST(T);
    cout<<res<<endl;
	return 0;
}
