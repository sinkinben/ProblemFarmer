## Lowest Common Ancestor

Problems:

- [236. Lowest Common Ancestor of a Binary Tree](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)
- [1644. Lowest Common Ancestor of a Binary Tree II](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree-ii/)
- [1650.  Lowest Common Ancestor of a Binary Tree III](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree-iii)
- [1676. Lowest Common Ancestor of a Binary Tree IV](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree-iv/)
- [235. Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)



## LCA

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the [definition of LCA on Wikipedia](https://en.wikipedia.org/wiki/Lowest_common_ancestor): “The lowest common ancestor is defined between two nodes `p` and `q` as the lowest node in `T` that has both `p` and `q` as descendants (where we allow **a node to be a descendant of itself**).”

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
```

**Example 3:**

```
Input: root = [1,2], p = 1, q = 2
Output: 1
```

**Constraints:**

- The number of nodes in the tree is in the range `[2, 105]`.
- `-10^9 <= Node.val <= 10^9`
- All `Node.val` are **unique**.
- `p != q`
- `p` and `q` will exist in the tree.

<br/>

**Solution**

Use **post-order** to solve this problem.

```cpp
class Solution 
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        return lca(root, p, q);
    }
    TreeNode* lca(TreeNode *node, TreeNode *p, TreeNode *q)
    {
        if (!node || !p || !q || node == p || node == q) return node;
        auto left =  lca(node->left, p, q);
        auto right = lca(node->right, p, q);
        if (left && right) return node;
        return left ? left : right;
    }
};
```





## LCA II

Given the `root` of a binary tree, return the lowest common ancestor (LCA) of two given nodes, `p` and `q`. **If either node `p` or `q` does not exist in the tree, return null.** All values of the nodes in the tree are unique.

According to the definition of LCA on Wikipedia: "The lowest common ancestor of two nodes `p` and `q` in a binary tree `T` is the lowest node that has both `p` and `q` as descendants (where we allow a node to be a descendant of itself)". A descendant of a node `x` is a node `y` that is on the path from node `x` to some leaf node.

**Follow up**: Can you find the LCA traversing the tree, without checking nodes existence?

**Example 1**

<img src="https://assets.leetcode.com/uploads/2018/12/14/binarytree.png" />

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
```

**Example 2**

<img src="https://assets.leetcode.com/uploads/2018/12/14/binarytree.png" />

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5. A node can be a descendant of itself according to the definition of LCA.
```

**Example 3**

<img src="https://assets.leetcode.com/uploads/2018/12/14/binarytree.png" />

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 10
Output: null
Explanation: Node 10 does not exist in the tree, so return null.
```

<br/>

**Solution**

- We should use **post-order** here.
- If one of `p` or `q` is found, we should not return, but record that `p` is found (or `q` is found).

```cpp
class Solution {
public:
    bool pflag = false, qflag = false;
    TreeNode *lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        auto res = lca(root, p, q);
        return pflag && qflag ? res : nullptr;
    }
    TreeNode *lca(TreeNode *node, TreeNode *p, TreeNode *q)
    {
        if (!node || !p || !q) return nullptr;
        auto left = lca(node->left, p, q);
        auto right = lca(node->right, p, q);
        if (node == p || node == q)
        {
            if (node == p) pflag = true;
            if (node == q) qflag = true;
            return node;
        }
        if (left && right) return node;
        return left ? left : right;
    }
};
```



## LCA III

Given two nodes of a binary tree `p` and `q`, return their lowest common ancestor (LCA).

Each node will have a reference to its parent node. The definition for Node is below:

```cpp
class Node {
    public int val;
    public Node *left;
    public Node *right;
    public Node *parent;
};
```

<br/>

**Solution**

It is similar to [160. Intersection of Two Linked Lists](https://leetcode-cn.com/problems/intersection-of-two-linked-lists/). We can solve it by hash-table or stacks.

```cpp
class Solution 
{
public:
    Node *lowestCommonAncestor(Node* p, Node * q) 
    {
        if (isSamePath(p, q)) return q;
        if (isSamePath(q, p)) return p;
        auto stk1 = getStack(p), stk2 = getStack(q);
        while (!stk1.empty() && !stk2.empty() && stk1.top() == stk2.top())
            stk1.pop(), stk2.pop();
        return !stk1.empty() ? stk1.top()->parent : stk2.top()->parent;
    }
    
    stack<Node *> getStack(Node *node)
    {
        stack<Node *> stk;
        for (auto p = node; p != nullptr; p = p->parent)
            stk.push(p);
        return stk;
    }
    
    Node *isSamePath(Node *bottom, Node *upper)
    {
        for (auto  p = bottom; p != nullptr; p = p->parent)
            if (p == upper) return p;
        return nullptr;
    }
};
```

But this code is terrible, and disgusting.

```cpp
class Solution 
{
public:
    Node *lowestCommonAncestor(Node* p, Node * q) 
    {
        auto p1 = p, p2 = q;
        while (p1 != p2)
        {
            p1 = (p1->parent ? p1->parent : q);
            p2 = (p2->parent ? p2->parent : p);
        }
        return p1;
    }
};
```



## LCA IV

Given the `root` of a binary tree and an array of `TreeNode` objects `nodes`, return the lowest common ancestor (LCA) of all the nodes in `nodes`. **All the nodes will exist in the tree**, and all values of the tree's nodes are **unique**.

**Example 1:**

<img src="https://assets.leetcode.com/uploads/2018/12/14/binarytree.png" />

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [4,7]
Output: 2
Explanation: The lowest common ancestor of nodes 4 and 7 is node 2.
```

**Example 2:**

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [1]
Output: 1
Explanation: The lowest common ancestor of a single node is the node itself.
```

**Example 3:**

<img src="https://assets.leetcode.com/uploads/2018/12/14/binarytree.png" />

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [7,6,2,4]
Output: 5
Explanation: The lowest common ancestor of the nodes 7, 6, 2, and 4 is node 5.
```

<br/>

**Solution**

```cpp
class Solution 
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) 
    {
        return lca(root, nodes);
    }
    
    TreeNode* lca(TreeNode *root, vector<TreeNode*> &nodes)
    {
        if (root == nullptr) return nullptr;
        
        auto itor = find(nodes.begin(), nodes.end(), root);
        if (itor != nodes.end()) return root;

        auto l = lca(root->left, nodes), r = lca(root->right, nodes);
        if (l && r) return root;
        return l ? l : r;
    }
};
```

Follow Up: What if some nodes in `nodes` vector do not exist in the given tree? 

Use post-order to check existence, which is similar to "1644. LCA II".

```cpp
class Solution 
{
public:
    int found = 0;
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) 
    {
        auto res = lca(root, nodes);
        return found == nodes.size() ? res : nullptr;
    }
    
    TreeNode* lca(TreeNode *root, vector<TreeNode*> &nodes)
    {
        if (root == nullptr) return nullptr;
        auto l = lca(root->left, nodes), r = lca(root->right, nodes);
        
        auto itor = find(nodes.begin(), nodes.end(), root);
        if (itor != nodes.end())
        {
            found += 1;
            return root;
        }
        if (l && r) return root;
        return l ? l : r;
    }
};
```



## LCA of BST

Same as "236. LCA", here the given binary tree is a BST.

```cpp
class Solution 
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        auto ptr = root;
        while (ptr)
        {
            if (ptr->val < p->val && ptr->val < q->val) ptr = ptr->right;
            else if (ptr->val > p->val && ptr->val > q->val) ptr = ptr->left;
            else break;
        }      
        return ptr;
    }
};
```

