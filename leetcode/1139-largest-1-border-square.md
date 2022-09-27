## 1139. 最大的以 1 为边界的正方形

Leetcode: [1139. 最大的以 1 为边界的正方形](https://leetcode.cn/problems/largest-1-bordered-square/)

给你一个由若干 0 和 1 组成的二维网格 `grid`，请你找出边界全部由 1 组成的最大正方形子网格，并返回该子网格中的元素数量（即正方形的面积）。如果不存在，则返回 0。

示例 1：
```
输入：grid = [[1,1,1],[1,0,1],[1,1,1]]
输出：9
```
示例 2：
```
输入：grid = [[1,1,0,0]]
输出：1
```

提示：
```
1 <= grid.length <= 100
1 <= grid[0].length <= 100
grid[i][j] 为 0 或 1
```

<br/>

**题解**

参考 [Solution](https://leetcode.com/problems/largest-1-bordered-square/discuss/345265/c%2B%2B-beats-100-(both-time-and-memory)-concise-with-algorithm-and-image) .

首先定义 2 个辅助数组，表示水平方向上连续 1 的最大数目，和垂直方向上连续 1 的最大数目。

<img src="https://images.cnblogs.com/cnblogs_com/sinkinben/2206480/o_220927135348_img1.png"/>

然后从 `[m - 1, n - 1]` 开始扫描，

<img src="https://images.cnblogs.com/cnblogs_com/sinkinben/2206480/o_220927135422_img2.png"/>

一个正方形有上下左右，一共 4 个边，记为 up-side, bottom-side, left-side, right-side 。

在扫描 `hor[i, j]` 和 `ver[i, j]` 的时候（上面的橙色格子，分别表示 bottom-side 和 right-side 的最长长度），令 `d = min(hor[i, j], ver[i, j])`，我们可以确定 bottom-side, right-side 的长度都能取 `d` ，此时需要检查 left-side 和 up-side 是否可以取 `d` 。即：

```
hor[i - d + 1, j] >= d &&
ver[i, j - d + 1] >= d
// 上图的蓝色格子位置
```

如果四个方向都能取 `d` ，那么我们就找到了一个满足要求的正方形，在所有这样的正方形中，取最大的边长即可。

```cpp
using vec = vector<int>;
using vec2 = vector<vec>;
class Solution {
public:
    int largest1BorderedSquare(vec2& grid)
    {
        int m = grid.size(), n = grid[0].size();
        vec2 hor(m, vec(n));  // horizonal line
        vec2 ver(m, vec(n));  // vertical line
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 0) continue;
                hor[i][j] = (j > 0 ? hor[i][j - 1] : 0) + 1;
                ver[i][j] = (i > 0 ? ver[i - 1][j] : 0) + 1;
            }
        }
        int res = 0;
        for (int i = m - 1; i >= 0; --i)
        {
            for (int j = n - 1; j >= 0; --j)
            {
                if (hor[i][j] == 0 || ver[i][j] == 0) continue;
                int d = min(hor[i][j], ver[i][j]);
                if (j + 1 >= d && ver[i][j - d + 1] >= d &&
                    i + 1 >= d && hor[i - d + 1][j] >= d)
                    res = max(res, d);
            }
        }
        return res * res;
    }
};
```

但上述代码忽略了这样的情况，

```
grid (满足要求的最大边长是 3 )
0 1 1 1
0 1 1 1
1 1 1 1
1 1 1 1

hor
0 1 2 3
0 1 2 3
1 2 3 4
1 2 3 4

ver
0 1 1 1
0 2 2 2
1 3 3 3
2 4 4 4
```

在 `[m - 1, n - 1]` 位置，虽然不能取边长为 4 的正方形，但可以取 3 。

因此，应该尝试 `[res, d]` 这个区间内的每一个值（`d -> res` 只要找到一个即可）。

```cpp
using vec = vector<int>;
using vec2 = vector<vec>;
class Solution {
public:
    int largest1BorderedSquare(vec2& grid)
    {
        int m = grid.size(), n = grid[0].size();
        vec2 hor(m, vec(n));  // horizonal line
        vec2 ver(m, vec(n));  // vertical line
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 0) continue;
                hor[i][j] = (j > 0 ? hor[i][j - 1] : 0) + 1;
                ver[i][j] = (i > 0 ? ver[i - 1][j] : 0) + 1;
            }
        }
        int res = 0;
        for (int i = m - 1; i >= 0; --i)
        {
            for (int j = n - 1; j >= 0; --j)
            {
                if (hor[i][j] == 0 || ver[i][j] == 0) continue;
                int d = min(hor[i][j], ver[i][j]);
                for (; d > res; --d)
                {
                    if (j + 1 >= d && ver[i][j - d + 1] >= d &&
                        i + 1 >= d && hor[i - d + 1][j] >= d)
                        res = max(res, d);
                }
            }
        }
        return res * res;
    }
};
```

