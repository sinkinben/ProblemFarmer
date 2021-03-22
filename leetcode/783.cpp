#include "leetcode.h"
#include <stack>
class Solution
{
public:
    int minDiffInBST(TreeNode *root)
    {
        return inorder2(root);
    }

    int inorder2(TreeNode *root)
    {
        bool first = true;
        int diff = 0x7ffffff;
        int pre = -1;
        auto p = root;
        stack<TreeNode *> s;
        while (p != nullptr || !s.empty())
        {
            if (p != nullptr)
            {
                s.push(p);
                p = p->left;
            }
            else
            {
                p = s.top(), s.pop();
                if (first)
                    pre = p->val, first = false;
                else
                    diff = min(diff, abs(p->val - pre)), pre = p->val;
                p = p->right;
            }
        }
        return diff;
    }

    int inorder(TreeNode *root)
    {
        vector<int> v;
        auto p = root;
        stack<TreeNode *> s;
        while (p != nullptr || !s.empty())
        {
            if (p != nullptr)
            {
                s.push(p);
                p = p->left;
            }
            else
            {
                p = s.top(), s.pop();
                v.push_back(p->val);
                p = p->right;
            }
        }
        int diff = abs(v[1] - v[0]);
        for (int i = 2; i < (int)v.size(); i++)
            diff = min(diff, abs(v[i] - v[i - 1]));
        return diff;
    }
};