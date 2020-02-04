// 给定两个数组w和v,两个数组长度相等,w[i]表示第i件商品的
// 重量,v[i]表示第i件商品的价值。
// 再给定一个整数bag,要求你挑选商品的重量加起来一定不能超
// 过bag,返回满足这个条件下,你能获得的最大价值。

#include <iostream>
using namespace std;

int maxValue(int* c, int* p, int i, int bag, int len) 
{
	if(i == len)
        return 0;
    if(c[i]>bag)
        return 0;
    int res1 = maxValue(c, p, i+1, bag, len);
    int res2 = maxValue(c, p, i+1, bag-c[i], len) + p[i];
    return max(res1, res2);
}

int maxValueDP(int* c, int* p, int bag, int len) 
{
    int** dp = new int*[len + 1];
    for(int i=0;i<len+1;i++)
        dp[i] = new int[bag + 1];
    for (int i = len - 1; i >= 0; i--) {
        for (int j = bag; j >= 0; j--) {
            dp[i][j] = dp[i + 1][j];
            if (j + c[i] <= bag) {
                dp[i][j] = max(dp[i][j], p[i] + dp[i + 1][j + c[i]]);
            }
        }
    }
    return dp[0][0];
}

int main(void) 
{
    int c[4] = { 3, 2, 4, 7 };
    int p[4] = { 5, 6, 3, 19 };
    int bag = 11;
    cout<<maxValue(c, p, 0, bag, 4)<<endl;
    cout<<maxValueDP(c, p, bag, 4)<<endl;
   return 0;
}