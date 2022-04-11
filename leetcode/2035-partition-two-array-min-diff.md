## Partition Array Into Two Arrays to Minimize Sum Difference

Leetcode: [2035. Partition Array Into Two Arrays to Minimize Sum Difference](https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/)

You are given an integer array `nums` of `2 * n` integers. You need to partition `nums` into **two** arrays of length `n` to **minimize the absolute difference** of the **sums** of the arrays. To partition `nums`, put each element of `nums` into **one** of the two arrays.

Return *the **minimum** possible absolute difference*.

**Constraints:**

- `1 <= n <= 15`
- `nums.length == 2 * n`
- `-1e7 <= nums[i] <= 1e7`

**Example**

```
Input: nums = [2,-1,0,4,-2,-9]
Output: 0
Explanation: One optimal partition is: [2,4,-9] and [-1,0,-2].
The absolute difference between the sums of the arrays is abs((2 + 4 + -9) - (-1 + 0 + -2)) = 0.
```



**Brute Force Solution (TLE/MLE)**

Let `dp[x]` denote the sum of subset `x`. Both time complexity and space complexity are $O(2^{2n})$.

```cpp
class Solution {
public:    
    int minimumDifference(vector<int>& nums) {
        int n = nums.size();
        vector<int> sum(1 << n, 0);
        for (int subset = 1; subset < (1 << n); ++subset)
        {
            int smaller = subset & (subset - 1);
            sum[subset] = sum[smaller] + nums[__builtin_ctz(subset)];
        }

        int diff = INT_MAX;
        int all = (1 << n) - 1;
        for (int s1 = 0; s1 < (1 << n); ++s1)
        {
            int s2 = all - s1;
            if (__builtin_popcount(s1) != n / 2 || __builtin_popcount(s2) != n / 2)
                continue;
            diff = min(diff, abs(sum[s1] - sum[s2]));
        }
        return diff;
    }
};
```



**Divide and Conquer Solution**

Analysis:

- Divide the array into two arrays with `size = n`, and minimize the `diff = abs(p1 - p2)`.
- Since `p2 = sum - p1`, we can have `diff = abs(sum - 2 * p1) `.

Algorithm details:

- Divide `nums` into left-part `[0, ..., n)` and right-part `[n, 2n)`.
- Use an 32-bit integer `x` to denote one subset of `nums`.

- Let `lsum[cnt]` gather the sum of those subsets `x` , where `x` have `cnt` 1-bit. `rsum` is similar.
- For each `lval = lsum[cnt][i]`, its complementary set (补集) is `rval = rsum[n - cnt][j]`. We can choose `lval + rval` as one of the two arrays.

Both time complexity and space complexity are $O(n \cdot 2^n)$.

```cpp
using vec = vector<int>;
using vec2 = vector<vec>;
class Solution
{
  public:
    int subsetSum(vector<int> &nums, int subset)
    {
        int sub = subset, sum = 0;
        while (sub)
        {
            int idx = __builtin_ctz(sub);
            sum += nums[idx];
            sub &= (sub - 1);
        }
        return sum;
    }
    int minimumDifference(vector<int> &nums)
    {
        int N = nums.size();
        int n = N / 2;
        vec2 lsum(n + 1, vec()), rsum(n + 1, vec());

        for (int x = 0; x < (1 << n); ++x)
        {
            /* x has cnt 1-bit in binary encoding. */
            int cnt = x ? __builtin_popcount(x) : 0;
            int lsub = x, rsub = (x << n);
            lsum[cnt].push_back(subsetSum(nums, lsub));
            rsum[cnt].push_back(subsetSum(nums, rsub));
        }

        for (auto &v : rsum)
            sort(begin(v), end(v));

        int diff = INT_MAX;
        int sum = lsum[n][0] + rsum[n][0];
        for (int i = 0; i <= n; ++i)
        {
            for (int lval : lsum[i])
            {
                auto rval = lower_bound(begin(rsum[n - i]), end(rsum[n - i]), sum / 2 - lval);
                if (rval != end(rsum[n - i]))
                    diff = min(diff, abs(sum - 2 * (lval + *rval)));
            }
        }
        return diff;
    }
};
/* Why binary search by (sum/2 - lval) ?
 * We have: p1 = lval + rval, 
 * we want to minimize diff = abs(sum - 2 * (lval + rval))
 * let diff = 0, then rval = (sum / 2 - lval),
 * hence we want rval as close to (sum / 2 - lval) as possible.
 */
```

