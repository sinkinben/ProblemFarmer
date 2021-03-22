## [Leetcode] 位运算题解

## [子集](https://leetcode-cn.com/problems/subsets/)
题目[78]：给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。  

示例:

```
输入: nums = [1,2,3]
输出:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
```

本题做过好几遍了, 之前用的是回溯法, 本次使用的是位运算的思想。

位运算解法: 将 $nums$ 的每一个位置看作一个 $bit$，如果某个 $bit$ 为1，表示 $nums[i]$ 需要加入子集，否则不加入。显然，每个子集都对应一个比特串，比特串从 $0...0$ 到 $1...1$ 变化（也就从另外一个角度证明了子集的数目为 $2^n$ ）。   

下面举例说明，当 $ nums = [1,2] $ 时：

| 比特位 | 对应子集 |
|:------:|:--------:|
|  0 0   |   [ ]    |
|  0 1   |   [2]    |
|  1 0   |   [1]    |
|  1 1   |  [1,2]   |

位运算代码(C++)如下，算法复杂度为 $O(n 2^n)$ ：
```cpp
class Solution
{
public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> vv;
        int total = 1 << nums.size();
        for (int i = 0; i < total; i++)
        {
            vv.push_back(getItem(i, nums));
        }

        return vv;
    }

    vector<int> getItem(int n, const vector<int> &nums)
    {
        vector<int> v;
        for (int i = 0; i < nums.size(); i++)
        {
            if ((n >> i) & 0x1)
                v.push_back(nums[i]);
        }
        return v;
    }
};
```

回溯法代码(python)：
```python
class Solution:
    def __init__(self):
        self.ans = list()
        self.ans.append([])

    def subsets(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        cur = []
        self.helper(cur, nums)
        return self.ans

    def helper(self, cur: list, nums: list):
        for i in range(0, len(nums)):
            cur.append(nums[i])
            self.ans.append(list(cur))
            self.helper(cur, nums[(i + 1):])
            cur.pop()
```

C++ 回溯法

```cpp
class Solution
{
public:
    vector<vector<int>> ans;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<int> cur;
        vector<bool> table(nums.size(), false);
        ans.push_back(vector<int>(cur));
        backtrack2(nums, 0, cur, table);
        return ans;
    }

    void backtrack(vector<int> &v, int start, vector<int> &cur, vector<bool> &table)
    {
        for (int i = start; i < v.size(); i++)
        {
            if (table[i])
                return;
            cur.push_back(v[i]), table[i] = true;
            ans.push_back(cur), backtrack(v, start + 1, cur, table);
            cur.pop_back(), table[i] = false;
        }
    }
    void backtrack2(vector<int> &v, int start, vector<int> &cur, vector<bool> &table)
    {
        for (int i = start; i < v.size(); i++)
        {
            if (table[i])
                continue;
            cur.push_back(v[i]), table[i] = true;
            ans.push_back(vector<int>(cur)), backtrack(v, start + 1, cur, table);
            cur.pop_back(), table[i] = false;
        }
    }
};
```



## [只出现一次的数字](https://leetcode-cn.com/problems/single-number/)
题目[137]：给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

示例：

```
输入: [2,2,1]
输出: 1

输入: [4,1,2,1,2]
输出: 4
```

解题前，首先需要熟知 3 个结论：
+ $0 \oplus x = x$ 
+ $x \oplus x = 0$
+ $(x \oplus y) \oplus z = x \oplus (y \oplus z)$

这是异或的 3 个性质。回到本题，要求找出只出现 1 (或者说奇数次，本题方法依旧适用)。显然，只要某个 $k$ 出现偶数次，所有的 $k$ 异或结果是 0。对于出现奇数次的数字 $x$，所有的 $x$ 异或的结果是 $x$。

只要理解了上面 3 个结论，直接看代码:
```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int x = 0;
        for (auto k:nums)
        {
            x^=k;
        }
        return x;
    }
};
```



## [只出现一次的数字 II](https://leetcode-cn.com/problems/single-number-ii/)

题目[137]：给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。找出那个只出现了一次的元素。

示例：

```bash
输入: [2,2,3,2]
输出: 3
输入: [0,1,0,1,0,1,99]
输出: 99
```

本题与上一题类似，上一题是某个 $bit$ 出现 2 次 1，那么就将该 $bit$ 清零。本题是要求某个 $bit$ 出现 3 次 1，那么就将该 $bit$ 清零。下面举例进行说明：

```bash
input: [2,2,3,2]
2: 0 0 1 0
2: 0 0 1 0
3: 0 0 1 1
-----plus-----
t: 0 0 0 1
2: 0 0 1 0
-----plus-----
t: 0 0 1 1
```

从运算过程来看，实质上就是三进制加法（不考虑进位）。

解题思路：开一个数组 $countBit[32]$ 记录每个 $bit$ 相加的结果，如果 $countBit[i]$ 为 3，则置零。最后把 $countBit[32]$ 还原为一个 $int$ 。算法复杂度 $O(32N)$。

```cpp
class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int countBits[32] = {0};
        for (auto x : nums)
        {
            for (int i = 0; i < 32; i++)
            {
                countBits[i] = (countBits[i] + ((x >> i) & 0x1)) % 3;
            }
        }
        int ans = 0;
        for (int i = 0; i < 32; i++)
        {
            ans |= ((countBits[i]) << i);
        }
        return ans;
    }
};
```



