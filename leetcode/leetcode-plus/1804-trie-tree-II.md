## Impl Trie Tree II

Leetcode: [1804. Implement Trie II (Prefix Tree)](https://leetcode-cn.com/problems/implement-trie-ii-prefix-tree/)

A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the `Trie` class:

- `Trie()` Initializes the trie object.
- `void insert(String word)` Inserts the string word into the trie.
- `int countWordsEqualTo(String word)` Returns the number of instances of the string word in the trie.
- `int countWordsStartingWith(String prefix)` Returns the number of strings in the trie that have the string prefix as a prefix.
- `void erase(String word)` Erases the string word from the trie.

<br/>

**Solution**

```cpp
struct TrieNode
{
    int cnt;  // cnt denote the number of word in trie tree
    array<TrieNode*, 26> children;
    TrieNode() : cnt{0}, children{nullptr} {}
    bool contains(char x) { return get(x) != nullptr; }
    TrieNode *put(char x) { return children[x - 'a'] = new TrieNode(); }
    TrieNode *get(char x) { return children[x - 'a']; }
};
class Trie {
public:
    TrieNode *root = new TrieNode();
    Trie() {}
    
    void insert(string word) {
        auto p = root;
        for (char x : word)
        {
            if (p->contains(x)) p = p->get(x);
            else p = p->put(x);
        }
        p->cnt += 1;
    }
    
    TrieNode *searchPrefix(string &prefix) {
        auto p = root;
        for (char x : prefix)
        {
            if (!p->contains(x)) return nullptr;
            p = p->get(x);
        }
        return p;
    }
    
    int countWordsEqualTo(string word) {
        auto p = searchPrefix(word);
        return p ? p->cnt : 0;
    }

    void erase(string word) {
        auto p = searchPrefix(word);
        if (p != nullptr) p->cnt -= 1;
    }
    
    int countWordsStartingWith(string prefix) {
        auto p = searchPrefix(prefix);
        return dfs(p);
    }
    
    int dfs(TrieNode *node) {
        if (node == nullptr) return 0;
        int sum = node->cnt;
        for (auto next : node->children)
            sum += dfs(next);
        return sum;
    }
};
```

