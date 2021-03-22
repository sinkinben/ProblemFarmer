/*
    DP解法
    结果发现时空效率还是不如暴力枚举
 */
#include "leetcode.h"
class Solution
{
public:
    string longestPalindrome(string s)
    {
        int len = s.length();
        if (len == 0 || len == 1)
            return s;
        if (len == 2)
        {
            if (s[0] == s[1])
                return s;
            else
                return s.substr(0, 1);
        }
        vector<vector<int>> dp(len + 1, vector<int>(len + 1, 0));
        int maxlen = 1;
        int start = 0;
        for (int i = 0; i <= len - 2; i++)
        {
            dp[i][i] = 1;
            if ((dp[i][i + 1] = (s[i] == s[i + 1])))
                start = i, maxlen = 2;
        }

        for (int d = 2; d < len; d++)
        {
            for (int i = 0; i < (len - d); i++)
            {
                int j = i + d;
                if (dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]))
                {
                    if (maxlen < (j - i + 1))
                        maxlen = (j - i + 1), start = i;
                }
            }
        }
        cout << start << endl;
        cout << maxlen << endl;
        return s.substr(start, maxlen);
    }
};

int main()
{
    Solution sol;
    cout << sol.longestPalindrome("cbbd") << endl;
}
/*
    dp[i,j] means: str[i...j] is palindrome or not. 
    so:
    dp[i,i] = 1
    do[i,i+1] = (s[i]==s[i+1])
    dp[i,j] = (dp[i+1,j-1])&&(s[i]==s[j])
 */