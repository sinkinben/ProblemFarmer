## Shortest Word Distance

Leetcode: [243. Shortest Word Distance](https://leetcode-cn.com/problems/shortest-word-distance/)

Given an array of strings `wordsDict` and two different strings that already exist in the array `word1` and `word2`, return the shortest distance between these two words in the list.

Example:

```
Input: wordsDict = ["practice", "makes", "perfect", "coding", "makes"], word1 = "coding", word2 = "practice"
Output: 3
```

**Brute Force Solution**

```cpp
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2)
    {
        auto v1 = find(words, word1);
        auto v2 = find(words, word2);
        int res = INT_MAX;
        for (int x : v1)
            for (int y : v2)
                res = min(res, abs(x - y));
        return res;
    }
    vector<int> find(vector<string> &words, string &s)
    {
        int n = words.size();
        vector<int> res;
        for (int i = 0; i < n; ++i)
            if (words[i] == s) res.emplace_back(i);
        return res;
    }
};
```

<br/>

**One Pass Solution**

```cpp
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int i = -1, j = -1, res = INT_MAX;
        int n = words.size();
        for (int k = 0; k < n; ++k)
        {
            if (words[k] == word1) i = k;
            if (words[k] == word2) j = k;
            if (i != -1 && j != -1)
                res = min(res, abs(i - j));
        }
        return res;
    }
};
```