#include "leetcode.h"
#include <algorithm>
class Solution
{
public:
    int countSquares(vector<vector<int>> &matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return 0;
        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<vector<int>> dp(matrix);
        int sum = 0;
        for (int i = 1; i < rows; i++)
        {
            for (int j = 1; j < cols; j++)
            {
                if (matrix[i][j] == 1)
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                else
                    dp[i][j] = 0;
                sum += dp[i][j];
            }
        }

        for (int i = 0; i < rows; i++)
            sum += dp[i][0];
        for (int j = 1; j < cols; j++)
            sum += dp[0][j];
        for (auto &v : dp)
        {
            for (int x : v)
                cout << x << ' ';
            cout << endl;
        }
        return sum;
    }
    int spaceOptimize(vector<vector<int>> &matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return 0;
        int rows = matrix.size();
        int cols = matrix[0].size();
        int sum = 0;
        vector<int> pre(matrix[0]);
        vector<int> cur(cols, 0);
        for (int i = 1; i < rows; i++)
        {
            cur[0] = matrix[i][0];
            for (int j = 1; j < cols; j++)
            {
                if (matrix[i][j] == 1)
                    cur[j] = 1 + min(cur[j - 1], min(pre[j], pre[j - 1]));
                else
                    cur[j] = 0;
                sum += cur[j];
            }
            pre = cur;
        }
        for (int j = 0; j < cols; j++)
            sum += matrix[0][j];
        for (int i = 1; i < rows; i++)
            sum += matrix[i][0];
        return sum;
    }
};

int main()
{
    vector<vector<int>> m = {{0, 1, 1, 1},
                             {1, 1, 1, 1},
                             {0, 1, 1, 1}};
    Solution sol;
    cout << sol.countSquares(m) << endl;
}