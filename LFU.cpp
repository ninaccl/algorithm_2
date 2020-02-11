// LFU：最近最少缓存
// 【思路】
// 双向链表由小到大存储访问次数
// 每个链接节点底下依靠访问次序存储key和value

#include <iostream>
#include <unordered_map>

using namespace std;

//单个小节点
class Node
{
public:
    int key;
    int value;
    int times;
    Node* up = NULL;
    Node* down = NULL;
    
    Node(){}
    Node(int key_, int value_, int times_)
    {
        key = key_;
        value = value_;
        times = times_;
    }
};

class LFUCache
{
    //单个次数的节点链 每次往头加，从尾开始删
    class NodeList
    {
        public:
            Node* head = NULL;
            Node* tail = NULL;
            NodeList* last = NULL;
            NodeList* next = NULL;

            NodeList(){}
            NodeList(Node* node)
            {
                head = node;
                tail = node;
            }

            void addNodeFromHead(Node* newHead)
            {
                //指针重联
                newHead->down = head;
                head->up = newHead;
                head = newHead;
            }

            bool isEmpty()
            {
                return head == NULL;
            }

            void deleteNode(Node* node)
            {
                if(head == NULL)
                {
                    head = NULL;
                    tail = NULL;
                }
                else
                {
                    if(node == head)
                    {
                        head = node->down;
                        if(head != NULL)
                            head->up = NULL;
                    }
                    else if(node == tail)
                    {
                        tail = node->up;
                        if(tail != NULL)
                            tail->down = NULL;
                    }
                    else
                    {
                        node->up->down = node->down;
                        node->down->up = node->up;
                    }
                }
                node->up = NULL;
                node->down = NULL;
            }
    };

private:
    int capacity;   //容量
    int size;   //当前大小
    unordered_map<int, Node*> records;  //key对应于value，key是整型
    unordered_map<Node*, NodeList*> heads;   //key对应于哪个NodeList
    NodeList* headList = NULL;  //大结构中的第一个headlist(指示次数最低的NodeList)

public:
    LFUCache(){}

    LFUCache(int capacity_)
    {
        capacity = capacity_;
        size = 0;
    }

    void set(int key, int value)
    {
        if(records.find(key)!=records.end())
        {
            Node* node = records[key];  //拿出node内存地址
            node->value = value;    //改value值
            node->times++;  //访问次数加1
            NodeList* curNodeList = heads[node];    //提出对应大链表
            move(node, curNodeList);    //在大链表中拿出并放在词频加一的list中
        }
        else
        {
            //size到阈值应先删除再加入。删除应删除第一个大链表的尾节点
            if(size == capacity)
            {
                Node* node = headList->tail;
                headList->deleteNode(node);
                modifyHeadList(headList);   //删掉之后对于NodeList调整，可能第一个大链表没有东西了需要删除
                records.erase(node->key);
                heads.erase(node);
                size--;
            }
            Node* node = new Node(key,value,1);
            //查看是否有大头且大头是否词频为1，因为此时新结点词频必为1
            if(headList == NULL)
                headList = new NodeList(node);
            else
            {
                //用头节点数据项自己的times指示词频
                if(headList->head->times == node->times)
                    headList->addNodeFromHead(node);
                else
                {
                    NodeList* newList = new NodeList(node);
                    newList->next = headList;
                    headList->last = newList;
                    headList = newList;
                }
            }
            records[key] = node;
            heads[node] = headList;
            size++;
        }
    }

    //在大链表中拿出并放在词频加一的list中
    void move(Node* node, NodeList* oldNodeList)
    {
        oldNodeList->deleteNode(node);
        //删除节点以后有可能老链表整个都没了
        //存prelist和nextList是为了防止需要新建一个NodeList时需要与整体大链表连接
        NodeList* preList = modifyHeadList(oldNodeList)? oldNodeList->last : oldNodeList;
        NodeList* nextList = oldNodeList->next;

        //如果oldList是原词频的尾
        if(nextList == NULL)
        {
            NodeList* newList = new NodeList(node);
            //重联
            if(preList != NULL)
                preList->next = newList;
            newList->last = preList;
            if(headList == NULL)
                headList = newList;
            //heads记录修正
            heads[node] = newList;
        }
        else
        {
            //判断原链表的下一链表词频是否等于节点词频，即是否要构建新链表
            if(nextList->head->times == node->times)
            {
                nextList->addNodeFromHead(node);
                heads[node] = nextList;
            }
            else
            {
                NodeList* newList = new NodeList(node);
                if(preList != NULL)
                    preList->next = newList;
                newList->last = preList;
                newList->next = nextList;
                nextList->last = newList;
                if(headList == nextList)
                    headList = newList;
                heads[node] = newList;
            }    
        }       
    }

    //调整大链表的头
    //返回值：大链表中该链表是否需要删
    bool modifyHeadList(NodeList* nodeList)
    {
        if(nodeList->isEmpty())
        {
            //当前链表是不是大链表的头部
            if(headList == nodeList)
            {
                //换头
                headList = nodeList->next;
                if(headList != NULL)
                    headList->last = NULL;
            }
            else
            {
                //链表重联
                nodeList->last->next = nodeList->next;
                if(nodeList->next != NULL)
                    nodeList->next->last = nodeList->last;
            }
            return true;
        }
        return false;
    }

    int get(int key)
    {
        if(records.find(key) == records.end())
            return -1;
        Node* node = records[key];
        node->times++;
        NodeList* curNodeList = heads[node];
        move(node, curNodeList);
        return node->value;
    }
};

int main(void)
{
    LFUCache testCache(3);
    testCache.set(1,7);
    testCache.set(2,8);
    testCache.set(3,9);
    cout<<testCache.get(1)<<endl;
    cout<<testCache.get(1)<<endl;    
    cout<<testCache.get(2)<<endl;
    cout<<testCache.get(3)<<endl;
    testCache.set(4,10);
    cout<<testCache.get(2)<<endl;
    cout<<testCache.get(4)<<endl;
    testCache.set(5,11);
    cout<<testCache.get(5)<<endl;
    testCache.set(3,12);
    cout<<testCache.get(3)<<endl;
    cout<<testCache.get(4)<<endl;
    return 0;
}