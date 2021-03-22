#include "leetcode.h"
class Solution
{
public:
    vector<int> singleNumber(vector<int> &nums)
    {
        int k = 0;
        for (auto x : nums)
            k ^= x;
        int mask = k & (-k);
        int y = 0;

        // find one of {a,b}
        for (auto x : nums)
        {
            if (mask & x) //ignore one of {a,b}
                y ^= x;
        }
        return vector<int>({y, k ^ y});
    }
};

int main()
{
    vector<int> v({1, 2, 1, 3, 2, 5});
    Solution s;
    auto ans = s.singleNumber(v);
    cout << ans[0] << ans[1] << endl;
}