#include "leetcode.h"
class Solution
{
public:
    int numRollsToTarget(int d, int f, int target)
    {
        const uint32_t mod = 1000000007;
        vector<vector<uint32_t>> dp(d + 1, vector<uint32_t>(target + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= d; i++)
        {
            for (int j = i; j <= target; j++)
            {
                for (int k = 1; k <= f; k++)
                {
                    if (j >= k)
                    {
                        dp[i][j] += dp[i - 1][j - k];
                        dp[i][j] %= mod;
                    }
                }
            }
        }
        return dp[d][target];
    }
};
int main()
{
    int d = 1, f = 6, t = 3;
    Solution sol;
    cout << sol.numRollsToTarget(d, f, t) << endl;
}