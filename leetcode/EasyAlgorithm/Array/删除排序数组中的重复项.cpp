#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int i = 0;
        vector<int>::const_iterator ibegin = nums.begin();
        while (i < ((int)nums.size() - 1))
        {
            if (nums[i] == nums[i + 1])
                nums.erase(ibegin + (i + 1));
            else
                i++;
        }
        return nums.size();
    }
};

