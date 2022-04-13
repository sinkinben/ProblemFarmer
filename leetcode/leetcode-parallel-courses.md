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

Topological sort and BFS.

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

Refer to: https://en.wikipedia.org/wiki/Analysis_of_parallel_algorithms

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
            /* `next` denote that in the remained courses (not finished course),
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

