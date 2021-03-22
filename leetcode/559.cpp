#include "leetcode.h"
#include <queue>
class Node
{
public:
    int val;
    vector<Node *> children;
    Node() {}
    Node(int _val) { val = _val; }
    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};
class Solution
{
public:
    int maxDepth(Node *root)
    {
        return levelorder(root);
    }

    int levelorder(Node *root)
    {
        auto p = root;
        queue<Node *> q;
        q.push(p);
        int level = 1;
        while (!q.empty())
        {
            queue<Node *> nextlevel;
            while (!q.empty())
            {
                p = q.front(), q.pop();
                for (auto x : p->children)
                    nextlevel.push(x);
            }
            level += (!nextlevel.empty());
            q = nextlevel;
        }
        return level;
    }
};