#include "leetcode.h"
class A
{
public:
    virtual int sum(int n) { return 0; }
};
static A *func[2];
class B : public A
{
public:
    int sum(int n) { return n + func[!!n]->sum(n - 1); }
};
class Solution
{
public:
    int sumNums(int n)
    {
        A a;
        B b;
        func[0] = &a, func[1] = &b;
        return func[!!n]->sum(n);
    }
};