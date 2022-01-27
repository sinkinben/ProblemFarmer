## Palindrome Partitioning

Problems:

- [131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning)
- [132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii)
- [1278. Palindrome Partitioning III](https://leetcode.com/problems/palindrome-partitioning-iii)
- [1745. Palindrome Partitioning IV](https://leetcode.com/problems/palindrome-partitioning-iv)



## Palindrome Partitioning

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



## Palindrome Partitioning IV

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

