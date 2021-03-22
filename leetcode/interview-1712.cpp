#include "leetcode.h"
class Solution
{
public:
    TreeNode *convertBiNode(TreeNode *root)
    {
        TreeNode *newRoot = new TreeNode(-1);
        auto t = newRoot;
        auto p = root;
        stack<TreeNode *> s;
        while (!s.empty() || p != nullptr)
        {
            if (p)
            {
                s.emplace(p);
                p = p->left;
            }
            else
            {
                p = s.top(), s.pop();
                t->right = p, t = t->right;
                p = p->right;
            }
        }
        t = newRoot;
        while (t)
            t->left = nullptr, t = t->right;
        return newRoot->right;
    }
};
