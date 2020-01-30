//要求：时间复杂度低于O(N),N为这棵树的节点个数

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

//返回深度
//一直往左走，走到不能再走为止
int mostLeftLevel(BinaryTreeNode* node, int level);
//返回以node为头的节点个数
int bs(BinaryTreeNode* node, int level, int totalheight);

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

//求节点个数的主函数
int nodeNum(BiTree head)
{
    if(head ==NULL)
        return 0;
    return bs(head, 1, mostLeftLevel(head, 1));
}

//返回以node为头的节点个数
int bs(BinaryTreeNode* node, int level, int totalheight)
{
    //level=totalheight时，表示目前节点为叶节点，所以以该节点为根结点的树只含有一个结点
    if(level == totalheight)
        return 1;
    //判断右子树左边的深度和层数是不是相等
    if(mostLeftLevel(node->right, level+1)==totalheight)
        //左树的结点个数加当前结点
        return (1<<(totalheight-level))+bs(node->right,level+1,totalheight);
    else
        //右树的结点个数加左树
        return (1<<(totalheight-level-1))+bs(node->left,level+1,totalheight);
}

//返回深度
//一直往左走，走到不能再走为止
int mostLeftLevel(BinaryTreeNode* node, int level)
{
    while(node!=NULL)
    {
        level++;
        node=node->left;
    }
    return level-1;
}

int main(void)
{
	BiTree T;
	Create(T);
    int res = nodeNum(T);
    cout<<res<<endl;
	return 0;
}
