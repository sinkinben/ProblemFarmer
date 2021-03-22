#include "leetcode.h"
/**  dp[i][j] 为 s1 的前 i 字符与 s2 的前 j 字符的编辑距离
 *   dp[i][0] = i, 1<=i<=len(s1)
 *   dp[0][j] = j, 1<=j<=len(s2)
 *   
 *   if s1[i] == s2[j] then dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]+1, di[i][j-1]+1)
 *   else dp[i][j] = min(dp[i-1][j-1]+1, dp[i-1][j]+1, dp[i][j-1]+1)
 **/
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        return dp1(word1, word2);
    }

    int dp1(string &s1, string &s2)
    {
        int len1 = s1.length(), len2 = s2.length();
        if (len1 == 0)
            return len2;
        if (len2 == 0)
            return len1;
        vector<int> dp(len2 + 1, 0);
        for (int j = 1; j <= len2; j++)
            dp[j] = j;
        vector<int> buf(dp);
        for (int i = 1; i <= len1; i++)
        {
            buf[0] = i - 1;
            dp[0] = i;
            for (int j = 1; j <= len2; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                    dp[j] = min(buf[j - 1], min(buf[j], dp[j - 1]) + 1);
                else
                    dp[j] = min(buf[j - 1], min(buf[j], dp[j - 1])) + 1;
            }
            buf = dp;
        }
        return dp.back();
    }

    int dp2(const string &s1, const string &s2)
    {
        int len1 = s1.length(), len2 = s2.length();
        if (len1 == 0)
            return len2;
        if (len2 == 0)
            return len1;

        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
        int i = 0, j = 0;
        for (auto &v : dp)
            v[0] = i++;
        for (int &x : dp[0])
            x = j++;

        for (i = 1; i <= len1; i++)
        {
            for (j = 1; j <= len2; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
                else
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
            }
        }
        return dp[len1][len2];
    }
};
