## 1224. 最大相等频率

Leetcode: https://leetcode.cn/problems/maximum-equal-frequency/

给你一个正整数数组 `nums`，请你帮忙从该数组中找出能满足下面要求的 最长 前缀，并返回该前缀的长度：

从前缀中恰好删除一个元素后，剩下每个数字的出现次数都相同。
如果删除这个元素后没有剩余元素存在，仍可认为每个数字都具有相同的出现次数（也就是 0 次）。

 

示例 1：
```
输入：nums = [2,2,1,1,5,3,3,5]
输出：7
解释：对于长度为 7 的子数组 [2,2,1,1,5,3,3]，如果我们从中删去 nums[4] = 5，就可以得到 [2,2,1,1,3,3]，里面每个数字都出现了两次。
```

示例 2：
```
输入：nums = [1,1,1,2,2,2,3,3,3,4,4,4,5]
输出：13
```

提示：

- `2 <= nums.length <= 1e5`
- `1 <= nums[i] <= 1e5`

<br/>

**双重哈希**


- 第一重哈希：`cnt[x]` 表示 `nums` 中元素 `x` 出现的次数。
- 第二重哈希：`freq[y]` 表示 `y = cnt[x]` 出现的次数。


例如：
```text
nums = [1, 1, 2, 2, 2, 3, 3]
cnt = {{1, 2}, {2, 3}, {3, 2}}
freq = {{2, 2}, {3, 1}}
```

那么，从左到右扫描每一个 `nums[i]`，`maxFreq` 表示目前为止的「元素出现次数」的最大值。

如果当前的前缀 `[0, i]` 满足下面 3 种情况之一，那么 `len = i + 1` 是一个有效前缀的长度。
- `maxFreq == 1`，说明每个元素 `nums[i]` 各不相同，只出现了一次。
- `maxFreq * freq[maxFreq] + 1 == len`，说明有一个值出现了一次，其他值均出现 `maxFreq` 次。
- `(maxFreq - 1) * freq[maxFreq - 1] + maxFreq == len`，有一个值出现了 `maxFreq` 次，其它值均出现 `maxFreq - 1` 次。这时我们可以把前者删除一个。
	- 举个例子，`[1, 1, 2, 2, 3, 3, 4, 4, 4]`。
	- 扫描完整个数组，`maxFreq = 3, freq = {{2, 3}, {3, 1}}`


```cpp
class Solution {
public:
    int maxEqualFreq(vector<int>& nums)
    {
        unordered_map<int, int> freq, cnt;
        int n = nums.size(), res = 0;
        int maxFreq = 0;
        for (int i = 0; i < n; ++i)
        {
            int oldFreq = cnt[nums[i]];
            int newFreq = ++cnt[nums[i]];

            if (freq.count(oldFreq) && (--freq[oldFreq]) == 0)
                freq.erase(oldFreq);
            freq[newFreq]++;

            int len = i + 1;
            maxFreq = max(maxFreq, newFreq);
            if (maxFreq == 1 || maxFreq * freq[maxFreq] + 1 == len || (maxFreq - 1) * (freq[maxFreq - 1]) + maxFreq == len)
                res = len;
        }
        return res;
    }
};
```