## Minimum Number of Work Sessions to Finish the Tasks

Leetcode: [1986. Minimum Number of Work Sessions to Finish the Tasks](https://leetcode-cn.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/)

There are `n` tasks assigned to you. The task times are represented as an integer array `tasks` of length `n`, where the `ith` task takes `tasks[i]` hours to finish. A **work session** is when you work for **at most** `sessionTime` consecutive hours and then take a break.

You should finish the given tasks in a way that satisfies the following conditions:

- If you start a task in a work session, you must complete it in the **same** work session.
- You can start a new task **immediately** after finishing the previous one.
- You may complete the tasks in **any order**.

Given `tasks` and `sessionTime`, return *the **minimum** number of **work sessions** needed to finish all the tasks following the conditions above.*

The tests are generated such that `sessionTime` is **greater** than or **equal** to the **maximum** element in `tasks[i]`.

**Constraints:**

- `n == tasks.length`
- `1 <= n <= 14`
- `1 <= tasks[i] <= 10`
- `max(tasks[i]) <= sessionTime <= 15`

**Example 1:**

```
Input: tasks = [1,2,3], sessionTime = 3
Output: 2
Explanation: You can finish the tasks in two work sessions.
- First work session: finish the first and the second tasks in 1 + 2 = 3 hours.
- Second work session: finish the third task in 3 hours.
```

**Example 2:**

```
Input: tasks = [3,1,3,1,1], sessionTime = 8
Output: 2
Explanation: You can finish the tasks in two work sessions.
- First work session: finish all the tasks except the last one in 3 + 1 + 3 + 1 = 8 hours.
- Second work session: finish the last task in 1 hour.
```

**Analysis**

We should put the `tasks` into `n` boxes, the size of each box is `sessionTime`. And we want to minimize such `n`.



## Binary Search

- The min number of sessions we need is `l = SUM(tasks) / sessionTime`.
- The max number of session we need is `n = tasks.size`.
- Perform a binary search on this range `[l, n]`, to test each `m` whether if it's valid.

```cpp
class Solution {
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size();
        int total = accumulate(begin(tasks), end(tasks), 0);
        int l = total / sessionTime, r = n;
        while (l < r)
        {
            int m = l + (r - l) / 2;
            if (check(tasks, m, sessionTime)) r = m;
            else l = m + 1;
        }
        return l;
    }
    
    /* @sessions - The number of sessions.
     * @limit - Each session should have >= 1 task, but total time <= limit.
     */
    bool check(vector<int> &tasks, int sessions, int limit)
    {
        /* there are `sessions` work-sessions, and each session
         * `assign[i]` should be assigned with >= 1 task
         */
        vector<int> assign(sessions, 0);
        return backtrack(tasks, assign, 0, limit);
    }

    bool backtrack(vector<int> &tasks, vector<int> &assign, int idx, int limit)
    {
        /* When all the tasks have been assigned, then return true. */
        int n = tasks.size();
        if (idx >= n) return true;

        int task = tasks[idx];
        /* For each session `assign[i]`, try to put the `task` on it. */
        for (int &workload : assign)
        {
            if (workload + task <= limit)
            {
                workload += task;
                if (backtrack(tasks, assign, idx + 1, limit)) return true;
                workload -= task;
            }
            /* After assignments(backtracking), there is no task assigned to
             * current session, then false.
             */
            if (workload == 0) return false;
        }
        return false;
    }
};
```



## State Compression DP

**Get time of each subset**

- Use an integer `x` to denote whether if `task[i]` is in the subset. If `(x >> j) & 1`, then `task[j]` is in the subset `x`.

- Let `total[x]` denote the total time of tasks subset `x`, then we have

  ```cpp
  total[x] = tasks[j] + total[x - (1 << j)] where ((x >> j) & 1) != 0
  ```

**DP**

Let `dp[x]` denote the min number of sessions, when we have a subset of tasks (denoted by `x`) . 

For each subset `s` of `x`, we can assign `s` with a new session (if the `sessionTime` is large enough to put `s` in).

Then we have
$$
dp[x] = \min_{s \sube x}\{ {dp[x -s]} + 1 \ \ | \ \ \text{total}[s] \le \text{sessionTime} \}
$$

```cpp
class Solution {
public:
    const int INF = INT_MAX / 2;
    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size();
        vector<int> total(1 << n, 0);
        for (int x = 1; x < (1 << n); ++x)
        {
            int j = x & (-x);
            int idx = __builtin__ctz(j);
            total[x] = tasks[idx] + total[x - j];
        }
        vector<int> dp(1 << n, INF);
        dp[0] = 0;
        for (int x = 1; x < (1 << n); ++x)
        {
            for (int s = x; s; s = (s - 1) & x)
                if (total[s] <= sessionTime)
                	dp[x] = min(dp[x], dp[x - s] + 1);
        }
        return dp.back();
    }
};
```

