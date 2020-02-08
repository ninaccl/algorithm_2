// 【题目】
// 一个环形山峰数组[1,2,4,5,3]数组环形，3和1连
// 1.相邻可见
// 2.若经过的路中间没有比两座山峰中低的高的，则可互相看见
// 则有多少对能互相看见
//    5  4
//   3    2
//     1
// 【答案】
// (1,2)(1,3)(2,4)(4,5)(3,5)(2,3)(3,4)
// 7对
// 【思路】
// 若值不同时
// 数组长度1   0对
// 数组长度2   1对
// 数组长度i   (2*i-3)对
// 有相同值时
// 需要使用单调栈 从大到小

#include <iostream>
#include <stack>

using namespace std;

//环形数组找下一个位置
int nextIndex(int size, int i)
{
    return i<(size-1)?(i+1):0;
}

//CK2(k个数选2个数组队的对数)实现
long getInternalSum(int n)
{
    return n==1? 0 : n*(n-1)/2;
}

long communications(int arr[], int len)
{
    if(len<2)
        return 0;
    //找到最大值位置
    int maxIndex = 0;
    for(int i=0;i<len;i++)
        maxIndex = arr[maxIndex]<arr[i]? i:maxIndex;
    int value = arr[maxIndex];
    //从最大值下一个数开始遍历
    int index = nextIndex(len,maxIndex);
    long res = 0;
    stack<pair<int, int>> singlestack;  //stack里放当前值和出现次数
    singlestack.push(pair<int,int>(value,1));
    //判断是否遍历结束
    while(index != maxIndex)
    {
        value = arr[index];
        //若有记录需要弹出
        while(!singlestack.empty() && singlestack.top().first <value)
        {
            int times = singlestack.top().second;
            singlestack.pop();
            res += getInternalSum(times)+2*times; //C(2,times)+2*times 此时栈不可能为空
        }
        if(!singlestack.empty() && singlestack.top().first == value)
            singlestack.top().second++;
        else
            singlestack.push(pair<int,int>(value,1));
        //查看下一个
        index = nextIndex(len, index);
    }
    while(!singlestack.empty())
    {
        int times = singlestack.top().second;
        singlestack.pop();
        res+=getInternalSum(times);
        if(!singlestack.empty())
        {
            res+=times;
            if(singlestack.size()>1)
                res+=times;
            else
                res+=singlestack.top().second>1? times:0;
        }
    }
    return res;
}

int main(void)
{
    int arr[5] = {1,2,4,5,3};
    cout<<communications(arr,5)<<endl;
    return 0;
}