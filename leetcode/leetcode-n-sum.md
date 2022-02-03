## N-Sum Problems

Two Sum:

- [1. Two Sum](https://leetcode.com/problems/two-sum)
- [167. Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted)
- [170. Two Sum III - Data structure design](https://leetcode.com/problems/two-sum-iii-data-structure-design)
- [653. Two Sum IV - Input is a BST](https://leetcode.com/problems/two-sum-iv-input-is-a-bst)
- [1214. Two Sum BSTs](https://leetcode.com/problems/two-sum-bsts)
- [1099. Two Sum Less Than K](https://leetcode.com/problems/two-sum-less-than-k)

3 Sum Problems:

- [15. 3Sum](https://leetcode.com/problems/3sum)
- [16. 3Sum Closest](https://leetcode.com/problems/3sum-closest)

4 Sum Problems:

- [454. 4Sum II](https://leetcode.com/problems/4sum-ii/)



## Two Sum

Given an array of integers `nums` and an integer `target`, return *indices of the two numbers such that they add up to `target`*.

You may assume that each input would have **exactly one solution**, and you may not use the *same* element twice.

You can return the answer in any order.

**Example**

```text
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
```

<br/>

**Solution**

```cpp
class Solution
{
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        unordered_map<int, int> table;
        int n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            int x = nums[i];
            if (table.count(target - x))
                return {table[target - x], i};
            table[x] = i;
        }
        return {};
    }
};
```



## Two Sum II - Sorted Array

Given a **1-indexed** array of integers `numbers` that is already **sorted in non-decreasing order**, find two numbers such that they add up to a specific `target` number. Let these two numbers be `numbers[index1]` and `numbers[index2]` where `1 <= index1 < index2 <= numbers.length`.

Return the indices of the two numbers, `index1` and `index2`, **added by one** as an integer array `[index1, index2]` of length 2.

The tests are generated such that there is **exactly one solution**. You **may not** use the same element twice.

**Constraints**

- `2 <= numbers.length <= 3 * 104`
- `-1000 <= numbers[i] <= 1000`
- `numbers` is sorted in **non-decreasing order**.
- `-1000 <= target <= 1000`
- The tests are generated such that there is **exactly one solution**.

<br/>

**Solution**

What we should consider here is: are there any solutions that cost `O(1)` space and `O(n)` time? The answer is yes.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        int l = 0, r = nums.size() - 1;
        while (l < r)
        {
            int val = nums[l] + nums[r];
            if (val == target) return {l + 1, r + 1};
            else if (val < target) ++l;
            else --r;
        }
        return {};
    }
};
```



## Two Sum III - Data Structure

Design a data structure that accepts a stream of integers and checks if it has a pair of integers that sum up to a particular value.

Implement the `TwoSum` class:

- `TwoSum()` Initializes the `TwoSum` object, with an empty array initially.
- `void add(int number)` Adds number to the data structure.
- `boolean find(int value)` Returns true if there exists any pair of numbers whose sum is equal to value, otherwise, it returns false.

**Constraints**

- `-10^5 <= number <= 10^5`
- `-2^31 <= value <= 2^31 - 1`
- At most `10^4` calls will be made to `add` and `find`.

<br/>

**Solution**

The problem mainly examines searching in the sorted data structures. Here we use `unordered_map`, and `add` will cost `O(1)` time, and `find` will cost `O(n)` time.

```cpp
class TwoSum
{
public:
    unordered_map<int64_t, int> cnt;
    void add(int x) { cnt[x]++; }
    bool find(int val)
    {
        for (auto [k, v] : cnt)
        {
            cnt[k] -= 1;
            if (cnt.count(val - k) && cnt[val - k] > 0)
            {
                cnt[k] += 1;
                return true;
            }
            cnt[k] += 1;
        }
        return false;
    }
};
```



## Two Sum IV - BST

Given the `root` of a Binary Search Tree and a target number `k`, return *`true` if there exist two elements in the BST such that their sum is equal to the given target*.

```cpp
class Solution
{
public:
    unordered_set<int> table;
    bool findTarget(TreeNode* root, int sum) { return preorder(root, sum); }
    bool preorder(TreeNode *node, int sum)
    {
        if (node == nullptr) return false;
        if (table.count(sum - node->val)) return true;
        table.emplace(node->val);
        return preorder(node->left, sum) || preorder(node->right, sum);
    }
};
```



## Two Sum - BSTs

Given the roots of two binary search trees, `root1` and `root2`, return true if and only if there is a node in the first tree and a node in the second tree whose values sum up to a given integer target.

**Example**

<img src="https://assets.leetcode.com/uploads/2021/02/10/ex1.png" />

```text
Input: root1 = [2,1,4], root2 = [1,0,3], target = 5
Output: true
Explanation: 2 and 3 sum up to 5.
```

<br/>

**Solution**

- Implement `contains(root2, val)`, to search `val` in the BST `root2`. This will cost `O(logn)` time.
- Traverse the BST `root1` (here we use in-order traversal), for each `node`, search `target - node->val` in `root2`.
- Total time complexity is `O(nlogn)`.

```cpp
class Solution
{
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target)
    {
        return inorder(root1, root2, target);
    }

    bool inorder(TreeNode *node, TreeNode *root, int target)
    {
        if (node == nullptr) return false;
        return inorder(node->left, root, target) || contains(root, target - node->val) || inorder(node->right, root, target);
    }

    /* Does BST `root` contain `val`? */
    bool contains(TreeNode *root, int val)
    {
        auto p = root;
        while (p)
        {
            if (val < p->val) p = p->left;
            else if (val > p->val) p = p->right;
            else return true;
        }
        return false;
    }
};
```



## Two Sum Less Than K

Given an array `nums` of integers and integer `k`, return the maximum `sum` such that there exists `i < j` with `nums[i] + nums[j] = sum` and `sum < k`. If no `i, j` exist satisfying this equation, return -1.

**Example**

```text
Input: nums = [34,23,1,24,75,33,54,8], k = 60
Output: 58
Explanation: We can use 34 and 24 to sum 58 which is less than 60.
```

<br/>

**Solution**

The brute force is the most straightward!

```cpp
class Solution
{
public:
    int twoSumLessThanK(vector<int>& nums, int k)
    {
        int res = -1;
        int n = nums.size();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
            {
                int val = nums[i] + nums[j];
                if (val < k) res = max(res, val);
            }
        return res;
    }
};
```

Sort the `nums`, and we can solve this problem in `O(nlogn)` time.

```cpp
class Solution
{
public:
    int twoSumLessThanK(vector<int>& nums, int k)
    {
        int res = -1, l = 0, r = nums.size() - 1;
        sort(nums.begin(), nums.end());
        while (l < r)
        {
            int val = nums[l] + nums[r];
            if (val < k) ++l, res = max(res, val);
            else if (val >= k) --r;
        }
        return res;
    }
};
```



## 3 Sum

Given an integer array nums, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

Notice that the solution set must not contain duplicate triplets.

We can solve this problem based on "Two Sum II - Sorted Array".

**1. Remove Duplicate by Set**

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n; ++i)
            twoSum(nums, 0 - nums[i], i);

        set<vector<int>> uniq(res.begin(), res.end());
        res.clear();
        for (auto &&x : uniq) res.emplace_back(x);
        return res;
    }

    void twoSum(vector<int> &nums, int target, int idx)
    {
        int n = nums.size();
        int l = idx + 1, r = n - 1;
        while (l < r)
        {
            if (nums[l] + nums[r] > target) r--;
            else if (nums[l] + nums[r] < target) l++;
            else
            {
                res.emplace_back(vector{nums[idx], nums[l], nums[r]});
                l++, r--;
            }
        }
    }
};
```

**2. Remove Duplicate by Skiping**

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            // skip the duplicate elements
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            twoSum(nums, 0 - nums[i], i);
        }
        return res;
    }

    void twoSum(vector<int> &nums, int target, int idx)
    {
        int n = nums.size();
        int l = idx + 1, r = n - 1;
        while (l < r)
        {
            if (nums[l] + nums[r] > target) r--;
            else if (nums[l] + nums[r] < target) l++;
            else
            {
                res.emplace_back(vector{nums[idx], nums[l], nums[r]});
                // skip the duplicate
                while (l + 1 < r && nums[l] == nums[l + 1]) l++;
                while (l < r - 1 && nums[r] == nums[r - 1]) r--;
                l++, r--;
            }
        }
    }
};
```



## 3Sum Cloest

Given an integer array `nums` of length `n` and an integer `target`, find three integers in `nums` such that the sum is closest to `target`.

Return *the sum of the three integers*.

You may assume that each input would have exactly one solution.



## 4 Sum II

Given four integer arrays `nums1`, `nums2`, `nums3`, and `nums4` all of length `n`, return the number of tuples `(i, j, k, l)` such that:

- `0 <= i, j, k, l < n`
- `nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0`
- `1 <= n <= 200`

**Solution**

```cpp
class Solution
{
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4)
    {
        int res = 0;
        unordered_map<int, int> cnt;
        for (int x : nums1) for (int y : nums2) cnt[x + y]++;
        for (int x : nums3) for (int y : nums4) res += cnt[0 - (x + y)];
        return res;
    }
};
```
