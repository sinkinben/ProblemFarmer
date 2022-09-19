## 2407. 最长递增子序列 II

Leetcode: [2407. 最长递增子序列 II](https://leetcode.cn/problems/longest-increasing-subsequence-ii/)

给你一个整数数组 `nums` 和一个整数 `k` 。找到 `nums` 中满足以下要求的最长子序列：

- 子序列严格递增.
- 子序列中相邻元素的差值不超过 `k` .
- 请你返回满足上述要求的最长子序列的长度。

子序列是从一个数组中删除部分元素后，剩余元素不改变顺序得到的数组。 

示例 1：
```
输入：nums = [4,2,1,4,3,4,5,8,15], k = 3
输出：5
解释：
满足要求的最长子序列是 [1,3,4,5,8] 。
子序列长度为 5 ，所以我们返回 5 。
注意子序列 [1,3,4,5,8,15] 不满足要求，因为 15 - 8 = 7 大于 3 。
```
示例 2：
```
输入：nums = [7,4,5,1,8,12,4,7], k = 5
输出：4
解释：
满足要求的最长子序列是 [4,5,8,12] 。
子序列长度为 4 ，所以我们返回 4 。
```
示例 3：
```
输入：nums = [1,5], k = 1
输出：1
解释：
满足要求的最长子序列是 [1] 。
子序列长度为 1 ，所以我们返回 1 。
```

提示：
```
1 <= nums.length <= 1e5
1 <= nums[i], k <= 1e5
```



<br/>

**题解**

先考虑传统 $O(n^2)$ 的解法。

令 `dp[i]` 表示以 `nums[i]` 结尾的 LIS 的长度。

```cpp
vector<int> dp(n, 1)
dp[i] = max(dp[i], dp[j] + 1) where (0 <= j < i) and (nums[j] < nums[i] && nums[i] - nums[j] <= k)
return max(dp)
```

$O(n^2)$ 的解法对于 `1e5` 的输入来说，是不可接受的，考虑如何对该解法优化。

要解决的关键问题是：如何在 `[0, i)` 这一范围内，找出满足条件的，最大的 `dp[j]` ，这里的「条件」指的是:

```text
(nums[i] - k) <= nums[j] <= (nums[i] - 1) where 0 <= j < i
```

如果我们依旧采用暴力枚举的方法，时间复杂度是 $O(nk)$，依旧无法通过本题。

现在的问题是一个「区间最值」问题，适合使用[线段树](https://www.cnblogs.com/sinkinben/p/15170482.html)。

- 令 `seg[x]` 表示以值 `x` 结尾的 LIS 的长度。注意，此处的 `x` 不是数组下标。
- 那么对于任意的 `y = nums[i]`, 我们有：`seg[y] = seg.queryMax(y - k, y - 1) + 1` .
- 因此，我们需要实现两种线段树操作：区间赋值，区间最大值。

```cpp
/* Max Segment Tree */
class SegTree
{
private:
    int N;
    vector<int> tree;
    // 查询区间 [ql, qr] 中的最大值
    int queryMax(int id, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr) return tree[id];
        else
        {
            int nxt = id << 1, mid = (l + r) >> 1;
            return max(ql <= mid ? queryMax(nxt, l, mid, ql, qr) : 0, 
                       qr > mid ? queryMax(nxt | 1, mid + 1, r, ql, qr) : 0);
        }
    }

    // 用 val 更新位置 pos 的最大值
    void modify(int id, int l, int r, int pos, int val) {
        if (l == r) tree[id] = max(tree[id], val);
        else
        {
            int nxt = id << 1, mid = (l + r) >> 1;
            if (pos <= mid) modify(nxt, l, mid, pos, val);
            else modify(nxt | 1, mid + 1, r, pos, val);
            tree[id] = max(tree[nxt], tree[nxt | 1]);
        }
    }

public:
    SegTree(int n): N(n)
    {
        tree.resize(4 * N + 1, 0);
    }
    int queryMax(int l, int r)
    {
        return queryMax(1, 1, N, l, r);
    }
    void modify(int pos, int val)
    {
        modify(1, 1, N, pos, val);
    }

};

class Solution
{
public:
    int lengthOfLIS(vector<int>& nums, int k) {
        int maxval = *max_element(begin(nums), end(nums));
        SegTree seg(maxval);
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int x;
            if (nums[i] == 1) x = 1;
            else x = seg.queryMax(max(1, nums[i] - k), nums[i] - 1) + 1;
            seg.modify(nums[i], x);
            ans = max(ans, x);
        }
        return ans;
    }
};
```

