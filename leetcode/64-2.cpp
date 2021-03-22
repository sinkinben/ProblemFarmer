#include "leetcode.h"
/*
    dp[i,j] 表示：从(0,0)到(i,j)的所有路径中的最小和
    dp[0,*] = sum(dp[0,*])
    dp[*,0] = sum(dp[*,0])
    dp[i,j] = min(dp[i-1,j],dp[i,j-1])+a[i][j]
 */
class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int rows = grid.size();
        int cols = grid.front().size();
        int dp[rows][cols];
        dp[0][0] = grid[0][0];

        for (int i = 1; i < cols; i++)
            dp[0][i] = dp[0][i - 1] + grid[0][i];
        for (int j = 1; j < rows; j++)
            dp[j][0] = dp[j - 1][0] + grid[j][0];

        for (int i = 1; i < rows; i++)
        {
            for (int j = 1; j < cols; j++)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[rows - 1][cols - 1];
    }
};
