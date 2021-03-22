#include "../leetcode/leetcode.h"
class Solution
{
public:
    string replaceSpace(string s)
    {
    }
    string method1(string &s)
    {
        const string target = "%20";
        const string src = " ";
        size_t pos = s.find(src, 0);
        while (pos != string::npos)
        {
            s.replace(pos, src.length(), target);
            pos = pos + target.length();
            pos = s.find(src, pos);
        }
        return s;
    }
};