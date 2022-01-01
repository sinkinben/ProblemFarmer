## Backtracking

Backtracking tag of leetcode:

- Subset
- Subset - II
- N Queen

The backtracking solutions of most leetcode-problems have a similar pattern. Let's take a look on it.

## Subset

**1. Recursion (Backtrack)** - Time complexity is `O(2^n)`, and the depth of recursion is `O(n)`.

```cpp
class Solution {
public:
    vector<vector<int>> ret;
    vector<int> sub;
    int n;
    vector<vector<int>> subsets(vector<int>& nums) 
    {
        n = nums.size();
        backtrack(nums, 0);
        return ret;
    }
    
    void backtrack(vector<int>& nums, int idx)
    {
        ret.emplace_back(sub);
        for (int i = idx; i < n; ++i)
        {
            sub.emplace_back(nums[i]);
            backtrack(nums, i + 1);
            sub.pop_back();
        }
    }
};
```

<br/>

**2. Iteration** - Time complexity is still `O(2^n)`, while space complexity is `O(1)`.

For example, if `nums = [1, 2, 3]`, then the changing process of `subs` is:

```text
init  : {[]}
x = 1 : {[], [1]}
x = 2 : {[], [1], [2], [1, 2]}
x = 3 : {[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]}
```

Our code:

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> subs = {{}};
        for (int x : nums)
        {
            int n = subs.size();
            for (int i = 0; i < n; i++)
            {
                subs.emplace_back(subs[i]);
                subs.back().emplace_back(x);
            }
        }
        return subs;
    }
};
```

<br/>

**3. bitmap** - Here the time complexity is `O(2^N * N)`.

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) 
    {
        int n = nums.size();
        int total = 1 << n;
        vector<vector<int>> subs(total);
        for (int i = 0; i < total; ++i)
        {
            for (int j = 0; j < n; ++j)
                if ((i >> j) & 1) subs[i].emplace_back(nums[j]);
        }
        return subs;
    }
};
```





## Subset II

**1. Backtrack (recursion)** - It's similar to "Subset" above.

```cpp
class Solution {
public:
    int n;
    vector<vector<int>> ret;
    vector<int> sub;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        n = nums.size();
        backtrack(nums, 0);
        return ret;
    }
    
    void backtrack(vector<int> &nums, int idx)
    {
        ret.emplace_back(sub);
        for (int i = idx; i < n; ++i)
        {
            if (i > idx && nums[i] == nums[i - 1]) continue;
            sub.emplace_back(nums[i]);
            backtrack(nums, i + 1);
            sub.pop_back();
        }
    }
};
```

<br/>

**2. Iteration**

It's a little similar to "Subset - Iteration" above, but not totally. [See this explanation](https://leetcode.wang/leetCode-90-SubsetsII.html).

<img src="https://windliang.oss-cn-beijing.aliyuncs.com/90_2.jpg" style="width: 50%"/>

For "Interation Solution" of Subset, in the internal loop, we traverse all elements in the `subs`. Here we can not do so, since there are duplicate numbers.

As the figure shown above, if we still traverse all elements of `subs`, then we will add duplicate subsets into `subs` (the black ones). We need to fix this issue.

When we meet the duplicate number, such as second `2` above, we should not traverse all elements of `subs`. We just need to traverse the newest added ones (the orange elements in 3rd line).

Here we use variable `start` to store start-position of the newest elements.

```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> subs = {{}};
        int size = nums.size();
        int start = subs.size();
        for (int i = 0; i < size; ++i)
        {
            int n = subs.size();
            for (int j = 0; j < n; ++j)
            {
                if ((i > 0 && nums[i] == nums[i - 1]) && j < start)
                    continue;
                subs.emplace_back(subs[j]);
                subs.back().emplace_back(nums[i]);
            }
            start = n;
        }
        return subs;
    }
};
```



## Permutations

**1. Backtrack**

- We allocate a buffer `seq`, to store each permutation of `nums`.
- For each position of `seq[idx]`, we try to put every numbers `nums[i]` on it (unless `nums[i]` have been used) .
- Note that in the for-loop of backtrack function, we do not start at `idx`, while start at `0`. 
  - Why is it different from "Subset"?  From the perspective of consequence, Subset has `2^n` different states, while permutation has `n!` different states. The actual reason is that here each number must occur at least once in `seq`, while the situation in Subset is not.

```cpp
class Solution {
public:
    vector<vector<int>> ret;
    vector<int> seq;
    bool used[6] = {0};
    int n;
    vector<vector<int>> permute(vector<int>& nums) {
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

<br/>

## Permutation II

**1. Backtrack**

There are duplicate number, hence we need a little modification on the solution of "Permutations".

See the if-branch, we add a new skip condition `(i > 0 && nums[i] == nums[i - 1] && used[i - 1])` .

For example, if input `[1a, 1b, a]`

```text
seq           used       idx    comment
[1a]          [1 0 0]     0     
[1a 1b]       [1 1 0]     1     (this can not happend, step back)
[1b]          [0 1 0]     0     
[1b 1a]       [1 1 0]     1     (this can happen)
[1b 1a 2a]    [1 1 1]     2     (add seq into result)
```

Thus, we can also change the condition into  `(i > 0 && nums[i] == nums[i - 1] && !used[i - 1])` . It will put `1a` on the 1st position in above example.

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

## Combination Sum

**1. Backtracking**

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<int> seq;
    int n, target;
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        n = nums.size(), this->target = target;
        backtrack(nums, 0, 0);
        return res;
    }
    void backtrack(vector<int> &nums, int idx, int cur)
    {
        if (cur > target) return;
        if (cur == target)
        {
            res.emplace_back(seq);
            return;
        }
        for (int i = idx; i < n; ++i)
        {
            seq.emplace_back(nums[i]);
            backtrack(nums, i, cur + nums[i]);
            seq.pop_back();
        }
    }
};
```



## Combination Sum II

**1. Backtracking**

- Sort the `nums`
- If we meet the same value, then skip it. (See the if-branch below. )

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<int> seq;
    int n, target;
    vector<vector<int>> combinationSum2(vector<int>& nums, int target) 
    {
        sort(nums.begin(), nums.end());
        n = nums.size(), this->target = target;
        backtrack(nums, 0, 0);
        return res;
    }
    void backtrack(vector<int> &nums, int idx, int cur)
    {
        if (cur > target) return;
        if (cur == target)
        {
            res.emplace_back(seq);
            return;
        }
        for (int i = idx; i < n; ++i)
        {
            if (i > idx && nums[i] == nums[i - 1]) continue;
            seq.emplace_back(nums[i]);
            backtrack(nums, i + 1 , cur + nums[i]);
            seq.pop_back();
        }
    }
};
```

##  Palindrome Partitioning

TBD.



## N-Queen

TBD.



