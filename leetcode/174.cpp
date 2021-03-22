#include "leetcode.h"
class Solution
{
public:
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        if (dungeon.size() == 0 || dungeon[0].size() == 0)
            return 0;
        int rows = dungeon.size();
        int cols = dungeon[0].size();
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        dp[0][0] = dungeon[0][0];
        for (int i = 1; i < rows; i++)
            dp[i][0] = dungeon[i][0] + dp[i - 1][0];
        for (int j = 1; j < cols; j++)
            dp[0][j] = dungeon[0][j] + dp[0][j - 1];
        for (int i = 1; i < rows; i++)
        {
            for (int j = 1; j < cols; j++)
            {
                
            }
        }
    }
};