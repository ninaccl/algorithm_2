// 【题目】
// 二叉树中，一个节点可以往上走和往下走，那么从节点A总能走到节点B。
// 节点A走到节点B的距离为：A走到B最短路径上的节点个数。
// 求一棵二叉树上的最远距离。

// 【可能性】
// 最大距离为左子树最大距离
// 最大距离为右子树最大距离
// 最大距离为左边深度+当前+右边深度

#include <iostream>

using namespace std;

typedef struct BinaryTreeNode
{
	int data;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
}BinaryTreeNode, *BiTree;

class ReturnType
{
public:
    int maxDistance;
    int h;  //高度

    ReturnType(){}
    ReturnType(int maxDistance_, int height_)
    {
        maxDistance = maxDistance_;
        h = height_;
    }
};

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

ReturnType process(BiTree head)
{
    if(head == NULL)
        return ReturnType(0,0);
    ReturnType leftReturnType = process(head->left);
    ReturnType rightReturnType = process(head->right);
    int includeHeadDistance = leftReturnType.h+1+rightReturnType.h;
    int p1 = leftReturnType.maxDistance;
    int p2 = rightReturnType.maxDistance;
    int resDistance = max(max(p1,p2),includeHeadDistance);
    int resheight = max(leftReturnType.h, rightReturnType.h)+1;
    return ReturnType(resDistance,resheight);
}

int main(void)
{
    BiTree T;
    Create(T);
    cout<<process(T).maxDistance<<endl;
    return 0;
}