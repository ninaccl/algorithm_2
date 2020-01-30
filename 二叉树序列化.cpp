#include <vector>
#include <queue>
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

//二叉树序列化 前序
string serialByPre(BiTree head)
{
    if(head==NULL)
        return "#!";
    string res=to_string(head->data)+"!";
    res += serialByPre(head->left);
    res += serialByPre(head->right);
    return res;
}

//split函数实现
queue<string> split(string s,char ch){
    int start=0;
    int len=0;
    queue<string> ret;
    for(int i=0;i<s.length();i++){
        if(s[i]==ch){
            ret.push(s.substr(start,len));
            start=i+1;
            len=0;
        }
        else{
            len++;
        }
    }
    if(start<s.length())
        ret.push(s.substr(start,len));
    return ret;
}

//二叉树反序列化 具体实现
BiTree reconByPreOrder(queue<string> valuesorigin)
{
    static queue<string> values = valuesorigin;
    string value = values.front();
    values.pop();
    if(value == "#")
        return NULL;
    BinaryTreeNode* head = new BinaryTreeNode;
	head->data = atoi(value.c_str());
    head->left = reconByPreOrder(values);
    head->right = reconByPreOrder(values);
    return head;
}

//二叉树反序列化 前序
BiTree reconPreByString(string prestr)
{
    queue<string> values = split(prestr,'!');
    BiTree head = reconByPreOrder(values);
    return head;
}

int main(void)
{
	BiTree T;
	Create(T);
    string res = serialByPre(T);
    cout<<res<<endl;
    BiTree head = reconPreByString(res);
	return 0;
}
