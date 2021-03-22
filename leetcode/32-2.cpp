/*
    DP解法：
    dp[i] 表示：以s[i]结尾的，最长有效子串
    那么：
        if s[i]=='(' then dp[i] = 0
        if s[i]==')':
            if (s[i-1]=='(') then dp[i] = dp[i-2]+2
            if (s[i-1]==')') then dp[i] = dp[i-dp[i-1]-2] + dp[i-1] + 2
        
 */
#include "leetcode.h"
#include <stack>
class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int len = s.length();
        if (len == 0 || len == 1)
            return 0;
        vector<int> dp(len, 0);
        for (int i = 1; i < len; i++)
        {
            if (s[i] == ')')
            {
                if (s[i - 1] == '(')
                {
                    if (i >= 2)
                        dp[i] = dp[i - 2] + 2;
                    else
                        dp[i] = 2;
                }
                else if (s[i - 1] == ')')
                {
                    int midlen = dp[i - 1];
                    if (i >= (midlen + 1))
                    {
                        char c = s[i - midlen - 1];
                        if (c == '(')
                            dp[i] = dp[i - 1] + 2 + (i >= (midlen + 2) ? dp[i - midlen - 2] : 0);
                        else
                            dp[i] = 0;
                    }
                    else
                    {
                        dp[i] = 0;
                    }
                    
                }
            }
        }
        for (int x : dp)
            cout << x << ' ';
        cout << endl;
        int result = -1;
        for (int x : dp)
            result = max(result, x);
        return result;
    }
};

int main()
{
    string s[] = {"())", "(()", ")()())"};
    Solution sol;
    for (int i = 0; i < 3; i++)
        cout << sol.longestValidParentheses(s[i]) << "\n"
             << endl;
}