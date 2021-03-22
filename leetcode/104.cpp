#include "leetcode.h"
#define max(a, b) ((a) > (b) ? (a) : (b))
class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        return dfs(root);
    }

    int dfs(TreeNode *p)
    {
        if (p == nullptr)
            return 0;
        int a = dfs(p->left), b = dfs(p->right);
        return max(a, b) + 1;
    }
};