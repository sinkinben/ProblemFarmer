#include "leetcode.h"
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
