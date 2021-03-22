#include "leetcode.h"
#include <queue>
#include <map>
class Solution
{
public:
    int minDepth(TreeNode *root)
    {
        return (root == nullptr) ? 0 : bfs(root);
    }
    int bfs(TreeNode *root)
    {
        typedef pair<TreeNode *, int> Node;
        queue<Node> q;
        q.push(Node(root, 1));
        while (!q.empty())
        {
            auto &node = q.front();
            q.pop();
            if (node.first->left == nullptr && node.first->right == nullptr)
                return node.second;
            if (node.first->left != nullptr)
                q.push(Node(node.first->left, node.second + 1));
            if (node.first->right != nullptr)
                q.push(Node(node.first->right, node.second + 1));
        }
        return -1;
    }
};