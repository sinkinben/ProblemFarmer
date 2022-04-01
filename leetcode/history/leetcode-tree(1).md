## [leetcode] tree-1

均为 Simple 难度的水题。

## [二叉树的中序遍历](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)

题目[94]：给定一个二叉树，返回它的*中序* 遍历。

解题思路：Too simple. 

```cpp
class Solution
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        return inorderNonRec(root);
        vector<int> v;
        innerTraversal(root, v);
        return v;
    }

    void innerTraversal(TreeNode *p, vector<int> &v)
    {
        if (p == nullptr)
            return;
        innerTraversal(p->left, v);
        v.push_back(p->val);
        innerTraversal(p->right, v);
    }

    vector<int> inorderNonRec(TreeNode *root)
    {
        vector<int> v;
        if (root != nullptr)
        {
            stack<TreeNode *> s;
            auto p = root;
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
                    v.push_back(p->val);
                    p = p->right;
                }
            }
        }
        return v;
    }
};
```



## [相同的树](https://leetcode-cn.com/problems/same-tree/)

题目[100]：给定两个二叉树，编写一个函数来检验它们是否相同。如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

示例

```
输入:       1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

输出: true
```

解题思路：递归。

```cpp
#include "leetcode.h"
class Solution
{
public:
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        return innerCheck(p, q);
    }

    bool innerCheck(TreeNode *p, TreeNode *q)
    {
        if ((p == nullptr) ^ (q == nullptr))
            return false;
        if (p == nullptr && q == nullptr)
            return true;
        if (p->val != q->val)
            return false;
        return innerCheck(p->left, q->left) && innerCheck(p->right, q->right);
    }
};
```

## [对称二叉树](https://leetcode-cn.com/problems/symmetric-tree/)

题目[101]：给定一个二叉树，检查它是否是镜像对称的。

示例

```
input:
    1
   / \
  2   2
 / \ / \
3  4 4  3
output: true
```

解题思路：递归。

```cpp
class Solution
{
public:
    bool isSymmetric(TreeNode *root)
    {
        if (root == nullptr)
            return true;
        return innerCheck(root->left, root->right);
    }

    bool innerCheck(TreeNode *p, TreeNode *q)
    {
        if ((p == nullptr) ^ (q == nullptr))
            return false;
        if (p == nullptr)
            return true;
        if (p->val != q->val)
            return false;
        return innerCheck(p->left, q->right) && innerCheck(p->right, q->left);
    }
};
```

## [二叉树的最大深度](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)

题目[104]：给定一个二叉树，找出其最大深度。二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

示例

```
input:
    3
   / \
  9  20
    /  \
   15   7
output: 3
```

解题思路：DFS 。

```CPP
#define max(a, b) ((a) > (b) ? (a) : (b))
class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        return dfs(root);
    }

    int dfs(TreeNode *p)
    {
        if (p == nullptr)
            return 0;
        int a = dfs(p->left), b = dfs(p->right);
        return max(a, b) + 1;
    }
};
```

值得注意的是，不能 `return max(dfs(p->lect), dfs(p->right)) + 1`，因为宏展开后就会执行 4 次 DFS 。

## [二叉树的层次遍历 II](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)

题目[107]：给定一个二叉树，返回其节点值自底向上的层次遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）。

示例

```
Input:
    3
   / \
  9  20
    /  \
   15   7
Output:
[[15,7], [9,20], [3]]
```

解题思路：使用队列进行层次遍历，同时记下层数，使用 `map<int,vector>` 记录各个层次的节点。

```cpp
struct Tuple
{
    TreeNode *ptr;
    int level;
    Tuple(TreeNode *q = nullptr, int l = -1) : ptr(q), level(l) {}
};
class Solution
{
public:
    vector<vector<int>> levelOrderBottom(TreeNode *root)
    {
        if (root == nullptr)
            return vector<vector<int>>();

        map<int, vector<int>> m;
        queue<Tuple> q;
        q.push(Tuple(root, 0));
        while (!q.empty())
        {
            Tuple p = q.front();
            q.pop();
            m[p.level].push_back(p.ptr->val);
            if (p.ptr->left)
                q.push(Tuple(p.ptr->left, p.level + 1));
            if (p.ptr->right)
                q.push(Tuple(p.ptr->right, p.level + 1));
        }
        vector<vector<int>> v;
        for (auto x : m)
            v.push_back(x.second);
        return vector<vector<int>>(v.rbegin(), v.rend());
    }
};
```

