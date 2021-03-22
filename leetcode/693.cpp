#include "leetcode.h"
class Solution
{
public:
    bool hasAlternatingBits(int n)
    {
        while (n)
        {
            if (((n >> 1) & 0x1) == (n & 0x1))
                return false;
            n >>= 1;
        }
        return true;
    }
    bool hasAlternatingBits2(int num)
    {
        unsigned int n = num;
        n = n ^ (n >> 1);
        return ((n + 1) & n) == 0;
    }
};

int main()
{
    Solution s;
    cout << s.hasAlternatingBits(4) << endl;
}
