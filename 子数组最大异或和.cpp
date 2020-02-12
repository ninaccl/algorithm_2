// 【题目】
// 给定一个数组，求子数组的最大异或和。
// 一个数组的异或和为，数组中所有的数异或起来的结果。
// 【思路】 时间复杂度O(N)
// 前缀树
// 求以i结尾的最大异或和 = 0...i的异或和异或0...j的异或和
// 0...j ^ j...i = 0...i -> j...i = 0...i ^ 0...j
// 除了符号位有想要正负的区别之外，其他都是紧着高位变1
// 因为负数除了最高位之外是取反+1

#include <iostream>
#include <algorithm>

using namespace std;

class Node
{
public:
    Node** nexts = new Node*[2];    //0的路或者1的路
};

class NumTrie
{
public:
    Node* head = new Node;

    void add(int num)
    {
        // 提取每位数字加入前缀树
        Node* cur = head;
        for(int move = 31;move>=0;move--)   //  32位整数
        {
            int path = ((num >> move) & 1); // 符号位来到最后，&1得到符号位数字  1，0
            //路径不存在就新建
            cur->nexts[path] = cur->nexts[path] == NULL? new Node : cur->nexts[path]; 
            cur = cur->nexts[path];
        }
    }

    //num为从0到i的异或结果
    int maxXor(int num)
    {
        Node* cur = head;
        int res = 0;
        for(int move = 31; move >= 0; move--)
        {
            //提取每一位
            int path = (num >> move) & 1;
            //符号为1希望选1，符号位为0希望选0
            //不是符号位希望选相反的
            int best = move == 31 ? path : (path ^ 1);
            //best路不为空选这条路，为空的话只能选其他路
            best = cur->nexts[best] != NULL ? best : (best ^ 1);
            //res为异或结果
            res |= (path ^ best) << move;
            //继续比较下一位
            cur = cur->nexts[best];
        }
        return res;
    }
};

int maxXorSubarray(int *arr, int len)
{
    if(len<1)
        return 0;
    int maxres = INT32_MIN;
    int eor = 0;
    NumTrie numtrie;    //存着0到各个位的异或结果
    numtrie.add(0);
    for(int i=0;i<len;i++)
    {
        eor ^= arr[i];  //从0到i的异或结果
        maxres = max(maxres, numtrie.maxXor(eor));
        numtrie.add(eor);
    }
    return maxres;
}

int main(void)
{
    int arr[] = {3,4,5,15};
    int num=3;
    for(int i=31;i>=0;i--)
    {
        int path=(num>>i)&1;
        cout<<path<<" ";
    }
    cout<<endl;
    int len = 4;
    cout<<maxXorSubarray(arr, len)<<endl;
    return 0;
}