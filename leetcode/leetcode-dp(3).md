## [leetcode] 动态规划（Ⅲ）

刷题心情日志：

+ 🖤 [2020/06/20]：刷不动了，么得感情。

## 不同的二叉搜索树 II

题目[95]：[不同的二叉搜索树 II](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/) 。

**解题思路**

参考[官方题解](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/solution/bu-tong-de-er-cha-sou-suo-shu-ii-by-leetcode/) ，主要思想是自底向上的递归。

**代码实现**

```cpp
class Solution
{
public:
    vector<TreeNode *> generateTrees(int n)
    {
        if (n == 0)  return {};
        return innerGenerate(1, n);
    }
    vector<TreeNode *> innerGenerate(int start, int end)
    {
        if (start > end)  return {nullptr};
        vector<TreeNode *> result;
        for (int i = start; i <= end; i++)
        {
            auto ltrees = innerGenerate(start, i - 1);
            auto rtrees = innerGenerate(i + 1, end);
            for (const auto &l : ltrees)
                for (const auto &r : rtrees)
                {
                    TreeNode *root = new TreeNode(i);
                    root->left = l, root->right = r;
                    result.push_back(root);
                }
        }
        return result;
    }
};
```

