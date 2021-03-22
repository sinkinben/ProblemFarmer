#include "leetcode.h"
class Solution
{
public:
    int n = 0;
    vector<string> ans;
    string buf;
    vector<string> permutation(string s)
    {
        buf = s;
        n = s.length();
        vector<int> v(n, 0);
        helper(v, 0);
        return ans;
    }
    string generate(vector<int> &v)
    {
        string s = "";
        for (int x : v)
            s.append(1, buf[x]);
        return s;
    }

    inline bool check(vector<int> &v, int idx)
    {
        for (int i = 0; i < idx; i++)
            if (v[idx] == v[i])
                return false;
        return true;
    }

    void helper(vector<int> &v, int pos)
    {
        for (int i = 0; i < n; i++)
        {
            v[pos] = i;
            if (check(v, pos))
            {
                if (pos == n - 1)
                    ans.push_back(generate(v));
                else
                    helper(v, pos + 1);
            }
        }
    }
};

int main()
{
    string s = "123";
    Solution sol;
    auto v = sol.permutation(s);
    for (auto x : v)
        cout << x << endl;
}