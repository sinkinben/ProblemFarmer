#include "leetcode.h"
class Solution
{
public:
    bool isMatch(string s, string p)
    {
        if (s == "" || p == "")
            return s == p;
        return match(s, p, 0, 0);
    }

    bool match(const string &s, const string &p, int sidx, int pidx)
    {
        bool x = (sidx == (int)s.length());
        bool y = (pidx == (int)p.length());
        if (x && y)
            return true;
        if (x ^ y)
            return false;
        if (pidx + 1 < (int)p.length() && p[pidx + 1] == '*')
        {
            if (match(s, p, sidx, pidx + 2))
                return true;
            if (s[sidx] == p[pidx] || p[pidx] == '.')
                return match(s, p, sidx + 1, pidx);
        }
        if (s[sidx] == p[pidx] || p[pidx] == '.')
            return match(s, p, sidx + 1, pidx + 1);
        return false;
    }
};