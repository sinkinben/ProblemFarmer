## Partition Equal Subset Sum (2 Partition)

Leetcode: https://leetcode.com/problems/partition-equal-subset-sum/

Given a **non-empty** array `nums` containing **only positive integers**, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

**Example 1:**

```
Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
```

<br/>

**Solution**

- 2-Partition Problem: Divide `nums` into two non-empty subset, two subsets have equal sum.
- Reduce it into **01-Knapsack** problem.
  - For each item, `value` is equal to `cost` .
  - we have a knapsack with `capacity = sum / 2`, can we get the max-value `sum / 2`.

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) 
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        int n = nums.size();
        vector<int> dp(sum / 2 + 1, 0);
        
        for (int i = 1; i <= n; ++i)
        {
            for (int j = sum / 2; j >= 0; --j)
            {
                int x = nums[i - 1];
                dp[j] = max(dp[j], (j >= x) ? dp[j - x] + x : 0);
            }
        }
        return dp[sum / 2] == sum / 2;
    }
};
/* let dp[i, j] denote that: under the limitation of volumn j, the max value we can get in the items[1 - i]
 * dp[i, j] = max(dp[i-1, j], dp[i-1, j-x] + x)
 * return dp[n, sum/2] == sum/2
 */
```



## Matchsticks to Square (4 Partition)

Leetcode: https://leetcode.com/problems/matchsticks-to-square/

You are given an integer array `matchsticks` where `matchsticks[i]` is the length of the `ith` matchstick. You want to use **all the matchsticks** to make one square. You **should not break** any stick, but you can link them up, and each matchstick must be used **exactly one time**.

Return `true` if you can make this square and `false` otherwise.

**Example 1:**

```
Input: matchsticks = [1,1,2,2,2]
Output: true
Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
```

**Example 2:**

```
Input: matchsticks = [3,3,3,3,4]
Output: false
Explanation: You cannot find a way to form a square with all the matchsticks.
```

**Constraints:**

- `1 <= matchsticks.length <= 15`
- `1 <= matchsticks[i] <= 1e8`

<br/>

**Solution**

It's 4-Partition Problem.

<br/>

**Backtracking and Pruning (AC)**

I copy this code from "k Partition Problem" as follows.

- `sort` the `nums` in decreasing order (to prune the backtracking tree).
- Allocate 4 buckets, try to put each number in each bucket.

```cpp
class Solution {
public:
    bool makesquare(vector<int>& nums, int k = 4) {
        int n =  nums.size();
        int sum = accumulate(begin(nums), end(nums), 0);

        if (sum % k != 0) return false;
        
        vector<int> buckets(k, 0);
        sort(begin(nums), end(nums), greater<int>());
        return backtrack(nums, buckets, 0, sum / k);
    }
    
    bool backtrack(vector<int>& nums, vector<int> &buckets, int idx, int target)
    {
        if (idx >= nums.size())
        {
            for (int x : buckets) if (x != target) return false;
            return true;
        }
        
        int val = nums[idx];
        for (int &x : buckets)
        {
            if (x + val > target) continue;
            x += val;
            if (backtrack(nums, buckets, idx + 1, target)) return true;
            x -= val;
        }
        return false;
    }
};
```



## Partition to K Equal Sum Subsets (k Partition)

Leetcode: https://leetcode.com/problems/partition-to-k-equal-sum-subsets/

Given an integer array `nums` and an integer `k`, return `true` if it is possible to divide this array into `k` non-empty subsets whose sums are all equal.

**Example 1:**

```
Input: nums = [4,3,2,3,5,2,1], k = 4
Output: true
Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
```

**Example 2:**

```
Input: nums = [1,2,3,4], k = 3
Output: false
```

**Constraints:**

- `1 <= k <= nums.length <= 16`
- `1 <= nums[i] <= 1e4`
- The frequency of each element is in the range `[1, 4]`.

<br/>



**Backtracking (TLE)**

- Sort the `nums` in decreasing (non-increasing) order (to prune the backtracking tree).
- Allocate `k` buckets.
- For each `nums[idx]`, try put it in each bucket `buckets[i]`.

```cpp
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n =  nums.size();
        int sum = accumulate(begin(nums), end(nums), 0);

        if (sum % k != 0) return false;
        
        vector<int> buckets(k, 0);
        sort(begin(nums), end(nums), greater<int>());
        return backtrack(nums, buckets, 0, sum / k);
    }
    
    bool backtrack(vector<int>& nums, vector<int> &buckets, int idx, int target)
    {
        if (idx >= nums.size())
        {
            for (int x : buckets) if (x != target) return false;
            return true;
        }
        
        int val = nums[idx];
        for (int &x : buckets)
        {
            if (x + val > target) continue;
            x += val;
            if (backtrack(nums, buckets, idx + 1, target)) return true;
            x -= val;
        }
        return false;
    }
};
```

<br/>



**Bitmask DP**

We use an integer `int x` to denote a subset of `nums`, since `1 <= n <= 16`.

Let `dp[x][i] = 0/1` denote whether if the the subset `x` can be divided into `i` parts (and each part has equal sum). Then we have:

```cpp
dp[x + subset][i] |= dp[x][i - 1] for any valid `subset` that are disjoint with `x`
```

- The "valid subset" means, those subsets whose sum is `avg = sum / k`.
- "disjoint" means `(x & subset) == 0`, since we can NOT use same number twice.

Here is the source code. Time complexity is $O(k \cdot 4^n)$.

```cpp
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = accumulate(begin(nums), end(nums), 0);
        if (total % k) return false;

        int n = nums.size();
        int avg = total / k;
        vector<vector<uint8_t>> dp(1 << n, vector<uint8_t>(k + 1, 0));
        
        /* dividing empty subset into 0 parts is always true */
        dp[0][0] = 1;
        
        vector<int> validsub;
        for (int subset = 1; subset < (1 << n); ++subset)
        {
            /* sum of current subset */
            int sum = 0, sub = subset;
            // for (int i = 0; i < n; ++i) sum += ((subset >> i) & 1) ? nums[i] : 0;
            while (sub)
            {
                int idx = __builtin_ctz(sub);
                sum += nums[idx];
                sub &= (sub - 1);
            }
            /* if sum of subset is avg, then it's a valid subset */
            if (sum == avg)
                validsub.emplace_back(subset);
        }
        for (int x = 0; x < (1 << n); ++x)
            for (int i = 1; i <= k; ++i)
                for (int sub : validsub)
                    if ((x & sub) == 0)
                    	dp[x + sub][i] |= dp[x][i - 1];
        return dp[(1 << n) - 1][k];
    }
};
```

Space optimization on `dp`, since `dp[x + sub][i]` only depends on `dp[x][i - 1]`.

```cpp
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = accumulate(begin(nums), end(nums), 0);
        if (total % k) return false;

        int n = nums.size();
        int avg = total / k;
        vector<uint8_t> dp(1 << n, 0);
        dp[0] = 1;
        vector<int> validsub;
        for (int subset = 1; subset < (1 << n); ++subset)
        {
            /* sum of current subset */
            int sum = 0, sub = subset;
            while (sub)
            {
                int idx = __builtin_ctz(sub);
                sum += nums[idx];
                sub &= (sub - 1);
            }
            /* if sum of subset is avg, then it's a valid subset */
            if (sum == avg)
                validsub.emplace_back(subset);
        }
        for (int x = 0; x < (1 << n); ++x)
            for (int i = 1; i <= k; ++i)
                for (int sub : validsub)
                    if ((x & sub) == 0)
                    	dp[x + sub] |= dp[x];
        return dp[(1 << n) - 1];
    }
};
```

