## 位操作题解 2 



## [重复的DNA序列](https://leetcode-cn.com/problems/repeated-dna-sequences/)

题目：所有 DNA 都由一系列缩写为 A，C，G 和 T 的核苷酸组成，例如：“ACGAATTCCG”。在研究 DNA 时，识别 DNA 中的重复序列有时会对研究非常有帮助。编写一个函数来查找 DNA 分子中所有出现超过一次的 10 个字母长的序列（子串）。（是个好题，请耐心看完优化的部分）

示例：

```
输入：s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
输出：["AAAAACCCCC", "CCCCCAAAAA"]
```

解题思路：显然，这里的序列都是连续的，因此最多只会有 $s.length - 10$ 种序列，因此采用数据结构 `map<string,int>` 进行计数即可。

```cpp
class Solution
{
public:
    vector<string> findRepeatedDnaSequences(string s)
    {
        unordered_map<string, int> m;
        vector<string> v;
        size_t len = s.length();
        for (int i = 0; (i + 9) < len; i++)
        {
            m[s.substr(i, 10)]++;
        }

        for (auto x : m)
        {
            if (x.second > 1)
                v.push_back(x.first);
        }
        return v;
    }
};
```

下面考虑如何优化，因为使用字符串作为 $key$ 值，效率低得令人发指（特别是使用的空间较大）。

