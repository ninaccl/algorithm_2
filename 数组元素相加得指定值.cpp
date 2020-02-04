// 给你一个数组arr,和一个整数aim。如果可以任意选择arr中的
// 数字,能不能累加得到aim,返回true或者false

#include <iostream>

using namespace std;

bool isSum(int *arr, int i, int sum, int aim, int len)
{
    if(i == len)
        return sum == aim;
    return isSum(arr, i+1, sum, aim, len) || isSum(arr, i+1, sum+arr[i], aim, len);
}

//动态规划表，横坐标sum+1，纵坐标为数组长度+1
int isSumDP(int *arr, int aim, int len)
{
    int sum=0;
    for(int i=0;i<len;i++)
        sum+=arr[i];
    if(sum<aim)
        return false;
    bool **dp = new bool*[len+1];
    for(int i=0;i<len+1;i++)
        dp[i] = new bool[sum+1]();

    for(int j=0;j<sum+1;j++)
    {
        if(j==aim)
            dp[len][j] = true;
    }   
    for(int i = len-1;i>=0;i--)
        for(int j = aim;j>=0;j--)
        {
            dp[i][j]=dp[i+1][j];
            if(j+arr[i]<=aim)
                dp[i][j]=dp[i+1][j]||dp[i+1][j+arr[i]];
        }
    return dp[0][0];
}


int main(void)
{
    int arr[]={1,4,8};
    int aim = 14;
    bool res1 = isSum(arr,0,0,aim,3);
    bool res2 = isSumDP(arr,aim,3);
    cout<<res1<<" "<<res2<<endl;
    return 0;
}