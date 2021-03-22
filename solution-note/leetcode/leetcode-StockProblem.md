## [leetcode] 股票问题

参考文章：

- [1] [团灭 LeetCode 股票买卖问题](https://labuladong.gitbook.io/algo/di-ling-zhang-bi-du-xi-lie/tuan-mie-gu-piao-wen-ti)
- [2] [Most consistent ways of dealing with the series of stock problems](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108870/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems)

其实文章 [1] 是文章 [2] 的「二次创作」，建议先阅读 [2] 后再阅读 [1] 。文章 [2] 最大的亮点是使用了**状态机图**对股票问题进行建模和描述，我觉得是写得很好的文章（因为动态规划最原始的数学模型就是状态机）。

本文通过的题目有：

+ 题目[121]：[买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock)
+ 题目[122]：[买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii) 
+ 题目[123]：[买卖股票的最佳时机 III](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii) 
+ 题目[188]：[买卖股票的最佳时机 IV](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv) 
+ 题目[309]：[最佳买卖股票时机含冷冻期](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown) 
+ 题目[714]：[买卖股票的最佳时机含手续费](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee) 

## 预备知识

股票买卖问题的本质是**状态穷举**。或者说，其实大部分动态规划问题都是状态穷举，只不过是某个状态的计算不是从初始条件开始计算，而是依赖于已经计算过的若干个状态。

股票问题面临的因素有三个：天数 $N$ 、最大交易次数 $K$ 、在某天股票的持有状态 $S(S\in\{0,1\})$ 。

+ **状态定义**

`dp[i][k][s]` 表示在第 `i` 天，最大交易次数为 `k` ，当前股票持状态为 `s` 的情况下的最大利润。其中，$0 \le i \le n-1, 1 \le k \le K, 0 \le s \le 1$ .

显然，股票问题所需的结果是 `dp[n-1][K][0]` 。为什么不是 `dp[n-1][K][1]` 呢？因为该状态表示持有股票，最后需要的结果当然是不持有股票的，卖出才具有最大利润。

+ **转移方程**

假设在第 `i` 天，最大交易次数为 `k` ，进行操作后没有持有股票，该状态依赖于：

1. 第 `i-1` 天持有股票，但是第 `i` 天卖出，即  `dp[i-1][k][1] + price[i]` 。
2. 第 `i-1` 天就不持有股票，即 `dp[i-1][k][0]` 。

假设在第 `i` 天，最大交易次数为 `k` ，进行操作后持有股票，该状态依赖于：

1. 第 `i-1` 天就持有股票，第 `i` 天什么都不做，即 `dp[i-1][k][1]` 。
2. 第 `i-1` 天不持有股票，第 `i` 天购入股票，即 `dp[i-1][k-1][0] - price[i]` 。因为第 `i` 天需要进行一次交易操作，所以要求前一天的交易次数减一。

所以有：

```cpp
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + price[i])    if i>=1 and k>=1
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - price[i])  if i>=1 and k>=1
dp[0][k][0] = 0                                               if i==0 and k>=1
dp[0][k][1] = -price[0]                                       if i==0 and k>=1
```

第三个下标只有 0 和 1 ，所以我个人更偏向于将这个三维数组拆分为 2 个二维数组：

```cpp
dp0[i][k] = max(dp0[i-1][k], dp1[i-1][k] + price[i])    if i>=1 and k>=1
dp1[i][k] = max(dp1[i-1][k], dp0[i-1][k-1] - price[i])  if i>=1 and k>=1
```

本文就采用 2 个二维数组的形式去解题。

+ **边界条件**

边界的发生主要发生在变量 `i` 和 `k` 上，具体条件是 `i == -1` 和 ` k == 0` 。

```cpp
dp[-1][k][0] = 0, dp[-1][k][1] = -INF
dp[i][0][0] = 0, dp[i][0][1] = -INF
```

`dp[-1][k][0]` 表示允许交易（即 $k \ge 1$），但时间未开始（一个形象比喻：股票交易市场未开市），手上未持有股票，利润固然为 0 .

`dp[i][0][0]` 表示不允许交易，股票市场开市，所以利润为 0 .

`dp[-1][k][1]` 表示允许交易，股票市场未开市，但手中已持有股票，该状态是不可能的。

`dp[i][0][1]` 表示不允许交易，股票市场开市，但手中已持有股票，该状态也是不可能的。

因为求解过程中需要取 `max` ，所以不可能状态以最小值 `-INF` 表示。

## 买卖股票的最佳时机 

题目[121]：[🔗链接](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/) 。

这里 $K = 1$ ，代入状态转移方程可得：

```cpp
dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + price[i])  if i>=1
dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - price[i])  if i>=1
```

由于 `dp[i-1][0][0]` 表示不允许交易，且未持有股票，所以为 0 . 因此：

```cpp
dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + price[i])  if i>=1
dp[i][1][1] = max(dp[i-1][1][1], -price[i])                 if i>=1
```

**（请注意此处的处理与下面 “买卖股票的最佳时机 Ⅱ” 的区别！）**

可以发现，该方程与 K 无关，因此可以进一步简化：

```cpp
dp[i][0] = max(dp[i-1][0], dp[i-1][1] + price[i])     if i>=1
dp[i][1] = max(dp[i-1][1], -price[i])                 if i>=1
```

`dp[i]` 只依赖于上一个状态，因此可进行空间优化：

```cpp
dp0 = max(dp0, dp1 + price[i])     if i>=1
dp1 = max(dp1, -price[i])          if i>=1
```

初始状态，第 0 天，`dp0 = 0` 表示在第 0 天未持有股票；`dp1 = -price[0]` 表示在第 0 天购入股票。

代码如下：

```cpp
int maxProfit(vector<int> &prices)
{
    if (prices.size() == 0)  return 0;
    int dp0 = 0, dp1 = -prices[0];
    for (int x : prices)
    {
        dp0 = max(dp0, dp1 + x);
        dp1 = max(dp1, -x);
    }
    return dp0;
}
```

在[这篇文章](https://www.cnblogs.com/sinkinben/p/13039093.html)中，还有一个适合新手理解的方法，现在发现二者是一致的，`dp1` 实际上就是 `minval` 。

```cpp
int maxProfit(vector<int> &prices)
{
    int minval = 0x3f3f3f3f;
    int maxval = 0;
    for (auto x : prices)
    {
        minval = min(x, minval);
        maxval = max(x - minval, maxval);
    }
    return maxval;
}
```

## 买卖股票的最佳时机 II

题目[122]：[买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/) 。

这里允许无限次交易，即 $K = + \infty$ .

转移方程：

```cpp
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + price[i])    if i>=1 and k>=1
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - price[i])  if i>=1 and k>=1
```

**由于 `k` 是无穷大，因此 `k-1` 也是无穷大。**所以，方程与 `k` 无关。

```cpp
dp0[i] = max(dp0[i-1], dp1[i-1] + price[i])  if i>=1
dp1[i] = max(dp1[i-1], dp0[i-1] - price[i])  if i>=1
```

空间优化：

```cpp
dp0 = max(dp0, dp1 + price[i])  if i>=1
dp1 = max(dp1, dp0 - price[i])  if i>=1
```

初始状态：`dp0 = 0, dp1 = -price[0]` .

代码：

```cpp
int maxProfit(vector<int> &prices)
{
    if (prices.size() == 0)  return 0;
    int dp0 = 0, dp1 = -prices[0], t;
    for (int x : prices)
        t = dp0, dp0 = max(dp0, dp1 + x), dp1 = max(dp1, t - x);
    return dp0;
}
```

## 买卖股票的最佳时机 III

题目[123]：[买卖股票的最佳时机 III](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/) 。

这里 $K=2$ ，转移方程：

```cpp
dp[i][2][0] = max(dp[i-1][2][0], dp[i-1][2][1] + price[i])    if i>=1
dp[i][2][1] = max(dp[i-1][2][1], dp[i-1][1][0] - price[i])    if i>=1
```

对第三个下标降维，分解为 2 个 DP 数组：

```cpp
dp0[i][2] = max(dp0[i-1][2], dp1[i-1][2] + price[i])    if i>=1
dp1[i][2] = max(dp1[i-1][2], dp0[i-1][1] - price[i])    if i>=1
```

### 我的解法

到这一步，要考虑的是怎么求出 `dp0[i-1][1]` ？它的含义是只允许一次交易，在第 i 天不持有股票的最大利润。显然这就是第一题 “买卖股票的最佳时机” 所求的。

所以，我们先求出 `dp0[n][1]` 这个数组，用 `vector` 记录下来。那么状态方程就变为：

```cpp
dp0[i][2] = max(dp0[i-1][2], dp1[i-1][2] + price[i])    if i>=1
dp1[i][2] = max(dp1[i-1][2], v[i-1] - price[i])         if i>=1
```

可以发现，这时候与 `k=2` 无关（即与第二维下标无关）：

```cpp
dp0[i] = max(dp0[i-1], dp1[i-1] + price[i])  if i>=1
dp1[i] = max(dp1[i-1], v[i-1] - price[i])    if i>=1
```

空间优化：

```cpp
dp0 = max(dp0, dp1 + price[i])     if i>=1
dp1 = max(dp1, v[i-1] - price[i])  if i>=1
```

代码：

```cpp
int maxProfit3(vector<int> &prices)
{
    if (prices.size() == 0)  return 0;
    vector<int> v(prices.size(), 0); // which is dp0 at above
    int t = -prices[0];              // which is dp1 at above
    int n = prices.size();
    for (int i = 1; i < n; i++)
    {
        v[i] = max(v[i - 1], t + prices[i]);
        t = max(t, -prices[i]);
    }
    int dp0 = 0, dp1 = -prices[0];
    for (int i = 1; i < n; i++)
    {
        dp0 = max(dp0, dp1 + prices[i]);
        dp1 = max(dp1, v[i - 1] - prices[i]);
    }
    return dp0;
}
```

### 原作者的解法

$K=2$ 时的转移方程：

```cpp
dp[i][2][0] = max(dp[i-1][2][0], dp[i-1][2][1] + price[i])    if i>=1
dp[i][2][1] = max(dp[i-1][2][1], dp[i-1][1][0] - price[i])    if i>=1
```

进一步对 `dp[.][1][.]` 进一步展开（实际上就是第一题 “买卖股票的最佳时机” 的转移方程）：

```cpp
dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + price[i])  if i>=1
dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - price[i])  if i>=1
```

综合一下：

```cpp
dp[i][2][0] = max(dp[i-1][2][0], dp[i-1][2][1] + price[i])  if i>=1
dp[i][2][1] = max(dp[i-1][2][1], dp[i-1][1][0] - price[i])  if i>=1
dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + price[i])  if i>=1
dp[i][1][1] = max(dp[i-1][1][1], -price[i])                 if i>=1
```

对第二、第三维的下标进行降维：

```cpp
dp20[i] = max(dp20[i-1], dp21[i-1] + price[i])  if i>=1
dp21[i] = max(dp21[i-1], dp10[i-1] - price[i])  if i>=1
dp10[i] = max(dp10[i-1], dp11[i-1] + price[i])  if i>=1
dp11[i] = max(dp11[i-1], -price[i])             if i>=1
```

空间优化：

```cpp
dp20 = max(dp20, dp21 + price[i])  if i>=1
dp21 = max(dp21, dp10 - price[i])  if i>=1
dp10 = max(dp10, dp11 + price[i])  if i>=1
dp11 = max(dp11, dp00 - price[i])  if i>=1
```

初始状态：`dp20=0, dp10=0, dp21=-price[0], dp11=-price[0]` .

代码（Ps：把变量名改为 `a,b,c,d` 马上 bigger 就高了🤣）：

```cpp
int maxProfit3(vector<int> &prices)
{
    if (prices.size() == 0)  return 0;
    int dp20 = 0, dp10 = 0, dp21 = -prices[0], dp11 = -prices[0];
    for (int x : prices)
    {
        dp20 = max(dp20, dp21 + x);
        dp21 = max(dp21, dp10 - x);
        dp10 = max(dp10, dp11 + x);
        dp11 = max(dp11, -x);
    }
    return dp20;
}
```

## 买卖股票的最佳时机 IV

题目[188]：[买卖股票的最佳时机 IV](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/) 。

这里的 $K$ 是一个参数。

转移方程：

```cpp
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + price[i])    if i>=1 and k>=1
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - price[i])  if i>=1 and k>=1
```

对第三个下标降维（拆解成 2 个二维数组）：

```cpp
dp0[i][k] = max(dp0[i-1][k], dp1[i-1][k] + price[i])    if i>=1 and k>=1
dp1[i][k] = max(dp1[i-1][k], dp0[i-1][k-1] - price[i])  if i>=1 and k>=1
```

### 二维数组形式

超时。当 `K = 1000000000, len(prices) = 100000` 时，超时。


```cpp
int maxProfit4(int K, vector<int> &prices)
{
    if (prices.size() == 0)  return 0;
    int n = prices.size();
    vector<vector<int>> dp0(n, vector<int>(K + 1, 0));
    vector<vector<int>> dp1(n, vector<int>(K + 1, 0));
    const int MINVAL = 0x80000000;
    
    dp0[0][0] = 0, dp1[0][0] = MINVAL;
    for (int k = 1; k <= K; k++)  dp0[0][k] = 0, dp1[0][k] = -prices[0];
    for (int i = 1; i < n; i++)   dp0[i][0] = 0, dp1[i][0] = MINVAL;
    
    for (int i = 1; i < n; i++)
    {
        for (int k = 1; k <= K; k++)
        {
            dp0[i][k] = max(dp0[i - 1][k], dp1[i - 1][k] + prices[i]);
            dp1[i][k] = max(dp1[i - 1][k], dp0[i - 1][k - 1] - prices[i]);
        }
    }
    return dp0[n - 1][K];
}
```

### 空间优化：一维数组形式

还是超时了。

方程只出现 `i` 和 `i-1`， 先看空间优化后的结果：

```cpp
dp0[k] = max(dp0[k], dp1[k] + price[i])    if i>=1 and k>=1
dp1[k] = max(dp1[k], dp0[k-1] - price[i])  if i>=1 and k>=1
```

值得注意的是，在第 2 行中，`dp0[k-1]` 是旧 `dp0` 数组的。

因此这种写法是错误的（对 k 正向扫描，所以当计算 `dp1[k]` 所用到的 `dp0[k-1]` 已被更新 ）：

```cpp
for (int i = 1; i < n; i++)
    for (int k = 1; k <= K; k++)
    {
        dp0[k] = max(dp0[k], dp1[k] + prices[i]);
        dp1[k] = max(dp1[k], dp0[k - 1] - prices[i]);
    }
```

代码：

```cpp
int maxProfit4Version2(int K, vector<int> &prices)
{
    if (prices.size() == 0)
        return 0;
    const int minval = 0x80000000;
    int n = prices.size();
    vector<int> dp0(K + 1, 0);
    vector<int> dp1(K + 1, -prices[0]);
    dp0[0] = 0, dp1[0] = minval;
    for (int i = 1; i < n; i++)
    {
        vector<int> olddp0(dp0);
        for (int k = 1; k <= K; k++)
        {
            dp0[k] = max(dp0[k], dp1[k] + prices[i]);
            dp1[k] = max(dp1[k], olddp0[k - 1] - prices[i]);
        }
    }
    return dp0[K];
}
```

实际上，`olddp0` 这一临时空间也可以优化（对 `k` 逆向扫描）：

```cpp
for (int i = 1; i < n; i++)
    for (int k = K; k >= 1; k--)
    {
        dp0[k] = max(dp0[k], dp1[k] + prices[i]);
        dp1[k] = max(dp1[k], dp0[k - 1] - prices[i]);
    }
```

### 原作者解法

对于 `prices` 的长度为 $n$ ，那么最多可以交易的次数为 $n/2$ . 因此当 $K \ge n/2$ 时，相当于允许进行无限次交易，这时候就变成第二题 “买卖股票的最佳时机 II” 了。

😎这就是面向测试用例编程？！

```cpp
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        return maxProfit4Version2(k, prices);
    }
    int maxProfit2(vector<int> &prices)
    {
        if (prices.size() == 0)  return 0;
        int dp0 = 0, dp1 = -prices[0], t;
        for (int x : prices)
            t = dp0, dp0 = max(dp0, dp1 + x), dp1 = max(dp1, t - x);
        return dp0;
    }    
    int maxProfit4Version2(int K, vector<int> &prices)
    {
        if (prices.size() == 0)      return 0;
        if (K >= prices.size() / 2)  return maxProfit2(prices);
        const int minval = 0x80000000;
        int n = prices.size();
        vector<int> dp0(K + 1, 0);
        vector<int> dp1(K + 1, -prices[0]);
        dp0[0] = 0, dp1[0] = minval;
        for (int i = 1; i < n; i++)
        {
            for (int k = K; k >= 1; k--)
            {
                dp0[k] = max(dp0[k], dp1[k] + prices[i]);
                dp1[k] = max(dp1[k], dp0[k - 1] - prices[i]);
            }
        }
        return dp0[K];
    }
};
```

## 最佳买卖股票时机含冷冻期

题目[309]：[最佳买卖股票时机含冷冻期](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/) 。

此处，$K = +\infty$ .

消去 k 后的转移方程：

```cpp
dp0[i] = max(dp0[i-1], dp1[i-1] + price[i])  if i>=1
dp1[i] = max(dp1[i-1], dp0[i-1] - price[i])  if i>=1
```

本题新增一个要求：**卖出股票后，无法在第二天买入股票 (即冷冻期为 1 天)。**

而在第二个方程中 `dp0[i-1] - price[i]` 表示**今天在昨天的基础买入股票**。

因此需要对第二个方程改进，改为**在前天的基础上买入股票**：

```cpp
dp0[i] = max(dp0[i-1], dp1[i-1] + prices[i])  if i>=2
dp1[i] = max(dp1[i-1], dp0[i-2] - prices[i])  if i>=2
```

代码：

```cpp
int maxProfit5(vector<int> &prices)
{
    if (prices.size() <= 1)  return 0;
    int n = prices.size();
    vector<int> dp0(n, 0), dp1(n, 0);
    dp0[0] = 0, dp1[0] = -prices[0];
    dp0[1] = max(0, prices[1] - prices[0]);
    dp1[1] = max(-prices[0], -prices[1]);
    for (int i = 2; i < n; i++)
    {
        dp0[i] = max(dp0[i - 1], dp1[i - 1] + prices[i]);
        dp1[i] = max(dp1[i - 1], dp0[i - 2] - prices[i]);
    }
    return dp0.back();
}
```

空间优化：

```cpp
int maxProfit5Version2(vector<int> &prices)
{
    if (prices.size() <= 1)
        return 0;
    int n = prices.size();
    int dp0 = 0, dp1 = -prices[0], predp0 = 0, t;
    for (int i = 1; i < n; i++)
    {
        t = dp0;
        dp0 = max(dp0, dp1 + prices[i]);
        dp1 = max(dp1, predp0 - prices[i]);
        predp0 = t;
    }
    return dp0;
}
```



## 买卖股票的最佳时机含手续费

题目[714]：[买卖股票的最佳时机含手续费](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/) 。

此处，$K = + \infty$ .

直接消去 `k` 后，转移方程为（实际上就是第二题的转移方程）：

```cpp
dp0[i] = max(dp0[i-1], dp1[i-1] + price[i])  if i>=1
dp1[i] = max(dp1[i-1], dp0[i-1] - price[i])  if i>=1
```

每一次交易，需要交付 fee 个单位的利润作为手续费。

假如在**卖出股票**的时候交手续费，那么有：

```cpp
dp0[i] = max(dp0[i-1], dp1[i-1] + price[i] - fee)  if i>=1
dp1[i] = max(dp1[i-1], dp0[i-1] - price[i])        if i>=1
```

假如在**购入股票**的时候交手续费，那么有：

```cpp
dp0[i] = max(dp0[i-1], dp1[i-1] + price[i])        if i>=1
dp1[i] = max(dp1[i-1], dp0[i-1] - price[i] - fee)  if i>=1
```

PS: 还可以优化空间，就不多写，上面已经写过不少了。

出售股票时交手续费：

```cpp
int maxProfit6(vector<int> &prices, int fee)
{
    if (prices.size() == 0)  return 0;
    int dp0 = 0, dp1 = -prices[0], t;
    for (int x : prices)
    {
        t = dp0;
        dp0 = max(dp0, dp1 + x - fee);
        dp1 = max(dp1, t - x);
    }
    return dp0;
}
```

买入股票时交手续费：

```cpp
int maxProfit6(vector<int> &prices, int fee)
{
    if (prices.size() == 0)  return 0;
    int dp0 = 0, dp1 = -prices[0] - fee, t;
    for (int x : prices)
    {
        t = dp0;
        dp0 = max(dp0, dp1 + x);
        dp1 = max(dp1, t - x - fee);
    }
    return dp0;
}
```



## 总结

原作者 `fun4leetcode` 实在太厉害了！👋🏻看完之后，6 道股票题都变成模板题了。

所有题目的源代码在[这里](https://github.com/sinkinben/Sin-Notebook/blob/master/leetcode/StocksProblems.cpp) 。