#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace std;
class Solution
{
public:
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_map<int, int> m;
        for (int x : nums1)
            m[x]++;
        vector<int> ans;
        for (int x : nums2)
        {
            if (m.find(x) != m.end() && m[x] >= 1)
            {
                m[x]--;
                ans.emplace_back(x);
            }
        }
        return ans;
    }
};

int main()
{
    vector<int> v1 = {1, 4, 9, 4, 9}, v2 = {4, 9};
    Solution sol;
    auto v = sol.intersect(v2, v1);
    for (int x : v)
        cout << x << ' ';
}