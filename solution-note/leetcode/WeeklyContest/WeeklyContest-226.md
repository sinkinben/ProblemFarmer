## [leetcode] 周赛 226

🏆 题目：https://leetcode-cn.com/contest/weekly-contest-226/

先贴个代码，后面如果有时间再写题解吧 😅 。

## 盒子中小球的最大数量

题目：[5654. 盒子中小球的最大数量](https://leetcode-cn.com/problems/maximum-number-of-balls-in-a-box/)。

哈希，取最大次数。

```cpp
class Solution {
public:
    int countBalls(int lowLimit, int highLimit) 
    {
        unordered_map<int, int> table;
        int ans = 0;
        for (int i=lowLimit; i<=highLimit; i++)
        {
            int key = hash_key(i);
            table[key]++, ans = max(ans, table[key]);
        }
        return ans;
    }
    
    int hash_key(int x)
    {
        int k = 0;
        while (x) k+=(x%10), x/=10;
        return k;
    }
};
```



## 从相邻元素对还原数组

题目：[5665. 从相邻元素对还原数组](https://leetcode-cn.com/problems/restore-the-array-from-adjacent-pairs/)

根据 `adjacentPairs` 建立图，然后从某个入度和出度均为 1 的点开始，做一次 DFS 遍历。

```cpp
class Solution
{
public:
    unordered_map<int, vector<int>> graph;
    unordered_map<int, int> indegree, outdegree;
    vector<int> result;
    unordered_map<int, bool> visited;
    vector<int> restoreArray(vector<vector<int>> &adjacentPairs)
    {
        for (auto &v : adjacentPairs)
        {
            graph[v[0]].emplace_back(v[1]), outdegree[v[0]]++, indegree[v[1]]++;
            graph[v[1]].emplace_back(v[0]), outdegree[v[1]]++, indegree[v[0]]++;
        }
        for (auto &[k, d] : indegree)
        {
            if (d == 1 && outdegree[k] == 1)
            {
                dfs(k);
                break;
            }
        }
        return result;
    }
    void dfs(int x)
    {
        visited[x] = true;
        result.emplace_back(x);
        for (int y : graph[x])
        {
            if (visited.count(y) == 0 || !visited[y])
                dfs(y);
        }
    }
};
```

## 恰糖果

🍬 题目：[5667. 你能在你最喜欢的那天吃到你最喜欢的糖果吗？](https://leetcode-cn.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/)

前缀和。主要思想是：计算出每天最少吃的数目与 `capacity` 比较（其实有很多细节要注意，太累了，不想写）。

```cpp
class Solution
{
public:
    vector<bool> canEat(vector<int> &candiesCount, vector<vector<int>> &queries)
    {
        vector<unsigned long long> prefixsum(candiesCount.size(), 0);
        int size = prefixsum.size();
        prefixsum[0] = candiesCount[0];
        for (int i = 1; i < size; i++)
            prefixsum[i] = candiesCount[i] + prefixsum[i - 1];

        size = queries.size();
        vector<bool> result(size, false);
        for (int i = 0; i < size; i++)
            result[i] = check(prefixsum, queries[i]);
        return result;
    }

    bool check(vector<unsigned long long> &prefixsum, vector<int> &v)
    {
        int64_t type = v[0], day = v[1], cap = v[2];
        int64_t sum = (type >= prefixsum.size() ? prefixsum.back() : prefixsum[type]);
        int64_t k = sum / (day + 1);
        if (k == 0) return false;
        bool flag = k <= cap;
        if (type == 0)
            return day <= prefixsum[0];
        while (k < cap && k * (day + 1) <= prefixsum[type-1])
            k++;
        return k * (day + 1) > prefixsum[type-1] && flag;
    }
};
```

## 回文串分割 IV

题目：[5666. 回文串分割 IV](https://leetcode-cn.com/problems/palindrome-partitioning-iv/)

搞不懂为什么是 Hard ？感觉是参加过的周赛中最简单的压轴题。

动态规划，计算出任意 `dp[i, j]` ，其表示子串 `[i, ..., j]` 是否为回文。

分割出 3 个子串，需要 2 个位置。双循环枚举所有可能的位置组合即可。

```cpp
class Solution {
public:
    bool checkPartitioning(string s) 
    {
        int len = s.length();
        if (len <= 2) return false;
        vector<vector<bool>> dp(len, vector<bool>(len, 0));
        for (int i=0; i<len; i++) dp[i][i] = 1;
        for (int i=0; i<len-1; i++) dp[i][i+1] = s[i] == s[i+1];
        for (int d=2; d<len; d++)
        {
            for (int i=0; i<(len-d); i++)
            {
                int j = i+d;
                dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1];
            }
        }
        for (int i=0; i<len-1; i++)
        {
            for (int j=i+1; j<len-1; j++)
            {
                if (dp[0][i] && dp[i+1][j] && dp[j+1][len-1]) return true;
            }
        }
        return false;

    }
};

/*
dp[i, j] = 1 if s[i, ..., j] 为回文, i <= j
dp[i, j] = (s[i] == s[j]) && dp[i+1, j-1]
*/
```

