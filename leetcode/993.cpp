#include <queue>
#include "leetcode.h"
class Solution
{
public:
    bool isCousins(TreeNode *root, int x, int y)
    {
        if (root == nullptr)
            return false;
        queue<TreeNode *> q;
        TreeNode *xparent = nullptr, *yparent = nullptr;
        auto p = root;
        q.emplace(p);
        while (!q.empty())
        {
            queue<TreeNode *> nextlevel;
            while (!q.empty())
            {
                p = q.front(), q.pop();
                if (p->left)
                {
                    nextlevel.emplace(p->left);
                    if (x == p->left->val)
                        xparent = p;
                    if (y == p->left->val)
                        yparent = p;
                }
                if (p->right)
                {
                    nextlevel.emplace(p->right);
                    if (x == p->right->val)
                        xparent = p;
                    if (y == p->right->val)
                        yparent = p;
                }
            }
            q = nextlevel;
            // not found yet
            if (xparent == nullptr && yparent == nullptr)
                continue;
            // not same level
            if ((xparent == nullptr) ^ (yparent == nullptr))
                return false;
            // found at same level
            return xparent != yparent;
        }
        // can not be here
        return false;
    }
};