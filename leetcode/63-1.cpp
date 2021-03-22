/*
    2018年能通过
    2019/9/12 int溢出
 */
#include "leetcode.h"
class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &o)
    {
        int m = o.size();
        int n = o[0].size();

        if (o[m - 1][n - 1] == 1)
            return 0;

        int dp[m][n];
        memset(dp, 0, sizeof(dp));

        int i = 0;
        while (i < n && o[0][i] == 0)
            dp[0][i] = 1, i++;
        while (i < n)
            dp[0][i++] = 0;

        int j = 0;
        while (j < m && o[j][0] == 0)
            dp[j++][0] = 1;
        while (j < m)
            dp[j++][0] = 0;

        for (i = 1; i < m; i++)
        {
            for (j = 1; j < n; j++)
            {
                if (o[i][j] == 0)
                    dp[i][j] += dp[i - 1][j] + dp[i][j - 1];
                else
                    dp[i][j] = 0;
            }
        }
        return dp[m - 1][n - 1];
    }
};