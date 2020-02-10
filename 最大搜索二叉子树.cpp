// 【题目】给定一棵树，找最大搜索二叉子树

// 【思路】
// 1)最大搜索二叉子树来源于左子树
// 2)最大搜索二叉子树来源于右子树
// 3)最大搜索二叉子树为包含头节点的整棵树

// 信息：
// 1.左树最大搜索二叉树大小
// 2.右树最大搜索二叉树大小
// 3.左树最大搜索二叉树头部
// 4.右树最大搜索二叉树头部
// 5.左树最大值
// 6.右树最小值

// 左右数返回的结构体应该是一样
// 1.搜索二叉树大小
// 2.头部
// 3.最小值
// 4.最大值

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
    int size;
    BiTree head;
    int min;
    int max;

    ReturnType(){}
    ReturnType(int size_, BiTree head_, int min_, int max_)
    {
        size = size_;
        head = head_;
        min = min_;
        max = max_;
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
        return ReturnType(0,NULL,INT32_MAX,INT32_MIN);

    BinaryTreeNode* left = head->left;
    ReturnType leftSubTressInfo = process(left);
    BinaryTreeNode* right = head->right;
    ReturnType rightSUbTressInfo = process(right);

    //可能性3
    int includeItSelf = 0;  //初始化为0
    if(leftSubTressInfo.head == left && rightSUbTressInfo.head == right 
        && head->data > leftSubTressInfo.max && head->data < rightSUbTressInfo.min)
        includeItSelf = leftSubTressInfo.size + 1 + rightSUbTressInfo.size;
    //可能性1
    int p1 = leftSubTressInfo.size;
    //可能性2
    int p2 = rightSUbTressInfo.size;
    int maxSize = max(max(p1, p2),includeItSelf);

    //构建本层的返回
    BinaryTreeNode* maxHead = p1 > p2? leftSubTressInfo.head : rightSUbTressInfo.head;
    if(maxSize == includeItSelf)
        maxHead = head;
    
    return ReturnType(maxSize, maxHead, min(min(leftSubTressInfo.min, rightSUbTressInfo.min),head->data),
            max(max(leftSubTressInfo.max, rightSUbTressInfo.max), head->data));
}

int main(void)
{
    BiTree T;
    Create(T);
    int res = process(T).size;
    cout<<res<<endl;
    return 0;
}