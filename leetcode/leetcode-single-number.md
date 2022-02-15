## Single Number

Problems:

- [136. Single Number](https://leetcode.com/problems/single-number)
- [137. Single Number II](https://leetcode.com/problems/single-number-ii)
- [260. Single Number III](https://leetcode.com/problems/single-number-iii)



## Single Number

Given a **non-empty** array of integers `nums`, every element appears *twice* except for one. Find that single one.

You must implement a solution with a linear runtime complexity and use only constant extra space.

**Solution**

Utilize the property of XOR.

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int x : nums) res ^= x;
        return res;
    }
};
```



## Single Number II

Given an integer array `nums` where every element appears **three times** except for one, which appears **exactly once**. *Find the single element and return it*.

You must implement a solution with a linear runtime complexity and use only constant extra space.

**Solution**

Hash table. `O(n)` time and `O(1)` space.

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums)
    {
        int table[32] = {0};
        for (int x : nums)
            for (int i = 0; i < 32; ++i)
                table[i] += (x >> i) & 1;
        int res = 0;
        for (int i = 0; i < 32; ++i)
            if (table[i] % 3 != 0)
                res |= (1 << i);
        return res;
    }
};
```

Since each bit of `nums[i]` at most occur for three time, we can use two bit as a counter. That is we need `2 * 32 = 64` bits, hence we can use `uint64_t table` to replace `int table[32]` (which is `32 * 4 * 8 = 1024`  bits) .

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums)
    {
        uint64_t table = 0, idx = 0;
        for (uint64_t x : nums)
        {
            for (int i = 0; i < 32; ++i)
            {
                idx = 2 * i;
                table += ((x >> i) & 1) << idx;
                if (((table >> idx) & 3) == 3)
                    table ^= ((uint64_t)(3) << idx);
            }
        }
                
        int res = 0;
        for (int i = 0; i < 32; ++i)
        {
            idx = 2 * i;
            if (((table >> idx) & 3) == 1)
                res |= (1 << i);
        }
        return res;
    }
};
```



## Single Number III

Given an integer array `nums`, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. You can return the answer in **any order**.

You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.

**Solution**

- Suppose those two elements we want to find is `x` and `y`.
- XOR all the elements in `nums`, then the result `all = x ^ y`.
  - `all` must be not zero, otherwise `x == y`.
- Let `split = (all) & (-all)`, it will only keep right-most 1-bit, and clear the others.
  - The only remained 1-bit, comes from either `x` or `y`.
- Then we can divide the `nums` into two parts, one part is `nums[i] & split == 0`, and the another part is `nums[i] & split != 0`. And `x` and `y` must be in different parts.
- XOR all the elements that satisfy  `nums[i] & split != 0`, then the result `val` is one of those two element we want to find. The another we want to find is `all ^ val`.

```cpp
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums)
    {
        uint32_t all = 0;
        for (int x : nums) all ^= x;
        
        uint32_t split = all & (-all), val = 0;
        
        for (int x : nums)
            if (x & split) val ^= x;
        
        return {int(val), int(val ^ all)};
    }
};
```

