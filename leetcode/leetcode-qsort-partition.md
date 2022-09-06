## 快排与 Partition

众所周知，`Partition(nums, l, r)` 操作是快排的核心，其主要思想是：

- 任意选取一个 `key` 。
- 把 `[l, r]` 区间分为两部分，`[l, idx)` 和 `[idx + 1, r]` ，其中 `[l, idx)` 的元素小于等于 `key` ， `[idx + 1, r]` 的元素大于 `key` ，并令 `nums[idx] = key` 。
- 返回 `idx` 。



## 数组中的第K个最大元素

Leetcode: [215. 数组中的第K个最大元素](https://leetcode.cn/problems/kth-largest-element-in-an-array/)

等价于 `std::nth_element` 这一库函数。

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        int l = 0, r = n - 1;
        int target = n - k, pos = -1;
        do {
            pos = partition(nums, l, r);
            if (pos < target)
                l = pos + 1;
            else if (pos > target)
                r = pos - 1;
        } while (pos != target);
        return nums[target];
    }
    
    int partition(vector<int> &nums, int l, int r) {
        int key = nums[r];
        int j = l;
        for (int i = l; i < r; ++i)
            if (nums[i] < key)
                swap(nums[i], nums[j++]);
        /* pay attention to this, should not be nums[j++] */
        swap(nums[r], nums[j]);
        return j;
    }
};
```

使用库函数实现：

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) 
    {
        nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), [](int a, int b) { return a > b; });
        return nums[k - 1];
    }
};
```



## 最少移动次数使数组元素相等 II

Leetcode: [462. 最少移动次数使数组元素相等 II](https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/)

求中位数。

```cpp
class Solution {
public:
    int minMoves2(vector<int>& nums)
    {
        int n = nums.size(), res = 0, medium = 0;
        nth_element(begin(nums), begin(nums) + n / 2, end(nums));
        medium = nums[n / 2];
        for (int x : nums)
            res += abs(x - medium);
        return res;
    }
};
```



## 颜色分类

Leetcode: [75. 颜色分类](https://leetcode.cn/problems/sort-colors/)

**Two Passes**

每次把 `target` 放在 `l` 开始的一段区间内，并返回结束位置。

```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int ptr = fill(nums, 0, n, 0);
        fill(nums, ptr, n, 1);
    }

    int fill(vector<int> &nums, int l, int r, int target)
    {
        int ptr = l;
        for (int i = l; i < r; ++i)
            if (nums[i] == target)
                swap(nums[i], nums[ptr++]);
        return ptr;
    }
};
```

<br/>

**One Pass (Three Ways Partition)**

一趟扫描，划分为三个区间。

```cpp
class Solution {
public:
    void sortColors(vector<int>& nums)
    {
        threeWayPartition(nums, 1, 1);
    }

    /* Make nums be 3 partition: (-INF, low - 1], [low, high], [hight + 1, +INF)
     */
    void threeWayPartition(vector<int> &nums, int low, int high)
    {
        int n = nums.size();
        int start = 0, end = n - 1;
        for (int i = 0; i <= end; )
        {
            if (nums[i] < low)
                swap(nums[i++], nums[start++]);
            else if (nums[i] > high)
                swap(nums[i], nums[end--]);
            else
                i++;
        }
    }
};
```