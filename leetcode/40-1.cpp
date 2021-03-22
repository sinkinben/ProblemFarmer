#include "leetcode.h"
class Solution
{
public:
    bool *used = nullptr;
    int len;
    set<vector<int>> result;
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        len = candidates.size();
        sort(candidates.begin(), candidates.end());
        used = new bool[len];
        memset(used, 0, sizeof(bool) * len);
        vector<int> v;
        backTrack(candidates, target, 0, v);
        return vector<vector<int>>(result.begin(), result.end());
    }
    void backTrack(const vector<int> &candidates, int target, int cur, vector<int> v)
    {
        for (int i = 0; i < len; i++)
        {
            if (used[i] == true)
                continue;
            v.push_back(candidates[i]);
            cur += v.back();
            used[i] = true;
            int flag = check(cur, target);
            if (flag < 0)
            {
                backTrack(candidates, target, cur, v);
                cur -= v.back();
                v.pop_back();
                used[i] = false;
            }
            else if (flag > 0)
            {
                used[i] = false;
                return;
            }
            else
            {
                sort(v.begin(),v.end());
                result.insert(v);
                used[i] = false;
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
    int a[] = {10, 1, 2, 7, 6, 1, 5}, t = 8;
    vector<int> v(a, a + 7);
    Solution sol;
    auto vv = sol.combinationSum2(v, t);
    for (auto &v : vv)
    {
        for (auto x : v)
        {
            cout << x << ' ';
        }
        cout << endl;
    }
}