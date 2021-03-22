#include "../leetcode.h"
#include <unordered_map>
class Solution
{
public:
    int paintingPlan(int n, int k)
    {
        if (k == n*n)
            return 1;
        int limit = 1 << n;
        int x, y;
        unordered_map<int, int> m;
        for (int i = 0; i < limit; i++)
        {
            for (int j = 0; j < limit;j++)
            {
                x = popcount(i), y = popcount(j);
                if ((x + y) * n - x * y == n*n)
                    cout << i << ' ' << j << endl;
                m[(x + y) * n - x * y]++;
            }
        }
        return m[k];
    }

    int popcount(int x)
    {
        int k = 0;
        while (x!=0)
            x = x & (x - 1), k++;
        return k;
    }
};

int main()
{
    int n = 2, k = 4;
    Solution sol;
    cout << sol.paintingPlan(n, k) << endl;
}