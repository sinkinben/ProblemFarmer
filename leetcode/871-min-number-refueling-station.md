## 871. Minimum Number of Refueling Stops

Leetcode: https://leetcode.com/problems/minimum-number-of-refueling-stops/

A car travels from a starting position to a destination which is `target` miles east of the starting position.

There are gas stations along the way. The gas stations are represented as an array `stations` where `stations[i] = [positioni, fueli]` indicates that the `ith` gas station is `positioni` miles east of the starting position and has `fueli` liters of gas.

The car starts with an infinite tank of gas, which initially has `startFuel` liters of fuel in it. It uses one liter of gas per one mile that it drives. When the car reaches a gas station, it may stop and refuel, transferring all the gas from the station into the car.

Return *the minimum number of refueling stops the car must make in order to reach its destination*. If it cannot reach the destination, return `-1`.

Note that if the car reaches a gas station with `0` fuel left, the car can still refuel there. If the car reaches the destination with `0` fuel left, it is still considered to have arrived.

 

**Example 1:**

```
Input: target = 1, startFuel = 1, stations = []
Output: 0
Explanation: We can reach the target without refueling.
```

**Example 2:**

```
Input: target = 100, startFuel = 1, stations = [[10,100]]
Output: -1
Explanation: We can not reach the target (or even the first gas station).
```

**Example 3:**

```
Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
Output: 2
Explanation: We start with 10 liters of fuel.
We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters to 60 liters of gas.
Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the target.
We made 2 refueling stops along the way, so we return 2.
```

 

**Constraints:**

- `1 <= target, startFuel <= 1e9`
- `0 <= stations.length <= 500`
- `0 <= position[i] <= position[i+1] < target`
- `1 <= fuel[i] < 1e9`

<br/>

**Dynamic Programming**

Let `dp[i, j]` denote the futhest position we can reach, in range of `stations[0, i)`, using **exactly** `j` times refueling. Then we have:

```cpp
dp[i, 0] =  startFuel    // Not allow to refuel.
dp[0, j] =  startFule    // No station to refuel
dp[i, j] =  dp[i - 1, j - 1] + fuel[i - 1] if dp[i - 1, j - 1] >= position[i - 1]
         or dp[i - 1, j] // We may not choose the (i - 1)-th station.
```

We can see that it's very similar to 01-Knapsack problem.

Here is the code.

```cpp
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int n = stations.size();
        // Pay attention to int32-overflow
        vector<vector<int64_t>> dp(n + 1, vector<int64_t>(n + 1, 0));

        for (int i = 0; i <= n; ++i) dp[i][0] = dp[0][i] = startFuel;
        
        for (int i = 1; i <= n; ++i)
        {
            int pos = stations[i - 1][0], fuel = stations[i - 1][1];
            for (int j = 1; j <= n; ++j)
            {
                dp[i][j] = dp[i - 1][j];
                if (dp[i - 1][j - 1] >= pos)
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + fuel);
            }
        }
        
        // All stations in [0, n) can be chosen, so scan dp[n]
        for (int j = 0; j <= n; ++j)
            if (dp[n][j] >= target) return j;
        return -1;
    }
};
```

<br/>

Obviously, we can perform space optimization on 2D-array `dp`. 

The solution given by the official is this one.

```cpp
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int n = stations.size();
        // Pay attention to int32-overflow
        vector<int64_t> dp(n + 1, startFuel);

        for (int i = 1; i <= n; ++i)
        {
            int pos = stations[i - 1][0], fuel = stations[i - 1][1];
            for (int j = n; j >= 1 && dp[j - 1] >= pos; --j)
                dp[j] = max(dp[j], dp[j - 1] + fuel);
        }

        for (int j = 0; j <= n; ++j)
            if (dp[j] >= target) return j;
        return -1;
    }
};
```



**Heap**

There is an intuition.

- When we passed a gas station, we don't not need to decide whether if we refuel up or not. That's because there may be a better choice ahead, i.e. a station with more fuel.
- However, when we run up the fuel of our car, we must fuel it up. And the best choice is: greedily choosing the largest gas stations we passed.

```cpp
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int> que;
        int res = 0;
        int cur = startFuel;  // Number of current fuel in the car
        int prev = 0;         // Position of previous gas station we met
        for (auto &vec: stations)
        {
            int pos = vec[0], fuel = vec[1];
            cur -= pos - prev;
            while (cur < 0 && !que.empty())
            {
                cur += que.top(), que.pop();
                res += 1;
            }
            // If we refuel up at all stations we met, but still can not reach stations[i],
            // then we can not reach target.
            if (cur < 0) return -1;
            prev = pos;
            que.emplace(fuel);
        }
        // Now we reached stations[n - 1], we need to get futher, to reach 'target'
        cur -= target - prev;
        while (cur < 0 && !que.empty())
            cur += que.top(), que.pop(), res++;
        return cur < 0 ? -1 : res;
    }
};
```



[LCP 30. 魔塔游戏](https://leetcode.cn/problems/p0NxJO/) is very similar to this problem.