#include "leetcode.h"
class Solution
{
public:
    int totalHammingDistance(vector<int> &nums)
    {
        size_t len = nums.size();
        vector<int> countOne(32, 0);
        for (auto x : nums)
        {
            for (int i = 0; i < 32; i++)
                countOne[i] += (x >> i) & 0x1;
        }
        int sum = 0;
        for (int i = 0; i < 32; i++)
            sum += countOne[i] * (len - countOne[i]);
        return sum;
    }

    int hammingDistance(int a, int b)
    {
        int k = a ^ b;
        int t = 0;
        while (k)
            t++, k &= (k - 1);
        return t;
    }
};

int main()
{
    Solution s;
    vector<int> v({4, 14, 2});
    cout << s.totalHammingDistance(v) << endl;
}