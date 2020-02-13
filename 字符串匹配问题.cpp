// 字符串匹配问题 
// 【题目】 
// 给定字符串str，其中绝对不含有字符'.'和'*'。再给定字符串exp，
// 其中可以含有'.'或'*'，'*'字符不能是exp的首字符，并且任意两个 '*'字符不相邻。
// exp中的'.'代表任何一个字符，exp中的'*'表示'*' 的前一个字符可以有0个或者多个。
// 请写一个函数，判断str是否能被 exp匹配。 
// 【举例】 str="abc"，exp="abc"，返回true。 
// str="abc"，exp="a.c"，exp中单个'.'可以代表任意字符，所以返回 true。 
// str="abcd"，exp=".*"。exp中'*'的前一个字符是'.'，所以可表示任 
// 意数量的'.'字符，当exp是"...."时与"abcd"匹配，返回true。 
// str=""，exp="..*"。exp中'*'的前一个字符是'.'，可表示任意数量 
// 的'.'字符，但是".*"之前还有一个'.'字符，该字符不受'*'的影响， 
// 所以str起码有一个字符才能被exp匹配。所以返回false。

// 【思路】
// 定义一个函数，str以i开始的字符串是否能以exp以j开头的字符串表示
// 三种情况：
// 1.j是最后一个字符
// 2.j+1上有字符，不是*
//        exp的j位置字符必须与str的i字符配上（要么是.要么一样），之后看下一位置，可以进递归
// 3.j+1上有字符，是*

#include <iostream>
#include <string>

using namespace std;

//暴力递归
//str[i...一直到最后]的字符串，能不能被exp[j...一直到最后]的字符串匹配
bool process(string str, string exp, int i, int j)
{
    //j位置到最后能否匹配上
    if(j == exp.length())
        return i == str.length();
    //j上面还有字符，考察j+1的情况
    if(j+1 == exp.length() || exp[j+1] != '*')
    {
        //首先j位置有不是*的字符，i不能到最后
        //其次，exp[j]需要可以匹配str[i]，即字符相等或者等于.
        //最后，后面的字符需要比对成功
        return i!= str.length() && (exp[j] == str[i] || exp[j] == '.') && process(str,exp,i+1,j+1);
    }
    //while发生隐含逻辑是exp的j+1位置上有字符且是*
    while(i!=str.length() && (exp[j]==str[i] || exp[j] == '.'))
    {
        if(process(str, exp, i, j+2))
            return true;
        i++;
    }
    //当前配不上，放在后面解决，假设当前*指示前面字符0个
    return process(str, exp, i, j+2);
}

//DP
// i和j的二维dp表
// 纵为i，横为j。i,j指字符串长度。
// 目标是0，0状态
// basic case：当纵坐标为j时，只有横坐标为i的时候才为true，其余全为false
// 普遍状况：依赖(i+1，j+1)和j+2列包含i以下的位置
// 所以需要倒数两列和最后一行
// 倒数第二列，表示exp剩一个字符，则str剩1个字符（横坐标为i-1）时需要判断是否相等或为.，其余行全为false
// 最后一行，表示str用尽，exp剩下某些后缀。a*b*c*的形式可以为TRUE，范式断掉的话直接为FALSE

bool isValid(string str, string exp)
{
    for(int i=0;i<str.length();i++)
        if(str[i]=='*'||str[i]=='.')
            return false;
    for(int i=0;i<exp.length();i++)
        if(exp[i]=='*' && ( i==0 || exp[i-1]=='*'))
            return false;
    return true;
}

bool** initDPMap(string str, string exp)
{
    int slen = str.length();
    int elen = exp.length();
    bool **dp = new bool*[slen+1];
    for(int i=0;i<slen+1;i++)
        dp[i] = new bool[elen+1];
    dp[slen][elen]=true;
    for(int j=elen-2;j>-1;j=j-2)
    {
        if(exp[j]!='*' && exp[j+1]=='*')
            dp[slen][j]=true;
        else
            break;
    }
    if(slen>0 && elen>0)
    {
        if(exp[elen-1]=='.' || exp[elen-1] == str[slen-1])
            dp[slen-1][elen-1]=true;
    }
    return dp;
}

bool isMatchDP(string str, string exp)
{
    if(str.length()==0 || exp.length()==0)
        return false;
    if(!isValid(str, exp))
        return false;
    bool **dp = initDPMap(str,exp);
    for(int i=str.length()-1 ;i>-1;i--)
    {
        for(int j=exp.length()-2;j>-1;j--)
        {
            if(exp[j+1]!='*')
                dp[i][j]=(str[i]==exp[j] || exp[j]=='.') && dp[i+1][j+1];
            else
            {
                int si=i;
                while(si!=str.length() && (str[si]==exp[j] || exp[j]=='.'))
                {
                    if(dp[si][j+2])
                    {
                        dp[i][j]=true;
                        break;
                    }
                    si++;
                }
                if(dp[i][j]!=true)
                    dp[i][j]=dp[si][j+2];
            }   
        }
    }
    return dp[0][0];
}

int main(void)
{
    string str = "abcccdefg";
    string exp = "a.*bc.*d..*e.*";
    cout<<process(str, exp, 0, 0)<<endl;
    cout<<isMatchDP(str,exp)<<endl;
    return 0;
}