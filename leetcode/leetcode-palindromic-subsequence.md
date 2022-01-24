

## Longest Palindromic Subsequence

Problems:

- [516. Longest Palindromic Subsequence](https://leetcode-cn.com/problems/longest-palindromic-subsequence/)
- [1682. Longest Palindromic Subsequence II](https://leetcode-cn.com/problems/longest-palindromic-subsequence-ii/)
- [730. Count Different Palindromic Subsequences](https://leetcode-cn.com/problems/count-different-palindromic-subsequences/)





## Longest Palindromic Subsequence

Given a string `s`, find *the longest palindromic **subsequence**'s length in* `s`.

A **subsequence** is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

**Constraints**

- `1 <= s.length <= 1000`
- `s` consists only of lowercase English letters.

**Example 1**

```
Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".
```

**Example 2**

```
Input: s = "cbbd"
Output: 2
Explanation: One possible longest palindromic subsequence is "bb".
```

 <br/>

**Solution**

Define `dp[i, j]` as the length of longest parlindromic subsequence, in the range of `s[i, ..., j]`.

State equation:

```text
dp[i, j] = dp[i + 1, j - 1] + 2,            if s[i] == s[j]
         = max(dp[i + 1, j], dp[i, j - 1]), otherwise
```

Here is the code.

```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) 
    {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
        {
            dp[i][i] = 1;
            if (i + 1 < n) dp[i][i + 1] = 1 + (s[i] == s[i + 1]);
        }
        for (int d = 2; d < n; ++d)
        {
            for (int i = 0; i + d < n; ++i)
            {
                int j = i + d;
                if (s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1] + 2;
                else dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
        return dp[0][n - 1];
    }
};
```



## Longest Palindromic Subsequence II

A subsequence of a string `s` is considered a good palindromic subsequence if:

- It is a subsequence of s.
- It is a palindrome (has the same value if reversed).
- It has an **even** length.
- No two consecutive characters are equal, except the two middle ones.

For example, if `s = "abcabcabb"`, then `"abba"` is considered a good palindromic subsequence, while `"bcb"` (not even length) and `"bbbb"` (has equal consecutive characters) are not.

Given a string `s`, return the length of the longest good palindromic subsequence in `s`. 

**Example 1**

```
Input: s = "bbabab"
Output: 4
Explanation: The longest good palindromic subsequence of s is "baab".
```

**Example 2**

```
Input: s = "dcbccacdb"
Output: 4
Explanation: The longest good palindromic subsequence of s is "dccd".
```

**Constraints**

- `1 <= s.length <= 250`
- `s` consists of lowercase English letters

<br/>

**Intuitive Solution (Wrong)**

Define `dp[i, j]` as the length of longest good palindromic subsequence, in range of `s[i, ..., j]`.

State equation:

```text
dp[i, j] = dp[i + 1, j - 1] + 2, if s[i] == s[j] && s[i] != s[i + 1]
         = dp[i + 1, j - 1], otherwise
```

But it's **WRONG**, since the problem demand a **sub-sequence**, hence `s[i] != s[i + 1]` is the wrong condition.

<br/>

**Correct Solution**

Let `dp[i, j, ch]` denote the the length of longest good palindromic subsequence in range of `s[i, ..., j]`, and its out-most letters are `ch`.

Then state equation is:

```text
dp[i, j, ch] = 2 + dp[i + 1, j - 1, s[i]], if s[i] == s[j] && s[i] != ch
             = max(dp[i + 1, j, ch], dp[i, j - 1, ch]), otherwise
```

And we should return `max(dp[0, n - 1])`.

Here is the code.

```cpp
typedef vector<int> vec_t;
typedef vector<vec_t> vec2_t;
typedef vector<vec2_t> vec3_t;
class Solution 
{
public:
    int longestPalindromeSubseq(string s) 
    {
        int n = s.length();
        vec3_t dp(n, vec2_t(n, vec_t(26, 0)));
        for (int d = 1; d < n; d++)
        {
            for (int i = 0; i + d < n; ++i)
            {
                int j = i + d;
                for (char ch = 'a'; ch <= 'z'; ++ch)
                {
                    if (s[i] == s[j] && s[i] != ch)
                        dp[i][j][ch - 'a'] = 2 + dp[i + 1][j - 1][s[i] - 'a'];
                    else
                        dp[i][j][ch - 'a'] = max(dp[i + 1][j][ch - 'a'], dp[i][j - 1][ch - 'a']);
                }
            }
        }
        return *max_element(dp[0][n - 1].begin(), dp[0][n - 1].end());
    }
};
```



## Count Different Palindromic Subsequences

Given a string s, return *the number of different non-empty palindromic subsequences in* `s`. Since the answer may be very large, return it **modulo** `109 + 7`.

A subsequence of a string is obtained by deleting zero or more characters from the string.

A sequence is palindromic if it is equal to the sequence reversed.

Two sequences `a1, a2, ...` and `b1, b2, ...` are different if there is some `i` for which `ai != bi`. 

**Example 1**

```
Input: s = "bccb"
Output: 6
Explanation: The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
Note that 'bcb' is counted only once, even though it occurs twice.
```

**Example 2**

```
Input: s = "abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba"
Output: 104860361
Explanation: There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 109 + 7.
```

**Constraints**

- `1 <= s.length <= 1000`
- `s[i]` is either `'a'`, `'b'`, `'c'`, or `'d'`.

<br/>

**Solution**

Here we still use dynamic programming, which is a little similar to LPS-II problem above.

Define `dp[i, j, ch]` as the number of non-empty palindomic sequence in the range of `s[i, ..., j]`, and its out-most letters are both `ch`.

Then the state equation is:

```cpp
dp[i, j, ch] = dp[i + 1, j, ch], if s[i] != ch
dp[i, j, ch] = dp[i, j - 1, ch], if s[j] != ch
dp[i, j, ch] = dp[i + 1, j - 1, 'a'] + 
               dp[i + 1, j - 1, 'b'] + 
               dp[i + 1, j - 1, 'c'] + 
               dp[i + 1, j - 1, 'd'] + 2, if s[i] = s[j] = ch
```

And we should return `SUM(dp[0, n - 1])`.

Here is my code.

```cpp
typedef vector<int> vec_t;
typedef vector<vec_t> vec2_t;
typedef vector<vec2_t> vec3_t;
class Solution 
{
public:
    const string chars = "abcd";
    const int NR_CHARS = 4;
    const int MOD = 1e9 + 7;
    int countPalindromicSubsequences(string s) 
    {
        int n = s.length();
        vec3_t dp(n, vec2_t(n, vec_t(NR_CHARS, 0)));

        for (int i = 0; i < n; ++i)
            for (char ch : chars)
                dp[i][i][ch - 'a'] = (s[i] == ch);

        
        for (int d = 1; d < n; ++d)
        {
            for (int i = 0; i + d < n; ++i)
            {
                int j = i + d;
                for (char ch : chars)
                {
                    if (s[i] != ch) dp[i][j][ch - 'a'] = dp[i + 1][j][ch - 'a'];
                    else if (s[j] != ch) dp[i][j][ch - 'a'] = dp[i][j - 1][ch - 'a'];
                    else if (s[i] == ch && s[j] == ch)
                    {
                        dp[i][j][ch - 'a'] = 2;
                        for (char c : chars)
                        {
                            dp[i][j][ch - 'a'] += dp[i + 1][j - 1][c - 'a'];
                            dp[i][j][ch - 'a'] %= MOD;
                        }
                    }
                }
            }
        }
        
        int res = 0;
        for (int x : dp[0][n - 1]) res += x, res %= MOD;
        return res;
    }
};
```

