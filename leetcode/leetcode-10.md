## Regex Matching

Leetcode: [10. Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/).

The description of this problem is clear:

- Given an input string `s` and a pattern `p`, implement regular expression matching with support for `'.'` and `'*'`.
  - `'.'` matches any single character.
  - `'*'` matches zero or more of the preceding element.
  - It is guaranteed for each appearance of the character `'*'`, there will be a previous valid character to match.
- The matching should cover the **entire** input string (not partial).



## Dynamic Programming

A popular solution is using dynamic programming. 

Let `dp[i, j]` be true if `s[1 ... i]` matches `p[1 ... j]`. And the state equations will be:

- `dp[i, j] = dp[i-1, j-1]` if `p[j] == '.' || p[j] == s[i] `
- `dp[i, j] = dp[i, j-2]` if `p[j] == '*'`, which means that we skip `"x*"` and matching nothing (or match `x` for zero times).
- `dp[i, j] = dp[i-1, j] && (s[i] == p[j-1] || p[j-1] == '.')`, if `p[j] == '*'`, which means that `"x*"` repeats >=1 times, and `x` can be character or a dot `'.'`.

Please note that the index of `s` and `p` in the program start with `0`, which is a little different from the state equations above.

```cpp
class Solution 
{
public:
    bool isMatch(string s, string p) 
    {
        int slen = s.length(), plen = p.length();
        vector<vector<bool>> dp(slen + 1, vector<bool>(plen + 1, false));
        dp[0][0] = true;
        // Note that s = "", can match p = "a*b*c*", hence `i` should be start with 0
        for (int i = 0; i <= slen; ++i)
        {
            for (int j = 1; j <= plen; ++j)
            {
                /* the index of '*' in `p`, must be >= 1, otherwise `p` is invalid,
                 * i.e. (j - 1 >= 1) ==> (j >= 2)
                 */
                if (p[j - 1] == '*')
                {
                    dp[i][j] = dp[i][j -  2] || 
                               (i > 0 && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
                }
                else if (i > 0 && (p[j - 1] == '.' || s[i - 1] == p[j - 1]))
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                
            }
        }
        return dp[slen][plen];
    }
};
```





## DFA

Here I want to show how can solve this problem by **deterministic finite automaton (DFA)**.

Please note that you should know the conception of DFA before you read this article.

For a pattern `p = "a.b*c"`, we can construct such a DFA:

<img src="https://gitee.com/sinkinben/pic-go/raw/master/img/20220121134600.png" style="background: #fff"/>

The `'$'` sign means that, we do not need any character to reach next state, since `'*'` matches **zero** or more of the preceding element. 

DFA can be represented by a graph in the program.

- `state` points to the last valid state we can reach.
-  `state = 0` denote the invalid state, since `0` is the default value of `unordered_map`. Of course, we can use `-1`.

```cpp
class Solution 
{
public:
    unordered_map<int, unordered_map<char, int>> automaton;
    int state = 1;
    bool isMatch(string s, string p)
    {
        int plen = p.length();
        for (int i = 0; i < plen; ++i)
        {
            char x = p[i];
            if ('a' <= x && x <= 'z' || x == '.')
                automaton[state][x] = state + 1, state += 1;
            else if (x == '*' && i > 0)
            {
                automaton[state - 1][p[i - 1]] = state - 1; // match >= 1 p[i - 1]
                automaton[state - 1]['$'] = state;          // match zero p[i - 1]
            }
        }
        return match(s, 0, 1);
    }
    
    /* idx - we are matching s[idx]
     * cur - current state in automaton
     */
    bool match(string &s, int idx, int cur)
    {
        int n = s.length();
        
        if (cur == 0) return false;
        if (idx >= n && cur == state) return true;
        
        if (idx < n)
        {
            /* Each node in automaton, has no more than 3 edges,
             * '$' means matching no character, hence still use `idx` in next matching.
             * For example, p = "a.b*c", s = "aac", we should output true,
             * match(s, idx, s3) means that, we skip matching "b*" in automaton (matched zero 'b').
             */
            int s1 = automaton[cur][s[idx]];
            int s2 = automaton[cur]['.'];
            int s3 = automaton[cur]['$'];
            return match(s, idx + 1, s1) || match(s, idx + 1, s2) || match(s, idx, s3);
        }
        else if (idx == n) 
        {
            /* May be the last edge of automaton is `state[n-1] -- $ --> state[n]`
             * e.g. s = "aa", p = "a*"
             */
            return match(s, idx, automaton[cur]['$']);
        }
        return false;
    }
};
```



At last, we can also pass this problem by STL library :-D.

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        return regex_match(s, regex(p));
    }
};
```

