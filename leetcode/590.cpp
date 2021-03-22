#include "leetcode.h"
#include <stack>
#include <algorithm>
class Solution
{
public:
    vector<int> result;
    vector<int> postorder(Node *root)
    {
        if (root == nullptr)
            return result;
        // postorderRecursion(root);
        postorderIteration(root);
        return result;
    }

    void postorderRecursion(Node *p)
    {
        if (p == nullptr)
            return;
        for (auto i = p->children.begin(); i != p->children.end(); i++)
        {
            postorderRecursion(*i);
        }
        result.push_back(p->val);
    }

    void postorderIteration(Node *root)
    {
        auto p = root;
        stack<Node *> s;
        s.push(p);
        while (!s.empty())
        {
            p = s.top(), s.pop();
            result.push_back(p->val);
            for (auto x : p->children)
                s.push(x);
        }
        reverse(result.begin(), result.end());
    }
};
