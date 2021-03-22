#include "leetcode.h"
#include <stack>
class Solution
{
public:
    int sum = 0;
    int sumRootToLeaf(TreeNode *root)
    {
        preorder(0, root);
        return sum;
    }

    void preorder(int val, TreeNode *p)
    {
        if (p == nullptr)
            return;
        val = (val << 1) | p->val;
        if (p->left == nullptr && p->right == nullptr)
            sum += val;
        preorder(val, p->left);
        preorder(val, p->right);
    }
};

int main()
{
    TreeNode *r = new TreeNode(1);
    r->left = new TreeNode(0);
    Solution sol;
    cout << sol.sumRootToLeaf(r) << endl;
}