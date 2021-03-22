#include "leetcode.h"
class Solution
{
public:
    int exchangeBits(int num)
    {
        for (int i = 30; i >= 0; i -= 2)
        {
            int t = (num >> i) & 0x3;
            if (t == 1 || t == 2)
                num ^= 0x3 << i;
        }
        return num;
    }
};
int main()
{
    Solution s;
    cout << s.exchangeBits(3) << endl;
}
