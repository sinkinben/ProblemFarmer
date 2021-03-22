#include "leetcode.h"
/*
    dp[i,j] 表示 s1[0...i] 与 s2[0...j]的最小 ascii 的差值
    dp[0,0] = 0
    dp[0,j] = sum(s2[0..j-1])
    dp[i,0] = sum(s1[0..i-1])
    dp[i,j] = if s1[i-1]==s2[j-1] then dp[i-1,j-1]
              if s1[i-1]!=s2[j-1] then min(dp[i-1,j]+s1[i-1], dp[i,j-1]+s2[j-1])
    
    空间可优化为：O(n)
    一点疑惑：
    原来是：min(dp[i-1,j]+s2[j-1], dp[i,j-1]+s1[i-1])
    没想到交换一下位置就AC了，真像两只老虎————真奇怪
 */
class Solution
{
public:
    int minimumDeleteSum(string s1, string s2)
    {
        int len1 = s1.length();
        int len2 = s2.length();
        int dp[len1 + 1][len2 + 1];
        dp[0][0] = 0;

        int sum = 0;
        for (int j = 1; j <= len2; j++)
        {
            sum += s2[j - 1];
            dp[0][j] = sum;
        }
        sum = 0;
        for (int i = 1; i <= len1; i++)
        {
            sum += s1[i - 1];
            dp[i][0] = sum;
        }
        for (int i = 1; i <= len1; i++)
        {
            for (int j = 1; j <= len2; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = min(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]);
                }
            }
        }
        // for (int i = 0; i < len1+1; i++)
        // {
        //     for (int j = 0; j < len2+1; j++)
        //         cout << setw(4) << dp[i][j];
        //     cout << endl;
        // }
        // cout << endl;
        return dp[len1][len2];
    }
};

int main()
{
    // string s1 = "sea", s2 = "eat";
    string s1 = "delete", s2 = "leet";

    Solution sol;
    cout << sol.minimumDeleteSum(s1, s2) << endl;
}