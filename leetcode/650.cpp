#include "leetcode.h"
#include <cmath>
class Solution
{
public:
    int minSteps(int n)
    {

        vector<int> dp(n + 1, 0);
        for (int i = 2; i <= n; i++)
        {
            dp[i] = i;
            for (int a = 2; a * a <= i; a++)
            {
                if (i % a == 0)
                {
                    int b = i / a;
                    // dp[i] = min(dp[i], min(dp[a] + b, dp[b] + a));
                    dp[i] = min(dp[i], dp[b] + a);
                }
            }
        }
        return dp[n];
    }

    int minSteps2(int n)
    {
        int k = 0;
        int d = 2;
        while (n > 1)
        {
            while (n % d == 0)
            {
                k += d;
                n /= d;
            }
            d++;
        }
        return k;
    }
};

int main()
{
    Solution sol;
    cout << sol.minSteps(111) << endl;
    cout << sol.minSteps(100) << endl;
    cout << sol.minSteps2(111) << endl;
    cout << sol.minSteps2(100) << endl;
}
