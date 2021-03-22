#include "leetcode.h"
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(nums);
        int maxval = dp[0];
        for (int i = 1; i < n; i++)
            dp[i] = max(nums[i], dp[i - 1] + nums[i]), maxval = max(maxval, dp[i]);
        return maxval;
    }
    int spaceOptimize(vector<int> &nums)
    {
        int dp = nums.front();
        int n = nums.size();
        int maxval = dp;
        for (int i = 1; i < n; i++)
            dp = max(dp + nums[i], nums[i]), maxval = max(maxval, dp);
        return maxval;
    }
};
