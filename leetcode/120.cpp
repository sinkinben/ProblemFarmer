#include "leetcode.h"
/*
    dp[i,j] 表示 (i,j)到底部的路径的最小值
    dp[i,level-1] = a[i,level-1]
    dp[i,j] = a[i,j] + min(dp[i+1,j], dp[i+1,j+1])

    可优化为 O(n) 的空间
 */
class Solution
{
public:
    int minimumTotal(vector<vector<int>> &triangle)
    {
        vector<vector<int>> dp(triangle);
        int level = triangle.size();
        for (int i = level - 2; i >= 0; i--)
        {
            int cols = triangle[i].size();
            for (int j = 0; j < cols; j++)
                dp[i][j] = triangle[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
        }
        return dp[0][0];
    }

    int minimumTotal2(vector<vector<int>> &triangle)
    {
        vector<int> dp(triangle.back());
        int level = triangle.size();
        int n = dp.size();
        for (int i = level - 2; i >= 0; i--)
        {
            for (int j = 0; j <= i; j++)
            {
                dp[j] = triangle[i][j]+min(dp[j], dp[j+1]);
            }
        }
        return dp.front();
    }
};