#include "leetcode.h"
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
class Solution
{
public:
    int ans = 0;
    int maxLength(vector<string> &arr)
    {
        vector<string> v;
        for (auto &x : arr)
        {
            if (check2(x))
                v.push_back(x);
        }
        string s = "";
        backtrack(v, s, 0);
        return ans;
    }

    void backtrack(vector<string> &v, string &cur, int start)
    {
        for (int i = start; i < v.size(); i++)
        {
            if (!check(cur, v[i]))
                continue;
            cur += v[i];
            ans = max(ans, cur.length());
            backtrack(v, cur, i + 1);
            for (int j = 0; j < v[i].length(); j++)
                cur.pop_back();
        }
    }
    bool check(string &a, string &b)
    {
        for (auto x : b)
            if (a.find(x) != string::npos)
                return false;
        return true;
    }

    bool check2(string &s)
    {
        bool table[26] = {0};
        for (auto x : s)
        {
            if (table[x - 'a'])
                return false;
            table[x - 'a'] = true;
        }
        return true;
    }
};

int main()
{
    Solution s;
    vector<string> v1({"yy", "bkhwmpbiisbldzknpm"});
    cout << s.maxLength(v1) << endl;
}