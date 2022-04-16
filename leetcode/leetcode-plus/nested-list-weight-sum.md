## [339. Nested List Weight Sum](https://leetcode-cn.com/problems/nested-list-weight-sum/)

You are given a nested list of integers `nestedList`. Each element is either an integer or a list whose elements may also be integers or other lists.

The depth of an integer is the number of lists that it is inside of. For example, the nested list `[1,[2,2],[[3],2],1]` has each integer's value set to its depth.

Return the sum of each integer in `nestedList` multiplied by its depth.

**Example - 1**

<img src="https://assets.leetcode.com/uploads/2021/01/14/nestedlistweightsumex1.png"/>

```
Input: nestedList = [[1,1],2,[1,1]]
Output: 10
Explanation: Four 1's at depth 2, one 2 at depth 1. 1*2 + 1*2 + 2*1 + 1*2 + 1*2 = 10.
```

**Example - 2**

```text
Input: nestedList = [1,[4,[6]]]
Output: 27
Explanation: One 1 at depth 1, one 4 at depth 2, and one 6 at depth 3. 1*1 + 4*2 + 6*3 = 27.
```

**Solution**

```cpp
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList, int depth = 1) {
        int n = nestedList.size();
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            if (nestedList[i].isInteger())
                sum += depth * nestedList[i].getInteger();
            else
                sum += depthSum(nestedList[i].getList(), depth + 1);
        }
        return sum;
    }
};
```





## [364. Nested List Weight Sum II](https://leetcode-cn.com/problems/nested-list-weight-sum-ii/)

You are given a nested list of integers `nestedList`. Each element is either an integer or a list whose elements may also be integers or other lists.

The depth of an integer is the number of lists that it is inside of. For example, the nested list `[1,[2,2],[[3],2],1]` has each integer's value set to its depth. Let `maxDepth` be the maximum depth of any integer.

The weight of an integer is `maxDepth - (the depth of the integer) + 1`.

Return the sum of each integer in nestedList multiplied by its weight.

<img src="https://assets.leetcode.com/uploads/2021/03/27/nestedlistweightsumiiex1.png" />

```
Input: nestedList = [[1,1],2,[1,1]]
Output: 8
Explanation: Four 1's with a weight of 1, one 2 with a weight of 2.
1*1 + 1*1 + 2*2 + 1*1 + 1*1 = 8
```

**Solution**

```cpp
class Solution {
public:
    int maxDepth = 1;
    vector<pair<int,int>> flattern;
    int depthSumInverse(vector<NestedInteger>& list) {
        dfs(list, 1);
        int res = 0;
        for (auto [val, depth] : flattern)
            res += val * (maxDepth - depth + 1);
        return res;
    }
    void dfs(vector<NestedInteger>& list, int depth = 1) {
        int n = list.size();
        maxDepth = max(maxDepth, depth);
        for (int i = 0; i < n; ++i)
        {
            if (list[i].isInteger())
                flattern.emplace_back(list[i].getInteger(), depth);
            else
                dfs(list[i].getList(), depth + 1);
        }
    }
};
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
```