## [将有序数组转换为二叉搜索树](https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/)

题目[108]：将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。本题中，一个高度平衡二叉树是指一个二叉树*每个节点* 的左右两个子树的高度差的绝对值不超过 1。

示例

```
给定有序数组: [-10,-3,0,5,9],
一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：
      0
     / \
   -3   9
   /   /
 -10  5
```

解题思路：二叉搜索树的性质是**中序遍历呈升序**，所以数组的中间元素 `nums[mid]` 必然是二叉树的根节点。所以 `[start, mid - 1]` 是左子树，`[mid + 1, end]` 是右子树，递归处理。如果数组长度为偶数，中间元素有 2 个，可任意取一个为根节点。

```cpp

class Solution
{
public:
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        TreeNode *root = nullptr;
        innerCreate(nums, 0, nums.size() - 1, root);
        return root;
    }
    void innerCreate(vector<int> &v, int start, int end, TreeNode *&p)
    {
        if (start > end)
            return;
        int mid = start + (end - start) / 2;
        p = new TreeNode(v[mid]);
        innerCreate(v, start, mid - 1, p->left);
        innerCreate(v, mid + 1, end, p->right);
    }
};
```

## [平衡二叉树](https://leetcode-cn.com/problems/balanced-binary-tree/)

题目[110]：给定一个二叉树，判断它是否是高度平衡的二叉树。

示例

```
Input: [3,9,20,null,null,15,7]
    3
   / \
  9  20
    /  \
   15   7
Output: true
```

解题思路：

+ 暴力解法

  ```cpp
  #include <cmath>
  class Solution
  {
  public:
      bool isBalanced(TreeNode *root)
      {
          return forceSolution(root);
      }
      // brute force solution
      bool forceSolution(TreeNode *p)
      {
          if (p == nullptr)
              return true;
          bool flag = abs(height(p->left) - height(p->right)) <= 1;
          return  flag && forceSolution(p->left) && forceSolution(p->right);
      }
      int height(TreeNode *p)
      {
          if (p == nullptr)
              return 0;
          return max(height(p->left), height(p->right)) + 1;
      }
  };
  ```

  请注意一点细节，`flag && forceSolution(p->left) && forceSolution(p->right)` 效率要比 ` forceSolution(p->left) && forceSolution(p->right) && flag` 高。

  显然，暴力解法对求高度存在需要「冗余」的情况，比如，我们知道 `h(left) = height(p->left)`，那么 `h(p) = h(left) + 1`，但是暴力解法仍然用 `h(p) = height(p)` 。

+ 自底向上的递归

  返回值表示以 `p` 为根的子树是否平衡，`height` 记录以 `p` 为根的子树的高度。

  ```cpp
  bool isBalanced(TreeNode *root)
  {
      int height = 0;
      return innerIsBalanced(root, height);
  }
  bool innerIsBalanced(TreeNode *p, int &height)
  {
      if (p == nullptr)
      {
          height = 0;
          return true;
      }
      int lh = 0, rh = 0;
      if (innerIsBalanced(p->left, lh) && innerIsBalanced(p->right, rh) && abs(lh - rh) <= 1)
      {
          height = max(lh, rh) + 1;
          return true;
      }
      return false;
  }
  ```

## [二叉树的最小深度](https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/)

题目[111]：给定一个二叉树，找出其最小深度。最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

示例

```
Input: 
    3
   / \
  9  20
    /  \
   15   7
Output: 2
```

解题思路：记录每个节点层数的层次遍历（实质上是 BFS）。第一个叶子节点的层数就是答案。

```cpp
class Solution
{
public:
    int minDepth(TreeNode *root)
    {
        return (root == nullptr) ? 0 : bfs(root);
    }
    int bfs(TreeNode *root)
    {
        typedef pair<TreeNode *, int> Node;
        queue<Node> q;
        q.push(Node(root, 1));
        while (!q.empty())
        {
            auto &node = q.front();
            q.pop();
            if (node.first->left == nullptr && node.first->right == nullptr)
                return node.second;
            if (node.first->left != nullptr)
                q.push(Node(node.first->left, node.second + 1));
            if (node.first->right != nullptr)
                q.push(Node(node.first->right, node.second + 1));
        }
        return -1;
    }
};
```

## [路径总和](https://leetcode-cn.com/problems/path-sum/)

题目[112]：给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。

示例

