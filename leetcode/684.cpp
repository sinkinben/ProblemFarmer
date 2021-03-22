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
            {
                r[x] = y;
            }
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