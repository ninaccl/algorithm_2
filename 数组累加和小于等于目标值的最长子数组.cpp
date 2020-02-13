// 【题目】
// 给定一个数组arr，值可正，可负，可0；一个整数aim，求累加和小于等于aim的，最长子数组，要求时间复杂度O(N)
// 【示例】
// arr = [... 7    5   4   -3  -1]
// index     N-5  N-4 N-3  N-2 N-1
// min_sum [  7    5   0   -4  -1] 以包含对应index往后得到的最小累加和
// min_sum_index
//         [ N-5  N-4 N-1  N-1 N-1]    以对应index往后得到最小累加和的最右index

// arr =   [1    -3      4     -5     7    3   -6   9],aim = 6
// min_sum=[-3   -4     -1     -5     4   -3   -6   9]
// min_index=[3   3      3      3     6    6    6   7]
// 从index=0开始，sum = -3,min_index = 3
// 从index=4开始，sum = -3+4 = 1,min_index = 6
// 从index=7开始，sum = 1+9 = 10 > aim，停
// 得到index=0开头的最长长度
// 之后解决1开头的，
// 窗口把1剔出去，sum = sum-arr[0],min_index不变
// 看min_index+1之后的部分能不能进来，能进来继续(窗口不回退，因为只关心更长的部分)
// 进不来的话直接看2开头部分
// 窗口把1剔出去，sum = sum-arr[1]

#include <iostream>

using namespace std;

int maxLength(int* arr, int aim, int len)
{
    if(len < 1)
        return 0 ;
    int *sums = new int[len];   //以包含对应index往后得到的最小累加和
    int *ends = new int[len];   //以对应index往后得到最小累加和的最右index
    sums[len-1] = arr[len-1];
    ends[len-1] = len-1;
    for(int i = len-2; i>=0; i--)
    {
        if(sums[i+1] < 0)
        {
            sums[i] = arr[i] + sums[i+1];
            ends[i] = ends[i+1];
        }
        else
        {
            sums[i] = arr[i];
            ends[i] = i;
        }   
    }

    //准备工作做完，开始从每位开始求最长长度

    int R = 0;  //右边界
    int sum = 0;    //start到R的值
    int res = 0;    //返回的最大长度
    for(int start=0; start<len; start++)
    {
        while(R<len && sum+sums[R]<=aim)
        {
            sum += sums[R];
            R = ends[R] + 1;
        }
        //R == start窗口没东西，因为R指向下一次要包含的头位置
        sums -= R>start ? arr[start] : 0;
        res = max(res, R-start);
        //防止当前的sums一开始就大于aim，R扩不出去的时候，R直接往下跳
        R = max(R, start+1);
    }
    return res;
}


int main(void)
{
    int arr[] = {1,-3,4,-5,7,3,-6,9};
    int aim = 6;
    cout<<maxLength(arr, aim, 8)<<endl;
}