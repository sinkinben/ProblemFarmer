#include "leetcode.h"
class Solution
{
public:
    int rows, cols;
    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {

        rows = mat.size();
        cols = mat[0].size();
        vector<vector<int>> prefix(rows, vector<int>(cols, 0));
        prefix[0][0] = mat[0][0];
        for (int j = 1; j < cols; j++)
            prefix[0][j] = mat[0][j] + prefix[0][j - 1];
        for (int i = 1; i < rows; i++)
            prefix[i][0] = mat[i][0] + prefix[i - 1][0];
        for (int i = 1; i < rows; i++)
            for (int j = 1; j < cols; j++)
                prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + mat[i][j];

        vector<vector<int>> ans(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                ans[i][j] = getval(i + k, j + k, prefix) - getval(i - k - 1, j + k, prefix) -
                            getval(i + k, j - k - 1, prefix) + getval(i - k - 1, j - k - 1, prefix);
            }
        }
        return ans;
    }

    int getval(int x, int y, vector<vector<int>> &prefix)
    {
        if (x < 0 || y < 0)
            return 0;
        else
            return prefix[min(x, rows - 1)][min(y, cols - 1)];
    }
};

int main()
{
    vector<vector<int>> m = {{1, 2, 3},
                             {4, 5, 6},
                             {7, 8, 9}};
    Solution sol;
    auto x = sol.matrixBlockSum(m, 1);
    cout << endl;
    for (auto &v : x)
    {
        for (int t : v)
            printf("%4d", t);
        cout << endl;
    }
}