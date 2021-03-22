#include "leetcode.h"
#include <iostream>
class Solution
{
public:
    const string strMap[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> v;
    vector<string> letterCombinations(string digits)
    {
        int len = digits.length();
        if (len == 0)
        {
            return v;
        }
        backTrack(digits, 0, "");
        return v;
    }
    void backTrack(string &digits, int now, string cur)
    {
        if (now == (int)digits.length())
        {
            v.push_back(cur);
            return;
        }
        for (char x : strMap[digits[now] - '0'])
        {
            cur.push_back(x);
            backTrack(digits, now + 1, cur);
            cur.pop_back();
        }
    }
};
int main()
{
    printf("[%c]\n", -48 + '0');
    Solution sol;
    auto v = sol.letterCombinations("23");
    for (auto x : v)
    {
        cout << x << ' ';
    }
}