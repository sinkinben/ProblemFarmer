#include "leetcode.h"
#define max(a, b) ((a) > (b) ? (a) : (b))
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int len = nums.size();
        vector<int> dp(nums);
        for (int i = 1; i < len; i++)
            dp[i] = max(nums[i], nums[i] + dp[i - 1]);
        int ans = dp[0];
        for (auto x : dp)
            ans = max(ans, x);
        return ans;
    }

    int maxSubArray2(vector<int> &nums)
    {
        int len = nums.size();
        int pre = nums[0], dp = 0;
        int ans = 0;
        for (int i = 1; i < len; i++)
        {
            dp = max(nums[i], nums[i] + pre);
            pre = dp;
            ans = max(ans, dp);
        }
        return ans;
    }
};