#include "leetcode.h"
#include <algorithm>
class Solution
{
public:
    int lastStoneWeightII(vector<int> &stones)
    {
        int sum = 0;
        for (int x : stones)
            sum += x;
        int len = stones.size();
        int volume = sum / 2;
        vector<vector<int>> dp(len + 1, vector<int>(volume + 1, 0));
        for (int i = 1; i <= len; i++)
        {
            for (int j = 1; j <= volume; j++)
            {
                if (j >= stones[i - 1])
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }
        return abs(sum - 2 * dp.back().back());
    }
};
int main()
{
    vector<int> v = {31, 26, 33, 21, 40};
    Solution s;
    cout << s.lastStoneWeightII(v);
}