```
Input: sum = 22
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
Output: true, because sum(5->4->11->2) = 22
```

解题思路：回溯法。`current` 记录当前的**遍历路径**的和。

```cpp
class Solution
{
public:
    bool hasPathSum(TreeNode *root, int sum)
    {
        bool result = false;
        innerSum(root, sum, 0, result);
        return result;
    }
    void innerSum(TreeNode *p, int target, int current, bool &result)
    {
        if (p == nullptr)
            return;
        current += p->val;
        if (current == target && p->left == nullptr && p->right == nullptr)
        {
            result = true;
            return;
        }
        innerSum(p->left, target, current, result);
        if (!result)
            innerSum(p->right, target, current, result);
    }
};
```

## [翻转二叉树](https://leetcode-cn.com/problems/invert-binary-tree/)

题目[226]：翻转一棵二叉树。

示例

```
Input:
     4
   /   \
  2     7
 / \   / \
1   3 6   9
Output:
     4
   /   \
  7     2
 / \   / \
9   6 3   1
```

解题思路：对每个节点执行 `swap(p->left, p->right)` 。`TreeNode* &p` 表示的是指针的引用。

```cpp
class Solution
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        if (root != nullptr)
            innerInvert(root->left, root->right);
        return root;
    }
    void innerInvert(TreeNode *&l, TreeNode *&r)
    {
        auto p = l;
        l = r;
        r = p;
        if (l != nullptr)
            innerInvert(l->left, l->right);
        if (r != nullptr)
            innerInvert(r->left, r->right);
    }
};
```



## [二叉搜索树的最近公共祖先](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)

题目[235]：给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

示例

```
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6 
解释: 节点 2 和节点 8 的最近公共祖先是 6。
```

解题思路：利用二叉搜索树的性质，左子树 < 根 < 右子树。那么：

+ `p.val < root.val && q.val < root.val`：在左子树搜索。
+ `p.val > root.val && q.val < root.val`：在右子树搜索。
+ 其他情况：`root` 就是公共祖先。

递归解法

```cpp
TreeNode *lca(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (p->val < root->val && q->val < root->val)
        return lca(root->left, p, q);
    else if (p->val > root->val && q->val > root->val)
        return lca(root->right, p, q);
    else
        return root;
}
```

非递归解法

```cpp
TreeNode *lca2(TreeNode *root, TreeNode *p, TreeNode *q)
{
    auto node = root;
    while (node != nullptr)
    {
        if (p->val < node->val && q->val < node->val)
            node = node->left;
        else if (p->val > node->val && q->val > node->val)
            node = node->right;
        else
            break;
    }
    return node;
}
```

## [二叉树的所有路径](https://leetcode-cn.com/problems/binary-tree-paths/)

题目[257]：给定一个二叉树，返回所有从根节点到叶子节点的路径。

示例

```
输入:
   1
 /   \
2     3
 \
  5
输出: ["1->2->5", "1->3"]
解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3
```

解题思路：显而易见的回溯法（实际上也是二叉树的遍历），如果找到叶子节点，说明是一个完整的路径。

```cpp
#include "leetcode.h"
class Solution
{
public:
    vector<string> result;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        if (root != nullptr)
            preorder(root, "");
        return result;
    }

    void preorder(TreeNode *p, string s)
    {
        bool l = (p->left != nullptr);
        bool r = (p->right != nullptr);
        if (l || r)
            s += to_string(p->val) + "->";
        else if (!l && !r)
        {
            s += to_string(p->val);
            result.push_back(s);
            return;
        }
        if (l)
            preorder(p->left, s);
        if (r)
            preorder(p->right, s);
    }
};
```



## [左叶子之和](https://leetcode-cn.com/problems/sum-of-left-leaves/)

题目[404]：计算给定二叉树的所有左叶子之和。

示例

```
    3
   / \
  9  20
    /  \
   15   7
在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24
```

解题思路：遍历过程使用一个 `flag` 来表示本次节点是否为左子树。如果既是左子树，又是叶子节点，就是要累加的节点。

```cpp
#include "leetcode.h"
class Solution
{
public:
    int sum = 0;
    int sumOfLeftLeaves(TreeNode *root)
    {
        if (root != nullptr)
            preorder(root, false);
        return sum;
    }

    void preorder(TreeNode *root, bool isLeft)
    {
        bool l = (root->left != nullptr);
        bool r = (root->right != nullptr);
        if (isLeft && !l && !r)
            sum += root->val;
        if (l)
            preorder(root->left, true);
        if (r)
            preorder(root->right, false);
    }
};
```

