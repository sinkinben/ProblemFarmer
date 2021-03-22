#include "leetcode.h"
#include <algorithm>
#include <queue>
class Solution
{
public:
    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> q;
        for (int x : stones)
            q.push(x);
        while (q.size() != 1)
        {
            int x, y;
            x = q.top(), q.pop();
            y = q.top(), q.pop();
            q.push(x - y);
        }
        return q.top();
    }
};

int main()
{
    Solution s;
    vector<int> v({2,7,4,1,8,1});
    cout<<s.lastStoneWeight(v);
}