[leetcode] 周赛 207 

🏆 周赛题目：https://leetcode-cn.com/contest/weekly-contest-207

## 重新排列单词间的空格

一道简单的模拟题。

首先计算空格个数，其次分割出单词，最后按照要求模拟即可。

```cpp
class Solution
{
public:
    string reorderSpaces(string text)
    {
        int spaces = 0;
        for (char x : text)
            spaces += (x == ' ');

        vector<string> words;
        stringstream ss(text);
        string buf;
        while (ss >> buf)
            words.emplace_back(buf);

        buf = "";

        int len = words.size();
        if (len == 1)
            return words.back().append(spaces, ' ');

        int k = spaces / (len - 1);
        for (int i = 0; i < len - 1; i++)
            buf.append(words[i]), buf.append(k, ' ');
        buf.append(words[len - 1]), buf.append(spaces - (k * (len - 1)), ' ');
        return buf;
    }
};
```



## 拆分字符串使唯一子字符串的数目最大

题目链接：[1593. 拆分字符串使唯一子字符串的数目最大](https://leetcode-cn.com/problems/split-a-string-into-the-max-number-of-unique-substrings/)。

**解题思路**

回溯法实现状态穷举。

**代码实现**

```cpp
class Solution
{
public:
    unordered_set<string> pool;
    int ans = 0;
    int maxUniqueSplit(string s)
    {
        dfs(s, 0);
        return ans;
    }

    void dfs(const string &s, int idx)
    {
        int len = s.length();
        if (idx >= len)
        {
            ans = max(ans, (int)pool.size());
            return;
        }
        string t;
        for (int i = idx; i < len; i++)
        {
            t += s[i];
            if (pool.find(t) == pool.end())
            {
                pool.insert(t);
                dfs(s, i + 1);
                pool.erase(t);
            }
        }
    }
};
```



## 矩阵的最大非负积

DFS 搜索所有路径，加一点小小的剪枝 trick 。

```cpp
class Solution
{
public:
    int rows, cols;
    int64_t ans = -1;
    const int mod = ((int)1e9 + 7);
    int maxProductPath(vector<vector<int>> &grid)
    {
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;
        rows = grid.size(), cols = grid[0].size();
        dfs(grid, 0, 0, 1);
        return ans % mod;
    }

    void dfs(vector<vector<int>> &g, int i, int j, int64_t cur)
    {
        if (i == rows || j == cols)
            return;
        cur = (cur * g[i][j]);
        if (cur == 0)
        {
            ans = max(ans, 0);
            return;
        }
        if (i == rows - 1 && j == cols - 1)
        {
            ans = max(ans, cur);
            return;
        }
        dfs(g, i + 1, j, cur);
        dfs(g, i, j + 1, cur);
    }
};

```



最后一题是 Hard 级别第题目：[连通两组点的最小成本](https://leetcode-cn.com/problems/minimum-cost-to-connect-two-groups-of-points/)，据评论区说是一道状态压缩型 DP，还是后面水平高一点再做吧，还是太菜了。