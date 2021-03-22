#include "leetcode.h"
#include <cmath>
class Solution
{
public:
    vector<int> root;
    int largestComponentSize(vector<int> &A)
    {
        int maxval = -1;
        for (int x : A)
            maxval = max(maxval, x);
        root.resize(maxval + 1, -1);

        for (int x : A)
        {
            int limit = (int)sqrt(x) + 1;
            for (int i = 2; i < limit; i++)
                if (x % i == 0)
                    merge(x, i), merge(x, x / i);
        }

        vector<int> counter(maxval + 1, 0);
        int ans = -1;
        for (int x : A)
            ans = max(ans, ++counter[find(x)]);
        return ans;
    }

    int find(int x)
    {
        return root[x] == -1 ? x : (root[x] = find(root[x]));
    }

    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x;
    }
};

int main()
{
    vector<int> v = {2, 3, 6, 7, 4, 12, 21, 39};
    Solution sol;
    cout << sol.largestComponentSize(v) << endl;
}
