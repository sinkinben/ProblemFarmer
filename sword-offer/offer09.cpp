#include "leetcode.h"
class CQueue
{
public:
    stack<int> s1, s2;
    CQueue()
    {
    }

    void appendTail(int value)
    {
        s1.push(value);
    }

    int deleteHead()
    {
        int t = -1;
        if (s2.empty())
        {
            while (!s1.empty())
                s2.push(s1.top()), s1.pop();
            if (!s2.empty())
                t = s2.top(), s2.pop();
        }
        else
        {
            t = s2.top(), s2.pop();
        }
        return t;
    }
};

class CStack
{
public:
    queue<int> q1, q2;
    void push(int e)
    {
        q1.push(e);
    }
    int pop()
    {
        bool x = q1.empty(), y = q2.empty();
        if (!x && y)
        {
            while (q1.size() > 1)
                q2.push(q1.front()), q1.pop();
            int t = q1.front();
            q1.pop();
            return t;
        }
        if (x && !y)
        {
            while (q2.size() > 1)
                q1.push(q2.front()), q2.pop();
            int t = q2.front();
            q2.pop();
            return t;
        }
        return -1;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */