## Palindrome Partitioning

Problems:

- [131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning)
- [132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii)
- [1278. Palindrome Partitioning III](https://leetcode.com/problems/palindrome-partitioning-iii)
- [1745. Palindrome Partitioning IV](https://leetcode.com/problems/palindrome-partitioning-iv)



## Palindrome Partitioning

Given a string `s`, partition `s` such that every substring of the partition is a **palindrome**. Return all possible palindrome partitioning of `s`.

A **palindrome** string is a string that reads the same backward as forward.

**Example**

```
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]
```

<br/>

**Solution**

Backtracking strategy.

If you want know more about backtracking, welcome to read my article "[A Pattern to Solve Backtracking Problems](https://github.com/sinkinben/leetcode/blob/master/solution-note/leetcode/leetcode-backtrack.md)".

```cpp
class Solution 
{
public:
    int n;
    vector<string> buf;
    vector<vector<string>> res;
    vector<vector<string>> partition(string s) 
    {
        n = s.length();
        backtrack(s, 0);
        return res;
    }
    
    void backtrack(string &s, int idx)
    {
        if (idx >= n)
        {
            res.emplace_back(buf);
            return;
        }
        for (int i = idx; i < n; ++i)
        {
            string sub = s.substr(idx, i - idx + 1);
            if (check(sub))
            {
                buf.emplace_back(sub);
                backtrack(s, i + 1);
                buf.pop_back();
            }
        }
    }
    
    bool check(string &s)
    {
        int n = s.length();
        for (int i = 0; i < n / 2; ++i) if (s[i] != s[n - i - 1]) return false;
        return true;
    }
};
```



## Palindrome Partitioning II

Given a string `s`, partition `s` such that every substring of the partition is a palindrome.

Return *the minimum cuts needed* for a palindrome partitioning of `s`.

**Example 1:**

```
Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
```

**Example 2:**

```
Input: s = "a"
Output: 0
```

**Example 3:**

```
Input: s = "ab"
Output: 1
```

**Constraints:**

- `1 <= s.length <= 2000`
- `s` consists of lowercase English letters only.

<br/>

**Solution**

```
TBD.
```



## Palindrome Partitioning III

You are given a string `s` containing lowercase letters and an integer `k`. You need to :

- First, change some characters of `s` to other lowercase English letters.
- Then divide `s` into `k` non-empty disjoint substrings such that each substring is a palindrome.

Return *the minimal number of characters that you need to change to divide the string*.

**Example 1:**

```
Input: s = "abc", k = 2
Output: 1
Explanation: You can split the string into "ab" and "c", and change 1 character in "ab" to make it palindrome.
```

**Example 2:**

```
Input: s = "aabbc", k = 3
Output: 0
Explanation: You can split the string into "aa", "bb" and "c", all of them are palindrome.
```

**Example 3:**

```
Input: s = "leetcode", k = 8
Output: 0
```

**Constraints:**

- `1 <= k <= s.length <= 100`.
- `s` only contains lowercase English letters.

<br/>

**Solution**

```
TBD.
```



## Palindrome Partitioning IV

Given a string `s`, return `true` *if it is possible to split the string* `s` *into three **non-empty** palindromic substrings. Otherwise, return* `false`.

A string is said to be palindrome if it the same string when reversed.

Constraints: `s.length <= 2000`.

**Example**

```
Input: s = "abcbdd"
Output: true
Explanation: "abcbdd" = "a" + "bcb" + "dd", and all three substrings are palindromes.
```

<br/>

**Solution**

Dynamic programming problem.

- Let `dp[i, j]` denote whether if `s[i, ..., j]` is palindromic.
- State equation is `dp[i, j] = s[i] == s[j] && dp[i + 1, j - 1]`.

We need **three** palindrome sub-string, hence we need to split at **two** position. Just enumerate all `(i, j)` pairs to find such sub-strings.

```cpp
class Solution {
public:
    bool checkPartitioning(string s)
    {
        int n = s.length();
        vector<vector<bool>> dp(n, vector<bool>(n, 0));
        for (int i = 0; i < n; ++i)
        {
            dp[i][i] = 1;
            if (i + 1 < n) dp[i][i + 1] = (s[i] == s[i + 1]);
        }

        for (int d = 2; d < n; ++d)
        {
            for (int i = 0; i + d < n; ++i)
            {
                int j = i + d;
                dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
            }
        }

        for (int i = 0; i + 1 < n; ++i)
            for (int j = 0; j + 1 < n; ++j)
                if (dp[0][i] && dp[i + 1][j] && dp[j + 1][n - 1])
                    return true;
        return false;
    }
};
```

