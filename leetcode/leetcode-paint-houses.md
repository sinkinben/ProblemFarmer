## Paint House

Problems:

- [256. Paint House](https://leetcode-cn.com/problems/paint-house)
- [265. Paint House II](https://leetcode-cn.com/problems/paint-house-ii)
- [1473. Paint House III](https://leetcode-cn.com/problems/paint-house-iii)



## Paint House

**Description**

There is a **row** of `n` houses, where each house can be painted one of three colors: red, blue, or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by an `n x 3` cost matrix costs.

For example, `costs[0][0]` is the cost of painting house 0 with the color red; `costs[1][2]` is the cost of painting house 1 with color green, and so on...

Return the minimum cost to paint all houses.

Constraints: `costs.length == n, costs[i].length == 3, 1 <= n <= 100, 1 <= costs[i][j] <= 20` .

**Example 1**

```text
Input: costs = [[17,2,17],[16,16,5],[14,3,19]]
Output: 10
Explanation: Paint house 0 into blue, paint house 1 into green, paint house 2 into blue.
Minimum cost: 2 + 5 + 3 = 10.
```

**Example 2**

```
Input: costs = [[7,6,2]]
Output: 2
```

<br/>

**Solution**

The shape of houses is a **ROW**, not a graph, hence the problem here is not 3-Coloring Problem (which is NPC). We can solve this problem by dynamic programming.

Let `dp0[i]` denote the min cost when the `house[i]` is red, `dp1[i]` denote the min cost when the `house[i]` is green, so does `dp2[i]`.

State equations:

```text
dp0[i] = cost[i][0] + min(dp1[i - 1][1], dp2[i - 1][2])
dp1[i] = cost[i][1] + min(dp1[i - 1][0], dp2[i - 1][2])
dp2[i] = cost[i][2] + min(dp1[i - 1][0], dp2[i - 1][1])
```

Here is the code.

```cpp
class Solution 
{
public:
    typedef enum {RED = 0, GREEN = 1, BLUE = 2} color_t;
    const int NR_COLOR = 3;
    int minCost(vector<vector<int>>& costs) 
    {
        int n = costs.size();
        vector<vector<int>> dp(n, vector<int>(NR_COLOR, 0));
        dp[0] = costs[0];
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < NR_COLOR; ++j)
                dp[i][j] = cost[i][j] + 
                           min(dp[i - 1][(j + 1) % NR_COLOR], dp[i - 1][(j + 2) % NR_COLOR]);
        }
        return min(dp[n - 1][0], min(dp[n - 1][1], dp[n - 1][2]));
    }
};
```



## Paint House II

**Description**

There are a **row** of `n` houses, each house can be painted with one of the `k` colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by an `n x k` cost matrix costs.

For example, `costs[0][0]` is the cost of painting house 0 with color 0; `costs[1][2]` is the cost of painting house 1 with color 2, and so on...

Return the minimum cost to paint all houses.

Constraints: `costs.length == n, costs[i].length == k, 1 <= n <= 100, 2 <= k <= 20, 1 <= costs[i][j] <= 20` .

Follow up: Could you solve it in `O(nk)` runtime?

**Example 1**

```
Input: costs = [[1,5,3],[2,9,4]]
Output: 5
Explanation:
Paint house 0 into color 0, paint house 1 into color 2. Minimum cost: 1 + 4 = 5; 
Or paint house 0 into color 2, paint house 1 into color 0. Minimum cost: 3 + 2 = 5.
```

**Example 2**

```
Input: costs = [[1,3],[2,4]]
Output: 5
```

<br/>

**Solution**

Let `dp[i][k]` denote the min cost when `house[i]` is with `color[k]`. Then the state equation is:

```text
dp[i][j] = costs[i][j] + min(dp[i - 1][t]) where 0 <= t < k and t != j
```

Time complexity is $O(nk^2)$ .

Here is the code.

```cpp
class Solution 
{
public:
    int minCostII(vector<vector<int>>& costs) 
    {
        if (costs.size() == 0 || costs[0].size() == 0) return 0;
        int n = costs.size(), k = costs[0].size();
        vector<vector<int>> dp(n, vector<int>(k, 0));
        dp[0] = costs[0];
        for (int i = 1; i < n; ++i)
            for (int j = 0; j < k; ++j)
                dp[i][j] = costs[i][j] + getMin(dp[i - 1], j);
        return getMin(dp[n - 1], -1);
    }
    
    int getMin(vector<int> &vec, int skip)
    {
        int n = vec.size(), res = INT_MAX;
        for (int i = 0; i < n; ++i)
        {
            if (i == skip) continue;
            res = min(res, vec[i]);
        }
        return res;
    }
};
```

How about the $O(nk)$ solution?

When we fill the row `dp[i]`, we need to know the min value of `dp[i - 1]` (but need to skip one element `dp[i - 1, j]` ).

Here we use `min1, min2` to record the first min value and the second min value of each row.

We should skip `dp[i - 1, j]` if and only if `do[i - 1, j]` is the first min value.

```cpp
class Solution 
{
public:
    int minCostII(vector<vector<int>>& costs) 
    {
        if (costs.size() == 0 || costs[0].size() == 0) return 0;
        int n = costs.size(), k = costs[0].size();
        vector<vector<int>> dp(n, vector<int>(k, 0));
        dp[0] = costs[0];
        auto [min1, min2] = getMinPair(dp[0]);
        for (int i = 1; i < n; ++i)
        {
            int curMin1 = INT_MAX, curMin2 = INT_MAX;
            for (int j = 0; j < k; ++j)
            {
                dp[i][j] = costs[i][j] + (dp[i - 1][j] == min1 ? min2 : min1);
                if (dp[i][j] < curMin1)
                    curMin2 = curMin1, curMin1 = dp[i][j];
                else if (dp[i][j] < curMin2)
                    curMin2 = dp[i][j];
            }
            min1 = curMin1, min2 = curMin2;
        }
        return min1;
    }
    
    // <first min val, second min val>
    pair<int, int> getMinPair(vector<int> &vec)
    {
        int min1 = INT_MAX, min2 = INT_MAX;
        for (int x : vec)
        {
            if (x < min1) min2 = min1, min1 = x;
            else if (x < min2) min2 = x;
        }
        return {min1, min2};
    }
};
```



## Paint House III

There is a row of `m` houses in a small city, each house must be painted with one of the `n` colors (labeled from `1` to `n`), some houses that have been painted last summer should not be painted again.

A neighborhood is a maximal group of continuous houses that are painted with the same color.

- For example: `houses = [1,2,2,3,3,2,1,1]` contains `5` neighborhoods `[{1}, {2,2}, {3,3}, {2}, {1,1}]`.

Given an array `houses`, an `m x n` matrix `cost` and an integer `target` where:

- `houses[i]`: is the color of the house `i`, and `0` if the house is not painted yet.
- `cost[i][j]`: is the cost of paint the house `i` with the color `j + 1`.

Return *the minimum cost of painting all the remaining houses in such a way that there are exactly* `target` *neighborhoods*. If it is not possible, return `-1`.

**Example 1:**

```
Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
Output: 9
Explanation: Paint houses of this way [1,2,2,1,1]
This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
```

**Example 2:**

```
Input: houses = [0,2,1,2,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
Output: 11
Explanation: Some houses are already painted, Paint the houses of this way [2,2,1,2,2]
This array contains target = 3 neighborhoods, [{2,2}, {1}, {2,2}]. 
Cost of paint the first and last house (10 + 1) = 11.
```

**Example 3:**

```
Input: houses = [3,1,2,3], cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]], m = 4, n = 3, target = 3
Output: -1
Explanation: Houses are already painted with a total of 4 neighborhoods [{3},{1},{2},{3}] different of target = 3. 
```

**Constraints:**

- `m == houses.length == cost.length`
- `n == cost[i].length`
- `1 <= m <= 100`
- `1 <= n <= 20`
- `1 <= target <= m`
- `0 <= houses[i] <= n`
- `1 <= cost[i][j] <= 10^4`

<br/>

**Solution**

Define `dp[i, j, k]` as the minimum cost where we have `k` neighborhoods in the first `i` houses and the `i`-th house is painted with the color `j`.

For 3-Dimension DP, we usually bottom-to-up (recursion) strategy to fill the array.

Here is the code.

```cpp
typedef vector<int> vec_t;
typedef vector<vec_t> vec2_t;
typedef vector<vec2_t> vec3_t;
class Solution 
{
public:
    vec3_t dp;
    int m, n;
    const int INF = 0x3f3f3f3f, INVALID_COLOR = 0;
    int minCost(vec_t &houses, vec2_t &cost, int m, int n, int target) 
    {
        dp.resize(m, vec2_t(n + 1, vec_t(target + 1, -1)));
        this->m = m, this->n = n;
        int res = compute(houses, cost, 0, INVALID_COLOR, target);
        return res >= INF ? -1 : res;
    }
    
    /* Define compute(i, j, k) to compute the value of dp[i, j, k], which is bottom-to-up DP.
     * i - current house we need to paint
     * j - previous color we used
     * k - target number of neighborhood groups
     */
    int compute(vec_t &houses, vec2_t &cost, int i, int j, int k)
    {
        // assert(0 <= j && j <= n);
        if (k < 0)  return INF;
        if (i >= m) return k == 0 ? 0 : INF;
        if (houses[i] != 0)
            return compute(houses, cost, i + 1, houses[i], k - (houses[i] != j));
		if (dp[i][j][k] != -1)
            return dp[i][j][k];
        int res = INF;
        for (int c = 0; c < n; ++c)
        {
            int color = c + 1;
            res = min(res, cost[i][c] + compute(houses, cost, i + 1, color, k - (color != j)));
        }
        return dp[i][j][k] = res;
    }
};
```

