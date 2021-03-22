#include "leetcode.h"
class Solution
{
public:
    int result = 0x7ffffff;
    int pre = 0x7fffffff;
    int getMinimumDifference(TreeNode *root)
    {
        inorder(root);
        return result;
    }

    void inorder(TreeNode *p)
    {
        if (p == nullptr)
            return;
        inorder(p->left);
        result = min(result, abs(p->val - pre));
        pre = p->val;
        inorder(p->right);
    }
};