## [只出现一次的数字 III](https://leetcode-cn.com/problems/single-number-iii/)

题目[260]：给定一个整数数组 `nums`，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。

示例：

```bash
输入: [1,2,1,3,2,5]
输出: [3,5]
```

先放异或运算的性质，设 $k = a \oplus b$ ，那么：
+ $k \oplus a = b$

+ $k \oplus b = a$

再看$x \& (-x)$ 的一个性质：
```bash
 x    = 1 0 1 0 1 0
-x    = 0 1 0 1 1 0
x&(-x)= 0 0 0 0 1 0
```
**$x\&(-x)$ 的作用是只保留 $x$ 中最低位的 1 。**

设只出现一次的元素为 $a$ 和 $b$，如果我们将 $nums$ 数组的所有元素进行异或运算，那么得到的结果 $k = a \oplus b$。

接下来，只需要找到 $a,b$ 的二者之一。

$mask=k\&(-k)$ 中只有一个 1 ，这个 1 要么来自 $a$，要么来自 $b$ ，并且只会来自二者之一，也即是：
+ `(mask & a) != 0, (mask & b)==0`
+ `(mask & b) != 0, (mask & a)==0`

只有上面 2 种情况会成立。下面直接 $Read \quad the \quad fucking \quad source \quad code.$

```cpp
class Solution
{
public:
    vector<int> singleNumber(vector<int> &nums)
    {
        int k = 0;
        for (auto x : nums)
            k ^= x;
        int mask = k & (-k);
        int y = 0;

        // find one of {a,b}
        for (auto x : nums)
        {
            if (mask & x) //ignore one of {a,b}
                y ^= x;
        }
        return vector<int>({y, k ^ y});
    }
};
```



## [多数元素](https://leetcode-cn.com/problems/majority-element/)

题目[169]：给定一个大小为 *n* 的数组，找到其中的多数元素。多数元素是指在数组中出现次数**大于** `⌊ n/2 ⌋` 的元素。

示例：

```bash
输入: [2,2,1,1,1,2,2]
输出: 2
```

解题思路：$Boyer-Moore$ 投票算法。初始假定 $nums[0]$ 为众数 $candidate$，扫描数组，如果 $x == candidate$ ，计数器加1，否则减1。只要计数器等于 0 ，我们就将 $nums$ 中之前访问的数字全部 **忘记** ，并把下一个数字当做候选的众数。下面举例说明：

```bash
nums: [7] 7 5 7 5 1 | [5] 7 | [5] 5 7 7 | [5] 5 5 5
cand: [7] 7 7 7 7 7 | [5] 5 | [5] 5 5 5 | [5] 5 5 5
flag: [1] 2 1 2 1 0 | [1] 0 | [1] 2 1 0 | [1] 2 3 4
```

如上图所示，`[x]` 的位置表示「重新开始寻找众数，状态回到初始状态」。可以发现，在符号 `|` 之前数字，「丢弃」之后并不影响数列中的众数，因为 $flag$ 为 0 表示有「若干个其他数字与众数抵消」。

```cpp
class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        int candidate = nums.front();
        int flag = 0;
        for (auto x : nums)
        {
            if (flag == 0)
                candidate = x;
            flag += (candidate == x) ? (1) : (-1);
        }
        return candidate;
    }
};
```



## [位1的个数](https://leetcode-cn.com/problems/number-of-1-bits/)

