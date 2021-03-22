#include "leetcode.h"
class Sum
{
public:
    static int sum;
    static int n;
    Sum()
    {
        sum += (++n);
    }
};
int Sum::sum = 0;
int Sum::n = 0;
class Solution
{
public:
    int sumNums(int n)
    {
        Sum *s = new Sum[n];
        delete[] s;
        s = nullptr;
        return Sum::sum;
    }
};

int main()
{
    Solution sol;
    cout << sol.sumNums(10) << endl;
}