class Solution(object):
    def countSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        dp = [[False for i in range(0, len(s))] for i in range(len(s))]
        result = 0
        for i in range(0, len(s)-1):
            dp[i][i], result = True, result+1
            dp[i][i+1] = (s[i] == s[i+1])
            if dp[i][i+1]:
                result += 1
        dp[len(s)-1][len(s)-1], result = True, result+1
        for d in range(2, len(s)):
            for i in range(0, len(s) - d):
                j = i + d
                dp[i][j] = (dp[i+1][j-1]) and (s[i] == s[j])
                if dp[i][j]:
                    result += 1
        return result


'''
dp[i,j]: s[i,j] 是否为回文串
dp[i,j] = invalid, if i > j
dp[i,i] = 1
dp[i,i+1] = (s[i] == s[i+1])
dp[i,j] = dp[i+1,j-1] && (s[i] == s[j])
'''

so = Solution()
print(so.countSubstrings('aaa'))
