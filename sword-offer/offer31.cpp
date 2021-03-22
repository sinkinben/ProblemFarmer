#include "leetcode.h"
class Solution
{
public:
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> s;
        int popIdx = 0;
        for (int x : pushed)
        {
            s.push(x);
            while (!s.empty() && s.top() == popped[popIdx])
                s.pop(), popIdx++;
        }
        return s.empty() && popIdx == (int)popped.size();
    }

    bool swordOfferMethod(vector<int> &pushed, vector<int> &popped)
    {

        if (popped.empty())
            return pushed.empty();
        int pushlen = pushed.size();
        int poplen = popped.size();
        stack<int> s;
        int pushIdx = 0, popIdx = 0;
        while (popIdx < poplen)
        {
            while (s.empty() || popped[popIdx] != s.top())
            {
                if (pushIdx >= pushlen)
                    break;
                s.push(pushed[pushIdx++]);
            }
            if (s.top() != popped[popIdx])
                break;
            s.pop(), popIdx++;
        }
        return s.empty() && popIdx >= poplen;
    }
};

int main()
{
}