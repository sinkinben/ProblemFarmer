#include "leetcode.h"
class Solution
{
public:
    int rangeBitwiseAnd(uint32_t m, uint32_t n)
    {
        int i = 0;
        while (m < n)
        {
            n &= (n - 1);
            i++;
            cout << n << endl;
        };
        cout << i << endl;
        return n;
    }
};

int main()
{
    Solution s;
    s.rangeBitwiseAnd(0, 0xffffffff);
}