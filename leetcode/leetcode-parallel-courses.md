## [1136. Parallel Courses](https://leetcode-cn.com/problems/parallel-courses/)

You are given an integer `n`, which indicates that there are `n` courses labeled from `1` to `n`. You are also given an array relations where `relations[i] = [prevCoursei, nextCoursei]`, representing a prerequisite relationship between course `prevCoursei` and course `nextCoursei`: course `prevCoursei` has to be taken before course `nextCoursei`.

In one semester, you can take any number of courses as long as you have taken all the prerequisites in the previous semester for the courses you are taking.

Return the minimum number of semesters needed to take all courses. If there is no way to take all the courses, return -1.

```
Input: n = 3, relations = [[1,3],[2,3]]
Output: 2
Explanation: The figure above represents the given graph.
In the first semester, you can take courses 1 and 2.
In the second semester, you can take course 3.
```

**Solution**

Topological sorting and BFS.

```cpp
class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<int> indeg(n, 0);
        vector<vector<int>> graph(n, vector<int>());
        for (auto &v : relations)
        {
            int x = v[0] - 1, y = v[1] - 1;
            graph[x].push_back(y);
            indeg[y]++;
        }
        /* the topological sequence */
        queue<int> seq;
        for (int i = 0; i < n; ++i)
            if (indeg[i] == 0)
                seq.push(i);

        if (seq.empty()) return -1;
        int res = 0;
        while (!seq.empty())
        {
            queue<int> next;
            res++;
            while (!seq.empty())
            {
                auto remove = seq.front();
                seq.pop();
                for (int vex : graph[remove])
                {
                    indeg[vex] -= 1;
                    if (indeg[vex] == 0)
                        next.push(vex);
                }
            }
            seq = std::move(next);
        }
        /* If there is no cycle in the graph, then the `indeg` must be filled with zeros. */
        return count(begin(indeg), end(indeg), 0) == n ? res : -1;
    }
};
```





## [1494. Parallel Courses II](https://leetcode.com/problems/parallel-courses-ii/)

You are given an integer `n`, which indicates that there are `n` courses labeled from `1` to `n`. You are also given an array `relations` where `relations[i] = [prevCoursei, nextCoursei]`, representing a prerequisite relationship between course `prevCoursei` and course `nextCoursei`: course `prevCoursei` has to be taken before course `nextCoursei`. Also, you are given the integer `k`.

In one semester, you can take **at most** `k` courses as long as you have taken all the prerequisites in the **previous** semester for the courses you are taking.

Return *the **minimum** number of semesters needed to take all courses*. The testcases will be generated such that it is possible to take every course.

<img src="https://assets.leetcode.com/uploads/2020/05/22/leetcode_parallel_courses_2.png" />

```
Input: n = 5, dependencies = [[2,1],[3,1],[4,1],[1,5]], k = 2
Output: 4 
Explanation: The figure above represents the given graph.
In the first semester, you can take courses 2 and 3 only since you cannot take more than two per semester.
In the second semester, you can take course 4.
In the third semester, you can take course 1.
In the fourth semester, you can take course 5.
```

<br/>

**Solution**

Bitmask DP.

- `depend[i]` denote the courses that course `i` depends on.
- Use an 32bit-integer  `x` to denote one subset of `course[0, ..., n - 1]`.
- Let `dp[x]` denote the min-number of semesters we need, to finish subset `x`.
  - For each subset `x`, the coming courses we can take are stored in `next`.
  - Choose the max (and possible) subset from `next` to take in ONE semester.

```cpp
class Solution {
public:
    const int INF = INT_MAX / 2;
    inline int popcount(int x) { return x == 0 ? 0 : __builtin_popcount(x); }
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        if (relations.empty())
            return n / k + (n % k != 0);

        /* depend[i] denote the courses that course `i` depends on. */
        vector<int> depend(n, 0);
        for (auto &v : relations)
        {
            int x = v[0] - 1, y = v[1] - 1;
            depend[y] |= (1 << x);
        }
        
        vector<int> dp(1 << n, INF);
        dp[0] = 0;
        /* x denote the subset courses that are finished. */
        for (int x = 0; x < (1 << n); ++x)
        {
            /* in the remained courses (not finished course), `next` denote 
             * all the courses that their prerequisites are finished. 
             */
            int next = 0;
            for (int c = 0; c < n; ++c)
                if (((x >> c) & 1) == 0 && (depend[c] & x) == depend[c])
                    next |= (1 << c);

            assert((x & next) == 0);

            /* In all subsets of `next`, we can ONLY choose `sub` that satisfis 
             * popcount(sub) <= k.
             */
            for (int sub = next; sub; sub = (sub - 1) & next)
            {
                int cnt = popcount(sub);
                if (cnt <= k)
                    dp[x | sub] = min(dp[x | sub], dp[x] + 1);
            }
        }
        int res = dp.back();
        return res == INF ? -1 : res;
    }
};
```



## [2050. Parallel Courses III](https://leetcode.com/problems/parallel-courses-iii/)

