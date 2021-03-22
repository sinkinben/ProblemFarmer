#include "leetcode.h"
/*
    卡特兰数
    h(0)=h(1)=1
    h(n)=h(0)h(n-1)+h(1)h(n-2)+...+h(n-1)h(0)
 */
class Solution
{
public:
    int numTrees(int n)
    {
        if (n == 0 || n == 1)
            return 1;
        vector<uint64_t> catalan(n + 1, 0);
        catalan[0] = catalan[1] = 1;
        for (int N = 2; N <= n; N++)
        {
            for (int j = 0; j <= N - 1; j++)
            {
                catalan[N] += catalan[j] * catalan[N - j - 1];
            }
        }
        return catalan.back();
    }

    /*
        递推公式
        C[0] = 1
        C[n] = 2(2n-1)*C[n-1]/(n+1)
     */
    int numTrees2(int N)
    {
        int c = 1;
        for (int i = 1; i <= N; i++)
        {
            c = 2 * (2 * i - 1) * c / (i + 1);
        }
        return c;
    }
};
int main()
{
    Solution sol;
    for (int i = 0; i < 10; i++)
        cout << sol.numTrees(i) << ' ' << sol.numTrees2(i) << endl;
}