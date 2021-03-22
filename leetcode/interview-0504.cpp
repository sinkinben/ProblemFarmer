#include "leetcode.h"
#include <vector>
#include <bitset>
class Solution
{
public:
    vector<int> findClosedNumbers(int n)
    {
        vector<int> v({-1, -1});
        if (n == 0 || n == 0x7fffffff)
            return v;
        v[0] = bigger(n), v[1] = smaller(n);
        cout << v[0] << ' ' << v[1] << endl;
        return v;
    }
    int bigger(int n)
    {
        bitset<32> bits(n);
        int i = 0;
        while (bits[i] == 0)
            i++;
        int t = i;
        while (i < 31 && bits[i] == 1)
            i++;
        if (i >= 31)
            return -1;
        int ones = i - t;
        bits[i] = 1, bits[i - 1] = 0;
        uint32_t mask = ~((1 << (i - 1)) - 1);
        bits &= mask;
        i = 0;
        while (--ones)
            bits[i++] = 1;
        return (int)bits.to_ulong();
    }
    int smaller(int n)
    {
        bitset<32> bits(n);
        int i = 0;
        while (bits[i] == 0)
            i++;
        int j = i - 1;
        if (j != -1)
        {
            // ...1000 的形式
            bits[i] = 0, bits[j] = 1;
            return (int)bits.to_ulong();
        }
        else
        {
            // 到这里说明 i=0
            // ..0...1 的形式
            // 一共 i 个 1
            //肯定有 0, 不必担心越界
            while (bits[i] == 1)
                i++;
            int ones = i;

            while (i < 31 && bits[i] == 0)
                i++;
            // i=31, 可确定n=1
            if (i == 31)
                return -1;
            bits[i] = 0, bits[i - 1] = 1;
            uint32_t mask = ~((1 << (i - 1)) - 1);
            bits &= mask;
            while (ones--)
                bits[i - 2] = 1, i--;
            return (int)bits.to_ulong();
        }
    }

    void printBits(int num)
    {
        bitset<32> bits(num);
        cout << bits << endl;
    }
};

int main()
{
    // int n = 0x7fffffff ^ (1 << 3);
    int n = 1156403390;
    Solution s;

    auto x = s.findClosedNumbers(n);

    s.printBits(n);
    s.printBits(x[0]);
    s.printBits(x[1]);
    cout << endl;

    s.printBits(n);
    s.printBits(1156403407);
    s.printBits(1156403389);
}