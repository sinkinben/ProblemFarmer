#include "leetcode.h"
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
class Solution
{
public:
    // brute force solution, time limit exceeded
    int maxProfit2(vector<int> &prices)
    {
        int len = prices.size();
        int profit = 0;
        for (int i = 0; i < len; i++)
            for (int j = i + 1; j < len; j++)
                profit = max(profit, prices[j] - prices[i]);
        return profit;
    }
    int maxProfit(vector<int> &prices)
    {
        int minval = 0x7ffffff0;
        int profit = 0;
        int len = prices.size();
        for (int i = 0; i < len; i++)
        {
            minval = min(minval, prices[i]);
            profit = max(profit, prices[i] - minval);
        }
        return profit;
    }
};

int main()
{
    Solution sol;
    vector<int> v({7, 1, 5, 3, 6, 4});
    cout << sol.maxProfit(v) << endl;
}
