#include "leetcode.h"
class Solution
{
public:
    int minArray(vector<int> &v)
    {
        int len = v.size();
        if (len == 0)
            return -1;
        if (len == 1)
            return v.front();
        int l = 0, r = len - 1, m = l;
        while (l <= r)
        {
            if (l == r)
                break;
            m = l + (r - l) / 2;
            if (v[m] < v[r])
                r = m;
            else if (v[m] > v[r])
                l = m + 1;
            else
                r--;
        }
        return v[l];
    }
};

int main()
{
    Solution sol;
    vector<int> v = {1, 2, 5};
    vector<int> v2 = {1, 1, 0, 1};
    v = {1, 3, 3};
    v = {2, 2, 2, 0, 1};
    cout << sol.minArray(v) << endl;
}