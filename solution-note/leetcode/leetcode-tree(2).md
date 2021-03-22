## [leetcode] tree-2

All questions are simple level.

## [Construct String from Binary Tree](https://leetcode-cn.com/problems/construct-string-from-binary-tree/)

Question[606]：You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way. The null node needs to be represented by empty parenthesis pair "()". And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.

**Example**

```
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     
Output: "1(2(4))(3)"
Explanation: Originallay it needs to be "1(2(4)())(3()())", but you need to omit all the unnecessary empty parenthesis pairs. And it will be "1(2(4))(3)".
```

**Solution**

Use pre-order traversal. These two methods is the same. The first one is implemented by passing arguments by reference. The second one is implemented by returned value.

```cpp
class Solution
{
public:
    string tree2str(TreeNode *t)
    {
        // string s = "";
        // preorder(t, s);
        // return s;
        return preorder2(t);
    }

    void preorder(TreeNode *p, string &s)
    {
        if (p == nullptr)
            return;
        string sval = to_string(p->val);
        string l, r;
        preorder(p->left, l);
        preorder(p->right, r);
        s += sval;
        bool lflag = (l != "");
        bool rflag = (r != "");
        if (lflag && rflag)
            s += "(" + l + ")(" + r + ")";
        if (!lflag && rflag)
            s += "()(" + r + ")";
        if (lflag && !rflag)
            s += "(" + l + ")";
    }

    string preorder2(TreeNode *p)
    {
        if (p == nullptr)
            return "";
        bool l = (p->left != nullptr);
        bool r = (p->right != nullptr);
        string sval = to_string(p->val);
        if (l && r)
            return sval + "(" + preorder2(p->left) + ")(" + preorder2(p->right) + ")";
        if (!l && r)
            return sval + "()(" + preorder2(p->right) + ")";
        if (l && !r)
            return sval + "(" + preorder2(p->left) + ")";
        return sval;
    }
};
```



## [Merge Two Binary Trees](https://leetcode-cn.com/problems/merge-two-binary-trees/)

Question[617]: Given two binary trees and imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not. You need to merge them into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of new tree.

**Solution**: Two versions, including recursion and iteration. 

+ Recursion version-1: create a completely new tree

  ```cpp
  class Solution
  {
  public:
      TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
      {
          TreeNode *root = nullptr;
          innerMerge(root, t1, t2);
          return root;
      }
      void innerMerge(TreeNode *&p, TreeNode *t1, TreeNode *t2)
      {
          bool flag1 = (t1 != nullptr);
          bool flag2 = (t2 != nullptr);
          if (flag1 && flag2)
              p = new TreeNode(t1->val + t2->val);
          else if (!flag1 && flag2)
              p = new TreeNode(t2->val);
          else if (flag1 && !flag2)
              p = new TreeNode(t1->val);
          else
              return;
          innerMerge(p->left, flag1 ? t1->left : nullptr, flag2 ? t2->left : nullptr);
          innerMerge(p->right, flag1 ? t1->right : nullptr, flag2 ? t2->right : nullptr);
      }
  };
  ```

+ Recursion version-2: directly modify on `t1`

  ```cpp
  class Solution
  {
  public:
      TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
      {
          return innerMerge(t1, t2);
      }
  
      TreeNode *innerMerge(TreeNode *t1, TreeNode *t2)
      {
          if (t1 == nullptr)
              return t2;
          if (t2 == nullptr)
              return t1;
          t1->val += t2->val;
          t1->left = innerMerge(t1->left, t2->left);
          t1->right = innerMerge(t1->right, t2->right);
          return t1;
      }
  };
  ```

+ Iteration-version implemented by pre-order traversal, modify on `t1` :

  ```cpp
  TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
  {
      return preorderMerge(t1, t2);
  }
  TreeNode *preorderMerge(TreeNode *t1, TreeNode *t2)
  {
      typedef pair<TreeNode *, TreeNode *> node;
      if (t1 == nullptr)
          return t2;
      stack<node> s;
      s.push(node(t1, t2));
      while (!s.empty())
      {
          node n = s.top();
          s.pop();
          if (n.second == nullptr)
              continue;
          n.first->val += n.second->val;
          if (n.first->left == nullptr)
              n.first->left = n.second->left;
          else
              s.push(node(n.first->left, n.second->left));
          if (n.first->right == nullptr)
              n.first->right = n.second->right;
          else
              s.push(node(n.first->right, n.second->right));
      }
      return t1;
  }
  ```


