#include "leetcode.h"
class Solution
{
public:
    set<vector<int>> result;
    int len;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<int> v;
        result.insert(v);
        len = nums.size();
        backTrack(nums, 0, v);
        return vector<vector<int>>(result.begin(), result.end());
    }

    void backTrack(const vector<int> &nums, int now, vector<int> subset)
    {
        for (int i = now; i < len; i++)
        {
            subset.push_back(nums[i]);
            result.insert(subset);
            backTrack(nums, i+1, subset);
            subset.pop_back();
        }
    }
};
int main()
{
    int a[] = {1, 2, 3};
    vector<int> v(a, a + 3);
    Solution sol;
    auto vv = sol.subsets(v);
    for (auto v : vv)
    {
        cout << '[';
        for (auto x : v)
        {
            cout << x << " ";
        }
        cout << ']' << endl;
    }
}