## Koko Eating Bananas

Leetcode: [875. Koko Eating Bananas](https://leetcode-cn.com/problems/koko-eating-bananas/)

Koko loves to eat bananas. There are `n` piles of bananas, the `ith` pile has `piles[i]` bananas. The guards have gone and will come back in `h` hours.

Koko can decide her bananas-per-hour eating speed of `k`. Each hour, she chooses some pile of bananas and eats `k` bananas from that pile. If the pile has less than `k` bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return *the minimum integer* `k` *such that she can eat all the bananas within* `h` *hours*.

 **Example 1:**

```
Input: piles = [3,6,7,11], h = 8
Output: 4
```

**Example 2:**

```
Input: piles = [30,11,23,4,20], h = 5
Output: 30
```

**Example 3:**

```
Input: piles = [30,11,23,4,20], h = 6
Output: 23 
```

**Constraints:**

- `1 <= piles.length <= 1e4`
- `piles.length <= h <= 1e9`
- `1 <= piles[i] <= 1e9`



**Solution**

```cpp
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h)
    {
        int l = 1;  // or l = max(1, sum / h)
        int r = INT_MAX;
        while (l < r)
        {
            int speed = l + (r - l) / 2;
            if (check(piles, speed, h)) r = speed;
            else l = speed + 1;
        }
        return l;
    }
    /* Eat `speed` bananas per hour. Can we eat them all
     * in `h` hours?
     */
    bool check(vector<int> &piles, int speed, int h)
    {
        int time = 0;
        for (int x : piles)
            time += (x / speed) + (x % speed != 0);
        return time <= h;
    }
};
```



## Minimized Maximum of Products Distributed to Any Store

Leetcode: [2064. Minimized Maximum of Products Distributed to Any Store](https://leetcode-cn.com/problems/minimized-maximum-of-products-distributed-to-any-store/)

You are given an integer `n` indicating there are `n` specialty retail stores. There are `m` product types of varying amounts, which are given as a **0-indexed** integer array `quantities`, where `quantities[i]` represents the number of products of the `ith` product type.

You need to distribute **all products** to the retail stores following these rules:

- A store can only be given **at most one product type** but can be given **any** amount of it.
- After distribution, each store will have been given some number of products (possibly `0`). Let `x` represent the maximum number of products given to any store. You want `x` to be as small as possible, i.e., you want to **minimize** the **maximum** number of products that are given to any store.

Return *the minimum possible* `x`.

 **Constraints:**

- `m == quantities.length`
- `1 <= m <= n <= 1e5`
- `1 <= quantities[i] <= 1e5`

```
Input: n = 6, quantities = [11,6]
Output: 3
Explanation: One optimal way is:
- The 11 products of type 0 are distributed to the first four stores in these amounts: 2, 3, 3, 3
- The 6 products of type 1 are distributed to the other two stores in these amounts: 3, 3
The maximum number of products given to any store is max(2, 3, 3, 3, 3, 3) = 3.
```

**Solution**

```cpp
class Solution {
public:
    int minimizedMaximum(int k, vector<int>& nums) {
        int l = 1, r = INT_MAX;
        while (l < r)
        {
            int m = l + (r - l) / 2;
            if (check(nums, m, k))
                r = m;
            else
                l = m + 1;
        }
        return l;
    }

    /* Put nums into some buckets, each bucket <= limit,
     * and each buckets[i] is allowed to put ONE nums[i] in.
     * Is k buckets enough?
     */
    bool check(vector<int> &nums, int limit, int k)
    {
        int cnt = 0;
        for (int x : nums)
            cnt += x / limit + (x % limit != 0);
        return cnt <= k;
    }
};
```

