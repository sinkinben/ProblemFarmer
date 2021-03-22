#include "leetcode.h"
#include <stack>
class Solution
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        return inorderNonRec(root);
        vector<int> v;
        innerTraversal(root, v);
        return v;
    }

    void innerTraversal(TreeNode *p, vector<int> &v)
    {
        if (p == nullptr)
            return;
        innerTraversal(p->left, v);
        v.push_back(p->val);
        innerTraversal(p->right, v);
    }

    vector<int> inorderNonRec(TreeNode *root)
    {
        vector<int> v;
        if (root != nullptr)
        {
            stack<TreeNode *> s;
            auto p = root;
            while (!s.empty() || p != nullptr)
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
        }
        return v;
    }
};