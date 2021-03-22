#include "leetcode.h"
#include <unordered_map>
#include <cassert>
class Solution
{
public:
    unordered_map<string, string> root;
    vector<string> trulyMostPopular(vector<string> &names, vector<string> &synonyms)
    {
        vector<string> ans;
        unordered_map<string, int> table;
        for (auto &s : names)
        {
            int idx = s.find('(');
            string n = s.substr(0, idx);
            int val = stoi(s.substr(idx + 1, s.length() - 2 - idx));
            table[n] = val;
        }
        for (auto &str : synonyms)
        {
            int idx = str.find(',');
            string n1 = str.substr(1, idx - 1);
            string n2 = str.substr(idx + 1, str.length() - 2 - idx);
            merge(n1, n2);
        }
        unordered_map<string, int> mapAns;
        for (auto &p : table)
            mapAns[find(p.first)] += p.second;

        for (auto &p : mapAns)
        {
            string s = p.first + "(" + to_string(p.second) + ")";
            ans.emplace_back(s);
        }

        return ans;
    }

    string find(string x)
    {
        return root.count(x) == 0 ? (x) : (root[x] = find(root[x]));
    }

    void merge(string x, string y)
    {
        x = find(x), y = find(y);
        if (x < y)
            root[y] = x;
        else if (x > y)
            root[x] = y;
        // do nothing if x == y
    }
};

int main()
{
    vector<string> names = {"John(15)", "Jon(12)", "Chris(13)", "Kris(4)", "Christopher(19)"};
    vector<string> s = {"(Jon,John)", "(John,Johnny)", "(Chris,Kris)", "(Chris,Christopher)"};
    Solution sol;
    auto v = sol.trulyMostPopular(names, s);
    for (auto x : v)
        cout << x << endl;
}