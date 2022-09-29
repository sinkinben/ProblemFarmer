## 曼哈顿距离

给定两个 2D 平面的点 $(x_1, y_1), (x_2, y_2)$，它们的曼哈顿距离是 $|x_1 - x_2| + |y_1 - y_2|$ 。

常见的场景：

- 二维平面的最大曼哈顿距离：[Luogu P5098](https://www.luogu.com.cn/problem/P5098)
- 三维空间的最大曼哈顿距离：[1131. 绝对值表达式的最大值](https://leetcode.cn/problems/maximum-of-absolute-value-expression/)
- N 维空间的曼哈顿距离





## 二维平面的最大曼哈顿距离

[Luogu P5098](https://www.luogu.com.cn/problem/P5098)

给定若干 2D 平面的坐标，求任意 2 点之间的最大曼哈顿距离。根据定义，$\text{dis} = |x_1 - x_2| + |y_1 - y_2|$，所以有：
$$
\text{dis} = \begin{cases}
(x_1 + y_1) - (x_2 + y_2), x_1 > x_2, y_1 > y_2 \\
(x_1 - y_1) - (x_2 - y_2), x_1 > x_2, y_1 < y_2 \\
(-x_1 + y_1) - (-x_2 + y_2), x_1 < x_2, y_1 > y_2 \\
(-x_1 - y_1) - (-x_2 - y_2), x_1 < x_2, y_1 < y_2
\end{cases}
$$
定义：
$$
A_i = p_x + p_y \\
B_i = p_x - p_y \\
C_i = -p_x + p_y \\
D_i = -p_x - p_y
$$
其中， $(p_x, p_y)$ 是任意点 $p$ 的坐标。那么最大的曼哈顿距离是：
$$
\max{\{
  A_{max} - A_{min},
  B_{max} - B_{min},
  C_{max} - C_{min},
  D_{max} - D_{min}
\}}
$$


```cpp
#include <bits/stdc++.h>
using namespace std;
using pair_t = pair<int, int>;
pair_t getMinMax(vector<int> &vec)
{
    return {
        *min_element(begin(vec), end(vec)),
        *max_element(begin(vec), end(vec))
    };
}
int main()
{
    int n;
    cin >> n;
    
    int x, y;
    vector<pair_t> vec(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        vec[i] = {x, y};
    }
    
    vector<int> a(n), b(n), c(n), d(n);
    for (int i = 0; i < n; ++i)
    {
        auto [x, y] = vec[i];
        a[i] = x + y;
        b[i] = x - y;
        c[i] = -x + y;
        d[i] = -x - y;
    }
    auto [a1, a2] = getMinMax(a);
    auto [b1, b2] = getMinMax(b);
    auto [c1, c2] = getMinMax(c);
    auto [d1, d2] = getMinMax(d);
    cout << max(max(a2 - a1, b2 - b1), max(c2 - c1, d2 - d1)) << '\n';
    
}
```



## N 维空间的最大曼哈顿距离

[1131. 绝对值表达式的最大值](https://leetcode.cn/problems/maximum-of-absolute-value-expression/)

从二维的公式可以看出，N 维空间，对于点的坐标运算，一共有 $2^N$ 种。

如果 $N = 3$，那么有：

```
+++: x + y + z
---: -x - y - z
++-: x + y - z
+-+: x - y + z
-++: -x + y + z
--+: -x - y + z
-+-: -x + y - z
+--: x - y - z
```

一共 8 种组合（因此一共会产生 8 个数组）。我们使用 3 个 bit 去记录对应的维度是否为加法，即：

```
000 -> ---
001 -> --+
010 -> -+-
011 -> -++
100 -> +--
101 -> +-+
110 -> ++-
111 -> +++
```

代码实现：

```cpp
using vec = vector<int>;
using vec2 = vector<vec>;
class Solution {
public:
    pair<int, int> getMinMax(int d, int op, vec2 &points)
    {
        int minval = INT_MAX, maxval = INT_MIN;
        for (auto &point: points)
        {
            int val = 0;
            for (int i = 0; i < d; ++i)
            {
                if ((op >> i) & 1) val += point[i];
                else val -= point[i];
            }
            minval = min(minval, val);
            maxval = max(maxval, val);
        }
        return {minval, maxval};
    }
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2)
    {
        int n = arr1.size();
        int d = 3;  // 3D Manhattan distance
        vec2 points(n);
        for (int i = 0; i < n; ++i)
            points[i] = vec{arr1[i], arr2[i], i};
        
        int res = 0;
        // For each bit in op, 1-bit means '+', 0-bit means '-'
        for (int op = 0; op < (1 << d); ++op)
        {
            // Compute min, max value in each vector
            auto [minval, maxval] = getMinMax(d, op, points);
            res = max(res, maxval - minval);
        }
        return res;
    }
};
```

