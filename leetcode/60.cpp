#include "leetcode.h"
class Solution
{
public:
    string getPermutation(int n, int k)
    {
        vector<int> v(n);
        for (int i = 1; i <= n; i++)
            v[i - 1] = i;
        k--;
        while (k--)
            next_permutation(v.begin(), v.end());
        string s="";
        for (int x:v)
            s.push_back(x+'0');
        return s;
    }
};
int main()
{
    Solution sol;
    cout<<sol.getPermutation(3,3);
}