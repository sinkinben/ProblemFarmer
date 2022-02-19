## Sequence in Binary Tree

Problems:

- [687. Longest Univalue Path](https://leetcode-cn.com/problems/longest-univalue-path/)
- [298. Longest Consecutive Sequence](https://leetcode-cn.com/problems/binary-tree-longest-consecutive-sequence/)
- [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)
- [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)

To solve these problem, we should clearly know that what the returned value of a recursion function really means.



## Longest Univalue Path

Given the `root` of a binary tree, return *the length of the longest path, where each node in the path has the same value*. This path may or may not pass through the root.

**The length of the path** between two nodes is represented by the number of edges between them.

**Constraints:**

- The number of nodes in the tree is in the range `[0, 104]`.
- `-1000 <= Node.val <= 1000`
- The depth of the tree will not exceed `1000`.

**Example 1:**

<img src="https://assets.leetcode.com/uploads/2020/10/13/ex1.jpg" />

```
Input: root = [5,4,5,1,1,5]
Output: 2
```

**Example 2:**

<img src="https://assets.leetcode.com/uploads/2020/10/13/ex2.jpg" />

```
Input: root = [1,4,5,4,4,5]
Output: 2
```

<br/>

**Solution**

- Let `postorder(node)` denote the max **depth with same value** of sub-tree `node`. 
  - The depth here denote the number of **nodes**, not number of edges.
  - `nullptr`-node's depth is 0, and leaf-node's depth is 1.
  - For example-2, the max depth with same value of `root = 1`, is 1 (only itself).
- Traverse the tree in post-order.

```cpp
class Solution 
{
public:
    int res = 0;
    int longestUnivaluePath(TreeNode* root) 
    {
        postorder(root);
        return res >= 1 ? res - 1 : 0;
    }
    
    int postorder(TreeNode *node)
    {
        if (node == nullptr) return 0;
        int leftArrow = postorder(node->left);   // depth of left sub-tree
        int rightArrow = postorder(node->right); // depth of right sub-tree
		
        bool leftSame = (node->left && node->left->val == node->val);    // is same as left ?
        bool rightSame = (node->right && node->right->val == node->val); // is same as right ?
        

        int sameLength = 1 + (leftSame ? leftArrow : 0) + (rightSame ? rightArrow : 0);
        res = max(sameLength, res);
        
        // a non-nullptr node's depth is at least 1
        int ret = max(leftSame ? leftArrow + 1 : 1, rightSame ? rightArrow + 1 : 1);
        return ret;
    }
};
```



Another version of code, I think it's clearer.

```cpp
class Solution {
public:
    int res = 0;
    int longestUnivaluePath(TreeNode* root) {
        postorder(root);
        return res >= 1 ? res - 1 : 0;
    }
    
    /* The returned value denote the depth with same-value of current node,
     * and including the current node.
     */
    int postorder(TreeNode *node) {
        if (node == nullptr) return 0;
        int ldepth = postorder(node->left);
        int rdepth = postorder(node->right);
        
        int ret = 1;
        bool lsame = node->left && node->left->val == node->val;
        bool rsame = node->right && node->right->val == node->val;
        if (lsame) ret = 1 + ldepth;
        if (rsame) ret = max(ret, 1 + rdepth);

        /* compute the max unique path */
        if (lsame && rsame) res = max(res, ldepth + rdepth + 1);
        else if (lsame || rsame) res = max(res, (lsame ? ldepth : rdepth) + 1);
        else res = max(res, 1);

        return ret;
    }
};
```



## Binary Tree Longest Consecutive Sequence

Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes **from some starting node to any node in the tree** along the parent-child connections. The longest consecutive path **need to be from parent to child** (cannot be the reverse).

**Constraints:**

- The number of nodes in the tree is in the range `[1, 3 * 10^4]`.
- `-3 * 10^4 <= Node.val <= 3 * 10^4`

**Example 1:**

<img src="https://assets.leetcode.com/uploads/2021/03/14/consec1-1-tree.jpg"/>

```
Input:

   1
    \
     3
    / \
   2   4
        \
         5

Output: 3
Explanation: Longest consecutive sequence path is 3-4-5, so return 3.
```

**Example 2:**

<img src="https://assets.leetcode.com/uploads/2021/03/14/consec1-2-tree.jpg" />

```
Input:

   2
    \
     3
    /
   2
  /
 1

Output: 2
Explanation: Longest consecutive sequence path is 2-3, not 3-2-1, so return 2.
```

<br/>

**Pre-order Solution**

```cpp
class Solution 
{
public:
    int res = 0;
    int longestConsecutive(TreeNode* root) 
    {
        if (root == nullptr) return 0;
        preorder(root, 1);
        return res;
    }
    
    // `len` represent the depth with increasing values, and len >= 1
    void preorder(TreeNode *node, int len)
    {
        if (node == nullptr) return;
        res = max(res, len);
        preorder(node->left, node->left && node->left->val == node->val + 1 ? len + 1 : 1);
        preorder(node->right, node->right && node->right->val == node->val + 1 ? len + 1 : 1);
    }
};
```

<br/>

**Post-order Solution**

`postorder(node)` represent the depth with increasing values of sub-tree `node`.

```cpp
class Solution 
{
public:
    int res = 0;
    int longestConsecutive(TreeNode* root) 
    {
        postorder(root);
        return res;
    }
    
    int postorder(TreeNode *node)
    {
        if (node == nullptr) return 0;
        int l = postorder(node->left);
        int r = postorder(node->right);
        bool linc = node->left && node->left->val == node->val + 1;
        bool rinc = node->right && node->right->val == node->val + 1;
        int ret = max(linc ? l + 1 : 1, rinc ? r + 1 : 1);
        res = max(res, ret);
        return ret;
    }
};
```



## Binary Tree Maximum Path Sum

A **path** in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence **at most once**. Note that the path does not need to pass through the root.

The **path sum** of a path is the sum of the node's values in the path.

Given the `root` of a binary tree, return *the maximum **path sum** of any **non-empty** path*.

**Constraints:**

- The number of nodes in the tree is in the range `[1, 3 * 10^4]`.
- `-1000 <= Node.val <= 1000`

**Example**

<img src="https://assets.leetcode.com/uploads/2020/10/13/exx2.jpg" />

```text
Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
```

**Solution**

```cpp
class Solution {
public:
    int res = INT_MIN;
    int maxPathSum(TreeNode* root) {
        return max(res, postorder(root));
    }
    
    /* The returned value denote the max-value of two path:
     * 1) along node->left, the sum-up value of the left-path
     * 2) along node->right, the sum-up value of the right-path
     * Both of them should contain current node->val, 
     * and allow that there is ONLY node->val in the path
     */
    int postorder(TreeNode *node) {
        if (node == nullptr) return 0;
        int lsum = postorder(node->left);
        int rsum = postorder(node->right);
        res = max(res, node->val + (lsum > 0 ? lsum : 0) + (rsum > 0 ? rsum : 0));
        return max(lsum > 0 ? lsum : 0, rsum > 0 ? rsum : 0) + node->val;
    }
};
```



## Diameter of Binary Tree

Given the `root` of a binary tree, return *the length of the **diameter** of the tree*.

The **diameter** of a binary tree is the **length** of the longest path between any two nodes in a tree. This path may or may not pass through the `root`.

The **length** of a path between two nodes is represented by the number of edges between them.

**Example**

<img src="https://assets.leetcode.com/uploads/2021/03/06/diamtree.jpg" />

```text
Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
```

**Solution**

I think this is the most easy one to solve here.

```cpp
class Solution {
public:
    int res = 0;
    int diameterOfBinaryTree(TreeNode* root) {
        postorder(root);
        return res >= 1 ? res - 1 : 0;
    }
    
    /* The returned value denote the max-depth of current node,
     * and the depth should include the current node.
     */
    int postorder(TreeNode *node) {
        if (node == nullptr) return 0;
        int ldepth = postorder(node->left);
        int rdepth = postorder(node->right);
        res = max(res, 1 + ldepth + rdepth);
        return 1 + max(ldepth, rdepth);
    }
};
```

