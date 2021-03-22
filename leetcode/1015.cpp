#include "leetcode.h"
class Solution
{
public:
    int smallestRepunitDivByK(int K)
    {
        if (K % 2 == 0 || K % 5 == 0)
            return -1;
        int len = 1;
        int num = 1;
        while (num < K)
            num = num * 10 + 1, len++;
        while (1)
        {
            if (num % K == 0)
                return len;
            num = (num * 10) + 1;
            num %= K;
            len++;
        }
    }
};
int main()
{
    Solution sol;
    printf("%d\n", sol.smallestRepunitDivByK(17));
    for (int i = 1; i < 100; i += 2)
    {

        printf("%d %d\n", i, sol.smallestRepunitDivByK(i));
    }
}