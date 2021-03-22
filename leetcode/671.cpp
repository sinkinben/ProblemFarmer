#include "leetcode.h"
#include <queue>
#include <set>
class Solution
{
public:
    int findSecondMinimumValue(TreeNode *root)
    {
        if (root == nullptr || root->left == nullptr)
            return -1;
        int minval = root->val;
        int result = -1;
        queue<TreeNode *> q;
        auto p = root;
        q.push(p);
        while (!q.empty())
        {
            p = q.front();
            q.pop();
            if (p->val > minval)
                result = result == -1 ? p->val : min(result, p->val);
            if (p->left)
                q.push(p->left);
            if (p->right)
                q.push(p->right);
        }
        return result;
    }
};