## Minimize Max Distance to Gas Station

Leetcode: [774. Minimize Max Distance to Gas Station](https://leetcode-cn.com/problems/minimize-max-distance-to-gas-station/)

You are given an integer array `stations` that represents the positions of the gas stations on the x-axis. You are also given an integer `k`.

You should add `k` new gas stations. You can add the stations anywhere on the x-axis, and **not necessarily on an integer position.**

Let `penalty()` be the maximum distance between adjacent gas stations after adding the `k` new stations.

Return the **smallest** possible value of `penalty()`. Answers within `1e-6` of the actual answer will be accepted.

**Solution**

Binary Search, to minimize the maximum distance.

```cpp
class Solution {
public:
    double minmaxGasDist(vector<int>& stations, int k)
    {
        int n = stations.size();
        vector<int> dis(n - 1, 0);
        for (int i = 0; i + 1 < n; ++i)
            dis[i] = stations[i + 1] - stations[i];
        double l = 0, r = 1e8;
        while (r - l > 1e-6)
        {
            double m = (l + r) / 2;
            if (check(dis, m, k)) r = m;
            else l = m;
        }
        return l;
    }

    /* @k - Insert `k` new stations.
     * @test - The distance between adjacent gas stations should be <= test.
     * Returned value denote we can make adjacent distances <= test.
     */
    bool check(vector<int> &dis, double test, int k)
    {
        /* To make adjacent distances <= test, we need to
         * add `cnt` stations at least.
         */
        int cnt = 0;
        for (int d : dis)
            cnt += ceil(d / test) - 1;
        return cnt <= k;
    }
};
```