题目[191]：编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’ 的个数（也被称为[汉明重量](https://baike.baidu.com/item/汉明重量)）。

解题思路：
+ 循环和位移计数。
  ```cpp
  for i=0 to 31
      ans += (n>>i)&0x1
  ```
  
+ 利用 $n \& (n-1)$ 优化：该操作总是把 $n$ 的最低位的 1 置为 0 ，显然该方法直接「命中要害」。
  ```cpp
  /*
  n      = [... 1 0 0 ... 0]
  (n-1)  = [... 0 1 1 ... 1]
  n&(n-1)= [... 0 0 0 ... 0]
  */
  int hammingWeight(uint32_t n)
  {
      int ans = 0;
      while (n)
      {
          ans++;
          n &= (n - 1);
      }
      return ans;
  }
  ```



## [数字范围按位与](https://leetcode-cn.com/problems/bitwise-and-of-numbers-range/)

题目[201]：给定范围 $[m, n]$，其中 $0 \le m \le n \le 2147483647$，返回此范围内所有数字的按位与（包含 m, n 两端点）。

解题思路：利用 $n \& (n-1)$ 清空最低位的 1 ，那么对于 $[n\&(n-1), n]$ 这个区间，所有数字按位与的结果就是 $n_1=n\&(n-1)$。类似地，区间 $[n_1\&(n_1-1), n_1]$ 这个区间，所有数字按位与的结果是 $n_2=n_1\&(n_1-1)$。

最坏情况下，$m=0, n=(111...111)_2$ 时，区间的上下界每次缩减 $2^i$ 个单位，$i$ 表示第 $i$ 次循环。

```cpp
class Solution
{
public:
    int rangeBitwiseAnd(uint32_t m, uint32_t n)
    {
        while (m < n)
            n &= (n - 1);
        return n;
    }
};
```

再来看一下算法复杂度：显然，当 `m=0, n=0xFFFFFFFF`时，循环次数达到最大值 32 。



## [2的幂](https://leetcode-cn.com/problems/power-of-two/)

题目[231]：给定一个整数，编写一个函数来判断它是否是 2 的幂次方。

还是利用 $n\&(n-1)$，由于 $2^k$ 在二进制中肯定是 `...010...` 的形式（只有一个1）。需要考虑 $n\le0$ 的特殊情况。

```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n>0  && (n&(n-1)) == 0;
    }
};
```




## [4的幂](https://leetcode-cn.com/problems/power-of-four/)

题目[342]：给定一个整数 (32 位有符号整数)，请编写一个函数来判断它是否是 4 的幂次方。

解题思路：$4^k$ 这一类数字，二进制表示中唯一的一个 $1$ 必然在第 $2, 4, ..., 30$ 个比特位中（比特位从 0 开始计算），也就是 2 的偶数次幂。前面以实现了 2 的 $n$ 次幂的判断，现在的目标是区分 2 的偶数次幂与奇数次幂。

```bash
1  = 0000 0000 0001
4  = 0000 0000 0100
16 = 0000 0001 0000
64 = 0000 0100 0000
256= 0001 0000 0000
```

按照 4 比特划分，偶数次幂，也就是说，1 的位置出现在 `0001` 或者 `0100` （即为`*1*1` 的形式，奇数次幂则相反）。因此构造掩码 `mask = (1010 ... 1010) = 0xAAAA...AAA`，`power(4,k) & mask` 必然为 0 。

```cpp
bool isPowerOfFour(int n)
{
    return (n >= 1) && ((n & (n - 1)) == 0) && ((n & 0xAAAAAAAA) == 0);
}
```





## [缺失数字](https://leetcode-cn.com/problems/missing-number/)

题目[268]：给定一个包含 `0, 1, 2, ..., n` 中 *n* 个数的序列，找出 0 .. *n* 中没有出现在序列中的那个数。

+ 解法1：
  $k = \frac{n(n-1)}{2} - \sum_{i=0}^{len-1}nums[i]$
  
+ 解法2：
  下面以 `[3,2,0]` 例子，假如**在数组最后**补上缺失的数字 $1$：
  
  | $Index$  |  0   |  1   |  2   |  3   |
  | :------: | :--: | :--: | :--: | :--: |
  | $ nums $ |  3   |  2   |  0   | [1]  |
  
  显然，通过异或的交换律，可以得到：$\oplus_{i=0}^{len-1} (i \oplus nums[i]) = 0$，即：`k ^= nums[i]^i (i=0,...,len-1) => k=0`。
  
  如果缺失 1 ，我们在数组的最后补上 0 ：
  
  ```cpp
  // index xor num[index]
  k = (0 xor 3) xor (1 xor 2) xor (2 xor 0) xor (3 xor 0)
    = (0 xor 0) xor (1 xor 0) xor (2 xor 2) xor (3 xor 3)
    = 0 xor 1 xor 0 xor 0 xor 0
    = 1
  ```
  
  代码：
  
  ```cpp
  class Solution
  {
  public:
      int missingNumber(vector<int> &nums)
      {
          nums.push_back(0);
          int k = 0;
          for (size_t i = 0; i < nums.size(); i++)
              k ^= (i ^ nums[i]);
          return k;
      }
  };
  ```
  
## [最大单词长度乘积](https://leetcode-cn.com/problems/maximum-product-of-word-lengths/)

题目[318]：给定一个字符串数组 words，找到 length(word[i]) * length(word[j]) 的最大值，并且这两个单词不含有公共字母。你可以认为每个单词只包含小写字母。如果不存在这样的两个单词，返回 0。

示例：

```bash
输入: ["abcw","baz","foo","bar","xtfn","abcdef"]
输出: 16 
解释: 这两个单词为 "abcw", "xtfn"。
```

解题思路：将每个字母映射到 $int$ 中的一个 $bit$ 。比如，字符串 $abd$ 映射为 $(1011)_2$ 。如果两个字符串没有交集，那么两个 $int$ 取与必然为 0 。

```cpp
#define max(a, b) ((a) > (b) ? (a) : (b))
class Solution
{
public:
    int maxProduct(vector<string> &words)
    {
        vector<int> v;
        for (auto &s : words)
            v.push_back(hash(s));

        size_t ans = 0;
        size_t len = words.size();
        for (size_t i = 0; i < len; i++)
        {
            for (size_t j = i + 1; j < len; j++)
            {
                if ((v[i] & v[j]) == 0)
                    ans = max(ans, words[i].size() * words[j].size());
            }
        }
        return ans;
    }

    int hash(string &s)
    {
        int n = 0;
        for (auto x : s)
        {
            n |= (1 << (x - 'a'));
        }
        return n;
    }
};
```



## [比特位计数](https://leetcode-cn.com/problems/counting-bits/)

题目[338]：给定一个非负整数 **num**。对于 **0 ≤ i ≤ num** 范围中的每个数字 **i** ，计算其二进制数中的 1 的数目并将它们作为数组返回。

示例：

```bash
输入: 2
输出: [0,1,1]
输入: 5
输出: [0,1,1,2,1,2]
```

解题思路：设 $dp[i]$ 是数字 $i$ 的汉明重量（就是 1 的个数），那么下面 2 种递推式均成立：

+ $dp[i] = dp[i>>1] + (i\&1)$
+ $dp[i] = dp[i\&(i-1)] + 1$

```cpp
class Solution
{
public:
    vector<int> countBits(int num)
    {
        vector<int> v(num + 1);
        for (int i = 0; i <= num; i++)
        {
            v[i] = v[i >> 1] + (i & 0x1);
        }
        return v;
    }
};
```



## [两整数之和](https://leetcode-cn.com/problems/sum-of-two-integers/)
题目[371]：**不使用**运算符 `+` 和 `-` ，计算两整数 `a` 、`b` 之和。

解题思路：利用异或模拟加法（`a^b` 就是不带进位的二进制加法），关键点在于如何记录进位并处理进位。

```bash
a   = 0 1 1
b   = 0 0 1
-----------
a^b = 0 1 0
```

代码：

```cpp
#define getBit(a, i) (((a) >> i) & 0x1)
int getSum(int a, int b)
{
    int in = 0;
    int c = 0;
    for (int i = 0; i < 32; i++)
    {
        c |= (getBit(a, i) ^ getBit(b, i) ^ in) << i;
        in = (getBit(a, i) && getBit(b, i)) || (in && getBit(a, i)) || (in && getBit(b, i));
    }
    return c;
}
```

## [找不同](https://leetcode-cn.com/problems/find-the-difference/)

题目[389]：给定两个字符串 ***s*** 和 ***t***，它们只包含小写字母。字符串 **t** 由字符串 **s** 随机重排，然后在随机位置添加一个字母。请找出在 ***t*** 中被添加的字母。

示例：

```
输入：
s = "abcd"
t = "abcde"
输出：e
```

+ 解法1（**其实是错误解法**）

  原来的想法：将字符串映射为一个 $int$ ，与**最大单词长度乘积**做法一致。但需要考虑出现字符串为`""` 的特殊情况。

  出错原因：如果输入 `s="aaa", t="aa"`，显然无法做映射了。

+ 解法2

  异或。显然，除了「添加的字母」，其他的都在 $s,t$ 中成对出现。

  ```cpp
  class Solution
  {
  public:
      char findTheDifference(string s, string t)
      {
          char k = 0;
          for (auto x : s)
              k ^= x;
          for (auto x : t)
              k ^= x;
          return k;
      }
  };
  ```

  

## [UTF-8 编码验证](https://leetcode-cn.com/problems/utf-8-validation/)

题目[393]：点击上面的标题进入查看。

思路：一道模拟题。根据第一个字节的前缀，判断后面要继续读多少个字节。根据条件判断即可。

```cpp
class Solution
{
public:
    bool validUtf8(vector<int> &data)
    {
        for (size_t i = 0; i < data.size();)
        {
            uint8_t byte = data[i] & 0xff;
            int t = unitLength(byte);
            if (t == -1)
                return false;
            if (t == 0 && (byte >> 7) == 0x1)
                return false;
            // read the after t bytes, but i can not out of the data.size()
            while (t--)
            {
                i++;
                if (i >= data.size())
                    return false;
                data[i] &= 0xff;
                if (!((data[i] >> 6) == 2))
                {
                    return false;
                }
            }
            i++;
        }
        return true;
    }

    int unitLength(uint8_t n)
    {
        if ((n & ~0x7F) == 0)
            return 0;
        else if ((n & ~0xDF) == 0)
            return 1;
        else if ((n & ~0xEF) == 0)
            return 2;
        else if ((n & ~0xF7) == 0)
            return 3;
        return -1;
    }
};
```



## [整数替换](https://leetcode-cn.com/problems/integer-replacement/)

题目：
> 给定一个正整数 n，你可以做如下操作：
> 1. 如果 n 是偶数，则用 n / 2替换 n。
> 2. 如果 n 是奇数，则可以用 n + 1或n - 1替换 n。  
> n 变为 1 所需的最小替换次数是多少？

示例：

```
输入:8
输出:3
解释:8 -> 4 -> 2 -> 1

输入:7
输出:4
解释:7 -> 8 -> 4 -> 2 -> 1或7 -> 6 -> 3 -> 2 -> 1
```

解题思路：
+ 解法1：递归

  显然，题目描述就是递归的结构。值得注意的地方就是递归函数的参数不能为 $int$ ，因为需要进行 $n+1$ 的操作，当 $n = 2147483647$ 的时候，leetcode 就会抛出溢出异常。

  ```cpp
  class Solution
  {
  public:
      int integerReplacement(int n)
      {
          return helper(n);
      }
  
      int helper(uint32_t n)
      {
          if (n == 1)
              return 0;
          if (n % 2 == 0)
              return 1 + helper(n / 2);
          return 1 + min(helper(n + 1), helper(n - 1));
      }
  };
  ```

+ 解法2：位操作

  不用递归的话，关键在于找出 $n+1$ 和 $n-1$ 的决策条件。显然，我们想数字 $n$ 的二进制尽可能地接近 $(...100...00)_2$ 这种形式（让末尾有尽可能多的 $0$ ，这样除以 $2$ 之后仍然是一个偶数，不断进入偶数的分支）。

  当 $n$ 为奇数时，其末尾的 $2$ 个比特为 $(01)_2$ 或者 $(11)_2$ 。显然，对于前者应该减一，后者应该加一，这样才能够让「末尾有尽可能多的 $0$ 」。

  **但是**，提交之后发现输入为 $3$ 时，输出应为 $2(3 \rightarrow 2 \rightarrow 1)$。根据上述算法，$n$ 的变化过程是 $3 \rightarrow 4 \rightarrow 2 \rightarrow 1$，这是需要考虑的特殊情况。

  ```cpp
  int integerReplacement(int num)
  {
      uint32_t n = num;
      int k = 0;
      while (n > 1)
      {
          if (n & 0x1)
              n = ((n & 0x2) == 0) || (n == 3) ? (n - 1) : (n + 1);
          else
              n >>= 1;
          k++;
      }
      return k;
  }
  ```

## [二进制手表](https://leetcode-cn.com/problems/binary-watch/)

题目：进入链接自行查看。

解题思路：

+ 用 `uint16_t bits` 来表示时间。第 $0 - 5$ 比特表示分钟，第 $6 - 9$ 比特表示小时。那么 `bits >> 6` 可求出小时，`bits & 0x3f` 可求出分钟。
+ 遍历 `0x0 - 0x3FF` ，只有二进制中 $1$ 的个数为 $n$ 的，才求出字符串计入答案。（同时需要考虑小时数和分钟数要在合理的范围内）

```cpp
class Solution
{
public:
    vector<string> readBinaryWatch(int num)
    {
        vector<string> vs;
        for (uint16_t bits = 0; bits < 1024; bits++)
        {
            int h = bits >> 6;
            int m = (bits & 0x3f);
            if (0 <= h && h <= 11 && 0 <= m && m <= 59 && countOne(bits) == num)
                vs.push_back(format(h, m));
        }
        return vs;
    }

    string format(int h, int m)
    {
        stringstream ss;
        ss << h << ":";
        ss << setfill('0') << setw(2) << m;
        return ss.str();
    }

    int countOne(int n)
    {
        int k = 0;
        while (n)
            n &= (n - 1), k++;
        return k;
    }
};
```



## [数字转换为十六进制数](https://leetcode-cn.com/problems/convert-a-number-to-hexadecimal/)

题目：给定一个整数，编写一个算法将这个数转换为十六进制数。对于负整数，我们通常使用 补码运算 方法。注意:

> 十六进制中所有字母(a-f)都必须是小写。
> 十六进制字符串中不能包含多余的前导零。如果要转化的数为0，那么以单个字符'0'来表示；对于其他情况，十六进制字符串中的第一个字符将不会是0字符。 
> 给定的数确保在32位有符号整数范围内。
> 不能使用任何由库提供的将数字直接转换或格式化为十六进制的方法。

解题思路：

+ 解法1：循环迭代

  经典做法，但效率低下，复杂度为 $O(log_{16}{N})$。

  ```
  while (n)
  {
  	s+=tochar(n%16);
  	n/=16;
  }
  return reverse(s);
  ```

+ 解法2：位操作

  针对 $n$ 的每 4 个 bit（字节顺序从高到低）进行转换，算法复杂度 $O(1)$ 。

  ```cpp
  class Solution
  {
  public:
      const char *stdstr = "0123456789abcdef";
      string toHex(int n)
      {
          string hex;
          int k = sizeof(int) * 8 / 4 - 1;
          while (k > 0 && (((n >> (4 * k)) & 0x0f) == 0))
              k--;
          while (k >= 0)
              hex.append(1, stdstr[(n >> (4 * k--)) & 0x0f]);
          return hex;
      }
  };
  ```




## [数字的补数](https://leetcode-cn.com/problems/number-complement/)

题目：给定一个正整数，输出它的补数。补数是对该数的二进制表示取反（二进制表示不含前导零）。

示例：

```
输入: 5
输出: 2
解释: 5的二进制表示为101（没有前导零位），其补数为010。所以你需要输出2。
输入: 1
输出: 0
解释: 1的二进制表示为1（没有前导零位），其补数为0。所以你需要输出0。
```

解题思路：首先，第一想到的当然是 `~n` 。但是需要「丢弃」前导零的取反部分，那就是需要计算出二进制表示的有效位数，然后利用掩码保留有效长度。$Read \quad the \quad fucking \quad source \quad code !$

```cpp
class Solution
{
public:
    int findComplement(int n)
    {
        int k = ~n, t = 0;
        while (n)
            n >>= 1, t++;
        return k & ~((-1) << t);
    }
};
```







## [汉明距离总和](https://leetcode-cn.com/problems/total-hamming-distance/)

题目：两个整数的 [汉明距离](https://baike.baidu.com/item/汉明距离/475174?fr=aladdin) 指的是这两个数字的二进制数对应位不同的数量。计算一个数组中，任意两个数之间汉明距离的总和。

示例：

```
输入: 4, 14, 2
输出: 6
解释: 在二进制表示中，4表示为0100，14表示为1110，2表示为0010（这样表示是为了体现后四位之间关系），所以答案为：HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
```

先来看一下怎么求汉明距离：

```cpp
int hammingDistance(int a, int b)
{
    int k = a ^ b;
    int t = 0;
    while (k)
    	t++, k &= (k - 1);
    return t;
}
```

解题思路：

+ 暴力的 $O(n^2)$ 解法：当然是超时了。

+ 位操作

  我们不妨从每一个 $bit$ 的角度来看汉明距离。假如输入 `nums = [4,14,2,12,0]`：

  ```bash
  4  = 0 1 0 0 
  14 = 1 1 1 0
  2  = 0 0 1 0
  12 = 1 1 0 0
  0  = 0 0 0 0
  ```

  看每个数字的第 $1$ 比特（倒数第二列），可见有 2 个 1，3 个 0 。那么在这一个 bit 上，产生的汉明距离是多少呢？显然是 $ C_{2}^{1} \cdot C_{3}^{1} = 6 $ ，每个数字都是 32 bit ，总的汉明距离就是：
  $$
  total = \sum_{i=0}^{31}{one_i} \cdot {zero_i}
  $$
  $one_i$ 表示该 bit 上 1 的数目，而显然 $zero_i = len(nums) - one_i$ 。

  代码：

  ```cpp
  class Solution
  {
  public:
      int totalHammingDistance(vector<int> &nums)
      {
          size_t len = nums.size();
          vector<int> countOne(32, 0);
          for (auto x : nums)
          {
              for (int i = 0; i < 32; i++)
                  countOne[i] += (x >> i) & 0x1;
          }
          int sum = 0;
          for (int i = 0; i < 32; i++)
              sum += countOne[i] * (len - countOne[i]);
          return sum;
      }
  };
  ```

  时间复杂度为 $O(N)$ 。



## [交替位二进制数](https://leetcode-cn.com/problems/binary-number-with-alternating-bits/)

题目：给定一个正整数，检查他是否为交替位二进制数：换句话说，就是他的二进制数相邻的两个位数永不相等。

示例：

```
输入: 5
输出: True
解释:5的二进制数是: 101
输入: 11
输出: False
解释:11的二进制数是: 1011
```

位操作的题目都不难，但是在于一个字——「巧」。

解题思路：

+ 解法1：循环位移比较

  ```cpp
  bool hasAlternatingBits(int n)
  {
      while (n)
      {
          if (((n >> 1) & 0x1) == (n & 0x1))
              return false;
          n >>= 1;
      }
      return true;
  }
  ```

+ 解法2：构造掩码，检查 `n ^ ( n >> 1 )` 的有效二进制位是否为全 1 。注意特殊情况 $n=2147483647$ 时，leetcode 会抛出溢出异常。

  ```cpp
  bool hasAlternatingBits2(int num)
  {
      unsigned int n = num;
      n = n ^ (n >> 1);
      return ((n + 1) & n) == 0;
  }
  ```

  

## [子数组按位或操作](https://leetcode-cn.com/problems/bitwise-ors-of-subarrays/)

题目：我们有一个非负整数数组 A。对于每个（连续的）子数组 B = [A[i], A[i+1], ..., A[j]] （ i <= j），我们对 B 中的每个元素进行按位或操作，获得结果 A[i] | A[i+1] | ... | A[j]。返回可能结果的数量。 （多次出现的结果在最终答案中仅计算一次。）

示例：

```
输入：[1,1,2]
输出：3
解释：可能的子数组为 [1]，[1]，[2]，[1, 1]，[1, 2]，[1, 1, 2]。产生的结果为 1，1，2，1，3，3 。有三个唯一值，所以答案是 3 。
输入：[1,2,4]
输出：6
解释：可能的结果是 1，2，3，4，6，以及 7 。
```



解题思路：第一直觉是动态规划。首先，定义 $dp[i,j](i \le j)$ 为 $a[i] | ... | a[j]$ 的或值，那么就有状态转移方程为 $dp[i,j] = dp[i,j-1] | a[j]$ 。最终结果就是数组 $dp[n,n]$ 中值的个数。那么就有第一个版本的代码：

```cpp
int subarrayBitwiseORs(vector<int> &A)
{
    unordered_set<int> s;
    int len = A.size();
    vector<vector<int>> dp(len + 1, vector<int>(len + 1, 0));
    for (int i = 0; i < len; i++)
    {
        dp[i][i] = A[i], s.insert(dp[i][i]);
        for (int j = i + 1; j < len; j++)
        {
            dp[i][j] = dp[i][j - 1] | A[j], s.insert(dp[i][j]);
        }
    }
    return s.size();
}
```

显然从状态转移方程可以看出，可进行一维数组的空间优化，那么就有第二个版本的代码：

```cpp
int subarrayBitwiseORs2(vector<int> &A)
{
    unordered_set<int> s(A.begin(), A.end());
    int len = A.size();
    vector<int> dp(len + 1, 0);
    for (int i = 0; i < len; i++)
    {
        dp[i] = A[i];
        for (int j = i + 1; j < len; j++)
            dp[j] = dp[j - 1] | A[j], s.insert(dp[j]);
    }
    return s.size();
}
```

到这一步，还能进一步看出，$dp[j]$ 仅仅依赖于 $dp[j-1]$ ，显然可以用一个变量代替（而这个变量实质上也可以用 `A[i]` 来代替）：

```cpp
int subarrayBitwiseORs3(vector<int> &A)
{
    unordered_set<int> s(A.begin(), A.end());
    int len = A.size();
    int dp = 0;
    for (int i = 0; i < len; i++)
    {
        dp = A[i];
        for (int j = i + 1; j < len; j++)
            dp = dp | A[j], s.insert(dp);
    }
    return s.size();
}
```

但是，这种 $O(n^2)$ 的解法超时了。本题放弃了，[看题解](https://leetcode-cn.com/problems/bitwise-ors-of-subarrays/solution/dptan-xin-you-hua-bao-li-fang-fa-su-du-chao-100nei/)。



## [串联字符串的最大长度](https://leetcode-cn.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/)

题目：给定一个字符串数组 arr，字符串 s 是将 arr 某一子序列字符串连接所得的字符串，如果 s 中的每一个字符都只出现过一次，那么它就是一个可行解。请返回所有可行解 s 中最长长度。

示例：

```
输入：arr = ["un","iq","ue"]
输出：4
解释：所有可能的串联组合是 "","un","iq","ue","uniq" 和 "ique"，最大长度为 4。
输入：arr = ["cha","r","act","ers"]
输出：6
解释：可能的解答有 "chaers" 和 "acters"。
```

解题思路：本题好像跟位操作没关系，我用的是回溯法（也是经典的回溯题目了）。需要注意的地方是：`arr[i]` 可能本来就存在重复字符，因此需要先预处理。

```cpp
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
class Solution
{
public:
    int ans = 0;
    int maxLength(vector<string> &arr)
    {
        vector<string> v;
        for (auto &x : arr)
        {
            if (check2(x))
                v.push_back(x);
        }
        string s = "";
        backtrack(v, s, 0);
        return ans;
    }
    void backtrack(vector<string> &v, string &cur, int start)
    {
        for (int i = start; i < v.size(); i++)
        {
            if (!check(cur, v[i]))
                continue;
            cur += v[i];
            ans = max(ans, cur.length());
            backtrack(v, cur, i + 1);
            for (int j = 0; j < v[i].length(); j++)
                cur.pop_back();
        }
    }
    bool check(string &a, string &b)
    {
        for (auto x : b)
            if (a.find(x) != string::npos)
                return false;
        return true;
    }

    bool check2(string &s)
    {
        bool table[26] = {0};
        for (auto x : s)
        {
            if (table[x - 'a'])
                return false;
            table[x - 'a'] = true;
        }
        return true;
    }
};
```





## [或运算的最小翻转次数](https://leetcode-cn.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/)

题目：给你三个正整数 a、b 和 c。你可以对 a 和 b 的二进制表示进行位翻转操作，返回能够使按位或运算   a OR b == c  成立的最小翻转次数。「位翻转操作」是指将一个数的二进制表示任何单个位上的 1 变成 0 或者 0 变成 1 。

示例：

```
输入：a = 2, b = 6, c = 5
输出：3
解释：翻转后 a = 1 , b = 4 , c = 5 使得 a OR b == c
输入：a = 4, b = 2, c = 7
输出：1
输入：a = 1, b = 2, c = 3
输出：0
```

首先，如何计算两个 int 的不同的比特位的个数？

> 即：k = a ^ b 结果中，1 的比特位的个数（异或的性质: 相同为0，不同为1）。

题目要求： `(a | b) == c`
那么，令 `k = (a|b)^c` ，则 k 中比特位为 1 的位置就是需要「位翻转」的位置。

对 k 的每一个比特位扫描，**当且仅当 bit(k,i) == 1 需要翻转**，这时看 c 的当前比特位:

+ 如果 `bit(c,i) == 1` ，说明 `bit(a|b, i) == 0`，即 `bit(a, i) == 0 && bit(b, i) == 0`，只需要对 a 或者 b 进行一次翻转操作.  
+ 如果 `bit(c,i) == 0` ，说明 `bit(a|b, i) == 1` ，这时有 2 种情况: `bit(a,i), bit(b,i)` 的其中之一为 1或者**两者都为 1 **。 如果 `bit(a,i) == 1` 那么 a 需要翻转；`bit(b,i)==1` 同理。只有这样才能保证 `bit(a|b,i) = 0`。

```cpp
class Solution
{
public:
    int minFlips(int a, int b, int c)
    {
        int k = (a | b) ^ c;
        int ans = 0;
        for (int i = 0; i < 32; i++)
        {
            if ((k >> i) & 0x1)
            {
                if ((c >> i) & 0x1)
                {
                    ans++;
                }
                else
                {
                    ans += (a >> i) & 0x1;
                    ans += (b >> i) & 0x1;
                }
            }
        }
        return ans;
    }
};
```













## 面试题专栏

### [插入](https://leetcode-cn.com/problems/insert-into-bits-lcci/)

题目：[自己看](https://leetcode-cn.com/problems/insert-into-bits-lcci/)。

示例：

```
 输入：N = 10000000000, M = 10011, i = 2, j = 6
 输出：N = 10001001100
```

解题思路：构造掩码将 $N$ 的 $[i,j]$ 比特位清零。比如，此处 $N=(100 0000 0000)_2,i=2,j=6$，我们就构造掩码 $mask = not(000 0111 1100) = (111 1000 0011)_2$，那么 $N\&mask$ 就把 $[i,j]$ 位置的比特全部清零（方便后面 $M$ 的插入）。

最后就是怎么构造掩码的问题？其关键在于：怎么构造 $j-i+1$ 个 1 比特。 $Read \quad the \quad code!$

```cpp
int insertBits(int N, int M, int i, int j)
{
    uint32_t mask = ~((0xffffffff >> (32 - (j - i + 1))) << i);
    return (N & mask) | (M << i);
}
```



### [配对交换](https://leetcode-cn.com/problems/exchange-lcci/)

题目：配对交换。编写程序，交换某个整数的奇数位和偶数位，尽量使用较少的指令（也就是说，位0与位1交换，位2与位3交换，以此类推）。

示例：

```
 输入：num = 2（或者0b10）
 输出 1 (或者 0b01)
```

解题思路：每相邻的 2 个比特，当且仅当 `10` 或者 `01` 需要交换，交换的结果就是对这 2 个比特取反（通过异或11实现取反）。还是用了循环和一个临时变量，总感觉不舒服(>_<)。

```cpp
int exchangeBits(int num)
{
    for (int i = 30; i >= 0; i -= 2)
    {
        int t = (num >> i) & 0x3;
        if (t == 1 || t == 2)
            num ^= 0x3 << i;
    }
    return num;
}
```



### [最大数值](https://leetcode-cn.com/problems/maximum-lcci/)

题目：（不用比较运算实现最值）编写一个方法，找出两个数字`a`和`b`中最大的那一个。不得使用if-else或其他比较运算符。

解题思路：印象中本题是 `CSAPP` 一书中的位操作实验的知识点。构造 $k_1 \cdot a + k_2 \cdot b$ ，当 $a>b$ ，我们需要构造出 $(k_1,k_2)=(1,0)$ 。

我们不妨从反面考虑 $x \le y$ 的条件是什么？$x \le y$ 等价于下面 2 种情况：

+ $x,y$ 异号。 `sign(x) == 1 && sign(y) == 0 `，即：`sign(x) & (sign(y) ^ 1)`，其中 `sign(x) = (x >> 1) & 1` 。

+ $x,y$ 同号

  ```bash
  1. sign(x) == sign(y) => (sign(x)^sign(y)^1)
  2. x - y <= 0
  => x - y < 1
  => x + (~y + 1) < 1
  => x + (~y) < 0
  => sign(x+(~y))
  ```

  因此，$x,y$ 同号的情况下，$x \le y$ 当且仅当 `(sign(x) ^ sign(y) ^ 1) & sign(x + (~y))` 。

  设 `flag1 = sign(x) & (sign(y) ^ 1)` ，`flag2 = (sign(x) ^ sign(y) ^ 1) & sign(x + (~y))` ，那么 `flag1 | flag2` 就表示 $x \le y$ 。

考虑特殊情况，当出现数字 `2147483647` 或者 `-2147483648` 这种边界情况的时候，需要特别注意我们的计算过程是否出现溢出的情况？

显然，只有「异号」的情况才会溢出（同号数字进行减法运算，结果向 0 的方向靠近），但「异号」的情况我们是通过比较符号位来比较大小的（没有做任何运算），因此不会存在「运算」导致的溢出问题。

如果您仍未明白上面这一段话，可以代入下面 2 种情况：

+ $x=2147483647, y=-1$
+ $x=-2147483648, y=1$

去验证：

```
x <= y iff (flag1 | flag2)
```

是否仍然成立。

代码：

```cpp
#define sign(x) ((((x) >> 31) & 0x1))
class Solution
{
public:
    int maximum(int a, int b)
    {
        uint8_t x1 = sign(a) & (sign(b) ^ 1);
        uint8_t x2 = (sign(a) ^ sign(b) ^ 1) & sign((a + (~b)));
        uint8_t le = x1 | x2;
        return (le ^ 1) * a + b * le;
    }
};
```

看了题解，还有一种将 int 扩展为 long (8 bytes) 来处理溢出的牛逼方法（在本题不算作弊，但是在 CSAPP 的实验应该是不允许的）。

```cpp
int maximum2(int x, int y)
{
    long a = x, b = y;
    int less = (((a - b) >> 63) & 0x1);
    return (less ^ 1) * a + less * b;
}
```




## 总结

+ `n & (n-1)`：将最右边的 1 置为 0 。
+ `x & (-x)`：只保留最右边的 1 。
+ 构造掩码
+ 异或的性质
  - $ x \oplus 0 = x$
  - $x \oplus (11...11)_2 = not(x)$
  - $x \oplus x = 0$
  - $(x \oplus y) \oplus z = x \oplus (y \oplus z)$
  - 设 $k=a \oplus b$，那么 $k \oplus a = b, k \oplus b = a$ 。

剩下的题目就放在下一篇文章吧，偷懒把大多数简单和中等题做了 #(逃 。