## Binary Search

Leetcode:

- [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)



## First and Last Position in Sorted Array

Leetcode: [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

Given an array of integers `nums` sorted in non-decreasing order, find the starting and ending position of a given `target` value.

If `target` is not found in the array, return `[-1, -1]`.

You must write an algorithm with `O(log n)` runtime complexity.

```text
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
```

<br/>

**Solution**

```cpp
/* Find right bounder of `val` in `nums`. If not found, return -1.
 * e.g. nums = [0, 1, 1, 2], val = 1, then return 2.
 */
int right_bounder(vector<int> &nums, int val)
{
    int n = nums.size();
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (val >= nums[m])     l = m + 1;
        else if (val < nums[m]) r = m - 1;
    }
    return (r >= 0 && nums[r] == val) ? r : -1;
}

/* Find left bounder of `val` in `nums`. If not found, return -1.
 * e.g. nums = [0, 1, 1, 2], val = 1, then return 1.
 */
int left_bounder(vector<int> &nums, int val)
{
    int n = nums.size();
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (val > nums[m])       l = m + 1;
        else if (val <= nums[m]) r = m - 1;
    }
    return (l < n && nums[l] == val) ? l : -1;
}

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int t) {
        return {left_bounder(nums, t), right_bounder(nums, t)};
    }
};
```

