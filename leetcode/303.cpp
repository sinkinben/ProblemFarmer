#include "leetcode.h"
class NumArray
{
public:
    vector<int> dp;
    NumArray(vector<int> &nums)
    {
        int n = nums.size();
        dp.resize(n + 1, 0);
        dp[0] = 0;
        for (int i = 1; i <= n; i++)
            dp[i] = nums[i - 1] + dp[i - 1];
    }

    int sumRange(int i, int j)
    {
        return dp[j + 1] - dp[i];
    }
};

int main()
{
    vector<int> v({-2, 0, 3, -5, 2, -1});
    NumArray sol(v);
    cout << sol.sumRange(0, 2) << endl;
    cout << sol.sumRange(2, 5) << endl;
    cout << sol.sumRange(0, 5) << endl;
}
/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */