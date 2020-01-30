//对任意节点，左子树和右子树的高度差不超过1

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

pair<bool, int> isBalance(BiTree head)
{
    if(head == NULL)
        return make_pair<bool, int>(true, 0);
    pair<bool, int> leftData = isBalance(head->left);
    if(leftData.first == false)
        return make_pair<bool, int>(false, 0);
    pair<bool, int> rightData = isBalance(head->right);
    if(leftData.first == false)
        return make_pair<bool, int>(false, 0);
    if(abs(leftData.second-rightData.second)<=1)
        return make_pair<bool, int>(true, max(leftData.second,rightData.second)+1);
    else
        return make_pair<bool, int>(false, 0);
}

int main(void)
{
	BiTree T;
	Create(T);
    bool res = (isBalance(T)).first;
    cout<<res<<endl;
	return 0;
}
