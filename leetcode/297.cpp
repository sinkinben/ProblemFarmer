#include "leetcode.h"
#include <queue>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec
{
public:
    const string NIL = "null";
    const string SEPARATOR = ",";
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        return levelSerialize(root);
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        return levelDeserialize(data);
    }

    // level order solution
    string levelSerialize(TreeNode *root)
    {
        if (root == nullptr)
            return "";
        queue<TreeNode *> q;
        q.push(root);
        vector<string> result;
        while (!q.empty())
        {
            auto node = q.front();
            q.pop();
            if (node != nullptr)
            {
                result.emplace_back(to_string(node->val));
                q.push(node->left);
                q.push(node->right);
            }
            else
                result.emplace_back(NIL);
        }
        while (result.back() == NIL)
            result.pop_back();
        string str;
        for (auto &x : result)
            str += (x + SEPARATOR);
        if (str.back() == SEPARATOR[0])
            str.pop_back();
        return "[" + str + "]";
    }

    TreeNode *levelDeserialize(string &data)
    {
        if (data.empty())
            return nullptr;
        if (data.front() == '[' && data.back() == ']')
            data = data.substr(1, data.length() - 2);

        auto v = split(data, SEPARATOR);
        int idx = 0, size = v.size();
        auto root = generateNode(v[idx++]);
        assert(root != nullptr);
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            auto node = q.front();
            q.pop();
            if (idx < size)
                node->left = generateNode(v[idx++]);
            if (idx < size)
                node->right = generateNode(v[idx++]);
            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }
        return root;
    }

    TreeNode *generateNode(const string &s)
    {
        return s == NIL ? nullptr : new TreeNode(stoi(s));
    }

    vector<string> split(string &data, const string &sep)
    {
        size_t l = 0;
        size_t r = data.find(sep, l);
        vector<string> result;
        while (r != string::npos)
        {
            result.emplace_back(data.substr(l, r - l));
            l = r + sep.length();
            r = data.find(sep, l);
        }
        if (l < data.length())
            result.emplace_back(data.substr(l));
        return result;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main()
{
    auto root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(7);
    auto t1 = new TreeNode(3);
    auto t2 = new TreeNode(2);
    root->left->left = t1;
    root->right->left = t2;
    t1->left = new TreeNode(-1);
    t2->left = new TreeNode(9);

    Codec codec;
    auto s = codec.levelSerialize(root);
    cout << s << endl;

    auto newRoot = codec.levelDeserialize(s);

    cout << codec.levelSerialize(newRoot) << endl;
}