## ⭐ [路径总和 III](https://leetcode-cn.com/problems/path-sum-iii/)

题目[437]：给定一个二叉树，它的每个结点都存放着一个整数值。找出路径和等于给定数值的路径总数。路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。

示例

```
root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1
返回 3。和等于 8 的路径有:
1.  5 -> 3
2.  5 -> 2 -> 1
3.  -3 -> 11
```

解题思路：将二叉树的每一个完整路径看作是一个数组 `nums`（假设第一个元素是 `nums[1]`），那么本题就是要找到 `sum(i, j) = sum` 的下标 i 和 j 。

为此，使用一个数组 `v` ，`v[0] = 0`，`v[i]` 表示 `sum(nums[1] ... nums[i])` ，即 `nums` 前 i 个元素的和。那么 `sum(nums[i] ... nums[j]) = v[j] - v[i - 1]` 。

使用先序遍历每一个从根到叶子的路径。

```cpp
class Solution
{
public:
    int result = 0;
    int pathSum(TreeNode *root, int sum)
    {
        if (root == nullptr)
            return 0;
        int d = depth(root);
        vector<int> v(d + 1);
        preorder(1, v, root, sum);
        return result;
    }

    int depth(TreeNode *p)
    {
        if (p == nullptr)
            return 0;
        return max(depth(p->left), depth(p->right)) + 1;
    }

    void preorder(int idx, vector<int> &v, TreeNode *p, const int sum)
    {
        if (p == nullptr)
            return;
        v[idx] = v[idx - 1] + p->val;
        for (int i = 0; i < idx; i++)
        {
            if (v[idx] - v[i] == sum)
                result++;
        }
        preorder(idx + 1, v, p->left, sum);
        preorder(idx + 1, v, p->right, sum);
    }
};
```



## ⭐[二叉搜索树中的众数](https://leetcode-cn.com/problems/find-mode-in-binary-search-tree/)

题目[501]：给定一个有相同值的二叉搜索树（BST），找出 BST 中的所有众数（出现频率最高的元素）。

示例

```
Input:
   1
    \
     2
    /
   2
Output: [2]
```

解题思路：利用BST的性质，中序遍历为升序序列。`current` 记录当前数字 `number` 出现的次数，`last` 记录上一次找到的「候选众数」出现的次数。

```cpp
class Solution
{
public:
    vector<int> v;
    int current = 0;
    int last = 0;
    int number = 0x80000000;
    vector<int> findMode(TreeNode *root)
    {
        if (root != nullptr)
            inorder(root);
        return v;
    }
    void inorder(TreeNode *p)
    {
        if (p == nullptr)
            return;
        inorder(p->left);
        if (last == 0)
            last = 1;
        if (p->val != number)
            current = 0;
        number = p->val;
        current++;
        if (current == last)
            v.push_back(number);
        if (current > last)
        {
            last = current;
            v.clear(), v.push_back(number);
        }
        inorder(p->right);
    }
};
```

## [二叉搜索树的最小绝对差](https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst/)

题目[530]：给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两节点的差的绝对值的最小值。

示例

```
输入：
   1
    \
     3
    /
   2
输出：1
解释：最小绝对差为 1，其中 2 和 1 的差的绝对值为 1（或者 2 和 3）。
```

解题思路：BST中序遍历呈升序。

```cpp
#include "leetcode.h"
class Solution
{
public:
    int result = 0x7ffffff;
    int pre = 0x7fffffff;
    int getMinimumDifference(TreeNode *root)
    {
        inorder(root);
        return result;
    }
    void inorder(TreeNode *p)
    {
        if (p == nullptr)
            return;
        inorder(p->left);
        result = min(result, abs(p->val - pre));
        pre = p->val;
        inorder(p->right);
    }
};
```

## [把二叉搜索树转换为累加树](https://leetcode-cn.com/problems/convert-bst-to-greater-tree/)

题目[538]：给定一个二叉搜索树（Binary Search Tree），把它转换成为累加树（Greater Tree)，使得每个节点的值是原来的节点值加上所有大于它的节点值之和。

示例

```
输入: 原始二叉搜索树:
              5
            /   \
           2     13
输出: 转换为累加树:
             18
            /   \
          20     13
```

解题思路：逆中序遍历 BST 。

