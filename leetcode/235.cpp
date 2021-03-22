#include "leetcode.h"
class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        return lca2(root, p, q);
    }

    TreeNode *lca(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (p->val < root->val && q->val < root->val)
            return lca(root->left, p, q);
        else if (p->val > root->val && q->val > root->val)
            return lca(root->right, p, q);
        else
            return root;
    }

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
};
