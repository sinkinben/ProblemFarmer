#include "leetcode.h"
class Solution
{
public:
    bool PredictTheWinner(vector<int> &nums)
    {
        return dpSolution(nums);
    }

    bool dpSolution(vector<int> &v)
    {
        if (v.size() <= 1)
            return true;
        int len = v.size();
        vector<vector<int>> dp(len, vector<int>(len, 0));
        for (int i = 0; i < len; i++)
            dp[i][i] = v[i];
        for (int d = 1; d < len; d++)
        {
            for (int i = 0; i < (len - d); i++)
            {
                int j = i + d;
                dp[i][j] = max(v[i] - dp[i + 1][j], v[j] - dp[i][j - 1]);
            }
        }
        return dp[0][len - 1] >= 0;
    }

    bool rec(vector<int> &v)
    {
        if (v.size() <= 1)
            return true;
        int sum = 0;
        for (int x : v)
            sum += x;
        int alex = f(v, 0, (int)v.size() - 1);
        return alex >= (sum - alex);
    }
    int f(vector<int> &v, int l, int r)
    {
        if (l == r)
            return v[l];
        if (l + 1 == r)
            return max(v[l], v[r]);
        if (l < r)
        {
            // Alex get 1st
            // int a = v[l] + f(v, l+2, r);
            // int b = v[l] + f(v, l+1, r-1);
            // Alex get the last
            // int c = v[r] + f(v, l+1, r-1);
            // int d = v[r] + f(v, l, r-2);
            return max(v[l] + min(f(v, l + 2, r), f(v, l + 1, r - 1)),
                       v[r] + min(f(v, l + 1, r - 1), f(v, l, r - 2)));
        }
        return -1;
    }
};


