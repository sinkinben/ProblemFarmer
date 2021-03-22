#include "leetcode.h"
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