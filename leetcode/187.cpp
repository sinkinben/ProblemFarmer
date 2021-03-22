#include "leetcode.h"
#include <unordered_map>
#include <bitset>
class Solution
{
public:
    unordered_map<char, int> m = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
    vector<string> findRepeatedDnaSequences2(string s)
    {
        int len = s.length();
        vector<string> v;
        if (len < 10)
            return v;
        uint32_t val = 0;              //val只需要低20bit
        uint32_t mask = (1 << 20) - 1; //低20位全1
        bitset<1 << 20> s1, s2;
        for (int i = 0; i < 10; i++)
            val = (val << 2) | m[s[i]];
        s1.set(val);

        for (int i = 10; i < len; i++)
        {
            val = ((val << 2) & mask) | m[s[i]];
            if (s2[val])
                continue;
            if (s1[val])
            {
                v.push_back(s.substr(i - 9, 10));
                s2.set(val);
            }
            else
            {
                s1.set(val);
            }
        }
        return v;
    }
    vector<string> findRepeatedDnaSequences(string s)
    {
        unordered_map<string, int> m;
        vector<string> v;
        size_t len = s.length();
        for (int i = 0; (i + 9) < len; i++)
        {
            m[s.substr(i, 10)]++;
        }

        for (auto x : m)
        {
            if (x.second > 1)
                v.push_back(x.first);
        }
        return v;
    }
};
int main()
{
    bitset<1 << 20> s;
    cout << 2 * sizeof(s) / 1024 << endl;
}
