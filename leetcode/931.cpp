#include "leetcode.h"
/*
    数塔问题的变体
    dp[i,j]表示(i,j)到最后一层的最小和
    dp[n-1,j] = A[n-1,j]
    if j==0   then dp[i,j] = A[i,j]+min(dp[i+1,j],dp[i+1,j+1])
    if j==n-1 then dp[i,j] = A[i,j]+min(dp[i+1,j],dp[i+1,j-1])
    else
    dp[i,j] = A[i,j]+min(dp[i+1,j],dp[i+1,j-1],dp[i+1,j+1])
 */
class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &A)
    {
        vector<vector<int>> dp(A);
        int n = A.size();
        for (int i = n - 2; i >= 0; i--)
        {
            dp[i][0] = A[i][0] + min(dp[i + 1][0], dp[i + 1][1]);
            for (int j = 1; j <= n - 2; j++)
            {
                dp[i][j] = A[i][j] + min(dp[i + 1][j], min(dp[i + 1][j - 1], dp[i + 1][j + 1]));
            }
            dp[i][n - 1] = A[i][n - 1] + min(dp[i + 1][n - 1], dp[i + 1][n - 2]);
        }
        int result = dp[0][0];
        auto &v = dp.front();
        for (int x:v)
            result = min(x,result);
        return result;
    }
};