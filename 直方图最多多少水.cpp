// 给定一个数组代表一个容器,
// 比如[3,1,2,4],
// 代表0位置是一个宽度为1,高度为3的直方图。
// 代表1位置是一个宽度为1,高度为1的直方图。
// 代表2位置是一个宽度为1,高度为2的直方图。
// 代表3位置是一个宽度为1,高度为4的直方图。
// 所有直方图的底部都在一条水平线上,且紧靠着。
// 把这个图想象成一个容器,这个容器可以装3格的水。
// 给定一个没有负数的数组arr,返回能装几格水?

//关键：单调栈 由小到大

#include <iostream>
#include <stack>

using namespace std;

int maxRecFromBottom(int height[], int len)
{
    if(len == 0)
        return 0;
    int maxArea = 0;
    stack<int> singlestack;
    for(int i=0;i<len;i++)
    {
        //弹出即结算
        while(!singlestack.empty() && height[i] <= height[singlestack.top()])
        //相等也没有关系，因为下标会替代
        {
            int j=singlestack.top();
            singlestack.pop();
            //查看左边界,i为右边界
            int k = singlestack.empty() ? -1: singlestack.top();
            int curArea = (i-k-2)*height[j];
            maxArea = max(curArea,maxArea);
        }
        singlestack.push(i);
    }
    while(!singlestack.empty())
    {
        int j = singlestack.top();
        singlestack.pop();
        int k = singlestack.empty()? -1:singlestack.top();
        int curArea = (len-k-2)*height[j];
        maxArea = max(curArea, maxArea);
    }
    return maxArea;
}

int main(void)
{
//    int arr[4] = {3,1,2,4};
    int arr[6] = {3,4,1,5,3,5};
    cout<<maxRecFromBottom(arr,6)<<endl;
    return 0;
}