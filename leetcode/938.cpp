#include <stack>
#include "leetcode.h"
class Solution
{
public:
    int sum = 0;
    int rangeSumBST(TreeNode *root, int L, int R)
    {
        // return inorder(root, L, R);

        // helper(root, L, R);
        // return sum;

        return search(root, L, R);
    }

    int search(TreeNode *root, int l, int r)
    {
        int result = 0;
        auto p = root;
        stack<TreeNode *> s;
        s.push(p);
        while (!s.empty())
        {
            p = s.top(), s.pop();
            if (p == nullptr)
                continue;
            if (l <= p->val && p->val <= r)
            {
                result += p->val;
                s.push(p->right);
                s.push(p->left);
            }
            else if (p->val < l)
                s.push(p->right);
            else if (p->val > r)
                s.push(p->left);
        }
        return result;
    }

    void helper(TreeNode *root, int l, int r)
    {
        if (root == nullptr)
            return;
        if (root->val < l)
            helper(root->right, l, r);
        else if (root->val > r)
            helper(root->left, l, r);
        else
        {
            sum += root->val;
            helper(root->left, l, r);
            helper(root->right, l, r);
        }
    }

    int inorder(TreeNode *root, int l, int r)
    {
        int sum = 0;
        auto p = root;
        stack<TreeNode *> s;
        while (p != nullptr || !s.empty())
        {
            if (p)
                s.push(p), p = p->left;
            else
            {
                p = s.top(), s.pop();
                if (l <= p->val && p->val <= r)
                    sum += p->val;
                else if (p->val > r)
                    break;
                p = p->right;
            }
        }
        return sum;
    }
};