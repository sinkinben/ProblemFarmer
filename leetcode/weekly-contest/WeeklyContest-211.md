## [leetcode] 周赛 211

🏆 比赛题目：https://leetcode-cn.com/circle/discuss/luvHfG/

## 两个相同字符之间的最长子字符串

题目：[5543. 两个相同字符之间的最长子字符串](https://leetcode-cn.com/problems/largest-substring-between-two-equal-characters/)。

开始理解错题意了，结果提交了 2 次错误答案 🤒️ 。

用一个 `map` 记录字符出现的第一次位置即可。时间 $O(n)$，空间 $O(1)$ 。

```cpp
class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) 
    {
        int maxval = -1;
        unordered_map<char, int> m;
        int len = s.length();
        for (int i=0; i<len; i++)
        {
            if (m.count(s[i]) == 1)
                maxval = max(maxval, i-m[s[i]]-1);
            else
                m[s[i]] = i;
        }
        return maxval;
    }
};
```

## 带阈值的图连通性

题目：[5128. 带阈值的图连通性](https://leetcode-cn.com/problems/graph-connectivity-with-threshold/)。

这题看出来是考察并查集的，但是第一次写是通过穷举图中的任意 2 个点是否联通实现的，时间复杂度是 $O(N^2)$ ，超时了。

```cpp
class Solution {
public:
    vector<int> root;
    vector<bool> res;
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) 
    {
        root.resize(n + 1, -1);
        for (int i=1; i<=n; i++)
        {
            for (int j=i+1; j<=n; j++)
            {
                if (check(n, threshold, j, i))
                    merge(i,j);
            }
        }
        for (auto &v: queries)
            res.push_back(find(v[0]) == find(v[1]));
        return res;
    }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y) root[y] = x;
    }
    int find(int x)
    {
        return root[x] == -1 ? x : (root[x] = find(root[x]));
    }
    int gcd(int a, int b)  // require a >= b
    {
        return (b == 0) ? a : gcd(b, a % b);
    }
    bool check(int n, int threshold, int x, int y)
    {
        return gcd(x, y) > threshold;
    }
};
```

然后也考虑了一下怎么优化，我的第一直觉是从「倍数」关系入手，对于 `i` 节点，我们只需要看它与 `j=2*i, 3*i, 4*i, ...` 是否联通。但是仔细一想，不对劲 🤨 ，比如 `threshold = 2` 时，`i=6, j=9` 这 2 个节点也是联通的，这么做不就忽略这种情况吗？

但其实并没有。

因为 `gcd(6, 9) = 3` ，所以其实 6 和 9 在并查集当中通过 3 连起来了。所以通过循环 `i=3, j=6,9,...` 时，我们已经把这种情况考虑了。

只需要改一下内层循环：

```cpp
for (int i=1; i<=n; i++)
    for (int j=i+i; j<=n; j+=i)
        if (check(n, threshold, j, i))
            merge(i, j);
```

实际上 `i` 可以从 `threshold` 开始。

空间复杂度 $O(n)$ 。下面看时间复杂度分析。

首先，双重循环的复杂度是：
$$
\sum_{i=1}^{n}\frac{n}{i} = n \sum_{i=1}^{n}\frac{1}{i}
$$
问题来了，这里有一个调和级数（真忘记了当时上算法课有没有学过 🤒️ ），但是高数里边判断是否收敛有个叫[积分判别法](https://baike.baidu.com/item/积分判别法)的东西。所以有（这里的等号并不严谨）：
$$
\sum_{i=1}^{n}\frac{1}{i} = \int_{1}^{n} \frac{1}{x}dx = \ln{n}
$$
所以双重循坏复杂度是 $O(n \log n)$，此外，每次循环还包含一次并查集操作，所以总的时间复杂度是 $O(n \log n \cdot \alpha(n))$ .

## 无矛盾的最佳球队

题目：[5545. 无矛盾的最佳球队](https://leetcode-cn.com/problems/best-team-with-no-conflicts/)。

这 TM 应该是最难的一道题了，看完题解的我还是一脸懵逼。

首先排序，年龄小的在前，同年龄分数小的在前。

那么对于 `data[i]` ，在其之前的人中（即下面的 `data[j]` ），跟他没有矛盾的条件是：

+ 同一年龄
+ 分数小于等于 `data[i]` 的分数

定义 `dp[i]` 是在区间 `[0, i]` 上选取人员，且选中人员 `i` 时最大分数。

转移方程：
$$
dp[i] = max(score[i], score[i] + dp[j]), 0 \le j < i
$$
有点类似于 LIS ，即最长上升子序列。

```cpp
class Node 
{
public:
    int score, age;
    Node(int s, int a): score(s), age(a){}
    bool operator < (const Node &n) const
    {
        return age < n.age || (age == n.age && score < n.score);
    }
};
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) 
    {
        int n = scores.size();
        vector<Node> data;
        for (int i=0; i<n; i++)
            data.push_back(Node(scores[i], ages[i]));
        sort(data.begin(), data.end());
        vector<int> dp(n);
        int maxval = data[0].score;
        for (int i=0; i<n; i++)
        {
            dp[i] = data[i].score;
            for (int j=0; j<i; j++)
            {
                if (data[j].age == data[i].age || data[j].score <= data[i].score)
                    dp[i] = max(dp[i], dp[j] + data[i].score);
            }
            maxval = max(maxval, dp[i]);
        }
        return maxval;
    }
};
```

还有一题是：[5544. 执行操作后字典序最小的字符串](https://leetcode-cn.com/problems/lexicographically-smallest-string-after-applying-operations/)，都说穷举（我也想到了），但就是写不出来，我是傻逼。

就这样吧，不要太难为自己 2333 。

