#include "leetcode.h"
class Solution
{
public:
    int sum = 0;
    TreeNode *convertBST(TreeNode *root)
    {
        postorder(root);
        return root;
    }

    void postorder(TreeNode *p)
    {
        if (p == nullptr)
            return;
        postorder(p->right);
        sum += p->val;
        p->val = sum;
        postorder(p->left);
    }
};