#include <cassert>
#include <cstdio>
#include <stack>
#include <map>
#define LEN 7
using namespace std;
map<char, int> m;

int help(char op, int a, int b)
{
    if (op == '+')
    {
        return (a + b);
    }
    else if (op == '-')
    {
        return (a - b);
    }
    else if (op == 'x')
    {
        return (a * b);
    }
    else
    {
        return (a / b);
    }
}
int calc(const char *str)
{
    stack<int> snum;
    stack<char> sop;
    for (int i = 0; i < LEN; i++)
    {
        if ('0' <= str[i] && str[i] <= '9')
            snum.push(str[i] - '0');
        else
        {
            if (sop.empty())
            {
                sop.push(str[i]);
                continue;
            }
            if (m[str[i]] > m[sop.top()])
                sop.push(str[i]);
            else
            {
                char op = sop.top();
                sop.pop();
                int b = snum.top();
                snum.pop();
                int a = snum.top();
                snum.pop();
                snum.push(help(op, a, b));
                sop.push(str[i]);
            }
        }
    }
    while (!sop.empty())
    {
        char op = sop.top();
        sop.pop();
        int b = snum.top();
        snum.pop();
        int a = snum.top();
        snum.pop();
        snum.push(help(op, a, b));
    }
    return snum.top();
}
int main()
{
    m['+'] = 1, m['-'] = 1, m['x'] = 2, m['/'] = 2;
    int n;
    scanf("%d", &n);
    char str[LEN + 1] = "";
    while (n--)
    {
        scanf("%s", str);
        if (calc(str) == 24)
            puts("Yes");
        else
        {
            puts("No");
        }
    }
}
/*
10
9+3+4x3
 */