#include "leetcode.h"
#include <queue>
#include <unordered_map>
class Solution
{
public:
    unordered_map<string, int> m;
    unordered_map<int, unordered_map<int, double>> graph;
    vector<double> calcEquation(vector<vector<string>> &equations,
                                vector<double> &values,
                                vector<vector<string>> &queries)
    {
        int V = hashstring(equations);

        // create gragh
        for (size_t i = 0; i < equations.size(); i++)
        {
            int a = m[equations[i][0]], b = m[equations[i][1]];
            double v = values[i];
            graph[a][b] = v, graph[b][a] = 1 / v;
            graph[a][a] = graph[b][b] = 1;
        }

        // exec
        vector<double> result;
        vector<bool> visited(V, false);
        for (auto &v : queries)
        {
            string &a = v[0], &b = v[1];
            if (m.find(a) == m.end() || m.find(b) == m.end())
            {
                result.emplace_back(-1);
                continue;
            }
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
int main()
{
    vector<vector<string>> e = {{"x1", "x2"}, {"x2", "x3"}, {"x1", "x4"}, {"x2", "x5"}};
    vector<double> v = {3.0, 0.5, 3.4, 5.6};
    vector<vector<string>> q = {{"x2", "x4"}, {"x1", "x5"}, {"x1", "x3"}, {"x5", "x5"}, {"x5", "x1"}, {"x3", "x4"}, {"x4", "x3"}, {"x6", "x6"}, {"x0", "x0"}};
    Solution sol;
    auto ans = sol.calcEquation(e, v, q);
    for (auto x : ans)
    {
        cout << x << ' ';
    }
}

/*
{{"x1","x2"},{"x2","x3"},{"x1","x4"},{"x2","x5"}}
{3.0,0.5,3.4,5.6}
{{"x2","x4"},{"x1","x5"},{"x1","x3"},{"x5","x5"},{"x5","x1"},{"x3","x4"},{"x4","x3"},{"x6","x6"},{"x0","x0"}}

and = {1.13333,16.8,1.5,1.0,0.05952,2.26667,0.44118,-1.0,-1.0}
 */