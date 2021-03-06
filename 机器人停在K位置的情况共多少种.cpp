// 【题目描述】
// 假设有排成一行的N个位置，记为1~N，开始时机器人在M位置，机器人可以往左或者往右走，如果机器人在1位置，
// 那么下一步机器人只能走到2位置，如果机器人在N位置，那么下一步机器人只能走到N-1位置。规定机器人只能走p步，
// 最终能来到k位置的方法有多少种。由于方案数可能比较大，所以答案需要对1e9+7取模。
// 【输入描述】
// 输出包括一行四个正整数N（2<=N<=5000）、M(1<=M<=N)、p(1<=K<=5000)、k(1<=P<=N)。
// 【输出描述】
// 输出一个整数，代表最终走到P的方法数对10^9+7109+7取模后的值。
// 【示例1】
// 输入
// 5 2 3 3
// 输出
// 3
// 说明
// 1).2->1,1->2,2->3
// 2).2->3,3->2,2->3
// 3).2->3,3->4,4->3
// 示例2
// 输入
// 1000 1 1000 1
// 输出
// 591137401
// 说明
// 注意答案要取模
// 备注:
// 时间复杂度O(n*k),空间复杂度O(N)。

#include <iostream>

using namespace std;

// N一共有1～N位置
// M来到的位置
// P可以走的步数
// K最终停在的位置
// 返回值：一共有多少种走法
int ways(int N, int M, int P, int K)
{
    if(N<2 || M<1 || M>N || P<0 || K<1 || K>N)
        return 0;
    if(P == 0)
        return M==K?1:0;
    int res = 0;
    if( M == 1)
        res = ways(N, M+1, P-1, K);
    else if(M == N)
        res = ways(N, M+1, P-1, K);
    else
        res = ways(N, M+1, P-1, K)+ways(N, M-1, P-1, K);
    return res;
}

// DP方法
// 纵向0-P，横向1-N
// 则纵向为0时，横向K位置为1，其余为0      if(P == 0) return M==K?1:0;
// 依赖为ways(N,M+1,P-1,K)+ways(N,M-1,P-1,K)
// 画图可看出其实是杨辉三角形
// 返回值为纵向为P，横向为M的值


int main(void)
{
    cout<<ways(5,2,3,3)<<endl;
    return 0;
}