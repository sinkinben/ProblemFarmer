#include "leetcode.h"
#include <stack>
class Solution
{
public:
    vector<int> result;
    vector<int> preorder(Node *root)
    {
        if (root == nullptr)
            return result;
        preorderIteration(root);
        return result;
    }

    void preorderRecursion(Node *p)
    {
        if (p == nullptr)
            return;
        result.push_back(p->val);
        for (auto x : p->children)
            preorderRecursion(x);
    }

    void preorderIteration(Node *root)
    {
        auto p = root;
        stack<Node *> s;
        s.push(p);
        while (!s.empty())
        {
            p = s.top(), s.pop();
            result.push_back(p->val);
            for (auto i = p->children.rbegin(); i != p->children.rend(); i++)
            {
                s.push(*i);
            }
        }
    }
};