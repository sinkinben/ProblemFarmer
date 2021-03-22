#include "leetcode.h"
class Solution
{
public:
    vector<int> nextLargerNodes(ListNode *head)
    {
        vector<int> v;
        auto p = head;
        while (p)
        {
            v.push_back(p->val);
            p = p->next;
        }
        stack<int> s;
        int len = v.size();
        vector<int> result(len, 0);
        for (int i = 0; i < len; i++)
        {
            if (s.empty() || v[i] <= v[s.top()])
                s.push(i);
            else
            {
                while (!s.empty() && v[s.top()] < v[i])
                {
                    int x = s.top();
                    s.pop();
                    result[x] = v[i];
                }
                s.push(i);
            }
        }
        return result;
    }
};