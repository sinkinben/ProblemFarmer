#include "leetcode.h"
#include <functional>
class Solution
{
public:
    vector<int> exchange(vector<int> &nums)
    {
        return helper(nums, [](int x) { return x % 2 == 0; });
    }

    vector<int> helper(vector<int> &nums, function<bool(int x)> fcmp)
    {
        int len = nums.size();
        int i = 0, j = len - 1;
        while (i < j)
        {
            while (i < len && !fcmp(nums[i]))
                i++;
            while (j >= 0 && fcmp(nums[j]))
                j--;
            if (i > j)
                break;
            else
                swap(nums[i], nums[j]);
        }
        return nums;
    }
};