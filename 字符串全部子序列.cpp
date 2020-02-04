// 打印一个字符串的全部子序列,包括空字符串

#include <string>
#include <iostream>

using namespace std;

void printAllSub(string str, int i, string res)
{
    if(i == str.length())
    {
        cout<<res<<endl;
        return;
    }
    printAllSub(str, i+1, res);
    printAllSub(str, i+1, res+str[i]);
}

int main(void)
{
    string test = "abc";
    printAllSub(test, 0, "");
}