## [Average of Levels in Binary Tree](https://leetcode-cn.com/problems/average-of-levels-in-binary-tree/)

Question[637]: Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

**Example**

```
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation: The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
```

**Solution**

+ Level-order traversal. Use the map `sumrecord` to record the sum of each level. Use `numrecord` to record the number of nodes of each level.

  ```cpp
  vector<double> averageOfLevels(TreeNode *root)
  {
      typedef pair<TreeNode *, int> node;
      unordered_map<int, double> sumrecord;
      unordered_map<int, int> numrecord;
      queue<node> q;
      q.push(node(root, 0));
      while (!q.empty())
      {
          auto n = q.front();
          q.pop();
          sumrecord[n.second] += n.first->val;
          numrecord[n.second]++;
          if (n.first->left != nullptr)
              q.push(node(n.first->left, n.second + 1));
          if (n.first->right != nullptr)
              q.push(node(n.first->right, n.second + 1));
      }
      vector<double> v(numrecord.size());
      for (auto &x : sumrecord)
          v[x.first] = x.second / numrecord[x.first];
      return v;
  }
  ```

+ Level-order traversal. Only use queue, discard the help of `node` and `unordered_map`.

  ```cpp
  vector<double> levelorder(TreeNode *root)
  {
      vector<double> v;
      queue<TreeNode *> q;
      q.push(root);
      while (!q.empty())
      {
          queue<TreeNode *> nextlevel;
          int64_t sum = 0;
          int counter = 0;
          while (!q.empty())
          {
              auto p = q.front();
              q.pop();
              sum += p->val, counter++;
              if (p->left != nullptr)
                  nextlevel.push(p->left);
              if (p->right != nullptr)
                  nextlevel.push(p->right);
          }
          q = nextlevel;
          v.push_back(sum * 1.0 / counter);
      }
      return v;
  }
  ```

  

## [Two Sum IV - Input is a BST](https://leetcode-cn.com/problems/two-sum-iv-input-is-a-bst/)

Question[653]: Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

**Example**

```
Input: 
    5
   / \
  3   6
 / \   \
2   4   7
Target = 9
Output: True
Explanation: 9 = 3+6, 9 = 2+7, 9 = 4+5
```

**Solution**

First, implement a function named `search(root, val)` which is used to search `val` in a  tree `root`. Then, traversal the tree `root` to judge every node `p` whether there is another node `q` satisfies `p->val + q->val == k`.

```cpp
bool search(TreeNode *p, int val, TreeNode *exceptNode)
{
    if (p == nullptr)
        return false;
    if (p->val == val && p != exceptNode)
        return true;
    if (val < p->val)
        return search(p->left, val, exceptNode);
    return search(p->right, val, exceptNode);
}
bool levelorder(TreeNode *root, int k)
{
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        int val = k - p->val;
        if (search(root, val, p))
            return true;
        if (p->left != nullptr)
            q.push(p->left);
        if (p->right != nullptr)
            q.push(p->right);
    }
    return false;
}
```

## [Trim a Binary Search Tree](https://leetcode-cn.com/problems/trim-a-binary-search-tree/)

Question[669]: Given a binary search tree and the lowest and highest boundaries as L and R, trim the tree so that all its elements lies in [L, R] (R >= L). You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.

**Example-1**

```
Input-1: 
    1
   / \
  0   2
  L = 1
  R = 2
Output-1: 
    1
      \
       2
```

**Example-2**

```
Input-2: 
    3
   / \
  0   4
   \
    2
   /
  1
  L = 1
  R = 3
Output-2: 
      3
     / 
   2   
  /
 1
```

**Solution**

For each node of a BST, there are only three cases:

1. val < L
2. val > R
3. L <= val <= R

When val < L, for an example:

```
   parent            parent          parent
     |                 |               |
     9       ==>       9       ==>   right
    / \               / \        
left   right      null   right   
```

