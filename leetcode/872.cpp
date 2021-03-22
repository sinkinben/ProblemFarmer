#include "leetcode.h"
#include <stack>
class Solution
{
public:
    bool leafSimilar(TreeNode *root1, TreeNode *root2)
    {
        return inorder(root1) == inorder(root2);
    }

    vector<int> inorder(TreeNode *root)
    {
        vector<int> v;
        auto p = root;
        stack<TreeNode *> s;
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
                if (p->left == nullptr && p->right == nullptr)
                    v.push_back(p->val);
                p = p->right;
            }
        }
        return v;
    }
};