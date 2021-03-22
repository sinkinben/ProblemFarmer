#include "leetcode.h"
class Solution
{
public:
    int tilt = 0;
    int findTilt(TreeNode *root)
    {
        int sum = 0;
        postorder(root, sum);
        return tilt;
    }

    void postorder(TreeNode *p, int &sum)
    {
        if (p == nullptr)
        {
            return;
        }
        int l = sum, r = sum;
        postorder(p->left, l);
        postorder(p->right, r);
        sum += p->val + l + r;
        tilt += abs(l - r);
    }
};