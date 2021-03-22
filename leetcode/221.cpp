#include "leetcode.h"
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        if (matrix.size() == 0)
            return 0;
        int rows = matrix.size();
        int cols = matrix[0].size();
        int maxval = 0;
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        for (int j = 0; j < cols; j++)
            dp[0][j] = (matrix[0][j] == '1'), maxval = max(maxval, dp[0][j]);
        for (int i = 0; i < rows; i++)
            dp[i][0] = (matrix[i][0] == '1'), maxval = max(maxval, dp[i][0]);
        for (int i = 1; i < rows; i++)
        {
            for (int j = 1; j < cols; j++)
            {
                if (matrix[i][j] == '1')
                    dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
                else
                    dp[i][j] = 0;
                maxval = max(maxval, dp[i][j]);
            }
        }
        for (auto v : dp)
        {
            for (int x : v)
                cout << x << ' ';
            cout << endl;
        }
        return maxval * maxval;
    }
};

int main()
{
    // vector<vector<char>> m = {{'1', '0', '1', '0', '0'},
    //                           {'1', '0', '1', '1', '1'},
    //                           {'1', '1', '1', '1', '1'},
    //                           {'1', '0', '0', '1', '0'}};
    vector<vector<char>> m = {{'0', '1', '1', '1'},
                              {'1', '1', '1', '1'},
                              {'0', '1', '1', '1'}};
    Solution sol;
    cout << sol.maximalSquare(m) << endl;
}