#include "leetcode.h"
#include <unordered_map>
#include <algorithm>
class Solution
{
public:
    vector<int> root;
    string smallestStringWithSwaps(string s, vector<vector<int>> &pairs)
    {
        int len = s.length();
        if (len == 0)
            return s;
        root.resize(len, -1);

        for (auto &v : pairs)
            merge(v[0], v[1]);

        // extract each component nodes
        unordered_map<int, vector<int>> table;
        for (int i = 0; i < len; i++)
            table[find(i)].emplace_back(i);

        for (auto &p : table)
        {
            string chars = "";
            for (int i : p.second)
                chars.push_back(s[i]);
            sort(chars.begin(), chars.end());
            int j = 0;
            for (int i : p.second)
                s[i] = chars[j++];
        }
        return s;
    }

    int find(int x)
    {
        return root[x] == -1 ? x : (root[x] = find(root[x]));
    }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x;
    }
};
int main()
{
    string s = "dcabfge";
    vector<vector<int>> v = {{0, 3}, {1, 2}, {0, 2}, {4, 6}};
    Solution sol;
    cout << sol.smallestStringWithSwaps(s, v) << endl;
}