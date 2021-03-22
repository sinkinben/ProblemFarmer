## [leetcode] 周赛 208

🏆 比赛题目：https://leetcode-cn.com/contest/weekly-contest-208/

## 文件夹操作日志搜集

题目：[5523. 文件夹操作日志搜集器](https://leetcode-cn.com/problems/crawler-log-folder/)。

直接模拟。

```cpp
class Solution {
public:
    int minOperations(vector<string>& logs) {
        int k = 0;
        for (auto &s: logs)
        {
            if (s == "./")
                continue;
            else if (s == "../")
            {
                if (k >= 1)
                    k--;
            }
            else
                k++;
        }
        return k;
    }
};
```

## 摩天轮的最大利润

🎡题目：[5524. 经营摩天轮的最大利润](https://leetcode-cn.com/problems/maximum-profit-of-operating-a-centennial-wheel/)。

**解题思路**

还是模拟。做的时候没留意，要求的是 **得到最大利润时的轮转次数** ，还纳闷样例 3 为什么输出不是 10 ？一度怀疑是不是给错输出了 orz 。

使用 `waiting` 记录等待人数，`finish` 记录已经登上摩天轮的人数（已经收钱的人数），按要求模拟即可，`i` 是当前轮转次数，`maxi` 是利润 `p` 最大时的轮转次数。

**代码实现**

```cpp
#define getProfit(x, y) (x * boardingCost - y * runningCost)
class Solution
{
public:
    int minOperationsMaxProfit(vector<int> &customers, int boardingCost, int runningCost)
    {
        int waiting = 0;
        int finish = 0;
        int p = -1;
        int maxi = 1;
        int i = 1;
        for (int x : customers)
        {
            waiting += x;
            bool flag = waiting >= 4;
            finish += (flag ? 4 : waiting);
            waiting = (flag ? waiting - 4 : 0);
            int t = getProfit(finish, i);
            if (p < t)
            {
                p = t;
                maxi = i;
            }
            i++;
        }
        while (waiting != 0)
        {
            bool flag = waiting >= 4;
            finish += (flag ? 4 : waiting);
            waiting = (flag ? waiting - 4 : 0);
            int t = getProfit(finish, i);
            if (p < t)
            {
                p = t;
                maxi = i;
            }
            i++;
        }
        return p > 0 ? maxi : -1;
    }
};
```



## 皇位继承顺序

题目：[5525. 皇位继承顺序](https://leetcode-cn.com/problems/throne-inheritance/)。

原本的思路是按照题意去实现 Successor 函数，一步一步模拟，但因为该函数涉及到「查找」操作（我用的 `vector` ，使用 `algorithm` 库自带的 `find` 函数，所以是线性查找），所以结果是超时了。

最后看排行榜的解法：其实就是建图，然后 DFS 遍历一次就可以了，如果该人没死，说明可以继承。

**代码实现**

```cpp
class ThroneInheritance
{
public:
    int order = 0;
    unordered_map<string, int> getOrder;
    unordered_map<int, string> getName;

    // unordered_map<int, int> getParent;
    unordered_map<int, vector<int>> graph;
    unordered_set<int> deathSet;

    ThroneInheritance(string kingName)
    {
        getOrder[kingName] = order;
        getName[order] = kingName;
        graph[order] = vector<int>();
        deathSet.clear();
        order++;
    }

    void dfs(int x, vector<string> &list)
    {
        if (deathSet.count(x) == 0)
            list.push_back(getName[x]);
        for (int y : graph[x])
            dfs(y, list);
    }

    void birth(string parentName, string childName)
    {
        getOrder[childName] = order;
        getName[order] = childName;
        graph[getOrder[parentName]].push_back(order);
        order++;
    }

    void death(string name)
    {
        deathSet.insert(getOrder[name]);
    }

    vector<string> getInheritanceOrder()
    {
        vector<string> list;
        dfs(0, list);
        return list;
    }
};

```

## 最多可达成的换楼请求数目

题目：[5526. 最多可达成的换楼请求数目](https://leetcode-cn.com/problems/maximum-number-of-achievable-transfer-requests/)。

**解题思路**

题目的意思是，从 `requests` 中选取若干条边，使得图中所有顶点（即 Building）的入度与出度相等，求满足该条件的最大边数。

观察条件 `1 <= request.length <= 16`，显然从 `00...0, ..., 11..1` 穷举，时间复杂度最大为 $2^{16}$ 。此外，建图，判断图所有顶点的入度和出度是否相等，时间复杂度为 $O(n)$ . 穷举的时间复杂度是可以接受的。

我们令 `int i` 从 `0` 到 `(1<<len)-1` 变化，其低 $len$ 个 bit 表示 `requests[i]` 这条边是否加入图中。

**代码实现**

```cpp
class Solution
{
public:
    int maximumRequests(int n, vector<vector<int>> &requests)
    {
        int len = requests.size();
        int ans = 0;
        for (int i = 1; i < (1 << len); i++)
        {
            if (check(n, i, requests))
                ans = max(ans, countOne(i));
        }
        return ans;
    }

    int countOne(int x)
    {
        int k = 0;
        while (x)
            k++, x &= (x - 1);
        return k;
    }

    bool check(const int n, const int k, const vector<vector<int>> &req)
    {
        vector<int> indegree(n, 0), outdegree(n, 0);
        int len = req.size();
        for (int i = 0; i < len; i++)
        {
            if ((k >> i) & 1)
            {
                int x = req[i][0], y = req[i][1];
                outdegree[x]++, indegree[y]++;
            }
        }
        return indegree == outdegree;
    }
};
```

