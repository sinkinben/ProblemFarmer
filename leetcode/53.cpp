/*
    这个就是算法课教的DP
 */
#include "leetcode.h"
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        if (nums.size() == 1)
            return nums[0];

        int len = nums.size();
        int a[len];
        for (int i = 0; i < len; i++)
            a[i] = nums[i];

        for (int i = 1; i < len; i++)
        {
            if (a[i - 1] > 0)
                a[i] = nums[i] + a[i - 1];
        }

        int max = INT_MIN;
        for (int i = 0; i < len; i++)
        {
            if (max < a[i])
                max = a[i];
        }
        return max;
    }
};
