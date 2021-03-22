#include "leetcode.h"
class Solution
{
public:
    string tree2str(TreeNode *t)
    {
        // string s = "";
        // preorder(t, s);
        // return s;
        return preorder2(t);
    }

    void preorder(TreeNode *p, string &s)
    {
        if (p == nullptr)
            return;
        string sval = to_string(p->val);
        string l, r;
        preorder(p->left, l);
        preorder(p->right, r);
        s += sval;
        bool lflag = (l != "");
        bool rflag = (r != "");
        if (lflag && rflag)
            s += "(" + l + ")(" + r + ")";
        if (!lflag && rflag)
            s += "()(" + r + ")";
        if (lflag && !rflag)
            s += "(" + l + ")";
    }

    string preorder2(TreeNode *p)
    {
        if (p == nullptr)
            return "";
        bool l = (p->left != nullptr);
        bool r = (p->right != nullptr);
        string sval = to_string(p->val);
        if (l && r)
            return sval + "(" + preorder2(p->left) + ")(" + preorder2(p->right) + ")";
        if (!l && r)
            return sval + "()(" + preorder2(p->right) + ")";
        if (l && !r)
            return sval + "(" + preorder2(p->left) + ")";
        return sval;
    }
};
