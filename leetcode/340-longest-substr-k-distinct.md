##  Longest Substring with At Most K Distinct Characters

Leetcode: 

- [159. Longest Substring with At Most Two Distinct Characters](https://leetcode-cn.com/problems/longest-substring-with-at-most-two-distinct-characters)
- [340. Longest Substring with At Most K Distinct Characters](https://leetcode-cn.com/problems/longest-substring-with-at-most-k-distinct-characters/)

Given a string `s` and an integer `k`, return the length of the longest substring of s that contains at most k distinct characters. 

Constraints: `1 <= s.length <= 5 * 10^4, 0 <= k <= 50`

Example 1:

```
Input: s = "eceba", k = 2
Output: 3
Explanation: The substring is "ece" with length 3.
```

Example 2:

```
Input: s = "aa", k = 1
Output: 2
Explanation: The substring is "aa" with length 2.
```

<br/>

**Solution**

```cpp
class Solution 
{
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) 
    {
        if (s.empty() || k == 0) return 0;
        unordered_map<char, int> map;
        int l = 0, r = 0, n = s.length(), res = 0;
        while (r < n)
        {
            map[s[r]]++, r += 1;
            while (map.size() > k)
            {
                map[s[l]]--;
                if (map[s[l]] == 0) map.erase(s[l]);
                l += 1;
            }
            res = max(res, r - l);
        }
        return res;
    }
};
```





## Longest Substring with At Most Two Distinct Characters

Given a string `s`, return the length of the longest substring that contains at most two distinct characters.

**Constraints** `1 <= s.length <= 105`, `s` consists of English letters.

**Example 1**

```
Input: s = "eceba"
Output: 3
Explanation: The substring is "ece" which its length is 3.
```

**Example 2**

```
Input: s = "ccaabbb"
Output: 5
Explanation: The substring is "aabbb" which its length is 5.
```

<br/>

**Solution**

Here is my solution.

```cpp
class Solution
{
public:
    int lengthOfLongestSubstringTwoDistinct(string s)
    {
        const int k = 2;
        unordered_map<char, int> table;
        int n = s.length();
        int l = 0, r = 0, res = 0;
        while (r < n)
        {
            table[s[r]]++, r += 1;
            while (table.size() > k && l < r)
            {
                table[s[l]]--;
                if (table[s[l]] == 0) table.erase(s[l]);
                l += 1;
            }
            res = max(res, r - l);
        }
        return res;
    }
};
```