All values in the `left` sub-tree should be less than 9, hence the `left` sub-tree should be discarded. And because of '9' is less than `L`, hence it also should be discarded. The code to do these two operations is:

```cpp
p->left = nullptr, p = trim(p->right)
```

The case `val > R` is similar to case `val < L`.

For the case `L <= val <= R`, there is nothing to do on the `val` node. Just continue to trim on its left sub-tree and right sub-tree.

Version-1:

```cpp
TreeNode *trimBST(TreeNode *root, int L, int R)
{
    return innerTrim(root, L, R);
}
TreeNode *innerTrim(TreeNode *&p, int l, int r)
{
    if (p == nullptr)
        return nullptr;
    if (p->val < l)
    {
        p->left = nullptr;
        return p = innerTrim(p->right, l, r);
    }
    else if (p->val > r)
    {
        p->right = nullptr;
        return p = innerTrim(p->left, l, r);
    }
    else
    {
        p->left = innerTrim(p->left, l, r);
        p->right = innerTrim(p->right, l, r);
        return p;
    }
}
```

Version-2:

```cpp
TreeNode *trimBST(TreeNode *root, int L, int R)
{
    innerTrim2(root, L, R);
    return root;
}
void innerTrim2(TreeNode *&p, int l, int r)
{
    if (p == nullptr)
        return;
    if (p->val < l)
    {
        p->left = nullptr, p = p->right;
        innerTrim2(p, l, r);
        return;
    }
    else if (p->val > r)
    {
        p->right = nullptr, p = p->left;
        innerTrim2(p, l, r);
        return;
    }
    else
    {
        innerTrim2(p->left, l, r);
        innerTrim2(p->right, l, r);
    }
}
```

## [Second Minimum Node In a Binary Tree](https://leetcode-cn.com/problems/second-minimum-node-in-a-binary-tree/)

Question[671]: Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes. More formally, the property `root.val = min(root.left.val, root.right.val)` always holds. Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree. If no such second minimum value exists, output -1 instead.

**Example-1**

```
Input: 
    2
   / \
  2   5
     / \
    5   7

Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.
```

**Solution**

The smallest value in the tree is `root->val` (at level-0) . Hence the solution is to find the smallest value in all numbers greater (at level >= 1) than `root->val`.

```cpp
class Solution
{
public:
    int findSecondMinimumValue(TreeNode *root)
    {
        if (root == nullptr || root->left == nullptr)
            return -1;
        int minval = root->val;
        int result = -1;
        queue<TreeNode *> q;
        auto p = root;
        q.push(p);
        while (!q.empty())
        {
            p = q.front();
            q.pop();
            if (p->val > minval)
                result = result == -1 ? p->val : min(result, p->val);
            if (p->left)
                q.push(p->left);
            if (p->right)
                q.push(p->right);
        }
        return result;
    }
};
```



## [Search in a Binary Search Tree](https://leetcode-cn.com/problems/search-in-a-binary-search-tree/)

Question[700]: Given the root node of a binary search tree (BST) and a value. You need to find the node in the BST that the node's value equals the given value. Return the subtree rooted with that node. If such node doesn't exist, you should return NULL.

**Example**

```
Given the tree:
        4
       / \
      2   7
     / \
    1   3
And the value to search: 2
      2     
     / \   
    1   3
```

**Solution**

Simple question!

```cpp
class Solution
{
public:
    TreeNode *searchBST(TreeNode *root, int val)
    {
        return iterationSearch(root, val);
    }
    TreeNode *recursionSearch(TreeNode *p, int val)
    {
        if (p == nullptr)
            return nullptr;
        if (p->val == val)
            return p;
        else if (val < p->val)
            return recursionSearch(p->left, val);
        else
            return recursionSearch(p->right, val);
    }
    TreeNode *iterationSearch(TreeNode *root, int val)
    {
        auto p = root;
        while (p != nullptr)
        {
            if (p->val == val)
                return p;
            else if (val < p->val)
                p = p->left;
            else
                p = p->right;
        }
        return nullptr;
    }
};
```



## N-ary Tree

### [Maximum Depth of N-ary Tree](https://leetcode-cn.com/problems/maximum-depth-of-n-ary-tree/)

