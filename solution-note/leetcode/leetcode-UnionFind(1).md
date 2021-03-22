## [leetcode] UnionFind-1

参考资料：https://oi-wiki.org/ds/dsu/

## 预备知识

并查集 (Union Set) 一种常见的应用是计算一个图中连通分量的个数。比如：

```text
    a     e
   / \    |
  b   c   f
  |       |
  d       g
```

上图的连通分量的个数为 2 。

并查集的主要思想是在每个连通分量的集合中，选取一个代表，作为这个连通分量的根。根的选取是任意的，因为连通分量集合中每个元素都是等价的。我们只需关心根的个数（也是连通分量的个数）。例如：

```  text
   a       e
 / | \    / \
b  c  d  f   g
```

也就是说：`root[b] = root[c] = root[d] = a` 而 `root[a] = -1`（根节点的特征也可以定义为 `root[x] = x`）。

最后计算 `root[x] == -1` 的个数即可，这也就是连通分量的个数。伪代码如下：

```cpp
// n nodes, all nodes is independent at the beginning
vector<int> root(n, -1);
int find(int x)
{
    return root[x] == -1 ? x : (root[x] = find(root[x]));
}
// if x and y are connected, then call union(x, y)
void unionSet(int x, int y)
{
    x = find(x), y = find(y);
    if (x != y)  root[x] = y; // it also can be root[y] = x
}
int main()
{
    // (x,y) are connected
    while (cin >> x >> y)
        unionSet(x, y);
    // print the number of connectivity components
    print(count(root.begin(), root.end(), -1));
}
```

`find` 函数也可以通过迭代实现：

```cpp
int find(int x)
{
    int t = -1, p = x;
    while (root[p] != -1)  p = root[p];
    while (x != p)  {t = root[x]; root[x] = p; x = t;}
    return p;
}
```

**启发式合并**

> 一个连通分量的祖先突然抖了个机灵：「你们家族人比较少，搬家到我们家族里比较方便，我们要是搬过去的话太费事了。」

在 2 个连通分量中，可能存在 A 分量的点数小于 B 分量的点数，因此「把 A 合并到 B」比「把 B 合并到 A」要更划算。

```cpp
vector<int> root(n, -1);
vector<int> size(n, 1);
int find(int x) { return root[x] == -1 ? x : root[x] = find(root[x]); }
void merge(int x, int y)
{
    x = find(x), y = find(y);
    if (x != y)
    {
        if (size[x] < size[y]) root[y] = x, size[x] += size[y];
        else root[x] = y, size[y] += x;
    }
}
```

**时间复杂度**

假设有 $n$ 次合并（即给定 $n$ 条边），$m$ 次查找（即调用 $m$ 次 `find` ）：

- 只含路径压缩的并查集：最坏时间复杂度是 $O(m\log{n})$, 平均时间复杂度 $O(m \alpha{(m,n)})$ .
- 只使用启发式合并，而不使用路径压缩的并查集：$O(m\log{n})$ .
- 同时含路径压缩和启发式合并 (aka, 按秩合并) 的并查集：$O(m \alpha{(m,n)})$ , 其中 $\alpha(x, y)$ 是 Ackerman 函数的反函数。

## 朋友圈

