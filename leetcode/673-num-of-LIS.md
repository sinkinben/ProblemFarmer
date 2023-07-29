## [Leetcode] 673. Number of Longest Increasing Subsequence

Link: https://leetcode.com/problems/number-of-longest-increasing-subsequence/

Given an integer array `nums`, return *the number of longest increasing subsequences.*

**Notice** that the sequence has to be **strictly** increasing. 

**Example 1:**

```
Input: nums = [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
```

**Example 2:**

```
Input: nums = [2,2,2,2,2]
Output: 5
Explanation: The length of the longest increasing subsequence is 1, and there are 5 increasing subsequences of length 1, so output 5.
```

**Constraints:**

- `1 <= nums.length <= 2000`
- `-1e6 <= nums[i] <= 1e6`

<br/>

**题解**

本题实际上是动态规划的子问题，求可行解的数目。

对于可行解，即 LIS 的最大长度，一个经典的 $O(n^2)$ 解法是，令 `dp[i]` 表示以 `nums[i]` 结尾的 LIS 的长度，那么有：

```text
fill dp with 1
dp[i] = max(dp[i], dp[j] + 1) for 0 <= j < i and a[j] < a[i]
return max(dp)
```

现在令 `cnt[i]` 表示以 `nums[i]` 结尾的最长 LIS 的数量，那么有：

```cpp
// 若 nums[...j] 加上 nums[i] 可得到更长的 LIS
cnt[i] = cnt[j]           if nums[j] < nums[i] && dp[j] + 1 > dp[i]  
// 若 nums[...j] 加上 nums[i] 只能得到与目前为止等长的 LIS (即在 j 之前已有一个长度为 dp[i] 的 LIS)
cnt[i] = cnt[i] + cnt[j]  if nums[j] < nums[i] && dp[j] + 1 == dp[i]
```

代码实现：

```cpp
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> dp(n, 1), cnt(n, 1);
        int maxlen = 1;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                {
                    if (dp[j] + 1 > dp[i])
                    {
                        cnt[i] = cnt[j];
                        dp[i] = dp[j] + 1;
                    }
                    else if (dp[j] + 1 == dp[i])
                        cnt[i] += cnt[j];
                }
            }
            maxlen = max(maxlen, dp[i]);
        }
        
        int res = 0;
        for (int i = 0; i < n; ++i)
            res += (dp[i] == maxlen) ? cnt[i] : 0;
        return res;
    }
};

/* Let dp[i] denote the max-length of LIS, ending with nums[i]
 * cnt[i] denote the number of LIS with max-length, ending with nums[i]
 */
```

