#include "leetcode.h"
class Solution
{
public:
    int numTrees(int n)
    {
        return dp(n);
    }

    int dp(int n)
    {
        if (n <= 2)
            return n;
        vector<int> catalan(n + 1, 0);
        catalan[0] = catalan[1] = 1, catalan[2] = 2;
        for (int i = 3; i <= n; i++)
            for (int k = 0; k < i; k++)
                catalan[i] += catalan[k] * catalan[i - k - 1];
        return catalan.back();
    }
    int func(int n)
    {
        uint64_t h = 1;
        for (int i = 1; i <= n; i++)
            h = h * 2 * (2 * i - 1) / (i + 1);
        return h;
    }
};
int main()
{
    Solution sol;
    cout << sol.numTrees(3) << endl;
    cout << sol.func(3);
}