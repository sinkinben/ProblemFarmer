## Trapping Rain Water

- [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
- [407. Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/)





## Trapping Rain Water

Leetcode: https://leetcode.com/problems/trapping-rain-water/

**Dynamic Programming**

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size(), sum = 0;
        // lmax[i] denote the max-value in range of height[0, ..., i-1]
        // rmax[i] denote the max-value in range of height[i+1, ..., n]
        vector<int> lmax(n, 0), rmax(n, 0);
        
        for (int i = 1; i < n; ++i)
            lmax[i] = max(lmax[i - 1], height[i - 1]);
        for (int i = n - 2; i >= 0; --i)
            rmax[i] = max(rmax[i + 1], height[i + 1]);
        
        for (int i = 1; i < n; ++i) {
            int h = min(lmax[i], rmax[i]);
            if (h > height[i])
                sum += h - height[i];
        }
        return sum;
    }
};
```

<br/>

**Double Pointers**

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int l = 0, r = n - 1;
        int res = 0, lmax = 0, rmax = 0;
        while (l <= r)
        {
            lmax = max(height[l], lmax);
            rmax = max(height[r], rmax);
            if (lmax >= rmax)
                res += rmax - height[r], r -= 1;
            else
                res += lmax - height[l], l += 1;
        }
        return res;
    }
};
```





## Trapping Rain Water II

Leetcode: https://leetcode.com/problems/trapping-rain-water-ii/

Refer to [this solution](https://leetcode-cn.com/problems/trapping-rain-water-ii/solution/jie-yu-shui-ii-by-leetcode-solution-vlj3/).

**Min-Heap**

It's a little similar to multiple sources BFS.

- For each position `(i, j)`, its capacity depends on the **min-heights** of 4 position around it.
- Therefore, we use a min-heap to maintain the nodes `{height, position-id}`.
- During each computation of loop, we pop a element from the min-heap, and check its 4 adjacent cells.

Time complexity is $O(mn \log{mn})$ .

```cpp
// p.first is height, p.second is id
typedef pair<int, int> node_t;
class Solution
{
public:
    int trapRainWater(vector<vector<int>>& height)
    {
        if (height.size() <= 2 || height[0].size() <= 2)
            return 0;

        int m = height.size(), n = height[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, 0));
        priority_queue<node_t, vector<node_t>, std::greater<node_t>> que;

        auto getid = [n](int i, int j) { return i * n + j; };
        
        for (int i = 0; i < m; ++i)
        {
            int inc = (i == 0 || i == m - 1) ? 1 : (n - 1);
            for (int j = 0; j < n; j += inc)
                que.emplace(height[i][j], getid(i, j)), visited[i][j] = 1;
        }
        
        static const vector<pair<int, int>> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        auto validIndex = [m, n](int x, int y) {
            return 0 <= x && x < m && 0 <= y && y < n;
        };
        int res = 0;
        while (!que.empty())
        {
            auto [cur, id] = que.top();
            que.pop();
            int x = id / n, y = id % n;
            for (auto [dx, dy] : dirs)
            {
                int nx = x + dx, ny = y + dy;
                if (!validIndex(nx, ny) || visited[nx][ny])
                    continue;
                if (cur > height[nx][ny])
                    res += cur - height[nx][ny];
                que.emplace(max(cur, height[nx][ny]), getid(nx, ny));
                visited[nx][ny] = 1;
            }
        }
        return res;
    }
};
```

