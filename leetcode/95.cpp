#include "leetcode.h"
class Solution
{
public:
    vector<TreeNode *> generateTrees(int n)
    {
        if (n == 0)
            return {};
        return innerGenerate(1, n);
    }

    vector<TreeNode *> innerGenerate(int start, int end)
    {
        if (start > end)
            return {nullptr};
        vector<TreeNode *> result;
        for (int i = start; i <= end; i++)
        {
            auto ltrees = innerGenerate(start, i - 1);
            auto rtrees = innerGenerate(i + 1, end);
            for (const auto &l : ltrees)
            {
                for (const auto &r : rtrees)
                {
                    TreeNode *root = new TreeNode(i);
                    root->left = l, root->right = r;
                    result.push_back(root);
                }
            }
        }
        return result;
    }
};