## Sequence in Binary Tree

Problems:

- [687. Longest Univalue Path](https://leetcode-cn.com/problems/longest-univalue-path/)
- [298. Longest Consecutive Sequence](https://leetcode-cn.com/problems/binary-tree-longest-consecutive-sequence/)



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

