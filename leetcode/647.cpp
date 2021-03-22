#include "leetcode.h"
/*
    提交前需要把所有输出删除，否则输出时间也会算入运行时间
    最长回文串的变体
    dp[i,j] (i...j)是否为回文
    dp[0,0] = 1
    dp[i,i] = 1
    dp[i,j] = 0 if i>j
    dp[i,j] = dp[i+1,j-1]&&s[i]==s[j]
 */
class Solution
{
public:
    int countSubstrings(string s)
    {
        int len = s.length();
        int dp[len][len];
        memset(dp, 0, sizeof(int) * len * len);
        int result = 0;
        for (int i = 0; i < len - 1; i++)
        {
            dp[i][i] = 1;
            dp[i][i + 1] = (s[i] == s[i + 1]);
        }
        dp[len - 1][len - 1] = 1;
        for (int d = 2; d < len; d++)
        {
            for (int i = 0; i < (len - d); i++)
            {
                int j = i + d;
                dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]);
            }
        }
        for (int i = 0; i < len; i++)
        {
            for (int j = i; j < len; j++)
            {
                result += dp[i][j];
            }
        }
        return result;
    }
};
int main()
{
    Solution sol;
    cout << sol.countSubstrings("aaa") << endl;
}