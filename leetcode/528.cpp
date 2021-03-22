#include "leetcode.h"
class Solution
{
public:
    int total = 0;
    vector<int> line;
    Solution(vector<int> &w)
    {
        int len = w.size();
        line.resize(len);
        for (int i = 0; i < len; i++)
        {
            total += w[i];
            line[i] = total;
        }
    }
    int pickIndex()
    {
        int k = rand() % total;
        int len = line.size();
        for (int i = 0; i < len; i++)
        {
            if (k<=line[i])
                return i;
        }
        return 0;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
int main()
{
    int k = rand();
}