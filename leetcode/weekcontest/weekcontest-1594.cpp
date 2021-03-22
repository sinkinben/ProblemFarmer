#include "../leetcode.h"
#define max(a, b) ((a) > (b)) ? (a) : (b)
class Solution
{
public:
    int rows, cols;
    int64_t ans = -1;
    const int mod = ((int)1e9 + 7);
    int maxProductPath(vector<vector<int>> &grid)
    {
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;
        rows = grid.size();
        cols = grid[0].size();
        dfs(grid, 0, 0, 1);
        return ans % mod;
    }

    void dfs(vector<vector<int>> &g, int i, int j, int64_t cur)
    {
        if (i == rows || j == cols)
            return;
        cur = (cur * g[i][j]);
        if (cur == 0)
        {
            ans = max(ans, 0);
            return;
        }
        if (i == rows - 1 && j == cols - 1)
        {
            ans = max(ans, cur);
            return;
        }
        dfs(g, i + 1, j, cur);
        dfs(g, i, j + 1, cur);
    }
};

int main()
{
    vector<vector<int>> grid = {{1, -2, 1},
                                {1, -2, 1},
                                {3, -4, 1}};
    vector<vector<int>> g = {{-1, -2, -3},
                             {-2, -3, -3},
                             {-3, -3, -2}};
    g = {{1, 4, 4, 0},
         {-2, 0, 0, 1},
         {1, -1, 1, 1}};
    Solution sol;
    cout << sol.maxProductPath(g);
}