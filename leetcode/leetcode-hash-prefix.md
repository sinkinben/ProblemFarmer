## Leetcode | Prefix Sum and Hash Table

总结几道哈希表 + 前缀和的题目。

- [523. 连续的子数组和](https://leetcode.com/problems/continuous-subarray-sum/): 给定数组 `nums` 和整数 `k` , 找到一个连续的子数组，其长度大于等于 2 ，并且和是 `k` 的倍数。
- [325. Maximum Size Subarray Sum Equals k](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/)：给定数组 `nums` 和整数 `k` ，返回和为 `k` 的连续子数组的最大长度。
- [560. 和为 K 的子数组](https://leetcode.com/problems/subarray-sum-equals-k/)：给定数组 `nums` 和整数 `k` ，求和为 `k` 的子数组的个数。

二维形式：

- [1074. Number of Submatrices That Sum to Target](https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/)：给定二维矩阵 `mat` 和整数 `target`，求和为 `target` 的子矩阵的数量。



## [523. Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/description/)

Given an integer array nums and an integer k, return `true` *if* `nums` *has a **good subarray** or* `false` *otherwise*.

A **good subarray** is a subarray where:

- its length is **at least two**, and
- the sum of the elements of the subarray is a multiple of `k`.

**Note** that:

- A **subarray** is a contiguous part of the array.
- An integer `x` is a multiple of `k` if there exists an integer `n` such that `x = n * k`. `0` is **always** a multiple of `k`.

**Example 1:**

```
Input: nums = [23,2,4,6,7], k = 6
Output: true
Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
```

**Constraints:**

- `1 <= nums.length <= 1e5`
- `0 <= nums[i] <= 1e9`
- `0 <= sum(nums[i]) <= 2^31 - 1`
- `1 <= k <= 2^31 - 1`

<br/>

**Solution**

- 构造前缀和 `prefix[i] = sum(nums[0, i])`。
- 现在的问题等价于：找到不同的索引 `i, j`，使得 `prefix[i] - prefix[j]` 是 `k` 的倍数，即：`prefix[i] % k == prefix[j] % k`。
	- 这里需要注意的是，找到 `prefix[i] - prefix[j]` ，这个区间其实代表的是 `[j + 1, i]`，因此区间长度为 `i - j`。
- 用哈希表记录前缀和 `prefix % k` 出现的索引位置，在扫描过程中，如果再一次找到 `prefix % k`，判断区间长度是否大于等于 2 。

```cpp
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        // unordered_map<int, int> mp = {{0, -1}};
        unordered_map<int, int> mp;
        int sum = 0, n = nums.size();
        
        for (int i = 0; i < n; ++i)
        {
            int x = nums[i];
            sum = (sum + x) % k;   // sum denotes sum of range [0, i]
            
            if (sum == 0 && i >= 1)  // if range [0, i] is satisfied
                return true;
            
            // prefix[i] - prefix[j] denote sum of range [j + 1, i], whose length is (i - j)
            if (mp.count(sum))
            {
                if (i - mp[sum] >= 2)
                    return true;
            }
            else
                mp[sum] = i;
        }
        return false;
        
    }
};
```



## [325. Maximum Size Subarray Sum Equals k](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/)

Given an integer array `nums` and an integer `k`, return the maximum length of a subarray that sums to `k`. If there is not one, return 0 instead.

**Constraints:**

- `1 <= nums.length <= 2 * 1e5`
- `-1e4 <= nums[i] <= 1e4`
- `-1e9 <= k <= 1e9`

**Example - 1**

```text
Input: nums = [1,-1,5,-2,3], k = 3
Output: 4
Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.
```

**Example - 2**

```text
Input: nums = [-2,-1,2,1], k = 1
Output: 2
Explanation: The subarray [-1, 2] sums to 1 and is the longest.
```

<br/>

**哈希 + 前缀和**
- 构造前缀和 `prefix[i] = sum(nums[0, i])`。
- 现在的问题等价于：找到一对索引 `i, j` （可以相同），使得 `prefix[i] - prefix[j] == k` 。`prefix[i]` 代表区间 `[0, i]`，`prefix[j]` 代表 `[0, j]`，因此 `prefix[i] - prefix[j]` 的区间长度为 `i - j` 。
  - 特殊情况：也有可能只需要找到一个 `prefix[i] = sum(nums[0, i]) = k`，这样区间长度是 `i + 1`。
- 扫描每一个 `prefix[i]`，并用哈希表记录它们出现的下标。对于当前的 `prefix[i]` ，如果找到 `prefix[i] - k` 出现过在哈希表中，那么就找到了一个满足条件的子数组。

`{0, -1}` 表示找到区间 `[0, i]` 是满足条件的。

```cpp
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        unordered_map<int, int> table = {{0, -1}};  // prefix sum -> index
        int n = nums.size(), sum = 0, res = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            // prefix[i] - prefix[j] denotes range [j + 1, i], whose length is i - j
            if (table.count(sum - k))
                res = max(res, i - table[sum - k]);
            
            if (!table.count(sum))
                table[sum] = i;
        }
        return res;
    }
};
```



## [560. Subarray Sum Equals K](https://leetcode.cn/problems/subarray-sum-equals-k/)

给你一个整数数组 `nums` 和一个整数 `k` ，请你统计并返回该数组中和为 `k` 的连续子数组的个数 。


示例 1：
```
输入：nums = [1,1,1], k = 2
输出：2
```
示例 2：
```
输入：nums = [1,2,3], k = 3
输出：2
```

提示：
```
1 <= nums.length <= 2 * 1e4
-1000 <= nums[i] <= 1000
-1e7 <= k <= 1e7
```

直觉想用滑动窗口，但由于存在 `nums[i] < 0` 的元素，所以窗口的和并不是单调的，所以滑动窗口不是有效的做法。

<br/>

**哈希 + 前缀和**

- 构造前缀和 `prefix[i] = sum(nums[0, i])`。
- 现在的问题等价于：找到一对索引 `i, j` （可以相同），使得 `prefix[i] - prefix[j] == k` 。用哈希表记录 `prefix[j]` 出现的次数。对于当前的 `prefix[i]`，如果 `prefix[i] - k` 出现了 `x` 次，那么就找到了 `x` 个满足要求的子数组。
  - 特殊情况：也有可能只需要找到一个 `prefix[i] = sum(nums[0, i]) = k`，区间 `[0, i]` 也是一个有效的子数组。

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        int n = nums.size(), prefix = 0, res = 0;
        for (int i = 0; i < n; ++i)
        {
            prefix += nums[i];
            if (prefix == k)
                res++;
            if (mp.count(prefix - k))
                res += mp[prefix - k];
            mp[prefix]++;
        }
        return res;
    }
};
```





## [1074. Number of Submatrices That Sum to Target](https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/)

Given a `matrix` and a `target`, return the number of non-empty submatrices that sum to target.

A submatrix `x1, y1, x2, y2` is the set of all cells `matrix[x][y]` with `x1 <= x <= x2` and `y1 <= y <= y2`.

Two submatrices `(x1, y1, x2, y2)` and `(x1', y1', x2', y2')` are different if they have some coordinate that is different: for example, if `x1 != x1'`.

