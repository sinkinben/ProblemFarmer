#include "leetcode.h"
#include <algorithm>
class Solution
{
public:
    int mincostTickets(vector<int> &days, vector<int> &costs)
    {
        if (days.size() == 0)
            return 0;
        int lastday = days.back();
        vector<int> dp(lastday + 1, 0);
        vector<bool> flag(lastday + 1, false);
        for (int d: days)
            flag[d] = true;
        dp[0] = 0;
        for (int i = 1; i <= lastday; i++)
        {
            if (!flag[i])
                dp[i] = dp[i - 1];
            else
            {
                dp[i] = dp[i - 1] + costs[0];
                dp[i] = min(dp[i], ((i >= 7) ? dp[i - 7] : 0) + costs[1]);
                dp[i] = min(dp[i], ((i >= 30) ? dp[i - 30] : 0) + costs[2]);
            }
        }
        return dp.back();
    }
};

int main()
{
    vector<int> days = {1, 4, 6, 7, 8, 20};
    vector<int> costs = {2, 3, 15};
    Solution sol;
    cout << sol.mincostTickets(days, costs) << endl;
}
