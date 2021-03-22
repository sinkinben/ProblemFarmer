#include "leetcode.h"
class Solution
{
public:
    int rob(vector<int> &nums)
    {
        return spaceOptimize(nums);
    }

    int officialSolution(vector<int> &v)
    {
        int n = v.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return v[0];
        int f0 = v[0], f1 = max(v[0], v[1]), f2 = max(f0, f1);
        for (int i = 2; i < n; i++)
        {
            f2 = max(f1, f0 + v[i]);
            f0 = f1, f1 = f2;
        }
        return f2;
    }

    int commonDP(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];
        vector<int> dp0(n, 0), dp1(n, 0);
        dp0[0] = 0, dp1[0] = nums[0];
        int maxval = max(nums[0], nums[1]);
        for (int i = 1; i < n; i++)
        {
            dp0[i] = max(dp0[i - 1], dp1[i - 1]);
            dp1[i] = dp0[i - 1] + nums[i];
            maxval = max(maxval, max(dp0[i], dp1[i]));
        }
        return maxval;
    }

    int spaceOptimize(vector<int> &v)
    {
        int n = v.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return v[0];
        int dp0 = 0, dp1 = v[0];
        int maxval = v[0];
        int t;
        for (int i = 1; i < n; i++)
        {
            t = dp0;
            dp0 = max(dp0, dp1);
            dp1 = v[i] + t;
            maxval = max(dp0, dp1);
        }
        return maxval;
    }
};
