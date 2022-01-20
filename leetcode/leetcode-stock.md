## [leetcode] 股票问题

一起来愉快的做题：

- 题目[121]：[买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock)
- 题目[122]：[买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii)
- 题目[123]：[买卖股票的最佳时机 III](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii)
- 题目[188]：[买卖股票的最佳时机 IV](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv)
- 题目[309]：[最佳买卖股票时机含冷冻期](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown)
- 题目[714]：[买卖股票的最佳时机含手续费](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee)



## Ready?

**状态定义**

- `dp0[i, k]` 表示在前 `i` 天，交易次数为 `k` ，**不持有股票**情况下的最大利润。
- `dp1[i, k]` 表示在前 `i` 天，交易次数为 `k` ，**持有股票**情况下的最大利润。
- 最后的结果应返回 `dp0[n-1, k]` .

PS: 当且仅当**买入**一次股票算一次交易。



**转移方程**

```cpp
dp0[i, k] = max(dp0[i-1, k], dp1[i-1, k] + price[i])   // 前一天就不持有，或者前一天持有，今天卖出
dp1[i, k] = max(dp1[i-1, k], dp0[i-1, k-1] - price[i]) // 前一天已经持有，或者前一天不持有，今天买入
```

显然，上面 `1 <= i < n` ，此处的边界条件是 `i = 0` :

```cpp
dp0[0, k] = 0 
dp1[0, k] = -price[0]
```

下面来看，怎么使用一个转移方程来 KO 上面的 6 道题。



## Go!

### 121

我们都知道，这题其实就是找最小值的同时，找出最大差值。

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minval = ~(1 << 31), maxgap = 1 << 31;
        for (int x : prices)
        {
            minval = min(minval, x);
            maxgap = max(maxgap, x - minval);
        }
        return maxgap;
    }
};
```

但看看如何通过上述的转移方程解决。交易次数 `k = 1` ，那么我们的转移方程是：

```cpp
dp0[i, 1] = max(dp0[i-1, 1], dp1[i-1, 1] + price[i])
dp1[i, 1] = max(dp1[i-1, 1], dp0[i-1, 0] - price[i])
// since dp0[i-1, 0] = 0, k = 0 means not allow to any transaction -->
dp0 = max(dp0, dp1 + price[i])
dp1 = max(dp1, -price[i])
// let dp1 = -T -->
dp0 = max(dp0, -T + price[i])
-T = max(-T, -price[i])
// -->
dp0 = max(dp0, -T + price[i])
T = min(T, price[i])
```

其实与上面给出的思路是等价的。



### 122

这里的交易次数是无限次，即 `k = INF` ，因而 `k-1` 也是无穷大 。

```cpp
dp0[i, k] = max(dp0[i-1, k], dp1[i-1, k] + price[i])
dp1[i, k] = max(dp1[i-1, k], dp0[i-1, k-1] - price[i])
// the equation is irrelevant with k, since k and k-1 are both INF -->
dp0 = max(dp0, dp1 + price[i])
dp1 = max(dp1, dp0 - price[i])
```

代码：

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int dp0 = 0, dp1 = -prices[0];
        for (int x: prices)
        {
            int t0 = dp0, t1 = dp1;
            dp0 = max(t0, t1 + x);
            dp1 = max(t1, t0 - x);
        }
        return dp0;
    }
};
```



### 123

最大交易次数为 `k = 2` 。

```cpp
dp0[i, 2] = max(dp0[i-1, 2], dp1[i-1, 2] + price[i])
dp1[i, 2] = max(dp1[i-1, 2], dp0[i-1, 1] - price[i])
```

一种朴素的做法是直接二维 DP 硬算，但容易发现：`k = 2` 时，依赖的是 `k = 1` 的情况（我们仅仅需要求出 `dp0[i-1, 1]` 这个数组），而 `k = 1` 的情况实际上是 leetcode-121.

到这里，我们有 2 种做法。

---

**做法一**

假设，我们已求得 `dp0[i-1, 1]` 这个数组，结果存放在 `v[0, ..., n - 1]` 中。

