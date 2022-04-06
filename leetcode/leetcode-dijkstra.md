## Dijkstra

Leetcode:

- [743. Network Delay Time](https://leetcode.com/problems/network-delay-time/)
- [1976. Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/)



## Code Template

```cpp
struct node_t
{
    int vex, cost;
    node_t(int v, int c) : vex(v), cost(c) {}
    bool operator<(const node_t &n) const { return cost > n.cost; }
};
unordered_map<int, unordered_map<int, int>> graph;
/* @n - There are `n` vertices in the graph.
 * @start - The source of shortest path.
 * @return - The length of shortest path from `start` to the others vertices.
 */
vector<int> dijkstra(int n, int start)
{
    vector<bool> vis(n, false);
    vector<int> dis(n, 0x3f3f3f3f);
    dis[start] = 0;
    priority_queue<node_t> q;
    q.emplace(start, 0);
    while (!q.empty())
    {
        int u = q.top().vex;
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        // graph[u][v] = c
        for (auto [v, c] : graph[u])
        {
            if (!vis[v] && dis[v] > dis[u] + c)
            {
                dis[v] = dis[u] + c;
                q.emplace(v, dis[v]);
            }
        }
    }
    return dis;
}
```



## Network Delay Time

Leetcode: https://leetcode.com/problems/network-delay-time/

You are given a network of `n` nodes, labeled from `1` to `n`. You are also given `times`, a list of travel times as directed edges `times[i] = (ui, vi, wi)`, where `ui` is the source node, `vi` is the target node, and `wi` is the time it takes for a signal to travel from source to target.

We will send a signal from a given node `k`. Return the time it takes for all the `n` nodes to receive the signal. If it is impossible for all the `n` nodes to receive the signal, return `-1`.

<img src="https://assets.leetcode.com/uploads/2019/05/23/931_example_1.png" />

```text
Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2
```

**Solution**

The answer is the max-value of all the shortest path (which are starting at `k`).

```cpp
struct node_t
{
    int vex, cost;
    node_t(int v, int c) : vex(v), cost(c) {}
    /* to make a min-heap with priority_queue<node_t> */
    bool operator<(const node_t &n) const { return cost > n.cost; }
};
class Solution {
public:
    unordered_map<int, unordered_map<int, int>> graph;
    const int INF = 0x3f3f3f3f;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        /* the id of vertices should minus 1 */
        for (auto &v : times)
            graph[v[0] - 1][v[1] - 1] = v[2];

        auto dis = dijkstra(n, k - 1);
        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            if (dis[i] == INF) return -1;
            res = max(dis[i], res);
        }
        return res;
    }
    
    vector<int> dijkstra(int n, int start)
    {
        vector<bool> vis(n, false);
        vector<int> dis(n, INF);
        dis[start] = 0;

        priority_queue<node_t> que;
        que.emplace(start, 0);
        while (!que.empty())
        {
            int u = que.top().vex;
            que.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            // graph[u][v] = c
            for (auto [v, c] : graph[u])
                if (!vis[v] && dis[v] > dis[u] + c)
                    dis[v] = dis[u] + c, que.emplace(v, dis[v]);
        }
        return dis;
    }
};
```



## Number of Ways to Arrive at Destination

Leetcode: https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/

You are in a city that consists of `n` intersections numbered from `0` to `n - 1` with **bi-directional** roads between some intersections. The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.

You are given an integer `n` and a 2D integer array `roads` where `roads[i] = [ui, vi, timei]` means that there is a road between intersections `ui` and `vi` that takes `timei` minutes to travel. You want to know in how many ways you can travel from intersection `0` to intersection `n - 1` in the **shortest amount of time**.

Return *the **number of ways** you can arrive at your destination in the **shortest amount of time***. Since the answer may be large, return it **modulo** `109 + 7`.

<img src="https://assets.leetcode.com/uploads/2021/07/17/graph2.png" style="background: white; width:20%"/>

```text
Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
Output: 4
Explanation: The shortest amount of time it takes to go from intersection 0 to intersection 6 is 7 minutes.
The four ways to get there in 7 minutes are:
- 0 -> 6
- 0 -> 4 -> 6
- 0 -> 1 -> 2 -> 5 -> 6
- 0 -> 1 -> 3 -> 5 -> 6
```

**Solution**

The problem here is to get the number of shortest path.

Let `dp[i]` denote the number of shortest path from `start` to `i` in Dijkstra algorithm. Then we have
$$
dp[i] = \sum_{(j, i) \in P}{dp[j]}
$$
where $(j, i) \in P$ denotes `j` is the previous vertex in one shortest path. Please note that there may exist multiple shortest paths.

Here is the code. **The type of `cost` should be `int64_t`.**

```cpp
struct node_t
{
    int vex;
    int64_t cost;
    node_t(int v, int64_t c) : vex(v), cost(c) {}
    bool operator<(const node_t &n) const { return cost > n.cost; }
};
class Solution {
public:
    const int MOD = 1e9 + 7;
    const int64_t INF = LLONG_MAX / 2 - 1;
    unordered_map<int, unordered_map<int, int>> graph;

    int countPaths(int n, vector<vector<int>>& roads) {
        for (auto &v : roads)
            graph[v[0]][v[1]] = graph[v[1]][v[0]] = v[2];
        return dijkstra(n, 0);
    }

    int dijkstra(int n, int start)
    {
        vector<bool> vis(n, false);
        vector<int64_t> dis(n, INF), dp(n, 0);
        dis[start] = 0, dp[start] = 1;
        
        priority_queue<node_t> q;
        q.emplace(start, 0);
        while (!q.empty())
        {
            int u = q.top().vex;
            q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            // graph[u][v] = c
            for (auto [v, c] : graph[u])
            {
                if (vis[v]) continue;
                if (dis[v] == dis[u] + c)
                    dp[v] = (dp[v] + dp[u]) % MOD;
                if (dis[v] > dis[u] + c)
                {
                    dp[v] = dp[u];
                    dis[v] = dis[u] + c;
                    q.emplace(v, dis[v]);
                }
            }
        }
        return dp[n - 1];
    }
};
```

