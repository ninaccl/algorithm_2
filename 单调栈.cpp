// 单调栈
// 找到每个位置的左边离它最近的比它大的，右边离它最近的比它大的

// 【解决方法】
// 栈底到栈顶从大到小放，类似窗口结构
// 当发现某个数无法压入，需要把栈顶的数弹出时，则它就为离栈顶指向的数右边最近的比它大的，栈顶在栈中下边的数为左
// 边离它最大的
// 数组遍历完，单独处理栈。则栈依次弹出，右边最大的为NULL，左边为栈下面的数。
// 栈中最后一个弹出的左右离它最大的都为NULL

// 特殊情况，相等的时候，在压入栈的时候若和栈顶元素相等，则把下标压在一起，栈顶元素原来空间再放一个下标

#include <iostream>
#include <stack>
#include <map>

using namespace std;

map<int, pair<int,int>> singleStack(int arr[], int len)
{
    map<int, pair<int,int>> res;
    stack<stack<int>> singlestack;
    for(int i=0;i<len;i++)
    {
        int flag = 0;
        while(!singlestack.empty())
        {
            if(arr[singlestack.top().top()] < arr[i])
            {
                stack<int> tobepop = singlestack.top();
                singlestack.pop();
                while(!tobepop.empty())
                {
                    pair<int, int> temp;
                    if(!singlestack.empty())
                        temp.first = singlestack.top().top();
                    else
                        temp.first = -1;
                    temp.second = i;
                    res[tobepop.top()] = temp;
                    tobepop.pop();
                }
            }
            else if(arr[singlestack.top().top()] == arr[i])
            {
                singlestack.top().push(i);
                flag = 1;
                break;
            }
            else
            {
                stack<int> tobeinsert;
                tobeinsert.push(i);
                singlestack.push(tobeinsert);
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
             stack<int> tobeinsert;
            tobeinsert.push(i);
            singlestack.push(tobeinsert);
        }
    }
    while(!singlestack.empty())
    {
        stack<int> tebeinsert;
        stack<int> tobepop = singlestack.top();
        singlestack.pop();
        while(!tobepop.empty())
        {
            pair<int, int> temp;
            if(!singlestack.empty())
                temp.first = singlestack.top().top();
            else
                temp.first = -1;
            temp.second = -1;
            res[tobepop.top()] = temp;
            tobepop.pop();
        }       
    }
    return res;
}

int main(void)
{
    //int arr[8] = {1,1,7,6,3,9,8,0};
    int arr[8] = {1,1,3,6,3,3,9,8};
    //int arr[8] = {5,5,5,5,5,5,5,5};
    map<int, pair<int,int>> res = singleStack(arr, 8);
    for(auto i:res)
    {
        cout<< arr[i.first] <<" left: ";
        if(i.second.first>-1)
            cout<<arr[i.second.first];
        else
            cout<<"NULL";
        cout<<" right: ";
        if(i.second.second>-1)
            cout<<arr[i.second.second];
        else
            cout<<"NULL";
        cout<<endl; 
    }
    return 0;
}