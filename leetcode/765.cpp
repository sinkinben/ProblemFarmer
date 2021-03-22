#include "leetcode.h"
#include <algorithm>
class Solution
{
public:
    int minSwapsCouples(vector<int> &row)
    {
        int n = row.size();
        int ans = 0;
        for (int i = 0; i < n; i += 2)
        {
            if ((row[i] ^ 1) == row[i + 1])
                continue;
            int target = row[i] ^ 1;
            for (int j = i + 2; j < n; j++)
            {
                if (row[j] == target)
                {
                    swap(row[i + 1], row[j]), ans++;
                    break;
                }
            }
        }
        return ans;
    }
    int minSwapsCouples2(vector<int> &row)
    {
        int ans = 0;
        int len = row.size();
        vector<int> v(len, 0);
        for (int i = 0; i < len; i++)
            v[row[i]] = i;
        int t;
        for (int i = 0; i < len; i += 2)
        {
            t = row[i] ^ 1;
            if (t != row[i + 1])
            {
                ans++;
                int idx = v[t];
                swap(row[idx], row[i + 1]);
                v[row[idx]] = idx;
                v[row[i + 1]] = i + 1;
            }
        }
        return ans;
    }
};

int main()
{
    vector<int> r({0, 2, 4, 6, 7, 1, 3, 5});
    Solution sol;
    cout << sol.minSwapsCouples2(r) << endl;
}
