// 给你一个二维数组,二维数组中的每个数都是正数,要求从左上
// 角走到右下角,每一步只能向右或者向下。沿途经过的数字要累
// 加起来。返回最小的路径和。

#include <iostream>

using namespace std;

//暴力递归法
//从(i,j)出发，到达最右下角，最小路径和
int walk(int **matrix, int i, int j, int row, int col)
{
    if(i == row-1 && j == col-1)
        return *((int*)matrix + i*col + j);
    if(i == row-1)
        return *((int*)matrix + i*col + j) + walk(matrix, i, j+1, row, col);
    if(j == col-1)
        return *((int*)matrix + i*col + j) + walk(matrix, i+1, j, row, col);
    //右边位置到右下角的最短路径和
    int right = *((int*)matrix + i*col + j) + walk(matrix, i, j+1, row, col);
    //下边位置到右下角的最短路径和
    int down = *((int*)matrix + i*col + j) + walk(matrix, i+1, j, row, col);
    return min(right, down);
}

int walkDP(int **matrix, int row, int col)
{
    if(row == 0 && col == 0)
        return 0;
    int **dp = new int*[row];
    for(int i=0;i<row;i++)
        dp[i] = new int[col];
    dp[row-1][col-1] = *((int*)matrix+(row-1)*col+col-1);
    for(int i=row-2;i>=0;i--)
        dp[i][col-1] = *((int*)matrix+i*col+col-1)+dp[i+1][col-1];
    for(int j=col-2;j>=0;j--)
        dp[row-1][j] = *((int*)matrix+(row-1)*col+j)+dp[row-1][j+1];
    for(int i=row-2;i>=0;i--)
        for(int j=row-2;j>=0;j--)
            dp[i][j] =  *((int*)matrix+i*col+j) + min(dp[i+1][j],dp[i][j+1]);
    int res = dp[0][0];
    for(int i=0;i<row;i++)
        delete []dp[i];
    delete []dp;
    return res;
}


int main(void)
{
    int m[][4]={{1,3,5,9},{8,1,3,4},{5,0,6,1},{8,8,4,0}};
    int m1[][4]={3,1,0,2,4,3,2,1,5,2,1,0};
    int res1 = walk((int **)m,0,0,4,4);
    int res2 = walkDP((int **)m, 4, 4);
    cout<<res1<<" "<<res2<<endl;
    return 0;
}