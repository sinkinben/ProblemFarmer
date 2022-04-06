## [leetcode] 打家劫舍

本文完成题目：

+ 题目[198]：[打家劫舍](https://leetcode-cn.com/problems/house-robber/) 
+ 题目[213]：[打家劫舍 II](https://leetcode-cn.com/problems/house-robber-ii/) 
+ 题目[337]：[打家劫舍 III](https://leetcode-cn.com/problems/house-robber-iii/) 

## 打家劫舍

题目[198]：[打家劫舍](https://leetcode-cn.com/problems/house-robber/) 。

与题目 [按摩师](https://leetcode-cn.com/problems/the-masseuse-lcci/) 一模一样。

状态定义：`dp1[i]` 表示选择第 i 个时的最大收益；`dp0[i]` 表示不选择第 i 个时的最大收益。

转移方程：

```cpp
// 不选择第 i 个，前一个可选可不选
dp0[i] = max(dp1[i-1], dp0[i-1])
// 选择第 i 个，前一个必然不能选
dp1[i] = dp0[i-1] + vals[i]
```

空间优化：

```cpp
dp0 = max(dp1, dp0)
dp1 = dp0 + val[i]
```

代码：

```cpp
int rob1(vector<int> &vals)
{
    if (vals.size() == 0)  return 0;
    int dp0 = 0, dp1 = vals[0], t;
    for (int i = 1; i < vals.size(); i++)
    {
        t = dp0;
        dp0 = max(dp0, dp1);
        dp1 = vals[i] + t;
    }
    return max(dp0, dp1);
}
```



## 打家劫舍 Ⅱ

题目[213]：[打家劫舍 II](https://leetcode-cn.com/problems/house-robber-ii/) 。

此处的附加条件是：房屋呈环形排列，第 0 号房屋与第 n-1 号房屋相邻（不能同时偷它们）。也就是说：

+ 如果想选择第 0 号房屋，就不能选择第 n-1 号房屋，只能从区间 `[0, n-2]` 中考虑。
+ 如果想选择第 n-1 号房屋，就不能选择第 0 号房屋，只能从区间 `[1, n-1]` 中考虑。

也就是说，基于第一题的实现，此处答案是 `max(rob1(vals[0, ..., n-2]), rob1(vals[1, ..., n-1]))` . 

可能你还有一个疑问：**假如第 0 号和第 n-1 号都不选才是最大的呢？**

实际上，`rob1(0, n-2)` 已经考虑了这种情况，此处的 `rob1` 只是在该区间内的最大收益，并不一定是选择第 0 号房屋。`rob1(1, n-1)` 同理。

代码：

```cpp
class Solution
{
public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)  return 0;
        if (n == 1)  return nums[0];
        if (n == 2)  return max(nums[0], nums[1]);
        return max(rob1(nums, 0, n-2), rob1(nums, 1, n-1));
    }
    int rob1(vector<int> &vals, int start, int end)
    {
        if (start == end)  return vals[start];
        int dp0 = 0, dp1 = vals[start], t;
        for (int i = start + 1; i <= end; i++)
        {
            t = dp0;
            dp0 = max(dp0, dp1);
            dp1 = vals[i] + t;
        }
        return max(dp0, dp1);
    }
};
```

## 打家劫舍 Ⅲ

题目[337]：[打家劫舍 III](https://leetcode-cn.com/problems/house-robber-iii/) 。

传说中的「树形DP」今天是终于遇上了😓。参考[此处题解](https://leetcode-cn.com/problems/house-robber-iii/solution/shu-xing-dp-ru-men-wen-ti-by-liweiwei1419/) 。

**状态定义**

`dp[node][0]` 表示不选择 `node` 的最大值，`dp[node][1]` 表示选择 `node` 的最大值。

**转移方程**

由于是二叉树，所以必然是采取递归处理的（实际上需要采用后序遍历）。假设在求解根节点前，对根 `node` 的左右子树进行了同样操作，所得结果为 `dp[left][0], dp[left][1], dp[right][0], dp[right][1]` 。

+ 选择 `node` ，那么 `node.left` 和 `node.right` 都不能选。
+ 不选 `node` ，那么 `node.left` 和 `node.right` 选或不选都可以。

所以转移方程为：

```cpp
dp[node][0] = max(dp[left][0], dp[left][1]) + max(dp[right][0], dp[right][1])
dp[node][1] = dp[left][0] + dp[right][0] + node.val
```

边界条件：`dp[null][0] = dp[null][1] = 0` .

代码：

```cpp
class Solution
{
public:
    int rob(TreeNode *root)
    {
        auto v = helper(root);
        return max(v[0], v[1]);
    }
    vector<int> helper(TreeNode *p)
    {
        if (p == nullptr)  return {0, 0};
        auto dpl = helper(p->left);
        auto dpr = helper(p->right);
        vector<int> dpnode(2);
        dpnode[0] = max(dpl[0], dpl[1]) + max(dpr[0], dpr[1]);
        dpnode[1] = p->val + dpl[0] + dpr[0];
        return dpnode;
    }
};
```

其实还能将 `dpnode` 部分 “缩” 得更短，更像 OI 风格一些：

```cpp
return {max(dpl[0], dpl[1]) + max(dpr[0], dpr[1]), p->val + dpl[0] + dpr[0]};
```

