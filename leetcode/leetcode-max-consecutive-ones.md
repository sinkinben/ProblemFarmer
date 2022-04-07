## Max Consecutive Ones

Leetcode: [485. Max Consecutive Ones](https://leetcode.com/problems/max-consecutive-ones)

Given a binary array `nums`, return *the maximum number of consecutive* `1`*'s in the array*.

```text
Input: nums = [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.
```

**Solution**

```cpp
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int cnt = 0, res = 0;
        for (int x : nums)
        {
            if (x == 1) ++cnt;
            else cnt = 0;
            res = max(cnt, res);
        }
        return res;
    }
};
```



## Max Consecutive Ones II

Leetcode: [487. Max Consecutive Ones II](https://leetcode-cn.com/problems/max-consecutive-ones-ii/)

Given a binary array `nums`, return the maximum number of consecutive 1's in the array if you can flip at most one 0.

```text
Input: nums = [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the maximum number of consecutive 1s. After flipping, the maximum number of consecutive 1s is 4.
```

**Solution**

```cpp
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums, int k = 1) {
        int n = nums.size(), res = 0, zero = 0;
        int l = 0, r = 0;
        while (r < n)
        {
            zero += nums[r++] == 0;
            while (l < r && zero > k)
                zero -= nums[l++] == 0;
            res = max(res, r - l);
        }
        return res;
    }
};
```



## Max Consecutive Ones III

Leetcode: [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)

Given a binary array `nums` and an integer `k`, return *the maximum number of consecutive* `1`*'s in the array if you can flip at most* `k` `0`'s.

```
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
```

**Solution**

```cpp
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size(), res = 0, zero = 0;
        int l = 0, r = 0;
        while (r < n)
        {
            zero += nums[r++] == 0;
            while (l < r && zero > k)
                zero -= nums[l++] == 0;
            res = max(res, r - l);
        }
        return res;
    }
};
```

