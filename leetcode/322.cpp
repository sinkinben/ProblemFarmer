#include "leetcode.h"
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int len = coins.size();
        vector<int> dp(amount + 1, -1);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++)
        {
            for (int x : coins)
            {
                if (i >= x && dp[i - x] != -1)
                {
                    if (dp[i] == -1)
                        dp[i] = dp[i - x] + 1;
                    else
                        dp[i] = min(dp[i], dp[i - x] + 1);
                }
            }
        }
        return dp[amount];
    }
    int coinChange2(vector<int> &coins, int amount)
    {
        const int inf = 0x3f3f3f3f;
        int len = coins.size();
        vector<int> dp(amount + 1, inf);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++)
        {
            for (int x : coins)
            {
                if (i >= x)
                    dp[i] = min(dp[i], dp[i - x] + 1);
            }
        }
        return dp[amount] >= inf ? -1 : dp[amount];
    }
};

int main()
{
    vector<int> coins{2, 5, 10, 1};
    int amount = 27;
    Solution sol;
    cout << sol.coinChange(coins, amount) << endl;
    cout << sol.coinChange2(coins, amount) << endl;
}
