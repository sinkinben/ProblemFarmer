## [leetcode] tree-3

All questions are simple level.

## [Minimum Distance Between BST Nodes](https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes/)

Question[783]: Given a Binary Search Tree (BST) with the root node root, return the minimum difference between the values of any two different nodes in the tree.

**Example**

```
Input: root = [4,2,6,1,3,null,null]
Output: 1
Explanation: Note that root is a TreeNode object, not an array. The given tree [4,2,6,1,3,null,null] is represented by the following diagram:

          4
        /   \
      2      6
     / \    
    1   3  

while the minimum difference in this tree is 1, it occurs between node 1 and node 2, also between node 3 and node 2.
```

**Solution**

Inorder traversal, only once traversal.

```cpp
class Solution
{
public:
    int minDiffInBST(TreeNode *root)
    {
        return inorder2(root);
    }

    int inorder2(TreeNode *root)
    {
        bool first = true;
        int diff = 0x7ffffff;
        int pre = -1;
        auto p = root;
        stack<TreeNode *> s;
        while (p != nullptr || !s.empty())
        {
            if (p != nullptr)
            {
                s.push(p);
                p = p->left;
            }
            else
            {
                p = s.top(), s.pop();
                if (first)
                    pre = p->val, first = false;
                else
                    diff = min(diff, abs(p->val - pre)), pre = p->val;
                p = p->right;
            }
        }
        return diff;
    }

    int inorder(TreeNode *root)
    {
        vector<int> v;
        auto p = root;
        stack<TreeNode *> s;
        while (p != nullptr || !s.empty())
        {
            if (p != nullptr)
            {
                s.push(p);
                p = p->left;
            }
            else
            {
                p = s.top(), s.pop();
                v.push_back(p->val);
                p = p->right;
            }
        }
        int diff = abs(v[1] - v[0]);
        for (int i = 2; i < (int)v.size(); i++)
            diff = min(diff, abs(v[i] - v[i - 1]));
        return diff;
    }
};
```

## [Leaf-Similar Trees](https://leetcode-cn.com/problems/leaf-similar-trees/)

Question[872]: Consider all the leaves of a binary tree.  From left to right order, the values of those leaves form a leaf value sequence. Two binary trees are considered leaf-similar if their leaf value sequence is the same. Return true if and only if the two given trees with head nodes `root1` and `root2` are leaf-similar.

**Solution**

Inorder traversal.

```cpp
class Solution
{
public:
    bool leafSimilar(TreeNode *root1, TreeNode *root2)
    {
        return inorder(root1) == inorder(root2);
    }
    vector<int> inorder(TreeNode *root)
    {
        vector<int> v;
        auto p = root;
        stack<TreeNode *> s;
        while (!s.empty() || p != nullptr)
        {
            if (p != nullptr)
            {
                s.push(p);
                p = p->left;
            }
            else
            {
                p = s.top(), s.pop();
                if (p->left == nullptr && p->right == nullptr)
                    v.push_back(p->val);
                p = p->right;
            }
        }
        return v;
    }
};
```



## [Increasing Order Search Tree](https://leetcode-cn.com/problems/increasing-order-search-tree/)

Question[897]: Given a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree, and every node has no left child and only 1 right child.

**Example**

```
Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]
       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \ 
1        7   9
Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
 1
  \
   2
    \
     3
      \
       4
        \
         5
          \
           6
            \
             7
              \
               8
                \
                 9  
```

**Solution**

```cpp
TreeNode *increasingBST(TreeNode *root)
{
    return inorder(root);
}
TreeNode *inorder(TreeNode *oldRoot)
{
    TreeNode *newRoot = new TreeNode(-1);
    auto t = newRoot;
    auto p = oldRoot;
    stack<TreeNode *> s;
    while (p != nullptr || !s.empty())
    {
        if (p != nullptr)
            s.push(p), p = p->left;
        else
        {
            p = s.top(), s.pop();
            t->right = new TreeNode(p->val);
            t = t->right;
            p = p->right;
        }
    }
    return newRoot->right;
}
```

## [Range Sum of BST](https://leetcode-cn.com/problems/range-sum-of-bst/)

Question[938]: Given the root node of a binary search tree, return the sum of values of all nodes with value between L and R (inclusive). The binary search tree is guaranteed to have unique values.

**Example**

```
Input: root = [10,5,15,3,7,null,18], L = 7, R = 15
Output: 32
```

**Solution**

Three solutions.

+ Inorder traversal

```cpp
int inorder(TreeNode *root, int l, int r)
{
    int sum = 0;
    auto p = root;
    stack<TreeNode *> s;
    while (p != nullptr || !s.empty())
    {
        if (p)
            s.push(p), p = p->left;
        else
        {
            p = s.top(), s.pop();
            if (l <= p->val && p->val <= r)
                sum += p->val;
            else if (p->val > r)
                break;
            p = p->right;
        }
    }
    return sum;
}
```

+ Search by recursion

