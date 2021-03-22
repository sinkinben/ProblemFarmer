#include "leetcode.h"
#include <queue>
class Solution
{
public:
    bool isSubtree(TreeNode *s, TreeNode *t)
    {
        if (s == nullptr)
            return t == nullptr;
        queue<TreeNode *> q;
        q.push(s);
        while (!q.empty())
        {
            auto p = q.front();
            q.pop();
            if (isSame(p, t))
                return true;
            if (p->left != nullptr)
                q.push(p->left);
            if (p->right != nullptr)
                q.push(p->right);
        }
        return false;
    }

    bool isSame(TreeNode *s, TreeNode *t)
    {
        if ((s == nullptr) ^ (t == nullptr))
            return false;
        if (s == nullptr && t == nullptr)
            return true;
        return (s->val == t->val) && isSame(s->left, t->left) && isSame(s->right, t->right);
    }
};