// 【题目】累加和为给定值的最长子数组
// 数组中的值有正有负
// 如[7,3,2,1,1,7,7,7]，aim为7
// 返回4

// 【思路】
// 以每位数结尾的最长子数组
// 如，数组共1000位，累加和为2000，求以1000位为结尾累加和为800的最长子数组
// 从0位开始加，数加到1200，则从该位到1000位的累加和必为800
// 用map求解，key为累加和，value为最早出现位置

#include <iostream>
#include <unordered_map>

using namespace std;

int maxLen(int* arr, int aim, int len)
{
    if(len <= 0)
        return 0;
    unordered_map<int, int> sumposition;
    sumposition[0]=-1;
    int maxlen = 0;
    int sum = 0;
    for(int i=0;i<len;i++)
    {
        sum+=arr[i];
        //查sum-aim的累加和是否出现过
        if(sumposition.find(sum-aim)!=sumposition.end())
            maxlen = max(maxlen, i-sumposition[sum-aim]);
        //累加和没出现过就加进去
        if(sumposition.find(sum)==sumposition.end())
            sumposition[sum] = i;
    }
    return maxlen;
}

int main(void)
{
//    int arr[]={7,3,2,1,1,7,-6,-1,7};
    int arr[]={7,3,2,1,1,7,7,7};
    cout<<maxLen(arr,7,8)<<endl;
    return 0;
}