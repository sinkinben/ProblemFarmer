#include "../leetcode.h"
class Solution
{
public:
    int maximumRequests(int n, vector<vector<int>> &requests)
    {
        int len = requests.size();
        int ans = 0;
        for (int i = 1; i < (1 << len); i++)
        {
            if (check(n, i, requests))
                ans = max(ans, countOne(i));
        }
        return ans;
    }

    int countOne(int x)
    {
        int k = 0;
        while (x)
            k++, x &= (x - 1);
        return k;
    }

    bool check(const int n, const int k, const vector<vector<int>> &req)
    {
        vector<int> indegree(n, 0), outdegree(n, 0);
        int len = req.size();
        for (int i = 0; i < len; i++)
        {
            if ((k >> i) & 1)
            {
                int x = req[i][0], y = req[i][1];
                outdegree[x]++, indegree[y]++;
            }
        }
        return indegree == outdegree;
    }
};