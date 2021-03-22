#include "leetcode.h"
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
    vector<vector<int>> levelOrder(TreeNode *root)
    {
    }
    vector<vector<int>> method2(TreeNode *root)
    {
        vector<vector<int>> ans;
        if (root == nullptr)
            return ans;
        deque<TreeNode *> q;
        q.push_back(root);
        while (!q.empty())
        {
            vector<int> cur;
            deque<TreeNode *> next;
            while (!q.empty())
            {
                TreeNode *p = nullptr;
                // 打印奇数层
                if (ans.size() % 2 == 0)
                {
                    p = q.front();
                    q.pop_front();
                    if (p->left)
                        next.push_back(p->left);
                    if (p->right)
                        next.push_back(p->right);
                }
                // 打印偶数层
                else
                {
                    p = q.back();
                    q.pop_back();
                    if (p->right)
                        next.push_front(p->right);
                    if (p->left)
                        next.push_front(p->left);
                }
                cur.push_back(p->val);
            }
            if (!cur.empty())
                ans.push_back(cur);
            q = next;
        }

        return ans;
    }

    auto method1(TreeNode *root)
    {
        vector<vector<int>> ans;
        if (root == NULL)
            return ans;
        queue<TreeNode *> q;
        q.push(root);
        bool needRev = false;
        while (!q.empty())
        {
            queue<TreeNode *> next;
            vector<int> v;
            while (!q.empty())
            {
                auto p = q.front();
                q.pop();
                v.push_back(p->val);
                if (p->left)
                    next.push(p->left);
                if (p->right)
                    next.push(p->right);
            }
            q = next;
            if (needRev)
                reverse(v.begin(), v.end());
            ans.push_back(v);
            needRev = !needRev;
        }
        return ans;
    }
};

int main()
{
    deque<int> q;
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);
    q.pop_back();
    cout << q.front();
}
