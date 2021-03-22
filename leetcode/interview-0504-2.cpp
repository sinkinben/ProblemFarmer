#include "leetcode.h"
class Solution
{
public:
    vector<int> findClosedNumbers(int n)
    {
        vector<int> v({-1, -1});
        if (n == 0 || n == 0x7fffffff)
            return v;
        int t = n;
        int bench = hammingWeight(n);
        while (--t)
        {
            if (hammingWeight(t) == bench)
            {
                v[1] = t;
                break;
            }
        }
        t = n;
        while (++t)
        {
            if (hammingWeight(t) == bench)
            {
                v[0] = t;
                break;
            }
        }
        return v;
    }

    int hammingWeight(uint32_t n)
    {
        int t = 0;
        while (n)
            t++, n &= (n - 1);
        return t;
    }
};