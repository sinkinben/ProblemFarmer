#include "leetcode.h"
#define getBit(x, i) ((x >> i) & 0x1)
class Solution
{
public:
    bool validUtf8(vector<int> &data)
    {
        for (size_t i = 0; i < data.size();)
        {
            uint8_t byte = data[i] & 0xff;
            int t = unitLength(byte);
            if (t == -1)
                return false;
            if (t == 0 && (byte >> 7) == 0x1)
                return false;
            // read the after t bytes, but i can not out of the data.size()
            while (t--)
            {
                i++;
                if (i >= data.size())
                    return false;
                data[i] &= 0xff;
                if (!((data[i] >> 6) == 2))
                {
                    return false;
                }
            }
            i++;
        }
        return true;
    }

    int unitLength(uint8_t n)
    {
        if ((n & ~0x7F) == 0)
            return 0;
        else if ((n & ~0xDF) == 0)
            return 1;
        else if ((n & ~0xEF) == 0)
            return 2;
        else if ((n & ~0xF7) == 0)
            return 3;
        return -1;
    }
};

int main()
{
    vector<int> v({237});
    Solution s;
    cout << s.validUtf8(v);
}