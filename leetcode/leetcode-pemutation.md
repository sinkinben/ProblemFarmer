## Permutation

Problems:

- [46. Permutations](https://leetcode.com/problems/permutations)
- [47. Permutations II](https://leetcode.com/problems/permutations-ii)
- [31. Next Permutation](https://leetcode.com/problems/next-permutation)
- [484. Find Permutation](https://leetcode.com/problems/find-permutation)
- [266. Palindrome Permutation](https://leetcode.com/problems/palindrome-permutation)
- [267. Palindrome Permutation II](https://leetcode.com/problems/palindrome-permutation-ii)
- [60. Permutation Sequence](https://leetcode.com/problems/permutation-sequence)



## Permutation

- Each element in `nums` is **unique**.
- Here we use backtracking strategy.
- Welcome to read "[A Pattern to Solve Backtracking Problems](https://github.com/sinkinben/leetcode/blob/master/solution-note/leetcode/leetcode-backtrack.md)".

```cpp
class Solution 
{
public:
    vector<vector<int>> ret;
    vector<int> seq;
    bool used[6] = {0};
    int n;
    vector<vector<int>> permute(vector<int>& nums) 
    {
        n = nums.size();
        seq.resize(n);
        backtrack(nums, 0);
        return ret;
    }

    void backtrack(vector<int> &nums, int idx)
    {
        if (idx >= n) 
        {
            ret.emplace_back(seq);
            return;
        }
        // here we do not start from idx
        // for position seq[idx], we try to put each number on it
        for (int i = 0; i < n; ++i)
        {
            if (used[i]) continue;
            seq[idx] = nums[i], used[i] = true;
            backtrack(nums, idx + 1);
            used[i] = false;
        }      
    }
};
```



## Permutation II

- There are duplicate numbers in `nums`, we need a little modification on the solution of "46. Permutations".
- See the if-branch, we add a new skip condition: `(i > 0 && nums[i] == nums[i - 1] && used[i - 1])` .

For example, if the input is `[1a, 1b, 2]`:

```text
seq           used       idx    comment
[1a ?  ?]     [1 0 0]     0     
[1a 1b ?]     [1 1 0]     1     (this can not happend, step back)
[1b ?  ?]     [0 1 0]     0     
[1b 1a ?]     [1 1 0]     1     (this can happen)
[1b 1a 2]     [1 1 1]     2     (add seq into result)
```

We can also change the condition into  `(i > 0 && nums[i] == nums[i - 1] && !used[i - 1])` . It will put `1a` on the 1st position in above example.

Here is the code.

```cpp
class Solution {
public:
    int n;
    vector<int> seq;
    vector<vector<int>> res;
    bool used[8] = {false};
    vector<vector<int>> permuteUnique(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        n = nums.size();
        seq.resize(n);
        backtrack(nums, 0);
        return res;
    }
    void backtrack(vector<int> &nums, int idx)
    {
        if (idx >= n)
        {
            res.emplace_back(seq);
            return;
        }
        for (int i = 0; i < n; ++i)
        {
            if (used[i] || (i > 0 && nums[i] == nums[i - 1] && used[i - 1])) continue;
            seq[idx] = nums[i], used[i] = true;
            backtrack(nums, idx + 1);
            used[i] = false;
        }
    }
};
```



## Next Permutation

- There are duplicate numbers in `nums`.
- Welcome to read [Cantor Expansion](https://www.cnblogs.com/sinkinben/p/15847869.html) first.

For this problem, a naive solution is:

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) { next_permutation(nums.begin(), nums.end()); }
};
```

but it will be not accepted by the interviewers. 

Now, let us have a look on [how the `next_permutation` implements](https://en.cppreference.com/w/cpp/algorithm/next_permutation).

```cpp
template<class BidirIt>
bool next_permutation(BidirIt first, BidirIt last)
{
    if (first == last) return false;
    BidirIt i = last;
    if (first == --i) return false;
 
    while (true) {
        BidirIt i1, i2;
 
        i1 = i;
        if (*--i < *i1) {
            i2 = last;
            while (!(*i < *--i2));
            std::iter_swap(i, i2);
            std::reverse(i1, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}
```

The basic idea is:

- We define `nums[0]` is the highest bit, and `nums[n - 1]` the lowest bit.
- We want to find a higher bit (as low as possible), and a low bit (which satisfies `nums[high] < nums[low]` and `nums[low]` is as small as possible), swap the high bit and low bit. This operation will make the "permutation" larger.

The algorithm is:

- From tail to head, find the first index `i` that satisfies `nums[i] < nums[i + 1]`.
- From `[i + 1, n)`, find the min value `nums[idx]`, among those numbers that are  (strictly) greater than `nums[i]`.
  - If there are duplicate numbers, we want `idx` as large as possible.
- Swap `nums[i]` and `nums[idx]`.
- Reverse the part of `[i + 1, n)`.

<img src="https://leetcode.com/media/original_images/31_Next_Permutation.gif" style="width: 50%"/>

```cpp
class Solution 
{
public:
    void nextPermutation(vector<int>& nums) 
    {
        int n = nums.size();
        if (n <= 1) return;
        
        int i = n - 2;
        while (i >= 0 && !(nums[i] < nums[i + 1])) i--;
        
        if (i >= 0)
        {
            int idx = i + 1;
            for (int j = i + 1; j < n; ++j)
                if (nums[j] > nums[i] && nums[idx] >= nums[j]) idx = j;
            swap(nums[i], nums[idx]);
        }
        
        reverse(nums.begin() + i + 1, nums.end());
    }
};
```

For the internal for-loop, we can scan from `j = n - 1` to `i + 1`.

```cpp
class Solution 
{
public:
    void nextPermutation(vector<int>& nums) 
    {
        int n = nums.size();
        if (n <= 1) return;
        
        int i = n - 2;
        while (i >= 0 && !(nums[i] < nums[i + 1])) i--;
        
        if (i >= 0)
        {
            int j;
            for (j = n - 1; j > i; --j)
                if (nums[j] > nums[i]) break;
            swap(nums[i], nums[j]);
        }
        
        reverse(nums.begin() + i + 1, nums.end());
    }
};
```



## Find Permutation

A permutation `perm` of `n` integers of all the integers in the range `[1, n]` can be represented as a string `s` of length `n - 1` where:

- `s[i] == 'I'` if `perm[i] < perm[i + 1]`, and

- `s[i] == 'D'` if `perm[i] > perm[i + 1]`.

Given a string `s`, re-construct the lexicographically smallest permutation `perm` and return it.

**Example 1:**

```text
Input: s = "I"
Output: [1,2]
Explanation: [1,2] is the only legal permutation that can represented by s, where the number 1 and 2 construct an increasing relationship.
```

**Example 2:**

```text
Input: s = "DI"
Output: [2,1,3]
Explanation: Both [2,1,3] and [3,1,2] can be represented as "DI", but since we want to find the smallest lexicographical permutation, you should return [2,1,3]
```

**Constraints:**

- `1 <= s.length <= 10^5`
- `s[i]` is either `'I'` or `'D'`.

<br/>

**Solution**

Our algorithm is:

- Fill `nums` with `1, 2, ..., n`.
- For some ranges of `s`, there will be `"DDD"`, reverse such ranges.

Let me explain it by an example.

```text
input   : s = "DI"
expected: [2, 1, 3]
--------
1. nums = [1, 2, 3]
2. s[0] = 'D', we should reverse nums[0, 1], since 'D' means that, nums[i] > nums[i + 1]
--------
input   : s = "DDI"
expected: [3, 2, 1, 4]
--------
1. nums = [1, 2, 3, 4]
2. s[0, 1] = "DD", we should reverse nums[0, 1, 2], i.e. nums = [3, 2, 1, 4]
```

Here is the code. Please note that `reverse(i, j + 1)` in STL means that we reverse the array of range `[i, j + 1) => [i, j]`.

```cpp
class Solution 
{
public:
    vector<int> findPermutation(string s) 
    {
        int size = s.length();
        int n = size + 1;
        vector<int> nums(n, 0);
        iota(nums.begin(), nums.end(), 1); // fill nums with 1, 2, ..., n
        
        for (int i = 0; i < size; ++i)
        {
            if (s[i] == 'D')
            {
                int j = i;
                while (j < n && s[j] == 'D') ++j;
                reverse(nums.begin() + i, nums.begin() + j + 1);
                i = j - 1;
			}
        }
        return nums;
    }
};
```



## Palindrome Permutation

Given a string `s`, return true if a permutation of the string could form a palindrome.

**Example**

```cpp
"code" -> false
"aab" -> true
"carerac" -> true
```

<br/>

**Solution**

```cpp
class Solution
{
public:
    bool canPermutePalindrome(string s) 
    {
        unordered_map<char, int> cnt;
        for (char x : s) cnt[x]++;
        int odd = 0;
        for (auto [key, val] : cnt) odd += (val & 1);
        return odd <= 1;
    }
};
```



## Palindrome Permutation II

Given a string `s`, return all the palindromic permutations (without duplicates) of it. You may return the answer in any order. If s has no palindromic permutation, return an empty list.

**Example 1:**

```
Input: s = "aabb"
Output: ["abba","baab"]
```

**Example 2:**

```
Input: s = "abc"
Output: []
```

**Constraints:**

- `1 <= s.length <= 16`
- `s` consists of only lowercase English letters.

**Solution**

We can't use brute force solution with $O(n!)$ time since `s.length <= 16`.

Consider using backtracking strategy.

- Same as "Palindrome Permutation", we use `s` to construct a `map<char, int> table`, which records the number of occurrences of each letter.
- The should be **0 or 1** odd value in `table`. And the key of the unique odd value is the middle letter in the palindrome permutations.
- Now, we need to find all the `perm` to construct `(perm) + middle + reverse(perm)`, and put them into `res`. Hence we use backtracking here.

```cpp
class Solution {
public:
    vector<string> res;
    string perm;
    int n;
    string mid = "";
    vector<string> generatePalindromes(string s) 
    {
        n = s.length();
        unordered_map<char, int> table;
        for (char x : s) table[x]++;
        
        // the middle char in the palindrome string
        unordered_set<char> middles;
        for (auto [ch, val] : table)
            if (val & 1) middles.emplace(ch);
        
        // if `s` can not consist of any palindrome string
        if (middles.size() > 1) return res;
        
        // there maybe no `middle` char in the palindrome string, since `n` is even number
        if (!middles.empty()) 
            mid.push_back(*middles.begin()), table[*middles.begin()] -= 1;
        
        // now, all values in `table` is even number
        for (auto &[key, val] : table) val /= 2;
        
        perm.resize(n / 2);
        backtrack(table, 0);
        return res;
    }
    
    void backtrack(unordered_map<char, int> &map, int idx)
    {
        if (idx >= n / 2)
        {
            string pal = perm;
            reverse(pal.begin(), pal.end());
            res.emplace_back(pal + mid + perm);
            return;
        }
        for (auto &[ch, val] : map)
        {
            if (val > 0)
            {
                perm[idx] = ch, val -= 1;
                backtrack(map, idx + 1);
                val += 1;
            }
        }
    }
};
```

 



## Permutation Sequence

See this article:  [Cantor Expansion](https://www.cnblogs.com/sinkinben/p/15847869.html) .



