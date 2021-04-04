## [leetcode] 单调栈

本文总结单调栈算法。

## 原问题

学习一个算法，我们需要清楚的是：这个算法最原始的问题背景是什么样的？



### 下一个更小元素

给定一个数组 `nums`，返回每个元素的下一个更小的元素的下标 `res`，即 `res[i]` 记录的是 `nums[i]` 右端第一个比它小的元素的下标（不存在则为 -1 ）。

例如 `nums = [2,1,2,4,3]`，那么 `res = [1, -1, -1, 4, -1]` .

从左往右扫描数组，栈底到栈顶维持严格升序，当扫描当前元素 `nums[i] = x` 时，如果需要出栈（说明栈顶大于等于当前的 `x` ），那么 `x` 就是**出栈元素**的下一个更小元素。

```cpp
vector<int> nextSmallerNumber(vector<int> &&nums)
{
    int n = nums.size(), idx = -1;
    vector<int> res(n, -1);
    stack<int> stk;
    for (int i = 0; i < n; i++)
    {
        while (!stk.empty() && nums[i] <= nums[stk.top()])
        {
            idx = stk.top(), stk.pop();
            res[idx] = i;
        }
        stk.emplace(i);
    }
    return res;
}
```

相关题目：

- [两侧的更小值](https://www.nowcoder.com//practice/e3d18ffab9c543da8704ede8da578b55?tpId=101&tqId=33169&rp=1&ru=%2Fta%2Fprogrammer-code-interview-guide&qru=%2Fta%2Fprogrammer-code-interview-guide%2Fquestion-ranking&tab=answerKey)

### 下一个更大元素

给定一个数组 `nums`，返回每个元素的下一个更大的元素的下标 `res`，即 `res[i]` 记录的是 `nums[i]` 右端第一个比它大的元素的下标（不存在则为 -1 ）。

例如 `nums = [2,1,2,4,3]`，那么 `res = [3, 2, 3, -1, -1]` .

从左往右扫描数组，栈底到栈顶维持降序（不要求严格），当扫描当前元素 `nums[i] = x` 时，如果需要出栈（说明栈顶严格小于当前的 `x` ），那么 `x` 就是出栈元素的下一个更大元素。

```cpp
vector<int> nextGreaterNumber(vector<int> &&nums)
{
    int n = nums.size(), idx;
    vector<int> res(n, -1);
    stack<int> stk;
    for (int i = 0; i < n; i++)
    {
        while (!stk.empty() && nums[stk.top()] < nums[i])
        {
            idx = stk.top(), stk.pop();
            res[idx] = i;
        }
        stk.emplace(i);
    }
    return res;
}
```

类似题目：

- [496. 下一个更大元素 I](https://leetcode-cn.com/problems/next-greater-element-i/)
- [503. 下一个更大元素 II](https://leetcode-cn.com/problems/next-greater-element-ii/)
-  [739. 每日温度](https://leetcode-cn.com/problems/daily-temperatures/)

## Leetcode

### 下一个更大元素 I

题目：[496. 下一个更大元素 I](https://leetcode-cn.com/problems/next-greater-element-i/)

题目保证 `nums1` 是 `nums2` 的子集，首先在 `nums2` 先做一次「下一个更大」元素，使用一个哈希表记录结果。

然后扫描 `nums1` ，把哈希表的结果按序填入数组 `res` 即可。

每次自己写出了最优解，并且官方也是同一思路，都会觉得好有成就感 😄 。

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) 
    {
        unordered_map<int,int> table;
        // 单调递减栈，不需要严格递减
        stack<int> stk;
        for (int x: nums2)
        {
            while (!stk.empty() && stk.top() < x)
            {
                table[stk.top()] = x;
                stk.pop();
            }
            stk.emplace(x);
        }
        int n = nums1.size();
        vector<int> res(n, -1);
        for (int i=0; i<n; i++)
        {
            if (table.count(nums1[i]))
                res[i] = table[nums1[i]];
        }
        return res;     
    }
};
```

### 下一个更大元素 II

题目：[503. 下一个更大元素 II](https://leetcode-cn.com/problems/next-greater-element-ii/)

这里数组是一个 **循环数组** ，那么最简单的处理方式当然就是令 `nums = nums + nums` 了，这样做完一遍「下一个更大元素」之后，只需要截取 `res` 数组的前一半即可。

```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        if (nums.size() == 0) return {};
        nums.insert(nums.end(), nums.begin(), nums.end());
        int n = nums.size(), idx;
        vector<int> res(n, -1);
        stack<int> stk;  // 单调递减栈，不需要严格递减
        for (int i=0; i<n; i++)
        {
            while (!stk.empty() && nums[stk.top()] < nums[i])
            {
                idx = stk.top(), stk.pop();
                res[idx] = nums[i];
            }
            stk.push(i);
        }
        return vector<int>(res.begin(), res.begin() + n/2);
    }
};
```

那么，有时候，面试官就对最优解非常苛刻（比如微软），不允许我们使用这种额外空间，那么就要使用**取模**的方式去模拟循环数组：

```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        if (nums.size() == 0) return {};
        int n = nums.size(), idx;
        vector<int> res(n, -1);
        stack<int> stk;  // 单调递减栈，不需要严格递减
        for (int i=0; i<=2*n-1; i++)
        {
            while (!stk.empty() && nums[stk.top()] < nums[i % n])
            {
                idx = stk.top(), stk.pop();
                res[idx] = nums[i % n];
            }
            stk.push(i % n);
        }
        return res;
    }
};
```

结果模运算多了，时间效率还不如第一种。



### 每日温度

题目：[739. 每日温度](https://leetcode-cn.com/problems/daily-temperatures/)

本题就是「下一个更大元素」的裸题了，维持一个递减栈（记录下标）即可。

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int n = T.size(), idx = 0;
        vector<int> res(n, 0);
        stack<int> stk;   // 单调递减栈
        for (int i=0; i<n; i++)
        {
            while (!stk.empty() && T[stk.top()] < T[i])
            {
                idx = stk.top(), stk.pop();
                res[idx] = i - idx;
            }
            stk.emplace(i);
        }
        return res;
    }
};
```

