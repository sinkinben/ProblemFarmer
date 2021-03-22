#include "leetcode.h"
#include <algorithm>
class Solution
{
public:
    int result = 0;
    int pathSum(TreeNode *root, int sum)
    {
        if (root == nullptr)
            return 0;
        int d = depth(root);
        vector<int> v(d + 1);
        preorder(1, v, root, sum);
        return result;
    }

    int depth(TreeNode *p)
    {
        if (p == nullptr)
            return 0;
        return max(depth(p->left), depth(p->right)) + 1;
    }

    void preorder(int idx, vector<int> &v, TreeNode *p, const int sum)
    {
        if (p == nullptr)
            return;
        v[idx] = v[idx - 1] + p->val;
        for (int i = 0; i < idx; i++)
        {
            if (v[idx] - v[i] == sum)
                result++;
        }
        preorder(idx + 1, v, p->left, sum);
        preorder(idx + 1, v, p->right, sum);
    }
};