## [leetcode] 周赛 212

🏆 比赛题目：https://leetcode-cn.com/circle/discuss/QFRzuS/。

## 按键持续时间最长的键

题目：[5546. 按键持续时间最长的键](https://leetcode-cn.com/problems/slowest-key/)。

时间不累加。

```cpp
class Solution {
public:
    char slowestKey(vector<int>& times, string keys) {
        int n = keys.length();
        char c = keys[0];
        int t = times[0];
        for (int i=1; i<n; i++)
        {
            int t2 = times[i] - times[i-1];
            if (t2 > t || (t2 == t && keys[i] > c)) t=t2, c=keys[i];
        }
        return c;
    }
};
```

## 等差子数组

题目：[5547. 等差子数组](https://leetcode-cn.com/problems/arithmetic-subarrays/)。

问就是暴力排序。

```cpp
class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) 
    {
        int m = l.size(), n = nums.size();
        vector<bool> ans(m, false);
        for (int i=0; i<m; i++)
            ans[i] = check(nums, l[i], r[i]);
        return ans;
    }
    bool check(vector<int> &v, int l, int r)
    {
        assert(l <= r);
        if (l == r) return true;
        vector<int> buf(v.begin()+l, v.begin()+r+1);
        sort(buf.begin(), buf.end());
        int d = buf[1] - buf[0];
        int size = buf.size();
        for (int i=1; i<size; i++)
            if (buf[i] - buf[i-1] != d)
                return false;
        return true;
    }
};
```

## 最小体力消耗路径

题目：[5548. 最小体力消耗路径](https://leetcode-cn.com/problems/path-with-minimum-effort/)。

第一直觉是 DFS 枚举每一个路径，记录每个路径的最大差值，然后取最小值。

剪枝：如果某一步的差值大于已找到的 `ans` ，那么停止搜索。

但是超时了。

这是一类找到「若干最大值中的最小值」的问题。

结合 BFS 和二分查找。

对每一个可能的阈值 `m` 进行二分查找，从当前位置走到下一位置的条件是 2 位置**高度之差小于等于该阈值**，按照这样的要求使用 BFS 搜索，如果可以走到 `(rows-1, cols-1)` 说明阈值可更小，所以 `r=m`，否则 `l=m+1`。

当然，还有并查集和最短路的[解法](https://leetcode-cn.com/problems/path-with-minimum-effort/solution/zui-xiao-ti-li-xiao-hao-lu-jing-by-zerotrac2/)。只能说 [zerotrac 🌸](https://leetcode-cn.com/u/zerotrac2/) 牛逼！

### BFS 和 二分查找

```cpp
class Solution {
public:
    int rows = -1, cols = -1;
    const vector<vector<int>> dir = {{-1,0}, {0,-1}, {1,0}, {0,1}};
    int minimumEffortPath(vector<vector<int>>& heights) 
    {
        rows = heights.size();
        cols = heights[0].size();
        int l=0, r=(int)1e6;
        while (l<=r)
        {
            if (l == r) break;
            int m = l + (r-l)/2;
            if (bfs(heights, m)) r = m;
            else l = m+1;
        }
        return l;
    }
    bool bfs(vector<vector<int>> &v, int val)
    {
        queue<pair<int,int>> q;
        vector<vector<bool>> vis(rows, vector<bool>(cols, false));
        q.push({0, 0});
        while (!q.empty())
        {
            auto [i,j] = q.front();
            q.pop();
            if (i == rows-1 && j == cols-1) return true;
            for (auto &d: dir)
            {
                int x = i+d[0], y = j+d[1];
                if (x < 0 || y < 0 || x >= rows || y >= cols || vis[x][y]) continue;
                if (abs(v[i][j] - v[x][y]) <= val) q.push({x,y}), vis[x][y] = 1;
            }
        }
        return false;
    }
};
```

### 并查集

定义每个格子为一个点，相邻格子的高度之差为边的权值。

通过优先队列，使得边从小到大排序，依次加入并查集，直到 `(0,0)` 和 `(rows-1, cols-1)` 相连。在加入并查集的边中的最小值，就是答案。

```cpp
class Edge 
{
public:
    int x, y, val;
    Edge(int xx, int yy, int vv) : x(xx), y(yy), val(vv) {}
    // 让堆顶是最小的边
    bool operator < (const Edge &e) const { return val > e.val; }
};
class Solution {
public:
    vector<int> root;
    int minimumEffortPath(vector<vector<int>>& heights) 
    {
        int rows = heights.size();
        int cols = heights[0].size();
        int total = rows * cols;
        root.resize(total, -1);
        priority_queue<Edge> q;
        for (int i=0; i<rows; i++)
        {
            for (int j=0; j<cols; j++)
            {
                int id = i*cols+j;
                if (i+1 < rows) q.push(Edge(id, id+cols, abs(heights[i][j] - heights[i+1][j])));
                if (j+1 < cols) q.push(Edge(id, id+1, abs(heights[i][j] - heights[i][j+1])));
            }
        }
        while (!q.empty())
        {
            auto e = q.top();
            q.pop();
            merge(e.x, e.y);
            if (find(0) == find(total-1)) return e.val;
        }
        return 0;
    }
    int find(int x) { return root[x] == -1 ? (x) : (root[x] = find(root[x])); }
    void merge(int x, int y)
    {
        int a = find(x), b = find(y);
        if (a != b) root[b] = a;
    }
};
```

最后一题是[矩阵转换后的秩](https://leetcode-cn.com/problems/rank-transform-of-a-matrix/)，看懂就算了。

