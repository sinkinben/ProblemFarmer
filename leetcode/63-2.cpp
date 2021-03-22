#include "leetcode.h"
class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int row = obstacleGrid.size();
        int col = obstacleGrid.front().size();
        if (row == 0 || col == 0)
            return 0;
        vector<vector<uint64_t>> dp(row, vector<uint64_t>(col, 0));
        int i = 0;
        while (i < col && obstacleGrid[0][i] == 0)
            dp[0][i++] = 1;
        i = 0;
        while (i < row && obstacleGrid[i][0] == 0)
            dp[i++][0] = 1;
        for (int i = 1; i < row; i++)
        {
            for (int j = 1; j < col; j++)
            {
                if (obstacleGrid[i][j] == 0)
                {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp.back().back();
    }
};

int main()
{
    int a[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    vector<vector<int>> v;
    for (int i = 0; i < 3; i++)
    {
        vector<int> t;
        for (int j = 0; j < 3; j++)
        {
            t.push_back(a[i][j]);
        }
        v.push_back(t);
    }
    Solution sol;
    
    cout << sol.uniquePathsWithObstacles(v) << endl;
    
}