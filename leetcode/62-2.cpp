/*
    dp[i,j]: 表示从(0,0)到(i,j)的路径数目
    dp[0,*] = 1
    dp[*,0] = 1
    dp[i,j] = dp[i-1,j] + dp[i,j-1]

    空间可以优化为O(n)
 */
#include "leetcode.h"
class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        vector<int> dp(n, 1);
        while (--m)
        {
            for (int i = 1; i < n; i++)
            {
                dp[i] = dp[i - 1] + dp[i];
            }
        }
        return dp.back();
    }
};

int main()
{
    Solution sol;
    cout << sol.uniquePaths(7, 3);
}