#include "leetcode.h"
class Solution
{
public:
    int rows = 0, cols = 0, limit = 0;
    int ans = 0;
    int movingCount(int m, int n, int k)
    {
        rows = m, cols = n, limit = k;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        dfs(visited, 0, 0);
        return ans;
    }

    int calculate(int x, int y)
    {
        int t = 0;
        while (x)
            t += (x % 10), x /= 10;
        while (y)
            t += (y % 10), y /= 10;
        return t;
    }

    void dfs(vector<vector<bool>> &visited, int x, int y)
    {
        if (visited[x][y])
            return;
        visited[x][y] = true, ans++;
        if (x + 1 < rows && calculate(x + 1, y) <= limit)
            dfs(visited, x + 1, y);
        if (x - 1 >= 0 && calculate(x - 1, y) <= limit)
            dfs(visited, x - 1, y);
        if (y + 1 < cols && calculate(x, y + 1) <= limit)
            dfs(visited, x, y + 1);
        if (y - 1 >= 0 && calculate(x, y - 1) <= limit)
            dfs(visited, x, y - 1);
    }
};