#include "leetcode.h"
class Solution
{
public:
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        TreeNode *root = nullptr;
        innerCreate(nums, 0, nums.size() - 1, root);
        return root;
    }

    void innerCreate(vector<int> &v, int start, int end, TreeNode *&p)
    {
        if (start > end)
            return;
        int mid = start + (end - start) / 2;
        p = new TreeNode(v[mid]);
        innerCreate(v, start, mid - 1, p->left);
        innerCreate(v, mid + 1, end, p->right);
    }
};