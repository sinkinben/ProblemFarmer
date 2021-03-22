#include "leetcode.h"
class Solution
{
public:
    int missingNumber(vector<int> &nums)
    {
        nums.push_back(0);
        int k = 0;
        for (size_t i = 0; i < nums.size(); i++)
            k ^= (i ^ nums[i]);
        return k;
    }
};

int main()
{
    vector<int> v1({9, 6, 4, 2, 3, 5, 7, 0, 1});
    vector<int> v2({1, 0, 3});
    Solution s;
    cout << s.missingNumber(v1) << endl;
    cout << s.missingNumber(v2) << endl;
}