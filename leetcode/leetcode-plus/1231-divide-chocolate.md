## Divide Chocolate

Leetcode: [1231. Divide Chocolate](https://leetcode-cn.com/problems/divide-chocolate/)

You have one chocolate bar that consists of some chunks. Each chunk has its own sweetness given by the array `sweetness`.

You want to share the chocolate with your `k` friends so you start cutting the chocolate bar into `k + 1` pieces using `k` cuts, each piece consists of some **consecutive** chunks.

Being generous, you will eat the **piece with the minimum total sweetness** and give the other pieces to your friends.

Find the **maximum** total sweetness of the piece you can get by cutting the chocolate bar optimally.

**Example 1**

```
Input: sweetness = [1,2,3,4,5,6,7,8,9], k = 5
Output: 6
Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9]
```

**Example 2**

```
Input: sweetness = [5,6,7,8,9,1,2,3,4], k = 8
Output: 1
Explanation: There is only one way to cut the bar into 9 pieces.
```

**Example 3**

```
Input: sweetness = [1,2,2,1,2,2,1,2,2], k = 2
Output: 5
Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]
```

**Constraints:**

- `0 <= k < sweetness.length <= 1e4`
- `1 <= sweetness[i] <= 1e5`

<br/>

**Solution**

- Divide the array `sweetness` into `k + 1` (consecutive) subarrays.
- For each division, it will have a min-sum among these sub-arrays.
- Maximize such min-sum.



## Binary Search

```cpp
class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        int sum = 0, minval = INT_MAX;
        for (int x : sweetness)
            sum += x, minval = min(minval, x);
        int l = minval, r = sum;
        /* k friends, we need k + 1 parts */
        k += 1;
        while (l < r)
        {
            int m = l + (r - l) / 2;
            /* Pay attention to m + 1,
             * [l, r) is equivalent [l, m), m, [m + 1, r)
             */
            if (check(sweetness, m + 1, k)) l = m + 1;
            else r = m;
        }
        return l;
    }
    
    /* For each subarray, SUM(sub) >= limit. Under such limitation, 
     * can we divide `nums` into k subarrays?
     */
    bool check(vector<int> &nums, int limit, int k)
    {
        int cnt = 0, sum = 0;
        for (int x : nums)
        {
            sum += x;
            if (sum >= limit)
                cnt += 1, sum = 0;
		}
        return cnt >= k;
    }
};
```





## TLE DP

Time complexity is $O(n^2k)$, it's a **TLE** solution.

Let `dp[i, j]` denote in the range of `[0, i]`, and divide the `sweetness` into `j` subarrays, the max-min sweetness we can get.

Then we have:
$$
dp[i, j] = \max\{ \min{(dp[k, j - 1], \text{sub}[k+1, i])} \ \ | \ \ 0 \le k < i \} \ \ \text{where} \ \ j \ge 2
$$

```cpp
class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        k += 1;
        int n = sweetness.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 1; i <= n; ++i)
            prefix[i] = prefix[i - 1] + sweetness[i - 1];
        
        vector<vector<int>> dp(n, vector(k + 1, 0));
        for (int i = 0; i < n; ++i)
            dp[i][1] = prefix[i + 1];
        
        for (int i = 0; i < n; ++i)
            for (int j = 2; j <= k; ++j)
                for (int idx = 0; idx < i; ++idx)
                    dp[i][j] = max(dp[i][j], min(dp[idx][j - 1], prefix[i + 1] - prefix[idx + 1]));

        return dp[n - 1][k];
    }
};
```

