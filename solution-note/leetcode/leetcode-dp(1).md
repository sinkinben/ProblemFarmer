## [leetcode] 动态规划（Ⅰ）

😮这次按通过率从高到低刷题。

本文完成的题目：`{338, 1025, 303, 121, 53, 392, 70, 746, 198}` ，带有「面试」Tag 的题目：`Interview - {1617, 42, 1716, 0801}` 。

大部分题目都是 Simple 难度的水题，可以作为动态规划的入门练习题。

## 比特位计数

题目[338]：一道位运算和动态规划结合的 [🔗题目](https://leetcode-cn.com/problems/counting-bits/) 。

**解题思路**

状态定义：`dp[i]` 表示第 i 个自然数二进制中 1 的个数。

状态转移方程：`dp[i] = dp[i >> 1] + (i & 1)`

**代码实现**

```cpp
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> v(num + 1);
        if (num == 0)  return v;
        v[1] = 1;
        for (int i = 2; i <= num; i++)
            v[i] = v[i >> 1] + (i & 0x1);
        return v;
    }
};
```

## 除数博弈

题目[1025]：点击 [🔗此处](https://leetcode-cn.com/problems/divisor-game/) 查看题目。

**解法1：数学方法**

规则是 Alice 先手，显然 2 到谁手上谁就是赢家。

+ 若 N 是奇数

不管 Alice 选择什么，x 的值必然是奇数（包括 1 在内）。那么交给 Bob 的 `N - x` 是一个偶数，Bob 只要一直取 `x = 2` ，把一个奇数交给 Alice，那么最后 2 必然会落到 Bob 的手中。所以 N 为奇数，Alice 必输。

也可以得到一个结论：**奇数先手必输。**

+ 若 N 是偶数

x 的值可奇可偶。在这时 Alice 只需要取 `x = 1` 把奇数 `N - x` 交给 Bob，此时对于 Bob 来说是「奇数先手」情况，Bob 必输。因此 N 为偶数，Alice 必赢。

```cpp
bool divisorGame(int N) { return N % 2 == 0; }
```

**解法2：动态规划**

状态方程：`dp[i] = true` 表示 Alice 赢，否则 Bob 赢。

显然，对于 `dp[i]` ，只要出现 `dp[i-x]` 为 `false` 的情况 ( `0 < x < i` )，`dp[i]` 就为 `true`。因为一旦出现这种情况，Alice选择该 x 就能胜出

```cpp
class Solution {
public:
    bool divisorGame(int N) {
        // return N % 2 == 0;
        return dpSolution(N);
    }
    bool dpSolution(int N)
    {
        if (N == 1 || N == 3)
            return false;
        if (N == 2)
            return true;
        vector<bool> v(N+1);
        v[1] = v[3] = false;
        v[2] = true;
        for (int i = 4; i <= N; i++)
            for (int j = 1; j < i; j++)
                if (i % j == 0 && !v[i - j])
                {
                    v[i] = true;
                    break;
                }
        return v[N];
    }
};
```

## 区域和检索 - 数组不可变

题目[303]：Click the [🔗Link](https://leetcode-cn.com/problems/range-sum-query-immutable/) to see the question.

**解题思路**

前缀和（这里是一维形式）。

状态定义：

```text
dp[i] = 0                       if i == 0
      = sum(nums[0, ..., i-1])  if i >= 1
```

那么：`sumRange(i,j) = sum(nums[0, ..., j]) - sum(nums[0, ..., i-1]) = dp[j+1] - dp[i]` .

**代码实现**

```cpp
class NumArray
{
public:
    vector<int> dp;
    NumArray(vector<int> &nums)
    {
        int n = nums.size();
        dp.resize(n + 1, 0);
        dp[0] = 0;
        for (int i = 1; i <= n; i++)
            dp[i] = nums[i - 1] + dp[i - 1];
    }
    int sumRange(int i, int j) { return dp[j + 1] - dp[i]; }
};
```

## 最大子序列和

题目[Interview-1617]：点击 [🔗此处](https://leetcode-cn.com/problems/contiguous-sequence-lcci/) 查看题目。

本题与题目 [Interview-42](https://leetcode-cn.com/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof/) 和 [题目53](https://leetcode-cn.com/problems/maximum-subarray/) 相同。

**解题思路**

状态定义：定义 `dp[i]` 表示以 `a[i]` 结尾的最大连续子序列。

转移方程：`dp[i] = max(a[i], dp[i-1] + a[i])`

**代码实现**

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(nums);
        int maxval = dp[0];
        for (int i = 1; i < n; i++)
            dp[i] = max(nums[i], dp[i-1] + nums[i]), maxval = max(maxval, dp[i]);
        return maxval;
    }
};
```

空间优化后：

```cpp
int spaceOptimize(vector<int> &nums)
{
    int dp = nums.front();
    int n = nums.size();
    int maxval = dp;
    for (int i = 1; i < n; i++)
        dp = max(dp + nums[i], nums[i]), maxval = max(maxval, dp);
    return maxval;
}
```



## 买卖股票的最佳时机

题目[121]：点击 [🔗链接](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/) 查看题目。

**解题思路**

只扫描一遍，一边记录当前已找到的「最小的价格」，一边记录目前为止「最大利润」。

**代码实现**

```cpp
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minval = 0x3f3f3f3f;
        int maxval = 0;
        for (auto x: prices)
        {
            minval = min(x, minval);
            maxval = max(x - minval, maxval);
        }
        return maxval;
    }
};
```



## 按摩师

题目[Interview-1716]：这个 [按摩师](https://leetcode-cn.com/problems/the-masseuse-lcci/) 的名字有点意思😗。

本题与下面的 [198. 打家劫舍](https://leetcode-cn.com/problems/house-robber/submissions/) 一模一样。

**解题思路**

状态定义：`dp0[i]` 表示在不接受 `num[i]` 情况下的最大预约时间；`dp1[i]` 表示接受 `num[i]` 情况下的最大预约时间。

转移方程：

+ `dp0[i] = max(dp0[i-1], dp1[i-1])` ：在不接受第 i 个请求的情况下，第 i-1 个请求可以选择接受或者不接受。
+ `dp1[i] = nums[i] + dp0[i-1]` ：在接受第 i 个请求的情况下，第 i-1 个请求必然不能接受。

**代码实现**

包括空间优化解法。

```cpp
class Solution
{
public:
    int massage(vector<int> &nums)
    {
        return spaceOptimize(nums);
    }
    int commonDP(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = 0, dp[0][1] = nums[0];
        int maxval = nums[0];
        for (int i = 1; i < n; i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0] + nums[i];
            maxval = max(maxval, max(dp[i][0], dp[i][1]));
        }
        return maxval;
    }

    int spaceOptimize(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        int dp0 = 0, dp1 = nums[0];
        int maxval = dp1;
        int t;
        for (int i = 1; i < n; i++)
        {
            t = dp1;
            dp1 = dp0 + nums[i];
            dp0 = max(dp0, t);
            maxval = max(maxval, max(dp0, dp1));
        }
        return maxval;
    }
};
```

## 判断子序列

题目[392]：点击 [🔗链接](https://leetcode-cn.com/problems/is-subsequence/) 查看题目。

**解法1：动态规划**

最长公共子序列 (LCS) 的变种题。

找出 `s` 和 `t` 的最长公共子序列长度 `maxval` ，判断 `maxval == s.length` 。

关于 LCS 的具体解法，看 [这里](https://www.cnblogs.com/sinkinben/p/11512710.html) 的第二小节。

```cpp
class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        int slen = s.length(), tlen = t.length();
        vector<vector<int>> dp(slen + 1, vector<int>(tlen + 1, 0));
        int maxval = 0;
        for (int i = 1; i <= slen; i++)
        {
            for (int j = 1; j <= tlen; j++)
            {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                maxval = max(maxval, dp[i][j]);
            }
        }
        return maxval == slen;
    }
};
```

**解法2：循环比较**

```cpp
bool loopSolution(string &s, string &t)
{
    int i = 0, j = 0;
    int slen = s.length(), tlen = t.length();
    while (i < slen && j < tlen)
    {
        if (s[i] == t[j])  i++;
        j++;
    }
    return i == slen;
}
```



## 爬楼梯

题目[72]：[经典题目](https://leetcode-cn.com/problems/climbing-stairs/) 。

**解法1：递归**

超时。

```cpp
int recursion(int n)
{
    if (n == 1 || n == 2)  return n;
    return recursion(n-1) + recursion(n-2);
}
```

**解法2：动态规划**

类似于斐波那契数列。

```cpp
int dp(int n)
{
    if (n == 1 || n == 2)  return n;
    int f1 = 1, f2 = 2, f3 = 3;
    for (int i = 3; i <= n; i++)
        f3 = f1 + f2, f1 = f2, f2 = f3;
    return f3;
}
```

## 使用最小花费爬楼梯

题目[746]：[爬楼梯的加强版](https://leetcode-cn.com/problems/min-cost-climbing-stairs/) 。

**解题思路**

状态定义：`dp[i]` 是到达第 i 个阶梯的最小花费（但不包括第 i 个的花费 `cost[i]` ），因此需要预处理 `cost.push_back(0)` 。

转移方程：

```cpp
dp[i] = cost[i]                          if i==0 or i==1
      = min(dp[i-1], dp[i-2]) + cost[i]  if i>=2
