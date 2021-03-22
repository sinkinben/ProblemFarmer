/**
 * Time: beat 53.84%
 * Memory: beat 5.09%
 * Both two methods.
 **/
#include "leetcode.h"
#include <queue>
class Solution
{
public:
    vector<int> vals;
    bool findTarget(TreeNode *root, int k)
    {
        inorder(root);
        int l = 0, r = (int)vals.size() - 1;
        while (l < r)
        {
            int sum = vals[l] + vals[r];
            if (sum == k)
                return k;
            if (sum < k)
                l++;
            else
                r--;
        }
        return false;
    }
    void inorder(TreeNode *p)
    {
        if (p == nullptr)
            return;
        inorder(p->left);
        vals.push_back(p->val);
        inorder(p->right);
    }
    bool search(TreeNode *p, int val, TreeNode *exceptNode)
    {
        if (p == nullptr)
            return false;
        if (p->val == val && p != exceptNode)
            return true;
        if (val < p->val)
            return search(p->left, val, exceptNode);
        return search(p->right, val, exceptNode);
    }

    bool levelorder(TreeNode *root, int k)
    {
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            auto p = q.front();
            q.pop();
            int val = k - p->val;
            if (search(root, val, p))
                return true;
            if (p->left != nullptr)
                q.push(p->left);
            if (p->right != nullptr)
                q.push(p->right);
        }
        return false;
    }
};
