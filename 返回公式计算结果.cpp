// 【题目】
// 给定一个字符串str，str表示一个公式，公式里可能有整数、加减乘除符号和左右括号，返回公式的计算结果。
// 【举例】
// str="48*((70-65)-43)+8*1"，返回-1816。
// str="3+1*4"，返回7。str="3+(1*4)"，返回7。
// 【说明】
// 1.可以认为给定的字符串一定是正确的公式，即不需要对str做公式有效性检查。
// 2.如果是负数，就需要用括号括起来，比如"4*(-3)"。但如果负数作为公式的开头或括号部分的开头，则可以没有括号，比如
// "-3*4"和"(-3*4)"都是合法的。
// 3.不用考虑计算过程中会发生溢出的情况
// 【思路】
// 建立栈，将数字和运算符号全部压入栈
// 放入栈之前判断栈顶是不是乘除，是乘除的话将栈中的东西替换进栈
// 遇到括号调用函数算括号里的所有，传入的参数为左括号下一位置，返回值为计算的结果和右括号位置


#include <iostream>
#include <stack>
#include <string>
#include <deque>

using namespace std;

int* value(string str, int i);
void addNum(deque<string>& que, int num);
int getNum(deque<string>& que);

//返回数组长度为2
//value[0]为计算结果
//value[1]为算到哪个位置
int* value(string str, int i)
{
    deque<string> que;
    int pre = 0;
    int* b = NULL;
    //i位置遇到右括号和终止条件时停止
    while(i < str.length() && str[i]!=')')
    {
        //在遇到符号前记录数字
        if(str[i] >= '0' && str[i] <= '9')
            pre = pre*10 + str[i++] - '0';
        //遇到的不是左括号，则遇到了加减乘除，则收集起来
        else if(str[i] != '(')
        {
            addNum(que, pre);
            string s(1,str[i]);
            que.push_back(s);
            i++;
            //之前pre收集结果为0
            pre = 0;
        }
        //当前i位置遇到了左括号，进递归
        else
        {
            //递归过程
            b = value(str, i+1);
            //pre记录计算结果
            pre = b[0];
            //i计算现在需要开始计算的位置
            i = b[1]+1;
        }
    }
    addNum(que, pre);
    int *res = new int[2]{getNum(que),i};
    return res;
}

void addNum(deque<string>& que, int num)
{
    if(!que.empty())
    {
        int cur =0;
        string top = que.back();
        que.pop_back();
        if(top == "+" || top == "-")
            que.push_back(top);
        else
        {
            cur = atoi(que.back().c_str());
            que.pop_back();
            num = top == "*"? (cur*num) : (cur/num);
        }
    }
    que.push_back(to_string(num));
}

int getNum(deque<string>& que)
{
    int res = 0;
    bool add = true;
    string cur = "";
    int num =0;
    while(!que.empty())
    {
        cur = que.front();
        que.pop_front();
        if(cur == "+")
            add = true;
        else if(cur == "-")
            add = false;
        else
        {
            num = atoi(cur.c_str());
            res += add? num : (-num);
        }    
    }
    return res;
}

int main(void)
{
//    string str = "5+7-8*9+4-(3*6)-5+7";
//    string str = "48*((70-65)-43)+8*1";
//    string str="3+1*4";
//    string str = "4*(-3)";
//    string str = "-3*4";
    string str = "(-3)*4";
    cout<<value(str,0)[0]<<endl;
    return 0;
}