## [leetcode] UnionFind-2

## 最长连续序列

题目[128]：[🔗链接](https://leetcode-cn.com/problems/longest-consecutive-sequence/)。

**解题思路**

节点本身的值作为节点的标号，两节点相邻，即允许合并`(x, y)`的条件为`x == y+1` 。

因为数组中可能会出现值为 -1 的节点，因此不能把 `root[x] == -1` 作为根节点的特征，所以采取 `root[x] == x` 作为判断是否为根节点的条件。默认较小的节点作为连通分量的根。

此外，使用 `map<int, int> counter` 记录节点所在连通分量的节点个数（也是`merge` 的返回值）。

```cpp
class Solution
{
public:
    unordered_map<int, int> counter;
    unordered_map<int, int> root;
    int longestConsecutive(vector<int> &nums)
    {
        int len = nums.size();
        // use map to discard the duplicate values
        for (int x : nums)
            root[x] = x, counter[x] = 1;
        int result = len == 0 ? 0 : 1;
        for (int x : nums)
        {
            if (root.count(x + 1) == 1)
                result = max(result, merge(x, x + 1));
        }
        return result;
    }
    int find(int x)
    {
        return root[x] == x ? x : (root[x] = find(root[x]));
    }
    int merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x != y)
        {
            root[y] = x;
            counter[x] += counter[y];
        }
        return counter[x];
    }
};
```



## 连通网络的操作次数

题目[1319]：[🔗Link](https://leetcode-cn.com/problems/number-of-operations-to-make-network-connected/).

**解题思路**

考虑使用并查集。

考虑到特殊情况，要使 N 个点连通，至少需要 N-1 条边，否则返回 -1 即可。

通过并查集，可以计算出多余的边的数目（多余的边是指使得图成环的边），只要 `findroot(x) == findroot(y)` 说明边 `(x,y)` 使得图成环。

遍历所有边，在并查集中执行合并 `merge` 操作（多余的边忽略不合并，只进行计数）。设 `components` 为合并后后 `root` 数组中 -1 的个数（也就是连通分量的个数），要想所有的连通分支都连起来，需要 `components - 1` 个边，所以要求「多余的边」的数目必须大于等于 `components - 1`。

一个简单的例子如下：

```text
0--1         0--1                0--1
| /    =>    |          =>       |  | 
2  3         2  3                2  3
             components = 2
             duplicateEdge = 1
```

**代码实现**

```cpp
class Solution
{
public:
    vector<int> root;
    int result = 0;
    int makeConnected(int n, vector<vector<int>> &connections)
    {
        int E = connections.size();
        // corner cases
        if (n == 0 || n == 1)
            return 0;
        if (E < n - 1)
            return -1;
        root.resize(n), root.assign(n, -1);
        // merge
        for (auto &v : connections)
        {
            int a = v[0], b = v[1];
            merge(a, b);
        }
        int components = count(root.begin(), root.end(), -1);
        if (counter >= (components - 1))
            return components - 1;
        // should not be here
        return -1;
    }
    int find(int x)
    {
        return root[x] == -1 ? x : (root[x] = find(root[x]));
    }
    // the number of duplicate edges
    int counter = 0;
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x;
        else
        {
            // there is a duplicate edge
            counter++;
        }
    }
};
```

## 等式方程的可满足性

题目[990]：[🔗Link](https://leetcode-cn.com/problems/satisfiability-of-equality-equations/).

**解题思路**

考虑并查集。遍历所有的包含 `==` 的等式，显然，相等的 2 个变量就合并。对于不等式 `x!=y` ，必须满足 `findroot(x) != findroot(y)` 才不会出现逻辑上的错误。也就是说，不相等的 2 个变量必然在不同的连通分支当中。

```cpp
#define getidx(x) ((x) - 'a')
class Solution
{
public:
    vector<int> root;
    bool equationsPossible(vector<string> &equations)
    {
        root.resize('z' - 'a' + 1, -1);
        vector<int> notequal;
        int len = equations.size();
        for (int i = 0; i < len; i++)
        {
            auto &s = equations[i];
            if (s[1] == '!')
            {
                notequal.emplace_back(i);
                continue;
            }
            int a = getidx(s[0]), b = getidx(s[3]);
            merge(a, b);
        }
        for (int i : notequal)
        {
            auto &s = equations[i];
            int a = getidx(s[0]), b = getidx(s[3]);
            if (find(a) == find(b))
                return false;
        }
        return true;
    }
    int find(int x)
    {
        return (root[x] == -1) ? x : (root[x] = find(root[x]));
    }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x;
    }
};
```



## 尽量减少恶意软件的传播 II

题目[928]：[😑这题有点难。](https://leetcode-cn.com/problems/minimize-malware-spread-ii/)

**解题思路**

参考 [题解1](https://leetcode-cn.com/problems/minimize-malware-spread-ii/solution/java-dfsshuang-bai-duo-tu-xiang-xi-jie-shi-bao-zhe/) 和 [题解2](https://leetcode-cn.com/problems/minimize-malware-spread-ii/solution/jin-liang-jian-shao-e-yi-ruan-jian-de-chuan-bo-ii-/) 。

首先，对原来的并查集结构添加一点改进，利用 `vector<int> size[N]` 记录某个连通分量中节点的数目，注意**当且仅当 `x` 是该连通分量的根节点时，`size[x]` 才表示该连通分量的节点数目**。这是因为在 `merge` 中，只对根节点的 `size` 进行了处理。

```cpp
vector<int> root;
vector<int> size;
int find(int x)
{
    return root[x] == -1 ? (x) : (root[x] = find(root[x]));
}
void merge(int x, int y)
{
    x = find(x), y = find(y);
    if (x != y)
        root[y] = x, size[x] += size[y];	// pay attention here
}
// get the size of the connected component where node x is in
int getComponentSize(int x)
{
    return size[find(x)];
}
```

然后，建立一个基本图，该图是原图 `graph` 去除所有感染节点 `initial` 的结果，并把这个基本图转换为上述改进后的并查集。把这个基本图中的节点暂且称为 clean nodes 或者 non-infected nodes .

从直觉上来说，我们应该在 `initial` 中找到那个标号最小，感染最多 non-infected nodes 的节点，但是这样是否符合预期？

显然是不符合的，来看个例子，设 `initial nodes = [a,b,c]` ，并设 2 个没有被感染的连通分量为 `N1, N2` ，且这 2 个连通分量的点数满足 `size(N1) > size(N2)`，原图 `graph` 结构如下：

```text
a--N1--c

b--N2
```

根据题目的意思，需要找到的是使得最终感染数目 `M(initial)` 最小的节点。

如果我们按照上述所谓的「直觉」：“在 initial 中找到那个感染最多 non-infected nodes 的节点”，应该去除的是节点 `a` ，但是由于 `c` 的存在，`N1` 依旧会被感染，这样 `M(initial) = size(N1) + size(N2)`。（也就是说，某个连通分量相邻的感染节点多于 1 个，该连通分量最终是必然被感染的，因为我们只能去除一个感染节点。）

实际上，这种情况下正确答案是去除 `b` ，因为除 `b` 后：`M(initial) = size(N1)` ，该结果才是最小的。

所以，我们要找的是：在 initial 中找到那个感染最多 non-infected nodes 的节点 `ans`，但这些 non-infected nodes 节点只能被 `ans` 感染，不能被其他的 initial 节点感染（即只能被感染一次）。

**代码实现**

```cpp
class Solution
{
public:
    vector<int> root;
    vector<int> size;
    int minMalwareSpread(vector<vector<int>> &graph, vector<int> &initial)
    {
        int N = graph.size();
        root.resize(N, -1);
        size.resize(N, 1);

        // use hash table to mark infected nodes
        vector<bool> init(N, false);
        for (int x : initial)
            init[x] = true;
        // change the non-infected graph into disjoint union set
        for (int i = 0; i < N; i++)
        {
            if (init[i])
                continue;
            for (int j = 0; j < i; j++)
            {
                if (init[j])
                    continue;
                if (graph[i][j] == 1)
                    merge(i, j);
            }
        }
        // table[x] = {...}
        // the set {...} means the non-infected components which initial node x will infect
        // counter[x] = k
        // k means that the non-infected component x will be infected by initial nodes for k times
        vector<int> counter(N, 0);
        unordered_map<int, unordered_set<int>> table;
        for (int u : initial)
        {
            unordered_set<int> infected;
            for (int v = 0; v < graph[u].size(); v++)
            {
                if (!init[v] && graph[u][v] == 1)
                    infected.insert(find(v));
            }
            table[u] = infected;
            for (int x : infected)
                counter[x]++;
        }

        // find the node we want
        int ans = N + 1, maxInfected = -1;
        for (int u : initial)
        {
            int sum = 0;
            for (int x : table[u])
                if (counter[x] == 1)	// must be infected only once
                    sum += getComponentSize(x);
            if (sum > maxInfected || (sum == maxInfected && u < ans))
            {
                ans = u;
                maxInfected = sum;
            }
        }
        return ans;
    }

    int find(int x)
    {
        return root[x] == -1 ? (x) : (root[x] = find(root[x]));
    }

    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x, size[x] += size[y];
    }

    int getComponentSize(int x)
    {
        return size[find(x)];
    }
};
```



## 尽量减少恶意软件的传播

题目[924]：[😅做了上面那题之后简单一点。](https://leetcode-cn.com/problems/minimize-malware-spread/)

**解题思路**

依然是使用上题中 **尽量减少恶意软件的传播 II** 改进后的并查集结构。

对整个原图处理，转换为并查集。然后，模拟处理。即 $\forall x \in initial$ ，使用集合 $newSet = initial - \{x\}$ 去模拟感染原图，得到最终的感染节点数 `t`，选取感染节点数 `t` 最小且标号值最小的 $x$ 作为返回结果。

**代码实现**

```cpp
class Solution
{
public:
    vector<int> root, size;
    int minMalwareSpread(vector<vector<int>> &graph, vector<int> &initial)
    {
        int N = graph.size();
        root.resize(N, -1);
        size.resize(N, 1);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < i; j++)
                if (graph[i][j] == 1)
                    merge(i, j);

        int ans = N + 1, minval = N + 1;
        // assume that discard the node x in the initial set
        // get the injected value
        for (int x : initial)
        {
            int t = getInjected(x, initial);
            if (t < minval || (t == minval && ans > x))
            {
                minval = t;
                ans = x;
            }
        }
        return ans;
    }
    // use set initial - {x} to inject the graph
    int getInjected(int x, vector<int> &initial)
    {
        unordered_set<int> s;
        for (int k : initial)
        {
            if (k == x)
                continue;
            s.insert(find(k));
        }
        int sum = 0;
        for (int t : s)
            sum += size[find(t)];
        return sum;
    }
    int find(int x)
    {
        return root[x] == -1 ? (x) : (root[x] = find(root[x]));
    }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x, size[x] += size[y];
    }
};
```



## 被围绕的区域

题目[130]：[🔗本题难度一般。](https://leetcode-cn.com/problems/surrounded-regions/)

**解题思路**

本题最特殊的节点是边界上的 `O` 以及内部与边界 `O` 相邻的节点。

首先，通过边界的 `O` 入手，从它开始进行 `DFS` 搜索，把所有这些的特殊节点标记为 `Y` 。然后，在 `board` 中剩下的 `O` 就是普通的节点（必然是不与边界 `O` 相邻且被 `X` 所围绕的），可以把它们全部换成 `X` 。最后，把所有的 `Y` 还原为 `O` 。

对于搜索方法，既可以是 `DFS` 也可以是 `BFS`。

**代码实现**

```cpp
class Solution
{
public:
    const vector<vector<int>> direction = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int row, col;
    void solve(vector<vector<char>> &board)
    {
        row = board.size();
        if (row == 0)
            return;
        col = board[0].size();
        #define func bfs
        for (int j = 0; j < col; j++)
        {
            if (board[0][j] == 'O')
                func(0, j, board);
            if (board[row - 1][j] == 'O')
                func(row - 1, j, board);
        }

        for (int i = 0; i < row; i++)
        {
            if (board[i][0] == 'O')
                func(i, 0, board);
            if (board[i][col - 1] == 'O')
                func(i, col - 1, board);
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                if (board[i][j] == 'Y')
                    board[i][j] = 'O';
            }
        }
    }

    void dfs(int i, int j, vector<vector<char>> &board)
    {
        board[i][j] = 'Y';
        for (auto &v : direction)
        {
            int a = i + v[0], b = j + v[1];
            if (a < 0 || b < 0 || a >= row || b >= col)
                continue;
            if (board[a][b] == 'O')
                dfs(a, b, board);
        }
    }

    void bfs(int i, int j, vector<vector<char>> &board)
    {
        typedef pair<int, int> node;
        queue<node> q;
        q.push(node(i, j));
        board[i][j] = 'Y';
        while (!q.empty())
        {
            node n = q.front();
            q.pop();
            for (auto &v : direction)
            {
                int a = n.first + v[0], b = n.second + v[1];
                if (!(a < 0 || b < 0 || a >= row || b >= col) && board[a][b] == 'O')
                    board[a][b] = 'Y', q.push(node(a, b));
            }
        }
    }
};
```

