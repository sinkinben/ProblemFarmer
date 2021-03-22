#include "leetcode.h"
#include <cmath>
class Solution
{
public:
    bool isBalanced(TreeNode *root)
    {
        int height = 0;
        return innerIsBalanced(root, height);
        // return forceSolution(root);
    }
    // brute force solution
    bool forceSolution(TreeNode *p)
    {
        if (p == nullptr)
            return true;
        bool flag = abs(height(p->left) - height(p->right)) <= 1;
        return flag && forceSolution(p->left) && forceSolution(p->right);
    }
    int height(TreeNode *p)
    {
        if (p == nullptr)
            return 0;
        return max(height(p->left), height(p->right)) + 1;
    }
    // traversal from the bottom to tht top
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
};
