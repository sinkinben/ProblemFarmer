#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Solution
{
    int hash[26] = {0};

public:
    int countCharacters(vector<string> &words, string chars)
    {
        int ans = 0;
        if (words.size() == 0 || chars == "")
        {
            return 0;
        }
        int len = chars.length();
        for (int i = 0; i < len; i++)
        {
            hash[chars[i] - 'a']++;
        }
        int size = words.size();
        for (int i = 0; i < size; i++)
        {
            if (judge(words[i]))
                ans += words[i].length();
        }
        return ans;
    }

    bool judge(string s)
    {
        int hashCopy[26] = {0};
        memcpy(hashCopy, hash, 26 * sizeof(int));
        if (s == "" || s.length() == 0)
            return false;
        int len = s.length();
        for (int i = 0; i < len; i++)
        {
            if (hashCopy[s[i] - 'a'] == 0)
                return false;
            else
            {
                hashCopy[s[i] - 'a']--;
            }
        }
        return true;
    }
};