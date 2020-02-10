// 【题目】
// 一个公司的上下级关系是一棵多叉数，这个公司要举办年会，你作为组织者已经摸清了大家的心理，一个员工的直接上级如果
// 到场，这个员工肯定不会来。每个员工都有一个活跃度的值，决定谁来你会给这个员工发邀请函，怎么让舞会的气氛最活跃？
// 返回最大的活跃值。
//
// 【举例】
// 给定一个矩阵来表述这种关系
// matrix = [1,6 1,5 1,4]
// 这个矩阵的含义是：
// matrix[0]={1,6}，表示0这个员工的直接上级为1，0这个员工自己的活跃度为6
// matrix[1]={1,5}，表示1这个员工的直接上级为1（她自己是这个公司的最大boss），1这个员工自己的活跃度为5
// matrix[2]={1,4}，表示2这个员工的直接上级为1，2这个员工自己的活跃度为4
// 为了让晚会活跃度最大，应该让1不来，0和2来，最后返回活跃度为10

// 【可能性】
// 1.x来，则其子节点不能来，总活跃度为子节点不来的活跃度+x自己的活跃度
// 2.x不来，总活跃度为所有子节点为头的树最大的活跃度的和

#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    int huoyue;
    vector<Node> nexts;
    Node(){}
    Node(int huoyue_)
    {
        huoyue = huoyue_;
    }
};

class ReturnData
{
public:
    int lai_huoyue;
    int bulai_huoyue;
    ReturnData(){}
    ReturnData(int lai, int bulai)
    {
        lai_huoyue = lai;
        bulai_huoyue = bulai;
    }
};

ReturnData process(Node head)
{
    int lai_huoyue = head.huoyue;
    int bulai_huoyue = 0;

    for(int i = 0; i<head.nexts.size();i++)
    {
        Node next = head.nexts[i];
        ReturnData nextData = process(next);
        //可能性1
        lai_huoyue += nextData.bulai_huoyue;
        //可能性2
        bulai_huoyue += max(nextData.lai_huoyue,nextData.bulai_huoyue);
    }

    return ReturnData(lai_huoyue,bulai_huoyue);
}

int getMaxHuoyue(Node head)
{
    ReturnData data = process(head);
    return max(data.lai_huoyue, data.bulai_huoyue);
}