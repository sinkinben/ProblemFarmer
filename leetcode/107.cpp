#include "leetcode.h"
#include <queue>
#include <map>
struct Tuple
{
    TreeNode *ptr;
    int level;
    Tuple(TreeNode *q = nullptr, int l = -1) : ptr(q), level(l) {}
};
class Solution
{
public:
    vector<vector<int>> levelOrderBottom(TreeNode *root)
    {
        if (root == nullptr)
            return vector<vector<int>>();

        map<int, vector<int>> m;
        queue<Tuple> q;
        q.push(Tuple(root, 0));
        while (!q.empty())
        {
            Tuple p = q.front();
            q.pop();
            m[p.level].push_back(p.ptr->val);
            if (p.ptr->left)
                q.push(Tuple(p.ptr->left, p.level + 1));
            if (p.ptr->right)
                q.push(Tuple(p.ptr->right, p.level + 1));
        }
        vector<vector<int>> v;
        for (auto x : m)
            v.push_back(x.second);
        return vector<vector<int>>(v.rbegin(), v.rend());
    }
};