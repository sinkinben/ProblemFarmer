#include "leetcode.h"
class Solution
{
public:
    vector<int> countOneAndZero(const string &s)
    {
        int one = 0;
        for (char x : s)
            one += (x == '1');
        return {(int)s.length() - one, one};
    }
    int findMaxForm(vector<string> &strs, int m, int n)
    {
        int items = strs.size();
        vector<vector<vector<int>>> dp(items + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        for (int k = 1; k <= items; k++)
        {
            auto counter = countOneAndZero(strs[k - 1]);
            for (int i = 0; i <= m; i++)
            {
                for (int j = 0; j <= n; j++)
                {
                    if (i < counter[0] || j < counter[1])
                        dp[k][i][j] = dp[k - 1][i][j];
                    else
                        dp[k][i][j] = max(dp[k - 1][i][j], dp[k - 1][i - counter[0]][j - counter[1]] + 1);
                }
            }
        }
        // for (auto &&vv : dp)
        //     printvv(vv);
        return dp[items][m][n];
    }
};

int main()
{
    vector<string> vs = {"10", "0", "1"};
    int m = 1, n = 1;
    Solution sol;
    cout << sol.findMaxForm(vs, m, n) << endl;
}
