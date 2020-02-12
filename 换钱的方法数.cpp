// 【题目】
// 给定数组arr，arr中所有的值都为正数且不重复。每个值代表一种面值的货币，每种面值的货币可以使用任意张，再给定
// 一个整数aim代表要找的钱数，求换钱有多少种方法。
// 【举例】
// arr=[5,10,25,1]，aim=0。
// 组成0元的方法有1种，就是所有面值的货币都不用。所以返回1。
// arr=[5,10,25,1],aim=15。
// 组成15元的方法有6种，分别为3张5元、1张10元+1张5元、1张10元+5张1元、10张1元+1张5元、
// 2张5元+5张1元和15张1元。所以返回6。
// arr=[3,5],aim=2。
// 任何方法都无法组成2元。所以返回0。

#include <iostream>
#include <unordered_map>

using namespace std;

//arr: 钱的数组
//index: 可以任意自由使用index及其之后所有的钱
//aim: 目标前数
//返回值: 方法数
//暴力法
int process1(int* arr, int index, int aim, int len)
{
    int res = 0;
    //来到数组最后剩的钱为0为有效划分
    if(index == len)
        res = aim == 0 ? 1 : 0;
    else
        //当前位置任意张对应不同可能性
        for(int i = 0; arr[index] * i <= aim ; i++)
            res += process1(arr, index+1, aim-arr[index]*i, len);
    return res;
}


//key:"index_aim"
//value:返回值
unordered_map<string, int> map;

//注意到暴力递归中，index和aim固定，结果res是固定的
int process_map(int *arr, int index, int aim, int len)
{
    int res = 0;
    //来到数组最后剩的钱为0为有效划分
    if(index == len)
        res = aim == 0 ? 1 : 0;
    else
        //当前位置任意张对应不同可能性
        for(int i = 0; arr[index] * i <= aim ; i++)
        {
            int nextAim = aim - arr[index]*i;
            string key = to_string(index+1) + "_" +to_string(nextAim);
            //判断之前有没有算法
            if(map.find(key)!=map.end())
                res += map[key];
            else
                res += process1(arr, index+1, aim-arr[index]*i, len);
        }
    //避免重复计算
    string key = to_string(index) + "_" +to_string(aim);
    map[key] = res;       
    return res;    
}

// DP方法
// 以index和aim作出动态规划二维表
// 第0行最后一列则指向index=0，aim=目标aim(totalaim)的点，为最终需要求的值
// 接下来找不依赖于其他值的点，找到index = len的行，其aim = 0的格上填1，其余全为0
// 之后看位置依赖，即res += process1(arr, index+1, aim-arr[index]*i, len);
// 看出需要下一行的aim-arr[index]*i的各个位置
// 进一步优化，由于整体是从下往上，从左往右求解的。
// 则index,aim位置的点为index，aim-arr[index]的点加上index,aim下面位置的点
// 优化的原因在于前面已经累加过，不需要重复累加。

int dp(int*arr, int aim, int len)
{
    if(len<1 || aim<0)
        return 0;
    int **dp = new int*[len+1];
    for(int i = 0;i < len+1; i++)
        dp[i] = new int[aim+1]();
    //aim为0对任何index都有1种
    for(int i = 0;i<len+1;i++)
        dp[i][0] = 1;
    //优化思路，同行位置的点可先确定一部分
    for(int j = 1;arr[0]*j<=aim;j++ )
        dp[0][arr[0]*j]=1;
    for(int i = 1;i<len;i++)
        for(int j=1;j<=aim;j++)
        {
            dp[i][j] = dp[i-1][j];
            dp[i][j]+= j-arr[i]>=0? dp[i][j-arr[i]]:0;
        }
    return dp[len-1][aim];
}

int main(void)
{
    int arr[] = {5,10,25,1};
    int aim = 15;
    cout<<process1(arr,0,aim,4)<<endl;
    cout<<process_map(arr,0,aim,4)<<endl;
    cout<<dp(arr,aim,4)<<endl;
    return 0;
}