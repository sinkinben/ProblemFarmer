



## Leetcode | Monotonic Stack

- [496. Next Greater Element I](https://leetcode.cn/problems/next-greater-element-i/) - 求元素的右侧最近较大值。
- [503. Next Greater Element II](https://leetcode.cn/problems/next-greater-element-ii/) - 循环数组，求元素的右侧最近较大值。
  - [556. Next Greater Element III](https://leetcode.cn/problems/next-greater-element-iii/) - 求 `n` 的下一个更大值，`std::next_permutation` 解决。
- [2454. Next Greater Element IV](https://leetcode.cn/problems/next-greater-element-iv/) - 求每个元素的右侧的第二较大值。TODO.
- [739. Daily Temperatures](https://leetcode.cn/problems/daily-temperatures/) - 求元素右侧较大值的下标。



结合单调栈的题目：

- [84. Largest Rectangle in Histogram](https://leetcode.cn/problems/largest-rectangle-in-histogram/)
- [907. Sum of Subarray Minimums](https://leetcode.cn/problems/sum-of-subarray-minimums/)
- [85. Maximal Rectangle](https://leetcode.cn/problems/maximal-rectangle/)





## 496. Next Greater Element I

给定元素唯一的两个数组 `nums1, nums2`，且 `nums1` 是 `nums2` 的子集（即每一个 `nums1[i]` 都有唯一的 `nums2[j]` 与之对应）。求每一个 `nums1[i]` 在 `nums2` 中的下一个更大元素。

问题等价于：求每一个 `nums2[j]` 的下一个更大元素。

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) 
    {
        unordered_map<int, int> table;  // element -> next greater element
        stack<int> stk; // non-increasing stack
        for (int x : nums2)
        {
            while (!stk.empty() && stk.top() < x)
            {
                table[stk.top()] = x;
                stk.pop();
            }
            stk.push(x);
        }
        vector<int> res;
        for (int x : nums1)
            res.emplace_back(table.count(x) ? table[x] : -1);
        return res;
    }
};
```



## 503. Next Greater Element II

给定环状数组 `nums`，求 `nums[i]` 的下一个更大元素。

**Example 1:**

```
Input: nums = [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; 
The number 2 can't find next greater number. 
The second 1's next greater number needs to search circularly, which is also 2.
```

**Example 2:**

```
Input: nums = [1,2,3,4,3]
Output: [2,3,4,-1,4]
```

**Constraints:**

- `1 <= nums.length <= 1e4`
- `-1e9 <= nums[i] <= 1e9`

**Solution**


```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        
        int n = nums.size();
        vector<int> res(n, -1);
        stack<int> stk;
        for (int i = 0; i < 2 * n; ++i)
        {
            int idx = i % n;
            while (!stk.empty() && nums[stk.top()] < nums[idx])
            {
                res[stk.top()] = nums[idx];
                stk.pop();
            }
            // now nums[stk.top()] >= nums[idx]
            stk.push(i % n);
        }
        return res;
    }
};
```



## 556. Next Greater Element III

给你一个正整数 `n` ，请你找出符合条件的最小整数，其由重新排列 `n` 中存在的每位数字组成，并且其值大于 `n` 。如果不存在这样的正整数，则返回 `-1` 。

**注意** ，返回的整数应当是一个 **32 位整数** ，如果存在满足题意的答案，但不是 **32 位整数** ，同样返回 `-1` 。

转换为字符串，然后求 `next_permutation` 。

```cpp
class Solution {
public:
    int nextGreaterElement(int n) {
        string str = to_string(n);
        next_permutation(begin(str), end(str));
        int64_t res = stoll(str);
        return INT_MIN <= res && res <= INT_MAX && res > n ? res : -1;
    }
};
```





## 84. Largest Rectangle in Histogram

给定数组 `arr`，元素 `arr[i]` 表示直方图的高度，求直方图中最大矩形的面积。

**Solution**

对于每个高度 `h = height[i]`，需要找到其左侧的最近的较小的高度的位置 `l = left[i]`，和右侧最近的较小高度的位置 `r = right[i]`，那么高度 `h` 横向扩展的范围为 `[l + 1, r)`，其组成的面积为 `h * (r - l - 1)`。

此处的「较小」为严格小于。

`left[i], right[i]` 数组可通过单调栈计算。

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights)
    {
        int n = heights.size();
        vector<int> left(n, -1), right(n, n);
        stack<int> stk;

        for (int i = 0; i < n; ++i)
        {
            while (!stk.empty() && heights[stk.top()] > heights[i])
            {
                right[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }

        stk = stack<int>();
        for (int i = n - 1; i >= 0; --i)
        {
            while (!stk.empty() && heights[stk.top()] > heights[i])
            {
                left[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }

        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            // l = left[i], r = right[i] denote the smaller position of 'h' at two sides
            // the range [l + 1, r) is less than 'h', possible area is h * (r - l - 1)
            int h = heights[i];
            res = max(res, h);
            res = max(res, h * (right[i] - left[i] - 1));
        }

        return res;
    }
};
```



## 85. Maximal Rectangle

给定 01 矩阵 `matrix`，求 `matrix` 中元素均为 1 的最大矩形的面积。

**Solution**

令 `histogram[i][j]` 表示：在第 `j` 列上，从 `mat[i][j]` 向上延伸（即 `mat[i -> 0][j]` 方向）的连续 `'1'` 的数量。

那么最大矩形的面积为：

- 对于每一行 `histogram[i]`，均可视为一个直方图，求出直方图中的最大矩形面积（即 [84. Largest Rectangle in Histogram](https://leetcode.cn/problems/largest-rectangle-in-histogram/) ）。
- 对于上述的 `n` 个 “最大面积”，当中最大的矩形的面积即为原问题的解。

```cpp
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& mat)
    {
        if (mat.empty() || mat[0].empty())
            return 0;
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> histogram(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
                if (mat[i][j] == '1')
                    histogram[i][j] = 1 + (i > 0 ? histogram[i - 1][j] : 0);
        }
        int res = 0;
        for (auto &vec : histogram)
            res = max(res, maxRectangleHistogram(vec));
        return res;
    }

    int maxRectangleHistogram(vector<int> &heights)  // leetcode 84. Largest Rectangle in Histogram
    {
        int n = heights.size();
        vector<int> left(n, -1), right(n, n);
        stack<int> stk;

        for (int i = 0; i < n; ++i)
        {
            while (!stk.empty() && heights[stk.top()] > heights[i])
            {
                right[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }

        stk = stack<int>();
        for (int i = n - 1; i >= 0; --i)
        {
            while (!stk.empty() && heights[stk.top()] > heights[i])
            {
                left[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }

        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            // l = left[i], r = right[i] denote the smaller position of 'h' at two sides
            // the range [l + 1, r) is less than 'h', possible area is h * (r - l - 1)
            int h = heights[i];
            res = max(res, h);
            res = max(res, h * (right[i] - left[i] - 1));
        }

        return res;
    }
};
```





## 907. Sum of Subarray Minimums

Given an array of integers `arr`, find the sum of `min(b)`, where `b` ranges over every (contiguous) subarray of `arr`. Since the answer may be large, return the answer **modulo** `1e9 + 7`.

**Solution**

- 记 `left[i]` 为：以 `arr[i]` 为左端点，且 `arr[i]` 为最小值的**连续子数组**的数量；
- 记 `right[i]` 为：以 `arr[i]` 为右端点，且 `arr[i]` 为最小值的连续子数组的数量；
- 最终结果为 `SUM{arr[i] * left[i] * right[i]}`。

`left, right` 数组，可通过单调栈求解。


```cpp
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr)
    {
        int n = arr.size(), j = 0;
        vector<int> left(n, 0), right(n, 0);
        stack<int> stk;
        for (int i = 0; i < n; ++i)
        {
            while (!stk.empty() && arr[stk.top()] >= arr[i])
            {
                // next smaller element of arr[j] is arr[i], that is
                // all elements in range [j, i) are >= arr[j]
                j = stk.top(), stk.pop();
                left[j] = i - j;
            }
            stk.push(i);
        }
        while (!stk.empty())
        {
            j = stk.top(), stk.pop();
            left[j] = n - j;
        }

        for (int i = n - 1; i >= 0; --i)
        {
            while (!stk.empty() && arr[stk.top()] > arr[i])
            {
                // range (i, j] are all >= arr[j]
                j = stk.top(), stk.pop();
                right[j] = j - i;
            }
            stk.push(i);
        }
        while (!stk.empty())
        {
            j = stk.top(), stk.pop();
            right[j] = j + 1;
        }

        constexpr int64_t MOD = 1e9 + 7;
        int64_t res = 0;
        for (int i = 0; i < n; ++i)
        {
            int64_t val = ((int64_t)arr[i] * left[i] * right[i]) % MOD;
            res = (res + val) % MOD;
        }
        return res;
    }
};
```

注意 2 个单调栈，一个的比较条件必须为 `<=`，另一个必须要为 `<` 。这是为了处理重复元素的情况：

```cpp
// arr = [71,55,82,55]

// >=, > exp: 593
// 1 2 1 1 
// 1 2 1 4 

// >, > got: 703
// 1 3 1 1 
// 1 2 1 4 

// >=, >= got: 483
// 1 2 1 1 
// 1 2 1 2

// 其中 [55, 82, 55] 只能计算 1 次
```



**官方题解的写法**

```cpp
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr)
    {
        int n = arr.size(), j = 0;
        stack<int> stk;
        vector<int> right(n, 0), left(n, 0);
        for (int i = 0; i < n; ++i)
        {
            while (!stk.empty() && arr[i] <= arr[stk.top()])
                stk.pop();
            // now we have: arr[stk.top()] < arr[i]
            left[i] = stk.empty() ? i + 1 : i - stk.top();
            stk.push(i);
        }

        stk = stack<int>();
        for (int i = n - 1; i >= 0; --i)
        {
            while (!stk.empty() && arr[i] < arr[stk.top()])
                stk.pop();
            // now we have: arr[i] >= arr[stk.top()]
            right[i] = stk.empty() ? n - i : stk.top() - i;
            stk.push(i);
        }

        constexpr int64_t MOD = 1e9 + 7;
        int64_t res = 0;
        for (int i = 0; i < n; ++i)
        {
            int64_t val = ((int64_t)arr[i] * left[i] * right[i]) % MOD;
            res = (res + val) % MOD;
        }
        return res;
    }
};
```

