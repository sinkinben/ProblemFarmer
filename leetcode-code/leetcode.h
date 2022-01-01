#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <cassert>
using namespace std;
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
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
template <typename type>
void print2dimension(const type *a[], int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cout << setw(4) << a[i][j];
        cout << endl;
    }
    cout << endl;
}
template <typename type>
void printvv(vector<vector<type>> &vv)
{
    for (auto &v : vv)
    {
        for (auto &x : v)
        {
            printf("%4d", x);
        }
        cout << endl;
    }
    cout << endl;
}