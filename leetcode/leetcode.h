#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <numeric>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Calcute running time
#define CLOCK_START(start) (start = clock())
#define GET_DURATION(start) (1.0 * (clock() - start) / CLOCKS_PER_SEC)

template <class T>
void print(vector<T> &vec)
{
    for (T &x : vec)
        cout << x << ' ';
    cout << '\n';
}

ListNode *makeList(int n, vector<int> vec)
{
    if (vec.size() != n)
    {
        vec.resize(n);
        std::iota(vec.begin(), vec.end(), 0);
    }
    ListNode dummy(-1);
    ListNode *cur = &dummy;
    for (int x : vec)
    {
        cur->next = new ListNode(x);
        cur = cur->next;
    }
    return dummy.next;
}
