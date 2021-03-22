## [leetcode] UnionFind-3

## 婴儿名字

题目[Interview-1707]：[典型并查集题目。](https://leetcode-cn.com/problems/baby-names-lcci/)

**解题思路**

首先对 `names` 这种傻 X 字符串结构进行预处理，转换为一个 `map`，`key` 是名字，`val` 是名字出现的次数。

然后是把 `synonyms` 转换为并查集结构，需要注意的是：**总是把字典序较小的名字作为连通分量的根。**

最后以连通分量的根作为代表，计算每个连通分量的总权重（即每个名字的次数之和）。

**代码实现**

```cpp
class Solution
{
public:
    unordered_map<string, string> root;
    vector<string> trulyMostPopular(vector<string> &names, vector<string> &synonyms)
    {
        vector<string> ans;
        unordered_map<string, int> table;
        for (auto &s : names)
        {
            int idx = s.find('(');
            string n = s.substr(0, idx);
            int val = stoi(s.substr(idx + 1, s.length() - 2 - idx));
            table[n] = val;
        }
        // build the disjoint-union set
        for (auto &str : synonyms)
        {
            int idx = str.find(',');
            string n1 = str.substr(1, idx - 1);
            string n2 = str.substr(idx + 1, str.length() - 2 - idx);
            merge(n1, n2);
        }
        // calculate the frequency of root nodes
        unordered_map<string, int> mapAns;
        for (auto &p : table)
            mapAns[find(p.first)] += p.second;

        for (auto &p : mapAns)
        {
            string s = p.first + "(" + to_string(p.second) + ")";
            ans.emplace_back(s);
        }

        return ans;
    }
    string find(string x)
    {
        return root.count(x) == 0 ? (x) : (root[x] = find(root[x]));
    }
    void merge(string x, string y)
    {
        x = find(x), y = find(y);
        if (x < y)
            root[y] = x;
        else if (x > y)
            root[x] = y;
        // do nothing if x == y
    }
};
```



## 冗余连接 Ⅱ

题目[685]：[😗需要观察出一点 trick .](https://leetcode-cn.com/problems/redundant-connection-ii/)

**解题思路**

请先完成[这篇文章中的 “冗余连接” ](https://www.cnblogs.com/sinkinben/p/12789613.html)。

看讨论区的题解，本题需要分成 2 种情况讨论（没想到真做不出来😅）：

+ 存在入度为 2 的点

  即给出的示例 1 。由于本题的隐含条件是：**去除一边后所得的图是树（即每个点的入度均为 1 ），所以可以确定这种情况下有且只有一个入度为 2 的点（通过反证法易证）。** 

  设入度为 2 的点为 `t` ，先在 `edges` 中剔除以 `t` 为终点的边（有且仅有 2 个这样的边），建立并查集结构。

  设被剔除的 2 个边**先后分别为** `e1` 和 `e2`，那么尝试在并查集中加入 `e1` ，如果加入 `e1` 后依然无环，说明 `e1` 属于树的边，那么返回 `e2` ；如果加入 `e1` 后有环，说明该剔除 `e1` ，即返回 `e1` 。（这么做的原因是题目要求：如果有多个满足则返回最后一个，如下图所示。）

+ 所有的点入度为 1

  即给出的示例 2 。这种情况下，必然存在一个边 `e` 使得图中存在一个有向环，该边 `e` 即为所求。扫描 `edges` 的每一个边，同时建立并查集结构，如果某一边使得 `find(x) == y`，说明有环，返回该边即可。

<img src="https://gitee.com/sinkinben/pic-go/raw/master/img/20210113200717.png" alt="image-20210113200717570" style="width:80%;" />

**代码实现**

```cpp
class Solution {
public:
    vector<int> root;
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        root.resize(n+1, -1);
        int node = getIndegreeTwoNode(edges);
        if (node == -1)
        {
            for (auto &v: edges)
            {
                if (find(v[0]) == v[1]) return v;
                else merge(v[0], v[1]);
            }
        }
        else
        {
            vector<vector<int>> candidate;
            for (auto &v: edges)
            {
                if (v[1] == node) candidate.push_back(v);
                else merge(v[0], v[1]);
            }
            auto &v = candidate[0];
            if (find(v[0]) == v[1]) return v;
            else return candidate[1];
        }
        // should not be here
        return {};
    }
    int find (int x) { return root[x] == -1 ? x : root[x] = find(root[x]); }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x!=y) root[y] = x;
    }
    int getIndegreeTwoNode(vector<vector<int>> &edges)
    {
        unordered_map<int, int> m;
        for (auto &v: edges) m[v[1]]++;
        for (auto &[k, v]: m) if (v == 2) return k;
        return -1;
    }
};
```

## 账户合并

题目[721]：[一般难度题目😑，有多种解法。](https://leetcode-cn.com/problems/accounts-merge/)

**解题思路**

+ DFS 解法

建立一个 `map` 记录每一个 email 对应的主人的 name ，方便后续的结果处理。

把所有的 email 建立一个图（以邻接表的形式）。每一个 account 的 email 都是相邻的，对于以下的 account ：

```text
account1 = ["John", "e1", "e2", "e3"]
account2 = ["John", "e4", "e3", "e5", "e2"]
```

在图 `graph` 中表现为：

```text
      _____________
      |           |
e1 -- e2 -- e3 -- e5
            |
            e4
```

其邻接表为：

```text
e1: [e2]
e2: [e1, e3, e5]
e3: [e2, e4, e5]
e4: [e3]
e5: [e3, e2]
```

最后，`graph` 图中的每一个连通分量必然是属于同一个人的，使用 `DFS` 或者  `BFS` 遍历整个图即可。

代码实现如下：

```cpp
class Solution
{
public:
    unordered_map<string, string> mailName;
    unordered_map<string, vector<string>> graph;
    unordered_set<string> visited;	// dfs helper
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {
        for (auto &v : accounts)
        {
            string &name = v[0];
            int size = v.size();
            // connect the emails
            for (int i = 1; i < size - 1; i++)
            {
                mailName[v[i]] = name;
                graph[v[i]].emplace_back(v[i + 1]);
                graph[v[i + 1]].emplace_back(v[i]);
            }
            // if this account has only one email, put it into the graph, too 
            if (size == 2 && graph.find(v[1]) == graph.end())
                graph[v[1]] = vector<string>();
            // the last email
            mailName[v[size - 1]] = name;
        }

        vector<vector<string>> ans;
        for (auto &p : graph)
        {
            auto &now = p.first;
            auto &list = p.second;
            vector<string> data({mailName[now]});
            if (visited.count(now) == 0)
            {
                dfs(data, now, list);
                sort(data.begin() + 1, data.end());
                ans.emplace_back(data);
            }
        }
        return ans;
    }
    void dfs(vector<string> &data, const string &now, vector<string> &list)
    {
        visited.insert(now);
        data.emplace_back(now);
        for (auto &x : list)
        {
            if (visited.count(x) == 0)
            {
                dfs(data, x, graph[x]);
            }
        }
    }
};
```

+ 并查集解法

其实与上面差不多 :-) . 只不过图的结构换成并查集，查找连通分量就可以不用 DFS 搜索了。

对于每个 account 的 email 列表，把第一个作为连通分量的根，把从第二个开始及后面的所有 email ，都将它们与第一个合并。

```cpp
class Solution
{
public:
    unordered_map<string, string> root;
    unordered_map<string, string> emailName;
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {
        // 建立并查集（结果不是完全路径压缩的）
        for (auto &v : accounts)
        {
            string &name = v.front();
            int size = v.size();
            emailName[v[1]] = name;
            for (int i = 2; i < size; i++)
            {
                emailName[v[i]] = name;
                merge(v[1], v[i]);
            }
        }
        vector<vector<string>> ans;
        unordered_map<string, vector<string>> table;
        // 把同一个连通分量归类在一起，key是该连通分量的根，val是连通分量的所有节点
        for (auto &p : emailName)
        {
            auto email = p.first, name = p.second;
            table[find(email)].emplace_back(email);
        }
        // 一个分量就是结果中的一个 account
        for (auto &p : table)
        {
            auto v = p.second;
            sort(v.begin(), v.end());
            v.insert(v.begin(), emailName[p.first]);
            ans.emplace_back(v);
        }
        return ans;
    }
    string find(const string &x)
    {
        return root.count(x) == 0 ? (x) : (root[x] = find(root[x]));
    }
    void merge(string x, string y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x;
    }
};
```



## 相似字符串组

题目[839]：[😎一道 Hard 题目，没想到暴力解法也能过。](https://leetcode-cn.com/problems/similar-string-groups/)

**解题思路**

每个字符串相当于一个节点，以该串在数组中的下标作为节点记号。

实现 `similar` 函数，判定 2 个字符串是否相似。对所有字符串进行两两比较（暴力枚举所有情况），判断是否相似，若相似则在并查集中合并。最后连通分量的个数就是答案。

👻执行用时只超过 25% （能用就行，能用就行，又不是不能用.jpg ）。

**代码实现**

```cpp
class Solution
{
public:
    vector<int> root;
    int numSimilarGroups(vector<string> &A)
    {
        int N = A.size();
        root.resize(N, -1);

        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                if (similar(A[i], A[j]))
                    merge(i, j);
            }
        }
        return count(root.begin(), root.end(), -1);
    }
    int find(int x)
    {
        return root[x] == -1 ? (x) : (root[x] = find(root[x]));
    }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x;
    }
    bool similar(const string &a, const string &b)
    {
        int len = min(a.length(), b.length());
        int diff = 0;
        for (int i = 0; i < len; i++)
            diff += (a[i] != b[i]);
        return diff <= 2;
    }
};
```



## 交换字符串中的元素

题目[1202]：[🐶看题解，看题解。](https://leetcode-cn.com/problems/smallest-string-with-swaps/)

**解题思路**

[🐶看这个无敌简洁的题解。](https://leetcode-cn.com/problems/smallest-string-with-swaps/solution/bing-cha-ji-python-by-fa-kuang-de-jie-zi/)

以 `s = "dcabfge", pairs = [[0,3],[1,2],[0,2],[4,6]]` 为例进行分析。

首先需要想到一点 trick ，怎么套上并查集的模板：此处的「交换」是具有传递性和对称性的，因此在 `pairs` 中，`[0,1,2,3]` 是可以两两进行任意交换（且不限次数），因此每一个 `pair = [a,b]` 实际上就是并查集中的一个边，无脑对 `pairs` 套上并查集的结构进行处理。

此处，并查集的结果是得到 3 个连通分量 `[5], [0,1,2,3]` 和 `[4,6]` ，（按顺序）对应可交换的字符是 `[g], [d,c,a,b]` 和 `[f,e]`，要求字典序最小，因此排序结果为 `[g], [a,b,c,d]` 和 `[e,f]` 。

将其还原到原始位置：

```text
index: 5 | 0 1 2 3 | 4 6   
chars: g | a b c d | e f
==>
return s = "abcdegf"
```

**代码实现**

+ 使用交换排序，超时

```cpp
class Solution
{
public:
    vector<int> root;
    string smallestStringWithSwaps(string s, vector<vector<int>> &pairs)
    {
        int len = s.length();
        if (len == 0)
            return s;
        root.resize(len, -1);
        for (auto &v : pairs)
            merge(v[0], v[1]);
        // extract each component nodes
        // table[r] = [...]
        // r is the root of connected component
        // [...] includes all nodes of the component
        unordered_map<int, vector<int>> table;
        for (int i = 0; i < len; i++)
            table[find(i)].emplace_back(i);
        for (auto &p : table)
        {
            auto &list = p.second;
            sortByValue(list, s);
        }
        return s;
    }
    void sortByValue(vector<int> &list, string &s)
    {
        int n = list.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (s[list[j]] < s[list[i]])
                    swap(s[list[i]], s[list[j]]);
            }
        }
    }
    // function 'merge' and 'find' are omitted since the space is limited
};
```

+ 使用 STL 自带的排序 sort，但执行用时只超过 50%

```cpp
class Solution
{
public:
    vector<int> root;
    string smallestStringWithSwaps(string s, vector<vector<int>> &pairs)
    {
        int len = s.length();
        if (len == 0)
            return s;
        root.resize(len, -1);

        for (auto &v : pairs)
            merge(v[0], v[1]);

        // extract each component nodes
        unordered_map<int, vector<int>> table;
        for (int i = 0; i < len; i++)
            table[find(i)].emplace_back(i);

        for (auto &p : table)
        {
            string chars = "";
            for (int i : p.second)
                chars.push_back(s[i]);
            sort(chars.begin(), chars.end());
            int j = 0;
            for (int i : p.second)
                s[i] = chars[j++];
        }
        return s;
    }
    // function 'merge' and 'find' are omitted since the space is limited
};
```



## 按公因数计算最大组件大小

题目[952]：[😑刷题？刷题解罢了。](https://leetcode-cn.com/problems/largest-component-size-by-common-factor/)

+ 暴力枚举（当然是超时了）

把 num 所在数组 `A` 中的下标作为并查集中节点的标号。如果 `GCD(A[i], A[j]) > 1` 说明节点 `i` 和 `j` 可以合并。

```cpp
class Solution
{
public:
    vector<int> root;
    vector<int> size;
    int largestComponentSize(vector<int> &A)
    {
        int n = A.size();
        root.resize(n, -1);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (GCD(A[i], A[j]) > 1)
                    merge(i, j);
        int maxval = size[0];
        for (int x : size)	maxval = max(x, maxval);
        return maxval;
    }
    // function 'find' is omitted
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)  root[y] = x, size[x] += size[y];
    }
    // a>b is required
    int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
    int GCD(int a, int b)
    {
        if (a > b)  return gcd(a, b);
        else        return gcd(b, a);
    }
};
```

+ [😑题解大法好](https://leetcode-cn.com/problems/largest-component-size-by-common-factor/solution/bing-cha-ji-java-python-by-liweiwei1419/)

此处，把 `A[i]` 的值作为并查集  `root` 节点的标号（不是下标作为标号）。

对于每一个 `A[i]` 找出它的所有大于 1 的因子，显然 `A[i]` 与这些因子之间是可以合并的，默认把 `A[i]` 作为连通分量的根（大数值作为根）。那么，并查集的结果就包含了任意两个 `A[i], A[j]` 之间的关系（这里的关系是指它们是否连通，即是否具有大于 1 的公因子）。为什么呢？来看个例子。

```text
A = [2, 3, 15, 10]
对于 2 和 3 ，不执行 merge 操作。
对于 15 ：merge(15, 3), merge(15, 5)
对于 10 ：merge(10, 2), merge(10, 5)

并查集最终结果，每一行表示一个连通分量，行首是连通分量的根：
2 : [2]
3 : [3]
15: [15,3,5,10,2]
```

显然，10 和 15 就通过 `merge(10,5)` 和 `merge(15, 5)` 这 2 个操作合并到一块。

最后的问题是如何找出 `A` 中最大的连通分量？注意，这里并不是并查集 `root` 的最大连通分量，因为 `root` 对 `A` 来说是一个扩充后的结构，它包含了 `A` 中没有的数值。

新建一个 `vector<int> counter` ，`counter[r]` 表示以 `r` 为根的连通分量中，数组 `A` 中的元素在该分量中出现的次数。 即：

```cpp
for (int x : A)
    ++counter[find(x)];
```

对于上述例子：

```text
counter[2] = 1
counter[3] = 1
counter[15] = 2
```

最终，counter 的最大值即为答案。

代码如下：

```cpp
class Solution
{
public:
    vector<int> root;
    int largestComponentSize(vector<int> &A)
    {
        int maxval = -1;
        for (int x : A)
            maxval = max(maxval, x);
        root.resize(maxval + 1, -1);

        for (int x : A)
        {
            int limit = (int)sqrt(x) + 1;
            for (int i = 2; i < limit; i++)
                if (x % i == 0)
                    merge(x, i), merge(x, x / i);
        }

        vector<int> counter(maxval + 1, 0);
        int ans = -1;
        for (int x : A)
            ans = max(ans, ++counter[find(x)]);
        return ans;
    }
    int find(int x) { return root[x] == -1 ? x : (root[x] = find(root[x])); }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y) root[y] = x;
    }
};
```



## 总结

磕磕碰碰总算把「并查集」的题目刷了一遍，好像还有几道题是没做出来的（当然是「下次再努力」啊🐶）。

