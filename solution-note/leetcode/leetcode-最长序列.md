## [leetcode] 最长序列题目

Leetcode 的最长 XX 序列的一系列题目。

我🤮了，你呢？

与 DP 无关的其实可以不用看，与 DP 有关的最 XX 序列，关键点在于要区分**是否连续**。一般要求连续都很好写（并且多数也能用滑动窗口完成），如果不要求连续，一般状态都定义为以 `a[i]` 结尾的，满足要求的序列的和/长度。

一维 DP 题目：

- [674. 最长连续递增序列](https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/)
- [300. 最长递增子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)
- [53. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)

二维 DP 题目：

- [516. 最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence/)
- [1143. 最长公共子序列](https://leetcode-cn.com/problems/longest-common-subsequence/)

与 DP 无关的题目：

- [521. 最长特殊序列 Ⅰ](https://leetcode-cn.com/problems/longest-uncommon-subsequence-i/)
- [128. 最长连续序列](https://leetcode-cn.com/problems/longest-consecutive-sequence/)

TODO:

- [594. 最长和谐子序列](https://leetcode-cn.com/problems/longest-harmonious-subsequence/)
- [522. 最长特殊序列 II](https://leetcode-cn.com/problems/longest-uncommon-subsequence-ii/)
- [1218. 最长定差子序列](https://leetcode-cn.com/problems/longest-arithmetic-subsequence-of-given-difference/)
- [1027. 最长等差数列](https://leetcode-cn.com/problems/longest-arithmetic-subsequence/)

## 一维 DP

### 最长连续递增序列

题目：[674. 最长连续递增序列](https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/)

Longest Continuous Increasing Subsequence, LCIS.

**要求连续。**

定义 `dp[i]` 是以 `a[i]` 结尾的，满足条件的最长序列的长度。

转移方程

```
dp[i] = 1           if a[i-1] >= a[i]
dp[i] = dp[i-1] + 1 if a[i-1] <  a[i]
```

注意 `n == 0` 的情况即可。

```cpp
class Solution {
public:
    int findLengthOfLCIS(vector<int>& a) 
    {
        int dp=1, n=a.size(), ans=1;
        if (n == 0) return 0;
        for (int i=1; i<n; i++)
        {
            if (a[i-1] < a[i]) dp++, ans = max(ans, dp);
            else dp = 1;
        }
        return ans;
    }
};
```



### 最长递增子序列

题目：[300. 最长递增子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

Longest Increasing Subsequence, LIS.

**不要求连续**。

定义 `dp[i]` 是以 `a[i]` 为结尾的，满足要求的最长序列长度。

转移方程：

```
dp[i] = max(dp[j] + 1) if a[j] < a[i], 0<=j<i
```

代码：

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& a) 
    {
        int n = a.size();
        if (n == 0) return 0;
        vector<int> dp(n, 1);
        int ans = 1;
        for (int i=1; i<n; i++)
        {
            for (int j=0; j<i; j++)
            {
                if (a[j] < a[i])
                    dp[i] = max(dp[i], dp[j]+1);
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};

// dp[i] = max(dp[j] + 1) if a[j] < a[i], 0<=j<i
```



### 最大子序和

题目：[53. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)

要求连续。

定义 `dp[i]` 为以 `a[i]` 结尾的，满足条件的最大子序和。根据定义，`a[i]` 必须要取，转移条件是是否保留 `a[i]` 之前的**若干连续**和。 

转移方程：`dp[i] = max(a[i], a[i] + dp[i-1])` .

动态规划解法。

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) 
    {
        int n = nums.size();
        int dp = nums[0], ans = nums[0];
        for (int i=1; i<n; i++)
            dp = max(nums[i], nums[i] + dp), ans = max(ans, dp);
        return ans;
    }
};

// dp[i]: 以 a[i] 结尾的最大连续和 
// dp[i] = max(a[i], a[i]+dp[i-1])
```

当然，其实滑动窗口也能做。



## 二维 DP

### 最长回文子序列

题目：[516. 最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence/)

是子序列，不是子串，**不要求连续**。

参考注释。

```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) 
    {
        int n = s.length();
        if (n == 0) return 0;
        vector<vector<int>> dp(n, vector<int>(n, 1));
        for (int i=0; i+1<n; i++) dp[i][i+1] += s[i] == s[i+1];
        for (int d=2; d<n; d++)
        {
            for (int i=0; i<(n-d); i++)
            {
                int j = i+d;
                if (s[i] == s[j]) dp[i][j] = dp[i+1][j-1] + 2;
                else dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
        return dp[0][n-1];
    }
};

// dp[i, j] 是 [i, j] 区间内的最长回文序列的长度
// dp[i, i] = 1, dp[i, i+1] = s[i] == s[i+1] ? 1 : 2
// dp[i, j] = dp[i+1, j-1] + 2            if s[i] == s[j]
// dp[i, j] = max(dp[i+1, j], dp[i, j-1]) if s[i] != s[j]
```

如果是求**最长回文子串**，那么可以定义 `dp[i, j] = {0, 1}` 是否为回文子串，那么转移方程为：

```
dp[i, i] = 1, dp[i, i+1] = s[i]==s[i+1]
dp[i, j] = dp[i+1, j-1] && s[i] == s[j]
```

求解过程中如果 `dp[i,j]` 为 1 ，那么记录最大长度：`ans = max(ans, j-i+1)` .

可以用来当练习：[5666. 回文串分割 IV](https://leetcode-cn.com/problems/palindrome-partitioning-iv/) 。





### 最长公共子序列

题目：[1143. 最长公共子序列](https://leetcode-cn.com/problems/longest-common-subsequence/)

Longest Common Subsequence, LCS.

子序列，**不要求连续**。

```cpp
class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) 
    {
        int len1 = s1.length(), len2 = s2.length();
        if (len1 == 0 || len2 == 0) return 0;
        vector<vector<int>> dp(len1, vector<int>(len2, 0));
        dp[0][0] = s1[0] == s2[0];
        for (int i=1; i<len1; i++) dp[i][0] = s1[i] == s2[0] || dp[i-1][0];
        for (int j=1; j<len2; j++) dp[0][j] = s1[0] == s2[j] || dp[0][j-1];
        for (int i=1; i<len1; i++)
        {
            for (int j=1; j<len2; j++)
            {
                if (s1[i] == s2[j]) dp[i][j] = dp[i-1][j-1] + 1;
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp.back().back();
    }
};
// dp[i, j] 是 s1[0, ..., i] 与 s2[0, ..., j] 的 LCS 的长度
// dp[i, j] = dp[i-1, j-1] + 1             if s1[i] == s2[j]
// dp[i, j] = max(dp[i-1, j], dp[i, j-1])  if s1[i] != s2[j]
```



## 非 DP

### 最长连续序列

题目：[128. 最长连续序列](https://leetcode-cn.com/problems/longest-consecutive-sequence/)

显然的想法，把数字都映射到哈希表，然后从某个最小的数字往前数，记录该序列的长度，求出最大值。

对于任意的 `x`, 一点 trick 是：如果哈希表中没有比 `x` 更小的数字，说明 `x` 必然是某个序列的开头，从 `x` 开始往前计数，知道哈希表中找不到 `x` 。

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) 
    {
        if (nums.size() == 0) return 0;
        unordered_set<int> s;
        for (int x: nums) s.insert(x);
        int ans = 1;
        for (int x: s)
        {
            // 确保 x 是序列的第一个数字
            if (s.count(x-1) == 0)
            {
                int len = 0;
                while (s.count(x)) x++, len++;
                ans = max(ans, len);
            }
        }
        return ans;
    }
};
```



### 最长特殊序列 Ⅰ

题目：[521. 最长特殊序列 Ⅰ](https://leetcode-cn.com/problems/longest-uncommon-subsequence-i/)

「最长特殊序列」定义如下：该序列为某字符串独有的最长子序列（即不能是其他字符串的子序列）。

显然：

- 如果 2 个长度不等，那么 `a, b` 都不可能为对方的子串，返回最大长度。
- 如果长度相等：
  - `a == b` 那么 -1 
  - `a != b` 那么「最长特殊序列」就是 `a, b` 自己。

```cpp
class Solution {
public:
    int findLUSlength(string a, string b) 
    {
        int alen = a.length(), blen = b.length();
        if (alen != blen) return max(alen, blen);
        if (a == b) return -1;
        return alen;
    }
};
```



### 最长特殊序列 II

题目：[522. 最长特殊序列 II](https://leetcode-cn.com/problems/longest-uncommon-subsequence-ii/)

