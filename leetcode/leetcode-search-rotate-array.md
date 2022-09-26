## 排序旋转数组

「搜索排序旋转数组」是一类经典的二分查找的题目。

那什么是「排序旋转数组」呢？假设有一个数组 `arr` 是有序的，`arr = [1, 2, 3, 4, 5]`，那么 `arr` 旋转若干位之后的数组，即：

```text
[2, 3, 4, 5, 1]
[3, 4, 5, 1, 2]
[4, 5, 1, 2, 3]
[5, 1, 2, 3, 4]
```

都属于「排序旋转数组」。

给定一个排序旋转数组 `arr`，有以下几种经典的问法：

- 给出 `arr` 发生旋转的下标，即数组最大值/最小值的下标。
- 给定一个 `target` ，求 `target` 在 `arr` 中的下标。
- 如果 `arr` 中存在重复元素，应该怎么处理？

对应的 Leetcode 题目是：

- [153. 寻找旋转排序数组中的最小值](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/)：数组的值互不相同，查找最小值。
- [154. 寻找旋转排序数组中的最小值 II](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/)：数组可能存在重复元素，查找最小值。
- [33. 搜索旋转排序数组](https://leetcode.cn/problems/search-in-rotated-sorted-array/)：数组的值互不相同，查找 `target` 的下标。
- [81. 搜索旋转排序数组 II](https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/): 数组可能存在重复元素，查找 `target` 的下标。





## 查找旋转位置（元素唯一）

Leetcode: [153. 寻找旋转排序数组中的最小值](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/)

```cpp
/* 1. nums 中元素各不相同。
 * 2. 返回最小值的下标。
 */
int getRotateIndex(vector<int> &nums)
{
    int n = nums.size();
    int l = 0, r = n - 1;
    while (l < r)
    {
        int m = l + (r - l) / 2;
        if (nums[m] > nums[r]) l = m + 1;  // m 落在了前半段, r 在后半段, 旋转的位置必然在 m 右侧
        else r = m;                        // m, r 同时在前半段, 或者同在后半段, 最小值必然在 m 的左侧
    }
    return l;
}
```



## 查找旋转位置（元素重复）

Leetcode: [154. 寻找旋转排序数组中的最小值 II](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/)

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;
        while (l < r)
        {
            int m = l + (r - l) / 2;
            if (nums[m] > nums[r])       // m 落在了前半段, r 在后半段, 旋转的位置 (即最小值) 必然在 m 右侧
                l = m + 1;
            else if (nums[m] < nums[r])  // m, r 同时在前半段, 或者同在后半段, 最小值必然在 m 的左侧
                r = m;
            else if (nums[m] == nums[r])
                r -= 1;
        }
        return nums[l];
    }
};
```



## 查找特定的值（元素唯一）

Leetcode: [33. 搜索旋转排序数组](https://leetcode.cn/problems/search-in-rotated-sorted-array/)

给你旋转后的数组 `nums` 和一个整数 `target` ，如果 `nums` 中存在这个目标值 `target` ，则返回它的下标，否则返回 -1 。数组中的值 **互不相同**。

设计一个时间复杂度为 `O(log n)` 的算法解决此问题。



### 三次二分查找

- 先基于「二分查找」找到最小值的下标 `p` 。
- 分别在 `[0, p - 1]` 和 `[p, n - 1]` 两段有序的子数组中，进行二分查找。

```cpp
/* 1. nums 中元素各不相同。
 * 2. 返回最小值的下标。
 */
