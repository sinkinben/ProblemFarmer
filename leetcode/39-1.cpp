#include "leetcode.h"
class Solution
{
public:
    set<vector<int>> result;
    int len;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        len = candidates.size();
        vector<int> v;
        sort(candidates.begin(), candidates.end());
        backTrack(candidates, target, 0, v);
        vector<vector<int>> vv(result.begin(), result.end());
        return vv;
    }

    void backTrack(vector<int> &candidates, int target, int cur, vector<int> v)
    {
        for (int i = 0; i < len; i++)
        {
            v.push_back(candidates[i]);
            cur += v.back();
            int flag = check(cur, target);
            if (flag < 0)
            {
                backTrack(candidates, target, cur, v);
                cur -= v.back();
                v.pop_back();
            }
            else if (flag > 0)
            {
                return;
            }
            else
            {
                sort(v.begin(), v.end());
                result.insert(v);
                return;
            }
        }
    }
    int check(int cur, int target)
    {
        return cur - target;
    }
};

int main()
{
    int a[] = {2, 3, 6, 7}, t = 7;
    vector<int> v(a, a + 4);
    Solution sol;
    auto vv = sol.combinationSum(v, t);
    for (auto &v : vv)
    {
        for (auto x : v)
        {
            cout << x << ' ';
        }
        cout << endl;
    }
}