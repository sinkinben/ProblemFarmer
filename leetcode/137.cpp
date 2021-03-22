#include "leetcode.h"
class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int countBits[32] = {0};
        for (auto x : nums)
        {
            for (int i = 0; i < 32; i++)
            {
                countBits[i] = (countBits[i] + ((x >> i) & 0x1)) % 3;
            }
        }
        int ans = 0;
        for (int i = 0; i < 32; i++)
        {
            ans |= ((countBits[i]) << i);
        }
        return ans;
    }
};

int main()
{
    Solution s;
    vector<int> v({3, 3, 3, 2, 1, 2, 2});
    cout << s.singleNumber(v) << endl;
}