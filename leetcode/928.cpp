#include <unordered_set>
#include <unordered_map>
#include "leetcode.h"
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
        // the set {...} means the nodes which initial node x will infect
        // counter[x] = k
        // the k means that the non-infected node x will be infected by initial nodes for k times
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

        // to find node we want
        int ans = N + 1, maxInfected = -1;
        for (int u : initial)
        {
            int sum = 0;
            for (int x : table[u])
                if (counter[x] == 1)
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

int main()
{
}