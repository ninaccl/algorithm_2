// 【题目】
// 据说著名犹太历史学家Josephus有过如下故事：在罗马人占领乔塔帕特后，
// 39个犹太人和Josephus及他的朋友躲进一个洞里，39个犹太人决定宁愿死也不要被敌人抓到，
// 于是决定了一个自杀方式，41个人排成一个圆圈，由第一个人开始报数，报数到3的人就自杀，
// 再由下一个人重新报1，报数到3的人就自杀，这样依次下去，知道剩下最后一个人时，
// 那个人可以自由选择自己的命运。这就是著名的约瑟夫问题。现在请用单向链表描述该结构并呈现整个自杀过程。
// 输入：一个环形单向链表的头节点head和报数的值m
// 返回：最后生存下来的节点，且这个节点自己组成环形单向链表，其他节点都删掉。
// 进阶：如果链表节点数为N，想在时间复杂度为O(N)时完成原问题的要求，该怎么实现？

// 【思路】
// 存活的节点在只剩它一个时为1号
// 可以往上找到最终生存的节点在原始链表中的编号
// 链表长度为i，编号和报的数之间的关系 编号=(报数-1)%i+1（当长度为i的时候）
// 旧号（长度为i），新号（长度i-1），需要举例发现
// 旧号 1 2 3 4 5 6 7 8 9，假设m=3，S=3被干掉
// 新号 7 8 x 1 2 3 4 5 6
// 旧号 = (新号-1+S)%i+1
// S杀掉的编号，数到m就杀人，i为每一步的长度

// 第一次反推：旧号 = (1-1+S)%i+1 S=(m-1)%i+1
// 算N次

#include <iostream>

using namespace std;

int getLive(int i, int m)
{
    if(i == 1)
        return 1;
    return (getLive(i-1, m)+m-1)%i+1;
}

int main(void)
{
    int i = 4, m = 7;
    cout<<getLive(i,m)<<endl; 
    return 0;
}