#include "leetcode.h"
#include <unordered_set>
class Solution
{
public:
    int subarrayBitwiseORs(vector<int> &A)
    {
        unordered_set<int> s;
        int len = A.size();
        vector<vector<int>> dp(len + 1, vector<int>(len + 1, 0));
        for (int i = 0; i < len; i++)
        {
            dp[i][i] = A[i], s.insert(dp[i][i]);
            for (int j = i + 1; j < len; j++)
            {
                dp[i][j] = dp[i][j - 1] | A[j], s.insert(dp[i][j]);
            }
        }
        for (auto x : s)
            cout << x << ' ';
        cout << endl;
        return s.size();
    }
    int subarrayBitwiseORs2(vector<int> &A)
    {
        unordered_set<int> s(A.begin(), A.end());
        int len = A.size();
        vector<int> dp(len + 1, 0);
        for (int i = 0; i < len; i++)
        {
            dp[i] = A[i];
            for (int j = i + 1; j < len; j++)
                dp[j] = dp[j - 1] | A[j], s.insert(dp[j]);
        }
        for (auto x : s)
            cout << x << ' ';
        cout << endl;
        return s.size();
    }
    int subarrayBitwiseORs3(vector<int> &A)
    {
        unordered_set<int> s(A.begin(), A.end());
        int len = A.size();
        int dp = 0;
        for (int i = 0; i < len; i++)
        {
            dp = A[i];
            for (int j = i + 1; j < len; j++)
            {
                dp = dp | A[j], s.insert(dp);
            }
        }
        return s.size();
    }

    int subarrayBitwiseORs4(vector<int> &a)
    {
        unordered_set<int> s(a.begin(), a.end());
        int len = a.size();
        vector<int> dp;
        for (int i = 0; i < len; i++)
        {
            vector<int> v;
            int cur = a[i];
            v.push_back(cur);
            s.insert(cur);
            for (auto x : dp)
            {
                int k = x | cur;
                if (k > cur)
                    v.push_back(k);
                s.insert(cur = k);
            }
            dp = v;
        }
        return s.size();
    }
};

int main()
{
    Solution s;
    vector<int> v1({3, 2, 4});
    vector<int> v2({1, 2, 4});
    vector<int> v3({7, 6, 4});
    cout << s.subarrayBitwiseORs(v1) << endl;
    cout << s.subarrayBitwiseORs(v2) << endl;
    cout << s.subarrayBitwiseORs(v3) << endl;

    cout << s.subarrayBitwiseORs3(v1) << endl;
    cout << s.subarrayBitwiseORs3(v2) << endl;
    cout << s.subarrayBitwiseORs3(v3) << endl;
}

/*
    dp[i][j] (i<=j)
    dp[i][i] = a[i]
    dp[0][j] = a[0]|...|a[j]
    dp[i][j] = dp[i][j-1]|a[j]
 */
