## Split Array Largest Sum

Leetcode: [410. 分割数组的最大值](https://leetcode-cn.com/problems/split-array-largest-sum/)

给定一个非负整数数组 `nums` 和一个整数 `m` ，你需要将这个数组分成 `m` 个非空的连续子数组。设计一个算法使得这 `m` 个子数组各自和的最大值最小。

**例子1**

```text
输入：nums = [7,2,5,10,8], m = 2
输出：18
解释：
一共有四种方法将 nums 分割为 2 个子数组。 
其中最好的方式是将其分为 [7,2,5] 和 [10,8] 。
因为此时这两个子数组各自的和的最大值为18，在所有情况中最小。
```

**例子2**

```text
输入：nums = [1,4,4], m = 3
输出：4
```

最大值极小化问题，一般可以通过：
- 二分查找，枚举所有的可能的解，逐一验证，取最小值解决。
- 区间动态规划。



### 动态规划

令 $dp[i, j]$ 表示 $[0, i]$ 范围内，分割为 $j$ 段之后，得到的子数组各自和的最小值，并令 $\text{sub}[i, j]$ 表示区间 $[i, j]$ 中所有元素的和。考虑第 $j$ 段的产生：

- 在 $[0, i]$ 范围内，任意取一个位置 $k$ ，分割为两段 $[0, k], [k + 1, i]$ .
- 把 $[0, k]$ 分割为 $j - 1$ 段，剩余的一段是 $[k+1, i]$ ，那么可以得到 $j$ 段（即 $j$ 个连续子数组）。
- 枚举所有可能的 $k$ .

转移方程：
$$
dp[i, j] = \min\{\max(dp[k, j - 1], \text{sub}[k + 1, i]) \ |\  0 \le k < i\} \ \ \text{where} \ \  j \ge 2
$$
初始条件：

```cpp
dp[i, 0] = INF
dp[i, 1] = sub[0, i]
```

上述的 $\text{sub}[i, j]$ 可通过前缀和数组实现。

```cpp
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 1; i <= n; ++i)
            prefix[i] += prefix[i - 1] + nums[i - 1];
        
        vector<vector<int>> dp(n, vector<int>(m + 1, INT_MAX));
        /* initial state: split [0, i] into one segement. */
        for (int i = 0; i < n; ++i)
            dp[i][1] = prefix[i + 1];
        
        for (int i = 0; i < n; ++i)
            for (int j = 2; j <= m; ++j)
                for (int k = 0; k < i; ++k)
                    dp[i][j] = min(dp[i][j], max(dp[k][j - 1], prefix[i + 1] - prefix[k + 1]));

        return dp[n - 1][m];
    }
};
```



### 二分查找

- 二分的下界为数组的最大值，上界为所有元素之和。关键点在于如何判定 `m = (l + r) / 2` 是否为一个可行解。
- 类似于滑动窗口 + 贪心，从左到右累加，如果小于等于待校验的 `val` ，那么可以放在同一个子数组。否则，需要一个新的子数组。
- 时间复杂度 $O(n\log{\sum{\text{nums}}})$. 

```cpp
class Solution {
public:
    /* Divide nums into some sub-arrays. For each sub-array,
     * SUM(sub-array) <= val, under such limitation, can we
     * divide nums into m sub-arrays?
     */
    bool valid(vector<int> &nums, int m, int val)
    {
        int cnt = 1, sum = 0;
        for (int x : nums)
        {
            if (sum + x <= val)
                sum += x;
            else
            {
                sum = x;
                cnt += 1;
            }
        }
        return cnt <= m;
    }
    int splitArray(vector<int>& nums, int m)
    {
        /* l = 0 is wrong, the left bounder should be max_element */
        int l = *max_element(begin(nums), end(nums));
        int r = INT_MAX;
        /* [l, r) is equivalent to [l, m), m, [m + 1, r) */
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (valid(nums, m, mid))
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }
};
```

