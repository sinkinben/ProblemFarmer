## 801. 使序列递增的最小交换次数

Leetcode: [801. 使序列递增的最小交换次数](https://leetcode.cn/problems/minimum-swaps-to-make-sequences-increasing/)

我们有两个长度相等且不为空的整型数组 `nums1` 和 `nums2` 。在一次操作中，我们可以交换 `nums1[i]` 和 `nums2[i]` 的元素。

例如，如果 `nums1 = [1,2,3,8]` ， `nums2 =[5,6,7,4]` ，你可以交换 `i = 3` 处的元素，得到 `nums1 =[1,2,3,4]` 和 `nums2 =[5,6,7,8]` 。
返回使 `nums1` 和 `nums2` 严格递增所需操作的最小次数 。

数组 `arr` 严格递增且 `arr[0] < arr[1] < arr[2] < ... < arr[arr.length - 1]` 。

用例保证可以实现操作。

示例 1:
```
输入: nums1 = [1,3,5,4], nums2 = [1,2,3,7]
输出: 1
解释: 
交换 A[3] 和 B[3] 后，两个数组如下:
A = [1, 3, 5, 7] ， B = [1, 2, 3, 4]
两个数组均为严格递增的。
```
示例 2:
```
输入: nums1 = [0,3,5,8,9], nums2 = [2,1,4,6,9]
输出: 1
```

提示:
```
2 <= nums1.length <= 1e5
nums2.length == nums1.length
0 <= nums1[i], nums2[i] <= 2 * 1e5
```

<br/>

**动态规划**

定义：
- `dp0[i]` 表示使得 `[0, i]` 范围内的元素满足条件，位置 `i` 不发生交换的最小操作次数。
- `dp1[i]` 表示使得 `[0, i]` 范围内的元素满足条件，位置 `i` 执行交换的最小操作次数。

显然有：`min(dp0[n - 1], dp1[n - 1])` 为最终答案，`dp0[0] = 0, dp1[0] = 1` 是初始条件。

交换必须在同一位置 `i`，如果位置 `i` 可以执行交换操作，那么必然满足二者：

1. 若 `nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1]`，那么位置 `i` 要么不交换，要么和 `i - 1` 同时发生交换。
```cpp
dp0[i] = dp0[i - 1]
dp1[i] = dp1[i - 1] + 1
```

2. 若 `nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]`，那么位置 `i` 和 `i - 1`，二者只能有一个发生交换。
```cpp
dp0[i] = dp1[i - 1]
dp1[i] = dp0[i - 1] + 1
```

3. 若同时满足上述 2 个条件，那么取最小值即可：
```cpp
dp0[i] = min(dp0[i - 1], dp1[i - 1])
dp1[i] = min(dp0[i - 1], dp1[i - 1]) + 1
```

上述 DP 可以进行空间优化。

```cpp
class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int dp0 = 0, dp1 = 1;
        for (int i = 1; i < n; ++i)
        {
            int t0 = dp0, t1 = dp1;
            bool b1 = (nums1[i] > nums1[i - 1]) && (nums2[i] > nums2[i - 1]);
            bool b2 = (nums1[i] > nums2[i - 1]) && (nums2[i] > nums1[i - 1]);
            if (b1 && b2)
                dp0 = min(t0, t1), dp1 = dp0 + 1;
            else if (b1)
                dp1++;
            else if (b2)
                dp0 = t1, dp1 = t0 + 1;
        }
        return min(dp0, dp1);
    }
};
```
