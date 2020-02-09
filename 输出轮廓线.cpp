// 给定一个N行3列二维数组，每一行表示有一座大楼，一共有N座大楼。所有大楼的底部都坐落在X轴上，每一行的
// 三个值(a,b,c)代表每座大楼的从(a,0)点开始，到(b,0)点结束，高度为c，输入的数据可以保证a<b，且
// a,b,c均为正数，大楼之间可以有重合。请输出整体的轮廓线。
// 例子：给定一个二维数组[[1,3,3]],[2,4,4],[5,6,1]]
// 输出为轮廓线[[1,2,3],[2,4,4],[5,6,1]]

// 【解决方法】
// 利用红黑树
// 原题变为[1,3,UP],[3,3,DOWN],[2,4,UP],[4,4,DOWN],[5,1,UP],[6,1,DOWN]
// 依据位置排序
// [1,3,UP],[2,4,UP],[3,3,DOWN],[4,4,DOWN],[5,1,UP],[6,1,DOWN]
// 轮廓是最大高度发生变化
// key为高度，value为次数
// 插入时看看最大高度是否发生变化

#include <map>
#include <list>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Node
{
public:
    bool isUp;
    int posi;
    int h;
    Node()
    {

    }
    Node(bool Up, int position, int height)
    {
        isUp = Up;
        posi = position;
        h = height;
    }
};

bool cmp(Node o1, Node o2)
{
    if(o1.posi != o2.posi)
        return o1.posi < o2.posi;
    if(o1.isUp != o2.isUp)
        return o1.isUp? -1:1;
    return false;
}

vector<vector<int>> buildingOutline(int** buildings, int row)
{
    vector<Node> nodes;
    for(int i=0;i<row;i++)
    {
        nodes.push_back(Node(true, *((int*)buildings+i*3), *((int*)buildings+i*3+2)));
        nodes.push_back(Node(false, *((int*)buildings+i*3+1), *((int*)buildings+i*3+2)));
    }
    //按位置排序
    sort(nodes.begin(),nodes.end(),cmp);
    //htMap高度信息     pmMap每个位置的最大高度
    map<int, int> htMap, pmMap;
    for(int i=0; i<nodes.size();i++)
    {
        //htMap更新
        if(nodes[i].isUp)
            if(htMap.find(nodes[i].h)==htMap.end())
                htMap.insert(pair<int,int>(nodes[i].h,1));
            else
                htMap[nodes[i].h]++;
        else
            if(htMap.find(nodes[i].h)!=htMap.end())
                if(htMap[nodes[i].h] == 1)
                    htMap.erase(nodes[i].h);
                else
                    htMap[nodes[i].h]--;
        //pmMap更新
        if(htMap.empty())
            pmMap.insert(pair<int,int>(nodes[i].posi,0));
        else
            pmMap.insert(pair<int,int>(nodes[i].posi,htMap.rbegin()->first));
    }
    vector<vector<int>> res;
    int start=0;
    //之前的高度
    int height=0;
    for(auto it:pmMap)
    {
        int curPosition = it.first;
        int curMaxHeight = it.second;
        if(curMaxHeight != height)
        {
            //高度为0轮廓线刚开始，不能生成记录
            if(height !=0)
            {
                vector<int> newRecord;
                newRecord.push_back(start);
                newRecord.push_back(curPosition);
                newRecord.push_back(height);
                res.push_back(newRecord);
            }
            start = curPosition;
            height = curMaxHeight;
        }
    }
    return res;
}

int main(void)
{
    int arr[][3]={{1,3,3},{2,4,4},{5,6,1}};
    vector<vector<int>> res = buildingOutline((int**)arr,3);
    for(auto it:res)
    {
        for(auto y:it)
            cout<<y<<" ";
        cout<<endl;
    }
    return 0;
}