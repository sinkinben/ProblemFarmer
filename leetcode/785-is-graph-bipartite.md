## 785. Is Graph Bipartite

Leetcode: [785. Is Graph Bipartite?](https://leetcode.com/problems/is-graph-bipartite/)

Difficulty: **Medium**  


There is an **undirected** graph with `n` nodes, where each node is numbered between `0` and `n - 1`. You are given a 2D array `graph`, where `graph[u]` is an array of nodes that node `u` is adjacent to. More formally, for each `v` in `graph[u]`, there is an undirected edge between node `u` and node `v`. The graph has the following properties:

*   There are no self-edges (`graph[u]` does not contain `u`).
*   There are no parallel edges (`graph[u]` does not contain duplicate values).
*   If `v` is in `graph[u]`, then `u` is in `graph[v]` (the graph is undirected).
*   The graph may not be connected, meaning there may be two nodes `u` and `v` such that there is no path between them.

A graph is **bipartite** if the nodes can be partitioned into two independent sets `A` and `B` such that **every** edge in the graph connects a node in set `A` and a node in set `B`.

Return `true` _if and only if it is **bipartite**_.

**Example 1:**

![](https://assets.leetcode.com/uploads/2020/10/21/bi2.jpg)

```
Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
Output: false
Explanation: There is no way to partition the nodes into two independent sets such that every edge connects a node in one and a node in the other.
```

**Example 2:**

![](https://assets.leetcode.com/uploads/2020/10/21/bi1.jpg)

```
Input: graph = [[1,3],[0,2],[1,3],[0,2]]
Output: true
Explanation: We can partition the nodes into two sets: {0, 2} and {1, 3}.
```

**Constraints:**

*   `graph.length == n`
*   `1 <= n <= 100`
*   `0 <= graph[u].length < n`
*   `0 <= graph[u][i] <= n - 1`
*   `graph[u]` does not contain `u`.
*   All the values of `graph[u]` are **unique**.
*   If `graph[u]` contains `v`, then `graph[v]` contains `u`.

<br/>


**1. DFS**

Two coloring problem.
+ Perform DFS on the graph.
+ For each node, its color can not be same as its adjacent node.

```c++
enum color_t
{
    BLACK = 0,
    WHITE = 1
};
class Solution {
public:
    vector<int> colors;
    bool isBipartite(vector<vector<int>>& graph)
    {
        int n = graph.size();
        colors.resize(n, -1);
        
        bool res = 1;
        for (int i = 0; i < n; ++i)
        {
            if (colors[i] == -1)
            {
                res = res && dfs(graph, i, BLACK, WHITE);
                if (!res) break;
            }
        }
        return res;
    }
    /* @cur - Current color we should use.
     * @pre - The color of previous node.
     * @x - Current node we are visiting.
     */
    bool dfs(vector<vector<int>>& graph, int x, bool cur, bool pre)
    {
        if (colors[x] != -1)
            return colors[x] == cur;
​
        colors[x] = cur;
        for (int next : graph[x])
        {
            if (!dfs(graph, next, !cur, !pre)) return false;
        }
        return true;
    }
};
```

<br/>

**2. BFS**
```cpp
enum { BLACK = 0, WHITE = 1};
class Solution {
public:
    vector<int> colors;
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        colors.resize(n, -1);
        
        bool res = 1;
        for (int i = 0; i < n; ++i)
        {
            if (colors[i] == -1)
            {
                res = res && bfs(graph, i);
                if (!res) break;   
            }
        }
        return res;
    }
    
    bool bfs(vector<vector<int>>& graph, int x)
    {
        queue<pair<int, bool>> que;
        que.emplace(x, BLACK);
        
        while (!que.empty())
        {
            auto [x, color] = que.front();
            que.pop();
            
            for (int next : graph[x])
            {
                if (colors[next] == -1)
                {
                    colors[next] = !color;
                    que.emplace(next, !color);
                }
                else if (colors[next] == color)
                    return false;
            }
        }
        return true;
    }
};
```
<br/>

**3. Disjoint Set**


> 如果是二分图的话，那么图中每个顶点的所有邻接点都应该属于同一集合，且不与顶点处于同一集合。因此我们可以使用并查集来解决这个问题，我们遍历图中每个顶点，将当前顶点的所有邻接点进行合并，并判断这些邻接点中是否存在某一邻接点已经和当前顶点处于同一个集合中了，若是，则说明不是二分图。
> 参考：https://leetcode-cn.com/problems/is-graph-bipartite/solution/bfs-dfs-bing-cha-ji-san-chong-fang-fa-pan-duan-er-/

If the graph is bipartite, then for each node `graph[i] = adjacent[...]`, the `adjacent[...]` will be in same set, and be in different set from `i`.

```cpp
class Solution {
public:
    vector<int> root;

    int find(int x) { return root[x] == -1 ? x : root[x] = find(root[x]); }
    
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y) root[y] = x;
    }

    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        root.resize(n, -1);
        for (int i = 0; i < n; ++i)
        {
            for (int j : graph[i])
            {
                if (find(i) == find(j))
                    return false;
                if (j != graph[i][0])
                    merge(graph[i][0], j);
            }
        }
        return true;
    }
};
```