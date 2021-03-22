#include "leetcode.h"
#include <list>
class Solution
{
public:
    int lastRemaining(int n, int m)
    {
        list<int> li;
        for (int i = 0; i < n; i++)
            li.push_back(i);
        auto p = li.begin();
        while (li.size() > 1)
        {
            for (int i = 1; i < m; i++)
            {
                p++;
                if (p == li.end())
                    p = li.begin();
            }
            auto next = ++p;
            if (next == li.end())
                next = li.begin();
            li.erase(--p);
            p = next;
        }
        return li.back();
    }
};