// 求最大子矩阵大小
// 【题目】
// 给定一个整型矩阵map，其中的值只有0和1两种，求其中全是1的所有矩形区域中，最大的矩形区域为1的数量。
// 例如：
// 1   1   1   0
// 其中，最大的矩形区域有3个1，所以返回3。
// 再如：
// 1   0   1   1
// 1   1   1   1
// 1   1   1   0
// 其中，最大的矩形区域有6个1，所以返回6。
//
// 【解决方法】 时间复杂度O(N*M)
// 关键：单调栈
// 以每一行为底求最大的长方形，参考直方图最多多少水.cpp
// 则上面数组变为
// 1    0   1   1
// 2    1   1   1
// 3    2   3   0

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
        while(!singlestack.empty() && height[i] <= height[singlestack.top()])
        {
            int j=singlestack.top();
            singlestack.pop();
            int k = singlestack.empty() ? -1: singlestack.top();
            int curArea = (i-k-1)*height[j];
            maxArea = max(curArea,maxArea);
        }
        singlestack.push(i);
    }
    while(!singlestack.empty())
    {
        int j = singlestack.top();
        singlestack.pop();
        int k = singlestack.empty()? -1:singlestack.top();
        int curArea = (len-k-1)*height[j];
        maxArea = max(curArea, maxArea);
    }
    return maxArea;
}

int maxRecSize(int** map, int row, int col)
{
    int maxArea = 0;
    int *height = new int[col]();
    for(int i=0;i<row;i++)
    {
       for(int j=0;j<col;j++)
            height[j] = *((int*)map+i*col+j)==0? 0:height[j]+1; // 当前数为0则为0，为1则加上之前的数。
        maxArea = max(maxRecFromBottom(height,col), maxArea);
    }
    delete height;
    return maxArea;
}

int main(void)
{
    int arr[][4] = {{1,0,1,1},{1,1,1,1},{1,1,1,0}};
    cout<<maxRecSize((int **)arr,3,4)<<endl;
    return 0;
}