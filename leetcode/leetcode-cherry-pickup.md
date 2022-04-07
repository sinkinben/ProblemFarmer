## Cherry Pickup

Leetcode: [741. Cherry Pickup](https://leetcode.com/problems/cherry-pickup)

You are given an `n x n` `grid` representing a field of cherries, each cell is one of three possible integers.

- `0` means the cell is empty, so you can pass through,
- `1` means the cell contains a cherry that you can pick up and pass through, or
- `-1` means the cell contains a thorn that blocks your way.

Return *the maximum number of cherries you can collect by following the rules below*:

- Starting at the position `(0, 0)` and reaching `(n - 1, n - 1)` by moving right or down through valid path cells (cells with value `0` or `1`).
- After reaching `(n - 1, n - 1)`, returning to `(0, 0)` by moving left or up through valid path cells.
- When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell `0`.
- If there is no valid path between `(0, 0)` and `(n - 1, n - 1)`, then no cherries can be collected.

**Example - 1**

<img src="https://assets.leetcode.com/uploads/2020/12/14/grid.jpg" />

```text
Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
Output: 5
Explanation: The player started at (0, 0) and went down, down, right right to reach (2, 2).
4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
Then, the player went left, up, up, left to return home, picking up one more cherry.
The total number of cherries picked up is 5, and this is the maximum possible.
```

**Example - 2**

```python
Input:
[
    [1, 1, 0],
    [0, 1, 1],
    [1, 1, 0],
    [0, 1, 1]
]
Output: 8
```

<br/>

**Solution - Three Dimensions DP**

Consider reverse the path in the 1st round above. That means we set two robots at `(n-1, n-1)`, and they want to get max numbers of cherries and reach `(0, 0)` finally.

**These two robots can be at same position at the same time.**

- Notice that after `t` steps, a robot reach `(r, c)`, and we can have `r + c = t`.
- For two robots, suppose after `t` steps, one is at `(r1, c1)`, and another is at `(r2, c2)`, then we can have `r2 = r1 + c1 - c2`.
- Hence we can use `r1, c1, c2` 3 variables to enumerate all the states.

Let `dp[r1][c1][c2]` denote the max numbers of cherries that robots can get when they are at `(r1, c1), (r2, c2)`. Then we can have:
```
dp[r1, c1, c2] = grid[r1, c1] + grid[r2, c2]+ 
max(
  dp[r1, c1 + 1, c2 + 1],  // bot1: ⬅️, bot2: ⬅️
  dp[r1 + 1, c1, c2 + 1],  // bot1: ⬆️, bot2: ⬅️
  dp[r1, c1 + 1, c2],      // bot1: ⬅️, bot2: ⬆️
  dp[r1 + 1, c1, c2]       // bot1: ⬆️, bot2: ⬆️
)
```
where `(r1, c1)` and `(r2, c2)` are different positions.


Here is the code. We define `calc(i, j, k)` to compute value of `dp[i, j, k]`.

```cpp
class Solution {
public:
    const int INTMIN = -(0x3f3f3f3f);
    typedef vector<int> vec_t;
    typedef vector<vec_t> vec2_t;
    typedef vector<vec2_t> vec3_t;
    vec3_t dp;
    int n;
    vec2_t grid;
    int cherryPickup(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0) return 0;
        
        n = grid.size();
        swap(this->grid, grid);
        dp.resize(n, vec2_t(n, vec_t(n, INTMIN)));
        return max(0, calc(0, 0, 0));
    }
    
    int calc(int r1, int c1, int c2)
    {
        int r2 = r1 + c1 - c2;
        if (r1 == n || r2 == n || c1 == n || c2 == n ||
            grid[r1][c1] == -1 || grid[r2][c2] == -1) 
            return INTMIN;
        else if (r1 == n - 1 && c1 == n - 1) 
            return grid[r1][c1];
        else if (dp[r1][c1][c2] != INTMIN) 
            return dp[r1][c1][c2];
        else
        {
            int res = grid[r1][c1];
            // pay attention to they are at the same position
            if (c1 != c2 && r1 != r2) res += grid[r2][c2];
            res += max(
                max(calc(r1, c1 + 1, c2), calc(r1 + 1, c1, c2)),
                max(calc(r1, c1 + 1, c2 + 1), calc(r1 + 1, c1, c2 + 1))
            );
            return dp[r1][c1][c2] = res;
        }
        
    }
};
```





## Cherry Pickup II

Leetcode: [1463. Cherry Pickup II](https://leetcode.com/problems/cherry-pickup-ii)

You are given a `rows x cols` matrix `grid` representing a field of cherries where `grid[i][j]` represents the number of cherries that you can collect from the `(i, j)` cell.

You have two robots that can collect cherries for you:

- **Robot #1** is located at the **top-left corner** `(0, 0)`, and
- **Robot #2** is located at the **top-right corner** `(0, cols - 1)`.

Return *the maximum number of cherries collection using both robots by following the rules below*:

- From a cell `(i, j)`, robots can move to cell `(i + 1, j - 1)`, `(i + 1, j)`, or `(i + 1, j + 1)`.
- When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
- When both robots stay in the same cell, only one takes the cherries.
- Both robots cannot move outside of the grid at any moment.
- Both robots should reach the bottom row in `grid`.

**Constraints:**

- `rows == grid.length`
- `cols == grid[i].length`
- `2 <= rows, cols <= 70`
- `0 <= grid[i][j] <= 100`

**Example**

<img src="https://assets.leetcode.com/uploads/2020/04/29/sample_1_1802.png" />

```text
Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
Output: 24
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
Total of cherries: 12 + 12 = 24.
```

<br/>

**Solution**

Before you read this, you should pass the [Cheery Pickup](https://leetcode.com/problems/cherry-pickup/), here is my [solution for it](https://leetcode.com/discuss/topic/1677993).

For this problem, we know that:
+ Two robots are always at the same row, and they maybe at different columns.
+ Hence we let `dp[r, c1, c2]` denote the max number of cherries we can get, when one robot is at `(r, c1)` and the another is at `(r, c2)`.

Each robot has 3 choices, then for `dp[r, c1, c2]`, the next state has 3 * 3 = 9 possible cases. That is:
```cpp
dp[r, c1, c2] = grid[r, c1] + grid[r, c2] + 
max(
	dp[r + 1, c1 - 1, c2 - 1],
	dp[r + 1, c1 - 1, c2 ],
	dp[r + 1, c1 - 1, c2 + 1],
	// ----
	dp[r + 1, c1, c2 - 1],
	dp[r + 1, c1, c2],
	dp[r + 1, c1, c2 + 1],
	// ----
	dp[r + 1, c1 + 1, c2 - 1],
	dp[r + 1, c1 + 1, c2],
	dp[r + 1, c1 + 1, c2 + 1],
)
```
where `c1 != c2`.

Here is the code. We define `calc(i, j, k)` to compute `dp[i, j, k]`.

```cpp
typedef vector<int> vec_t;
typedef vector<vec_t> vec2_t;
typedef vector<vec2_t> vec3_t;
class Solution {
public:
    vec3_t dp;
    vec2_t grid;
    int m, n;
    int cherryPickup(vector<vector<int>>& grid) 
    {
        m = grid.size(), n = grid[0].size();
        dp.resize(m, vec2_t(n, vec_t(n, -1)));
        swap(this->grid, grid);
        return max(0, calc(0, 0, n - 1));
    }
    int calc(int r, int c1, int c2)
    {
        static const int dirs[3] = {-1, 0, 1}; // movement on column
        
        if (r == m || c1 < 0 || c1 >= n || c2 < 0 || c2 >= n) return 0;
        if (dp[r][c1][c2] != -1) return dp[r][c1][c2];
        
        int res = grid[r][c1] + (c1 != c2 ? grid[r][c2] : 0);
        if (r == m - 1)
            return dp[r][c1][c2] = res;
        else
        {
            int maxval = -1;
            for (int dy1 : dirs)
            {
                for (int dy2 : dirs)
                    maxval = max(maxval, calc(r + 1, c1 + dy1, c2 + dy2));
            }
            res += maxval;
            return dp[r][c1][c2] = res;
        }
        
    }
};
```