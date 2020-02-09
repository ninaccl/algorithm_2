// 例：数组为[3 2 1 0 1 2 3 0]
// 答案为 3 2 1 | 0 | 1 2 3| 0，为4个异或和为0的

// 异或操作满足交换律和结合律
// 0和任何数异或结果为n
// 任何数和自己异或结果为0

// 求以i结尾的最优划分方式（即划分出异或和为0的最多子数组）
// 有两种情况：
// 1)i所在部分是最优划分中异或和为0的部分，则以i结尾的最多个数和以i-1为结尾的最多个数一样
// 2)i所在部分是最优划分中异或和不为0的部分，则该部分的起始位置一定是离i最近的到i异或和为0的位置

// 如果从0到i的异或和为sum，则k位置为从0开始异或和为sum的下一位置

// 则两种情况的解分别为
// dp[i]=dp[i-1];
// dp[i]=dp[k-1]+1;

//参考等于给定数的最长子数组.cpp
// key记录异或和，value记录最晚位置

#include <iostream>
#include <unordered_map>

using namespace std;

int mostEOR(int *arr, int len)
{
    int ans=0;
    int yihuo=0;
    int *dp = new int[len]();
    unordered_map<int,int> xorposition;
    xorposition[0]=-1;
    for(int i=0;i<len;i++)
    {
        yihuo ^= arr[i];
        if(xorposition.find(yihuo)!=xorposition.end())
        {
            int pre = xorposition[yihuo];
            //判断是否为0,0自己单独异或为0
            dp[i] = pre==-1?1:(dp[pre]+1);
        }
        if(i>0)
            dp[i]=max(dp[i-1],dp[i]);
        xorposition[yihuo]=i;
        ans = max(ans,dp[i]);
    }
    return ans;
}

int main(void)
{
    int arr[]={3,2,1,0,1,2,3,0};
    cout<<mostEOR(arr,8)<<endl;
    return 0;
}