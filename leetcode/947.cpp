#include "leetcode.h"
#include <unordered_map>
#include <algorithm>
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