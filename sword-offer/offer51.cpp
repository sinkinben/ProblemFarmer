#include "leetcode.h"
class Solution
{
public:
    int reversePairs(vector<int> &nums)
    {
        int len = nums.size();
        vector<int> buf(len, 0);
        int x = mergeSort(nums, buf, 0, len - 1);
        vprint(nums);
        return x;
    }

    int mergeSort(vector<int> &data, vector<int> &buf, int l, int r)
    {
        if (l >= r)
            return 0;
        int mid = l + (r - l) / 2;
        int leftCount = mergeSort(data, buf, l, mid);
        int rightCount = mergeSort(data, buf, mid + 1, r);
        int p1 = l, p2 = mid + 1, idx = l;
        int count = 0;
        while (p1 <= mid && p2 <= r)
        {
            if (data[p1] <= data[p2])
                buf[idx] = data[p1++], count += (p2 - (mid + 1));
            else
                buf[idx] = data[p2++];
            idx++;
        }
        while (p1 <= mid)
            buf[idx++] = data[p1++], count += (p2 - (mid + 1));
        while (p2 <= r)
            buf[idx++] = data[p2++];
        copy(buf.begin() + l, buf.begin() + idx, data.begin() + l);
        return count + leftCount + rightCount;
    }
};

int main()
{
    vector<int> v = {1, 3, 2, 3, 1};
    Solution sol;
    cout << sol.reversePairs(v);
}