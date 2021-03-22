#include "leetcode.h"
class Solution
{
public:
    vector<int> xorQueries(vector<int> &arr, vector<vector<int>> &queries)
    {
        size_t len = arr.size();
        vector<vector<int>> dp(len + 1, vector<int>(len + 1, 0));
        for (int i = 0; i <= len; i++)
        {
            dp[i][i] = arr[i];
            for (int j = i + 1; j <= len; j++)
                dp[i][j] = dp[i][j - 1] ^ arr[j];
        }

        vector<int> v;
        for (auto &x : queries)
        {
            v.push_back(dp[x[0]][x[1]]);
        }
        return v;
    }
    vector<int> xorQueries2(vector<int> &arr, vector<vector<int>> &queries)
    {
        size_t len = arr.size();
        int dp = 0;
        for (int i = 0; i <= len; i++)
        {
            dp = arr[i];
            for (int j = i + 1; j <= len; j++)
                dp ^= arr[i];
        }

        vector<int> v;
        return v;
    }
};

int main()
{
    Solution s;
    vector<int> arr({4, 8, 2, 10});
    vector<vector<int>> q({{2, 3}, {1, 3}, {0, 0}, {0, 3}});
    auto v = s.xorQueries(arr, q);
    for (auto x : v)
    {
        cout << x << endl;
    }
}