You are given an integer `n`, which indicates that there are `n` courses labeled from `1` to `n`. You are also given a 2D integer array `relations` where `relations[j] = [prevCoursej, nextCoursej]` denotes that course `prevCoursej` has to be completed **before** course `nextCoursej` (prerequisite relationship). Furthermore, you are given a **0-indexed** integer array `time` where `time[i]` denotes how many **months** it takes to complete the `(i+1)-th` course.

You must find the **minimum** number of months needed to complete all the courses following these rules:

- You may start taking a course at **any time** if the prerequisites are met.
- **Any number of courses** can be taken at the **same time**.

Return *the **minimum** number of months needed to complete all the courses*.

**Note:** The test cases are generated such that it is possible to complete every course (i.e., the graph is a directed acyclic graph).

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/10/07/ex1.png)

```
Input: n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
Output: 8
Explanation: The figure above represents the given graph and the time required to complete each course. 
We start course 1 and course 2 simultaneously at month 0.
Course 1 takes 3 months and course 2 takes 2 months to complete respectively.
Thus, the earliest time we can start course 3 is at month 3, and the total time required is 3 + 5 = 8 months.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/10/07/ex2.png)

```
Input: n = 5, relations = [[1,5],[2,5],[3,5],[3,4],[4,5]], time = [1,2,3,4,5]
Output: 12
Explanation: The figure above represents the given graph and the time required to complete each course.
You can start courses 1, 2, and 3 at month 0.
You can complete them after 1, 2, and 3 months respectively.
Course 4 can be taken only after course 3 is completed, i.e., after 3 months. It is completed after 3 + 4 = 7 months.
Course 5 can be taken only after courses 1, 2, 3, and 4 have been completed, i.e., after max(1,2,3,7) = 7 months.
Thus, the minimum time needed to complete all the courses is 7 + 5 = 12 months.
```

 

**Constraints:**

- `1 <= n <= 5 * 1e4`
- `0 <= relations.length <= min(n * (n - 1) / 2, 5 * 104)`
- `relations[j].length == 2`
- `1 <= prevCoursej, nextCoursej <= n`
- `prevCoursej != nextCoursej`
- All the pairs `[prevCoursej, nextCoursej]` are **unique**.
- `time.length == n`
- `1 <= time[i] <= 104`
- The given graph is a directed acyclic graph.



<br/>

**Solution**

Topological sorting and dynamic programming.

Let `dp[i]` denote the minimum number of month to complete course `i`, and let `prev[i]` denote the prerequisite courses of  course `i`. Then we have,

- `dp[i] = time[i - 1]`, if course `i` has no prerequisite, i.e. its in-degree is zero.
- Otherwise,

$$
dp[i] = \max_{j \in prev[i]}{ \{ dp[j] + time[i - 1] \} }
$$

The final answer is `max(dp)` .

The time complexity is `O(V + E)`, same as topological sorting.

```cpp
using vec = vector<int>;
using vec2 = vector<vec>;
class Solution
{
public:
    int minimumTime(int n, vector<vector<int>> &relations, vector<int> &time)
    {
        vec2 prev(n + 1, vec());
        vec2 graph(n + 1, vec());
        vec indeg(n + 1, 0);

        for (auto &e : relations)
        {
            int u = e[0], v = e[1]; // u -> v
            prev[v].emplace_back(u);
            graph[u].emplace_back(v);
            indeg[v]++;
        }

        vec seq;
        for (int i = 1; i <= n; ++i)
        {
            if (indeg[i] == 0)
                seq.emplace_back(i);
        }

        vec dp(n + 1, 0);
        for (int i = 0; i < (int)seq.size(); ++i)
        {
            int v = seq[i];
            int maxval = 0;
            
            for (int u : prev[v])
                maxval = std::max(maxval, dp[u]);
            dp[v] = time[v - 1] + maxval;

            for (int nxt : graph[v])
            {
                if (--indeg[nxt] == 0)
                    seq.emplace_back(nxt);
            }
        }
        return *std::max_element(begin(dp), end(dp));
    }
};
```

Actually, we do not need two prerequisite arrays (`graph` and `prev`), we can reduce the `prev` array.
```cpp
using vec = vector<int>;
using vec2 = vector<vec>;
class Solution
{
public:
    int minimumTime(int n, vector<vector<int>> &relations, vector<int> &time)
    {
        vec2 graph(n + 1, vec());
        vec indeg(n + 1, 0);

        for (auto &e : relations)
        {
            int u = e[0], v = e[1]; // u -> v
            graph[u].emplace_back(v);
            indeg[v]++;
        }

        vec seq;
        vec dp(n + 1, 0);
        for (int i = 1; i <= n; ++i)
        {
            if (indeg[i] == 0)
            {
                seq.emplace_back(i);
                dp[i] = time[i - 1];
            }
        }

        for (int i = 0; i < (int)seq.size(); ++i)
        {
            int u = seq[i];
            int maxval = 0;
            for (int v : graph[u])
            {
                dp[v] = std::max(dp[v], dp[u] + time[v - 1]);
                if (--indeg[v] == 0)
                    seq.emplace_back(v);
            }
        }
        return *std::max_element(begin(dp), end(dp));
    }
};
```