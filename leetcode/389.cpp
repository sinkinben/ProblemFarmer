#include "leetcode.h"
class Solution
{
public:
    char findTheDifference(string s, string t)
    {
        char k = 0;
        for (auto x : s)
            k ^= x;
        for (auto x : t)
            k ^= x;
        return k;
    }
};
int main()
{
    string a = "", t = "y";
    Solution s;
    cout << s.findTheDifference(a, t);
}