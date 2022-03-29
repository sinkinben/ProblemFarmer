## Subarray Sum Equals K

Leetcode:

- [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)
- [325. Maximum Size Subarray Sum Equals k](https://leetcode-cn.com/problems/maximum-size-subarray-sum-equals-k/)

Both of them are problems of "Hash Table + Prefix Sum".



## Subarray Sum Equals K

```cpp
class Solution
{
public:
    int subarraySum(vector<int>& nums, int k) 
    {
        // prefix sum -> number of subarray whose sum is sum
        unordered_map<int, int> prefix = {{0, 1}};
        int sum = 0, cnt = 0;
        for (int x : nums)
        {
            sum += x;
            /* prefix[sum] - prefix[sum - k] will get the subarray whose sum = k */
            if (prefix.count(sum - k))
                cnt += prefix[sum - k];
            ++prefix[sum];
        }
        return cnt;
    }
};
```



## Maximum Size Subarray Sum Equals k

Why do we init `table` with `{0, -1}`?

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

