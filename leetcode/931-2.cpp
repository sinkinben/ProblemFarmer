#include "leetcode.h"
class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &A)
    {
        if (A.size() == 0 || A[0].size() == 0)
            return 0;
        vector<vector<int>> dp(A);
        int rows = A.size();
        int cols = A[0].size();
        for (int i = 1; i < rows; i++)
        {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + A[i][0];
            dp[i][cols - 1] = min(dp[i - 1][cols - 1], dp[i - 1][cols - 2]) + A[i][cols - 1];
            for (int j = 1; j < (cols - 1); j++)
                dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i - 1][j + 1])) + A[i][j];
        }
        int minval = dp[rows - 1][0];
        for (int x : dp[rows - 1])
            minval = min(minval, x);
        return minval;
    }
};