// 一块金条切成两半,是需要花费和长度数值一样的铜板的。比如长度为20的
// 金条,不管切成长度多大的两半,都要花费20个铜板。一群人想整分整块金
// 条,怎么分最省铜板?
// 例如,给定数组{10,20,30},代表一共三个人,整块金条长度为10+20+30=60.
// 金条要分成10,20,30三个部分。
// 如果,
// 先把长度60的金条分成10和50,花费60
// 再把长度50的金条分成20和30,花费50
// 一共花费110铜板。
// 但是如果,
// 先把长度60的金条分成30和30,花费60
// 再把长度30金条分成10和20,花费30
// 一共花费90铜板。
// 输入一个数组,返回分割的最小代价。

//求解思路：哈夫曼编码作贪心策略

#include <iostream>
#include <vector>
#include <queue>

int lessMoney(const std::vector<int>& arr) {
    std::priority_queue<int, std::vector<int>, std::greater<int> > minHeap;   // min heap
    for (auto it: arr) {
        minHeap.push(it);   // all of arr push in minHeap;
    }
    int res = 0;
    while (minHeap.size() > 1) {
        int top1 = minHeap.top();
        minHeap.pop();
        int top2 = minHeap.top();
        minHeap.pop();
        res += top1 + top2;
        minHeap.push(top1 + top2);
    }

    return res;
}

int main()
{
//    std::vector<int> test1 = {10, 20, 30};
    std::vector<int> test1 = { 1, 2, 6, 4, 3, 7, 1, 8 };
    int res1 = lessMoney(test1);
//    int res2 = lessMoney(test2);
    std::cout << "test1: " << res1 << std::endl;
//    std::cout << "test2: " << res2 << std::endl;
    return 0;
}