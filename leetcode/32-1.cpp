/*
    暴力枚举法
    O(n**3)
    提交超时
 */
#include "leetcode.h"
class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int maxlen = 0;
        int len = s.length();
        if (len == 0 || len == 1)
            return 0;
        for (int i = 0; i < len; i++)
        {
            for (int j = i + 1; j < len; j+=2)
            {
                if (check(s, i, j))
                {
                    maxlen = max(maxlen, j - i + 1);
                }
            }
        }
        return maxlen;
    }

    bool check(string &s, int l, int r)
    {
        if ((r - l + 1) % 2)
            return false;
        int flag = 0;
        while (l <= r)
        {
            flag += (s[l] == '(');
            flag -= (s[l] == ')');
            if (flag < 0)
                return false;
            l++;
        }
        return flag == 0;
    }
};

int main()
{
    string s[] = {"())", "(()", ")()())","()(()"};
    Solution sol;
    for (int i = 0; i < 4; i++)
        cout << sol.longestValidParentheses(s[i]) << endl;
}