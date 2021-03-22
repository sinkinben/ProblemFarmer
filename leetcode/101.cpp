#include "leetcode.h"
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