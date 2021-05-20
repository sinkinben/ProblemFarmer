#include "leetcode.h"
#include <unordered_map>
class Solution
{
public:
    vector<string> topKFrequent(vector<string> &words, int k)
    {
        unordered_map<string, int> table;
        for (auto &s : words)
            table[s]++;
        vector<string> res;
        auto cmp = [&](string &a, string &b) {
            int x = table[a], y = table[b];
            return x > y || x == y && a < b;
        };
        for (auto &[word, freq] : table)
        {
            res.emplace_back(word);
            push_heap(res.begin(), res.end(), cmp);
            if ((int)res.size() == k + 1)
            {
                pop_heap(res.begin(), res.end(), cmp);
                res.pop_back();
            }
        }
        sort(res.begin(), res.end(), cmp);
        return res;
    }
};
int main()
{
    vector<string> v = {"i", "love", "leetcode", "i", "love", "coding"};
    v = {"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"};
    Solution sol;
    auto res = sol.topKFrequent(v, 4);
    for (auto &s : res)
        cout << s << ' ';
}