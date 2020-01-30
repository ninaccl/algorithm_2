//二叉树按层遍历，每层不满的话节点必须在左边，不满的层数最多为1 
//判断条件：
//一个节点只有右孩子，没有左孩子，必然不是
//一个节点不是左右孩子都全，之后遇到的所有节点都必须是叶节点

#include <iostream>
#include <queue>

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

bool isComplete(BiTree head)
{
    if(head==NULL)
        return true;
    queue<BinaryTreeNode*> treelayer;
    bool leaf = false;
    BinaryTreeNode *left = NULL, *right =NULL;
    treelayer.push(head);
    while(!treelayer.empty())
    {
        head = treelayer.front();
        treelayer.pop();
        left = head->left;
        right = head->right;
        if((leaf && (left!= NULL || right!=NULL))||(left == NULL && right != NULL))
            return false;
        if(left!=NULL)
            treelayer.push(left);
        if(right!=NULL)
            treelayer.push(right);
        else
            leaf = true;
    }
    return true;
}

int main(void)
{
	BiTree T;
	Create(T);
    bool res = isComplete(T);
    cout<<res<<endl;
	return 0;
}
