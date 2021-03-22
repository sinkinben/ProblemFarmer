#include "leetcode.h"
/*
    f[n] = n if n=0 or n=1
    f[2] = 2 
    f[n] = f[n-1]+f[n-2]
 */
class Solution
{
public:
    int climbStairs(int n)
    {
        int a = 0, b = 1;
        int c = a + b;
        if (n == 0)
            return a;
        else if (n == 1)
            return b;
        for (int i = 1; i <= n; i++)
        {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
};
int main()
{
    Solution sol;
    cout << sol.climbStairs(45) << endl;
}