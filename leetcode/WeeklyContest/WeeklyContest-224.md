## [leetcode] 周赛 224

🏆 比赛题目：https://leetcode-cn.com/contest/weekly-contest-224/

## 可以形成最大正方形的矩形数目

题目：[5653. 可以形成最大正方形的矩形数目](https://leetcode-cn.com/problems/number-of-rectangles-that-can-form-the-largest-square/)。

最大值出现的次数。

```cpp
class Solution {
public:
    int countGoodRectangles(vector<vector<int>>& rectangles) {
        unordered_map<int, int> m;
        for (auto &v: rectangles) m[min(v[0], v[1])]++;
        int maxkey = 0, maxval = 0;
        for (auto &[k,v]: m)
            if (k > maxkey) maxkey = k, maxval = v;
        return maxval;
    }
};
```

## 同积元组

题目：[5243. 同积元组](https://leetcode-cn.com/problems/tuple-with-same-product/)。

显然，任意取出 4 个不同的数字，按从小到大排列为 `{a,b,c,d}`，如果满足 `a * d == b * c `，那么这个序列一共能产生 8 个满足题目要求的同积元组。

因为数组长度最大为 1000，而暴力枚举时间复杂度为 $O(n^4)$ ，超时。

这是[两数之和](https://leetcode-cn.com/problems/two-sum/)的扩展。枚举每一对 `(a,b)` ，同时通过哈希记录 `a*b` 出现的次数，`m[t]` 表示满足 `a*b == t` 的 `(a,b)` 的数量。那么在枚举过程中 `m[a*b]` 就是使得 `(a,b,c,d)` 满足  `a*b==c*d` 的 `(c,d)`的数量。

```cpp
class Solution {
public:
    int tupleSameProduct(vector<int>& nums) 
    {
        unordered_map<int, int> m;
        int n = nums.size();
        int result = 0;
        int a, b;
        for (int i=0; i<n; i++)
        {
            a = nums[i];
            for (int j=i+1; j<n; j++)
            {
                b = nums[j];
                result += m[a*b];
                m[a*b]++;
            }
        }
        return result * 8;
    }
};
```

好吧，这周就 2 题了, Nothing more.