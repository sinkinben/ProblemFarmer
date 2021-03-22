#include "leetcode.h"
#define max(a, b) ((a) > (b) ? (a) : (b))
class Solution
{
public:
    int maxProduct(vector<string> &words)
    {
        vector<int> v;
        for (auto &s : words)
            v.push_back(hash(s));

        size_t ans = 0;
        size_t len = words.size();
        for (size_t i = 0; i < len; i++)
        {
            for (size_t j = i + 1; j < len; j++)
            {
                if ((v[i] & v[j]) == 0)
                    ans = max(ans, words[i].size() * words[j].size());
            }
        }
        return ans;
    }

    int hash(string &s)
    {
        int n = 0;
        for (auto x : s)
        {
            n |= (1 << (x - 'a'));
        }
        return n;
    }
};

int main()
{
    vector<string> v({"abcw", "baz", "foo", "bar", "xtfn", "abcdef"});
    Solution s;
    cout << s.maxProduct(v) << endl;
}