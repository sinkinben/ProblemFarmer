#include "leetcode.h"
#include <unordered_map>
#include <algorithm>
class Solution
{
public:
    vector<int> root;
    int result = 0;
    int makeConnected(int n, vector<vector<int>> &connections)
    {
        int E = connections.size();
        if (n == 0 || n == 1)
            return 0;
        if (E < n - 1)
            return -1;
        root.resize(n), root.assign(n, -1);

        for (auto &v : connections)
        {
            int a = v[0], b = v[1];
            merge(a, b);
        }
        int components = count(root.begin(), root.end(), -1);
        if (counter >= (components - 1))
            return components - 1;
        return -1;
    }

    int find(int x)
    {
        return root[x] == -1 ? x : (root[x] = find(root[x]));
    }

    int counter = 0;
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x;
        else
        {
            // there is a duplicate edge
            counter++;
        }
    }
};

int main()
{
    int n = 6;
    vector<vector<int>> c = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}};
    // vector<vector<int>> c = {{0, 1}, {0, 2}, {0, 3}, {1, 2}};
    // vector<vector<int>> c = {{0, 1}, {0, 2}, {3, 4}, {2, 3}};
    Solution sol;
    cout << sol.makeConnected(n, c);
}