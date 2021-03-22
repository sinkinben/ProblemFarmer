#include "leetcode.h"
class Solution
{
public:
    int numDecodings(string s)
    {
        int len = s.length();
        if (len == 0)
            return 0;
        if (len == 1)
            return ('1' <= s[0] && s[0] <= '9') == true ? 1 : 0;
        if (s.front() == '0')
            return 0;
        uint64_t dp[len];
        dp[0] = (s[0] != '0');
        if (s[1] == '0')
            dp[1] = (s[0] == '1' || s[0] == '2');
        else
            dp[1] = 1 + ((s[0] == '1' && '0' <= s[1] <= '9') || (s[0] == '2' && '0' <= s[1] && s[1] <= '6'));
        for (int i = 2; i < len; i++)
        {
            if (s[i] == '0')
            {
                if (s[i - 1] == '1' || s[i - 1] == '2')
                    dp[i] = dp[i - 2];
                else
                    return 0;
            }
            else if ('1' <= s[i] && s[i] <= '9')
            {
                if (s[i - 1] == '1')
                    dp[i] = dp[i - 1] + dp[i - 2];
                else if (s[i - 1] == '2')
                {
                    if ('0' <= s[i] && s[i] <= '6')
                        dp[i] = dp[i - 1] + dp[i - 2];
                    else
                        dp[i] = dp[i - 1];
                }
                else
                {
                    //s[i]='0' or s[i]>='3'
                    dp[i] = dp[i - 1];
                }
            }
        }
        for (int i = 0; i < len; i++)
            cout << dp[i] << ' ';
        cout << endl;
        return dp[len - 1];
    }
};
int main()
{
    string s[] = {"12", "226", "10", "27", "01", "101"};
    Solution sol;
    for (int i = 0; i < 6; i++)
        cout << sol.numDecodings(s[i]) << endl;
}
/*
    考虑到译码范围是[1,26]，所以对于 s[i]=0 or s[i]>=3 的位置，必须要组合译码
    dp[i] 表示 s[0...i] 的 译码方法总数
    dp[0] = 1
    现考虑 dp[i] 的转移：
        if s[i]='0' then:
            if s[i-1]='1' or '2' then dp[i] = dp[i-2] else return 0 
            为什么是return 0 而不是 dp[i] = 0? 因为 '0' 必须与前面s[i-1]组合译码，s[i-1]只能是{1,2}
        if s[i-1]='1' then dp[i] = dp[i-1]+dp[i-2]
        if s[i-1]='2':
            if 0<=s[i]<=6 then dp[i]=dp[i-1]+dp[i-2]
            if s[i]>=7 then dp[i]=dp[i-1]

 */
/*
    需要特别留意边界：
    + "01"
    + len=2: "27", "10"
    提交了8次才改对，我佛了 
 */