// 一些项目要占用一个会议室宣讲，会议室不能同时容纳两个项目的宣讲。
// 给你每一个项目开始的时间和结束的时间（给你一个数组，里面是一个个具体的项目），
// 你来安排宣讲的日成，要求会议室进行的宣讲的场次最多。返回这个最多的宣讲场次。

//解决方案：贪心策略 先安排早结束的，淘汰掉因为早结束的项目而不能做的项目

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Program
{
public:
    int start;
    int end;
    Program(int start, int end)
    {
        this->start=start;
        this->end=end;
    }
};

bool cmp(Program x, Program y)
{
    return x.end>y.end;
}

int bestArrange(vector<Program> programs, int start)
{
    sort(programs.begin(),programs.end(),cmp);
    int res = 0;
    for(int i=0;i<programs.size();i++)
    {
        if(start <= programs[i].start)
        {
            res++;
            start = programs[i].end;
        }
    }
    return res;
}

int main(void) {
    
    return 0;
}