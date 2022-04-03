## Valid Palindrome

Leetcode:

- [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)
- [680. Valid Palindrome II](https://leetcode.com/problems/valid-palindrome-ii/)
- [1216. Valid Palindrome III](https://leetcode-cn.com/problems/valid-palindrome-iii/)



## Valid Palindrome I

A phrase is a **palindrome** if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string `s`, return `true` *if it is a **palindrome**, or* `false` *otherwise*.

 **Example**

```text
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
```

<br/>

**Solution**

```cpp
class Solution {
public:
    bool valid(char &ch) {
        if ('A' <= ch && ch <= 'Z') ch = ch - 'A' + 'a';
        return ('a' <= ch && ch <= 'z') || ('0' <= ch && ch <= '9');
    };
    bool isPalindrome(string s) {
        int n = s.length();
        int l = 0, r = n - 1;

        while (l <= r) {
            while (l <= r && !valid(s[l])) ++l;
            while (r >= l && !valid(s[r])) --r;
            if (l > r) break;
            if (s[l] != s[r]) return false;
            ++l, --r;
        }
        
        return true;
    }
};
```





## Valid Palindrome II

Given a string `s`, return `true` *if the* `s` *can be palindrome after deleting **at most one** character from it*.

**Example - 1**

```text
Input: s = "abca"
Output: true
Explanation: You could delete the character 'c'.
```

**Example - 2**

```text
Input: s = "abc"
Output: false
```

<br/>

**Solution**

- Scan the string `s` in a common way, check whether if `s` is palindrome.
- Once we meet the case `s[l] != s[r]`, check the range `[l + 1, r]` and `[l, r - 1]` . 
- If one of them is valid, the we can make `s` become a valid palindrome by removing at most one character.

```cpp
class Solution
{
public:
    /* Check whether if s[l, ..., r] is palindrome. */
    bool isPal(string &s, int l, int r)
    {
        while (l < r)
        {
            if (s[l] != s[r]) return false;
            ++l, --r;
        }
        return true;
    }

    bool validPalindrome(string s)
    {
        int n = s.length();
        if (n <= 2) return true;
        for (int i = 0; i < n / 2; ++i)
        {
            if (s[i] != s[n - i - 1])
                return isPal(s, i + 1, n - i - 1) || isPal(s, i, n - i - 2);
        }
        return true;
    }
};
```



## Valid Palindrome III

Given a string `s` and an integer `k`, return `true` if `s` is a `k`**-palindrome**.

A string is `k`-palindrome if it can be transformed into a palindrome by removing at most `k` characters from it. `1 <= k <= s.length <= 1000`.

**Example - 1**

```text
Input: s = "abcdeca", k = 2
Output: true
Explanation: Remove 'b' and 'e' characters.
```

**Example - 2**

```text
Input: s = "abbababa", k = 1
Output: true
```

<br/>

**Solution**

It's similar to [516. Longest Palindromic Subsequence](https://leetcode-cn.com/problems/longest-palindromic-subsequence/). 

The problem here is that remove `<= k` characters, let `s` become a palindrome string. It means that `s` contains a palindromic sequence with `length >= n - k`.

Let `dp[i, j]` denote the length of Longest Palindromic Subsequence in range `[i, j]`. Then we have:

```cpp
dp[i, j] = dp[i + 1, j - 1] + 2            if s[i] == s[j]
         = max(dp[i + 1, j], dp[i, j - 1]) otherwise
```

Here is the code.

```cpp
class Solution {
public:
    bool isValidPalindrome(string s, int k) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
        {
            dp[i][i] = 1;
            if (i + 1 < n) dp[i][i + 1] = (s[i] == s[i + 1]) + 1;
        }

        for (int d = 2; d < n; ++d)
        {
            for (int i = 0; i + d < n; ++i)
            {
                int j = i + d;
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
        return dp[0][n - 1] >= n - k;
    }
};
```