```cpp
dp0[i, 2] = max(dp0[i-1, 2], dp1[i-1, 2] + price[i])
dp1[i, 2] = max(dp1[i-1, 2], v[i-1] - price[i])
// that is
dp0 = max(dp0, dp1 + price[i])
dp1 = max(dp1, v[i-1] - price[i])
```

代码：

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        auto res = leetcode121(prices);
        int dp0 = 0, dp1 = -prices[0];
        for (int i=1; i<n; i++)
        {
            int t0 = dp0, t1 = dp1, x = prices[i];
            dp0 = max(t0, t1 + x);
            dp1 = max(t1, res[i-1] - x);
        }
        return dp0;
    }
    vector<int> leetcode121(vector<int> &prices)
    {
        int n = prices.size();
        vector<int> dp0(n, 0), dp1(n, 0);
        dp0[0] = 0, dp1[0] = -prices[0];
        for (int i=1; i<n; i++)
        {
            dp0[i] = max(dp0[i-1], dp1[i-1] + prices[i]);
            dp1[i] = max(dp1[i-1], -prices[i]);
        }
        return dp0;
    }
};
// dp0[i, k] = max(dp0[i-1, k], dp1[i-1, k] + prices[i])
// dp1[i, k] = max(dp1[i-1, k], dp0[i-1, k-1] - prices[i])
```

---

**做法二**

```cpp
dp0[i, 2] = max(dp0[i-1, 2], dp1[i-1, 2] + price[i])
dp1[i, 2] = max(dp1[i-1, 2], dp0[i-1, 1] - price[i])
// expand dp0[i-1, 1] (i.e. the equation in leetcode-121)
dp0[i, 1] = max(dp0[i-1, 1], dp1[i-1, 1] + price[i])
dp1[i, 1] = max(dp1[i-1, 1], - price[i])
// obviously, we can reduce these 4 equations
dp02 = max(dp02, dp12 + price[i])
dp12 = max(dp12, dp01 - price[i])
dp01 = max(dp01, dp11 + price[i])
dp11 = max(dp11, - price[i])
```

代码：

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        const int INTMIN = ~(1 << 31);
        int dp02 = 0, dp12 = -prices[0];
        int dp01 = 0, dp11 = -prices[0];
        for (int x : prices)
        {
            dp02 = max(dp02, dp12 + x);
            dp12 = max(dp12, dp01 - x);
            dp01 = max(dp01, dp11 + x);
            dp11 = max(dp11, - x);
        }
        return dp02;
    }
};
```



### 188

这里的交易次数 `k` 是一个参数，那么我们也只能二维 DP 硬算了。

```cpp
dp0[i, k] = max(dp0[i-1, k], dp1[i-1, k] + price[i])   // 前一天就不持有，或者前一天持有，今天卖出
dp1[i, k] = max(dp1[i-1, k], dp0[i-1, k-1] - price[i]) // 前一天已经持有，或者前一天不持有，今天买入
```

代码：

```cpp
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) 
    {
        int n = prices.size();
        if (n == 0) return 0;
        vector<vector<int>> dp0(n, vector<int>(k+1, 0));
        auto dp1 = dp0;
        // 不允许交易, k = 0
        for (int i=0; i<n; i++)
            dp0[i][0] = dp1[i][0] = 0;

        // 不论交易次数, i = 0 时
        for (int j=1; j<=k; j++)
        {
            dp0[0][j] = 0;
            dp1[0][j] = -prices[0];
        }
        for (int i=1; i<n; i++)
        {
            for (int j=1; j<=k; j++)
            {
                dp0[i][j] = max(dp0[i-1][j], dp1[i-1][j] + prices[i]);
                dp1[i][j] = max(dp1[i-1][j], dp0[i-1][j-1] - prices[i]);
            }
        }
        return dp0[n-1][k];
        
    }
};
// PLEASE remember this equation.
// dp0[i, k] = max(dp0[i-1, k], dp1[i-1, k] + prices[i])
// dp1[i, k] = max(dp1[i-1, k], dp0[i-1, k-1] - prices[i])
```

