#include "leetcode.h"
class Solution
{
public:
    int countNodes(TreeNode *root)
    {
        // return levelorder(root);
        return binsearch(root);
    }

    bool check(int idx, int d, TreeNode *p)
    {
        int l = 0, r = (1 << d) - 1;
        for (int i = 0; i < d; i++)
        {
            int m = l + (r - l) / 2;
            if (idx <= m)
                r = m - 1, p = p->left;
            else
                l = m + 1, p = p->right;
        }
        return p != nullptr;
    }

    int binsearch(TreeNode *root)
    {
        auto p = root;
        int depth = 0;
        while (p != nullptr)
            p = p->left, depth++;

        if (depth == 0 || depth == 1)
            return depth;

        // bottom level has 2^(depth-1) at most => [0, 2^(depth-1) - 1]
        int l = 0, r = 1 << (depth - 1), m;
        while (l <= r)
        {
            m = l + (r - l) / 2;
            if (check(m, depth - 1, root))
                l = m + 1;
            else
                r = m - 1;
        }

        return (1 << (depth - 1)) - 1 + m;
    }

    int levelorder(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        queue<TreeNode *> q;
        q.push(root);
        int ans = 0;
        while (!q.empty())
        {
            auto p = q.front();
            q.pop();
            ans++;
            if (p->left)
                q.push(p->left);
            if (p->right)
                q.push(p->right);
        }
        return ans;
    }
};