int getRotateIndex(vector<int> &nums)
{
    int n = nums.size();
    int l = 0, r = n - 1;
    while (l < r)
    {
        int m = l + (r - l) / 2;
        if (nums[m] > nums[r]) l = m + 1;
        else r = m;
    }
    return l;
}
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int p = getRotateIndex(nums);
        int idx = binarySearch(nums, 0, p - 1, target);
        return idx != -1 ? idx : binarySearch(nums, p, n - 1, target);
    }
    
    // Common Binary Search in range of [l, r]
    int binarySearch(vector<int> &nums, int l, int r, int val)
    {
        while (l <= r)
        {
            int m = l + (r - l) / 2;
            if (val == nums[m]) return m;
            else if (val < nums[m]) r = m - 1;
            else if (val > nums[m]) l = m + 1;
        }
        return -1;
    }
};
```



### 递归

- `binarySearch` 用于查找一个严格升序的数组，范围是双闭区间 `[l, r]` 。
- `searchRotate` 用于查找一个旋转数组，范围是双闭区间 `[l, r]` 。

```cpp
class Solution {
public:
    // Common Binary Search in range of [l, r]
    int binarySearch(vector<int> &nums, int l, int r, int val)
    {
        while (l <= r)
        {
            int m = l + (r - l) / 2;
            if (val == nums[m]) return m;
            else if (val < nums[m]) r = m - 1;
            else if (val > nums[m]) l = m + 1;
        }
        return -1;
    }
    // Search rotate array in range of [l, r]
    int searchRotate(vector<int> &nums, int l, int r, int val)
    {
        int n = nums.size();
        while (l <= r)
        {
            int m = l + (r - l) / 2;
            if (nums[m] == val) return m;
            if (nums[0] <= nums[m]) // m 在前半段
            {
                if (nums[0] <= val && val < nums[m]) return binarySearch(nums, l, m - 1, val);
                else return searchRotate(nums, m + 1, r, val);
            }
            else // m 在后半段
            {
                if (nums[m] < val && val <= nums[n - 1]) return binarySearch(nums, m + 1, r, val);
                else return searchRotate(nums, l, m - 1, val);
            }
        }
        return -1;
    }
    int search(vector<int>& nums, int val)
    {
        int n = nums.size();
        return searchRotate(nums, 0, n - 1, val);
    }
};
```



### 一次二分查找（非递归）

```cpp
class Solution {
public:
    // Search rotate array in range of [l, r]
    int searchRotate(vector<int> &nums, int l, int r, int val)
    {
        int n = nums.size();
        while (l <= r)
        {
            int m = l + (r - l) / 2;
            if (nums[m] == val) return m;
            if (nums[0] <= nums[m]) // m 在前半段
            {
                if (nums[0] <= val && val < nums[m]) r = m - 1;
                else l = m + 1;
            }
            else // m 在后半段
            {
                if (nums[m] < val && val <= nums[n - 1]) l = m + 1;
                else r = m - 1;
            }
        }
        return -1;
    }
    int search(vector<int>& nums, int val)
    {
        int n = nums.size();
        return searchRotate(nums, 0, n - 1, val);
    }
};
```



## 查找特定的值（元素重复）

Leetcode: [81. 搜索旋转排序数组 II](https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/)

查找 `target` 是否出现在数组中，不需要输出下标。

```cpp
class Solution {
public:
    // Search rotate array in range of [l, r]
    bool searchRotate(vector<int> &nums, int l, int r, int val)
    {
        int n = nums.size();
        while (l <= r)
        {
            int m = l + (r - l) / 2;
            if (nums[m] == val) return true;
            if (nums[l] == nums[m] && nums[m] == nums[r]) // 无法判断 [l, r] 区间是否有序
                ++l, --r;
            else if (nums[l] <= nums[m]) // [l, m] 同在前半段 (或者同在后半段)
            {
                if (nums[l] <= val && val < nums[m]) r = m - 1;
                else l = m + 1;
            }
            else if (nums[l] > nums[m]) // l 在前半段, m 在后半段, 此时, [m, r] 同在后半段
            {
                if (nums[m] < val && val <= nums[r]) l = m + 1;
                else r = m - 1;
            }
        }
        return false;
    }
    bool search(vector<int>& nums, int val)
    {
        int n = nums.size();
        return searchRotate(nums, 0, n - 1, val);
    }
};
```

