#include "leetcode.h"
#include <queue>
#include <unordered_set>
class Solution
{
public:
    bool check(deque<pair<TreeNode *, TreeNode *>> &deq, int x, int y)
    {
        auto xitor = deq.end(), yitor = deq.end();
        for (auto i = deq.begin(); i != deq.end(); i++)
        {
            if (xitor != deq.end() && yitor != deq.end())
                break;
            if (i->first->val == x)
                xitor = i;
            if (i->first->val == y)
                yitor = i;
        }
        return xitor->second != yitor->second;
    }
    bool isCousins(TreeNode *root, int x, int y)
    {
        if (root == nullptr)
            return false;
        deque<pair<TreeNode *, TreeNode *>> cur;
        cur.emplace_back(root, nullptr);
        while (!cur.empty())
        {
            deque<pair<TreeNode *, TreeNode *>> next;
            while (!cur.empty())
            {
                auto [node, parent] = cur.front();
                cur.pop_front();
                if (node->left)
                    next.emplace_back(node->left, node);
                if (node->right)
                    next.emplace_back(node->left, node);
            }
            if (check(next, x, y))
                return true;
            cur = move(next);
        }
        return false;
    }
};
int main()
{
}