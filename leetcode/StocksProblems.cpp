#include "leetcode.h"
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        // return maxProfit4(prices);
    }
    int maxProfit1(vector<int> &prices)
    {
        if (prices.size() == 0)
            return 0;
        int dp0 = 0, dp1 = -prices[0];
        for (int x : prices)
        {
            dp0 = max(dp0, dp1 + x);
            dp1 = max(dp1, -x);
        }
        return dp0;
    }
    int maxProfit2(vector<int> &prices)
    {
        if (prices.size() == 0)
            return 0;
        int dp0 = 0, dp1 = -prices[0], t;
        for (int x : prices)
            t = dp0, dp0 = max(dp0, dp1 + x), dp1 = max(dp1, t - x);
        return dp0;
    }
    int maxProfit3(vector<int> &prices)
    {
        if (prices.size() == 0)
            return 0;
        vector<int> v(prices.size(), 0); // which is dp0 at above
        int t = -prices[0];              // which is dp1 at above
        int n = prices.size();
        for (int i = 1; i < n; i++)
        {
            v[i] = max(v[i - 1], t + prices[i]);
            t = max(t, -prices[i]);
        }
        int dp0 = 0, dp1 = -prices[0];
        for (int i = 1; i < n; i++)
        {
            dp0 = max(dp0, dp1 + prices[i]);
            dp1 = max(dp1, v[i - 1] - prices[i]);
        }
        return dp0;
    }
    int maxProfit3Version2(vector<int> &prices)
    {
        if (prices.size() == 0)
            return 0;
        int dp20 = 0, dp10 = 0, dp21 = -prices[0], dp11 = -prices[0];
        for (int x : prices)
        {
            dp20 = max(dp20, dp21 + x);
            dp21 = max(dp21, dp10 - x);
            dp10 = max(dp10, dp11 + x);
            dp11 = max(dp11, -x);
        }
        return dp20;
    }

    int maxProfit4(int K, vector<int> &prices)
    {
        if (prices.size() == 0)
            return 0;
        int n = prices.size();
        vector<vector<int>> dp0(n, vector<int>(K + 1, 0));
        vector<vector<int>> dp1(n, vector<int>(K + 1, 0));
        const int MINVAL = 0x80000000;
        dp0[0][0] = 0, dp1[0][0] = MINVAL;
        for (int k = 1; k <= K; k++)
            dp0[0][k] = 0, dp1[0][k] = -prices[0];
        for (int i = 1; i < n; i++)
            dp0[i][0] = 0, dp1[i][0] = MINVAL;
        for (int i = 1; i < n; i++)
        {
            for (int k = 1; k <= K; k++)
            {
                dp0[i][k] = max(dp0[i - 1][k], dp1[i - 1][k] + prices[i]);
                dp1[i][k] = max(dp1[i - 1][k], dp0[i - 1][k - 1] - prices[i]);
            }
        }
        printvv<int>(dp0);
        return dp0[n - 1][K];
    }
    int maxProfit4Version2(int K, vector<int> &prices)
    {
        if (prices.size() == 0)
            return 0;
        if (K >= prices.size() / 2)
            return maxProfit2(prices);
        const int minval = 0x80000000;
        int n = prices.size();
        vector<int> dp0(K + 1, 0);
        vector<int> dp1(K + 1, -prices[0]);
        dp0[0] = 0, dp1[0] = minval;
        for (int i = 1; i < n; i++)
        {
            for (int k = K; k >= 1; k--)
            {
                dp0[k] = max(dp0[k], dp1[k] + prices[i]);
                dp1[k] = max(dp1[k], dp0[k - 1] - prices[i]);
            }
        }
        return dp0[K];
    }

    int maxProfit5(vector<int> &prices)
    {
        if (prices.size() <= 1)
            return 0;
        int n = prices.size();
        vector<int> dp0(n, 0), dp1(n, 0);
        dp0[0] = 0, dp1[0] = -prices[0];
        dp0[1] = max(0, prices[1] - prices[0]);
        dp1[1] = max(-prices[0], -prices[1]);
        for (int i = 2; i < n; i++)
        {
            dp0[i] = max(dp0[i - 1], dp1[i - 1] + prices[i]);
            dp1[i] = max(dp1[i - 1], dp0[i - 2] - prices[i]);
        }
        return dp0.back();
    }
    int maxProfit5Version2(vector<int> &prices)
    {
        if (prices.size() <= 1)
            return 0;
        int n = prices.size();
        int dp0 = 0, dp1 = -prices[0], predp0 = 0;
        int t;
        for (int i = 1; i < n; i++)
        {
            t = dp0;
            dp0 = max(dp0, dp1 + prices[i]);
            dp1 = max(dp1, predp0 - prices[i]);
            predp0 = t;
        }
        return dp0;
    }

    int maxProfit6(vector<int> &prices, int fee)
    {
        if (prices.size() == 0)
            return 0;
        int dp0 = 0, dp1 = -prices[0] - fee;
        int t;
        for (int x : prices)
        {
            t = dp0;
            dp0 = max(dp0, dp1 + x);
            dp1 = max(dp1, t - x - fee);
        }
        return dp0;
    }
};

int main()
{
    vector<int> v = {2, 1, 4};
    Solution sol;
    cout << sol.maxProfit5Version2(v) << endl;
}

