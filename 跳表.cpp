// O(log(N))
// redis 为阉割后的跳表结构
// 每次插入时都用01概率决定层数。最左边的最小表的最大层数为掷出的实时最大层数。
// 低层的数多，高层的数少，在查找和插入时从高层往低层走，可以越过非常多低层的点。

#include<iostream>
#include<vector>

using namespace std;

class SkipListNode
{
public:
    int value;
    //vector的长度为10表示开到10层，nextNodes[0]表示在第一层的下一个节点
    //越是小的越是高层
    vector<SkipListNode*> nextNodes;
    
    SkipListNode(int value_)
    {
        value = value_;
    }
};

class SkipList
{
private:
    //head为巨小
    SkipListNode* head = new SkipListNode(NULL);
    int maxLevel;   //数据扔出的最大层
    int size;   //加进来多少key
    static const double PROBABILITY = 0.5;    //01概率

public:
    SkipList()
    {
        size = 0;
        maxLevel = 0;
        head->nextNodes.push_back(NULL);
    }

    SkipListNode* getHead()
    {
        return head;
    }

    void add(int newValue)
    {
        if(!contains(newValue))
        {
            size++;
            int level = 0;
            while((rand()/double(RAND_MAX))<PROBABILITY)
                level++;
            while(level>maxLevel)
            {
                head->nextNodes.push_back(NULL);
                maxLevel++;
            }
            SkipListNode* newNode = new SkipListNode(newValue);
            SkipListNode* current = head;
            do
            {
                current = findNext(newValue, current, level);
                newNode->nextNodes.insert(newNode->nextNodes.begin()+1,current->nextNodes.at(level));
                current->nextNodes[level] = newNode;
            } while (level-- > 0);  
        }
    }

    void delete(int deleteValue)
    {
        if(contains(newValue))
        {
            SkipListNode* deleteNode = find(deleteValue);
            size--;
            int level = maxLevel;
            SkipListNode* current = head;
            do
            {
                current = findNext(newValue, current, level);
                if(deleteNode->)
                current->nextNodes[level] = newNode;
            } while (level-- > 0);  
        }        
    }

    SkipListNode* findNext(int e, SkipListNode* current, int level)
    {
        SkipListNode* next = current->nextNodes[level];
        while(next != NULL)
        {
            int value = next->value;
            if(e < value)
                break;
            current = next;
            next = current->nextNodes[level];
        }
        //current为这层最后一个小于e的
        return current;
    }

    int size()
    {
        return size;
    }

    bool contains
    {

    }
};