#include "leetcode.h"
#include <algorithm>
#include <map>
class Solution
{
public:
    map<int, int> hash;
    bool isNStraightHand(vector<int> &hand, int W)
    {
        int size = hand.size();
        if (size % W)
        {
            return false;
        }
        for (int x : hand)
        {
            hash[x]++;
        }
        while (!hash.empty())
        {
            if (help(W) == false)
            {
                return false;
            }
        }
        return true;
    }

    bool help(int W)
    {
        map<int, int>::iterator itor = hash.begin();
        int num = itor->first;
        int times = itor->second;
        for (int i = num; i <= (num + W - 1); i++)
        {
            hash[i] -= times;
            if (hash[i] == 0)
                hash.erase(i);
            else if (hash[i] < 0)
                return false;
        }
        return true;
    }
};

int main()
{
}