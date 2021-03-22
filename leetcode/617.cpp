#include "leetcode.h"
#include <stack>
class Solution
{
public:
    TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
    {
        // return innerMerge(t1, t2);
        return preorderMerge(t1, t2);
    }

    TreeNode *innerMerge(TreeNode *t1, TreeNode *t2)
    {
        if (t1 == nullptr)
            return t2;
        if (t2 == nullptr)
            return t1;
        t1->val += t2->val;
        t1->left = innerMerge(t1->left, t2->left);
        t1->right = innerMerge(t1->right, t2->right);
        return t1;
    }

    TreeNode *preorderMerge(TreeNode *t1, TreeNode *t2)
    {
        typedef pair<TreeNode *, TreeNode *> node;
        if (t1 == nullptr)
            return t2;
        stack<node> s;
        s.push(node(t1, t2));
        while (!s.empty())
        {
            node n = s.top();
            s.pop();
            if (n.second == nullptr)
                continue;
            n.first->val += n.second->val;
            if (n.first->left == nullptr)
                n.first->left = n.second->left;
            else
                s.push(node(n.first->left, n.second->left));
            if (n.first->right == nullptr)
                n.first->right = n.second->right;
            else
                s.push(node(n.first->right, n.second->right));
        }
        return t1;
    }
};
