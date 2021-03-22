#include "leetcode.h"
#define getBit(x, i) ((x >> i) & 0x1)
class Solution
{
public:
    int getSum(int a, int b)
    {
        int in = 0;
        int c = 0;
        for (int i = 0; i < 32; i++)
        {
            c |= (getBit(a, i) ^ getBit(b, i) ^ in) << i;
            in = (getBit(a, i) && getBit(b, i)) || (in && getBit(a, i)) || (in && getBit(b, i));
        }
        return c;
    }
};

int main()
{
    Solution s;
    cout << s.getSum(20, 30) << endl;
}