## 其他

### 两侧的更小值 I

题目：[两侧的更小值](https://www.nowcoder.com//practice/e3d18ffab9c543da8704ede8da578b55?tpId=101&tqId=33169&rp=1&ru=%2Fta%2Fprogrammer-code-interview-guide&qru=%2Fta%2Fprogrammer-code-interview-guide%2Fquestion-ranking&tab=answerKey)

微软的面试题 😭 ，这是套「下一个更小元素」的模版。**此处不含重复元素**

维持一个**严格升序**的栈，当扫描当前元素 `nums[i] = x` 时，如果需要出栈（说明栈顶大于等于当前的 `x` ），那么 `x` 就是**出栈元素**的右侧更小值。那么，出栈元素的左侧更小值在哪呢？就是它在栈中的邻居。

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
vector<pair<int, int>> solve(vector<int> &nums)
{
    int n = nums.size(), idx;
    stack<int> stk; // 严格递增栈
    vector<pair<int, int>> res(n, {-1, -1});
    for (int i = 0; i < n; i++)
    {
        while (!stk.empty() && nums[stk.top()] >= nums[i])
        {
            idx = stk.top(), stk.pop();
            res[idx].second = i;
            res[idx].first = (stk.empty() ? -1 : stk.top());
        }
        stk.push(i);
    }
    while (!stk.empty())
    {
        idx = stk.top(), stk.pop();
        res[idx].first = (stk.empty() ? -1 : stk.top());
    }
    return res;
}
int main()
{
    int n;
    cin >> n;
    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++) cin >> nums[i];
    auto ans = solve(nums);
    for (auto [x,y]: ans) printf("%d %d\n", x, y);
}
```

### 两侧的更小值 II

题目：[两侧的更小值 II](https://www.nowcoder.com//practice/2a2c00e7a88a498693568cef63a4b7bb?tpId=101&tqId=33256&rp=1&ru=%2Fta%2Fprogrammer-code-interview-guide&qru=%2Fta%2Fprogrammer-code-interview-guide%2Fquestion-ranking&tab=answerKey)

**此处含有重复元素。**

那么我们还是维持一个递增的栈（不要求严格），当扫描 `nums[i]` 时需要出栈，说明 `nums[s.top()]` 严格大于 `nums[i]`，那么就找到了 `nums[s.top()]` 的右侧更小值是 `nums[i]` 。

那么 `nums[s.top()]` 左侧更小值在哪呢？是否就是在栈中的邻居呢？答案是否定的。

比如输入：`[1, 3, 3, 1]` . 当扫描到最后一个元素 1 的时候：

```
stk: 1 3 3 (1)
     ^      ^
     |      |
    left   cur
```

这时候显然需要出栈，那么两个 3 的右侧更小值都是 `cur` ，但**栈顶的 3 的左侧更小值不是它的邻居**（而是 `left` 指向的 1 ）。

这时候，我们用一个 `buf` 把这样 3 都记录下来，那么 `buf` 中的元素，它们的两侧更小值都是 `{left, cur}` 。如果 `left` 不存在（栈为空），那么 `left = -1` 。

**注意：代码实现中，栈存放的是下标。**

**代码实现**

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
vector<pair<int, int>> solve(vector<int> &nums)
{
    int n = nums.size(), idx;
    stack<int> stk; // 递增栈，不要求严格
    vector<pair<int, int>> res(n, {-1, -1});
    for (int i = 0; i < n; i++)
    {
        while (!stk.empty() && nums[stk.top()] > nums[i])
        {
            idx = stk.top(), stk.top();
            vector<int> buf = {idx};
            while (!stk.empty() && nums[stk.top()] == nums[idx])
                buf.emplace_back(stk.top()), stk.pop();
            for (int x : buf)
            {
                res[x].first = (stk.empty() ? -1 : stk.top());
                res[x].second = i;
            }
        }
        stk.emplace(i);
    }
    while (!stk.empty())
    {
        idx = stk.top(), stk.top();
        vector<int> buf = {idx};
        while (!stk.empty() && nums[stk.top()] == nums[idx])
            buf.emplace_back(stk.top()), stk.pop();
        for (int x : buf)
            res[x].first = (stk.empty() ? -1 : stk.top());
    }
    return res;
}
```

