#include "leetcode.h"
class Solution
{
public:
    bool isPowerOfFour(int n)
    {
        return (n >= 1) && ((n & (n - 1)) == 0) && ((n & 0xAAAAAAAA) == 0);
    }
};

int main()
{
    Solution s;
    cout << s.isPowerOfFour(256) << endl;
}