## Bit Mask DP

Bitmask DP on Leetcode:

- [698. Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/)
  - See `leetcode-k-partition-equal-sum.md`
- [1723. Find Minimum Time to Finish All Jobs](https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs/)
  - See `1723-min-time-finish-jobs.md`
- [2035. Partition Array Into Two Arrays to Minimize Sum Difference](https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/)
  - See `2035.md`
- [1755. Closest Subsequence Sum](https://leetcode.com/problems/closest-subsequence-sum/)
  - See `1755.md`
- [1494. Parallel Courses II](https://leetcode-cn.com/problems/parallel-courses-ii/)
  - See `leetcode-parallel-courses.md`.
- [1239. Maximum Length of a Concatenated String with Unique Characters](https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/)
  - See `1239-max-length-concat-string.md`




## TSP

参考: https://www.cnblogs.com/sinkinben/p/14264235.html

题目：[毕业旅行问题](https://www.nowcoder.com/questionTerminal/3d1adf0f16474c90b27a9954b71d125d?answerType=1&f=discussion)

考虑使用状态压缩的动态规划解决。

- 令 $dp[s,v]$ 中，$s$ 表示没去过的城市集合，$v$ 表示当前所在城市。因此，$dp[0,0]$ 表示所有城市去过，并在所在地为 0 城市，即结束状态；$dp[2^n-1, 0]$ 表示所有城市都没去过，当前在 0 号城市，即开始状态。
- 定义 `is_visited(s, u)` 为集合 `s` 是否包含了城市 `u`, 即当前状态是否已经访问过 `u` .
- 定义 `set_zero(s, k)` 把 `s` 的从左往右数的第 `k` 比特置为 0 ，表示城市 `k` 已访问。

时间复杂度 $O(n^2\cdot2^n)$，空间复杂度 $O(n \cdot 2^n)$ .

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 21;
/* 任意不同的城市 (i, j) 联通, graph[i][i] = 0. */
int graph[N][N] = {{0}};
int tsp(int n)
{
    vector<vector<int>> dp((1 << n), vector<int>(n, 0x3f3f3f3f));
    auto is_visited = [](int s, int u) { return ((s >> u) & 1) == 0; };
    auto set_zero = [](int s, int k) { return (s & (~(1 << k))); };
    dp[(1 << n) - 1][0] = 0;
    // double 'for' loop to fill the dp
    for (int s = (1 << n) - 1; s >= 0; s--)
    {
        // we are at city 'v' now
        for (int v = 0; v < n; v++)
        {
            // for current 's', try all the cities
            for (int u = 0; u < n; u++)
            {
                if (!is_visited(s, u))  // if 'u' has not been visited
                {
                    int state = set_zero(s, u);
                    dp[state][u] = min(dp[state][u], dp[s][v] + graph[v][u]);
                }
            }
        }
    }
    return dp[0][0];
}
int main()
{
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];
        cin.ignore();
    }
    cout << tsp(n) << endl;
}
```