//母牛每年生一只母牛,新出生的母牛成长三年后也能每年生一只母牛,假设不会死。求N年后,母牛的数量。

#include <iostream>

using namespace std;

int cowNum(int i)
{
    if(i < 4)
        return i;
    int res = cowNum(i-1) + cowNum(i-3);
    return res;
}

int main(void)
{
    int res = cowNum(4);
    cout<<res<<endl;
    return 0;
}