## 688. Knight Probability in Chessboard

Link: https://leetcode.com/problems/knight-probability-in-chessboard/

On an `n x n` chessboard, a knight starts at the cell `(row, column)` and attempts to make exactly `k` moves. The rows and columns are **0-indexed**, so the top-left cell is `(0, 0)`, and the bottom-right cell is `(n - 1, n - 1)`.

A chess knight has eight possible moves it can make, as illustrated below. Each move is two cells in a cardinal direction, then one cell in an orthogonal direction.

<img src="https://assets.leetcode.com/uploads/2018/10/12/knight.png"/>

Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly `k` moves or has moved off the chessboard.

Return *the probability that the knight remains on the board after it has stopped moving*.

 

**Example 1:**

```
Input: n = 3, k = 2, row = 0, column = 0
Output: 0.06250
Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.
```

**Example 2:**

```
Input: n = 1, k = 0, row = 0, column = 0
Output: 1.00000
```

 

**Constraints:**

- `1 <= n <= 25`
- `0 <= k <= 100`
- `0 <= row, column <= n - 1`

<br/>

**Solution**

Let `dp[s, i, j]` denote the probability that the knight starts at position `(i, j)` and remains in chessboard at `s`-th step. Then we can have:

- If `s = 0`, then for any valid `0 <= i, j < n`, `dp[0, i, j] = 1` denotes that the knight "stays" at `(i, j)` and has done nothing.

- Otherwise,
  $$
  dp[s, i, j] = \frac{1}{8} \sum_{(i, j) \in pos}dp[s-1, i, j]
  $$
  where $pos$ denotes the 8 possible moved positions.

```cpp
using pair_t = pair<int, int>;
using vec = vector<double>;
using vec2 = vector<vec>;
using vec3 = vector<vec2>;
class Solution
{
public:
    double knightProbability(int n, int k, int row, int column)
    {
        vec3 dp(k + 1, vec2(n, vec(n, 0)));
        vector<pair_t> dirs = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},
                               {1, -2}, {2, -1}, {2, 1}, {1, 2}};
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dp[0][i][j] = 1;
        
        auto valid = [=](int x, int y) { return 0 <= x && x < n && 0 <= y && y < n; };
        for (int s = 1; s <= k; ++s)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    for (auto [dx, dy]: dirs)
                    {
                        int x = i + dx, y = j + dy;
                        if (valid(x, y))
                            dp[s][i][j] += dp[s - 1][x][y] / 8;
                    }
                }
            }
        }
        return dp[k][row][column];
    }
};
```

