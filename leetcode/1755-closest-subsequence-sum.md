## Closest Subsequence Sum

Leetcode: [1755. Closest Subsequence Sum](https://leetcode.com/problems/closest-subsequence-sum/)

You are given an integer array `nums` and an integer `goal`.

You want to choose a subsequence of `nums` such that the sum of its elements is the closest possible to `goal`. That is, if the sum of the subsequence's elements is `sum`, then you want to **minimize the absolute difference** `abs(sum - goal)`.

Return *the **minimum** possible value of* `abs(sum - goal)`.

Note that a subsequence of an array is an array formed by removing some elements **(possibly all or none)** of the original array. 

**Example 1:**

```
Input: nums = [5,-7,3,5], goal = 6
Output: 0
Explanation: Choose the whole array as a subsequence, with a sum of 6.
This is equal to the goal, so the absolute difference is 0.
```

**Example 2:**

```
Input: nums = [7,-9,15,-2], goal = -5
Output: 1
Explanation: Choose the subsequence [7,-9,-2], with a sum of -4.
The absolute difference is abs(-4 - (-5)) = abs(1) = 1, which is the minimum.
```

**Example 3:**

```
Input: nums = [1,2,3], goal = -7
Output: 7
```

**Constraints:**

- `1 <= nums.length <= 40`
- `-107 <= nums[i] <= 1e7`
- `-1e9 <= goal <= 1e9`

**Solution**

Divide and conquer.

- Divide `nums` into two halfs. One is `[0, N / 2)`, another is `[N / 2, N)`.
- Use an **64bit**-integer `sub` to denote one subset of `nums`.
- Let `lsum[x]` denote the sum of subset `x`, the `rsum[x]` is similar.
- Sort `lsum` and `rsum`.
- For the target subset,
  - it can be only consist of `lsum[i]` (or `rsum[j]`).
  - it can be consist of `lsum[i]` and `rsum[j]`.

```cpp
class Solution {
public:
    /* count the number of trailing zero, x != 0 */
    int ctz(int64_t x)
    {
        int i = 0;
        while (((x >> i) & 1) == 0) ++i;
        return i;
    }
    int64_t subsetSum(vector<int> &nums, int64_t subset)
    {
        int64_t sum = 0, sub = subset;
        while (sub != 0)
        {
            int idx = ctz(sub);  /* I don't know why __builtin_ctz(sub) failed here. */
            sum += nums[idx];
            sub &= (sub - 1);
        }
        return sum;
    }
    int minAbsDifference(vector<int>& nums, int goal) {
        int N = nums.size();
        int n = N / 2;
        vector<int64_t> lsum(1 << n, 0), rsum(1 << (N - n), 0);
        
        for (int64_t x = 1; x < (1 << n); ++x)
            lsum[x] = subsetSum(nums, x);
        for (int64_t x = 1; x < (1 << (N - n)); ++x)
            rsum[x] = subsetSum(nums, x << n);
        
        
        sort(begin(lsum), end(lsum));
        sort(begin(rsum), end(rsum));
        
        int64_t res = INT_MAX;
        for (auto x : lsum) res = min(res, abs(x - goal));
        for (auto x : rsum) res = min(res, abs(x - goal));
        
        int l = 0, r = rsum.size() - 1;
        /* Double pointers to reach the closest target. */
        while (l < (1 << n) && r >= 0)
        {
            int64_t t = lsum[l] + rsum[r];
            res = min(res, abs(t - goal));
            if (t > goal) r--;
            else if (t < goal) l++;
            else break;
        }
        return res;
    }
};
```

