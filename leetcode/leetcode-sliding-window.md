## 滑动窗口

滑动窗口可以分为固定长度窗口和非固定长度窗口两种类型。

- 对于非定长窗口，一般有最大窗口、最小窗口 2 种类型。
- 窗口一般可以用一个计数器、一个定长 `vector` 或者哈希表来表示。

Leetcode:

- [3. 无重复字符的最长子串](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/) - 非定长，最大窗口
- [1004. 最大连续1的个数 III](https://leetcode-cn.com/problems/max-consecutive-ones-iii/) - 非定长，最大窗口
- [1438. 绝对差不超过限制的最长连续子数组](https://leetcode-cn.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/) - 非定长，最大窗口
- [76. 最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring/) - 非定长，最小窗口
- [209. 长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/) - 非定长，最小窗口
- [567. 字符串的排列](https://leetcode-cn.com/problems/permutation-in-string/) - 定长
- [438. 找到字符串中所有字母异位词](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/) - 定长
- [1297. 子串的最大出现次数](https://leetcode-cn.com/problems/maximum-number-of-occurrences-of-a-substring/) - 定长



## 最大窗口

### 无重复字符的最长子串

非定长类型、求最大窗口。

给定一个字符串 `s` ，请你找出其中不含有重复字符的 **最长子串** 的长度。

```cpp
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_set<char> set;
        int n = s.length(), res = 0;
        int l = 0, r = 0;
        while (r < n)
        {
            while (l < r && set.count(s[r]))
                set.erase(s[l++]);
            while (r < n && !set.count(s[r]))
                set.emplace(s[r++]);
            res = max(res, r - l);
        }
        return res;
    }
};
```

或者是：

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) 
    {
        int n = s.length();
        int l = 0, r = 0;
        unordered_set<char> table;
        int ans = 0;
        while (r < n)
        {
            while (table.count(s[r])) table.erase(s[l++]);
            table.insert(s[r++]);
            ans = max(ans, (int)table.size());
        }
        return ans;
    }
};
```



### [最大连续1的个数 III](https://leetcode-cn.com/problems/max-consecutive-ones-iii/)

给定一个二进制数组 `nums` 和一个整数 `k`，如果可以翻转最多 `k` 个 `0` ，则返回 数组中连续 `1` 的最大个数。

```text
输入：nums = [1,1,1,0,0,0,1,1,1,1,0], K = 2
输出：6
解释：[1,1,1,0,0,1,1,1,1,1,1]
粗体数字从 0 翻转到 1，最长的子数组长度为 6。
```

**Solution**

最多允许窗口内有 K 个 0，求窗口的最大长度。

- 每次窗口增大 1 ，如果 0 的个数超过了 K ，那么从左侧收缩，把 0 移出去。

```cpp
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int l = 0, r = 0, res = 0, zero = 0;
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

模版写法：

```cpp
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int l = 0, r = 0, res = 0, zero = 0;
        while (r < n)
        {
            while (l < r && zero > k)  zero -= nums[l++] == 0;
            while (r < n && zero <= k) zero += nums[r++] == 0;
            if (zero <= k) res = max(res, n - l);
            else res = max(res, r - 1 - l);
        }
        return res;
    }
};
```

需要注意的是：

```cpp
if (zero <= k) res = max(res, n - l);
else res = max(res, r - 1 - l);
```

为什么呢？考虑 ` while (r < n && zero <= k)` 的条件：

- 如果是因为打破了 `zero <= k` 而跳出循环，这时候 `nums[r - 2], nums[r - 1] == 0, nums[r]`，有效的窗口应为 `[l, r-1)` .
- 如果是因为打破 `r < n` ，这时候有效窗口为 `[l, n)` 。

本题推荐第一种写法。



## 最小窗口

### 最小覆盖子串

非定长类型、求最小窗口。

给你一个字符串 `s` 、一个字符串 `t` 。返回 `s` 中涵盖 `t` 所有字符的最小子串。如果 `s` 中不存在涵盖 `t` 所有字符的子串，则返回空字符串 `""` 。

- 对于 `t` 中重复字符，我们寻找的子字符串中该字符数量必须不少于 `t` 中该字符数量。
- 如果 `s` 中存在这样的子串，我们保证它是唯一的答案。

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> source, target;
        for (char x: t) target[x]++;
        int n = s.length();

        if (n < (int)t.length()) return "";

        auto containsAll = [&]() {
            for (auto [k, v]: target)
                if (source[k] < v) return false;
            return true;
        };

        int l = 0, r = 0;        
        int minlen = 0x3f3f3f3f, pos = -1;
        while (r < n)
        {
            while (r < n && !containsAll()) source[s[r]]++, r++;
            while (l < r && containsAll()) source[s[l]]--, l++;
            // [l-1, r-1] is the interval that contains 't'
            if (minlen > r - l + 1) minlen = r - l + 1, pos = l - 1;
        }
        return pos == -1 ? "" : s.substr(pos, minlen);
    }
};
```



### [长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/)

给定一个含有 `n` 个正整数的数组和一个正整数 `target` 。

找出该数组中满足其和 `>= target` 的长度最小的连续子数组 `[nums[l], nums[l+1], ..., nums[r-1], nums[r]]` ，并返回其长度。如果不存在符合条件的子数组，返回 0 .

```text
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
```

<br/>

**Solution**

非定长，求最小窗口。

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = 0, sum = 0, res = INT_MAX;
        while (r < n)
        {
            while (r < n && sum < target) sum += nums[r++];
            while (l < r && sum >= target) sum -= nums[l++];
            /* [l - 1, r) is the window */
            if (l > 0 && sum + nums[l - 1] >= target)
                res = min(res, r - l + 1);
        }
        return res == INT_MAX ? 0 : res;
    }
};
```

