#include "leetcode.h"
class Solution
{
public:
    int findComplement(int n)
    {
        int k = ~n, t = 0;
        while (n)
            n >>= 1, t++;
        return k & ~((-1) << t);
    }
};
int main()
{
    Solution s;
    cout << s.findComplement(5) << endl;
    cout << s.findComplement(1) << endl;
}