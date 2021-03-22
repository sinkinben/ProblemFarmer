#include "leetcode.h"
#include <sstream>
#include <set>
#include <vector>
#include <map>
class Solution
{
public:
    vector<string> uncommonFromSentences(string A, string B)
    {
        auto a = split(A);
        auto b = split(B);
        vector<string> result;
        for (auto &x : a)
        {
            if (x.second == 1 && b.find(x.first) == b.end())
                result.push_back(x.first);
        }
        for (auto &x : b)
        {
            if (x.second == 1 && a.find(x.first) == a.end())
                result.push_back(x.first);
        }
        return result;
    }

    map<string, int> split(string &s)
    {
        map<string,int> m;
        istringstream stream(s);
        string t;
        while (stream >> t)
        {
            m[t]++;
        }
        return m;
    }
};