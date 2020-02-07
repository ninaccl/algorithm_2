// 最大值减去最小值小于或等于num的子数组数量
// 【题目】
// 给定数组arr和整数num，共返回有多少个子数组满足如下情况：
// max(arr[i...j]) - min(arr[i...j]) <= num
// max(arr[i...j])表示子数组arr[i...j]中的最大值，min(arr[i...j])表示子数组arr[i...j]中的最小值
// 【要求】
// 如果数组长度为N，请实现时间复杂度为O(N)的解法

// 注意：子数组数量是O(N^2) N+...+1的等差序列

//比暴力求解改进：某数组达标，则其子数组都达标

#include <iostream>
#include <list>

using namespace std;

int getNum(int *arr, int num, int len)
{
    if(len<=0)
        return 0;
    list<int> qMin,qMax;
    int L = 0;
    int R = 0;
    int res = 0;
    while(L<len)
    {
        //当L确定时，R往右扩到不能再扩，停
        while(R<len)
        {
            while(!qMin.empty() && arr[qMin.back()] >= arr[R])
                qMin.pop_back();
            qMin.push_back(R);
            while(!qMax.empty() && arr[qMax.back()] <= arr[R])
                qMax.pop_back();
            qMax.push_back(R);
            if(arr[qMax.front()]-arr[qMin.front()] > num)
                break;
            R++;
        }
        //判断下标是否过期,因为L马上要缩一个位置
        if(qMin.front() == L)
            qMin.pop_front();
        if(qMax.front() == L)
            qMax.pop_front();
        res += R-L;
        L++;
    }
    return res;
}

int main(void)
{
    int arr[4] = {1,2,3,4};
    cout<<getNum(arr,3,4)<<endl;;
    return 0;
}