```cpp
class Solution
{
public:
    int sum = 0;
    TreeNode *convertBST(TreeNode *root)
    {
        postorder(root);
        return root;
    }

    void postorder(TreeNode *p)
    {
        if (p == nullptr)
            return;
        postorder(p->right);
        sum += p->val;
        p->val = sum;
        postorder(p->left);
    }
};
```

## ⭐[二叉树的直径](https://leetcode-cn.com/problems/diameter-of-binary-tree/)

题目[534]：给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。

示例

```
Input:
          1
         / \
        2   3
       / \     
      4   5    
Output: 3
```

解题思路：所谓直径，就是二叉树中任意路径上的节点数减一。

对于二叉树中的每个节点 `node`，以 `node` 为根的子树，其直径为 `depth(node.left) + depth(node.right)` 。

+ 自顶向下的递归

  ```cpp
  int result = 0;
  int diameterOfBinaryTree(TreeNode *root)
  {
      preorder(root);
      return result;
  }
  
  int depth(TreeNode *p)
  {
      return p == nullptr ? 0 : max(depth(p->left), depth(p->right)) + 1;
  }
  
  void preorder(TreeNode *p)
  {
      if (p == nullptr)
          return;
      result = max(result, depth(p->left) + depth(p->right));
      preorder(p->left);
      preorder(p->right);
  }
  ```

+ 自底向上的递归

  显然，对每个节点都调用一次 `depth` 函数，有很多冗余的遍历。求出每个节点的高度，实际上只需要一次自底向上的遍历。因为 `depth(p) = max(depth(p.left), depth(p.right)) + 1` 。因此可使用后序遍历。

  ```cpp
  int result = 0;
  int diameterOfBinaryTree(TreeNode *root)
  {
      int height = 0;
      bottom2top(root, height);
      return result;
  }
  void bottom2top(TreeNode *p, int &height)
  {
      if (p == nullptr)
      {
          height = 0;
          return;
      }
      int l = height, r = height;
      bottom2top(p->left, l);
      bottom2top(p->right, r);
      height = max(l, r) + 1;
      result = max(result, l + r);
  }
  ```

## [二叉树的坡度](https://leetcode-cn.com/problems/binary-tree-tilt/)

题目[563]：给定一个二叉树，计算整个树的坡度。一个树的节点的坡度定义即为，该节点左子树的结点之和和右子树结点之和的差的绝对值。空结点的的坡度是0。整个树的坡度就是其所有节点的坡度之和。

示例

```
输入: 
         1
       /   \
      2     3
输出: 1
解释: 
结点的坡度 2 : 0
结点的坡度 3 : 0
结点的坡度 1 : |2-3| = 1
树的坡度 : 0 + 0 + 1 = 1
```

解题思路：实际上要解决的问题是**怎么求出每个子树的和**。显然还是采取自底向上的后序遍历。

```cpp
class Solution
{
public:
    int tilt = 0;
    int findTilt(TreeNode *root)
    {
        int sum = 0;
        postorder(root, sum);
        return tilt;
    }

    void postorder(TreeNode *p, int &sum)
    {
        if (p == nullptr)
        {
            return;
        }
        int l = sum, r = sum;
        postorder(p->left, l);
        postorder(p->right, r);
        sum += p->val + l + r;
        tilt += abs(l - r);
    }
};
```



## [另一个树的子树](https://leetcode-cn.com/problems/subtree-of-another-tree/)

题目[572]：给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看做它自身的一棵子树。

解题思路：暴力解法。先实现 `isSame(s, t)` 判断 `s` 和 `t` 是否完全相等，再遍历 `s` 的每一个节点 `p` ，判断 `isSame(p, t)` 。

```cpp
class Solution
{
public:
    bool isSubtree(TreeNode *s, TreeNode *t)
    {
        if (s == nullptr)
            return t == nullptr;
        queue<TreeNode *> q;
        q.push(s);
        while (!q.empty())
        {
            auto p = q.front();
            q.pop();
            if (isSame(p, t))
                return true;
            if (p->left != nullptr)
                q.push(p->left);
            if (p->right != nullptr)
                q.push(p->right);
        }
        return false;
    }

    bool isSame(TreeNode *s, TreeNode *t)
    {
        if ((s == nullptr) ^ (t == nullptr))
            return false;
        if (s == nullptr && t == nullptr)
            return true;
        return (s->val == t->val) && isSame(s->left, t->left) && isSame(s->right, t->right);
    }
};
```

