#include "leetcode.h"
/*
    龙鸣递归解法，超时了
 */
class Solution
{
public:
    int climbStairs(int n)
    {
        if (n == 1 || n == 0)
            return n;
        else if (n == 2)
            return 2;
        return climbStairs(n - 1) + climbStairs(n - 2);
    }
};

int main()
{
    Solution sol;
    cout << sol.climbStairs(3) << endl;
}