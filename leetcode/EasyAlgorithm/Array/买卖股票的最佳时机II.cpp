class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.size() == 0)
            return 0;
        int dp0 = 0, dp1 = -prices[0];
        for (int x : prices)
            dp0 = max(dp0, dp1 + x), dp1 = max(dp1, dp0 - x);
        return dp0;
    }
};
/*
 *  dp0[i][k] = max(dp0[i-1][k], dp1[i-1][k] + prices[i])
 *  dp1[i][k] = max(dp1[i-1][k], dp0[i-1][k-1] - prices[i])
 *  ==>
 *  dp0[i] = max(dp0[i-1], dp1[i-1] + p[i])
 *  dp1[i] = max(dp1[i-1], dp0[i-1] - p[i])
 *  ==>
 *  dp0 = max(dp0, dp1 + p[i])
 *  dp1 = max(dp1, dp0 - p[i])
 */