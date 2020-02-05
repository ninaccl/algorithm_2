// 给定两个二叉树T1和T2,返回T1的某个子树结构是否与T2的结构相等。
//解决方法：T1和T2都序列化，若T2为T1的子串，则T1的某个子树结构是否与T2的结构相等

#include <vector>
#include <queue>
#include <iostream>

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

int* getNextArray(string str)
{
    int len = str.length();
    int* next = new int[len]{-1,0,};
    int i = 2;  // i指示当前位置
    int cn = 0; // cn指示跳的位置
    while(i<len) 
    {
        if(str[i-1] == str[cn])
            next[i++] = ++cn;
        else if(cn>0)
            cn = next[cn];
        else
            next[i++] = 0;
    }
    return next;
}

int getIndexof(string str1,string str2 )
{
    int i1 = 0, i2 = 0;
    int* next = getNextArray(str2);
    while(i1 <str1.length() && i2 < str2.length())
    {
        if(str1[i1] == str2[i2])
        {
            i1++;
            i2++;
        }
        else if(next[i2] == -1) //-1指string2零位置的字符
            i1++;
        else
            i2 = next[i2];
    }
    delete []next;
    return i2 == str2.length() ? i1-i2: -1;
}

int main(void)
{
    BiTree T1;
	Create(T1);
    string str1 = serialByPre(T1);
    cout<<str1<<endl;
    BiTree T2;
	Create(T2);
    string str2 = serialByPre(T2);
    cout<<str2<<endl;
    int index = getIndexof(str1, str2);
    cout << index <<endl;
    return 0;
}