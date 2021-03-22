#include "leetcode.h"
class Solution
{
public:
    int massage(vector<int> &nums)
    {
        return spaceOptimize(nums);
    }

    int commonDP(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = 0, dp[0][1] = nums[0];
        int maxval = nums[0];
        for (int i = 1; i < n; i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0] + nums[i];
            maxval = max(maxval, max(dp[i][0], dp[i][1]));
        }
        return maxval;
    }

    int spaceOptimize(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        int dp0 = 0, dp1 = nums[0];
        int maxval = dp1;
        int t;
        for (int i = 1; i < n; i++)
        {
            t = dp1;
            dp1 = dp0 + nums[i];
            dp0 = max(dp0, t);
            maxval = max(maxval, max(dp0, dp1));
        }
        return maxval;
    }
};