**Example 1:**

<img src="https://assets.leetcode.com/uploads/2020/09/02/mate1.jpg" />

```
Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.
```

**Example 2:**

```
Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix. 
```

**Constraints:**

- `1 <= matrix.length <= 100`
- `1 <= matrix[0].length <= 100`
- `-1000 <= matrix[i] <= 1000`
- `-10^8 <= target <= 10^8`

<br/>

**Solution**

一种直观的做法是枚举每一个矩阵的左上角 `(i1, j1)` 和右下角 `(i2, j2)` ，即可枚举所有的子矩阵，但该做法的时间复杂度为 `O(mn * mn)`，超过 `1e8`。一共 4 层循环。

下面介绍哈希 + 前缀和的技巧，降低 1 层循环。

假设输入为 `matrix = [[0,1,0],[1,1,1],[0,1,0]]`，**构造每一列的前缀和**，即为：

```cpp
col_prefix = [
    [0, 0, 0],
    [0, 1, 0],
    [1, 2, 1],
    [1, 3, 1]
]
```

二维矩阵 `matrix` 的前缀和 `prefix[i, j]` 表示 `(0, 0) -> (i, j)` 的和，那么 `prefix` 和 `col_prefix` 存在以下关系：

```cpp
sum{col_prefix[i][0, ..., j]} = prefix[i, j] where 0 <= j < n
```

此时，枚举任意的 2 行 `i1, i2`，可以在 `O(n)` 时间内完成对 `j1, j2` 的检查。



**Code**

```cpp
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& mat, int target)
    {
        if (mat.empty() || mat[0].empty())
            return 0;
        
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> col_prefix(m + 1, vector<int>(n));
        
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 0; j < n; ++j)
                col_prefix[i][j] = col_prefix[i - 1][j] + mat[i - 1][j];
        }
        
        
        int res = 0;
        for (int i1 = 0; i1 <= m; ++i1)
        {
            for (int i2 = i1 + 1; i2 <= m; ++i2)
            {
                // the internal loop is leetcode-560, and 
                // nums = {col_prefix[i1, j] - col_prefix[i2, j]} where 0 <= j < n
                unordered_map<int, int> mp = {{0, 1}};
                int sub_mat = 0;
                for (int j = 0; j < n; ++j)
                {
                    sub_mat += col_prefix[i2][j] - col_prefix[i1][j];
                    if (mp.count(sub_mat - target))
                        res += mp[sub_mat - target];
                    mp[sub_mat]++;
                }
            }
        }
        return res;
    }
};
```

