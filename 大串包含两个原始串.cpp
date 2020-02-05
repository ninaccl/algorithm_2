// KMP算法拓展
// 给定一个字符串str1,只能往str1的后面添加字符变成str2。
// 要求1:str2必须包含两个str1,两个str1可以有重合,但是不能以同一个位置开头。
// 要求2:str2尽量短
// 最终返回str2
// 举例:
// str1 = 123,str2 = 123123 时,包含两个str1,且不以相同位置开头,且str2最短。
// str1 = 123123,str2 = 123123123 时,包含两个str1,且不以相同位置开头,且str2最短。
// str1 = 111,str2 = 1111 时,包含两个str1,且不以相同位置开头,且str2最短。

#include <string>
#include <iostream>

using namespace std;

void getMaxStr(string s)
{
    int len = s.length()+1;
    int* next = new int[len]{-1,0};
    int i = 2;
    int cn = 0;
    while(i<len)
    {
        if(s[i-1]==s[cn])
            next[i++]=++cn;
        else if(cn > 0 )
            cn = next[cn];
        else
            next[i++] = 0;   
    }
    string res;
    res = s + s.substr(next[len-1]);
    delete []next;
    cout<<res<<endl;
}

int main(void)
{
    string str = "111";
    getMaxStr(str);
    return 0;
}