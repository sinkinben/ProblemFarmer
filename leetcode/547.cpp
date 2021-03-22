#include "leetcode.h"
#include <algorithm>
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
            for (int j = i; j < len; j++)
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

    int findRoot(vector<int> &v, int x)
    {
        return (v[x] == -1) ? x : (v[x] = findRoot(v, v[x]));
    }
};
