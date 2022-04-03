## Find Leaves of Tree

Leetcode: [366. Find Leaves of Binary Tree](https://leetcode.com/problems/find-leaves-of-binary-tree), which is the most similar, not exactly.

Given the `root` of a binary tree, collect a tree's nodes as if you were doing this:

- Collect all the leaf nodes.
- Remove all the leaf nodes.
- Repeat until the tree is empty.

<img src="https://assets.leetcode.com/uploads/2021/03/16/remleaves-tree.jpg" />

**Example**

```text
Input: root = [1,2,3,4,5]
Output: [[4,5,3],[2],[1]]
Explanation:
[[3,5,4],[2],[1]] and [[3,4,5],[2],[1]] are also considered correct answers since per each level it does not matter the order on which elements are returned.
```



## Binary Tree

Given a binary tree (or a N-ary Tree), collect a tree's nodes as if you were doing this: Collect and remove all leaves, repeat until the tree is empty.

**Example**

```text
Input: [1,2,3,4,5]
          1
         / \
        2   3
       / \     
      4   5    
Output: [[4,5,3],[2],[1]]
```

<br/>

**Solution**

```cpp
class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode *root) {
        vector<vector<int>> res;
        vector<int> leaves;
        while (root) {
            leaves.clear();
            root = removeLeaves(root, leaves);
            res.push_back(leaves);
        }
        return res;
    }

    TreeNode *removeLeaves(TreeNode *node, vector<int> &leaves) {
        if (node == nullptr)
            return nullptr;
        if (!(node->left) && !(node->right)) {
            leaves.push_back(node->val);
            delete node;
            return node = nullptr;
        }
        node->left = removeLeaves(node->left, leaves);
        node->right = removeLeaves(node->right, leaves);
        return node;
    }
};
```

Obviously, the time complexity here is $O(N^2)$ . 



## N-ary Tree

What if we are given a N-ary Tree? 

Example

```text
Input:
      5
   /  |  \  \
  1   2   3   8
 /   / \   \
15  4   5   6 

Output:
[
  [15, 4, 5, 6, 8],
  [1, 2, 3],
  [5]
]
```

Suppose the `TreeNode` is :

```cpp
struct TreeNode {
    int val;
    vector<TreeNode *> children;
    TreeNode(int val) : val(val) { children.clear(); }
};
```

And here is my solution.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    vector<TreeNode *> children;
    TreeNode(int val) : val(val) { children.clear(); }
};

void preorder(TreeNode *node) {
    if (node == nullptr)
        return;
    cout << node->val << ' ';
    for (auto p : node->children)
        preorder(p);
}

class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode *root) {
        vector<vector<int>> res;
        vector<int> leaves;
        while (root) {
            leaves.clear();
            root = removeLeaves(root, leaves);
            res.emplace_back(leaves);
        }
        return res;
    }

    TreeNode *removeLeaves(TreeNode *node, vector<int> &leaves) {
        if (node == nullptr)
            return node;
        if (node->children.empty()) {
            leaves.push_back(node->val);
            delete node;
            return node = nullptr;
        }
        auto &children = node->children;
        for (size_t i = 0; i < children.size(); ++i) {
            children[i] = removeLeaves(children[i], leaves);
            // if children[i] becomes nullptr, we should remove it from node->children
            if (children[i] == nullptr) {
                children.erase(children.begin() + i);
                i -= 1;
            }
        }
        return node;
    }
};
```

