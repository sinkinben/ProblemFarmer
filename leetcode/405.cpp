#include "leetcode.h"
#include <stack>
class Solution
{
public:
    const char *stdstr = "0123456789abcdef";
    string toHex(int n)
    {
        string hex;
        int k = sizeof(int) * 8 / 4 - 1;
        while (k > 0 && (((n >> (4 * k)) & 0x0f) == 0))
            k--;
        while (k >= 0)
        {
            hex.append(1, stdstr[(n >> (4 * k--)) & 0x0f]);
        }
        return hex;
    }
};