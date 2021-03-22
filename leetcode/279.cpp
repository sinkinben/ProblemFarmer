#include "leetcode.h"
#include <cmath>
class Solution
{
public:
    int numSquares(int n)
    {
        const int inf = 0x3f3f3f3f;
        vector<int> dp(n + 1, inf);
        dp[0] = 0, dp[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            int k = sqrt(i);
            if (k * k == i)
                dp[i] = 1;
            else
            {
                dp[i] = i;
                for (int j = 1; j <= (i / 2); j++)
                    dp[i] = min(dp[i], dp[i - j] + dp[j]);
            }
        }
        return dp.back();
    }

    int numSquares2(int n)
    {
        int k = sqrt(n);
        vector<int> list;
        for (int i = 1; i <= k; i++)
            list.push_back(i * i);
        vector<int> dp(n + 1);
        dp[0] = 0, dp[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            if (k * k == i)
                dp[i] = 1;
            else
            {
                dp[i] = i;
                for (int x : list)
                {
                    if (i < x)
                        break;
                    dp[i] = min(dp[i], dp[i - x] + 1);
                }
            }
        }
        return dp.back();
    }
};

int main()
{
    Solution sol;
    cout << sol.numSquares2(8829);
}

