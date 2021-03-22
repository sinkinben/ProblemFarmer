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