#include "leetcode.h"
class Solution
{
public:
    TreeNode *trimBST(TreeNode *root, int L, int R)
    {
        // return innerTrim(root, L, R);
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
};
