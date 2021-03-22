#include "leetcode.h"
class Solution
{
public:
    vector<int> printNumbers(int n)
    {
        char str[n + 1];
        memset(str, '0', n);
        str[n] = '\0';
        while (increment(str, n))
            print(str, n);
        return vector<int>();
    }

    void print(char str[], int n)
    {
        int i = n - 1;
        while (i >= 0 && str[i] == '0')
            i--;
        assert(i != -1);
        while (i >= 0)
            cout << str[i--];
        cout << endl;
    }

    bool increment(char str[], int size)
    {
        int cur = str[0] - '0' + 1;
        if (cur <= 9)
        {
            str[0] = cur + '0';
            return true;
        }
        else
        {
            int inbit = 1;
            int i = 0;
            str[i] = '0';
            while (inbit)
            {
                i++;
                cur = str[i] - '0' + inbit;
                inbit = (cur >= 10);
                str[i] = (inbit ? ('0') : (cur + '0'));
                if (i == size - 1 && inbit)
                    return false;
            }
            return true;
        }
    }
};

int main()
{
    Solution sol;
    sol.printNumbers(6);
}