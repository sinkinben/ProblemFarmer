#include "leetcode.h"
#define MODNUM (1000000007)
class Solution
{
public:
    int waysToStep(int n)
    {
        if (n <= 1)
            return 1;
        if (n == 2)
            return 2;
        uint64_t f0 = 1, f1 = 1, f2 = 2, f3 = 4;
        for (int i = 3; i <= n; i++)
        {
            f3 = (f0 + f1 + f2) % MODNUM;
            f0 = f1, f1 = f2, f2 = f3;
        }
        return f3;
    }
};

int main()
{
    Solution sol;
    for (int i = 0; i <= 5; i++)
        cout << sol.waysToStep(i) << endl;
}