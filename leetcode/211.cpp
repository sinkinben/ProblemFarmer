#include "leetcode.h"
struct TrieNode
{
    vector<TrieNode *> links;
    bool isend;
    TrieNode() : isend(false) { links.resize(26, nullptr); }
    bool contains(char c) { return (links[c - 'a'] != nullptr); }
    void put(char c) { links[c - 'a'] = new TrieNode(); }
    TrieNode *get(char c) { return links[c - 'a']; }
};
class WordDictionary
{
public:
    TrieNode *root;
    /** Initialize your data structure here. */
    WordDictionary()
    {
        root = new TrieNode();
    }

    /** Adds a word into the data structure. */
    void addWord(string word)
    {
        auto cur = root;
        for (char c : word)
        {
            if (!cur->contains(c))
                cur->put(c);
            cur = cur->get(c);
        }
        cur->isend = true;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word)
    {
        return innerSearch(root, word);
    }

    bool innerSearch(TrieNode *p, string word)
    {
        if (p == nullptr)
            return false;
        if (word.length() == 0)
            return p->isend;
        auto cur = p;
        int len = word.length();
        for (int i = 0; i < len; i++)
        {
            char c = word[i];
            if (c == '.')
            {
                for (auto x : cur->links)
                {
                    if (x != nullptr && innerSearch(x, word.substr(i + 1)))
                        return true;
                }
                return false;
            }
            else
            {
                if (!cur->contains(c))
                    return false;
                else
                    cur = cur->get(c);
            }
        }
        // assert(0);
        return cur->isend;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

int main()
{
    WordDictionary d;
    d.addWord("add");
    cout << d.search("a") << endl;
}