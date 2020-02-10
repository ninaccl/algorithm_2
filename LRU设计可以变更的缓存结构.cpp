// 【题目】
// 设计一种缓存结构，该结构在构造时确定大小，假设大小为k，并有两个功能：
// set(key, value):将记录插入该结构
// get(key):返回key对应的value值
// 【要求】
// 1.set和get方法的时间复杂度为O(1)
// 2.某个key的set和get操作一旦发生，认为这个key的记录成了最经常使用的
// 3.当缓存大小超过k时，移除最不经常使用的记录，即set或get最久远的

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

template <class K, class V>
class Node
{
public:
    K key;
    V value;
    Node* last = NULL;
    Node* next = NULL;

    Node(){}
    Node(K key, V value)
    {
        this->key = key;
        this->value = value;
    }
};

template<class K, class V>
class NodeDoubleLinkedList
{
private:
    Node<K,V> *head = NULL;
    Node<K,V> *tail = NULL;

public:
    NodeDoubleLinkedList()
    {}
    void addNode(Node<K,V>* newNode)
    {
        if(newNode == NULL)
            return;
        if(head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->last = tail;
            tail = newNode;
        }
    }

    void moveNodeToTail(Node<K,V>* node)
    {
        if(tail == node)
            return;
        if(head == node)
        {
            //头变换
            head = node->next;   
            head->last = NULL;
        }
        else
        {
            node->last->next = node->next;
            node->next->last = node->last;
        }
        node->last = tail;
        node->next = NULL;
        tail->next = node;
        tail = node;
    }

    Node<K,V>* removeHead()
    {
        if(head == NULL)
            return NULL;
        Node<K,V>* res = head;
        if(head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = res->next;
            res->next = NULL;
            head->last = NULL;
        }
        return res;       
    }
};

template<class K, class V>
class Mycache
{
private:
    unordered_map<K, Node<K,V>*> keyNodeMap;
    NodeDoubleLinkedList<K,V> nodeList;
    int capacity;

public:
    Mycache(int capacity)
    {
        if(capacity<1)
            throw runtime_error("should be more tahn 0");
        this->capacity = capacity;
    }

    V get(K key)
    {
        if(keyNodeMap.find(key)!=keyNodeMap.end())
        {
            Node<K,V>* res = keyNodeMap[key];
            nodeList.moveNodeToTail(res);
            return res->value;
        }
        return 0;
    }

    void set(K key, V value)
    {
        if(keyNodeMap.find(key)!=keyNodeMap.end())
        {
            Node<K,V>* node = keyNodeMap[key];
            node->value = value;
            nodeList.moveNodeToTail(node);
        }
        else
        {
            Node<K,V>* newNode = new Node<K,V>(key,value);
            keyNodeMap[key]=newNode;
            nodeList.addNode(newNode);
            if(keyNodeMap.size() == capacity+1)
                removeMostUnusedCache();
        }
    }

    void removeMostUnusedCache()
    {
        Node<K,V>* removeNode = nodeList.removeHead();
        K removekey = removeNode->key;
        keyNodeMap.erase(removekey);
    }
};

int main(void)
{
    Mycache<string, int> testCache(3);
    testCache.set("A",1);
    testCache.set("B",2);
    testCache.set("C",3);
    cout<<testCache.get("B")<<endl;
    cout<<testCache.get("A")<<endl;
    testCache.set("D",4);
    cout<<testCache.get("C")<<endl;
    return 0;
}