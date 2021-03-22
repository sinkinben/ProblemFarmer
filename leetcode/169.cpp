#include "leetcode.h"
class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        int candidate = nums.front();
        int flag = 0;
        for (auto x : nums)
        {
            if (flag == 0)
                candidate = x;
            flag += (candidate == x) ? (1) : (-1);
        }
        return candidate;
    }
};

int main()
{
    Solution s;
    vector<int> v({7, 7, 5, 7, 5, 1, 5, 7, 5, 5, 7, 7, 5, 5, 5, 5});
    cout << s.majorityElement(v) << endl;
}