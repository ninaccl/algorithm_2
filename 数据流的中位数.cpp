// 注意：
// 对于取堆顶元素的操作的时间复杂度是常数级别的。
// 插入新节点时我们需要判断节点的值是否小于大根堆堆顶的值或者大于小根堆堆顶的值，
// 如果小于大根堆堆顶的值，那么节点应该插入大根堆，反过来应该插入小根堆。
// 每次插入新节点我们还需要判断两个堆之间的元素个数是否平衡。
// 插入新节点后，我们判断两个堆的元素个数，如果相差为2那么我们就要对堆进行调整。
// 比如新插入一个节点到小根堆中，而此时大根堆的个数+1小于小根堆的节点个数，
// 这个时候只需要将小根堆的堆顶元素弹出，然后将这个弹出的元素插入大根堆即可。反过来也是一样的操作。
// 为什么可以这样做呢？
// 这是因为我们说了小根堆保存的是较大的n/2个数，而小根堆的堆顶是小根堆中最小的元素，
// 同时也是大根堆中最大的元素，
// 因此我们将这个堆顶元素弹出并插入大根堆的操作并不会破坏“小根堆保存较大的n/2个数，
// 大根堆保存较小的n/2”这样的前提。


#include <iostream>
#include <vector>
#include <queue>

class MedianFinder {
 private:
     std::priority_queue<int, std::vector<int>, std::less<int> > maxHeap;
     std::priority_queue<int, std::vector<int>, std::greater<int> > minHeap;
 public:
    /** initialize your data structure here. */
    MedianFinder() {

    }

    void addNum(int num) {
        if (maxHeap.empty()) {  // if maxHeap is empty, push it directly
            maxHeap.push(num);
            return;
        }
        if (maxHeap.top()>= num) {  // small number push to maxHeap
            maxHeap.push(num);
        } 
        else {    // max number push to minHeap
            if (minHeap.empty()) {  // if minHeap is empty, push it directly
                minHeap.push(num);
                return;
            }
            if (minHeap.top() >= num) { // push it to maxHeap
                maxHeap.push(num);
            } else {    // push it to minHeap
                minHeap.push(num);
            }
        }
        // adjust maxHeap and minHeap, ensure the different size <= 1
        if (maxHeap.size() == minHeap.size() + 2) { // maxHeap - minHeap = 2, adjust
            int maxTmp = maxHeap.top();
            minHeap.push(maxTmp);
            maxHeap.pop();
        }
        if (minHeap.size() == maxHeap.size() + 2) { // minHeap - maxHeap = 2, adjust
            int minTmp = minHeap.top();
            maxHeap.push(minTmp);
            minHeap.pop();
        }

    }

    double findMedian() {
        int maxHeapSize = maxHeap.size();
        int minHeapSize = minHeap.size();
        if (maxHeapSize + minHeapSize == 0) {   // empty return 0.0
            return 0.0;
        }
        int maxHeapTop = maxHeap.top();
        int minHeapTop = minHeap.top();
        if (((maxHeapSize + minHeapSize) & 1) == 0) {
            return (maxHeapTop + minHeapTop) / 2.0;
        }
        else {    // total sum is odd
            return maxHeapSize > minHeapSize ? (double)maxHeapTop : (double)minHeapTop;
        }
    }
};

 int main () {
    MedianFinder* obj = new MedianFinder();
    obj->addNum(1);
    obj->addNum(2);
    std::cout << obj->findMedian() << std::endl;
    obj->addNum(3);
    std::cout << obj->findMedian() << std::endl;
    return 0;
 }