优化：如果给定的数组长度为 `n` ，那么我们最多可以进行 `n/2` 次交易，因此当 `j >= n/2` 时，可以视作时允许无限次交易（即 leetcode-122），并且上述二维 DP 也可以进行空间优化。

```cpp
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();

        if (n <= 1) return 0;
        if (k >= n / 2) return leetcode122(prices);

        vector<int> dp0(k+1, 0), dp1(k+1, 0);
        for (int j=1; j<=k; j++) dp1[j] = -prices[0];
        for (int i=1; i<n; i++)
        {
            for (int j=k; j>=1; j--)
            {
                dp0[j] = max(dp0[j], dp1[j] + prices[i]);
                dp1[j] = max(dp1[j], dp0[j-1] - prices[i]);
            }
        }
        return dp0.back();
    }
    int leetcode122(vector<int> &prices)
    {
        int dp0 = 0, dp1 = -prices[0];
        for (int x: prices)
        {
            int t0 = dp0, t1 = dp1;
            dp0 = max(t0, t1 + x);
            dp1 = max(t1, t0 - x);
        }
        return dp0;
    }
};
```



### 309

此处允许无限次交易，即 `k = INF` ，即 leetcode-122 的转移方程：

```cpp
dp0[i, k] = max(dp0[i-1, k], dp1[i-1, k] + price[i])
dp1[i, k] = max(dp1[i-1, k], dp0[i-1, k-1] - price[i])
// the equation is irrelevant with k, since k and k-1 are both INF -->
dp0[i] = max(dp0[i-1], dp1[i-1] + price[i])
dp1[i] = max(dp1[i-1], dp0[i-1] - price[i])
// if we sell stock on i-th day, then we can not buy on i+1 day, 
// which means we can only buy stock on the basic of (i-2) day.
dp0[i] = max(dp0[i-1], dp1[i-1] + price[i]), 0 <= i < n
dp1[i] = max(dp1[i-1], dp0[i-2] - price[i]), 2 <= i < n
```

代码：

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        int n = prices.size();
        if (n <= 1) return 0; 
        vector<int> dp0(n, 0), dp1(n, 0);
        dp0[0] = 0, dp1[0] = -prices[0];
        dp0[1] = max(dp0[0], dp1[0] + prices[1]);  // max(0, prices[1] - prices[0])
        dp1[1] = max(-prices[0], -prices[1]);
        for (int i=2; i<n; i++)
        {
            dp0[i] = max(dp0[i-1], dp1[i-1] + prices[i]);
            dp1[i] = max(dp1[i-1], dp0[i-2] - prices[i]);  
        }
        return dp0.back();
    }
};
```

再来一个小小的空间优化：

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        int n = prices.size();
        if (n <= 1) return 0; 
        int predp0, dp0, dp1;
        predp0 = dp0 = 0, dp1 = -prices[0];
        dp0 = max(0, prices[1] - prices[0]);  // dp0[i-1]
        dp1 = max(-prices[0], -prices[1]);    // dp1[i-1]
        for (int i=2; i<n; i++)
        {
            int t = dp0;  // t is actually dp0[i-1]
            dp0 = max(dp0, dp1 + prices[i]);    // get dp0[i]
            dp1 = max(dp1, predp0 - prices[i]); // get dp1[i]
            predp0 = t;
        }
        return dp0;
    }
};
```



### 714

无限次交易，但每次交易要收手续费：也就是说，我们在售出的时候（当然可以在购入的时候减），需要减去一个 `fee` 。

```cpp
dp0[i] = max(dp0[i-1], dp1[i-1] + price[i] - fee)
dp1[i] = max(dp1[i-1], dp0[i-1] - price[i])
```

代码：

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) 
    {
        int n = prices.size();
        if (n <= 1) return 0;
        int dp0 = 0, dp1 = -prices[0];
        for (int x : prices)
        {
            int t0 = dp0, t1 = dp1;
            dp0 = max(t0, t1 + x - fee);
            dp1 = max(t1, t0 - x);
        }
        return dp0;
    }
};
```





## References

- [Most consistent ways of dealing with the series of stock problems](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108870/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems)