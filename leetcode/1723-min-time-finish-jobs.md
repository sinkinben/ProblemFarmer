## Find Minimum Time to Finish All Jobs

Leetcode: [1723. Find Minimum Time to Finish All Jobs](https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs/)

You are given an integer array `jobs`, where `jobs[i]` is the amount of time it takes to complete the `ith` job.

There are `k` workers that you can assign jobs to. Each job should be assigned to **exactly** one worker. The **working time** of a worker is the sum of the time it takes to complete all jobs assigned to them. Your goal is to devise an optimal assignment such that the **maximum working time** of any worker is **minimized**.

*Return the **minimum** possible **maximum working time** of any assignment.*

**Example 1:**

```
Input: jobs = [3,2,3], k = 3
Output: 3
Explanation: By assigning each person one job, the maximum time is 3.
```

**Example 2:**

```
Input: jobs = [1,2,4,7,8], k = 2
Output: 11
Explanation: Assign the jobs the following way:
Worker 1: 1, 2, 8 (working time = 1 + 2 + 8 = 11)
Worker 2: 4, 7 (working time = 4 + 7 = 11)
The maximum working time is 11.
```

**Constraints:**

- `1 <= k <= jobs.length <= 12`
- `1 <= jobs[i] <= 1e7`

<br/>

**Solution**

An intuition is that, we need to divide `jobs` into `k` parts (NOT need to be consecutive), and make the sum of each part as close as possible.

This is a min-max problem, usually, we can solve such problems via dynamic programming or binary search.



## Dynamic Programming

Refer to: https://www.cnblogs.com/sinkinben/p/14264235.html

**Get time of each subset**

- Let $n$ denote the length of `jobs`, then `jobs` will have $2^n$ subsets. 

- We use one integer `int(x)` to denote one subset, if `(x >> j) & 1 == 1`, then it means `jobs[j]` is in the subset `x`.

- Let `total[x]` denote the total time of subset `x`. Then we have

  ```cpp
  total[x] = jobs[j] + total[x - (1 << j)] where ((x >> j) & 1) != 0
  ```

**DP**

Let `dp[i, x]` denote the min-time when we assign `workers[0, ..., i]` to finish to jobs subset `x`.

Let `s` denote each subset of `x`, then we have two choices: 

- `total[s]` denote the min-time, when we assign jobs subset `s` to `worker[i]`.
- The remained part is `x - s`, we should assign them to `worker[0, ..., i - 1]`.

Therefore, the state equation is:
$$
dp[i, x] = \min_{s \sube x}\{ \max(\text{total}[s], dp[i - 1][x - s]) \}
$$
The initial condition is:

```cpp
dp[0, x] = total[x];
```

The final answer is `dp[k - 1][(1 << n) - 1]`.

**Source Code**

Space complexity is $O(k\cdot2^n)$.

```cpp
class Solution {
public:
    /* k workers, n jobs */
    const int INF = INT_MAX / 2;
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int n = jobs.size();
        vector<int> total(1 << n, 0);
        for (int x = 0; x < (1 << n); ++x)
        {
            for (int j = 0; j < n; ++j)
            {
                if ((x >> j) & 1)
                {
                    total[x] = jobs[j] + total[x - (1 << j)];
                    break;
                }
            }
        }
        vector<vector<int>> dp(k, vector<int>(1 << n, INF));
        for (int x = 0; x < (1 << n); ++x)
            dp[0][x] = total[x];
        for (int i = 1; i < k; ++i)
            for (int x = 0; x < (1 << n); ++x)
                for (int s = x; s != 0; s = (s - 1) & x)
                    dp[i][x] = min(dp[i][x], max(total[s], dp[i - 1][x - s]));

        return dp[k - 1][(1 << n) - 1];
    }
};
```

We can use `__builtin_ctz(x)` to compute the number of trailing zero-bits. **`x` can not be 0 in `__builtin_ctz(x)`**.

```cpp
class Solution {
public:
    // k workers, n jobs
    const int INF = INT_MAX / 2;
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int n = jobs.size();
        vector<int> total(1 << n, 0);
        // x should start at 1
        for (int x = 1; x < (1 << n); ++x)
        {
            int j = x & (-x);           // keep the right-most bit=1, which is equivalent to x&(~x+1)
            int idx = __builtin_ctz(j); // count the number of trailing zeros
            total[x] = total[x - j] + jobs[idx];
        }
        vector<vector<int>> dp(k, vector<int>(1 << n, INF));
        for (int x = 0; x < (1 << n); ++x)
            dp[0][x] = total[x];
        for (int i = 1; i < k; ++i)
            for (int x = 0; x < (1 << n); ++x)
                for (int s = x; s != 0; s = (s - 1) & x)  // enumerate all subsets of `x`, except empty set
                    dp[i][x] = min(dp[i][x], max(total[s], dp[i - 1][x - s]));

        return dp[k - 1][(1 << n) - 1];
    }
};
```



## Binary Search + Backtracking

Obviously, the answer should be in the range of `[MAX(jobs), SUM(jobs)]`, we performe binary search on this range.

The key point is how to check a value `limit` whether if it's valid. 

- Here we use backtracking strategy. **Note that each worker should have a job.**
- For each job `jobs[idx]`, we try to assign it to each worker.

```cpp
class Solution {
public:
    int n;
    vector<int> assign;

    /* k workers, n jobs */
    int minimumTimeRequired(vector<int>& jobs, int k) 
    {
        if (jobs.empty()) return 0;
        assign.resize(k, 0);
        n = jobs.size();
        /* firstly assign the max-job */
        sort(begin(jobs), end(jobs), [](int x, int y) { return x > y; });
        int l = jobs[0], r = accumulate(begin(jobs), end(jobs), 0);
        while (l < r)
        {
            int m = l + (r - l) / 2;
            if (check(jobs, k, m)) r = m;
            else l = m + 1;
        }
        return l;
    }
    
    /* @limit - The workload of each worker must be <= limit, i.e. assign[i] <= limit
     */
    bool check(vector<int> &jobs, int k, int limit)
    {
        std::fill(begin(assign), end(assign), 0);
        return backtrack(jobs, 0, limit);
    }
    
    /* try to assign jobs[idx] to each worker */
    bool backtrack(vector<int> &jobs, int idx, int limit)
    {
        if (idx >= n) return true;
        int job = jobs[idx];
        for (int &workload : assign)
        {
            if (workload + job <= limit)
            {
                workload += job;
                if (backtrack(jobs, idx + 1, limit)) return true;
                workload -= job;
            }
            /* After assignments (backtracking), if current worker has no job,
             * then the assignment failed.
             */
            if (workload == 0) return false;
        }
        return false;
    }
};
```

