## Consecutive Number Sum

Leetcode:

- [829. Consecutive Numbers Sum](https://leetcode-cn.com/problems/consecutive-numbers-sum/)
- [剑指 Offer 57 - II. 和为s的连续正数序列](https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/)



## 和为 s 的连续正数序列

输入一个正整数 `target` ，输出所有和为 `target` 的连续正整数序列（至少含有两个数）。序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。

**滑动窗口**

```cpp
class Solution
{
public:
    vector<int> generate(int l, int r)
    {
        vector<int> seq(r - l + 1, 0);
        for (int i = l; i <= r; ++i) seq[i - l] = i;
        return std::move(seq);
    }
    vector<vector<int>> findContinuousSequence(int target)
    {
        vector<vector<int>> res;
        int l = 1, r = 2;
        while (l < r)
        {
            int sum = (r - l + 1) * (l + r) / 2;
            if (sum == target)
                res.emplace_back(generate(l, r)), ++l, ++r;
            else if (sum > target)
                ++l;
            else if (sum < target)
                ++r;
        }
        return res;
    }
};
```

<br/>

**数学**

设区间 $[l, r]$ 为一个可行解，根据等差数列求和公式，那么有：
$$
\frac{(r - l + 1)(l + r)}{2} = n \ \ \Rightarrow \ \ r^2+r-l^2+l-2n=0
$$
将 $r$ 视作未知数，根据求根公式：
$$
r = \frac{-1 \pm \sqrt{1+4(l^2-l+2n)}}{2}
$$
舍去负根。

有效的 $l, r$ 必须满足：$l, r$ 为整数，并且 $l < r$ ， 因为题目要求序列长度大于 1 。

从 $l = 1$ 开始枚举即可。

```cpp
class Solution
{
public:
    vector<int> generate(int l, int r)
    {
        vector<int> seq(r - l + 1, 0);
        for (int i = l; i <= r; ++i) seq[i - l] = i;
        return std::move(seq);
    }
    vector<vector<int>> findContinuousSequence(int n)
    {
        vector<vector<int>> res;
        int l = 1;
        double r = 2;
        do
        {
            r = (-1 + sqrt(1 + 4 * (1.0 * l * l - l + 2.0 * n))) / 2;
            if (l < r && r == (int)r)
                res.emplace_back(generate(l, (int)r));
            ++l;
        } while (l < r);
        return res;
    }
};
```



## 连续整数求和

给定一个正整数 `n`，返回连续正整数满足所有数字之和为 `n (1 <= n <= 1e9)` 的组数 。 

示例 1:

```text
输入: n = 5
输出: 2
解释: 5 = 2 + 3，共有两组连续整数([5],[2,3])求和后为 5。
```

示例 2:

```text
输入: n = 9
输出: 3
解释: 9 = 4 + 5 = 2 + 3 + 4
```

示例 3:

```text
输入: n = 15
输出: 4
解释: 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5
```

<br/>

**滑动窗口 (TLE)**

因为 `n <= 1e9` . 

```cpp
class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int l = 1, r = 2, res = 1;
        while (l < r)
        {
            int sum = (r - l + 1) * (l + r) / 2;
            if (sum == n)
                ++res, ++l, ++r;
            else if (sum < n)
                ++r;
            else if (sum > n)
                ++l;
        }
        return res;
    }
};
```

<br/>

**数学**

设满足要求的序列为 $x + 1, x + 2, \dots, x + k$ ，该序列之和满足：
$$
kx + \frac{k(1+k)}{2} = n \ \ \Rightarrow \ \ 2kx+k(k+1) = 2n \ \ \Rightarrow \ \ k(2x+k+1) = 2n
$$
显然，从 $k = 1$ 开始枚举，并找到对应的**整数** $x(x \ge 0)$ , 那么就相当于找到一个可行解。

但由于 $O(n)$ 时间是不可接受的，因此还需要找到枚举的上界。
$$
2n = k(2x+k+1) \ge k(k+1) > k^2 \ \ \Rightarrow \ \ k < \sqrt{2n}
$$
$O(\sqrt{n})$ 的解法对于 $n \le 10^9$ 来说是可接受的。

```cpp
class Solution {
public:
    int consecutiveNumbersSum(int n) {
        n <<= 1;
        /* sqrt(n) 应当向上取整 */
        int limit = sqrt(n) + 1, res = 0;
        for (int k = 1; k < limit; ++k)
            res += (n % k == 0) && ((n / k - k - 1) & 1) == 0;
        return res;
    }
};
```

