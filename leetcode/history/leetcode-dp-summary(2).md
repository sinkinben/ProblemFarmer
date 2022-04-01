## [leetcode-DP] Distinct Ways

本文题目

+ [70. 爬楼梯](https://leetcode-cn.com/problems/climbing-stairs/)
+ [62. 不同路径](https://leetcode-cn.com/problems/unique-paths/)
+ [1155. 掷骰子的N种方法](https://leetcode-cn.com/problems/number-of-dice-rolls-with-target-sum/)
+ [688. “马”在棋盘上的概率](https://leetcode-cn.com/problems/knight-probability-in-chessboard/)

未通过题目：

+ ❌[494. 目标和](https://leetcode-cn.com/problems/target-sum/)

## 掷骰子的 N 种方法

题目：[Link](https://leetcode-cn.com/problems/number-of-dice-rolls-with-target-sum/) .

状态方程：`dp[i, j]` 表示 `i` 个骰子掷出点数和为 `j` 的方法数目。

转移方程：
$$
dp[i,j] = \sum_{k=1}^{f}dp[i-1, j-k]
$$
解析：第 `i` 个骰子可以掷出 `1 -> f` 的任意点数，因此 `dp[i, j]` 依赖于 `dp[i-1]` ，并把第 `i` 个骰子可能出现的情况求和。

边界条件：`dp[0, 0] = 1` .

**代码实现**

```cpp
class Solution
{
public:
    int numRollsToTarget(int d, int f, int target)
    {
        const uint32_t mod = 1000000007;
        vector<vector<uint32_t>> dp(d + 1, vector<uint32_t>(target + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= d; i++)
        {
            for (int j = i; j <= target; j++)
            {
                for (int k = 1; k <= f; k++)
                {
                    if (j >= k)
                    {
                        dp[i][j] += dp[i - 1][j - k];
                        dp[i][j] %= mod;
                    }
                }
            }
        }
        return dp[d][target];
    }
};
```

## 马在棋盘上的概率

题目[688]：[Link.](https://leetcode-cn.com/problems/knight-probability-in-chessboard/)

状态方程：`dp[(x,y)][step]` 表示走完第 `step` 步后，马在棋盘上位置 `(x,y)` 的概率。

转移方程：
$$
dp[(x,y)][step] = \sum \frac{1}{8}dp[(x,y)+(x',y')][step-1]
$$
其中，$(x',y') \in \{(2,1),(-2,1),(2,-1),(-2,-1),(1,2),(-1,2),(1,-2),(-1,-2)\}$ .

解析：每一个位置 `(x,y)` 可以从 8 个「上一位置」而来。

最终结果为最后一步 `dp[...][K]` 之和。

可以看出，`dp[][][step]` 只依赖于 `dp[][][step-1]` ，因此进行空间优化，拆分为 2 个二维数组。

**代码实现**

```cpp
class Solution
{
public:
    double knightProbability(int N, int K, int r, int c)
    {
        vector<vector<int>> direction = {{2, 1}, {-2, 1}, {2, -1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
        vector<vector<double>> curstep(N, vector<double>(N, 0));
        curstep[r][c] = 1;
        while (K--)
        {
            vector<vector<double>> prestep(curstep);
            curstep = vector<vector<double>>(N, vector<double>(N, 0));
            for (int x = 0; x < N; x++)
            {
                for (int y = 0; y < N; y++)
                {
                    for (auto &v : direction)
                    {
                        int dx = x + v[0], dy = y + v[1];
                        if (0 <= dx && dx < N && 0 <= dy && dy < N)
                            curstep[x][y] += prestep[dx][dy] / 8.0;
                    }
                }
            }
        }
        double sum = 0;
        for (auto &v : curstep)
            for (double p : v)
                sum += p;
        return sum;
    }
};
```

## 目标和

题目：[494. 目标和](https://leetcode-cn.com/problems/target-sum/) 。

+ **解法1：转换为背包问题**

来源自讨论区题解。

本题相当于给每个数一个正负号，然后求和，使得和为 `S` 。

假设正数之和为 `A` ，负数之和为 `B`，那么：

```
A + B = S
A - B = sum(nums)
```

则有：`A = (S + sum) / 2` .

那么这里可以转换为背包问题：从 `nums` 中选取若干个数（即背包问题中的物品），使得其和为 `(S+sum)/2` ，即背包的容量。



