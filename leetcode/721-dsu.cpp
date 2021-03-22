#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "leetcode.h"
class Solution
{
public:
    unordered_map<string, string> root;
    unordered_map<string, string> emailName;
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {
        for (auto &v : accounts)
        {
            string &name = v.front();
            int size = v.size();
            emailName[v[1]] = name;
            for (int i = 2; i < size; i++)
            {
                emailName[v[i]] = name;
                merge(v[1], v[i]);
            }
        }

        vector<vector<string>> ans;
        unordered_map<string, vector<string>> table;
        for (auto &p : emailName)
        {
            auto email = p.first, name = p.second;
            table[find(email)].emplace_back(email);
        }

        for (auto &p : table)
        {
            auto v = p.second;
            sort(v.begin(), v.end());
            v.insert(v.begin(), emailName[p.first]);
            ans.emplace_back(v);
        }
        return ans;
    }

    string find(const string &x)
    {
        return root.count(x) == 0 ? (x) : (root[x] = find(root[x]));
    }

    void merge(string x, string y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x;
    }
};

int main()
{
    vector<vector<string>> vs = {{"John", "e1", "e2", "e3"},
                                 {"John", "johnnybravo@mail.com"},
                                 {"John", "e4", "e3", "e5", "e2"},
                                 {"Mary", "mary@mail.com"}};
    Solution sol;
    auto v = sol.accountsMerge(vs);
    for (auto &x : v)
    {
        for (auto &k : x)
            cout << k << " ";
        cout << endl;
    }
}
