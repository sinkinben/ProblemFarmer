



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

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) 
    {
        unordered_map<int, int> table;
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



## 2454. Next Greater Element IV

Hard. TODO.



## 84. Largest Rectangle in Histogram

对于每个高度 `h = height[i]`，需要找到其左侧的最近的较小的高度 `l = left[i]`，和右侧最近的较小高度 `r = right[i]`，那么高度 `h` 横向扩展的范围为 `[l + 1, r)`，其组成的面积为 `h * (r - l - 1)`。

`left[i], right[i]` 数组可通过单调栈计算。

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& arr)
    {
        stack<int> stk;
        int n = arr.size();
        vector<int> left(n, -1), right(n, -1);
        for (int i = n - 1; i >= 0; --i)
        {
            while (!stk.empty() && arr[i] <= arr[stk.top()])
                stk.pop();
            // now arr[i] >= arr[stk.top()]
            right[i] = stk.empty() ? n : stk.top();
            stk.push(i);
        }
        stk = stack<int>();
        for (int i = 0; i < n; ++i)
        {
            while (!stk.empty() && arr[i] < arr[stk.top()])
                stk.pop();
            // now arr[i] > arr[stk.top()]
            left[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);
        }

        // for (int x : left) cout << x << ' '; cout << '\n';
        // for (int x : right) cout << x << ' '; cout << '\n';

        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            int h = arr[i];
            res = max(res, h);
            res = max(res, h * (right[i] - 1 - left[i]));
        }
        return res;
    }
};
```



## 85. Maximal Rectangle

令 `histogram[i][j]` 表示：在第 `j` 列上，从 `mat[i][j]` 向上延伸（即 `mat[i -> 0][j]` 方向）的连续 `'1'` 的数量。

那么最大矩形的面积为：

- 对于每一行 `histogram[i]`，均可视为一个直方图，求出直方图中的最大矩形面积（即 [84. Largest Rectangle in Histogram](https://leetcode.cn/problems/largest-rectangle-in-histogram/) ）。
- 对于上述的 `n` 个 “最大面积”，当中最大的矩形的面积即为原问题的解。

```cpp
using vec = vector<int>;
using vec2 = vector<vec>;
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& mat) {
        if (mat.empty() || mat[0].empty())
            return 0;

        int m = mat.size(), n = mat[0].size();
        vec2 histogram(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j)
                if (mat[i][j] == '1')
                    histogram[i][j] = (i > 0 ? histogram[i - 1][j] : 0) + 1;
        }

        int res = 0;
        for (int i = 0; i < m; ++i)
            res = max(res, maxRectangleInHistogram(histogram[i]));
        return res;
    }

    int maxRectangleInHistogram(vec& nums) // 84. Largest Rectangle in Histogram
    {
        int n = nums.size();
        stack<int> stk;
        vec left(n, 0), right(n, 0);

        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && nums[stk.top()] >= nums[i])
                stk.pop();
            // now nums[stk.top()] < nums[i]
            left[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);
        }

        stk = stack<int>();
        for (int i = n - 1; i >= 0; --i) {
            while (!stk.empty() && nums[stk.top()] >= nums[i])
                stk.pop();
            // now nums[i] > nums[stk.top()]
            right[i] = stk.empty() ? n : stk.top();
            stk.push(i);
        }

        int area = 0;
        for (int i = 0; i < n; ++i) {
            int h = nums[i];
            area = max(area, h);
            area = max(area, h * (right[i] - left[i] - 1));
        }
        return area;
    }
};
```





## 907. Sum of Subarray Minimums

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
        stack<int> stk;
        vector<int> right(n, 0), left(n, 0);
        for (int i = 0; i < n; ++i)
        {
            while (!stk.empty() && arr[i] <= arr[stk.top()])
            {
                j = stk.top(), stk.pop();
                right[j] = i - j;
            }
            stk.push(i);
        }

        while (!stk.empty())
        {
            j = stk.top(), stk.pop();
            right[j] = n - j;
        }


        for (int i = n - 1; i >= 0; --i)
        {
            while (!stk.empty() && arr[i] < arr[stk.top()])
            {
                j = stk.top(), stk.pop();
                left[j] = j - i;
            }
            stk.push(i);
        }

        while (!stk.empty())
        {
            j = stk.top(), stk.pop();
            left[j] = j + 1;
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

