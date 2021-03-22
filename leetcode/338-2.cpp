#include "leetcode.h"
/*
    v[i] 表示 数字 i 的 1 的个数
    那么：
    v[i] = v[i>>1] + (i&0x1)
 */
class Solution
{
public:
    vector<int> countBits(int num)
    {
        vector<int> v(num + 1, 0);
        for (int i = 0; i <= num; i++)
            v[i] = v[i >> 1] + (i & 0x1);
        return v;
    }
};