题目[547]：点击 [🔗链接](https://leetcode-cn.com/problems/friend-circles/) 查看题目。

**示例**

```text
输入: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]
输出: 2 
说明：已知学生0和学生1互为朋友，他们在一个朋友圈。第2个学生自己在一个朋友圈。所以返回2。
```

**解题思路**

典型的计算连通分量的模板题。

```cpp
class Solution
{
public:
    int findCircleNum(vector<vector<int>> &m)
    {
        int len = m.size();
        vector<int> v(len, -1);
        int a, b;
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (m[i][j] == 1)
                {
                    a = findRoot(v, i), b = findRoot(v, j);
                    if (a != b)
                        v[a] = b;
                }
            }
        }
        return count(v.begin(), v.end(), -1);
    }

    int findRoot(vector<int> &root, int x)
    {
        // return (v[x] == -1) ? x : (v[x] = findRoot(v, v[x]));
        int p = x;
        while (root[p] != -1)  p = root[p];
        int t;
        while (x != p)  {t = root[x]; root[x] = p; x = t;}
        return p;        
    }
};
```

## 冗余连接

题目[684]：点击 [🔗链接](https://leetcode-cn.com/problems/redundant-connection/) 查看题目。

**解题思路**

关键在于找到使得现有的图中成环的第一条边。也就是对于新边 `(x,y)` 使得 `findroot(x) == findroot(y)`，该边就是问题所求。

```cpp
#include "leetcode.h"
class Solution
{
public:
    vector<int> findRedundantConnection(vector<vector<int>> &edges)
    {
        int n = edges.size();
        vector<int> r(n + 1, -1);
        vector<int> ans(2);
        int x, y;
        for (auto &v : edges)
        {
            x = findroot(r, v[0]), y = findroot(r, v[1]);
            if (x != y)
                r[x] = y;
            else
            {
                ans[0] = v[0], ans[1] = v[1];
                break;
            }
        }
        return ans;
    }
    int findroot(vector<int> &r, int x)
    {
        return (r[x] == -1) ? x : (r[x] = findroot(r, r[x]));
    }
};
```

## 情侣牵手

题目[765]：[🔗题目详情](https://leetcode-cn.com/problems/couples-holding-hands/) 。

**解题思路**

本题用并查集似乎会使问题变得复杂（实际上我自己也没想到用并查集怎么做😄）。这里采用了简单的模拟法（本质上是贪心算法），但怎么证明是「最小次数」确实是个问题。

设第 `i` 个人的编号为 `row[i]`：

+ 如果 `row[i]` 为偶数，那么其伴侣编号为 `row[i] + 1`
+ 如果 `row[i]` 为奇数，那么其伴侣编号为 `row[i] - 1`

也即是说：**对于任意一个 `row[i]` ，其伴侣编号为 `row[i] ^ 1`。**

每次从 `row` 读取 2 个数： `x = row[i], y = row[i+1]`，如果 `(x ^ 1) == y` 则 `(x,y)` 配对成功，否则找到 `x` 的伴侣，让其与 `y` 交换。

+ **朴素暴力模拟法**

直接遍历后面的元素，找到 `row[i]` 的伴侣，与 `row[i+1]` 交换位置。

```cpp
int minSwapsCouples(vector<int> &row)
{
    int n = row.size();
    int ans = 0;
    for (int i = 0; i < n; i += 2)
    {
        if ((row[i] ^ 1) == row[i + 1])
            continue;
        int target = row[i] ^ 1;
        for (int j = i + 2; j < n; j++)
        {
            if (row[j] == target)
            {
                swap(row[i + 1], row[j]), ans++;
                break;
            }
        }
    }
    return ans;
}
```

+ **优化查找伴侣**

上面我们采取的是遍历找伴侣，实际上可以通过哈希表记录每个人的座位号。对于数组 `index[N]` 和给定的编号 `row[i]`，令 `index[row[i]] = i`。时间和空间复杂度均为 $O(N)$ 。

```cpp
int minSwapsCouples2(vector<int> &row)
{
    int ans = 0;
    int len = row.size();
    vector<int> v(len, 0);
    for (int i = 0; i < len; i++)
        v[row[i]] = i;
    int t;
    for (int i = 0; i < len; i += 2)
    {
        t = row[i] ^ 1;
        if (t != row[i + 1])
        {
            ans++;
            int idx = v[t];
            // swap position
            swap(row[idx], row[i + 1]);
            // update hash table
            v[row[idx]] = idx;
            v[row[i + 1]] = i + 1;
        }
    }
    return ans;
}
```



## 除法求值

题目[399]：[🔗链接](https://leetcode-cn.com/problems/evaluate-division/)。

**解题思路**

这是一道图论的题目（~~废话~~）。首先对于 `x1 / x2 = value` 这样的等式，使用二维结构 `graph[x1][x2] = value` 去记录（图的二维矩阵形式）。

给定 `(u, v)` ，如果存在路径 `u -> x0 -> ... -> xn -> v`，那么 `u/v` 的值为：
$$
getval(u,v) = graph(u,x_0) \cdot \prod_{i=0}^{n-1}{graph(x_i,x_{i+1})} \cdot graph(x_n,v)
$$


对于题目给出的输入`x1`和`x2`都是字符串，需要优化空间，所以采取预处理把每个 `xi` 都映射为一个 `int` 。

+ **BFS**

给定 `(u,v)` ，采取 BFS 去搜索 `u` 到 `v` 的路径，同时在 `graph` 中记录 `u/xi` 的值（这样可减少一定量的重复搜索）。

```cpp
class Solution
{
public:
    unordered_map<string, int> m;
    unordered_map<int, unordered_map<int, double>> graph;
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        int V = hashstring(equations);
        // init gragh
        for (size_t i = 0; i < equations.size(); i++)
        {
            int a = m[equations[i][0]], b = m[equations[i][1]];
            double v = values[i];
            graph[a][b] = v, graph[b][a] = 1 / v;
            graph[a][a] = graph[b][b] = 1;
        }
        // exec
        vector<bool> visited(V, false);
        for (auto &v : queries)
        {
            string &a = v[0], &b = v[1];
            // one of the arguments is not given in equations
            if (m.find(a) == m.end() || m.find(b) == m.end())
            {
                result.emplace_back(-1);
                continue;
            }
            // bfs(a) to find whether if it can reach b 
            result.emplace_back(getval(m[a], m[b]));
        }
        return result;
    }

    // bfs
    double getval(int x, int y)
    {
        if (graph[x].find(y) != graph[x].end())
            return graph[x][y];
        typedef pair<int, double> node;
        queue<node> q;
        vector<int> vis(graph.size(), 0);
        q.push(node(x, 1));
        vis[x] = 1;
        while (!q.empty())
        {
            node n = q.front();
            q.pop();
            graph[x][n.first] = n.second;
            graph[n.first][x] = 1 / n.second;
            if (n.first == y)
                return n.second;
            for (auto &p : graph[n.first])
            {
                if (vis[p.first] == 0)
                {
                    vis[p.first] = 1;
                    q.push(node(p.first, n.second * p.second));
                }
            }
        }
        return -1;
    }

    // pre hashing string into int
    int hashstring(vector<vector<string>> &e)
    {
        int idx = 0;
        for (auto &v : e)
        {
            if (m.find(v[0]) == m.end())
                m[v[0]] = idx++;
            if (m.find(v[1]) == m.end())
                m[v[1]] = idx++;
        }
        return idx;
    }
};
```

+ **并查集**

待完善。

## 岛屿数量

题目[200]：[🔗链接](https://leetcode-cn.com/problems/number-of-islands/)。

**解题思路**

由题意可得，显然是找连通分量的数目，需要套上并查集的模板。

将每一个 `grid[i][j]` 看作是一个节点，那么二维数组中**相邻**的 `1` 需要合并，**所有**的 `0` 可以合并在一起（可以把任意的 `0` 作为根）。

并查集需要用一个 `root` 数组，其下标含义是每个节点的标号。设 `rows, cols` 分别为 `grid` 的行数和列数，使用 `i * cols + j` 作为节点 `grid[i][j]` 的标号，并设一个 `waterFiled = rows * cols` 作为所有 `0` 的根节点（根据题意，地图的所有水域都是连在一起的）。那么 `root` 数组的长度为 `rows + cols + 1`。

关键点是如何处理合并？

+ 对于 `grid[i][j] == 0` 的节点，只需要把 `getid(i, j)` 和水域的根节点 `waterField` 连接合并。
+ 对于 `grid[i][j] == 1` 的节点，需要合并相邻的 1 。「相邻」一共有 4 个位置，但是由于扫描数组 `grid` 的方向是从左到右，从上到下，因此只需要看节点右边和下边是否为 1 即可。如果 `grid[i][j+1] == 1` 那么需要 `merge(getid(i, j), getid(i, j+1))`，`grid[i+1][j]` 与之同理。

根据上面的操作，需要对 `grid` 进行预处理，在地图的最右边和最下边使用 `0` 包围起来。

```cpp
#define getid(i, j) ((i)*cols + (j))
class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        const int rows = grid.size();
        if (rows == 0)
            return 0;
        const int cols = grid[0].size();
        const int waterField = rows * cols;
        vector<int> root(rows * cols + 1, -1);

        // preparation
        for (auto &v : grid)
            v.push_back('0');
        grid.push_back(vector<char>(cols + 1, '0'));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == '1')
                {
                    if (grid[i][j + 1] == '1')
                        merge(root, getid(i, j), getid(i, j + 1));
                    if (grid[i + 1][j] == '1')
                        merge(root, getid(i, j), getid(i + 1, j));
                }
                else
                {
                    merge(root, waterField, getid(i, j));
                }
            }
        }
        return count(root.begin(), root.end(), -1) - 1;
    }

    int find(vector<int> &r, int x)
    {
        return (r[x] == -1) ? (x) : (r[x] = find(r, r[x]));
    }

    void merge(vector<int> &r, int x, int y)
    {
        int a = find(r, x);
        int b = find(r, y);
        if (a != b)
            r[b] = a;
    }
};
```

## 移除最多的同行或同列石头

题目[947]：[🔗链接](https://leetcode-cn.com/problems/most-stones-removed-with-same-row-or-column/)。

**示例解析**

```text
输入：stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
输出：5
```

使用 `stones` 的下标作为每个点的记号，对于上述输入，可以用下图来表示：

```text
     3----5
          |
1---------4
|
0----2
```

可以按照 `3, 5, 4, 1, 0` 的顺序去除，所以输出为 5 。

**解题思路**

使用下标作为各个点的记号，并且两个点相连的条件为：横坐标或纵坐标相等。下面考虑使用并查集解决。

显然，对于任意多的点，图中就会有若干的连通分量，但其形式总是下面 2 种形式的组合：

```
Type-1
a----b

Type-2
a
|
b
```

通过归纳法容易证明：**对于有 `n` 个点的连通分量，最多可执行 move 操作的次数为 `n - 1`。**（证明思路：对于 $n=2$ 或者 $n=3$ 的情况是显然成立的，而 $n=k$ 的连通分量总是可以通过 $n=2$ 和 $n=3$ 的情况组合而成。）

假设有 n 个连通分量，在第 `i` 个分支包含的节点数为 `p[i]`，这个图最多可以执行的 move 操作的次数为：
$$
\sum_{i=1}^{n}(p_i-1) = -n + \sum_{i=1}^{n}{p_i}
$$
也就是说，本题所求即是：**图的点数减去连通分量的个数**。

**代码实现**

`stones` 的下标作为节点的记号。通过 `rowmap<int, vector<int>>` 记录位于同一行的点，`colmap` 记录同一列的点，那么同一个 `vector` 里面的点都是可以合并到同一个连通分量的。选取 `vector[0]` 作为这个连通分量的根。

```cpp
class Solution
{
public:
    int removeStones(vector<vector<int>> &stones)
    {
        int len = stones.size();
        vector<int> root(len, -1);

        unordered_map<int, vector<int>> rowmap, colmap;
        for (int i = 0; i < stones.size(); i++)
        {
            const auto &v = stones[i];
            rowmap[v[0]].emplace_back(i);
            colmap[v[1]].emplace_back(i);
        }

        for (auto &p : rowmap)
        {
            auto &v = p.second;
            for (int x : v)
                merge(root, v[0], x);
        }

        for (auto &p : colmap)
        {
            auto &v = p.second;
            for (int x : v)
                merge(root, v[0], x);
        }
        return len - count(root.begin(), root.end(), -1);
    }
    int find(vector<int> &r, int x)
    {
        return (r[x] == -1) ? (x) : (r[x] = find(r, r[x]));
    }
    void merge(vector<int> &r, int x, int y)
    {
        if (x == y)
            return;
        x = find(r, x), y = find(r, y);
        if (x != y)
            r[y] = x;
    }
};
```

