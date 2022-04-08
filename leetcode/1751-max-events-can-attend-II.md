## Maximum Number of Events That Can Be Attended II

Leetcode: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/

Refer to [this solution](https://leetcode-cn.com/problems/maximum-number-of-events-that-can-be-attended-ii/solution/po-su-dp-er-fen-dp-jie-fa-by-ac_oier-88du/).

You are given an array of `events` where `events[i] = [startDayi, endDayi, valuei]`. The `ith` event starts at `startDayi` and ends at `endDayi`, and if you attend this event, you will receive a value of `valuei`. You are also given an integer `k` which represents the maximum number of events you can attend.

You can only attend one event at a time. If you choose to attend an event, you must attend the **entire** event. Note that the end day is **inclusive**: that is, you cannot attend two events where one of them starts and the other ends on the same day.

Return *the **maximum sum** of values that you can receive by attending events.*

**Example - 1**

<img src="https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-60048-pm.png" style="width:50%"/>

```
Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
Output: 7
Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.
```

**Example - 2**

<img src="https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-60150-pm.png" style="width:50%" />

```
Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
Output: 10
Explanation: Choose event 2 for a total value of 10.
Notice that you cannot attend any other event as they overlap, and that you do not have to attend k events.
```

**Solution**

An intuition is that we can solve this problem by reducing it into "01 Knapsack Problem".

Let `dp[i, j]` denote the max value we can get, in range of `events[0, ..., i]`. Then we have

```cpp
dp[i, j] = max(dp[i - 1][j], dp[pre][j - 1] + val[i])
```

where `pre` denotes the most-recent state that has no conflict with current `events[i]`.

Code Explanation:

- Sort `events` according to their end day. Put those events with earlier end-day at the front.
- The key point is how to find the `pre` state that has no conflict with current `events[i]`.
  - "No conflict" means `event[pre].end < cur.start`.
  - Scan the range `events[..., i - 1]` from right to left. This is why we sort it firstly.
- Time complexity is `O(n(n+k))`.

```cpp
class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        
        sort(begin(events), end(events), [](auto &v1, auto &v2) {
           return v1[1] < v2[1]; 
        });
        
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        for (int i = 1; i <= n; ++i)
        {
            auto &e = events[i - 1];
            int start = e[0], end = e[1], val = e[2];
            int pre = i - 1;
            
            /* please note that i-th events is `events[i - 1]`,
             * where 1 <= i <= n, hence `pre - 1` is used.
             */
            while (pre >= 1 && !(events[pre - 1][1] < start))
                --pre;
            
            for (int j = 0; j <= k; ++j)
                dp[i][j] = max(dp[i - 1][j], (j >= 1) ? (dp[pre][j - 1] + val) : 0);
        }
        return dp[n][k];
    }
};

```

