#include "leetcode.h"
#include <unordered_map>
class Solution
{
public:
    unordered_map<int, int> counter;
    unordered_map<int, int> root;
    int longestConsecutive(vector<int> &nums)
    {
        int len = nums.size();
        for (int x : nums)
            root[x] = x, counter[x] = 1;
        int result = len == 0 ? 0 : 1;
        for (int x : nums)
        {
            if (root.count(x + 1) == 1)
                result = max(result, merge(x, x + 1));
        }
        return result;
    }
    int find(int x)
    {
        return root[x] == x ? x : (root[x] = find(root[x]));
    }
    int merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x != y)
        {
            root[y] = x;
            counter[x] += counter[y];
        }
        return counter[x];
    }
};
int main()
{
    vector<int> v({100, 4, 200, 1, 3, 2, 3});
    Solution sol;
    cout << sol.longestConsecutive(v);
}