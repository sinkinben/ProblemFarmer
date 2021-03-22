#include "leetcode.h"
class Solution
{
public:
    vector<int> v;
    int current = 0;
    int last = 0;
    int number = 0x80000000;
    vector<int> findMode(TreeNode *root)
    {
        if (root != nullptr)
            inorder(root);
        return v;
    }

    void inorder(TreeNode *p)
    {
        if (p == nullptr)
            return;
        inorder(p->left);
        if (last == 0)
            last = 1;
        if (p->val != number)
            current = 0;
        number = p->val;
        current++;
        if (current == last)
            v.push_back(number);
        if (current > last)
        {
            last = current;
            v.clear(), v.push_back(number);
        }
        inorder(p->right);
    }
};