```cpp
int sum = 0;
void helper(TreeNode *root, int l, int r)
{
    if (root == nullptr)    return;
    if (root->val < l)      helper(root->right, l, r);
    else if (root->val > r) helper(root->left, l, r);
    else
    {
        sum += root->val;
        helper(root->left, l, r);
        helper(root->right, l, r);
    }
}
```

+ Search by iteration(stack)

```cpp
int search(TreeNode *root, int l, int r)
{
    int result = 0;
    auto p = root;
    stack<TreeNode *> s;
    s.push(p);
    while (!s.empty())
    {
        p = s.top(), s.pop();
        if (p == nullptr)
            continue;
        if (l <= p->val && p->val <= r)
        {
            result += p->val;
            s.push(p->right);
            s.push(p->left);
        }
        else if (p->val < l)
            s.push(p->right);
        else if (p->val > r)
            s.push(p->left);
    }
    return result;
}
```

## [Cousins in Binary Tree](https://leetcode-cn.com/problems/cousins-in-binary-tree/)

Question[993]: In a binary tree, the root node is at depth `0`, and children of each depth `k` node are at depth `k+1`. Two nodes of a binary tree are cousins if they have the same depth, but have different parents. We are given the root of a binary tree with unique values, and the values `x` and `y` of two different nodes in the tree. Return `true` if and only if the nodes corresponding to the values `x` and `y` are cousins.

**Solution**

Level order traversal.

```cpp
class Solution
{
public:
    bool isCousins(TreeNode *root, int x, int y)
    {
        if (root == nullptr)
            return false;
        queue<TreeNode *> q;
        TreeNode *xparent = nullptr, *yparent = nullptr;
        auto p = root;
        q.emplace(p);
        while (!q.empty())
        {
            queue<TreeNode *> nextlevel;
            while (!q.empty())
            {
                p = q.front(), q.pop();
                if (p->left)
                {
                    nextlevel.emplace(p->left);
                    if (x == p->left->val)
                        xparent = p;
                    if (y == p->left->val)
                        yparent = p;
                }
                if (p->right)
                {
                    nextlevel.emplace(p->right);
                    if (x == p->right->val)
                        xparent = p;
                    if (y == p->right->val)
                        yparent = p;
                }
            }
            q = nextlevel;
            // not found yet
            if (xparent == nullptr && yparent == nullptr)
                continue;
            // not same level
            if ((xparent == nullptr) ^ (yparent == nullptr))
                return false;
            // found at same level
            return xparent != yparent;
        }
        // can not be here
        return false;
    }
};
```

## [Sum of Root To Leaf Binary Numbers](https://leetcode-cn.com/problems/sum-of-root-to-leaf-binary-numbers/)

Question[1022]: Given a binary tree, each node has value `0` or `1`.  Each root-to-leaf path represents a binary number starting with the most significant bit.  For example, if the path is `0 -> 1 -> 1 -> 0 -> 1`, then this could represent 01101 in binary, which is 13. For all leaves in the tree, consider the numbers represented by the path from the root to that leaf. Return the sum of these numbers.

**Example**

```
Input: [1,0,1,0,1,0,1]
Output: 22
Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
```

**Solution**

Bit operation and back-track method(preorder traversal actually).  Use `val = (val << 1) | p->val` to record a path.

```cpp
class Solution
{
public:
    int sum = 0;
    int sumRootToLeaf(TreeNode *root)
    {
        preorder(0, root);
        return sum;
    }
    void preorder(int val, TreeNode *p)
    {
        if (p == nullptr)
            return;
        val = (val << 1) | p->val;
        if (p->left == nullptr && p->right == nullptr)
            sum += val;
        preorder(val, p->left);
        preorder(val, p->right);
    }
};
```

## Interview Questions

### [BiNode LCCI](https://leetcode-cn.com/problems/binode-lcci/)

Question[17.12]: The data structure `TreeNode` is used for binary tree, but it can also used to represent a single linked list (where left is null, and right is the next node in the list). Implement a method to convert a binary search tree (implemented with `TreeNode`) into a single linked list. The values should be kept in order and the operation should be performed in place (that is, on the original data structure). Return the head node of the linked list after converting.

**Example**

```
Input:  [4,2,5,1,3,null,6,0]
Output:  [0,null,1,null,2,null,3,null,4,null,5,null,6]
```

**Solution**

Inorder traversal.

```cpp
TreeNode *convertBiNode(TreeNode *root)
{
    TreeNode *newRoot = new TreeNode(-1);
    auto t = newRoot;
    auto p = root;
    stack<TreeNode *> s;
    while (!s.empty() || p != nullptr)
    {
        if (p)
        {
            s.emplace(p);
            p = p->left;
        }
        else
        {
            p = s.top(), s.pop();
            t->right = p, t = t->right;
            p = p->right;
        }
    }
    t = newRoot;
    while (t)
        t->left = nullptr, t = t->right;
    return newRoot->right;
}
```





