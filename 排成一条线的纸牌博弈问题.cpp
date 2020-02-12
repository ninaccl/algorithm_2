// 【题目】
// 给定一个整型数组arr，代表数值不同的纸牌排成一条线。玩家A和玩家B依次拿走每张纸牌，规定玩家A先拿，玩家B后拿，
// 但是每个玩家每次只能拿走最左或最右的纸牌，玩家A和玩家B都绝顶聪明，请返回最后获胜者的分数。
// 【举例】
// arr=[1,2,100,4]
// 开始时玩家A只能拿走1或4。如果玩家A拿走1。则排列变为[2,100,4]，接下来玩家B可以拿走2或4，然后继续轮到玩家A。
// 如果开始时玩家A拿走4，则排列变为[1,2,100]，接下来玩家可以拿走1或100，然后继续轮到玩家A。玩家A作为绝顶聪明
// 的人不会先拿4，因为拿4之后，玩家B将拿走100。所以玩家A会先拿1，让排列变为[2,100,4]，接下来玩家B不管怎么选，
// 100都会被玩家A拿走。玩家A会获胜，分数为101。所以返回101。
// arr=[1,100,2]。
// 开始时玩家A不管是拿1还是2，玩家B作为绝顶聪明的人，都会把100拿走。玩家B会获胜，分数为100。所以返回100。

#include <iostream>

using namespace std;

//暴力递归
int f(int *arr, int i, int j);
int s(int *arr, int i, int j);

//first person
int f(int *arr, int i, int j)
{
    if(i == j)
        return arr[i];
    return max(arr[i] + s(arr, i+1, j), arr[j]+s(arr,i,j-1));
}

//second person
int s(int *arr, int i, int j)
{
    //i==j时第二个人不能选
    if(i==j)
        return 0;
    //否则第一个人为了赢，一定会使第二个人的值最小
    return min(f(arr, i+1,j),f(arr,i,j-1));
}

//dp表
// f一张，s一张
// 纵为i，横为j
// f和s都需要i=0，j=jmax的值。
// 且不可能出现i>j情况，左下角不用填

// 对角线上f为对应位的值，因为暴力递归中i==j返回arr[i]
// 对角线上s为0，因为暴力递归中i==j返回0
// 由暴力递归条件可以推出两张表可以对角线互推，直至填满表格

int main(void)
{
//    int arr[]={1,2,100,4};
    int arr[]={1,100,1};

    cout<<f(arr,0,2)<<" "<<s(arr,0,2)<<endl;
    cout<<max(f(arr,0,2),s(arr,0,2))<<endl;
    return 0;
}