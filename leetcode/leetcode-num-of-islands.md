## Number of Islands

Problems:

- [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)
- [305. Number of Islands II](https://leetcode-cn.com/problems/number-of-islands-ii/)
- [694. Number of Distinct Islands](https://leetcode-cn.com/problems/number-of-distinct-islands/)
- [711. Number of Distinct Islands II](https://leetcode-cn.com/problems/number-of-distinct-islands-ii/)



## Num of Islands

Here we will show two solutions for this problem, disjoint set (union find) and DFS.

<br/>

**1. Union Find (Disjoint Set)**

+ Regrad each cell in `grid` as a node in a graph. For each `grid[i, j]`, name it with id `i * n + j`.
+ For `grid[i, j] = 1`, connect it with cells on its right and bottom (if they were `1`-cell, too).
+ For `grid[i, j] = 0`, connect it with a special id `water = m * n`.
+ Finally, we should return the number of connected-components in the graph, and minus one.

Time complexity is $O(mn + mn \cdot \log{mn})$.

```cpp
class Solution {
public:
    vector<int> root;
    
    int find(int x) { return root[x] == -1 ? x : root[x] = find(root[x]); }
    
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y) root[y] = x;
    }
    
    int numIslands(vector<vector<char>>& grid) 
    {
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;
        
        int m = grid.size(), n = grid[0].size();
        int water = m * n;
        root.resize(water + 1, -1);
        
        auto getId = [n](int i, int j) { return i * n + j; };
        
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int id = getId(i, j);
                if (grid[i][j] == '0')
                    merge(id, water);
                else
                {
                    if (i + 1 < m && grid[i + 1][j] == '1') merge(id, getId(i + 1, j));
                    if (j + 1 < n && grid[i][j + 1] == '1') merge(id, getId(i, j + 1));
                }
            }
        }
        return count(root.begin(), root.end(), -1) - 1;
    }
};
```

<br/>

**2. DFS**

This solution is much faster than above. It will cost $O(mn)$ time and $O(mn)$ space.

```cpp
class Solution {
public:
    int m, n;
    int numIslands(vector<vector<char>>& grid) 
    {
        if (grid.size() == 0 || grid[0].size() == 0) return 0;
        m = grid.size(), n = grid[0].size();
        int res = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                res += dfs(grid, i, j);
        return res;
    }
    
    bool dfs(vector<vector<char>>& grid, int x, int y)
    {
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != '1')
            return false;
        grid[x][y] = '2';
        dfs(grid, x + 1, y), dfs(grid, x - 1, y);
        dfs(grid, x, y + 1), dfs(grid, x, y - 1);
        return true;
    }
};
```



## Num of Islands II

**Description**

You are given an empty 2D binary grid grid of size `m x n`. The grid represents a map where 0's represent water and 1's represent land. Initially, all the cells of grid are water cells (i.e., all the cells are 0's).

We may perform an add land operation which turns the water at position into a land. You are given an array positions where `positions[i] = [ri, ci]` is the position `(ri, ci)` at which we should operate the ith operation.

Return an array of integers answer where `answer[i]` is the number of islands after turning the cell `(ri, ci)` into a land.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

<img src="https://assets.leetcode.com/uploads/2021/03/10/tmp-grid.jpg" style="width: 60%"/>

**Solution**

Here we will use disjoint set (union find) to solve this problem.

- For each cell `(r, c)`, we name it by an unique id `r * n + c`, where `n` is the number of columns of this grid.
- `root[x] == -1` represents `x` is a single node, but it can not express whether if `x` is land or water field. Hence we use `unordered_set<int> land` to stored the ids of cells that marked as land.
- The `cnt` denote the number of islands at present.
- Scan the `positions` array, for each `pos = (x, y)`, add it to `land`, and let `cnt += 1`. If the `pos` could be merged with other land (marked before), merged them and minus one from `cnt`.

```cpp
class Solution 
{
public:
    int find(vector<int> &root, int x) { return root[x] == -1 ? x : root[x] = find(root, root[x]); }

    bool merge(vector<int> &root, int x, int y)
    {
        x = find(root, x), y = find(root, y);
        if (x == y) return false;
        else
        {
            root[y] = x;
            return true;
        }
    }

    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) 
    {
        int k = positions.size();
        vector<int> res(k, 0);
        vector<int> root(m * n, -1);

        auto getId = [n](int i, int j) { return i * n + j; };
        auto validIndex = [m, n](int i, int j) { return 0 <= i && i < m && 0 <= j && j < n; };
        static const vector<pair<int,int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        // record the all the ids of land
        unordered_set<int> land;
        int cnt = 0;
        for (int i = 0; i < k; ++i)
        {
            int x = positions[i][0], y = positions[i][1];
            int id = getId(x, y);
            if (land.count(id)) 
            {
                res[i] = cnt;
                continue;
            }
            land.emplace(id), cnt += 1;
            for (auto [dx, dy] : dirs)
            {
                int x2 = x + dx, y2 = y + dy;
                int id2 = getId(x2, y2);
                if (validIndex(x2, y2) && land.count(id2) && merge(root, id, id2))
                    cnt -= 1;
            }
            res[i] = cnt;
        }

        return res;
    }
};
```

Here I use disjoint set (union find) with compressed-path, each operation will cost $O(\log{mn})$ time, where $mn$ denote the total number of edges in the graph.

Therefore, the total time complexity here is $O(k\log{mn})$ .



## Num of Distinct Islands

**Description**

You are given an `m x n` binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

An island is considered to be the same as another if and only if one island can be translated (and not rotated or reflected) to equal the other.

Return the number of distinct islands. `0 <= m, n <= 50` .

<br/>

**Example - 1**

<img src="https://assets.leetcode.com/uploads/2021/05/01/distinctisland1-1-grid.jpg" />

```text
Input: grid = [[1,1,0,0,0],[1,1,0,0,0],[0,0,0,1,1],[0,0,0,1,1]]
Output: 1
```

<br/>

**Example - 2**

<img src="https://assets.leetcode.com/uploads/2021/05/01/distinctisland1-2-grid.jpg" />

```text
Input: grid = [[1,1,0,1,1],[1,0,0,0,0],[0,0,0,0,1],[1,1,0,1,1]]
Output: 3
```

<br/>

**Solution**

The key point of this problem is that: how can we denote the translated islands in a same value?

And this demand us to design a hash function, map the translated islands into a same value.

- Remind the problem "200. Num of Islands", we use DFS to find a island each time. **In each DFS, we can also get a path, and such path for each island is unique.** 
- Such path could be represent by a position sequence like `(x1, y1) -> (x2, y2) -> ...`, and we can store this position sequence in a `vector`.
- Now, the question is: for the same class of translated islands, how can we map their position sequence into a same value?
- A solution is that, regard the start-points of DFS `(x1, y1)` as origin coordinate `(0, 0)` , and the following positions `(xi, yi)` become `(xi - x1, yi - y1)`.

```cpp
typedef pair<int, int> pos_t;
class Solution 
{
public:
    int m, n;
    int numDistinctIslands(vector<vector<int>>& grid) 
    {
        if (grid.size() == 0 || grid[0].size() == 0) return 0;
        m = grid.size(), n = grid[0].size();
        set<vector<pos_t>> islands;
        vector<pos_t> path;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                path.clear();
                dfs(grid, {i, j}, {i, j}, path);
                // ignore if we start dfs at grid[i, j] = 0 or -1
                if (!path.empty())
                    islands.emplace(path);
            }
        }
        return islands.size();
    }
    
    bool validIndex(int x, int y) { return 0 <= x && x < m && 0 <= y && y < n; }
    
    void dfs(vector<vector<int>>& grid, pos_t origin, pos_t cur, vector<pos_t> &path)
    {
        static const vector<pos_t> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        auto [x, y] = cur;
        if (!validIndex(x, y) || grid[x][y] <= 0) return;
        grid[x][y] = -1;
        // path += to_string(x - origin.first) + " " + to_string(y - origin.second) + " ";
        path.emplace_back(x - origin.first, y - origin.second);
        for (auto [dx, dy] : dirs)
            dfs(grid, origin, {x + dx, y + dy}, path);
    }
};

```



Here we use `set<vector<pos_t>>` to remove the duplicate paths, and it will cost $O(\log{k})$ time for each `emplace` operation, where $k$ is the number of paths (islands). Total time complexity is $O(mn \log{k})$

If we store a path by a string, then we can use `unordered_set<string>` to remove the duplicate paths. Time complexity can be optimized to $O(mn)$.



## Num of Distinct Islands II

**Description**

You are given an `m x n` binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

An island is considered to be the same as another if they have the **same shape**, or have the **same shape after rotation** (90, 180, or 270 degrees only) or **reflection** (left/right direction or up/down direction).

Return the number of distinct islands. `1 <= m, n <= 50` .

<br/>

**Example**

<img src="https://assets.leetcode.com/uploads/2021/05/01/distinctisland2-1-grid.jpg" />

```text
Input: grid = [[1,1,0,0,0],[1,0,0,0,0],[0,0,0,0,1],[0,0,0,1,1]]
Output: 1
Explanation: The two islands are considered the same because if we make a 180 degrees clockwise rotation on the first island, then two islands will have the same shapes.
```

<br/>

**Solution**

- For a cell `(x, y)` in the grid (suppose it was in first quadrant), 

  - after only rotations, it could be `(y, -x), (-x, -y), (-y, x), (x, y)`, and 

  - after only reflections, it could be `(-x, y), (x, -y), (-x, -y), (x, y)`, and

  - after the combination of rotations and reflections, it totally has 8 different cases

    ```text
    (x,  y)  (x,  -y)
    (-x, y)  (-x, -y)
    (y,  x)  (y,  -x)
    (-y, x)  (-y, -x)
    ```

- This means, for each path (a path uniquely represents an island), there are another 7 paths (islands) with the same shapes.

- Based on "694. Num of Distinct Islands", now we need to design a new hash function, and such hash-function will map the 8 paths above into same value.

- **We can sort the 8 paths, and select the max one (or small one).**

Here is the code.


```cpp
typedef pair<int, int> pos_t;
class Solution 
{
public:
    int m, n;
    int numDistinctIslands2(vector<vector<int>>& grid) 
    {
        if (grid.size() == 0 || grid[0].size() == 0) return 0;
        m = grid.size(), n = grid[0].size();
        set<vector<pos_t>> islands;
        vector<pos_t> path;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                path.clear();
                dfs(grid, {i, j}, path);
                // ignore if we start dfs at grid[i, j] = 0 or -1
                if (!path.empty())
                    islands.emplace(hashPath(path));
            }
        }
        return islands.size();
    }
    
    bool validIndex(int x, int y) { return 0 <= x && x < m && 0 <= y && y < n; }
    
    void dfs(vector<vector<int>>& grid, pos_t cur, vector<pos_t> &path)
    {
        static const vector<pos_t> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        auto [x, y] = cur;
        if (!validIndex(x, y) || grid[x][y] <= 0) return;
        grid[x][y] = -1;
        // push the absolute coordinates, not relative coordinates
        path.emplace_back(x, y);
        for (auto [dx, dy] : dirs)
            dfs(grid, {x + dx, y + dy}, path);
    }
    
    vector<pos_t> hashPath(vector<pos_t> &path)
    {        
        vector<vector<pos_t>> shapedPaths(8);
        for (auto &pos : path)
        {
            auto [x, y] = pos;
            int idx = 0;
            for (int i : {x, -x}) for (int j : {y, -y}) shapedPaths[idx++].emplace_back(i, j);
            for (int i : {y, -y}) for (int j : {x, -x}) shapedPaths[idx++].emplace_back(i, j);
        }
        for (auto &v : shapedPaths)
        {
            sort(v.begin(), v.end());
            int len = path.size();
            for (int i = len - 1; i >= 0; --i)
            {
                v[i].first -= v[0].first;
                v[i].second -= v[0].second;
            }
        }
        sort(shapedPaths.begin(), shapedPaths.end());
        return shapedPaths[0];
    }
};
```

