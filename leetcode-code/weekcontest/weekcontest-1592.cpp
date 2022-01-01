#include "../leetcode.h"
class Solution
{
public:
    string reorderSpaces(string text)
    {
        int spaces = 0;
        for (char x : text)
            spaces += (x == ' ');

        vector<string> words;
        stringstream ss(text);
        string buf;
        while (ss >> buf)
            words.emplace_back(buf);

        buf = "";

        int len = words.size();
        if (len == 1)
            return words.back().append(spaces, ' ');

        int k = spaces / (len - 1);
        for (int i = 0; i < len - 1; i++)
            buf.append(words[i]), buf.append(k, ' ');
        buf.append(words[len - 1]), buf.append(spaces - (k * (len - 1)), ' ');
        return buf;
    }
};
int main()
{
    Solution sol;
    // string s = "  walks  udp package   into  bar a";
    // string s = "  this   is  a sentence ";
    string s = " practice   makes   perfect";
    cout << "{" << sol.reorderSpaces(s) << "}" << endl;
}