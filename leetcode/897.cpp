#include <stack>
#include "leetcode.h"
class Solution
{
public:
    TreeNode *increasingBST(TreeNode *root)
    {
        return inorder(root);
    }

    TreeNode *inorder(TreeNode *oldRoot)
    {
        TreeNode *newRoot = new TreeNode(-1);
        auto t = newRoot;
        auto p = oldRoot;
        stack<TreeNode *> s;
        while (p != nullptr || !s.empty())
        {
            if (p != nullptr)
                s.push(p), p = p->left;
            else
            {
                p = s.top(), s.pop();
                t->right = new TreeNode(p->val);
                t = t->right;
                p = p->right;
            }
        }
        return newRoot->right;
    }
};
