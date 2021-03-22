#include "leetcode.h"
class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        return loopSolution(s, t);
        int slen = s.length(), tlen = t.length();
        vector<vector<int>> dp(slen + 1, vector<int>(tlen + 1, 0));
        int maxval = 0;
        for (int i = 1; i <= slen; i++)
        {
            for (int j = 1; j <= tlen; j++)
            {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                maxval = max(maxval, dp[i][j]);
            }
        }
        return maxval == slen;
    }

    bool loopSolution(string &s, string &t)
    {
        int i = 0, j = 0;
        int slen = s.length(), tlen = t.length();
        while (i < slen && j < tlen)
        {
            if (s[i] == t[j])
                i++;
            j++;
        }
        return i == slen;
    }
};
