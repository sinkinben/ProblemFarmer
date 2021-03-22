#include <unordered_map>
#include <cassert>
#include "leetcode.h"
class Solution
{
public:
    vector<int> root;
    vector<int> findRedundantDirectedConnection(vector<vector<int>> &edges)
    {
        root.resize(edges.size() + 2, -1);
        int t = checkIndegree(edges);
        if (t == -1)
        {
            for (auto &v : edges)
            {
                int x = v[0], y = v[1];
                if (find(x) == y)
                    return v;
                merge(x, y);
            }
        }
        else
        {
            vector<vector<int>> candidate;
            for (auto &v : edges)
            {
                if (v[1] == t)
                    candidate.emplace_back(v);
                else
                    merge(v[0], v[1]);
            }
            assert(candidate.size() == 2);
            auto &v = candidate[0];
            int a = find(v[0]), b = find(v[1]);
            if (find(a) != b)
                return candidate[1];
            return v;
        }
        // should not be here
        return vector<int>();
    }

    int checkIndegree(vector<vector<int>> &egdes)
    {
        unordered_map<int, int> m;
        for (auto &v : egdes)
            m[v[1]]++;
        for (auto &p : m)
            if (p.second >= 2)
                return p.first;
        return -1;
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
};
int main()
{
    // vector<vector<int>> v = {{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 5}};
    vector<vector<int>> v = {{1, 2}, {1, 3}, {2, 3}};
    Solution sol;
    auto x = sol.findRedundantDirectedConnection(v);
    cout << x[0] << ' ' << x[1] << endl;
}