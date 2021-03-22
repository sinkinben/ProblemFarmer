#include "leetcode.h"
class Solution
{
public:
    vector<int> result;
    vector<int> grayCode(int n)
    {
        if (n == 0)
        {
            result.push_back(0);
            return result;
        }
        else if (n == 1)
        {
            result.push_back(0);
            result.push_back(1);
            return result;
        }
        result.push_back(0);
        result.push_back(1);
        for (int i = 1; i < n; i++)
        {
            helper(i);
        }
        for (int x : result)
        {
            cout << x << ' ';
        }
        return result;
    }

    void helper(int k)
    {
        int len = result.size();
        vector<int> v(result.rbegin(), result.rend());
        for (int x : v)
        {
            result.push_back(x);
        }
        //[0...len-1] + [len ... 2len-1]
        for (int i = len; i < 2 * len; i++)
        {
            result[i] = result[i] | (1 << k);
        }
    }
};
int main()
{
    Solution sol;
    sol.grayCode(2);
}