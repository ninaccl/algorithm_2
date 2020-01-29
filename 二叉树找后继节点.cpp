// 在二叉树中找到一个节点的后继节点
// 【题目】
// 现在有一种新的二叉树节点类型如下:
// public class Node {
//     public int value;
//     public Node left;
//     public Node right;
//     public Node parent;
//     public Node(int data) {
//     this.value = data;
//     }
// }
// 该结构比普通二叉树节点结构多了一个指向父节点的parent指针。假设有一
// 棵Node类型的节点组成的二叉树,树中每个节点的parent指针都正确地指向
// 自己的父节点,头节点的parent指向null。只给一个在二叉树中的某个节点
// node,请实现返回node的后继节点的函数。在二叉树的中序遍历的序列中,
// node的下一个节点叫作node的后继节点。

//后继前驱相对于中序遍历而言
//树 1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 7 -1 -1
//     1
//   2   3
//  4 5 6 7
//中序遍历 4 2 5 1 6 3 7
#include <iostream>

typedef struct BinarytreeNode
{
    int data;
    BinarytreeNode* left;
    BinarytreeNode* right;
    BinarytreeNode* parent;
}BinaryTreeNode, *BiTree;

using namespace std;

BinaryTreeNode* getLeftMost(BinaryTreeNode* node)
{
    if(node ==NULL)
        return node;
    while(node->left!=NULL)
        node=node->left;
    return node;
}

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

BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node)
{
    if(node == NULL)
        return NULL;
    if(node->right != NULL)
        return getLeftMost(node->right);
    else
    {
        BinaryTreeNode* parent = node->parent;
        while(parent!=NULL && parent->left!=node)
        {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }   
}

int main(void)
{
    BiTree T;
	Create(T);
    return 0;
}