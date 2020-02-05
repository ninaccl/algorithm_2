// KMP方法
// 判断str2是否为str1子串

#include <iostream>
#include <string>

using namespace std;

int* getNextArray(string str)
{
    int len = str.length();
    int* next = new int[len]{-1,0,};
    int i = 2;  // i指示当前位置
    int cn = 0; // cn指示跳的位置
    while(i<len) 
    {
        if(str[i-1] == str[cn])
            next[i++] = ++cn;
        else if(cn>0)
            cn = next[cn];
        else
            next[i++] = 0;
    }
    return next;
}

int getIndexof(string str1,string str2 )
{
    int i1 = 0, i2 = 0;
    int* next = getNextArray(str2);
    while(i1 <str1.length() && i2 < str2.length())
    {
        if(str1[i1] == str2[i2])
        {
            i1++;
            i2++;
        }
        else if(next[i2] == -1) //-1指string2零位置的字符
            i1++;
        else
            i2 = next[i2];
    }
    delete []next;
    return i2 == str2.length() ? i1-i2: -1;
}


int main(void)
{
    string s1 = "abcabcababaccc";
    string s2 = "ababa";
    int index = getIndexof(s1, s2);
    cout << index <<endl;
    return 0;
}