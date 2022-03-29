## Maximum Size Subarray Sum Equals k

Leetcode: [325. Maximum Size Subarray Sum Equals k](https://leetcode-cn.com/problems/maximum-size-subarray-sum-equals-k/)

Given an integer array `nums` and an integer `k`, return the maximum length of a subarray that sums to `k`. If there is not one, return 0 instead.

**Constraints:**

- `1 <= nums.length <= 2 * 1e5`
- `-1e4 <= nums[i] <= 1e4`
- `-1e9 <= k <= 1e9`

**Example - 1**

```text
Input: nums = [1,-1,5,-2,3], k = 3
Output: 4
Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.
```

**Example - 2**

```text
Input: nums = [-2,-1,2,1], k = 1
Output: 2
Explanation: The subarray [-1, 2] sums to 1 and is the longest.
```

<br/>

**Solution**

Hash Table and Prefix Sum.

- Why do we init `table` with `{0, -1}`?
  - Consider such a sequence `nums[0, ..., idx]`, if `sum([0, ..., idx])` is 0, then we can choose total sequence, whose length is `idx - (-1)`.

```cpp
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        unordered_map<int, int> table = {{0, -1}};  // prefix sum -> index
        int n = nums.size(), sum = 0, res = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            if (table.count(sum - k))
                res = max(res, i - table[sum - k]);
            
            if (!table.count(sum))
                table[sum] = i;
        }
        return res;
    }
};
```



[560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) is similar to this.