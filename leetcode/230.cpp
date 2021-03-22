#include <cstdio>
#include <>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    int kthSmallest(TreeNode *root, int k)
    {
        int ans = -1;
        inorder(root, k, ans);
        return ans;
    }

    void inorder(TreeNode *root, int &k, int &ans)
    {
        if (root == NULL)
            return;
        inorder(root->left, k, ans);
        k--;
        if (k == 0)
        {
            ans = root->val;
            return;
        }
        inorder(root->right, k, ans);
    }
};

int main()
{
}
