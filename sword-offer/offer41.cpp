#include "leetcode.h"
#include <algorithm>
#include <set>

class MedianFinder
{
public:
    /** initialize your data structure here. */
    int total = 0;
    vector<int> small, large;
    inline void pushHeap(int x, vector<int> &v, bool bigHeap)
    {
        v.push_back(x);
        if (bigHeap)
            push_heap(v.begin(), v.end(), greater<int>());
        else
            push_heap(v.begin(), v.end(), less<int>());
    }

    inline int popHeap(vector<int> &v, bool bigHeap)
    {
        int x = v[0];
        if (bigHeap)
            pop_heap(v.begin(), v.end(), greater<int>());
        else
            pop_heap(v.begin(), v.end(), less<int>());
        v.pop_back();
        return x;
    }

    void addNum(int x)
    {
        total++;
        if (total % 2)
        {
            // insert into the small set
            pushHeap(x, large, true);
            x = popHeap(large, true);
            pushHeap(x, small, false);
        }
        else
        {
            pushHeap(x, small, false);
            x = popHeap(small, false);
            pushHeap(x, large, true);
        }
    }

    double findMedian()
    {
        if (total == 0)
            return -1;
        if (total % 2)
            return small[0];
        else
            return ((double)small[0] + (double)large[0]) / 2;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main()
{
    MedianFinder finder;
    finder.addNum(1);
    finder.addNum(2);
    cout << finder.findMedian() << endl;
    finder.addNum(3);
    cout << finder.findMedian() << endl;
}