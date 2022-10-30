## 1239. Maximum Length of a Concatenated String with Unique Characters

Leetcode: https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/

You are given an array of strings `arr`. A string `s` is formed by the **concatenation** of a **subsequence** of `arr` that has **unique characters**.

Return *the **maximum** possible length* of `s`.

A **subsequence** is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

**Example 1:**

```
Input: arr = ["un","iq","ue"]
Output: 4
Explanation: All the valid concatenations are:
- ""
- "un"
- "iq"
- "ue"
- "uniq" ("un" + "iq")
- "ique" ("iq" + "ue")
Maximum length is 4.
```

**Example 2:**

```
Input: arr = ["cha","r","act","ers"]
Output: 6
Explanation: Possible longest valid concatenations are "chaers" ("cha" + "ers") and "acters" ("act" + "ers").
```

**Example 3:**

```
Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
Output: 26
Explanation: The only string in arr has all 26 characters.
```

 

**Constraints:**

- `1 <= arr.length <= 16`
- `1 <= arr[i].length <= 26`
- `arr[i]` contains only lowercase English letters.

<br/>

**Bitmask DP**

Firstly, we make a hashing.
+ Since `arr[i].length <= 26`, we can let one `int` integer denote one `string`.
+ If there are duplicate letters in `arr[i]`, then its hash value will be 0.
+ If `arr[i], arr[j]` have no inter-set, then `hash(arr[i]) & hash(arr[j]) == 0`.

Suppose we have a new vector `nums`, and `nums[i] = hash(arr[i])`. Now the problem becomes:
+ Find a sub-sequence in `nums`, and this OR value of this sub-sequence should be maximum. And  arbitrary two elements in this sequence have no inter-set.
+ The "OR value" of sub-sequence is the result of logical OR on all elements.

Let `dp[i, j]` denote: in range of `[0, i]`, such sequence ends with `nums[i]`, and its OR value is `j`.

```cpp
class Solution {
public:
    int makeHash(string &s)
    {
        int k = 0;
        for (char x: s)
        {
            int i = x - 'a';
            if (((k >> i) & 1) == 0)
                k |= 1 << i;
            else
                return 0; // s contains duplicate letter
        }
        return k;
    }
    int maxLength(vector<string>& arr)
    {
        int n = arr.size();
        vector<int> nums(n);

        for (int i = 0; i < n; ++i) nums[i] = makeHash(arr[i]);
        
        vector<vector<int>> dp(n, vector<int>());
        
        for (int i = 0; i < n; ++i)
        {
            dp[i].emplace_back(nums[i]);
            for (int j = 0; j < i; ++j)
            {
                for (int x: dp[j])
                    if ((x & nums[i]) == 0)
                        dp[i].emplace_back(x | nums[i]);
            }
        }
        
        int res = 0;
        for (auto &vec: dp)
        {
            for (int x: vec)
                res = max(res, __builtin_popcount(x));
        }
        return res;
    }
};
```