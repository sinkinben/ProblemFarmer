#include "leetcode.h"
class Solution
{
public:
    vector<string> result;
    int len;
    vector<string> generateParenthesis(int n)
    {
        len = n<<1;
        backTrack(0, "");
        return result;
    }
    void backTrack(int now, string str)
    {
        if (now == len)
        {
            if (check(str))
                result.push_back(str);
            return;
        }
        str.push_back('(');
        backTrack(now + 1, str);
        str.pop_back();
        str.push_back(')');
        backTrack(now + 1, str);
        str.pop_back();
    }
    bool check(string &s)
    {
        int flag = 0;
        int len = s.length();
        if (len == 0)
            return true;
        if (len % 2)
            return false;
        for (int i = 0; i < len; i++)
        {
            flag += (s[i] == '(');
            flag -= (s[i] == ')');
            if (flag < 0)
                return false;
        }
        return flag == 0;
    }
};

int main()
{
    Solution sol;
    auto v = sol.generateParenthesis(3);
    for (auto x : v)
    {
        cout << x << endl;
    }
}