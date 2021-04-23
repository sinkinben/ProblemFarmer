#include "leetcode.h"
class Solution
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        const int idx = nums.size() - k;
        int l = 0, r = nums.size() - 1;
        int p = -1;
        while ((p = randomPartition(nums, l, r)) != idx)
        {
            cout << p << endl;
            if (p == idx)
                break;
            else if (p > idx)
                r = p - 1;
            else
                l = p + 1;
        }
        return nums[p];
    }
    int randomPartition(vector<int> &v, int l, int r)
    {
        srand(time(nullptr));
        int idx = l + random() % (r - l + 1);
        swap(v[idx], v[r]);
        return partition(v, l, r);
    }
    int partition(vector<int> &v, int l, int r)
    {
        int x = v[r];
        int i = l - 1;
        for (int j = l; j < r; j++)
            if (v[j] < x)
                i++, swap(v[i], v[j]);
        swap(v[i + 1], v[r]);
        return i + 1;
    }
};
int main()
{
    vector<int> v = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k = 4;
    Solution sol;
    sol.findKthLargest(v, k);
}