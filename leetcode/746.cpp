#include "leetcode.h"
#define min(a, b) (((a) < (b)) ? (a) : (b))
class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        cost.push_back(0);
        int n = cost.size();
        int f0 = cost[0], f1 = cost[1], f2;
        for (int i = 2; i < n; i++)
            f2 = cost[i] + min(f0, f1), f0 = f1, f1 = f2;
        return f2;
    }
};
int main()
{
    int a = 1, b = 2, c = 3;
    int d = (a++, b++, c = c + a + b);

    cout << d << endl;
}
