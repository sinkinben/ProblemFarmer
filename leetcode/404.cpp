#include "leetcode.h"
class Solution
{
public:
    int sum = 0;
    int sumOfLeftLeaves(TreeNode *root)
    {
        if (root != nullptr)
            preorder(root, false);
        return sum;
    }

    void preorder(TreeNode *root, bool isLeft)
    {
        bool l = (root->left != nullptr);
        bool r = (root->right != nullptr);
        if (isLeft && !l && !r)
            sum += root->val;
        if (l)
            preorder(root->left, true);
        if (r)
            preorder(root->right, false);
    }
};