## 1359. Count All Valid Pickup and Delivery Options

Link: https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/

Given `n` orders, each order consist in pickup and delivery services. 

Count all valid pickup/delivery possible sequences such that delivery(i) is always after of pickup(i). 

Since the answer may be too large, return it modulo 10^9 + 7.



**Example 1:**

```
Input: n = 1
Output: 1
Explanation: Unique order (P1, D1), Delivery 1 always is after of Pickup 1.
```

**Example 2:**

```
Input: n = 2
Output: 6
Explanation: All possible orders: 
(P1,P2,D1,D2), (P1,P2,D2,D1), (P1,D1,P2,D2), (P2,P1,D1,D2), (P2,P1,D2,D1) and (P2,D2,P1,D1).
This is an invalid order (P1,D2,P2,D1) because Pickup 2 is after of Delivery 2.
```

**Example 3:**

```
Input: n = 3
Output: 90
```

 

**Constraints:**

- `1 <= n <= 500`

<br/>

**Solution**

- For $i$-th sequence, it can be constructed from $(i-1)$-th sequence.
- Let $f(i)$ denote the number of possible sequences when inputing $i$ , and let $k = 2(i-1)$ denote the length of $(i - 1)$-th sequence. 
- Now we need to insert $(P_i, D_i)$ into the gap of $(i-1)$-th sequence.
  - If we put $(P_i, D_i)$ adjacently, then we have $(k + 1) * f(i - 1)$ choices, since there are $k + 1$ gap in $(i-1)$-th sequence.
  - If we put $(P_i, D_i)$ at two different gaps, then we have $[k(k+1)/2] \cdot f(i-1)$ choices.

That is:
$$
f(i) = f(i-1) \cdot [(k + 1) + \frac{k(k + 1)}{2}] = f(i - 1) \cdot i \cdot (2i-1)
$$

```cpp
class Solution
{
public:
    const int MOD = 1e9 + 7;
    int countOrders(int n)
    {
        int64_t f = 1;
        for (int i = 2; i <= n; ++i)
        {
            int64_t k = 2 * (i - 1);
            f = (((k + 1) + (k * (k + 1) / 2)) * f) % MOD;
        }
        return f;
    }
};
```





