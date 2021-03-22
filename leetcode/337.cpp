#include "leetcode.h"
class Solution
{
public:
    int rob(TreeNode *root)
    {
        auto v = helper(root);
        return max(v[0], v[1]);
    }

    vector<int> helper(TreeNode *p)
    {
        if (p == nullptr)
            return {0, 0};

        auto dpl = helper(p->left);
        auto dpr = helper(p->right);

        vector<int> dpnode(2, 0);
        dpnode[0] = max(dpl[0], dpl[1]) + max(dpr[0], dpr[1]);
        dpnode[1] = p->val + dpl[0] + dpr[0];
        return dpnode;
    }
};