#include <string>
#include <iostream>
using namespace std;

class TrieNode 
{
public:
    int path;
	int end;
	TrieNode** map;
    TrieNode() 
    {
		path = 0;
		end = 0;
        map = new TrieNode*[26];
	}
};

class Trie 
{
private: 
    TrieNode *root;
public:
	Trie() 
    {
		root = new TrieNode();
	}

    void insert(string word) 
    {
		if (word.empty()) 
			return;
		TrieNode *node = root;
		int index = 0;
		for (int i = 0; i < word.length(); i++) 
        {
			index = word[i] - 'a';
			if (node->map[index] == NULL)
            { 
				node->map[index] = new TrieNode();
            }
			node = node->map[index];
			node->path++;
		}
		node->end++;
	}

	void Delete(string word) 
    {
		if (search(word)) 
        {
			TrieNode* node = root;
			int index = 0;
			for (int i = 0; i < word.length(); i++) 
            {
				index = word[i] - 'a';
                node->map[index]->path--;
				if (node->map[index]->path == 0) 
                {     
					deleteserial(node->map[index],word,++i);
                    node->map[index]=NULL;
                    return;
				}
				node = node->map[index];
			}
			node->end--;
		}
    }

    void deleteserial(TrieNode* node, string word, int i)
    {
        if(i>=word.length())
        {
            delete node;
            return;
        }
        int index = 0;
        index = word[i] - 'a';
        i++;
        deleteserial(node->map[index],word,i);
        node->path = 0;
        node->end = 0;
        node->map[index] =NULL;
        delete node;
        return;
    }

	bool search(string word) 
    {
		if (word.empty()) 
			return false;
		TrieNode* node = root;
		int index = 0;
		for (int i = 0; i < word.length(); i++) 
        {
			index = word[i] - 'a';
			if (node->map[index] == NULL) 
				return false;
			node = node->map[index];
		}
		return node->end;
	}

	int prefixNumber(string pre) 
    {
		if (pre.empty()) 
			return 0;
		TrieNode* node = root;
		int index = 0;
		for (int i = 0; i < pre.length(); i++) 
        {
			index = pre[i] - 'a';
			if (node->map[index] == NULL) 
				return 0;
			node = node->map[index];
		}
		return node->path;
	}
};

int main(void) 
{
    // 0 1 0 1 0 0 3
	Trie trie;
	cout<<trie.search("zuo")<<endl; 
	trie.insert("zuo");
	cout<<trie.search("zuo")<<endl;
	trie.Delete("zuo");
	cout<<trie.search("zuo")<<endl;
	trie.insert("zuo");
	trie.insert("zuo");
	trie.Delete("zuo");
	cout<<trie.search("zuo")<<endl;
	trie.Delete("zuo");
	cout<<trie.search("zuo")<<endl;
	trie.insert("zuoa");
	trie.insert("zuoac");
	trie.insert("zuoab");
	trie.insert("zuoad");
	trie.Delete("zuoa");
	cout<<trie.search("zuoa")<<endl;
	cout<<trie.prefixNumber("zuo")<<endl;
    return 0;
}