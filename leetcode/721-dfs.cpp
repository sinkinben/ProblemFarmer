#include "leetcode.h"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
class Solution
{
public:
    unordered_map<string, string> mailName;
    unordered_map<string, vector<string>> graph;
    unordered_set<string> visited;
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {
        for (auto &v : accounts)
        {
            string &name = v[0];
            int size = v.size();
            for (int i = 1; i < size - 1; i++)
            {
                mailName[v[i]] = name;
                graph[v[i]].emplace_back(v[i + 1]);
                graph[v[i + 1]].emplace_back(v[i]);
            }

            // some account has only one email
            if (size == 2 && graph.find(v[1]) == graph.end())
                graph[v[1]] = vector<string>();

            mailName[v[size - 1]] = name;
        }

        vector<vector<string>> ans;
        for (auto &p : graph)
        {
            auto &now = p.first;
            auto &list = p.second;
            vector<string> data({mailName[now]});
            if (visited.count(now) == 0)
            {
                dfs(data, now, list);
                sort(data.begin() + 1, data.end());
                ans.emplace_back(data);
            }
        }
        return ans;
    }
    void dfs(vector<string> &data, const string &now, vector<string> &list)
    {
        visited.insert(now);
        data.emplace_back(now);
        for (auto &x : list)
        {
            if (visited.count(x) == 0)
            {
                dfs(data, x, graph[x]);
            }
        }
    }
};

int main()
{
    vector<vector<string>> vs = {{"John", "johnsmith@mail.com", "john00@mail.com"},
                                 {"John", "johnnybravo@mail.com"},
                                 {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
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