或者是：

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = 0, sum = 0, res = INT_MAX;
        while (r < n)
        {
            sum += nums[r++];
            while (l < r && sum >= target) sum -= nums[l++];
            /* [l - 1, r) is the window */
            if (l > 0 && sum + nums[l - 1] >= target)
                res = min(res, r - l + 1);
        }
        return res == INT_MAX ? 0 : res;
    }
};
```



## 定长窗口

### 字符串的排列

给你两个字符串 `s1` 和 `s2` ，写一个函数来判断 `s2` 是否包含 `s1` 的排列。如果是，返回 `true` ；否则，返回 `false`。

换句话说，`s1` 的排列之一是 `s2` 的 **子串** 。

```text
输入：s1 = "ab" s2 = "eidbaooo"
输出：true
解释：s2 包含 s1 的排列之一 ("ba").
```

<br/>

**Solution**

定长窗口，窗口长度为 `n = s1.length()`。

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) return false;

        vector<int> v1(26, 0), v2(26, 0);
        for (char ch : s1) v1[ch - 'a']++;

        int n1 = s1.length(), n2 = s2.length();
        for (int i = 0; i < n2; ++i)
        {
            if (i >= n1)
                v2[s2[i - n1] - 'a']--;
            v2[s2[i] - 'a']++;
            if (v1 == v2) return true;
        }
        return false;
    }
};
```



### [找到字符串中所有字母异位词](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/)

给定两个字符串 `s` 和 `p`，找到 `s` 中所有 `p` 的 **异位词** 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

**异位词** 指由相同字母重排列形成的字符串（包括相同的字符串）。

```text
输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
```

<br/>

**Solution**

