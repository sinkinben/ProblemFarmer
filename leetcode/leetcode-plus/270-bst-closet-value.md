## Closest Binary Search Tree Value

Leetcode: [270. Closest Binary Search Tree Value](https://leetcode-cn.com/problems/closest-binary-search-tree-value/)

Given the `root` of a binary search tree and a target value, return the value in the BST that is closest to the `target`.

<img src="https://assets.leetcode.com/uploads/2021/03/12/closest1-1-tree.jpg"/>

```
Input: root = [4,2,5,1,3], target = 3.714286
Output: 4
```

<br/>

**Solution**

```cpp
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int res = -1;
        auto ptr = root;
        while (ptr) {
            res = select(res, ptr->val, target);
            if (target < ptr->val)
                ptr = ptr->left;
            else if (target > ptr->val)
                ptr = ptr->right;
            else if (target == ptr->val)
                return ptr->val;
        }
        return res;
    }
    
    int select(int oldval, int newval, double target) {
        if (oldval == -1) return newval;
        return abs(target - oldval) < abs(target - newval) ? oldval : newval;
    }
};
```

