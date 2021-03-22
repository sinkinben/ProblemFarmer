#include "../leetcode/leetcode.h"
class Solution
{
public:
    bool findNumberIn2DArray(vector<vector<int>> &matrix, int target)
    {
        return method2(matrix, target);
    }
    bool method2(vector<vector<int>> &m, int t)
    {
        if (m.size() == 0 || m[0].size() == 0)
            return false;
        int rows = m.size();
        int cols = m[0].size();
        int i = 0, j = cols - 1;
        while (i < rows && j >= 0)
        {
            if (m[i][j] == t)
                return true;
            else if (t < m[i][j])
                j--;
            else
                i++;
        }
        return false;
    }

    bool method1(vector<vector<int>> &m, int t)
    {
        for (auto &v : m)
        {
            if (binsearch(v, t))
                return true;
        }
        return false;
    }
    bool binsearch(vector<int> &v, int t)
    {
        int len = v.size();
        if (len == 0)
            return false;
        int l = 0, r = len - 1;
        while (l <= r)
        {
            if (l == r)
                return v[l] == t;
            int m = l + (r - l) / 2;
            if (t < v[m])
                r = m - 1;
            else if (v[m] < t)
                l = m + 1;
            else
                return true;
        }
        return false;
    }
};

