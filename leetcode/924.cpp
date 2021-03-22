#include "leetcode.h"
#include <unordered_set>
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