#include "leetcode.h"
#include <queue>
#include <unordered_map>
class Solution
{
public:
    vector<double> averageOfLevels(TreeNode *root)
    {
        return levelorder(root);
        typedef pair<TreeNode *, int> node;
        unordered_map<int, double> sumrecord;
        unordered_map<int, int> numrecord;
        queue<node> q;
        q.push(node(root, 0));
        while (!q.empty())
        {
            auto n = q.front();
            q.pop();
            sumrecord[n.second] += n.first->val;
            numrecord[n.second]++;
            if (n.first->left != nullptr)
                q.push(node(n.first->left, n.second + 1));
            if (n.first->right != nullptr)
                q.push(node(n.first->right, n.second + 1));
        }
        vector<double> v(numrecord.size());
        for (auto &x : sumrecord)
        {
            v[x.first] = x.second / numrecord[x.first];
        }
        return v;
    }

    vector<double> levelorder(TreeNode *root)
    {
        vector<double> v;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            queue<TreeNode *> nextlevel;
            int64_t sum = 0;
            int counter = 0;
            while (!q.empty())
            {
                auto p = q.front();
                q.pop();
                sum += p->val, counter++;
                if (p->left != nullptr)
                    nextlevel.push(p->left);
                if (p->right != nullptr)
                    nextlevel.push(p->right);
            }
            q = nextlevel;
            v.push_back(sum * 1.0 / counter);
        }
        return v;
    }
};
