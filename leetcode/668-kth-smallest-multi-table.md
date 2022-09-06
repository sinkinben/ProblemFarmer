## Kth Smallest Number in Multiplication Table

Leetcode: [668. Kth Smallest Number in Multiplication Table](https://leetcode.cn/problems/kth-smallest-number-in-multiplication-table/)



**Solution**

乘法表中，每一行的从左往右，每一列的从上往下，都是递增的，不难想到矩阵形式的二分查找来做。

不妨转换一下问题的形式：给定数字 $x$ ，它是乘法表中的第几小元素？令 $f(x)$ 来表示乘法表中，严格小于 $x$ 的元素的个数。

显然我们需要令 $f(x) = k$ ，求得对应的 $x$ 。

对于第 $i$ 行，元素均为 $i$ 的倍数（且每个元素都是不同的），不超过 $x$ 的元素个数为 $\min{(\lfloor \frac{x}{i} \rfloor, n)}$ ，因此严格小于 $x$ 的元素个数为：
$$
f(x) = \sum_{i = 1}^{m} \min(\lfloor \frac{x}{i} \rfloor, n)
$$
当 $\lfloor \frac{x}{i} \rfloor \ge n$ 时，可得 $i \le \lfloor \frac{x}{n} \rfloor$ ，此时 $f(x) = n$，因此有：
$$
f(x) = \lfloor \frac{x}{n} \rfloor \cdot n + \sum_{i = \lfloor \frac{x}{n} \rfloor + 1}^{m} \lfloor \frac{x}{i} \rfloor
$$
显然， $f(x)$ 是一个单调递增函数，因而 $f(x) = k$ 这一方程可以使用二分法求零点。

```cpp
class Solution
{
public:
    int eval(int x, int m, int n)
    {
        int res = x / n * n;
        for (int i = x / n + 1; i <= m; ++i)
            res += x / i;
        return res;
    }
    int findKthNumber(int m, int n, int k)
    {
        int l = 1, r = m * n;
        /* binary search in range [l, r) */
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            int cnt = eval(mid, m, n);
            if (cnt < k) l = mid + 1;
            else r = mid;
        }
        return l;
    }
};
```

