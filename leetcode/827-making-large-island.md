## 827. 最大人工岛

Leetcode: [827. 最大人工岛](https://leetcode.cn/problems/making-a-large-island/)

给你一个大小为 `n x n` 二进制矩阵 `grid` 。最多 只能将一格 0 变成 1 。

返回执行此操作后，`grid` 中最大的岛屿面积是多少？

岛屿由一组上、下、左、右四个方向相连的 1 形成。

示例 1:
```
输入: grid = [[1, 0], [0, 1]]
输出: 3
解释: 将一格0变成1，最终连通两个小岛得到面积为 3 的岛屿。
```
示例 2:
```
输入: grid = [[1, 1], [1, 0]]
输出: 4
解释: 将一格0变成1，岛屿的面积扩大为 4。
```
示例 3:
```
输入: grid = [[1, 1], [1, 1]]
输出: 4
解释: 没有0可以让我们变成1，面积依然为 4。
```

**提示：**

- `n == grid.length`
- `n == grid[i].length`
- `1 <= n <= 500`
- `grid[i][j]` 为 `0` 或 `1`

<br/>

**并查集解法**

- 首先，给每个单元格 `grid[i, j]` 一个 ID，为 `i * n + j` .
- 对 `grid[i, j] == 1` 的位置，建立并查集，如果它的上下左右四个方向，存在 `grid[x, y] = 1`，那么合并之。

与此同时，并查集需要记录每个联通分量的大小（即顶点数目）。

建立并查集之后，设结果为 `res`:

- 对于 `grid[i, j] = 1` 的位置，其所在联通分量的根结点为 `p = find(i * n + j)`，那么令 `res = max(res, size[p])`.

- 对每一个 `grid[i, j] == 0` 的位置，尝试令它变为 1 。

  - 尝试将其与四个方向联通（条件是这四个方向满足 `grid[x, y] = 1`）。

  - 考虑到这四个方向可能同属于一个联通分量（如下例子），一个联通分量可通过它的根结点来标记，我们可通过 `set` 去重。

    ```text
    1 1 1
    1 0 1
    1 1 1
    ```

**代码实现**

```cpp
const pair<int, int> dirs[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
class Solution {
public:
    vector<int> root, size;
    int find(int x) { return root[x] == -1 ? x : root[x] = find(root[x]); }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y) root[y] = x, size[x] += size[y], size[y] = size[x];
    }
    int largestIsland(vector<vector<int>>& grid)
    {
        int n = grid.size();
        if (n <= 1) return n;

        auto getID = [=](int i, int j) { return i * n + j; };
        auto valid = [=](int i, int j) { return 0 <= i && i < n && 0 <= j && j < n; };

        // Build the disjoint set
        root.resize(n * n, -1);
        size.resize(n * n, 1);
        for (int id = 0; id < n * n; ++id)
        {
            int i = id / n, j = id % n;
            if (grid[i][j] == 0) continue;
            for (auto [dx, dy]: dirs)
            {
                int x = i + dx, y = j + dy;
                if (valid(x, y) && grid[x][y] == 1) merge(id, getID(x, y));
            }
        }

        // Change one zero to one
        int res = 0;
        for (int id = 0; id < n * n; ++id)
        {
            int i = id / n, j = id % n;
            if (grid[i][j] == 1)
                res = max(res, size[find(id)]);
            else
            {
                set<int> st;
                for (auto [dx, dy]: dirs)
                {
                    int x = i + dx, y = j + dy;
                    if (valid(x, y) && grid[x][y] == 1)
                        st.emplace(find(getID(x, y)));
                }
                int area = 1;
                for (int x: st) area += size[x];
                res = max(res, area);
            }
        }
        return res;
    }
};
```