定长窗口，长度为 `p.length()` ，与 [567. 字符串的排列](https://leetcode-cn.com/problems/permutation-in-string/) 可以说一模一样。

```cpp
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (p.length() > s.length()) return {};
        vector<int> vs(26, 0), vp(26, 0);

        for (char ch : p) vp[ch - 'a']++;

        int slen = s.length(), plen = p.length();
        vector<int> res;
        for (int i = 0; i < slen; ++i)
        {
            if (i >= plen)
                vs[s[i - plen] - 'a']--;
            vs[s[i] - 'a']++;
            if (vs == vp)
                res.emplace_back(i + 1 - plen);
        }
        return res;
    }
};
```



### [子串的最大出现次数](https://leetcode-cn.com/problems/maximum-number-of-occurrences-of-a-substring/)

给你一个字符串 `s` ，请你返回满足以下条件且出现次数最大的 **任意** 子串的出现次数：

- 子串中不同字母的数目必须小于等于 `maxLetters` 。
- 子串的长度必须大于等于 `minSize` 且小于等于 `maxSize` 。

```text
输入：s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
输出：2
解释：子串 "aab" 在原字符串中出现了 2 次。
它满足所有的要求：2 个不同的字母，长度为 3 （在 minSize 和 maxSize 范围内）。
```

<br/>

**Solution**

> If a sub-string of size `minSize` repeats `k` times, then a sub-string of size `minSize + 1`, will repeat no more than `k` times. Therefore, the most frequent sub-string must be have size of `minSize`. 

定长滑动窗口，枚举每一个长度为 `size` 的子串，使用哈希表统计次数。

```cpp
class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        return maxFreq(s, maxLetters, minSize);
    }

    int maxFreq(string &s, int maxLetters, int size) {
        int n = s.length();
        int freq = 0;
        unordered_map<string, int> cnt;
        unordered_map<char, int> window;
        string sub;
        for (int i = 0; i < n; ++i)
        {
            if (i >= size)
            {
                if ((--window[s[i - size]]) == 0)
                    window.erase(s[i - size]);
                sub.erase(begin(sub));
            }
            sub.push_back(s[i]);
            window[s[i]]++;
            if (sub.length() == size && window.size() <= maxLetters)
                freq = max(freq, ++cnt[sub]);
        }
        return freq;
    }
};
```

优化代码长度，每次直接截取长度为 `size` 的子串：

```cpp
class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        return maxFreq(s, maxLetters, minSize);
    }

    int maxFreq(string &s, int maxLetters, int size) {
        int n = s.length(), freq = 0;
        unordered_map<string, int> cnt;
        string sub;
        for (int i = 0; i + size - 1 < n; ++i)
        {
            sub = s.substr(i, size);
            if (unordered_set<char>(begin(sub), end(sub)).size() <= maxLetters)
                ++cnt[sub], freq = max(freq, cnt[sub]);
        }
        return freq;
    }
};
```





## 模版

定长窗口：

```cpp
for (int i = 0; i < n; ++i)
{
    if (i >= width)
    {
        remove element[i - width] from the window;
    }
    add element[i] into the window;
    if (window is satisfied with something)
        ...
}
```

非定长模版，求最大/最小窗口需要自定义。

```cpp
int l = 0, r = 0;
while (r < n)
{
    while (l < r && conditions)
    {
        remove element[l] from the window;
        l++;
    }
    while (r < n && !condition)
    {
        add element[r] into the window;
        r++;
    }
    if (window is satisfied with something)
        ...
}
```

在内层循环中：

- 如果是求最大窗口，那么需要「先左侧收缩，后右侧扩张」，以达到求最大窗口的目的。例如，[3. 无重复字符的最长子串](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)。
- 如果是求最小窗口，那么需要「先右侧扩张，后左侧收缩」，以达到求最小窗口的目的。例如，[76. 最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring/) 和 [209. 长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/) 。

求最大或者最小窗口，其实最常用的是这个：

```cpp
int l = 0, r = 0;
while (n < r)
{
    add element[r++] into the windows;
    while (l < r && !condition)
        remove element[l++] from the window;
    
    if (window is satisfied with something)
        ...
}
```

