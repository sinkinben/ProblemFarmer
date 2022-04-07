## Unique Paths

Leetcode: [62. Unique Paths](https://leetcode.com/problems/unique-paths)

There is a robot on an `m x n` grid. The robot is initially located at the **top-left corner** (i.e., `grid[0][0]`). The robot tries to move to the **bottom-right corner** (i.e., `grid[m - 1][n - 1]`). The robot can only move either down or right at any point in time.

Given the two integers `m` and `n`, return *the number of possible unique paths that the robot can take to reach the bottom-right corner*.

The test cases are generated so that the answer will be less than or equal to `2 * 1e9`.

<img src="https://assets.leetcode.com/uploads/2018/10/22/robot_maze.png" />

```cpp
Input: m = 3, n = 7
Output: 28
```

**DP Solution**

`dp[i, j]` denote the number of paths to reach position `(i, j)`.

```cpp
class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        return dp.back().back();
    }
};
```

**Math Solution**

To reach `(m, n)`, the robot need to go down for `m - 1` steps, and go right for `n - 1` steps. Totally `m + n - 2` steps.

These two directions are independent. So the answer is $C_{m+n - 2}^{m - 1}$.

```cpp
class Solution
{
public:
    uint64_t combineNumber(int n, int m)
    {
        uint64_t k = 1;
        for (int i = 1; i <= m; i++)
            k = k * (n - m + i) / i;
        return k;
    }
    int uniquePaths(int m, int n) { return combineNumber(m + n - 2, m - 1); }
};
```



## Unique Paths II

Leetcode: [63. Unique Paths II](https://leetcode.com/problems/unique-paths-ii)

You are given an `m x n` integer array `grid`. There is a robot initially located at the **top-left corner** (i.e., `grid[0][0]`). The robot tries to move to the **bottom-right corner** (i.e., `grid[m-1][n-1]`). The robot can only move either down or right at any point in time.

An obstacle and space are marked as `1` or `0` respectively in `grid`. A path that the robot takes cannot include **any** square that is an obstacle.

Return *the number of possible unique paths that the robot can take to reach the bottom-right corner*.

The testcases are generated so that the answer will be less than or equal to `2 * 109`.

**Example**

```text
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
```

**DP Solution**

Let `dp[i, j]` denote the number of path to reach position `(i, j)`.

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0 || grid[0][0]) return 0;
        int m = grid.size(), n = grid[0].size();
        
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m && grid[i][0] != 1; ++i) dp[i][0] = 1;
        for (int j = 0; j < n && grid[0][j] != 1; ++j) dp[0][j] = 1;
        
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                dp[i][j] = grid[i][j] ? 0 : dp[i-1][j] + dp[i][j-1];
        
        return dp[m-1][n-1];
    }
};
```



## Unique Paths III

Leetcode: [980. Unique Paths III](https://leetcode.com/problems/unique-paths-iii)

You are given an `m x n` integer array `grid` where `grid[i][j]` could be:

- `1` representing the starting square. There is exactly one starting square.
- `2` representing the ending square. There is exactly one ending square.
- `0` representing empty squares we can walk over.
- `-1` representing obstacles that we cannot walk over.

Return *the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once*.

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 20`
- `1 <= m * n <= 20`
- `-1 <= grid[i][j] <= 2`
- There is exactly one starting cell and one ending cell.

**Example**

<img src="https://assets.leetcode.com/uploads/2021/08/02/lc-unique1.jpg" />

```text
Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
```

**Brute Force Solution (AC)**

- Brute force DFS. It's a suprise that brute force DFS can be accepted.
- `remained` denote the number of cells that we have not visited.
- Time complexity is $O(4^{m+n})$ .

```cpp
using pair_t = pair<int, int>;
class Solution {
public:
    int m, n, res = 0;
    vector<pair_t> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    int uniquePathsIII(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        m = grid.size(), n = grid[0].size();
        
        int x = -1, y = -1;
        int remained = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1) x = i, y = j;
                remained += grid[i][j] != -1;
            }
        }
        dfs(grid, remained, x, y);
        return res;
    }
    
    bool valid(int idx, int limit) { return 0 <= idx && idx < limit; }
    
    void dfs(vector<vector<int>>& grid, int remained, int x, int y)
    {
        if (!valid(x, m) || !valid(y, n) || grid[x][y] == -1)
            return;
        if (grid[x][y] == 2)
        {
            if (remained == 1) ++res;
            return;
        }
        --remained, grid[x][y] = -1;
        for (auto [dx, dy] : dirs)
            dfs(grid, remained, x + dx, y + dy);
        ++remained, grid[x][y] = 0;
    }
};
```