```

解析：第 i 个阶梯总是可以通过第 i-1 或 i-2 个直接抵达。

**代码实现**

```cpp
int minCostClimbingStairs(vector<int> &cost)
{
    cost.push_back(0);
    int n = cost.size();
    vector<int> dp(n, 0);
    dp[0] = cost[0], dp[1] = cost[1];
    for (int i = 2; i < n; i++)
        dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
    return dp[n - 1];
}
```

空间优化：

```cpp
int minCostClimbingStairs(vector<int> &cost)
{
    cost.push_back(0);
    int n = cost.size();
    int f0 = cost[0], f1 = cost[1], f2;
    for (int i = 2; i < n; i++)
        f2 = cost[i] + min(f0, f1), f0 = f1, f1 = f2;
    return f2;
}
```



## 打家劫舍

题目[198]：点击查看 [题目](https://leetcode-cn.com/problems/house-robber/) 。

**解法1：与上面的「按摩师」一模一样**

包括普通形式与空间优化形式。

```cpp
class Solution
{
public:
    int rob(vector<int> &nums)
    {
        return spaceOptimize(nums);
    }
    int commonDP(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)  return 0;
        if (n == 1)  return nums[0];
        vector<int> dp0(n, 0), dp1(n, 0);
        dp0[0] = 0, dp1[0] = nums[0];
        int maxval = max(nums[0], nums[1]);
        for (int i = 1; i < n; i++)
        {
            dp0[i] = max(dp0[i - 1], dp1[i - 1]);
            dp1[i] = dp0[i - 1] + nums[i];
            maxval = max(maxval, max(dp0[i], dp1[i]));
        }
        return maxval;
    }
    int spaceOptimize(vector<int> &v)
    {
        int n = v.size();
        if (n == 0)  return 0;
        if (n == 1)  return v[0];
        int dp0 = 0, dp1 = v[0];
        int maxval = v[0];
        int t;
        for (int i = 1; i < n; i++)
        {
            t = dp0;
            dp0 = max(dp0, dp1);
            dp1 = v[i] + t;
            maxval = max(dp0, dp1);
        }
        return maxval;
    }
};
```

**解法2：官方题解**

状态定义：`dp[i]` 表示在 `[0, ..., i]` 中偷窃的最大收益。

转移方程：`dp[i] = max(dp[i-1], dp[i-2] + nums[i])` 。如果选择偷窃 `nums[i]` 那么就只能在 `[0,...,i-2]` 的条件下进行；如果选择不偷窃 `nums[i]` 那么可以在 `[0,...,i-1]` 的范围内选择。

```cpp
int officialSolution(vector<int> &v)
{
    int n = v.size();
    if (n == 0)  return 0;
    if (n == 1)  return v[0];
    int f0 = v[0], f1 = max(v[0], v[1]), f2 = max(f0, f1);
    for (int i = 2; i < n; i++)
    {
        f2 = max(f1, f0 + v[i]);
        f0 = f1, f1 = f2;
    }
    return f2;
}
```

## 三步问题

题目[Interview-0801]：点击查看 [题目](https://leetcode-cn.com/problems/three-steps-problem-lcci/) 。

**解题思路**

与上面的「爬楼梯」一模一样，是斐波那契数列的变种。需要注意的是：**数据溢出，需要使用 `uint64_t` 作为数据类型。**

**代码实现**

```cpp
#define MODNUM (1000000007)
class Solution
{
public:
    int waysToStep(int n)
    {
        if (n <= 1)  return 1;
        if (n == 2)  return 2;
        uint64_t f0 = 1, f1 = 1, f2 = 2, f3 = 4;
        for (int i = 3; i <= n; i++)
        {
            f3 = (f0 + f1 + f2) % MODNUM;
            f0 = f1, f1 = f2, f2 = f3;
        }
        return f3;
    }
};
```

