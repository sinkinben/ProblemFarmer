#include "../leetcode.h"
#include <unordered_set>
class Solution
{
public:
    unordered_set<string> pool;
    int ans = 0;
    int maxUniqueSplit(string s)
    {
        dfs(s, 0);
        return ans;
    }

    void dfs(const string &s, int idx)
    {
        int len = s.length();
        if (idx >= len)
        {
            ans = max(ans, (int)pool.size());
            return;
        }
        string t;
        for (int i = idx; i < len; i++)
        {
            t += s[i];
            if (pool.find(t) == pool.end())
            {
                pool.insert(t);
                dfs(s, i + 1);
                pool.erase(t);
            }
        }
    }
};

int main()
{
    string s = "abc";
    Solution sol;
    cout << sol.maxUniqueSplit(s) << endl;
}