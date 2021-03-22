#include "leetcode.h"
class Solution
{
public:
    int countNegatives2(vector<vector<int>> &grid)
    {
        const int cols = grid[0].size();
        int pos = cols - 1;
        int ans = 0;
        for (auto &v : grid)
        {
            while (pos >= 0 && v[pos] < 0)
                pos--;
            // now v[pos] >= 0 or pos = -1
            if (pos == -1)
                ans += cols;
            else
                ans += cols - 1 - pos;
        }
        return ans;
    }
    int countNegatives(vector<vector<int>> &grid)
    {
        int ans = 0;
        for (auto &&v : grid)
        {
            int l = 0, r = (int)v.size() - 1, pos = -1;
            while (l <= r)
            {
                int mid = l + (r - l) / 2;
                if (v[mid] < 0)
                {
                    pos = mid;
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            // cout << pos << endl;
            if (pos != -1)
                ans += v.size() - pos;
        }
        return ans;
    }
};

int main()
{
    vector<vector<int>> v = {{4, 3, 2, -1},
                             {3, 2, 1, -1},
                             {1, 1, -1, -2},
                             {-1, -1, -2, -3}};

    Solution sol;
    cout << sol.countNegatives2(v) << endl;
}