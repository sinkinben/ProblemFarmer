#include "leetcode.h"
#include <sstream>
#include <algorithm>
#include <map>
class Solution
{
public:
    string mostCommonWord(string paragraph, vector<string> &banned)
    {
        map<string, int> m;
        const string s = "!?\',;.";
        for (char c : s)
        {
            stringstream ss;
            ss << c;
            replaceAll(paragraph, ss.str(), " ");
        }
        transform(paragraph.begin(), paragraph.end(), paragraph.begin(), ::tolower);
        printf("%s\n", paragraph.c_str());
        vector<string> vs = split(paragraph);
        for (string temp : vs)
        {
            m[temp]++;
        }
        for (string temp : banned)
        {
            m.erase(temp);
        }
        map<string, int>::iterator itor = m.begin();
        int maxval = itor->second;
        string t = itor->first;
        while (itor != m.end())
        {
            if (itor->second > maxval)
            {
                maxval = itor->second;
                t = itor->first;
            }
            itor++;
        }
        return t;
    }

    void replaceAll(string &src, string pattern, string target)
    {
        int pos = src.find(pattern);
        while (pos != -1)
        {
            src.replace(pos, pattern.length(), target);
            pos = src.find(pattern);
        }
    }

    vector<string> split(string s)
    {
        istringstream ss(s);
        string temp;
        vector<string> res;
        while (ss >> temp)
        {
            res.push_back(temp);
        }
        return res;
    }
};
int main()
{
    string s = "Bob hit a ball, the hit BALL flew far after it was hit.";
    Solution sol;
    vector<string> v;
    sol.mostCommonWord(s, v);
}