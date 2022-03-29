## 3Sum Samller

Leetcode: [259. 3Sum Smaller](https://leetcode-cn.com/problems/3sum-smaller/)

Given an array of `n` integers `nums` and an integer `target`, find the number of index triplets `i, j, k` with `0 <= i < j < k < n` that satisfy the condition `nums[i] + nums[j] + nums[k] < target`.

```text
Input: nums = [-2,0,1,3], target = 2
Output: 2
Explanation: Because there are two triplets which sums are less than 2:
[-2,0,1]
[-2,0,3]
```

**Solution**

```cpp
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int t) {
        int res = 0, n = nums.size();
        sort(begin(nums), end(nums));
        for (int i = 0; i < n; ++i)
            res += twoSumSmaller(nums, i + 1, t - nums[i]);
        return res;
    }
    int twoSumSmaller(vector<int> &nums, int start, int t) {
        int n = nums.size(), res = 0;
        int l = start, r = n - 1;
        while (l < r)
        {
            int val = nums[l] + nums[r];
            if (val < t) res += r - l, ++l;
            else --r;
        }
        return res;
    }
};
```