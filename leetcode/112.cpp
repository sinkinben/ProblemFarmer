#include "leetcode.h"
class Solution
{
public:
    bool hasPathSum(TreeNode *root, int sum)
    {
        bool result = false;
        innerSum(root, sum, 0, result);
        return result;
    }
    void innerSum(TreeNode *p, int target, int current, bool &result)
    {
        if (p == nullptr)
            return;
        current += p->val;
        if (current == target && p->left == nullptr && p->right == nullptr)
        {
            result = true;
            return;
        }
        innerSum(p->left, target, current, result);
        if (!result)
            innerSum(p->right, target, current, result);
    }
};