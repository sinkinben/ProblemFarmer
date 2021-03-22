#include "leetcode.h"
#include <iostream>
#include <map>
#include <cmath>
struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution
{
    map<TreeNode *, int> m;
    map<int, int> times;

public:
    vector<int> findFrequentTreeSum(TreeNode *root)
    {
        traversal(root);
        vector<int> v;
        int val = -1;
        for (auto p = times.begin(); p != times.end(); p++)
        {
            val = max(val, p->second);
        }
        for (auto p = times.begin(); p != times.end(); p++)
        {
            if (p->second == val)
                v.push_back(p->first);
        }
        return v;
    }

    int traversal(TreeNode *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        int l = traversal(root->left);
        int r = traversal(root->right);
        m[root] = l + r + root->val;
        times[m[root]]++;
        return l + r + root->val;
    }
};