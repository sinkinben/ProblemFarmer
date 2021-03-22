#include "leetcode.h"
#define min(a, b) ((a) > (b) ? (b) : (a))
class Solution
{
public:
    int integerReplacement(int num)
    {
        uint32_t n = num;
        int k = 0;
        while (n > 1)
        {
            if (n & 0x1)
                n = ((n & 0x2) == 0) || (n == 3) ? (n - 1) : (n + 1);
            else
                n >>= 1;
            k++;
        }
        return k;
    }
    int integerReplacement2(int n)
    {
        return helper(n);
    }

    int helper(uint32_t n)
    {
        if (n == 1)
            return 0;
        if (n % 2 == 0)
            return 1 + helper(n / 2);
        return 1 + min(helper(n + 1), helper(n - 1));
    }
};
int main()
{
    Solution s;
}