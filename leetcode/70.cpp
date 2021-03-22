#include "leetcode.h"
#include <cmath>
class Solution
{
public:
    int climbStairs(int n)
    {
        if (n <= 2)
            return n;
        return climbStairs(n - 1) + climbStairs(n - 2);
    }

    int climbStairs2(int n)
    {
        int a = 0, b = 1, c = 0;
        for (int i = 1; i <= n; i++)
            c = a + b, a = b, b = c;
        return c;
    }
    int climbStairs3(int n)
    {
        n++;
        double sqrt5 = sqrt(5);
        return (int)((pow((1 + sqrt5) / 2, n) - pow((1 - sqrt5) / 2, n)) / sqrt5);
    }
};

int main()
{
    Solution s;
    int a[5] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; i++)
        cout << s.climbStairs2(a[i]) << endl;
}
