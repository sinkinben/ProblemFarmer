#include "leetcode.h"
class Solution
{
public:
    set<vector<int>> result;
    vector<vector<int>> combine(int n, int k)
    {
        vector<int> v;
        backTrack(v, n, k, 1);
        return vector<vector<int>>(result.begin(), result.end());
    }
    void backTrack(vector<int> &v, int n, int k, int now)
    {

        for (int i = now; i <= n; i++)
        {
            v.push_back(i);
            if (v.size() < k)
            {
                backTrack(v, n, k, i + 1);
            }
            else if (v.size() == k)
            {
                result.insert(v);
            }
            else
            {
                assert(0);
            }
            v.pop_back();
        }
    }
};
int main()
{
    Solution sol;
    auto vv = sol.combine(13, 13);
    for (auto &v : vv)
    {
        for (auto x : v)
        {
            cout << x << ' ';
        }
        cout << endl;
    }
}