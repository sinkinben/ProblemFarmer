#define min(a,b) ((a<b)?a:b)
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        return sol2(strs);
    }

    string sol2(vector<string> &vs)
    {
        if (vs.size() == 0) return "";
        auto &s = vs[0];
        for (auto &x: vs)
        {
            while (x.find(s, 0) != 0)
                s.pop_back();
        }
        return s;
    }

    string sol1(vector<string> &strs)
    {
        if (strs.size() == 0) return "";
        int k = 0;
        auto check = [&](int c)->bool {
            char ch = strs[0][c];
            for (auto &s: strs) 
                if (s[c] != ch)
                    return false;
            return true; 
        };
        int minlen = 0x3f3f3f3f;
        for (auto &s: strs)
            minlen = min(minlen, s.length());
        while (k < minlen)
        {
            if (check(k)) k++;
            else break;
        }
        return strs[0].substr(0, k);
    }
};
