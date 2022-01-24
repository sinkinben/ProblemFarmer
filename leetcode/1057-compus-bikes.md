## Compus Bikes

On a campus represented on the X-Y plane, there are `n` workers and `m` bikes, with `n <= m`.

You are given an array workers of length `n` where `workers[i] = [xi, yi]` is the position of the `i`-th worker. You are also given an array bikes of length `m` where `bikes[j] = [xj, yj]` is the position of the `j`-th bike. All the given positions are **unique**.

Assign a bike to each worker. Among the available bikes and workers, we choose the `(workeri, bikej)` pair with the shortest Manhattan distance between each other and assign the bike to that worker.

If there are multiple `(workeri, bikej)` pairs with the same shortest Manhattan distance, we choose the pair with the **smallest worker index**. If there are multiple ways to do that, we choose the pair with the smallest bike index. Repeat this process until there are no available workers.

Return an array answer of length `n`, where `answer[i]` is the index (0-indexed) of the bike that the `i`-th worker is assigned to.

The Manhattan distance between two points `p1` and `p2` is `Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|`.

**Example 1**

<img src="https://assets.leetcode.com/uploads/2019/03/06/1261_example_1_v2.png" />

```
Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
Output: [1,0]
Explanation: Worker 1 grabs Bike 0 as they are closest (without ties), and Worker 0 is assigned Bike 1. So the output is [1, 0].
```

**Example 2**

<img src="https://assets.leetcode.com/uploads/2019/03/06/1261_example_2_v2.png" />

```
Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
Output: [0,2,1]
Explanation: Worker 0 grabs Bike 0 at first. Worker 1 and Worker 2 share the same distance to Bike 2, thus Worker 1 is assigned to Bike 2, and Worker 2 will take Bike 1. So the output is [0,2,1].
```

**Constraints**

- `n == workers.length`
- `m == bikes.length`
- `1 <= n <= m <= 1000`
- `workers[i].length == bikes[j].length == 2`
- `0 <= xi, yi < 1000`
- `0 <= xj, yj < 1000`
- All worker and bike locations are **unique**.

<br/>

**Solution**

Greedy algorithm.

- We aggreate all `<worker, bike>` pairs according to their distance, and put them in `map<uint, vector<pair>>`. And the `map` is auto-sorted.
- Scan the `map`, we can get `<worker, bike>` pairs from smaller-distance to larger-distance.
- If `<worker, pair>` has not been used (both of them are not used), then we can set `res[worker] = bike`.

Since we use `map`, the time complexity is $O(mn \log{mn})$.

```cpp
typedef pair<int, int> pair_t;
class Solution
{
public:
    uint32_t dis(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }
    
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) 
    {
        int n = workers.size(), m = bikes.size();
        // sort all the pairs according to their distances
        map<uint32_t, vector<pair_t>> map;
        for (int i = 0; i < n; ++i)
        {
            auto &w = workers[i];
            for (int j = 0; j < m; ++j)
            {
                auto &b = bikes[j];
                map[dis(w[0], w[1], b[0], b[1])].emplace_back(i, j);
            }
        }
        vector<int> res(n, -1);
        vector<bool> bikeUsed(m, false);
        for (auto &[d, vec] : map)
        {
            for (auto [worker, bike] : vec)
            {
                if (res[worker] == -1 && !bikeUsed[bike])
                    res[worker] = bike, bikeUsed[bike] = 1;
            }
        }
        return res;
    }
};
```

Since `0 <= xi, yi < 1000`, we can know that the max distance is 2000. Therefore, we can use hash-table to replace `map`.

```cpp
typedef pair<int, int> pair_t;
class Solution
{
public:
    const int MAX_DIS = 2000;
    
    uint32_t dis(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }
    
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) 
    {
        int n = workers.size(), m = bikes.size();
        // sort all the pairs according to their distances
        vector<vector<pair_t>> table(MAX_DIS);
        for (int i = 0; i < n; ++i)
        {
            auto &w = workers[i];
            for (int j = 0; j < m; ++j)
            {
                auto &b = bikes[j];
                table[dis(w[0], w[1], b[0], b[1])].emplace_back(i, j);
            }
        }
        vector<int> res(n, -1);
        vector<bool> bikeUsed(m, false);
        for (auto &vec : table)
        {
            for (auto [worker, bike] : vec)
            {
                if (res[worker] == -1 && !bikeUsed[bike])
                    res[worker] = bike, bikeUsed[bike] = 1;
            }
        }
        return res;
    }
};
```

