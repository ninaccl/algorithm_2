// 生成窗口最大值数组
// 【题目】
// 有一个整型数组arr和一个大小为w的窗口从数组的最左边滑到最右边,窗口每次向右边滑一个
// 位置。
// 例如,数组为[4,3,5,4,3,3,6,7],窗口大小为3时:
// [4 3 5] 4 3 3 6 7    窗口中最大值为5
// 4 [3 5 4] 3 3 6 7    窗口中最大值为5
// 4 3 [5 4 3] 3 6 7    窗口中最大值为5
// 4 3 5 [4 3 3] 6 7    窗口中最大值为4
// 4 3 5 4 [3 3 6] 7    窗口中最大值为6
// 4 3 5 4 3 [3 6 7]    窗口中最大值为7
// 如果数组长度为n,窗口大小为w,则一共产生n-w+1个窗口的最大值。
// 请实现一个函数。
// 输入:整型数组arr,窗口大小为w。
// 输出:一个长度为n-w+1的数组res,res[i]表示每一种窗口状态下的最大值。
// 以本题为例,结果应该返回{5,5,5,4,6,7}。

// 注意：窗口缩的时候是左边窗口动，所以右边的值永远晚过期
// 窗口L和R不能回退，L要小于R
// 由于值分辨不出是哪一个，所以一定要存下标，值可以不用存（因为通过下标可以拿到值）

#include <iostream>
#include <list>
using namespace std;

int* getMaxWindow(int* arr, int w, int len)
{
    if(len < w || w < 1)
        return nullptr;
    list<int> qMax;
    int *res = new int[len-w+1];
    int index = 0;
    for(int i = 0; i<len;i++)
    {
        while(!qMax.empty() && arr[qMax.back()]<=arr[i])
            qMax.pop_back();
        qMax.push_back(i);
        //头坐标过期,弹出
        if(qMax.front() == i-w)
            qMax.pop_front();
        //是否形成窗口
        if(i >= w-1)
            res[index++] = arr[qMax.front()];
    }
    return res;
}

int main(void)
{
    int arr[8] = {4,3,5,4,3,3,6,7};
    int *res = getMaxWindow(arr,3,8);
    for(int i=0;i<6;i++)
        cout<<res[i]<<" ";
    cout<<endl;
    return 0;
}