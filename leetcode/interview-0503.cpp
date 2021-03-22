#include "leetcode.h"
#include <bitset>
#include <regex>
#define bit(n, i) (((n) >> (i)) & 0x1)
class Solution
{
public:
    int reverseBits(int num)
    {
        int len = 0;
        bitset<32> bits(num);
        for (int i = 0; i < 32; i++)
        {
            if (bits[i] == 0)
            {
                bits[i] = 1;
                len = max(len, count((uint32_t)bits.to_ulong()));
                bits[i] = 0;
            }
        }
        return len;
    }

    int count(uint32_t n)
    {
        if (((int)n) == -1)
            return 32;
        if (n & (n - 1) == 0)
            return 1;
        int idx = 0;
        int len = 0;
        while (idx < 32 && bit(n, idx) == 0)
            idx++;

        for (int i = idx; i < 32; i++)
        {
            if (bit(n, i) == 0)
            {
                cout << idx << endl;
                len = max(len, i - idx);
                while (i < 32 && bit(n, i) == 0)
                    i++;
                idx = i;
            }
        }
        return len;
    }
};

int main()
{
    Solution s;
    // cout << s.reverseBits(0) << endl;
    cout << s.count(0x80000000) << endl;
}