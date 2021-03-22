## [leetcode-DP] Min/Max Cost to Reach A Target

本文题目：

+ [746. 使用最小花费爬楼梯](https://leetcode-cn.com/problems/min-cost-climbing-stairs/)：见[文章](https://www.cnblogs.com/sinkinben/p/13039093.html) 。
+ [221. 最大正方形](https://leetcode-cn.com/problems/maximal-square/)：见[文章](https://www.cnblogs.com/sinkinben/p/13047322.html) 。
+ [322. 零钱兑换](https://leetcode-cn.com/problems/coin-change/)
+ [983. 最低票价](https://leetcode-cn.com/problems/minimum-cost-for-tickets/)
+ [650. 只有两个键的键盘](https://leetcode-cn.com/problems/2-keys-keyboard/)
+ [279. 完全平方数](https://leetcode-cn.com/problems/perfect-squares/)
+ [474. 一和零](https://leetcode-cn.com/problems/ones-and-zeroes/)

「最小路径和」系列题目（经典且简单）：

+ [64. 最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/)：见[文章](https://www.cnblogs.com/sinkinben/p/13047322.html) 。
+ [120. 三角形最小路径和](https://leetcode-cn.com/problems/triangle/)：见[文章](https://www.cnblogs.com/sinkinben/p/13047322.html) 。
+ [931. 下降路径最小和](https://leetcode-cn.com/problems/minimum-falling-path-sum/)

「最后一块石头」系列题目：

+ [1046. 最后一块石头的重量](https://leetcode-cn.com/problems/last-stone-weight/)
+ [1049. 最后一块石头的重量 II](https://leetcode-cn.com/problems/last-stone-weight-ii/)

Hard 级别的题目：

+ ❎[1240. 铺瓷砖](https://leetcode-cn.com/problems/tiling-a-rectangle-with-the-fewest-squares/)
+ ❎[174. 地下城游戏](https://leetcode-cn.com/problems/dungeon-game/)
+ ❎[871. 最低加油次数](https://leetcode-cn.com/problems/minimum-number-of-refueling-stops/)

## 零钱兑换

题目[322]：[🔗链接](https://leetcode-cn.com/problems/coin-change/) 。

状态定义：`dp[i]` 为 `i` 元所需的最小硬币个数。

转移方程：
$$
dp[i] = \mathop{\min}_{j=0,...,n-1}dp[i-coin[j]] + 1
$$
$n$ 为硬币数组 `coin` 的长度。

初始状态：`dp[0] = 0` .

**代码实现**

```cpp
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int len = coins.size();
        vector<int> dp(amount + 1, -1);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++)
        {
            for (int x : coins)
            {
                if (i >= x && dp[i - x] != -1)
                {
                    if (dp[i] == -1)
                        dp[i] = dp[i - x] + 1;
                    else
                        dp[i] = min(dp[i], dp[i - x] + 1);
                }
            }
        }
        return dp[amount];
    }
};
```

如果使用 `0x3f3f3f3f` 来标记不可能状态：

```cpp
int coinChange2(vector<int> &coins, int amount)
{
    const int inf = 0x3f3f3f3f;
    int len = coins.size();
    vector<int> dp(amount + 1, inf);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++)
        for (int x : coins)
            if (i >= x)
                dp[i] = min(dp[i], dp[i - x] + 1);
    return dp[amount] >= inf ? -1 : dp[amount];
}
```



## 下降最小路径和

题目[931]: [🔗链接](https://leetcode-cn.com/problems/minimum-falling-path-sum/) 。

状态定义：`dp[i][j]` 是到达位置 `(i, j)` 的最小和。

转移方程：

```cpp
dp[i, j] = min(dp[i-1, j-1], dp[i-1, j], dp[i-1, j+1]) if 1 <= j <= (cols-2)
         = min(dp[i-1, 0], dp[i-1], 1)                 if j == 0
         = min(dp[i-1, cols-1], dp[i-1, cols-2])       if j == cols-1
```

`cols` 是矩阵 A 的列数。

初始状态：`dp[0] = A[0]` .

**代码实现**

```cpp
class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &A)
    {
        if (A.size() == 0 || A[0].size() == 0)
            return 0;
        vector<vector<int>> dp(A);
        int rows = A.size();
        int cols = A[0].size();
        for (int i = 1; i < rows; i++)
        {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + A[i][0];
            dp[i][cols - 1] = min(dp[i - 1][cols - 1], dp[i - 1][cols - 2]) + A[i][cols - 1];
            for (int j = 1; j < (cols - 1); j++)
                dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i - 1][j + 1])) + A[i][j];
        }
        int minval = dp[rows - 1][0];
        for (int x : dp[rows - 1])
            minval = min(minval, x);
        return minval;
    }
};
```

## 最低票价

题目[983]：[链接🔗](https://leetcode-cn.com/problems/minimum-cost-for-tickets/) 。

状态定义：`dp[i]` 第 `i` 天的最小票价，`0 <= i <= 365` .

转移方程：

```cpp
dp[i] = dp[i-1]                                                    if i is not in days
      = min(dp[i-1]+costs[0], dp[i-7]+costs[1], dp[i-30]+costs[2]) if i is in days
```

初始状态：`dp[0] = 0` .

细节问题：如果下标 `i-7` 和 `i-30` 为负数，代表什么情况？以 `days = [1,4,6,7,8,20], costs = [2,7,15]` 为例，当 `i=4` 时，不考虑票价，可以选择买 `2*costs[0]` ，也可以选择从第一天起直接买一个 `costs[1]` ，故 `i<7` 时 `dp[i-7] = 0` 。

**代码实现**

```cpp
class Solution
{
public:
    int mincostTickets(vector<int> &days, vector<int> &costs)
    {
        if (days.size() == 0)
            return 0;
        int lastday = days.back();
        vector<int> dp(lastday + 1, 0);
        vector<bool> flag(lastday + 1, false);
        for (int d: days)  flag[d] = true;
        dp[0] = 0;
        for (int i = 1; i <= lastday; i++)
        {
            if (!flag[i])
                dp[i] = dp[i - 1];
            else
            {
                dp[i] = dp[i - 1] + costs[0];
                dp[i] = min(dp[i], ((i >= 7) ? dp[i - 7] : 0) + costs[1]);
                dp[i] = min(dp[i], ((i >= 30) ? dp[i - 30] : 0) + costs[2]);
            }
        }
        return dp.back();
    }
};
```

## 只有两个键的键盘

题目[650]：[链接](https://leetcode-cn.com/problems/2-keys-keyboard/) 。

**解题思路**

+ **DP解法**

状态定义：`dp[i]` 为打印 `i` 个字符的最小操作次数。

下面求转移方程。

对于 `i = 2*k` 的情况，显然有 `dp[i] = dp[i/2] + 2` ，这是最容易想到的，全复制一次，然后粘贴，必然能够保证最小次数。但是对于其他情况呢？

对于质数 `i` 而言，显然有 `dp[i] = i` 。因为质数无法拆解成其他数的倍数（无法分解因数）。

对于其他的 `i` ，例如 `i=18`, 根据 `18 = 3 * 6`, 我们可以把 `'AAA'` 复制 1 次，粘贴 5 次；也可以把 `'AAAAAA'` 复制 1 次，粘贴 2 次；又因为 `18 = 2 * 9` ，所以有：

```cpp
dp[6] = 5, dp[9] = dp[3] + 3 = 6;
dp[18] = dp[3] + 1 + 6 - 1 = 9;
dp[18] = dp[6] + 1 + 3 - 1 = 9;
dp[18] = dp[2] + 1 + 9 - 1 = 11;
dp[18] = dp[9] + 1 + 2 - 1 = 8;
```

所以 `i = a*b` 时，`dp[i] = min(dp[a]+b, dp[b]+a)` .

直觉上来看，当 `a < b` 时，`dp[b]+a < dp[a]+b` （实际检验结果也是这样😄）。

代码实现

```cpp
class Solution
{
public:
    int minSteps(int n)
    {
        vector<int> dp(n + 1, 0);
        for (int i = 2; i <= n; i++)
        {
            dp[i] = i;
            for (int a = 2; a * a <= i; a++)
            {
                if (i % a == 0)
                {
                    int b = i / a;
                    // dp[i] = min(dp[i], min(dp[a] + b, dp[b] + a));
                    dp[i] = min(dp[i], dp[b] + a);
                }
            }
        }
        return dp[n];
    }
};
```

当然 `i % 2 == 0` 的情况可以单独考虑（该情况能够保证最大），可以提高运行效率，但为了代码的简洁性，没有单独写出来。  

+ **数学解法**

来源于 [官方题解](https://leetcode-cn.com/problems/2-keys-keyboard/solution/zhi-you-liang-ge-jian-de-jian-pan-by-leetcode/) 。

结论：$n$ 的质因数之和。

例如：`12 = 3 * 2 * 2`，所以 `minStep2(12) = 7` ；`111 = 3 * 37`，所以 `minSteps(111) = 40` ；`100 = 2 * 2 * 5 * 5`，所以 `minSteps(100) = 14` .

下面看证明过程。

使用 `C` 代表 `copy`，`P` 代表 `paste`。所有操作过程可分解为若干 `[CP...P]` 的序列，如 12 的操作序列为 `[CPP][CPPP]` 。`[CPP]` 得到 `AAA` , `[CPPP]` 则代表 `3*4` 这一因子分解操作。

对于任意的 $n$ ，其操作序列为 $K_1...K_m$，每一操作序列得到的 `A` 的个数为 $k_1, ..., k_m$ ，最终想要 $k_1 \cdot k_2... \cdot k_m = n$ ，并且要求 $\sum_{i=1}^{m}k_i$ 是最小的。

（下面用的是反证法的思想😄）

如果存在一个 $k_i$ 为合数，那么设 $k_i = p*q$ 。$p$ 代表 1 次复制，$p-1$ 次粘贴，共 $p$ 次操作，$q$ 与之同理。

所以要证明 $k_i \ge p+q$，即证明 $p*q \ge p+q$ .

我的证法：
$$
p+q \le p*q \Rightarrow \frac{1}{q} + \frac{1}{p} \le 1
$$
对于 $p \ge 2, q \ge 2$ 时，上式显然成立。

官方题解证法（因式分解）：
$$
\begin{aligned}
p*q &\ge p+q \\
p*q-p-q &\ge 0 \\
p*q-p-q+1 &\ge 1 \\
(p-1)(q-1) &\ge 1
\end{aligned}
$$
同理可证。

如果 $p,q$ 仍然不是质数，显然需要进一步分解质因数。

综上所述，所有 $k_i$ 必须为素数时，其和最小。

代码实现：

```cpp
int minSteps2(int n)
{
    int k = 0;
    int d = 2;
    while (n > 1)
    {
        while (n % d == 0)
        {
            k += d;
            n /= d;
        }
        d++;
    }
    return k;
}
```

## 完全平方数

题目[279]：[Link 🔗](https://leetcode-cn.com/problems/perfect-squares/) .

**我的解法：动态规划**

状态定义：`dp[i]` 为 `i` 的平方数分解的最小个数。

转移方程：
$$
dp[i] = 
\left\{
\begin{aligned}
1 \quad &if \quad i为完全平方数 \\
\mathop{\min}_{j=1,...,i/2}(dp[i-j]+dp[j]) \quad &otherwise
\end{aligned}
\right.
$$
初始状态：`dp[i] = i` .

解析：将 `i = a+b` 拆分，则 `dp[a] + dp[b]` 是 `i` 的平方数分解的最小个数。

结果：超时。

```cpp
class Solution
{
public:
    int numSquares(int n)
    {
        const int inf = 0x3f3f3f3f;
        vector<int> dp(n + 1, inf);
        dp[0] = 0, dp[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            int k = sqrt(i);
            if (k * k == i)
            {
                dp[i] = 1;
                continue;
            }
            dp[i] = i;
            for (int j = 1; j <= (i / 2); j++)
                dp[i] = min(dp[i], dp[i - j] + dp[j]);
        }
        return dp.back();
    }
};
```

**优化解法**

优化转移方程：`dp[i] = min(dp[i], dp[i-x]+1)`，`x` 是所有小于 `i` 的完全平方数。

同样的输入 `8829`，前者 360 ms，优化后 16 ms。

```cpp
int numSquares2(int n)
{
    int k = sqrt(n);
    vector<int> list;
    for (int i = 1; i <= k; i++)
        list.push_back(i * i);
    vector<int> dp(n + 1);
    dp[0] = 0, dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (k * k == i)
            dp[i] = 1;
        else
        {
            dp[i] = i;
            for (int x : list)
            {
                if (i < x)  break;
                dp[i] = min(dp[i], dp[i - x] + 1);
            }
        }
    }
    return dp.back();
}
```

## 最后一块石头的重量

题目[1046]：[Link.](https://leetcode-cn.com/problems/last-stone-weight/)

与 DP 无关，简单的模拟题，优先队列解决之。

```cpp
class Solution
{
public:
    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> q;
        for (int x : stones)  q.push(x);
        int x, y;
        while (q.size() != 1)
        {
            x = q.top(), q.pop();
            y = q.top(), q.pop();
            q.push(x - y);
        }
        return q.top();
    }
};
```

## 最后一块石头的重量 II

题目[1049]：[Link.](https://leetcode-cn.com/problems/last-stone-weight-ii/?utm_source=LCUS&utm_medium=ip_redirect_q_uns&utm_campaign=transfer2china)

结论：01背包问题的变形。

分析：实质上是把数字分为 2 堆，使得这 2 堆数字的和之差最小。例如 `[31,26,33,21,40]` 可分为 `[33, 40]` 和 `[21, 26, 31]` ，最小差值为 `abs(73 - 78) = 5` . 再比如 `[2,7,4,1,8,1]` 可分为 `[7,2,1,1]` 和 `[8,4]`, 最小差值为 `abs(11 - 12) = 1` 。

也就是说：**需要其中的一堆数字尽可能地接近 `sum/2`** ，背包容量为 `sum/2` ，物品的体积与价值均为 `stones[]` .

如果找到其中一堆数字之和为 `k` ，那么另外一堆为 `sum - k`，最终结果就是 `abs(sum - 2*k)` .

**代码实现**：无空间优化。

```cpp
class Solution
{
public:
    int lastStoneWeightII(vector<int> &stones)
    {
        int sum = 0;
        for (int x : stones)
            sum += x;
        int len = stones.size();
        int volume = sum / 2;
        vector<vector<int>> dp(len + 1, vector<int>(volume + 1, 0));
        for (int i = 1; i <= len; i++)
        {
            for (int j = 1; j <= volume; j++)
            {
                if (j >= stones[i - 1])
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }
        return abs(sum - 2 * dp.back().back());
    }
};
```

##  一和零

题目[474]：[Link .](https://leetcode-cn.com/problems/ones-and-zeroes/)

解题思路：01背包问题的变种。此处，背包的容量是二维的，分别是允许使用的 `0` 的个数 `m` 和允许使用的 `1` 的个数 `n` 。「物品」的体积也是二维的，即字符串中 `1` 和 `0` 的个数，价值均为 1（因为是找出最大个数）。

状态定义和状态转移方程可以完全套用 [背包问题](https://www.cnblogs.com/sinkinben/p/11512710.html) 。

状态定义：`dp[k][i][j]` 表示可用的 `0/1` 为 `(i,j)` 的情况下，在前 `k` 个字符串中（`strs[0]`是第一个字符串），可以拼凑出来的最大个数。

转移方程：

```cpp
dp[k, i, j] = 0              if k = 0
            = dp[k-1, i, j]  if i < zeroCounter || j < oneCounter
            = max(dp[k-1, i, j], dp[k-1, i-zeroCounter, j-oneCounter])  otherwise
```

代码实现

```cpp
class Solution
{
public:
    vector<int> countOneAndZero(const string &s)
    {
        int one = 0;
        for (char x : s)
            one += (x == '1');
        return {(int)s.length() - one, one};
    }
    int findMaxForm(vector<string> &strs, int m, int n)
    {
        int items = strs.size();
        vector<vector<vector<int>>> dp(items + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        for (int k = 1; k <= items; k++)
        {
            auto counter = countOneAndZero(strs[k - 1]);
            for (int i = 0; i <= m; i++)
            {
                for (int j = 0; j <= n; j++)
                {
                    if (i < counter[0] || j < counter[1])
                        dp[k][i][j] = dp[k - 1][i][j];
                    else
                        dp[k][i][j] = max(dp[k - 1][i][j], dp[k - 1][i - counter[0]][j - counter[1]] + 1);
                }
            }
        }
        return dp[items][m][n];
    }
};
```

