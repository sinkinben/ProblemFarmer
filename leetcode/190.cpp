#include "leetcode.h"
class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t ans = 0;
        for (int i = 0; i < 32; i++)
        {
            ans = ans << 1;
            ans |= ((n >> i) & 0x1);
        }
        return ans;
    }
};

int main()
{
    Solution s;
    cout << s.reverseBits(43261596) << endl;
}