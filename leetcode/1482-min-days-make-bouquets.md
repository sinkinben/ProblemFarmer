## Minimum Number of Days to Make m Bouquets

Leetcode: [1482. Minimum Number of Days to Make m Bouquets](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/)

You are given an integer array `bloomDay`, an integer `m` and an integer `k`.

You want to make `m` bouquets. To make a bouquet, you need to use `k` **adjacent flowers** from the garden.

The garden consists of `n` flowers, the `ith` flower will bloom in the `bloomDay[i]` and then can be used in **exactly one** bouquet.

Return *the minimum number of days you need to wait to be able to make* `m` *bouquets from the garden*. If it is impossible to make m bouquets return `-1`.

**Example - 1**

```
Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
Output: 3
Explanation: Let us see what happened in the first three days. x means flower bloomed and _ means flower did not bloom in the garden.
We need 3 bouquets each should contain 1 flower.
After day 1: [x, _, _, _, _]   // we can only make one bouquet.
After day 2: [x, _, _, _, x]   // we can only make two bouquets.
After day 3: [x, _, x, _, x]   // we can make 3 bouquets. The answer is 3.
```

**Example - 2**

```text
Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
Output: 12
Explanation: We need 2 bouquets each should have 3 flowers.
Here is the garden after the 7 and 12 days:
After day 7: [x, x, x, x, _, x, x]
We can make one bouquet of the first three flowers that bloomed. We cannot make another bouquet from the last three flowers that bloomed because they are not adjacent.
After day 12: [x, x, x, x, x, x, x]
It is obvious that we can make two bouquets in different ways.
```

<br/>



**Solution**

Use min days to get max number of bouquets.

Binary search to find the min days `mid` .

```cpp
class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        if (1ll * m * k > bloomDay.size()) return -1;

        int l = INT_MAX, r = INT_MIN;
        for (int x : bloomDay)
            l = min(l, x), r = max(r, x);

        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (check(bloomDay, mid, m, k))
                r = mid;
            else 
                l = mid + 1;
        }
        return l;
    }

    /* @test - The number of days we need to wait.
     */
    bool check(vector<int> &bloomDay, int test, int m, int k)
    {
        int n = bloomDay.size();
        auto isBloom = [=](int idx) { return bloomDay[idx] <= test; };
        
        int cnt = 0, l = 0;
        while (l < n)
        {
            /* skip the flowers not bloom */
            while (l < n && !isBloom(l)) ++l;

            /* [l, r) has bloomed */
            int r = l + 1;
            while (r < n && isBloom(r)) ++r;

            cnt += (r - l) / k;
            l = r;
        }
        return cnt >= m;
    }
};
```

