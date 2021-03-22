#include <sstream>
#include <iomanip>
#include "leetcode.h"
class Solution
{
public:
    vector<string> readBinaryWatch(int num)
    {
        vector<string> vs;
        for (uint16_t bits = 0; bits < 2048; bits++)
        {
            int h = bits >> 6;
            int m = (bits & 0x3f);
            if (0 <= h && h <= 11 && 0 <= m && m <= 59 && countOne(bits) == num)
                vs.push_back(format(h, m));
        }
        return vs;
    }

    string format(int h, int m)
    {
        stringstream ss;
        ss << h << ":";
        ss << setfill('0') << setw(2) << m;
        return ss.str();
    }

    int countOne(int n)
    {
        int k = 0;
        while (n)
            n &= (n - 1), k++;
        return k;
    }
};
int main()
{
    Solution s;
    int n = 1;
    auto vs = s.readBinaryWatch(n);
    for (auto x : vs)
        cout << x << endl;
}