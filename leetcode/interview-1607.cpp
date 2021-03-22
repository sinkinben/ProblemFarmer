#include "leetcode.h"
#define sign(x) ((((x) >> 31) & 0x1))

class Solution
{
public:
    int maximum(int a, int b)
    {
        uint8_t x1 = sign(a) & (sign(b) ^ 1);
        uint8_t x2 = (sign(a) ^ sign(b) ^ 1) & sign((a + (~b)));
        uint8_t le = x1 | x2;
        return (le ^ 1) * a + b * le;
    }
    int maximum2(int x, int y)
    {
        long a = x, b = y;
        int less = (((a - b) >> 63) & 0x1);
        return (less ^ 1) * a + less * b;
    }
};
int main()
{
    Solution s;
    cout << s.maximum(1, 2) << endl;
    cout << s.maximum(2, 1) << endl;

    cout << s.maximum(31234, 34) << endl;

    cout << s.maximum(0x80000000, 1) << endl;
    cout << s.maximum(3, 0x80000000) << endl;

    cout << s.maximum(0x7fffffff, -1) << endl;
    cout << s.maximum(0x7fffffff, 0x80000000) << endl;
}
