#include "../leetcode/leetcode.h"
#include <algorithm>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int ridx = 0;
        return innerBuild(preorder, inorder, ridx, 0, inorder.size() - 1);
    }

    inline int vfind(vector<int> &v, int val)
    {
        return find(v.begin(), v.end(), val) - v.begin();
    }

    TreeNode *innerBuild(vector<int> &preorder, vector<int> &inorder, int &ridx, int l, int r)
    {
        if (ridx >= (int)preorder.size() || l > r)
            return nullptr;
        if (l == r)
            return new TreeNode(preorder[ridx++]);
        int pos = vfind(inorder, preorder[ridx]);
        auto p = new TreeNode(preorder[ridx++]);
        p->left = innerBuild(preorder, inorder, ridx, l, pos - 1);
        p->right = innerBuild(preorder, inorder, ridx, pos + 1, r);
        return p;
    }
};