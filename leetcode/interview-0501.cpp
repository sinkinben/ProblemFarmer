#include "leetcode.h"
class Solution
{
public:
    int insertBits(int N, int M, int i, int j)
    {
        uint32_t mask = ~((0xffffffff >> (32 - (j - i + 1))) << i);
        return (N & mask) | (M << i);
    }

    void printbits(uint32_t n)
    {
        for (int i = 31; i >= 0; i--)
        {
            cout << ((n >> i) & 0x1);
        }
        cout << endl;
    }
};
int main()
{
    Solution s;
    cout << s.insertBits(1143207437, 1017033, 11, 31) << endl;
    s.printbits(2082885133);
}