从 leetcode 的海外版找到一个十分 geek 的 [优化方案](https://leetcode.com/problems/repeated-dna-sequences/discuss/53952/20-ms-solution-(C%2B%2B)-with-explanation)（[中文也有人翻译了一下](https://leetcode-cn.com/problems/repeated-dna-sequences/solution/bit-manipulation-8-ms-faster-than-9980-of-c96-mb-l/)）。建议阅读一下英文原文的三点优化思路，可以看出原作者的计算机基础十分好（特别是 C++  Runtime 这一块）。

简单来说，就是优化 map 的 `(key, val)` 的存储：

+ key ：不使用10个字符的子串作为 key 值，而是将其转化为若干比特位。
+ val ：不需要完整计算子串出现的次数，只需要记录 3 种状态：出现零次，出现一次，出现多次（编码表示为00, 01, 11, 实则是出现一个1就代表出现一次，因此只需要 2 bit）。

首先对 `ACGT` 四种字符编码： 。

```cpp
unordered_map<char, int> m = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
```

对于 10 个字符的子串，映射之后的值为：

```cpp
for (int i = 0; i < 10; i++)
    val = (val << 2) | m[s[i]];
```

一个 10 字符的子串 $substr$ ，只有 $4^{10}=2^{20}$ 种不同的形式，经过映射为一个 20bit 的数值之后，仍然只有 $2^{20}$ 种不同的值，那么在这 $[0,2^{20}-1]$ 这些数值当中，我们如何记录某个值 $val$ 是否出现呢？答案是使用一个 `bitset<(1<<20)> bs` 去记录，如果某个 `val` 出现，那么 `bs[val]=1 (bs.set(val))`。

到这一步解决了 key 的映射和存储，val 的「出现零次」和「出现一次」的问题也解决了，那么如何记录「出现多次」呢？上面已经提到，需要用到 2 bit 去记录，目前，某个 val 是否出现只用了 `bs[val]` 一个 bit 去记录，因此我们需要再添加一个 `bitset<1<<20> bs2` ：

+ 出现 0 次：`bs1[val]=0, bs2[val]=0`
+ 出现 1 次：`bs1[val]=1, bs2[val]=0`
+ 出现 2 次：`bs1[val]=1, bs2[val]=1`

```cpp
class Solution
{
public:
    unordered_map<char, int> m = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
    vector<string> findRepeatedDnaSequences2(string s)
    {
        int len = s.length();
        vector<string> v;
        if (len < 10)
            return v;
        uint32_t val = 0;              //val只需要低20bit
        uint32_t mask = (1 << 20) - 1; //低20位全1
        bitset<1 << 20> s1, s2;
        for (int i = 0; i < 10; i++)
            val = (val << 2) | m[s[i]];
        s1.set(val);

        for (int i = 10; i < len; i++)
        {
            val = ((val << 2) & mask) | m[s[i]];
            if (s2[val])
                continue;
            if (s1[val])
            {
                v.push_back(s.substr(i - 9, 10));
                s2.set(val);
            }
            else
            {
                s1.set(val);
            }
        }
        return v;
    }
};
```

时间复杂度 $O(N)$ ，对于空间的使用，`bitset<1<<20>` 看似很大但其实：

```cpp
int main()
{
    bitset<1 << 20> s;
    cout << 2 * sizeof(s) / 1024 << endl;
}
```

上面程序的输出是：`256 (KB)` 。而使用原始字符串作为 `key` 值，最坏情况下有 $2^{20}$ 种不同的字符串，每个字符串 10 个字节：$2^{20} \cdot 10 = 10 MB$  的空间开销。



## 面试题专栏

### [下一个数](https://leetcode-cn.com/problems/closed-number-lcci/)

题目：下一个数。给定一个正整数，找出与其二进制表达式中1的个数相同且大小最接近的那两个数（一个略大，一个略小）。

示例：

```
 输入：num = 2（或者0b10）
 输出：[4, 1] 或者（[0b100, 0b1]）
 输入：num = 1
 输出：[2, -1]
```

解题思路：细节巨多，还没完成。「正面刚」解法如下所述。

我们先了解一个预备知识：假如某个整数中， `bits[i]` 为 1 ，把它移动到 `bits[i + d]` 的位置（`bits[i+d]` 这个位置为 0 ），那么前后数值的变化为 $\Delta = 2^{i+d} - 2^i = 2^{i} \cdot (2^d-1)$ 。

对于 `01000100111011010101000010111110` ，找比它「最近大」的，肯定是把 1 向高位移动，并遵循以下原则： **把位于尽可能低位的 1 提高到尽可能低位的 0 （并要求两个位置尽可能地接近）** 。也就是：

```bash
   0100010011101101010100001 0  1 11110
=> 0100010011101101010100001 1  0 11110
```

但是这是不是就是要找的「最近大」的数值呢？显然不是，经过「放大」之后，还能适当缩小：

```bash
   0100010011101101010100001 0  1 11110
=> 0100010011101101010100001 1  0 11110
=> 0100010011101101010100001 1  0 01111
```

把位于**被移动的1**后面的那些1全部「挤」到最低位，显然这才是答案。

下面来看如何找「最近小」。操作必定是把高位的 1 向低位移动。并且还是遵循：**把位于尽可能低位的 1 降低到尽可能低位的 0 （并要求两个位置尽可能地接近）**。比如：

```bash
   00001010110000
=> 00001010101000
```

这是比较简单的情况，考虑到 `...00001111` 这种形式，如果省略号的位置都没有 1 ，那么显然找不到。如果有 1 ，那就是 `...10...0000111` 这种形式，比如 `0100 0000 1111`，那么：

```bash
   0100 0000 1111
=> 0010 0000 1111
```

同理，这里我们是缩小了，但其实还应该适当「放大」才是我们需要的答案：

```bash
   0100 0000 1111
=> 0010 0000 1111
=> 0011 1110 0000
```

把**被移动的1**后面的那些1全部排到后面。

完整代码：

```cpp
class Solution
{
public:
    vector<int> findClosedNumbers(int n)
    {
        vector<int> v({-1, -1});
        if (n == 0 || n == 0x7fffffff)
            return v;
        v[0] = bigger(n), v[1] = smaller(n);
        cout << v[0] << ' ' << v[1] << endl;
        return v;
    }
    int bigger(int n)
    {
        bitset<32> bits(n);
        int i = 0;
        while (bits[i] == 0)
            i++;
        int t = i;
        while (i < 31 && bits[i] == 1)
            i++;
        if (i >= 31)
            return -1;
        int ones = i - t;
        bits[i] = 1, bits[i - 1] = 0;
        uint32_t mask = ~((1 << (i - 1)) - 1);
        bits &= mask;
        i = 0;
        while (--ones)
            bits[i++] = 1;
        return (int)bits.to_ulong();
    }
    int smaller(int n)
    {
        bitset<32> bits(n);
        int i = 0;
        while (bits[i] == 0)
            i++;
        int j = i - 1;
        if (j != -1)
        {
            // ...1000 的形式
            bits[i] = 0, bits[j] = 1;
            return (int)bits.to_ulong();
        }
        else
        {
            // 到这里说明 i=0
            // ..0...1 的形式
            // 计算连续 i 个 1
            //肯定有 0, 不必担心越界
            while (bits[i] == 1)
                i++;
            int ones = i;

            while (i < 31 && bits[i] == 0)
                i++;
            // i=31, 可确定n=1
            if (i == 31)
                return -1;
            bits[i] = 0, bits[i - 1] = 1;
            uint32_t mask = ~((1 << (i - 1)) - 1);
            bits &= mask;
            while (ones--)
                bits[i - 2] = 1, i--;
            return (int)bits.to_ulong();
        }
    }

    void printBits(int num)
    {
        bitset<32> bits(num);
        cout << bits << endl;
    }
};
```

还有一个「正面刚」的方法，遍历，计算 1 的个数，如果与 n 相等就找到了，到 0 说明没找到，则是默认值 -1 。

```cpp
class Solution
{
public:
    vector<int> findClosedNumbers(int n)
    {
        vector<int> v({-1, -1});
        if (n == 0 || n == 0x7fffffff)
            return v;
        int t = n;
        int bench = hammingWeight(n);
        while (--t)
        {
            if (hammingWeight(t) == bench)
            {
                v[1] = t;
                break;
            }
        }
        t = n;
        while (++t)
        {
            if (hammingWeight(t) == bench)
            {
                v[0] = t;
                break;
            }
        }
        return v;
    }

    int hammingWeight(uint32_t n)
    {
        int t = 0;
        while (n)
            t++, n &= (n - 1);
        return t;
    }
};
```



### [翻转数位](https://leetcode-cn.com/problems/reverse-bits-lcci/)

题目：给定一个32位整数 `num`，你可以将一个数位从0变为1。请编写一个程序，找出你能够获得的最长的一串1的长度。

示例

```
输入: num = 1775(11011101111)
输出: 8
输入: num = 7(0111)
输出: 4
```

解题思路：暴力解法，遍历每个0，翻转，计算1的个数，取最大。

```cpp
#define bit(n, i) (((n) >> (i)) & 0x1)
class Solution
{
public:
    int reverseBits(int num)
    {
        int len = 0;
        bitset<32> bits(num);
        for (int i = 0; i < 32; i++)
        {
            if (bits[i] == 0)
            {
                bits[i] = 1;
                len = max(len, count((uint32_t)bits.to_ulong()));
                bits[i] = 0;
            }
        }
        return len;
    }

    int count(uint32_t n)
    {
        if (((int)n) == -1)
            return 32;
        if (n & (n - 1) == 0)
            return 1;
        int idx = 0;
        int len = 0;
        while (idx < 32 && bit(n, idx) == 0)
            idx++;

        for (int i = idx; i < 32; i++)
        {
            if (bit(n, i) == 0)
            {
                cout << idx << endl;
                len = max(len, i - idx);
                while (i < 32 && bit(n, i) == 0)
                    i++;
                idx = i;
            }
        }
        return len;
    }
};
```

### [交换数字](https://leetcode-cn.com/problems/swap-numbers-lcci/)

题目：编写一个函数，不用临时变量，直接交换`numbers = [a, b]`中`a`与`b`的值。

解题思路：异或的性质。

```cpp
class Solution {
public:
    vector<int> swapNumbers(vector<int>& numbers) {
        numbers[0]^=numbers[1]; //n[0]^n[1]
        numbers[1]^=numbers[0]; //n[1]=n[1]^n[0]^n[1]=n[0]
        numbers[0]^=numbers[1]; //n[0]=n[0]^n[1]^n[0]=n[1]
        return numbers;
    }
};
```

