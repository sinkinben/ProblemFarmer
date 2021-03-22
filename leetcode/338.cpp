#include "leetcode.h"
class Solution
{
public:
    vector<int> countBits(int num)
    {
        vector<int> v(num + 1);
        for (int i = 0; i <= num; i++)
        {
            v[i] = v[i >> 1] + (i & 0x1);
        }
        return v;
    }
};