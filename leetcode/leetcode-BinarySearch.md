## [leetcode] 二分查找

本文题目：

+ [1351. 统计有序矩阵中的负数](https://leetcode-cn.com/problems/count-negative-numbers-in-a-sorted-matrix/)



## 统计有序矩阵中的负数

题目：[1351. 统计有序矩阵中的负数](https://leetcode-cn.com/problems/count-negative-numbers-in-a-sorted-matrix/)。

+ **解法1：对每一行二分查找**

```cpp
int countNegatives(vector<vector<int>> &grid)
{
    int ans = 0;
    for (auto &&v : grid)
    {
        int l = 0, r = (int)v.size() - 1, pos = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (v[mid] < 0)
            {
                pos = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        if (pos != -1)
            ans += v.size() - pos;
    }
    return ans;
}
```

+ **解法2：对解法1优化一下**

解法 1 利用了每行非递增的规律，但是没用到每列也是非递增，显然具有可以优化的地方。

不妨设每行第一个为负数的位置为 $pos_i$ ，显然有 $0 \le pos_{i+1} \le pos_i$ ，即：
$$
pos_{n-1} \le pos_{n-2} \le ... \le pos_1 \le pos_0
$$
对于每一行，我们**逆向从尾到头**找到第一个为正数的 `pos` ，那么 `pos+1` 就是第一个为负数的地方，在下一行的扫描当中，可以直接从 `pos+1` 开始逆向扫描。

```cpp
int countNegatives2(vector<vector<int>> &grid)
{
    const int cols = grid[0].size();
    int pos = cols - 1;
    int ans = 0;
    for (auto &v : grid)
    {
        while (pos >= 0 && v[pos] < 0)
            pos--;
        // now v[pos] >= 0 or pos = -1
        if (pos == -1)
            ans += cols;
        else
            ans += cols - 1 - pos;
    }
    return ans;
}
```

## 完全二叉树的节点个数

题目：[222. 完全二叉树的节点个数](https://leetcode-cn.com/problems/count-complete-tree-nodes/)。

+ 层次遍历

算法复杂度 $O(N)$ .

```cpp
int levelorder(TreeNode *root)
{
    if (root == nullptr) return 0;
    queue<TreeNode *> q;
    q.push(root);
    int ans = 0;
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        ans++;
        if (p->left)  q.push(p->left);
        if (p->right) q.push(p->right);
    }
    return ans;
}
```

假设二叉树一共 d+1 层，那么层次遍历时间复杂度为 $O(N)$ = $O(2^{d+1}-1)$ .

官方二分