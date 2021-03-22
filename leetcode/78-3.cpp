#include "leetcode.h"
class Solution
{
public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> vv;
        int total = 1 << nums.size();
        for (int i = 0; i < total; i++)
        {
            vv.push_back(getItem(i, nums));
        }

        return vv;
    }

    vector<int> getItem(int n, const vector<int> &nums)
    {
        vector<int> v;
        for (int i = 0; i < nums.size(); i++)
        {
            if ((n >> i) & 0x1)
                v.push_back(nums[i]);
        }
        return v;
    }
};
int main()
{
    Solution s;
    vector<int> v({1, 2, 3});
    auto vv = s.subsets(v);
    printvv(vv);
    cout << vv.size() << endl;
}