#include "leetcode.h"
class Solution
{
public:
    int result = 0;
    int diameterOfBinaryTree(TreeNode *root)
    {
        // preorder(root);
        int height = 0;
        bottom2top(root, height);
        return result;
    }

    int depth(TreeNode *p)
    {
        return p == nullptr ? 0 : max(depth(p->left), depth(p->right)) + 1;
    }

    void preorder(TreeNode *p)
    {
        if (p == nullptr)
            return;
        result = max(result, depth(p->left) + depth(p->right));
        preorder(p->left);
        preorder(p->right);
    }

    void bottom2top(TreeNode *p, int &height)
    {
        if (p == nullptr)
        {
            height = 0;
            return;
        }
        int l = height, r = height;
        bottom2top(p->left, l);
        bottom2top(p->right, r);
        height = max(l, r) + 1;
        result = max(result, l + r);
    }
};
