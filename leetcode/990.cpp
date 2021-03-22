#include "leetcode.h"
#include <unordered_map>
#define getidx(x) ((x) - 'a')
class Solution
{
public:
    vector<int> root;
    bool equationsPossible(vector<string> &equations)
    {
        root.resize('z' - 'a' + 1, -1);
        vector<int> notequal;
        int len = equations.size();
        for (int i = 0; i < len; i++)
        {
            auto &s = equations[i];
            if (s[1] == '!')
            {
                notequal.emplace_back(i);
                continue;
            }
            int a = getidx(s[0]), b = getidx(s[3]);
            merge(a, b);
        }
        for (int i : notequal)
        {
            auto &s = equations[i];
            int a = getidx(s[0]), b = getidx(s[3]);
            if (find(a) == find(b))
                return false;
        }
        return true;
    }

    int find(int x)
    {
        return (root[x] == -1) ? x : (root[x] = find(root[x]));
    }

    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x;
    }
};

int main()
{
    vector<string> v = {"c==c", "b==d", "x!=z"};
    Solution sol;
    cout << sol.equationsPossible(v);
}