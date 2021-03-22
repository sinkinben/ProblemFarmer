#include "leetcode.h"
class Solution
{
public:
    vector<string> result;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        if (root != nullptr)
            preorder(root, "");
        return result;
    }

    void preorder(TreeNode *p, string s)
    {
        bool l = (p->left != nullptr);
        bool r = (p->right != nullptr);
        if (l || r)
            s += to_string(p->val) + "->";
        else if (!l && !r)
        {
            s += to_string(p->val);
            result.push_back(s);
            return;
        }
        if (l)
            preorder(p->left, s);
        if (r)
            preorder(p->right, s);
    }
};