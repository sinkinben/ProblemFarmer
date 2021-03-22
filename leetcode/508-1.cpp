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

public:
    map<TreeNode *, int> m;
    map<int, int> times;
    vector<int> findFrequentTreeSum(TreeNode *root)
    {
        traversal(root);
        // for (auto itor = m.begin(); itor != m.end(); itor++)
        // {
        //     cout << itor->first->val << " " << itor->second << endl;
        // }
        int maxVal = -1;
        for (auto i = times.begin(); i != times.end(); i++)
        {
            maxVal = max(maxVal, i->second);
        }
        vector<int> v;
        for (auto i = times.begin(); i != times.end(); i++)
        {
            if (i->second == maxVal)
                v.push_back(i->first);
        }
        return v;
    }

    void traversal(TreeNode *root)
    {
        if (root == NULL)
            return;
        int val = 0;
        inorderSum(root, val);
        m[root] = val;
        times[val]++;
        traversal(root->left);
        traversal(root->right);
    }

    void inorderSum(TreeNode *root, int &val)
    {
        if (root == NULL)
            return;
        inorderSum(root->left, val);
        val += root->val;
        inorderSum(root->right, val);
    }
};

int main()
{
}