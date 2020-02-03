//汉诺塔问题
//打印n层汉诺塔从最左边移动到最右边的全部过程

#include <string>
#include <iostream>
using namespace std;

//N:1~N
void process(int N, string from, string to, string help)
{
    if(N==1)
        cout<<"Move 1 from "<<from<<" to "<<to<<endl;
    else
    {
        process(N-1, from, help, to);
        cout<<"Move "<<N<<" from "<<from<<" to "<<to<<endl;
        process(N-1, help, to, from);
    }
    
}

int main(void)
{
    process(3,"左","右","中");
}