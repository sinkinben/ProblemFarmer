## [leetcode] 动态规划（Ⅱ）

本文均为 **中等** 难度的题目。

完成题目包括有：

```text
{1314, 221, 1277, 877, 96, 64, 120}
Interview - {47}
```

## 矩阵区域和

题目[1314]：点击 [此处](https://leetcode-cn.com/problems/matrix-block-sum/)  查看题目。

**解题思路**

二维前缀和的应用（默认读这篇文章的人都会了😎）。

实际上，这里题目的意思是求出某个点 $\pm k$ 二维矩形范围内的和。

如果还没想法，建议 [看题解](https://leetcode-cn.com/problems/matrix-block-sum/solution/ju-zhen-qu-yu-he-by-leetcode-solution/) 。

**代码实现**

```cpp
class Solution
{
public:
    int rows, cols;
    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        rows = mat.size();
        cols = mat[0].size();
        vector<vector<int>> prefix(rows, vector<int>(cols, 0));
        prefix[0][0] = mat[0][0];
        // calculate prefix sum
        for (int j = 1; j < cols; j++)
            prefix[0][j] = mat[0][j] + prefix[0][j - 1];
        for (int i = 1; i < rows; i++)
            prefix[i][0] = mat[i][0] + prefix[i - 1][0];
        for (int i = 1; i < rows; i++)
            for (int j = 1; j < cols; j++)
                prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - 
                               prefix[i - 1][j - 1] + mat[i][j];

        vector<vector<int>> ans(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                ans[i][j] = getval(i + k, j + k, prefix) - getval(i - k - 1, j + k, prefix) -
                            getval(i + k, j - k - 1, prefix) + 
                            getval(i - k - 1, j - k - 1, prefix);
            }
        }
        return ans;
    }

    int getval(int x, int y, vector<vector<int>> &prefix)
    {
        if (x < 0 || y < 0)
            return 0;
        else
            return prefix[min(x, rows - 1)][min(y, cols - 1)];
    }
};
```

## 最大正方形

题目[221]：点击 [🔗此处](https://leetcode-cn.com/problems/maximal-square/) 查看题目。

**解题思路**

先看 [这个题解](https://leetcode-cn.com/problems/maximal-square/solution/li-jie-san-zhe-qu-zui-xiao-1-by-lzhlyle/) 和 [官方题解](https://leetcode-cn.com/problems/maximal-square/solution/zui-da-zheng-fang-xing-by-leetcode-solution/)？

状态定义：`dp[i][j]` 表示以 `matrix[i][j]` 为右下角的最大正方形的**边长**。

转移方程：

```cpp
dp[i,j] = matrix[i, j]                                   if i==0 or j==0 
        = 0                                              if i>=1 and j>=1 and matrix[i, j]==0
        = 1 + min(dp[i, j-1], dp[i-1, j], dp[i-1, j-1])  if i>=1 and j>=1 and matrix[i, j]==1
```

值得关注的是为什么要取**最小值**？

<img src="https://github.com/Sin-Kinben/PicGo/raw/master/img/20210117160221.png" width="80%"/>

如上图所示，在位置 `(3, 4)` 上，相邻的三个 DP 值为：3, 1, 3 . 我们可以理解为以该位置为起点，在其左上方一圈一圈地扩大正方形的范围（直至边界遇到 0 值），最终所能扩充到的**边界必然受限于 3 个邻居中最小的一个**。

[这里](https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/solution/tong-ji-quan-wei-1-de-zheng-fang-xing-zi-ju-zhen-2/) 似乎有一个更为严谨的证明，但好像还是没解释清楚「最小值」的直观含义。

时间复杂度为 $O(m * n)$ , 空间复杂度为 $O(m*n)$ , 实际上可优化为 $O(2n)$ 。

**代码实现**

```cpp
class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        if (matrix.size() == 0)
            return 0;
        int rows = matrix.size();
        int cols = matrix[0].size();
        int maxval = 0;
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        for (int j = 0; j < cols; j++)
            dp[0][j] = (matrix[0][j] == '1'), maxval = max(maxval, dp[0][j]);
        for (int i = 0; i < rows; i++)
            dp[i][0] = (matrix[i][0] == '1'), maxval = max(maxval, dp[i][0]);
        for (int i = 1; i < rows; i++)
        {
            for (int j = 1; j < cols; j++)
            {
                if (matrix[i][j] == '1')
                    dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
                else
                    dp[i][j] = 0;
                maxval = max(maxval, dp[i][j]);
            }
        }
        return maxval * maxval;
    }
};
```

## 统计全为 1 的正方形子矩阵

题目[1277]：点击 [🔗此处](https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/) 查看题目。

**解题思路**

状态定义与转移方程与上一题**最大正方形**一模一样，有一点上面没提到， `dp[i][j]` 的值具有下列 2 层含义：

+ 以 `m[i, j]` 为右下角的最大正方形的边长（即上一题的含义）
+ 以 `m[i, j]` 为右下角的正方形的个数（即本题的含义）。为什么会具有这个含义呢？回想上一题的过程，在计算某个位置的 DP 值时，我们以该位置为起点，在其左上方一圈一圈地扩大正方形的范围（直至边界遇到 0 值），所以 `dp[i, j] = k` 表示的是有 `k` 个以 `m[i, j]` 为右下角的正方形，且边长分别为 `1, 2, ..., k` ，如下图所示。

那么本题的答案就是所有 DP 值之和 `sum(dp)` 。

<img src="https://github.com/Sin-Kinben/PicGo/raw/master/img/20210117160244.png" width="300px"/>



**代码实现**

```cpp
class Solution
{
public:
    int countSquares(vector<vector<int>> &matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return 0;
        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<vector<int>> dp(matrix);
        int sum = 0;
        for (int i = 1; i < rows; i++)
        {
            for (int j = 1; j < cols; j++)
            {
                if (matrix[i][j] == 1)
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                else
                    dp[i][j] = 0;
                sum += dp[i][j];
            }
        }
        for (int i = 0; i < rows; i++)  sum += dp[i][0];
        for (int j = 1; j < cols; j++)  sum += dp[0][j];
        return sum;
    }
};
```

空间优化后：

```cpp
int spaceOptimize(vector<vector<int>> &matrix)
{
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return 0;
    int rows = matrix.size();
    int cols = matrix[0].size();
    int sum = 0;
    vector<int> pre(matrix[0]);
    vector<int> cur(cols, 0);
    for (int i = 1; i < rows; i++)
    {
        cur[0] = matrix[i][0];
        for (int j = 1; j < cols; j++)
        {
            if (matrix[i][j] == 1)  cur[j] = 1 + min(cur[j - 1], min(pre[j], pre[j - 1]));
            else  cur[j] = 0;
            sum += cur[j];
        }
        pre = cur;
    }
    for (int j = 0; j < cols; j++)  sum += matrix[0][j];
    for (int i = 1; i < rows; i++)  sum += matrix[i][0];
    return sum;
}
```

## 石子游戏

题目[877]：[石子游戏](https://leetcode-cn.com/problems/stone-game/) 。

**解题思路**

跟[这里的除数博弈](https://www.cnblogs.com/sinkinben/p/13039093.html)类似。

**答案是先手必胜。**这里有偶数堆石头，石头的总和是奇数，每个人只能取头尾的二者之一。所以，必然有一方取得所有的奇数堆，一方取得所有的偶数堆（从 1 开始计数）。并且 Sum(奇数堆) 和 Sum(偶数堆) 必然是一大一小的（因为总和是一个奇数）。

而取奇数堆还是偶数堆的主动权在 Alice 手中。Alice 取的是奇数堆还是偶数堆，取决于 Alice 第一次取的是第 1 个还是第 n 个（ n 是偶数）。

题目说明，每个人均以**最优策略**取，因此 Alice 是先手必胜的。

`return true` 即可。

但是如果石头的堆数是奇数，那就不一定了，比如 `[1, 100, 1, 100, 1]` 。当 Alice 取走一个 1 后（不论头尾），Bob 就变成了「先手必胜」的那一个。

## 礼物的最大价值

题目[Interview-47]：[礼物的最大价值](https://leetcode-cn.com/problems/li-wu-de-zui-da-jie-zhi-lcof/) 。

**解题思路**

[数塔问题](https://www.cnblogs.com/sinkinben/p/11512710.html)（在文章第五小节）的变种。

类似题还有：[最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/) ，[三角形最小路径和](https://leetcode-cn.com/problems/triangle/) 。（紧跟着的后面 2 题）

状态定义：`dp[i, j]` 表示从 (0, 0) 到 (i, j) 取得的最大值。

转移方程：

```cpp
dp[i,j] = dp[0,j-1] + grid[0,j]                 if i==0
        = dp[i-1,0] + grid[i,0]                 if j==0
        = max(dp[i-1,j], dp[i,j-1]) + grid[i,j] if i>=1 and j>=1
```

**代码实现**

可以优化，但没必要。

```cpp
class Solution
{
public:
    int maxValue(vector<vector<int>> &grid)
    {
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        dp[0][0] = grid[0][0];
        for (int j = 1; j < cols; j++)  dp[0][j] = dp[0][j - 1] + grid[0][j];
        for (int i = 1; i < rows; i++)  dp[i][0] = dp[i - 1][0] + grid[i][0];
        for (int i = 1; i < rows; i++)
            for (int j = 1; j < cols; j++)
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
        return dp.back().back();
    }
};
```

## 最小路径和

题目[64]：[最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/) 。

```cpp
class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;
        int rows = grid.size();
        int cols = grid[0].size();
        // some trick to simplify the code
        vector<vector<int>> dp(rows + 1, vector<int>(cols + 1, 0x3f3f3f3f));
        dp[0][1] = dp[1][0] = 0;
        for (int i = 1; i <= rows; i++)
            for (int j = 1; j <= cols; j++)
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
        return dp[rows][cols];
    }
};
```

## 三角形最小路径和

题目[120]：[三角形最小路径和](https://leetcode-cn.com/problems/triangle/) 。

**解题思路**

真·数塔问题。

**代码实现**

可以空间优化，但没必要😗。

```cpp
class Solution
{
public:
    int minimumTotal(vector<vector<int>> &triangle)
    {
        if (triangle.size() == 0 || triangle[0].size() == 0)
            return 0;
        vector<vector<int>> dp(triangle);
        int minval = 0x3f3f3f3f;
        for (int i = 1; i < dp.size(); i++)
            for (int j = 0; j < dp[i].size(); j++)
                dp[i][j] = min(getval(j-1, dp[i - 1]), getval(j, dp[i - 1])) + triangle[i][j];
        auto &v = dp.back();
        for (int x : v)
            minval = min(minval, x);
        return minval;
    }

    int getval(int x, vector<int> &v)
    {
        int len = v.size();
        if (0 <= x && x < len)  return v[x];
        return 0x3f3f3f3f;
    }
};
```



## 不同的二叉搜索树

题目[96]：[不同的二叉搜索树](https://leetcode-cn.com/problems/unique-binary-search-trees/) 。

**解题思路**

卡特兰数的应用。
$$
h(n)=
\left\{
\begin{aligned}
& 0, & n=0 \\
& n, & n=1 \quad or \quad n=2 \\
& \sum_{i=0}^{n-1}h(i)h(n-i-1), & n\ge3
\end{aligned}
\right.
$$
为什么是卡特兰数呢？

设 $h(n)$ 是具有 n 个节点，不同的二叉搜索树的数目（条件也可以是二叉树？），任意选定一个根节点，那么剩余的 $n-1$ 个节点需要分配到左右子树。假如左子树 $a$ 个节点，右子树 $n-1-a$ 个节点，那么选定某个根的情况下产生的数目为 $h(a)*h(n-1-a)$ 。

根的选取可以有 n 种情况，把这 n 种情况累加即可。

最后，卡特兰数还有一个递推形式：
$$
h(n) = h(n-1) \cdot \frac{4n-2}{n+1}, n=0,1,2,... 
$$
**代码实现**

注意溢出即可。

```cpp
class Solution
{
public:
    int numTrees(int n)
    {
        return dp(n);
    }
    int dp(int n)
    {
        if (n <= 2)  return n;
        vector<int> catalan(n + 1, 0);
        catalan[0] = catalan[1] = 1, catalan[2] = 2;
        for (int i = 3; i <= n; i++)
            for (int k = 0; k < i; k++)
                catalan[i] += catalan[k] * catalan[i - k - 1];
        return catalan.back();
    }
    int func(int n)
    {
        uint64_t h = 1;
        for (int i = 1; i <= n; i++)
            h = h * 2 * (2 * i - 1) / (i + 1);
        return h;
    }
};
```

