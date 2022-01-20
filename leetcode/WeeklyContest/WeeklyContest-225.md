## [leetcode] 周赛 225

🏆 比赛题目：https://leetcode-cn.com/contest/weekly-contest-225/

## 替换隐藏数字得到的最晚时间

题目：[5661. 替换隐藏数字得到的最晚时间](https://leetcode-cn.com/problems/latest-time-by-replacing-hidden-digits/)

签到题。

```cpp
class Solution {
public:
    string maximumTime(string time) {
        auto getint = [](char c) { return c == '?' ? -1 : c - '0'; };
        int a = getint(time[0]);
        int b = getint(time[1]);
        int c = getint(time[3]);
        int d = getint(time[4]);
        if (a == -1)
        {
            if (b == -1 || (0<=b && b<=3)) a = 2;
            else if (b >=4) a = 1;
        }
        if (b == -1)
        {
            if (a == 0 || a == 1) b = 9;
            else if (a == 2) b = 3;
        }
        if (c == -1) c = 5;
        if (d == -1) d = 9;   
        time[0] = a+'0', time[1] = b+'0', time[3] = c+'0', time[4] = d+'0';
        return time;
    }
};
```



## 满足三条件之一需改变的最少字符数

题目：[1737. 满足三条件之一需改变的最少字符数](https://leetcode-cn.com/problems/change-minimum-characters-to-satisfy-one-of-three-conditions/)

枚举三种情况，取最小值。

首先，把每个字符出现的次数记录在 `amap, bmap` 当中。

先考虑最简单的第三种情况，显然，要么把 2 个字符串都替换为在 `a` 出现次数最多的字符，要么都替换为在 `b` 出现次数最多的字符。

对于情况 1 和 2 ，本质上是一样的，因此只考虑第 1 种情况：

- 令 `a` 的所有字符都小于 `c` ，那么需要把大于 `c` 的字符全部替换，所需要的次数为 $\sum_{j=c}^{26}amap[j]$ .
- 令 `b` 的所有字符都大于 `c` ，那么需要把小于 `c` 的字符全部替换，所需要的次数为 $\sum_{j=0}^{c}bmap[j]$ .
- 对于特定的 `c` ，所需要的次数就是上述 2 个次数之和。

然后枚举 `c` ，取最小值即可。

代码：

```cpp
class Solution {
public:
    int minCharacters(string a, string b) {
        if (a.length() == 0) return b.length();
        if (b.length() == 0) return a.length();

        int amap[26] = {0}, bmap[26] = {0};
        int alen = a.length(), blen = b.length();
        for (char x: a) amap[x-'a']++;
        for (char x: b) bmap[x-'a']++;

        // 最大次数的字母
        int aidx = 0, bidx = 0;
        for (int i=0; i<26; i++)
        {
            if (amap[i] > amap[aidx]) aidx = i;
            if (bmap[i] > bmap[bidx]) bidx = i;
        }

        // case 3
        int ans = min(alen - amap[aidx] + blen - bmap[aidx],
                      blen - bmap[bidx] + alen - amap[bidx]);
        
        // case {1, 2}
        auto smaller = [&ans](int amap[26], int bmap[26])
        {
            for (int i=1; i<26; i++)
            {
                int total = 0;
                for (int j=i; j<26; j++) total += amap[j];
                for (int j=0; j<i; j++) total += bmap[j];
                ans = min(ans, total);
            }
        };
        smaller(amap, bmap), smaller(bmap, amap);
        return ans;
    }
};
```



## 找出第 K 大的异或坐标值

题目：[1738. 找出第 K 大的异或坐标值](https://leetcode-cn.com/problems/find-kth-largest-xor-coordinate-value/)

二维前缀和的思想（也可以说是 DP）。

定义 `dp[i][j]` 为：从 `[0,0]`开始，以 `[i,j]` 为右下角的的矩形内所有元素的异或的结果。

状态转移方程：

```text
dp[i, j] = dp[i-1, j] ^ dp[i, j-1] ^ dp[i-1, j-1] ^ matrix[i, j]
1 <= i < m, 1 <= j < n
```

边界情况：

```text
dp[0, j] = dp[0, j-1] ^ matrix[0, j]
dp[i, 0] = dp[i-1, 0] ^ matrix[i, 0]
```

根据题目意思，就是需要从数组 `dp` 中找出第 K 大的数字，这可以用：

- 优先队列：小顶堆队列最多保留 K 个数字，如果超过 K 个，那么丢弃堆顶。
- `set` : 把所有数字添加到 `set` ，最后不断 `erase(s.begin())` 直到 `set` 的大小为 K。

代码：

```cpp
class Solution
{
public:
    int kthLargestValue(vector<vector<int>> &matrix, int k)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return 0;
        int m = matrix.size(), n = matrix[0].size();
        multiset<int> s;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = matrix[0][0];
        s.insert(dp[0][0]);
        for (int i = 1; i < m; i++)
            dp[i][0] = dp[i - 1][0] ^ matrix[i][0], s.insert(dp[i][0]);
        for (int j = 1; j < n; j++)
            dp[0][j] = dp[0][j - 1] ^ matrix[0][j], s.insert(dp[0][j]);
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                dp[i][j] = dp[i][j - 1] ^ dp[i - 1][j] ^ dp[i - 1][j - 1] ^ matrix[i][j];
                s.insert(dp[i][j]);
            }
        }
        while ((int)s.size() > k) s.erase(s.begin());
        return *s.begin();
    }
};
```



最后一题是小学奥数题了，不想背（除非出原题，不然的话，该不会我还是不会 😅 ）。