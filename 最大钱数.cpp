// 输入:
// 参数1,正数数组costs
// 参数2,正数数组profits
// 参数3,正数k
// 参数4,正数m
// costs[i]表示i号项目的花费
// profits[i]表示i号项目在扣除花费之后还能挣到的钱(利润)
// k表示你不能并行、只能串行的最多做k个项目
// m表示你初始的资金
// 说明:你每做完一个项目,马上获得的收益,可以支持你去做下一个项目。
// 输出:
// 你最后获得的最大钱数。

//构造小根堆，谁花费低谁做小根堆。
//依次弹出小根堆头部，直到比m大
//弹出的进入大根堆，大根堆按照收益来排
//大根堆的头部是能做的项目里收益最高的

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node
{
public:
    int p;
    int c;
    Node()
    {
        p=0;
        c=0;
    }
    Node(int p, int c)
    {
        this->p = p;
        this->c = c;
    }
};

struct mincostcmp{
    bool operator()(Node x, Node y)
{
    return x.c > y.c;
}
};

struct maxprofittcmp{
    bool operator()(Node x, Node y)
{
    return x.p < y.p;
}
};


int findMaxMoney(int k, int m, int* profits, int* costs, int len)
{
    vector<Node> nodes;
    for(int i=0;i<len;i++)
    {
        nodes.push_back(Node(profits[i], costs[i]));
    }
    priority_queue<Node, vector<Node>, mincostcmp> mincostQ;
    priority_queue<Node, vector<Node>, maxprofittcmp> maxprofitQ;
    for(int i=0;i<len;i++)
        mincostQ.push(nodes[i]);
    for(int i=0;i<k;i++)
    {
        while(!mincostQ.empty() && mincostQ.top().c <= m)
        {
            maxprofitQ.push(mincostQ.top());
            mincostQ.pop();
        }
        if(maxprofitQ.empty())
            return m;
        m+=maxprofitQ.top().p;
        maxprofitQ.pop();           
    }
    return m;
}

int main(void)
{
    int costs[]={5,10,6,20};
    int profits[]={3,2,4,9};
    int len = 4;
    int k = 4;
    int m = 7;
    int res = findMaxMoney(k, m, profits, costs, len);
    cout<<res<<endl;
    return 0;
}