#include "leetcode.h"
class Solution
{
public:
    int minFlips(int a, int b, int c)
    {
        int k = (a | b) ^ c;
        int ans = 0;
        // printBits(a), printBits(b), printBits(c), printBits(a | b), printBits(k);
        for (int i = 0; i < 32; i++)
        {
            if ((k >> i) & 0x1)
            {
                if ((c >> i) & 0x1)
                {
                    ans++;
                }
                else
                {
                    ans += (a >> i) & 0x1;
                    ans += (b >> i) & 0x1;
                }
            }
        }
        return ans;
    }

    int countOne(int k)
    {
        int one = 0;
        for (int i = 0; i < 32; i++)
        {
            one += (k >> i) & 0x1;
        }
        return one;
    }

    void printBits(int k)
    {
        cout << setfill('0') << setw(2) << k << ":";
        for (int i = 8; i >= 0; i--)
        {
            cout << ((k >> i) & 0x1);
        }
        cout << endl;
    }
};

int main()
{
    Solution so;
    cout << so.minFlips(8, 3, 5) << endl;
}