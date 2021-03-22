#include "leetcode.h"
class Solution
{
public:
    double knightProbability(int N, int K, int r, int c)
    {
        vector<vector<int>> direction = {{2, 1}, {-2, 1}, {2, -1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
        vector<vector<double>> curstep(N, vector<double>(N, 0));
        curstep[r][c] = 1;
        while (K--)
        {
            vector<vector<double>> prestep(curstep);
            curstep = vector<vector<double>>(N, vector<double>(N, 0));
            for (int x = 0; x < N; x++)
            {
                for (int y = 0; y < N; y++)
                {
                    for (auto &v : direction)
                    {
                        int dx = x + v[0], dy = y + v[1];
                        if (0 <= dx && dx < N && 0 <= dy && dy < N)
                            curstep[x][y] += prestep[dx][dy] / 8.0;
                    }
                }
            }
        }
        double sum = 0;
        for (auto &v : curstep)
            for (double p : v)
                sum += p;
        return sum;
    }
};

int main()
{
    int n = 3, k = 2, r = 0, c = 0;
    Solution sol;
    cout << sol.knightProbability(n, k, r, c) << endl;
}