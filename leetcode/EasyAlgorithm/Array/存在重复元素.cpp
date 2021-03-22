#include <vector>
#include <bitset>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    bool containsDuplicate(vector<int> &nums)
    {
        return func2(nums);
    }

    // TLE
    bool func1(vector<int> &nums)
    {
        int i, j, size = nums.size();
        for (i = 0; i < size; i++)
        {
            for (j = i + 1; j < size; j++)
            {
                if (nums[i] == nums[j])
                    return true;
            }
        }
        return false;
    }

    // AC
    bool func2(vector<int> &v)
    {
        sort(v.begin(), v.end());
        int len = v.size();
        for (int i = 0; i + 1 < len; i++)
        {
            if (v[i] == v[i + 1])
                return true;
        }
        return false;
    }

    bool func3(vector<int> &v)
    {
        unordered_set<int> s;
        for (int x : v)
            s.insert(x);
        return s.size() != v.size();
    }
};