#include "leetcode.h"
#include <algorithm>
#define getid(i, j) ((i)*cols + (j))
class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        const int rows = grid.size();
        if (rows == 0)
            return 0;
        const int cols = grid[0].size();
        const int waterField = rows * cols;
        vector<int> root(rows * cols + 1, -1);

        // preparation
        for (auto &v : grid)
            v.push_back('0');
        grid.push_back(vector<char>(cols + 1, '0'));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == '1')
                {
                    if (grid[i][j + 1] == '1')
                        merge(root, getid(i, j), getid(i, j + 1));
                    if (grid[i + 1][j] == '1')
                        merge(root, getid(i, j), getid(i + 1, j));
                }
                else
                {
                    merge(root, waterField, getid(i, j));
                }
            }
        }
        return count(root.begin(), root.end(), -1) - 1;
    }

    int find(vector<int> &r, int x)
    {
        // return (r[x] == -1) ? (x) : (r[x] = find(r, r[x]));
        int t = -1, p = x;
        while (r[p] != -1)
            p = r[p];
        while (x != p)
            t = r[x], r[x] = p, x = t;
        return p;
    }

    void merge(vector<int> &r, int x, int y)
    {
        int a = find(r, x);
        int b = find(r, y);
        if (a != b)
            r[b] = a;
    }
};

int main()
{
}