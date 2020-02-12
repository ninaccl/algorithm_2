// 【题目】
// 给定一个数组arr，全是正数；一个整数aim，求累加和等于aim的最长子数组，要求额外空间复杂度O(1)，时间
// 复杂度O(N)
// 【举例】
// arr=[3,2,1,5,1,1,1,1,1,1],aim=6;
// 【思路】全为正数可用双指针求解，不需要额外空间记录
// 双指针构建窗口，当前累加和小于aim，R往右动，累加和为6记录长度，L往右动，当前累加和大于aim，L往右动

#include <iostream>

using namespace std;

int getMaxLength(int *arr, int len, int aim)
{
    if(len == 0 || aim <= 0)
        return 0;
    int L = 0;
    int R = 0;
    int sum = arr[0];
    int maxlen = 0;
    while(R < len)
    {
        //累加和为6记录长度，L往右动
        if(sum == aim)
        {
            maxlen = max(maxlen, R-L+1);
            sum-=arr[L++];
        }
        //当前累加和小于aim，R往右动
        else if(sum < aim)
        {
            R++;
            if(R == len)
                break;
            sum += arr[R];
        }
        //当前累加和大于aim，L往右动
        else
        {
            sum -= arr[L++];
        } 
    }
    return maxlen;
}

int main(void)
{
    int arr[]={3,2,1,5,1,1,1,1,1,1};
    int aim = 6;
    int len = 10;
    cout<<getMaxLength(arr, len, aim)<<endl;
    return 0;
}