Question[559]: Given a n-ary tree, find its maximum depth. The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node. Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).

**Example**

```
Input: root = [1,null,3,2,4,null,5,6]
            1
          / | \
         3  2  4
        / \
       5   6
Output: 3
```

**Solution**

Level order traversal.

```cpp
#include "leetcode.h"
#include <queue>
class Node
{
public:
    int val;
    vector<Node *> children;
    Node() {}
    Node(int _val) { val = _val; }
    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};
class Solution
{
public:
    int maxDepth(Node *root)
    {
        return levelorder(root);
    }
    int levelorder(Node *root)
    {
        auto p = root;
        queue<Node *> q;
        q.push(p);
        int level = 1;
        while (!q.empty())
        {
            queue<Node *> nextlevel;
            while (!q.empty())
            {
                p = q.front(), q.pop();
                for (auto x : p->children)
                    nextlevel.push(x);
            }
            level += (!nextlevel.empty());
            q = nextlevel;
        }
        return level;
    }
};
```

### [N-ary Tree Preorder Traversal](https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/)

Question[589]: Given an n-ary tree, return the *preorder* traversal of its nodes' values.

**Example**

```
Input: root = [1,null,3,2,4,null,5,6]
            1
          / | \
         3  2  4
        / \
       5   6
Output: [1,3,5,6,2,4]
```

**Solution**

First step, we should have a look at perorder traversal of a binary tree, which is similar to open the door of fridge.

```cpp
stack s;
s.push(root);
while (!s.empty())
{
    p = s.top(), s.pop();
    print(p->val);
    if (p->right)  s.push(p->right);
    if (p->left)   s.push(p->left);
}
```

Second, put the elephant 🐘 into the fridge, including recursion method and iteration method.

```cpp
class Solution
{
public:
    vector<int> result;
    vector<int> preorder(Node *root)
    {
        if (root == nullptr)
            return result;
        preorderIteration(root);
        return result;
    }
    void preorderRecursion(Node *p)
    {
        if (p == nullptr)
            return;
        result.push_back(p->val);
        for (auto x : p->children)
            preorderRecursion(x);
    }
    void preorderIteration(Node *root)
    {
        auto p = root;
        stack<Node *> s;
        s.push(p);
        while (!s.empty())
        {
            p = s.top(), s.pop();
            result.push_back(p->val);
            for (auto i = p->children.rbegin(); i != p->children.rend(); i++)
            {
                s.push(*i);
            }
        }
    }
};
```

Third, close the door of the fridge. Submit the code.

### [N-ary Tree Postorder Traversal](https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/)

Question[590]: Given an N-ary tree, return the *postorder* traversal of its nodes' values.

**Example**

```
Input: root = [1,null,3,2,4,null,5,6]
            1
          / | \
         3  2  4
        / \
       5   6
Output: [5,6,3,2,4,1]
```

**Solution**

+ Recursion

  For a binary tree, postorder traversal is `left => right => root`. Hence the postorder traversal f a n-ary tree is `child[0,...,n] => root`.

  ```cpp
  vector<int> result;
  void postorderRecursion(Node *p)
  {
      if (p == nullptr)
          return;
      for (auto i = p->children.begin(); i != p->children.end(); i++)
          postorderRecursion(*i);
      result.push_back(p->val);
  }
  ```

+ Iteration

  Take a look at postorder traversal of binary tree.

  ```cpp
  postorder(TreeNode *root)
  {
      l = []
      auto p = root;
      stack<TreeNode *> s;
      s.push(p);
      while (!s.empty())
      {
          p = s.top(), s.pop();
          l.append(p->val);
          if (p->left)  s.push(p->left);
          if (p->right) s.push(p->right);
      }
      return reverse(l)
  }
  ```

  The postorder traversal of Nary-Tree is similar.

  ```cpp
  vector<int> result;
  void postorderIteration(Node *root)
  {
      auto p = root;
      stack<Node *> s;
      s.push(p);
      while (!s.empty())
      {
          p = s.top(), s.pop();
          result.push_back(p->val);
          for (auto x : p->children)
              s.push(x);
      }
      reverse(result.begin(), result.end());
  }
  ```

  

